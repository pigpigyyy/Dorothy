local CCDirector = require("CCDirector")
local CCLayerColor = require("CCLayerColor")
local ccColor4 = require("ccColor4")
local oVec2 = require("oVec2")
local CCNode = require("CCNode")
local oLine = require("oLine")
local CCTouch = require("CCTouch")
local oEvent = require("oEvent")
local oListener = require("oListener")
local oScale = require("oScale")
local oEase = require("oEase")
local CCDictionary = require("CCDictionary")
local oPos = require("oPos")
local oRuler = require("oRuler")
local oWorld = require("oWorld")

local function oViewArea()
	local winSize = CCDirector.winSize
	
	-- init view --
	local view = CCLayerColor(ccColor4(0xff1a1a1a),winSize.width,winSize.height)
	view.anchor = oVec2.zero
	view.cascadeOpacity = true
	
	local crossNode = CCNode()
	local origin = oVec2(
		60+(winSize.width-120-180)*0.5,
		winSize.height*0.5)
	crossNode.position = origin
	view:addChild(crossNode)

	-- init cross --
	local cross = oLine(
	{
		oVec2(0,-winSize.height*2),
		oVec2(0,winSize.height*2)
	},ccColor4())
	cross.opacity = 0.2
	crossNode:addChild(cross)
	cross = oLine(
	{
		oVec2(-winSize.width*2,0),
		oVec2(winSize.width*2,0)
	},ccColor4())
	cross.opacity = 0.2
	crossNode:addChild(cross)

	-- listen reset events --
	crossNode.data = CCDictionary()
	crossNode.data.toScaleListener = oListener("viewArea.toScale",function(scale)
		crossNode:runAction(oScale(0.5,scale,scale,oEase.OutQuad))
	end)
	crossNode.data.toOriginListener = oListener("viewArea.toOrigin",function()
		crossNode:runAction(oPos(0.5,origin.x,origin.y,oEase.OutQuad))
	end)

	-- init world node --
	local world = oWorld()
	crossNode:addChild(world)
	view.world = world

	-- register view touch event --
	view:registerTouchHandler(
		function(eventType, touches)
			if eventType == CCTouch.Moved then
				if #touches == 1 then -- move view
					oEvent:send("viewArea.move",touches[1].delta)
					crossNode.position = crossNode.position + touches[1].delta
				elseif #touches >= 2 then -- scale view
					local preDistance = touches[1].preLocation:distance(touches[2].preLocation)
					local distance = touches[1].location:distance(touches[2].location)
					local delta = (distance - preDistance) * 4 / winSize.height
					local scale = crossNode.scaleX + delta
					if scale <= 0.5 then
						scale = 0.5
					end
					crossNode.scaleX = scale
					crossNode.scaleY = scale
					oEvent:send("viewArea.scale",scale)
				end
			end
		end, true)
	view.touchEnabled = true

	-- test codes below
	local CCDrawNode = require("CCDrawNode")
	local drawNode = CCDrawNode()
	drawNode:drawDot(oVec2.zero,100,ccColor4(0xff80ff00))
	world:addChild(drawNode)

	return view
end

return oViewArea