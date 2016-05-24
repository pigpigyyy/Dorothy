local Trigger = require("Lib.Game.Trigger")
local Game = require("Lib.Game.Game")
local Class = require("Class")
local once = require("once")
local sleep = require("sleep")
local thread = require("thread")
local tolua = require("tolua")
local oContent = require("oContent")
local oVec2 = require("oVec2")
local oModel = require("oModel")
local oAction = require("oAction")
local oAI = require("oAI")
local oSeq = require("oSeq")
local oSel = require("oSel")
local oCon = require("oCon")

local type = type
local select = select
local ctype = tolua.type
local inf = math.huge
local ninf = -inf

local function IsValidNumber(x)
	return x == x and ninf < x and x < inf
end

local function InvalidNumber(x)
	if x ~= x or ninf > x or x > inf then
		return true
	end
	return false
end

local function InvalidNumbers(...)
	for i = 1,select("#",...) do
		local x = select(i,...)
		if x ~= x or ninf > x or x > inf then
	 		return true
		end
	end
	return false
end

local function IsValid(x)
	if type(x) == "number" then
		return IsValidNumber(x)
	else
		return x ~= nil
	end
end

local function InvalidItem(x)
	return x == nil
end

local function InvalidItems(...)
	for i = 1,select("#",...) do
		local x = select(i,...)
		if x == nil then
			return true
		end
	end
	return false
end

local APIs
APIs = {
	Trigger = Trigger,

	Event = function(event)
		return event
	end,

	NoEvent = function()
		return Game.instance:slot("NoEvent")
	end,

	SceneInitialized = function()
		return Game.instance:slot("Initialized")
	end,

	TimeCycled = Class {
		__init = function(self,interval)
			if IsValidNumber(interval) then
				self._slots = Game.instance:slot("Update")
				self._interval = interval
			end
		end,
		add = function(self,handler)
			if not self._slots then return end
			if not self._handler then
				self._handler = once(function()
					repeat
						sleep(self._interval)
						thread(handler)
					until false
				end)
			end
			self._slots:add(self._handler)
		end,
		remove = function(self)
			if not self._slots then return end
			self._slots:remove(self._handler)
		end,
	},

	TimeElapsed = Class {
		__init = function(self,interval)
			if IsValidNumber(interval) then
				self._slots = Game.instance:slot("Update")
				self._interval = interval
				self._fired = false
			end
		end,
		add = function(self,handler)
			if self._fired or not self._slots then return end
			if not self._handler then
				self._handler = once(function()
					sleep(self._interval)
					thread(handler)
					self._slots:remove(self._handler)
					self._fired = true
				end)
			end
			self._slots:add(self._handler)
		end,
		remove = function(self)
			if self._fired or not self._slots then return end
			self._slots:remove(self._handler)
		end,
	},

	BodyEnter = Class {
		__init = function(self,sensor)
			if not sensor then return end
			self._slots = sensor:slot("BodyEnter")
			self.passValues = true
		end,
		add = function(self,handler)
			if not self._slots then return end
			if not self._handler then
				self._handler = function(body,sensor)
					handler(body,sensor.tag)
				end
			end
			self._slots:add(self._handler)
		end,
		remove = function(self)
			if not self._slots then return end
			self._slots:remove(self._handler)
		end,
	},

	Condition = function(condition)
		return condition
	end,

	Action = function(condition)
		return condition
	end,

	DoNothing = function() end,
	IsValid = IsValid,
	Sleep = sleep,
	Print = print,

	Effect = function(name)
		local item = Game.instance:getItem(name)
		if ctype(item) == "oEffect" then
			return item
		end
		return nil
	end,
	Sprite = function(name)
		local item = Game.instance:getItem(name)
		if ctype(item) == "CCSprite" then
			return item
		end
		return nil
	end,
	Model = function(name)
		local item = Game.instance:getItem(name)
		if ctype(item) == "oModel" then
			return item
		end
		return nil
	end,
	Body = function(name)
		local item = Game.instance:getItem(name)
		if ctype(item) == "CCNode" then
			return item
		end
		return nil
	end,
	BodySlice = function(name)
		local index = name:find("%.")
		if index then
			local bodyName = name:sub(1,index-1)
			local body = APIs.Body(bodyName)
			if body then
				local sliceName = name:sub(index+1,-1)
				local slice = body.data[sliceName]
				if slice then
					return slice
				end
			end
		end
		return nil
	end,
	Sensor = function(name)
		local index = name:find("%.")
		if index then
			local bodyName = name:sub(1,index-1)
			local body = APIs.Body(bodyName)
			if body then
				local sensorName = name:sub(index+1,-1)
				local sensor = body.data[sensorName]
				if sensor and sensor.sensor then
					return sensor
				end
			end
		end
		return nil
	end,
	Layer = function(name)
		local item = Game.instance:getItem(name)
		if ctype(item) == "oNode3D" then
			return item
		end
		return nil
	end,

	Point = oVec2,

	Loop = function(start,stop,step,work)
		if InvalidNumbers(start,stop,step) then return end
		if (start < stop and step > 0) or (start > stop and step < 0) then
			for i = start,stop,step do
				work(i)
			end
		end
	end,

	CreateModel = function(modelType, position, layer, angle, look, animation, loop)
		if InvalidNumber(angle) or InvalidItem(layer) then return nil end
		local modelFile = Game.instance.gamePath..modelType
		if oContent:exist(modelFile) then
			local model = oModel(modelFile)
			model.position = position
			model.angle = angle
			model.look = look
			model.loop = loop
			model:play(animation)
			layer:addChild(model)
			return model
		end
		return nil
	end,

	PlayAnimation = function(model, animation, loop, look)
		if InvalidItem(model) then return 0 end
		model.loop = loop
		model.look = look
		return model:play(animation)
	end,

	DestroyModel = function(model)
		if InvalidItem(model) then return end
		if model.parent then
			model.parent:removeChild(model)
		end
	end,

	UnitAction = function(name, priority, reaction, recovery, available, run, stop)
		if InvalidNumbers(priority, reaction, recovery) then return end
		oAction:add(name, priority, reaction, recovery, available, run, stop)
	end,

	AIRoot = function(name, ...)
		oAI:add(name,oSel{...})
	end,

	SelNode = function(...)
		return oSel{...}
	end,

	SeqNode = function(...)
		return oSeq{...}
	end,

	ConNode = function(name, condition)
		if condition then
			return oCon(condition)
		else
			return Game.instance:getCondition(name)
		end
	end,
}

return APIs
