$[
cclog = function(...)
    CCLuaLog(string.format(...))
end

ccmsg = function(title, ...)
    CCMessageBox(string.format(...), title)
end

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

oEvent.args = {}

oEvent.send = (function()
	local send = oEvent.send
	return function(self, name, args)
		oEvent.args[name] = args
		send(self, name)
	end
end)()

oListener = (function()
	local listener = oListener
	return function(name, handler)
		return listener(name,
			function(event)
				handler(oEvent.args[name], event)
		end)
	end
end)()

CCView = CCView()
CCFileUtils = CCFileUtils()
CCApplication = CCApplication()
CCDirector = CCDirector()
CCUserDefault = CCUserDefault()
CCTextureCache = CCTextureCache()

oContent = oContent()
oData = oData()
$]
