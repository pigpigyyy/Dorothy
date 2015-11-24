local tolua = require("tolua")
local setmetatable = setmetatable
local getmetatable = getmetatable
local pairs = pairs
local rawget = rawget
local rawset = rawset
local type = type

--[[
Class Field:
	0 - C++ instance
	1 - getters
	2 - setters

Field Level:
	0 - class
	1 - instance

To inherit a class
Inherit a lua table class:
	Base = class({ ... })
	MyClass = class(Base,{ ... })

Inherit a C++ instance class:
	MyClass = class({
		__partial = function(self)
			return CCNode()
		end,
	})

Use number index to add field to a class
is deprecated. Example below may cause error.

	MyClass = class({
		[0] = 123
		[1] = 998
		[2] = 233
	})
]]

local function __call(self,...)
	local inst = {}
	setmetatable(inst,self)
	if self.__partial then
		local c_inst = self.__partial(inst,...)
		if c_inst then
			local peer = tolua.getpeer(c_inst)
			if peer then
				for k,v in pairs(peer) do
					inst[k] = v
				end
				local peerClass = getmetatable(peer)
				if peerClass then
					local baseClass = getmetatable(self)
					setmetatable(baseClass,peerClass) -- chaining partial class`s metatable
				end
			end
			tolua.setpeer(c_inst,inst)
			inst[0] = c_inst
		end
		inst = c_inst or inst
	end
	if self.__init then
		self.__init(inst,...)
	end
	return inst
end

local function __index(self,name)
	local cls = getmetatable(self)
	local item = cls[1][name] -- access properties
	if item then
		return item(self[0] or self)
	else
		item = rawget(cls,name) -- access member functions
		if item then
			return item
		else
			local c = getmetatable(cls)
			while c do -- recursive to access super classes
				item = c[1][name]
				if item then
					cls[1][name] = item -- cache super properties to class
					return item(self[0] or self)
				else
					item = rawget(c,name)
					if item then
						rawset(cls,name,item) -- cache super member to class
						return item
					end
				end
				c = getmetatable(c)
			end
			return nil
		end
	end
end

local function __newindex(self,name,value)
	local cls = getmetatable(self)
	local item = cls[2][name] -- access properties
	if item then
		item(self[0] or self,value)
	else
		local c = getmetatable(cls)
		while c do -- recursive to access super properties
			item = c[2][name]
			if item then
				cls[2][name] = item -- cache super property to class
				item(self[0] or self,value)
				return
			end
			c = getmetatable(c)
		end
		rawset(self,name,value) -- assign field to self
	end
end

local function assignReadOnly()
	error("Try to assign to a readonly property!")
end

local function class(arg1,arg2)
	local typeDef = arg2 or arg1
	local base
	if arg2 then
		base = arg1
	else
		base = {
			{
				__class = function() return base end
			},
			{
				__class = assignReadOnly
			},
			__index = __index,
			__newindex = __newindex,
			__call = __call,
		}
	end
	local cls
	cls = {
		{
			__class = function() return cls end,
			__base = function() return base end,
		},
		{
			__class = assignReadOnly,
			__base = assignReadOnly,
		},
		__index = __index,
		__newindex = __newindex,
		__call = __call,
	}
	if typeDef then
		for k,v in pairs(typeDef) do
			if type(v) == "table" then
				if v.__fieldlevel == 0 then
					base[1][k] = v[1]
					base[2][k] = v[2]
				elseif v.__fieldlevel == 1 then
					cls[1][k] = v[1]
					cls[2][k] = v[2]
				else
					cls[k] = v
				end
			else
				cls[k] = v
			end
		end
	end
	setmetatable(cls,base)
	if cls.__initc then
		cls:__initc()
		cls.__initc = nil -- run once and dispose this method
	end
	return cls
end

local function property(getter,setter)
	return {getter,setter or assignReadOnly,__fieldlevel=1}
end

local function classfield(getter,setter)
	return {getter,setter or assignReadOnly,__fieldlevel=0}
end

local function classmethod(method)
	return method
end

return {class,property,classfield,classmethod}
