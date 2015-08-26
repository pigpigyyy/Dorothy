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
