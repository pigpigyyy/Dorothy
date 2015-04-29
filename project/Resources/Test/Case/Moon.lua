local moon = require("moonscript")

local codes,msg = moon.to_lua([[

setfenv Dorothy!

{:width,:height} = CCDirector.winSize

model = with oModel "ActionEditor/Model/Output/xiaoli.model"
	.look = "happy"
	.loop = true
	.position = oVec2 width*0.5, height*0.5
	\play "walk"

layer = with CCLayer!
	.touchEnabled = true
	.anchor = oVec2.zero
	\registerTouchHandler (eventType,touch)->
		if eventType == CCTouch.Moved
			model.position += touch.delta
		true
	\addChild model
	
scene = with CCScene!
	\addChild layer

CCDirector\run CCScene\crossFade 1,scene

]])

--[[

setfenv(Dorothy())

local winSize = CCDirector.winSize

local model = oModel("ActionEditor/Model/Output/xiaoli.model")
model.look = "happy"
model.loop = true
model.position = oVec2(winSize.width*0.5, winSize.height*0.5)
model:play("walk")

local layer = CCLayer()
layer.touchEnabled = true
layer.anchor = oVec2.zero
layer:registerTouchHandler(function(eventType,touch)
	if eventType == CCTouch.Moved then
		model.position = model.position + touch.delta
	end
	return true
end)
layer:addChild(model)

local scene = CCScene()
scene:addChild(layer)

CCDirector:run(CCScene:crossFade(1,scene))

]]

print(codes or msg)

loadstring(codes)()
