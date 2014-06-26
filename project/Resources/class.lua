local function __call(self,...)
	local inst = {}
	setmetatable(inst,self)
	local c_inst
	if self.__init then c_inst = self.__init(inst,...) end
	if c_inst then tolua.setpeer(c_inst,inst) end
	return c_inst or inst
end

local function __index(self,name)
	local item = rawget(self,name)--self field
	if item ~= nil then
		return item
	end
	local cls = getmetatable(self)
	item = rawget(cls,name)
	if item == nil then
		local c = cls
		while c do
			item = rawget(c,name)
			if item then break end
			c = getmetatable(c)
		end
		if item then
			rawset(cls,name,item)--cache item from super in self
		end
	end
	if type(item) == "table" then
		return item[1](self)
	else
		return item
	end
end

local function __newindex(self,name,value)
	local item = rawget(self,name)--self field
	if item ~= nil then
		rawset(self,name,value)
		return
	end
	local cls = getmetatable(self)
	item = rawget(cls,name)
	if item == nil then
		local c = cls
		while c do
			item = rawget(c,name)
			if item then break end
			c = getmetatable(c)
		end
		if item then
			rawset(cls,name,item)--cache item from super in self
		end
	end
	if type(item) == "table" then
		item[2](self,value)
	else
		rawset(self,name,value)
	end
end

local function class(...)
	local arg1 = select(1,...)
	local arg2 = select(2,...)
	local typeDef = arg2 or arg1
	local base = arg2 and arg1 or nil
	local cls =
	{
		__index = __index,
		__newindex = __newindex,
		__call = __call,
	}
	for k,v in pairs(typeDef) do
		rawset(cls,k,v)
	end
	setmetatable(cls,base or {__call=__call})
	return cls
end

local function property(getter,setter)
	return {getter,setter}
end

return {class,property}
