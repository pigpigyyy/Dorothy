local tolua = require("tolua")
local setmetatable = setmetatable
local getmetatable = getmetatable
local pairs = pairs
local rawget = rawget
local rawset = rawset
local type = type

local function __call(self,...)
	local inst = {}
	setmetatable(inst,self)
	local c_inst
	if self.__partial then c_inst = self.__partial(inst,...) end
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
	if self.__init then self.__init(inst,...) end
	return inst
end

local function __index(self,name)
	local item = rawget(self,name) -- self field
	if item ~= nil then
		return item
	end
	local cls = getmetatable(self)
	item = rawget(cls,name)
	if item == nil then
		local c = getmetatable(cls)
		while c do
			item = rawget(c,name)
			if item ~= nil then break end
			c = getmetatable(c)
		end
		if item then
			rawset(cls,name,item) -- cache item from super in self
		end
	end
	if type(item) == "table" then -- item is property
		return item[1](self[0] or self)
	else
		return item
	end
end

local function __newindex(self,name,value)
	local cls = getmetatable(self)
	local item = rawget(cls,name)
	if item == nil then
		local c = getmetatable(cls)
		while c do
			item = rawget(c,name)
			if item ~= nil then break end
			c = getmetatable(c)
		end
		if item then
			rawset(cls,name,item) -- cache item from super in self
		end
	end
	if type(item) == "table" then
		item[2](self[0] or self,value)
	else
		rawset(self,name,value)
	end
end

local function class(arg1,arg2)
	local typeDef = arg2 or arg1
	local base = arg2 and arg1 or {
		__index = __index,
		__newindex = __newindex,
		__call = __call,
	}
	local cls = {
		__index = __index,
		__newindex = __newindex,
		__call = __call,
	}
	for k,v in pairs(typeDef) do
		if type(v) == "table" and v.__classfield then
			rawset(base,k,v)
		else
			rawset(cls,k,v)
		end
	end
	setmetatable(cls,base)
	if cls.__initc then cls:__initc() end
	return cls
end

local function property(getter,setter)
	return {getter,setter}
end

local function classfield(getter,setter)
	return {getter,setter,__classfield=true}
end

local function classmethod(method)
	return method
end

return {class,property,classfield,classmethod}
