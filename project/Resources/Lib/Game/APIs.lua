local Trigger = require("Lib.Game.Trigger")
local Game = require("Lib.Game.Game")
local Class = require("Class")
local once = require("once")
local sleep = require("sleep")
local thread = require("thread")
local tolua = require("tolua")

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
			self._slots = Game.instance:slot("Update")
			self._interval = interval
		end,
		add = function(self,handler)
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
			self._slots:remove(self._handler)
		end,
	},

	TimeElapsed = Class {
		__init = function(self,interval)
			self._slots = Game.instance:slot("Update")
			self._interval = interval
			self._fired = false
		end,
		add = function(self,handler)
			if self._fired then return end
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
			if self._fired then return end
			self._slots:remove(self._handler)
		end,
	},

	BodyEnter = Class {
		__init = function(self,sensor)
			if not sensor then return end
			self._slots = sensor:slot("BodyEnter")
		end,
		add = function(self,handler)
			if not self._slots then return end
			if not self._handler then
				self._handler = function(body, sensor)
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

	Sleep = sleep,
	Print = print,

	Model = function(name)
		local item = Game.instance:getItem(name)
		if tolua.type(item) == "oModel" then
			return item
		end
		return nil
	end,

	Body = function(name)
		local item = Game.instance:getItem(name)
		if tolua.type(item) == "CCNode" and item.data then
			return item
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

}

return APIs
