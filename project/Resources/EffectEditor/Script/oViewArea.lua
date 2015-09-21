local require = using("EffectEditor.Script")
local CCLayerColor = require("CCLayerColor")
local ccColor4 = require("ccColor4")
local oVec2 = require("oVec2")
local CCNode = require("CCNode")
local oEditor = require("oEditor")
local oEffect = require("oEffect")
local oScale = require("oScale")
local oEase = require("oEase")
local oPos = require("oPos")
local CCDirector = require("CCDirector")
local oLine = require("oLine")
local emit = require("emit")

local function oViewArea()
	local view = CCLayerColor(ccColor4(0xff1a1a1a))
	view.anchor = oVec2.zero

	local scrollNode = CCNode()
	view:addChild(scrollNode)
	scrollNode.position = oEditor.origin

	local winSize = CCDirector.winSize
	local crossNode = CCNode()
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
	scrollNode:addChild(crossNode)

--[[
	local winSize = CCDirector.winSize
	local radius = 50
	local star = oStar(radius,ccColor4(0x6600ffff),0.5,ccColor4(0xff00ffff))
	star.position = oVec2(radius,radius)
	local renderTarget = CCRenderTarget(radius*2,radius*2)
	renderTarget:beginDraw(ccColor4(0))
	renderTarget:draw(star)
	renderTarget:endDraw()

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
--]]

	view.touchEnabled = true

	local S = oVec2.zero
	local V = oVec2.zero
	local accel = winSize.height*2
	local function updateDragSpeed(dt)
		V = S / dt
		if V.length > accel then
			V:normalize()
			V = V * accel
		end
		S = oVec2.zero
	end
	local function updateDragPos(dt)
		local dir = oVec2(V.x,V.y)
		dir:normalize()
		local A = dir * -accel
		local incX = V.x > 0
		local incY = V.y > 0
		V = V + A * dt * 0.5
		local decX = V.x < 0
		local decY = V.y < 0
		if incX == decX and incY == decY then
			view:unschedule()
		else
			scrollNode.position = scrollNode.position + V * dt
		end
	end

	view:slots("TouchBegan",function()
		S = oVec2.zero
		V = oVec2.zero
		view:schedule(updateDragSpeed)
		return true
	end)

	view:slots("TouchMoved",function(touch)
		S = touch.delta
		scrollNode.position = scrollNode.position + S
	end)

	local function touchEnded()
		if V ~= oVec2.zero then
			view:schedule(updateDragPos)
		end
	end
	view:slots("TouchEnded",touchEnded)
	view:slots("TouchCancelled",touchEnded)

	view:gslot("Effect.viewArea.changeEffect",function(effectName)
		emit("Effect.viewArea.toOrigin",oEditor.origin)
		if not effectName and oEditor.effect then
			oEditor.effect:autoRemove():stop()
			oEditor.effect = nil
			return
		end
		if oEditor.effect then
			oEditor.effect:autoRemove():stop()
		end
		local effect = oEffect(effectName)
		effect:attachTo(scrollNode):start()
		oEditor.effect = effect
	end)
	view:gslot("Effect.viewArea.scroll",function(scale)
		scrollNode:runAction(oScale(0.3,scale,scale,oEase.OutQuad))
	end)
	view:gslot("Effect.viewArea.toOrigin",function(origin)
		view:unschedule()
		scrollNode:runAction(oPos(0.3,origin.x,origin.y,oEase.OutQuad))
	end)
	view:gslot("Effect.viewArea.pos",function(pos)
		scrollNode.position = pos
	end)
	view:gslot("Effect.viewArea.play",function()
		if oEditor.effect then
			oEditor.effect:start()
		end
	end)

	return view
end

return oViewArea
