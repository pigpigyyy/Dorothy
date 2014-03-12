local scene = CCScene()
local layerColor = CCLayerColor(ccColor4(0xffffffff),460,300)
layerColor.position = oVec2(10,10)
layerColor.anchorPoint = oVec2.zero

local sprite = CCSprite("loli.jpg")
sprite.rotation = 45
sprite.anchorPoint = oVec2.zero

layerColor:addChild(sprite)
layerColor.touchMode = CCLayer.TouchesAllAtOnce
layerColor:registerTouchHandler(
	function(eventType, touches)
		for _,touch in ipairs(touches) do
			--touch = CCTouch
			local v = sprite:convertToNodeSpace(
				touch.location)
			local result = CCRect(
					0,0,
					sprite.contentSize.width,
					sprite.contentSize.height
					):containsPoint(v)
			if eventType == CCTouch.Began then
				if result then
					sprite.opacity = 0.3
				end
			elseif eventType == CCTouch.Cancelled then
				sprite.opacity = 1.0
				cclog("Cancelled")
			elseif eventType == CCTouch.Ended then
				sprite.opacity = 1.0
				cclog("Ended")
			elseif eventType == CCTouch.Moved then
				if result then
					cclog("move %d:[%d,%d]",
					touch.id, v.x, v.y)
				end
			end
		end
	end, true)
layerColor.touchEnabled = true
scene:addChild(layerColor)

CCDirector:run(scene)