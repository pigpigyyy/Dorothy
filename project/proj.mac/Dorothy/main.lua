setfenv(Dorothy())
local loop = oRoutine.loop
local wait = oRoutine.wait
local seconds = oRoutine.seconds

oRoutine(loop(function()
	print("Running!")
	for i = 1,10 do
		wait(seconds(1))
		print(i)
	end
end))

local size = CCDirector.winSize
local scene = CCScene()
local layer = CCLayerColor(ccColor4(0xff00ffff), size.width, size.height)
layer.position = oVec2(size.width*0.5, size.height*0.5)
layer.opacity = 0
layer:runAction(CCRepeatForever(CCSequence({oOpacity(1,1),oOpacity(1,0)})))
scene:addChild(layer)

CCDirector:run(scene)
