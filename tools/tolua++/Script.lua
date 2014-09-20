$[
local loaded = package.loaded

loaded.CCView = require("CCView")()
loaded.CCFileUtils = require("CCFileUtils")()
loaded.CCApplication = require("CCApplication")()
loaded.CCDirector = require("CCDirector")()
loaded.CCUserDefault = require("CCUserDefault")()
loaded.CCTextureCache = require("CCTextureCache")()
loaded.CCKeyboard = require("CCKeyboard")()
loaded.oContent= require("oContent")()
loaded.oData= require("oData")()

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

local CCArray = require("CCArray")
local CCDictionary = require("CCDictionary")
local oEvent = require("oEvent")
local oAction = require("oAction")
local CCDirector = require("CCDirector")

local yield = coroutine.yield
local wrap = coroutine.wrap
local create = coroutine.create
local resume = coroutine.resume
local status = coroutine.status

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
			table.remove(self,pos)
		end
	end,
	clear = function(self)
		while #self > 0 do
			table.remove(self)
		end
	end,
	wait = function(cond)
		while cond(CCDirector.deltaTime) do
			yield()
		end
	end,
	once = function(job)
		return wrap(function(...)
			job(...)
			return true
		end)
	end,
	loop = function(job)
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
	end,
	seconds = function(duration)
		local time = 0
		return function(deltaTime)
			time = time + deltaTime
			return time < duration
		end
	end,
	cycle = function(duration,work)
		local time = 0
		return function(deltaTime)
			time = time + deltaTime
			if time < duration then
				work(deltaTime)
				return true
			end
			return false
		end
	end,
}

setmetatable(oRoutine,
{
	__call = function(self,routine)
		table.insert(self,routine)
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
				table.remove(self,count)
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

local oEvent_args = {}
local oEvent_send = oEvent.send
oEvent.send = function(self,name,args)
	oEvent_args[name] = args
	oEvent_send(self,name)
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

local oCache_clear = loaded.oCache.clear
loaded.oCache.clear = function(self)
	oCache_clear()
end

Dorothy = (function()
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
