local CCLayerColor = require("CCLayerColor")
local ccColor4 = require("ccColor4")
local oVec2 = require("oVec2")
local CCNode = require("CCNode")
local oEditor = require("oEditor")
local CCTouch = require("CCTouch")
local CCArray = require("CCArray")
local oListener = require("oListener")
local oEffect = require("oEffect")
local oScale = require("oScale")
local oEase = require("oEase")
local oPos = require("oPos")

local function oViewArea()
	local view = CCLayerColor(ccColor4(0xff1a1a1a))
	view.anchor = oVec2.zero
	
	local scrollNode = CCNode()
	view:addChild(scrollNode)
	scrollNode.position = oEditor.origin

--[[
	local radius = 50
	local star = oStar(radius,ccColor4(0x6600ffff),0.5,ccColor4(0xff00ffff))
	star.position = oVec2(radius,radius)
	local renderTarget = CCRenderTarget(radius*2,radius*2)
	renderTarget:beginPaint(ccColor4(0))
	renderTarget:draw(star)
	renderTarget:endPaint()

	local tex = oCache.Texture:add(renderTarget,"star.png")

	local progressTimer = CCProgressTimer(CCSprite(tex))
	progressTimer:runAction(
		CCRepeatForever(
			CCSequence
			{
				CCCall(function()
					progressTimer.reverseDirection = false
				end),
				CCEase:sineInOut(CCProgress(1,0,100)),
				CCCall(function()
					progressTimer.reverseDirection = true
				end),
				CCEase:sineInOut(CCProgress(1,100,0)),
			}))
	progressTimer.position = oVec2(winSize.width*0.5,winSize.height*0.5)
	view:addChild(progressTimer)
]]

	view.touchEnabled = true
	view.touchHandler = function(eventType,touch)
		if eventType == CCTouch.Moved then
			scrollNode.position = scrollNode.position + touch.delta
		end
		return true
	end

	view.data = CCArray()
	view.data:add(oListener("viewArea.changeEffect",function(effectName)
		if not effectName and oEditor.effect then
			oEditor.effect:autoRemove():stop()
			oEditor.effect = nil
			return
		end
		if oEditor.effect then
			oEditor.effect:autoRemove():stop()
		end
		local extension = string.match(oEditor.items[effectName], "%.([^%.\\/]*)$")
		if extension == "par" then
			local effect = oEffect(effectName)
			effect:attachTo(scrollNode):start()
			oEditor.effect = effect
		elseif extension == "frame" then
			-- TODO
		end
	end))
	view.data:add(oListener("viewArea.scroll",function(scale)
		scrollNode:runAction(oScale(0.3,scale,scale,oEase.OutQuad))
	end))
	view.data:add(oListener("viewArea.toOrigin",function(origin)
		scrollNode:runAction(oPos(0.3,origin.x,origin.y,oEase.OutQuad))
	end))
	view.data:add(oListener("viewArea.play",function()
		if oEditor.effect then
			oEditor.effect:start()
		end
	end))

	return view
end

return oViewArea
