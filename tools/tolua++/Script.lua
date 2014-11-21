$[
local loaded = package.loaded

loaded.CCView = loaded.CCView()
loaded.CCFileUtils = loaded.CCFileUtils()
loaded.CCApplication = loaded.CCApplication()
loaded.CCDirector = loaded.CCDirector()
loaded.CCUserDefault = loaded.CCUserDefault()
loaded.CCKeyboard = loaded.CCKeyboard()
loaded.oContent = loaded.oContent()
loaded.oData = loaded.oData()

local CCLuaLog = loaded.CCLuaLog
loaded.cclog = function(...)
    CCLuaLog(string.format(...))
end
loaded.CCLuaLog = nil

local CCMessageBox = loaded.CCMessageBox
loaded.ccmsg = function(title, ...)
    CCMessageBox(string.format(...), title)
end
loaded.CCMessageBox = nil

local yield = coroutine.yield
local wrap = coroutine.wrap
local create = coroutine.create
local resume = coroutine.resume
local status = coroutine.status
local CCDirector = loaded.CCDirector
local table_insert = table.insert
local table_remove = table.remove
local type = type

local function wait(cond)
	while cond(CCDirector.deltaTime) do
		yield()
	end
end

local function once(job)
	return wrap(function(...)
		job(...)
		return true
	end)
end

local function loop(job)
	return wrap(function(...)
		local _job = job
		local worker = create(_job)
		repeat
			local _,result = resume(worker,...)
			if status(worker) == "dead"then
				worker = create(_job)
			end
			yield(result)
		until false
	end)
end

local function seconds(duration)
	local time = 0
	return function(deltaTime)
		time = time + deltaTime
		return time < duration
	end
end

local function cycle(duration,work)
	local time = 0
	return function(deltaTime)
		time = time + deltaTime
		if time < duration then
			work(deltaTime)
			return true
		end
		return false
	end
end

local oRoutine =
{
	remove = function(self,routine)
		local pos
		for i = 1,#self do
			if self[i] == routine then
				pos = i
				break
			end
		end
		if pos then
			table_remove(self,pos)
		end
	end,
	clear = function(self)
		while #self > 0 do
			table_remove(self)
		end
	end,
	wait = wait,
	once = once,
	loop = loop,
	seconds = seconds,
	cycle = cycle,
}

setmetatable(oRoutine,
{
	__call = function(self,routine)
		table_insert(self,routine)
	end,
})

oRoutine.start = function(self)
	CCDirector:schedule(function()
		local i,count = 1,#self
		while i <= count do
			if self[i]() then
				if i < count then
					self[i] = self[count]
				end
				table_remove(self,count)
				i = i-1
				count = count-1
			end
			i = i+1
		end
	end)
end

oRoutine.stop = function(self)
	CCDirector:unschedule()
end

oRoutine:start()

loaded.oRoutine = oRoutine

local CCArray = loaded.CCArray
local CCArray_index = CCArray.__index
local CCArray_get = CCArray.get
CCArray.__index = function(self,key)
	if type(key) == "number" then
		return CCArray_get(self,key)
	end
	return CCArray_index(self,key)
end

local CCArray_newindex = CCArray.__newindex
local CCArray_set = CCArray.set
CCArray.__newindex = function(self,key,value)
	if type(key) == "number" then
		CCArray_set(self,key,value)
	else
		CCArray_newindex(self,key,value)
	end
end

local CCDictionary = loaded.CCDictionary
local CCDictionary_index = CCDictionary.__index
local CCDictionary_get = CCDictionary.get
CCDictionary.__index = function(self,key)
	local item = CCDictionary_get(self,key)
	if item ~= nil then return item end
	return CCDictionary_index(self,key)
end

local CCDictionary_set = CCDictionary.set
CCDictionary.__newindex = function(self,key,value)
	CCDictionary_set(self,key,value)
end

local oEvent = loaded.oEvent
local oEvent_args = {}
local oEvent_send = oEvent.send
oEvent.send = function(self,name,args)
	oEvent_args[name] = args
	oEvent_send(self,name)
	oEvent_args[name] = nil
end

local oEvent_remove = oEvent.remove
oEvent.remove = function(self,name)
	oEvent_args[name] = nil
	oEvent_remove(self,name)
end

local oListener = loaded.oListener
loaded.oListener = function(name,handler)
	return oListener(name,
			function(event)
				handler(oEvent_args[name],event)
			end)
end

local oAction = loaded.oAction
local oAction_add = oAction.add
local oRoutine_once = oRoutine.once
oAction.add = function(self,id,priority,reaction,recovery,access,routine,stop)
	oAction_add(self,
		id,
		priority,
		reaction,
		recovery,
		access,
		function()
			return oRoutine_once(routine)
		end,
		stop)
end

local oCache = loaded.oCache
local oCache_clear = oCache.clear
oCache.clear = function(self)
	oCache_clear()
end
local oCache_removeUnused = oCache.removeUnused
oCache.removeUnused = function(self)
	oCache_removeUnused()
end
local oCache_poolCollect = oCache.Pool.collect
oCache.Pool.collect = function(self)
	return oCache_poolCollect()
end
oCache.Texture = loaded.CCTextureCache()
loaded.CCTextureCache = nil

local function _loadTextureAsync(filename, loaded)
	if type(filename) == "table" then
		local length = #filename
		local count = 0
		oCache.Texture:loadAsync(filename,
			function(name)
				if loaded then
					loaded(name)
				end
				count = count + 1
			end)
		return function()
			return not (count == length)
		end
	elseif type(filename) == "string" then
		local isloaded = false
		oCache.Texture:loadAsync(filename,
			function(name)
				if loaded then
					loaded(name)
				end
				isloaded = true
			end)
		return function()
			return not isloaded
		end
	end
end

local oSound = require("oSound")
local oMusic = require("oMusic")
local function _loadAsync(filename, loaded)
	local extension = string.match(filename, "%.([^%.\\/]*)$")
	if extension then extension = string.lower(extension) end
	local itemType = nil
	if extension == "png" or extension == "jpg" or extension == "tiff" or extension == "webp" then
		return _loadTextureAsync(filename, loaded)
	else
		local isLoaded = false
		local function loader()
			if not isLoaded then
				isLoaded = true
				if loaded then
					loaded(filename)
				end
				return true
			else
				return false
			end
		end
		if extension == "model" then
			itemType = "Model"
		elseif extension == "clip" then
			itemType = "Clip"
		elseif extension == "frame" then
			itemType = "Animation"
		elseif extension == "effect" then
			itemType = "Effect"
		elseif extension == "par" then
			itemType = "Particle"
		elseif extension == "wav" then
			oSound:load(filename)
			return loader
		elseif extension == "mp3" then
			oMusic:preload(filename)
			return loader
		else
			CCLuaLog(string.format("[ERROR] Unsupported file to load: %s", filename))
			loaded = nil
			return loader
		end
		local cacheType = oCache[itemType]
		cacheType["load"](cacheType, filename)
		return loader
	end
end

local function loadAsync(_, filename, loaded)
	if type(filename) == "string" then
		wait(_loadAsync(filename, loaded))
	elseif type(filename) == "table" then
		for _,item in ipairs(filename) do
			wait(_loadAsync(item, loaded))
		end
	end
end
oCache.loadAsync = loadAsync

local function swapAsync(cache, listA, listB, loaded)
	local removal_list = {}
	for _,itemA in ipairs(listA) do
		local found = false
		for _,itemB in ipairs(listB) do
			if itemA == itemB then
				found = true
				break
			end
		end
		if not found then
			table_insert(removal_list, itemA)
		end
	end
	local added_list = {}
	for _,itemB in ipairs(listB) do
		local found = false
		for _,itemA in ipairs(listA) do
			if itemB == itemA then
				found = true
				break
			end
		end
		if not found then
			table_insert(added_list, itemB)
		end
	end
	for _,item in ipairs(removal_list) do
		local extension = string.match(item, "%.([^%.\\/]*)$")
		if extension then extension = string.lower(extension) end
		local itemType = nil
		if extension == "png" or extension == "jpg" or extension == "tiff" or extension == "webp" then
			itemType = "Texture"
		elseif extension == "model" then
			itemType = "Model"
		elseif extension == "clip" then
			itemType = "Clip"
		elseif extension == "frame" then
			itemType = "Animation"
		elseif extension == "effect" then
			itemType = "Effect"
		elseif extension == "par" then
			itemType = "Particle"
		elseif extension == "wav" then
			oSound:unload(item)
		elseif extension == "mp3" then
		else
			CCLuaLog(string.format("[ERROR] Unsupported file to unload: %s", item))
		end
		if itemType ~= nil then
			local cacheType = oCache[itemType]
			cacheType["unload"](cacheType, item)
		end
	end
	cache:loadAsync(added_list, loaded)
end
oCache.swapAsync = swapAsync

_G["Dorothy"] = (function()
	local tb
	local function gettb()
		tb = {}
		for k,v in pairs(package.loaded) do
			tb[k] = v
		end
		setmetatable(tb,{__index=_G})
		return tb
	end
	return function() return 1,tb or gettb() end
end)()
$]
