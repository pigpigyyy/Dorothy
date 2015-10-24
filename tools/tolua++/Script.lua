$[
for k,v in pairs(package.loaded) do
	package.loaded[k] = nil
end

local builtin = _G.builtin

builtin.CCView = builtin.CCView()
builtin.CCApplication = builtin.CCApplication()
builtin.CCDirector = builtin.CCDirector()
builtin.CCUserDefault = builtin.CCUserDefault()
builtin.CCKeyboard = builtin.CCKeyboard()
builtin.oContent = builtin.oContent()
builtin.oData = builtin.oData()
local tolua = builtin.tolua

local CCLuaLog = builtin.CCLuaLog
builtin.cclog = function(...)
    CCLuaLog(string.format(...))
end
builtin.CCLuaLog = nil

local CCMessageBox = builtin.CCMessageBox
builtin.ccmsg = function(title, ...)
    CCMessageBox(string.format(...), title)
end
builtin.CCMessageBox = nil

local yield = coroutine.yield
local wrap = coroutine.wrap
local CCDirector = builtin.CCDirector
local table_insert = table.insert
local table_remove = table.remove
local type = type

local function wait(cond)
	while cond(CCDirector.deltaTime) do
		yield()
	end
end

local function once(job)
	return wrap(function()
		job()
		return true
	end)
end

local function loop(job)
	return wrap(function()
		repeat yield() until job()
		return true
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
	local function worker()
		local deltaTime = CCDirector.deltaTime
		time = time + deltaTime
		if time < duration then
			work(deltaTime)
			return true
		end
		return false
	end
	while worker() do
		yield()
	end
end

local function oRoutine_end() return true end
local oRoutine =
{
	remove = function(self,routine)
		for i = 1,#self do
			if self[i] == routine then
				self[i] = oRoutine_end
				return true
			end
		end
		return false
	end,
	clear = function(self)
		while #self > 0 do
			table_remove(self)
		end
	end,
}

setmetatable(oRoutine,
{
	__call = function(self,routine)
		table_insert(self,routine)
		return routine
	end,
})

oRoutine.start = function(self)
	CCDirector:schedule(function()
		local i,count = 1,#self
		while i <= count do
			if self[i]() then
				self[i] = self[count]
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

builtin.oRoutine = oRoutine
builtin.wait = wait
builtin.once = once
builtin.loop = loop
builtin.seconds = seconds
builtin.cycle = cycle

local CCArray = builtin.CCArray
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

local CCDictionary = builtin.CCDictionary
local CCDictionary_index = CCDictionary.__index
local CCDictionary_get = CCDictionary.get
CCDictionary.__index = function(self,key)
	local item = CCDictionary_get(self,key)
	if item ~= nil then return item end
	return CCDictionary_index(self,key)
end

local CCDictionary_newindex = CCDictionary.__newindex
local CCDictionary_set = CCDictionary.set
CCDictionary.__newindex = function(self,key,value)
	local vtype = tolua.type(value)
	if vtype == "function" or vtype == "table" then
		CCDictionary_newindex(self,key,value)
	else
		CCDictionary_set(self,key,value)
	end
end

local CCUserDefaultClass = getmetatable(builtin.CCUserDefault)
local CCUserDefaultClass_index = CCUserDefaultClass.__index
local CCUserDefaultClass_get = CCUserDefaultClass.get
CCUserDefaultClass.__index = function(self,key)
	local item = CCUserDefaultClass_get(self,key)
	if item ~= nil then return item end
	return CCUserDefaultClass_index(self,key)
end
local CCUserDefaultClass_set = CCUserDefaultClass.set
CCUserDefaultClass.__newindex = function(self,key,value)
	CCUserDefaultClass_set(self,key,value)
end

local emit = builtin.emit
local oEvent_args = {}
local argsCount = 0
builtin.emit = function(name,args)
	argsCount = argsCount + 1
	oEvent_args[argsCount] = args
	emit(name)
	oEvent_args[argsCount] = nil
	argsCount = argsCount - 1
end

local CCNode_gslot = builtin.CCNode.gslot
builtin.CCNode.gslot = function(self,name,...)
	local handler = select(1,...)
	if handler then
		return CCNode_gslot(self,name, function(event)
			handler(oEvent_args[argsCount],event)
		end)
	else
		return CCNode_gslot(self,name,...)
	end
end

local oSlot = builtin.oSlot
builtin.oSlot = function(name,handler)
	return oSlot(name, function(event)
		handler(oEvent_args[argsCount],event)
	end)
end

local oAction = builtin.oAction
local oAction_add = oAction.add
oAction.add = function(self,id,priority,reaction,recovery,access,routine,stop)
	oAction_add(self,
		id,
		priority,
		reaction,
		recovery,
		access,
		function()
			return once(routine)
		end,
		stop)
end

local oCache = builtin.oCache
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
local CCTextureCache = builtin.CCTextureCache
local CCTextureCache_loadAsync = CCTextureCache.loadAsync
oCache.Texture = builtin.CCTextureCache()
builtin.CCTextureCache = nil
CCTextureCache.loadAsync = nil

local oContent = builtin.oContent
local function _loadTextureAsync(filename, loaded)
	if not oContent:exist(filename) then
		CCLuaLog(string.format("[ERROR] Texture file fails to load: %s", filename))
		return function() return false end
	end
	local isloaded = false
	CCTextureCache_loadAsync(oCache.Texture,filename,function(name)
		if loaded then
			loaded(name)
		end
		isloaded = true
	end)
	return function()
		return not isloaded
	end
end

local oSound = builtin.oSound
local oMusic = builtin.oMusic
local function _loadAsync(filename, loaded)
	local extension = string.match(filename, "%.([^%.\\/]*)$")
	if extension then extension = string.lower(extension) end
	local itemType = nil
	if extension == "png" or extension == "jpg" or extension == "tiff" or extension == "webp" then
		return _loadTextureAsync(filename, loaded)
	elseif extension == "clip" then
		if oCache.Clip:load(filename) then
			local texFile = oCache.Clip:getTextureFile(filename)
			if oContent:exist(texFile) then
				return _loadTextureAsync(texFile,function()
					if loaded then
						loaded(filename)
					end
				end)
			end
		end
		CCLuaLog(string.format("[ERROR] Clip file fails to load: %s", filename))
		return function() return false end
	elseif extension == "model" then
		if oCache.Model:load(filename) then
			local clipFile = oCache.Model:getClipFile(filename)
			if oContent:exist(clipFile) then
				local texFile = oCache.Clip:getTextureFile(clipFile)
				if oContent:exist(texFile) then
					return _loadTextureAsync(texFile,function()
						if loaded then
							loaded(filename)
						end
					end)
				end
			end
		end
		CCLuaLog(string.format("[ERROR] Model file fails to load: %s", filename))
		return function() return false end
	else
		local isLoaded = false
		local function loader()
			if not isLoaded then
				isLoaded = true
				if loaded then
					loaded(filename)
				end
				return false
			else
				return true
			end
		end
		if extension == "frame" then
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

oCache.loadAsync = function(_, filename, loaded)
	if type(filename) == "string" then
		wait(_loadAsync(filename, loaded))
	elseif type(filename) == "table" then
		for _,item in ipairs(filename) do
			wait(_loadAsync(item, loaded))
		end
	end
end

oCache.swapAsync = function(cache, listA, listB, loaded)
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

local oContent = builtin.oContent
local oContent_copyAsync = oContent.copyAsync
oContent.copyAsync = function(self,src,dst)
	local loaded  = false
	oContent_copyAsync(self,src,dst,function()
		loaded = true
	end)
	wait(function() return not loaded end)
end

local io_open = io.open
io.open = function(file,...)
	return io_open(oContent:getFullPath(file),...)
end

_G["thread"] = function(routine)
	return oRoutine(once(routine))
end

_G["threadLoop"] = function(routine)
	return oRoutine(loop(routine))
end

_G["sleep"] = function(sec)
	if sec then
		wait(seconds(sec))
	else
		yield()
	end
end

_G["using"] = function(path)
	return function(name)
		local result = package.loaded[name]
		if not result then
			result = require(path.."."..name)
		end
		return result
	end
end

for k,v in pairs(_G) do
	builtin[k] = v
end
local function Dorothy(env)
	if env then
		local newEnv = {}
		for k,v in pairs(env) do newEnv[k] = v end
		setmetatable(newEnv,{__index=builtin})
		setfenv(2,newEnv)
	else
		setfenv(2,builtin)
	end
end
_G["Dorothy"] = Dorothy
builtin["Dorothy"] = Dorothy

setmetatable(package.loaded,{__index=builtin})

collectgarbage("setpause", 100)
collectgarbage("setstepmul", 5000)
$]
