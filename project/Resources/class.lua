local function class(...)
	local arg1 = select(1,...)
	local arg2 = select(2,...)
	local typeDef = arg2 or arg1
	local base = arg2 and arg1 or nil
	local call = function(self,...)
		local inst = {}
		setmetatable(inst,self)
		if self.__init__ then self.__init__(inst,...) end
		local c_inst
		if self.__new__ then c_inst = self.__new__(inst,...) end
		if c_inst then tolua.setpeer(c_inst,inst) end
		return c_inst or inst
	end
	local cls
	cls =
	{
		__index = function(self,name)
			if cls.__getter then
				local getter = cls.__getter[name]
				if getter then
					return getter(self)
				end
			end
			return rawget(cls,name)--[[member method]]
				or getmetatable(cls)[name]--[[super method]]
				or rawget(self,name)--[[self field]]
		end,
		__newindex = function(self,name,value)
			if cls.__setter then
				local setter = cls.__setter[name]
				if setter then
					setter(self,value)
					return
				end
			end
			if cls.__getter and cls.__getter[name] then
				(nil)()
				return
			end
			rawset(self,name,value)
		end,
		__call = call,
	}
	for k,v in pairs(typeDef) do
		if type(v) == "table" then
			local set,get = v.__set__,v.__get__
			if get then
				cls.__getter = {} or cls.__getter
				cls.__getter[k] = get
				if set then
					cls.__setter = {} or cls.__setter					
					cls.__setter[k] = set
				end
			end
		elseif type(v) == "function" then
			rawset(cls,k,v)
		end
	end
	if base then
	for k,v in pairs(base) do
		if k:sub(1,1) ~= "_" and not cls[k] then
		end
	end
	setmetatable(cls,base or {__call=call})
	return cls
end

local function property(__get__,__set__)
	return {__get__=__get__,__set__=__set__}
end

return {class,property}
