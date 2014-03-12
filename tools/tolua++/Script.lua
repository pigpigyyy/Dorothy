$[
cclog = function(...)
    CCLuaLog(string.format(...))
end

ccmsg = function(title, ...)
    CCMessageBox(string.format(...), title)
end

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
