Dorothy()
local winSize = CCDirector.winSize
if winSize.width >= 1280 and winSize.height >= 960 then
	CCView:setDesignResolution(winSize.width/2,winSize.height/2,CCView.ExactFit)
end

local CCLabelTTF = builtin.CCLabelTTF
builtin.CCLabelTTF = function(text,fontName,fontSize)
	if fontSize == 17
		or fontSize == 20
		or fontSize == 24 then
		return CCLabelBMFont(text,"Font/Arial"..tostring(fontSize)..".fnt",CCLabelBMFont.AutomaticWidth,CCTextAlign.HCenter)
	elseif fontSize == 10
		or fontSize == 12 then
		return CCLabelBMFont(text,"Font/Arial14.fnt",CCLabelBMFont.AutomaticWidth,CCTextAlign.HCenter)
	elseif fontSize == 14 or fontSize == 16 or fontSize == 18 then
		return CCLabelBMFont(text,"Font/Arial17.fnt",CCLabelBMFont.AutomaticWidth,CCTextAlign.HCenter)
	end
	return CCLabelTTF(text,fontName,fontSize)
end

require("Test.Entry")

--[[
Dorothy()

oRoutine:stop()
cclog("Object Count: %d",CCObject.count)
cclog("Lua Count: %d",CCObject.luaRefCount)
cclog("Callback Count: %d", CCObject.callRefCount)
local size = oCache.Pool.size
cclog("Pool alloc : %.2f MB(%d KB)",size/1024/1024,size/1024)
for i,item in pairs(ubox()) do
	print(i,item)
end

CCDirector:run(CCScene())
local oContent = require("oContent")
oContent:setSearchPaths({"","Lib"})
require("EffectEditor.Script.main")
--]]

--[[
CCScene:transition("cf",{"crossFade",1,CCOrientation.Left})
CCScene:add("firstScene",CCScene())
CCScene:run("firstScene","fadeIn")
CCScene:push("firstScene","cf")
CCScene:popTo("secondScene","crossFade")
--]]
