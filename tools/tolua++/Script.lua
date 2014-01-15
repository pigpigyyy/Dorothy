$[
cclog = function(...)
    CCLuaLog(string.format(...))
end

ccmsg = function(title, ...)
    CCMessageBox(string.format(...), title)
end

CCDrawNode.drawPolygon =
	(function()
		local _drawPolygon = CCDrawNode.drawPolygon
		return function(self, verts, borderWidth, fillColor, borderColor)
			_drawPolygon(self, #verts, verts, fillColor, borderWidth, borderColor)
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
