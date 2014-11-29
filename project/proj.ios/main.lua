setfenv(Dorothy())
local loop = oRoutine.loop
local wait = oRoutine.wait
local seconds = oRoutine.seconds

oRoutine(loop(function()
	wait(seconds(1))
	print("good")
	wait(seconds(2))
	print("again")
	wait(seconds(3))
	print("and again")
end))

local size = CCDirector.winSize
local layer = CCLayerColor(ccColor4(0xff00ffff), size.width, size.height)
layer.anchor = oVec2.zero
layer.opacity = 0
layer:runAction(CCRepeatForever(CCSequence({oOpacity(1,1),oOpacity(1,0)})))

local scene = CCScene()
scene:addChild(layer)

CCDirector.displayStats = true

CCDirector:run(scene)
