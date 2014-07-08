$[
local loaded = package.loaded

loaded.CCView = require("CCView")()
loaded.CCFileUtils = require("CCFileUtils")()
loaded.CCApplication = require("CCApplication")()
loaded.CCDirector = require("CCDirector")()
loaded.CCUserDefault = require("CCUserDefault")()
loaded.CCTextureCache = require("CCTextureCache")()
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
	wait = (function()
		local director = CCDirector
		return function(cond)
			while cond(director.deltaTime) do
				yield()
			end
		end
	end)(),
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
		local i,count = 1,#oRoutine
		while i <= count do
			if oRoutine[i]() then
				if i ~= count then
					oRoutine[i] = oRoutine[count]
				end
				table.remove(oRoutine)
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

CCArray.__index = (function()
	local _index = CCArray.__index
	local _get = CCArray.get
	return function(self,key)
		if type(key) == "number" then
			return _get(self,key)
		end
		return _index(self,key)
	end
end)()

CCArray.__newindex = (function()
	local _newindex = CCArray.__newindex
	local _set = CCArray.set
	return function(self,key,value)
		if type(key) == "number" then
			_set(self,key,value)
		else
			_newindex(self,key,value)
		end
	end
end)()

CCDictionary.__index = (function()
	local _index = CCDictionary.__index
	local _get = CCDictionary.get
	return function(self,key)
		local item = _get(self,key)
		if item ~= nil then return item end
		return _index(self,key)
	end
end)()

CCDictionary.__newindex = (function()
	local _set = CCDictionary.set
	return function(self,key,value)
		_set(self,key,value)
	end
end)()

oEvent.send = (function()
	oEvent.args = {}
	local send = oEvent.send
	return function(self, name, args)
		oEvent.args[name] = args
		send(self, name)
	end
end)()

loaded.oListener = (function()
	local listener = loaded.oListener
	return function(name, handler)
		return listener(name,
			function(event)
				handler(oEvent.args[name], event)
		end)
	end
end)()

oAction.add = (function()
	local _add = oAction.add
	local _once = oRoutine.once
	return function(self,id,priority,reaction,recovery,access,routine,stop)
		_add(self,id,
			priority,
			reaction,
			recovery,
			access,
			function()
				return _once(routine)
			end,
			stop)
	end
end)()

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
	return function() return tb or gettb() end
end)()
$]
