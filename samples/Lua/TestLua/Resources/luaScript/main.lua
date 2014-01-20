require("luaScript/helper")

-- avoid memory leak
collectgarbage("setpause", 100) 
collectgarbage("setstepmul", 5000)

local function createLayer()
	--local size = CCDirector:sharedDirector():getWinSize()
	--local kTagSprite = 1
	local size = CCSize(100,200)
	cclog("%d %d",size.width,size.height)
	size = nil
	layer = oPlatformWorld()
	--local bgLayer = CCLayerColor:create(ccc4(255,255,0,255))
    --layer:addChild(bgLayer, -1)
	--layer:getLayer(-1):setPositionZ(-100)
	--layer:getLayer(-1):setRotationX(-45)
	
    --layer:addChild(sprite, 0, kTagSprite)
    --sprite:setPosition(CCPointMake(20,150))

    --sprite:runAction(CCJumpTo:create(4, CCPointMake(300,48), 100, 4))

	--bgLayer:setOpacity(0)
    --bgLayer:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
    --                                             CCFadeIn:create(1),
    --                                             CCFadeOut:create(1))))
	local drawNode = CCDrawNode()
	drawNode:drawPolygon(
	{
		oVec2(0,0),
		oVec2(100,0),
		oVec2(100,100),
		oVec2(0,100),
	},0.5,ccColor4(255,0,0,255),ccColor4(255,0,0,255))
	drawNode.position = oVec2(100,100)
	layer:addChild(drawNode)
	local LAYER_FRONT = 2
	local LAYER_GAME = 1
	local LAYER_BACK = 0

	oCache.Effect:load("main.effect")
	--oCache.Model:load("jixienv.model")
	local model = oModel("jixienv.model")
	model.loop = true
	model.recovery = 0.1
	model.look = "happy"
	model:play("walk")
	local function func(model)
		cclog(model.currentAnimation)
	end
	model:addHandler("walk", func)
	model:removeHandler("walk", func)
	
	--model:setPosition(CCPointMake(200,200))
	--layer:addChild(model)
	
	local groupOne = 1
	layer:setShouldContact(groupOne, groupOne, true)
	
	local bodyDef = oBodyDef()
	bodyDef.type = oBodyDef.Dynamic
	bodyDef:attachPolygon(100, 200, 1.0, 0.4, 0.4)
	local body = bodyDef:toBody(layer, groupOne, 200, 200)
	body:addChild(model, 0, 998)
	model:runAction(oScale(2, 0.5, 0.5, oEase.Linear))
	layer:addChild(body, LAYER_GAME, 998)
	--local char = body
	--oEffect(1):attachTo(body):autoRemove():start()
	
	--Terrain
	bodyDef = oBodyDef()
	bodyDef.type = oBodyDef.Static
	bodyDef:attachChain(Vec2s(
	{
		{0,0},
		{1000,0},
		{1000,1000},
		{0,1000},
		{0,0}
	}))
	body = bodyDef:toBody(layer, groupOne, 0, 0)
	layer:addChild(body)
	--Sensor
	local sensorTag = 1;
	bodyDef = oBodyDef()
	bodyDef.type = oBodyDef.Static
	body = bodyDef:toBody(layer, groupOne, 200, 0)
	local sensor = body:attachSensor(sensorTag, oBodyDef:polygon(100, 100))
	sensor:addHandler(oSensor.Enter, function() cclog("Entered !") end)
	--sensor.addLeaveHandler(this.onBodyLeave);
	layer:addChild(body)
	
	--oMusic:play("background.mp3", true)
	local function onTouchEnded(x, y)
		model:play("attack")
		cclog("%d",CCObject.count)
		--char.velocity.y = 400
        --local s = layer:getChildByTag(kTagSprite)
        --s:stopAllActions()
        --s:runAction(CCMoveTo:create(1, CCPointMake(x, y)))
        --local posX, posY = s:getPosition()
        --local o = x - posX
        --local a = y - posY
		--if a ~= 0 then
		--	local at = math.atan(o / a) / math.pi * 180.0
		--	if a < 0 then
		--		if o < 0 then
		--			at = 180 + math.abs(at)
		--		else
		--			at = 180 - math.abs(at)
		--		end
		--	end
		--	cclog("what %.4f", at)
		--	s:runAction(CCRotateTo:create(1, at))
		--end
		--oSound:play("effect1.wav")
		collectgarbage()
    end

    local function onTouch(eventType, x, y)
        if eventType == CCTouch.Began then
            return true
        elseif eventType == CCTouch.Ended then
            return onTouchEnded(x, y)
        end
    end
    layer.touchEnabled = true
    layer:registerTouchHandler(onTouch)
    return layer
end

--------------------------------
-- Test
--------------------------------
local scene = CCScene()
scene:addChild(CreateBackMenuItem())
scene:addChild(createLayer())
--CCDirector:run(CCScene:pageTurn(3,scene,true))
CCDirector:run(scene)
