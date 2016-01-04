Dorothy()
local winSize = CCDirector.winSize
if winSize.width >= 1280 and winSize.height >= 960 then
	CCView:setDesignResolution(winSize.width/2,winSize.height/2,CCView.ExactFit)
end

local fontSize_cov = {
	[17] = 17,
	[20] = 20,
	[24] = 24,

	[10] = 14,
	[12] = 14,

	[14] = 17,
	[16] = 17,
	[18] = 17,
}

local CCLabelTTF = builtin.CCLabelTTF
builtin.CCLabelTTF = function(text,fontName,fontSize)
	local cov = fontSize_cov[fontSize]

	if cov then
		return CCLabelBMFont(text,"res/Font/Arial"..cov..".fnt",CCLabelBMFont.AutomaticWidth,CCTextAlign.HCenter)
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
