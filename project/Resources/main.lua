--require("Test/Entry")
--[[setfenv(Dorothy())

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
--]]

setfenv(Dorothy())

CCDirector:run(CCScene())