local Class = require("Class")
local property = require("property")
local thread = require("thread")
local oRoutine = require("oRoutine")

local Trigger = Class {
	__init = function(self, name, enable, event, condition, action)
		self._name = name
		self._enabled = enable
		self._event = event
		self._condition = condition
		self._action = action
		self._handler = function(...)
			if condition(...) then
				local args = {...}
				self._routine = thread(function()
					action(unpack(args))
					self._routine = nil
				end)
			end
		end
	end,

	enabled = property(
		function(self)
			return self._enabled
		end,
		function(self,value)
			self._enabled = value
			if value then
				self:register()
			else
				self:unregister()
			end
		end),

	register = function(self)
		if self._enabled then
			self._event:add(self._handler)
		end
	end,

	unregister = function(self)
		self._event:remove(self._handler)
	end,

	stop = function(self)
		if self._routine then
			oRoutine:remove(self._routine)
			self._routine = nil
		end
	end,
}

return Trigger
