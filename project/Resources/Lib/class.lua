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
]]

local function __call(self,...)
	local inst = {}
	setmetatable(inst,self)
	local c_inst
	if self.__partial then
		c_inst = self.__partial(inst,...)
	end
	if c_inst then
		local peer = tolua.getpeer(c_inst)
		if peer then
			for k,v in pairs(peer) do
				inst[k] = v
			end
			local peermt = getmetatable(peer)
			if peermt then
				-- chaining partial class`s metatable
				local selfmt = getmetatable(self)
				setmetatable(selfmt,peermt)
			end
		end
		tolua.setpeer(c_inst,inst)
		inst[0] = c_inst
	end
	inst = c_inst or inst
	if self.__init then
		self.__init(inst,...)
	end
	return inst
end

local function __index(self,name)
	local cls = getmetatable(self)
	local item = cls[1][name]
	if item then
		return item(self[0] or self)
	else
		item = rawget(cls,name)
		if item then
			return item
		else
			local c = getmetatable(cls)
			while c do
				item = c[1][name]
				if item then
					cls[1][name] = item
					return item(self[0] or self)
				else
					item = rawget(c,name)
					if item then
						rawset(cls,name,item)
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
	local item = cls[2][name]
	if item then
		item(self[0] or self,value)
	else
		local c = getmetatable(cls)
		while c do
			item = c[2][name]
			if item then
				cls[2][name] = item
				item(self[0] or self,value)
				return
			end
			c = getmetatable(c)
		end
		rawset(self,name,value)
	end
end

local function class(arg1,arg2)
	local typeDef = arg2 or arg1
	local base
	if arg2 then
		base = arg1
	else
		base = {
			{__class = function() return base end},{},
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
		},{},
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
	return {getter,setter,__fieldlevel=1}
end

local function classfield(getter,setter)
	return {getter,setter,__fieldlevel=0}
end

local function classmethod(method)
	return method
end

return {class,property,classfield,classmethod}
