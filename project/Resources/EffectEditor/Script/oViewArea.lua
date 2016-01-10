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

	local origin = oEditor.origin

	local scrollNode = CCNode()
	view:addChild(scrollNode)
	scrollNode.position = origin
	view.viewNode = scrollNode

	local winSize = CCDirector.winSize
	local crossNode = CCNode()
	local ycross = oLine(
	{
		oVec2(0,-winSize.height*2),
		oVec2(0,winSize.height*2)
	},ccColor4())
	ycross.opacity = 0.2
	crossNode:addChild(ycross)
	local xcross = oLine(
	{
		oVec2(-winSize.width*2,0),
		oVec2(winSize.width*2,0)
	},ccColor4())
	xcross.opacity = 0.2
	crossNode:addChild(xcross)
	scrollNode:addChild(crossNode)

--[[
	local winSize = CCDirector.winSize
	local radius = 50
	local star = CCDrawNode()
	star:drawPolygon(oStar(radius),ccColor4(0x6600ffff),0.5,ccColor4(0xff00ffff))
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
	view.multiTouches = true

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
			xcross.positionX = -(scrollNode.positionX - origin.x)/scrollNode.scaleX
			ycross.positionY = -(scrollNode.positionY - origin.y)/scrollNode.scaleX
		end
	end

	view:slot("TouchBegan",function()
		S = oVec2.zero
		V = oVec2.zero
		view:schedule(updateDragSpeed)
		return true
	end)

	view:slot("TouchMoved",function(touches)
		if #touches == 1 then
			S = touches[1].delta
			scrollNode.position = scrollNode.position + S
		elseif #touches >= 2 then -- scale view
			local preDistance = touches[1].preLocation:distance(touches[2].preLocation)
			local distance = touches[1].location:distance(touches[2].location)
			local delta = (distance - preDistance) * 4 / winSize.height
			local scale = scrollNode.scaleX + delta
			if scale <= 0.5 then
				scale = 0.5
			end
			scrollNode.scaleX = scale
			scrollNode.scaleY = scale
			emit("Effect.viewArea.scale",scale)
		end
		print(scrollNode.positionX,scrollNode.positionY)
		xcross.positionX = -(scrollNode.positionX - origin.x)/scrollNode.scaleX
		ycross.positionY = -(scrollNode.positionY - origin.y)/scrollNode.scaleX
	end)

	local function touchEnded()
		if V ~= oVec2.zero then
			view:schedule(updateDragPos)
		end
	end
	view:slot("TouchEnded",touchEnded)
	view:slot("TouchCancelled",touchEnded)

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
		if effectName then
			local effect = oEffect(effectName)
			effect:attachTo(scrollNode):start()
			oEditor.effect = effect
		end
	end)
	view:gslot("Effect.viewArea.scroll",function(scale)
		scrollNode:runAction(oScale(0.5,scale,scale,oEase.OutQuad))
		xcross:runAction(oPos(0.5,-(scrollNode.positionX - origin.x)/scale,0,oEase.OutQuad))
		ycross:runAction(oPos(0.5,0,-(scrollNode.positionY - origin.y)/scale,oEase.OutQuad))
	end)
	view:gslot("Effect.viewArea.toOrigin",function(pos)
		view:unschedule()
		scrollNode:runAction(oPos(0.5,pos.x,pos.y,oEase.OutQuad))
		xcross:runAction(oPos(0.5,0,0,oEase.OutQuad))
		ycross:runAction(oPos(0.5,0,0,oEase.OutQuad))
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
