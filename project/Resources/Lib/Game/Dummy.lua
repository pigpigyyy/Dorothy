local oVec2 = require("oVec2")

local NoOp = function() end
local function Point() return oVec2.zero end
local function Boolean() return false end
--local function String() return "" end
local function Number() return 0 end
local function NumberFunc() return Number end

local Defaults = {
	position = Point,
	visible = Boolean,
	angle = Number,
	scale = Point,
	skew = Point,
	opacity = Number,
	play = NumberFunc,
}

local Dummy
Dummy = setmetatable({},{
	__index = function(self, key)
		local default = Defaults[key]
		if default == nil then
			return Dummy
		else
			return default()
		end
	end,
	__newindex = NoOp
})

local DummyNoDefault = setmetatable({},{
	__index = function()
		return Dummy
	end,
	__newindex = NoOp
})

return {Dummy,DummyNoDefault}
