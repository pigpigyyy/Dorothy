local class = unpack(require("class"))
local CCDirector = require("CCDirector")
local oLine = require("oLine")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCLayerColor = require("CCLayerColor")
local oListener = require("oListener")
local CCDictionary = require("CCDictionary")
local oScale = require("oScale")
local oEase = require("oEase")
local oOpacity = require("oOpacity")
local CCTouch = require("CCTouch")
local CCRect = require("CCRect")
local CCLabelTTF = require("CCLabelTTF")
local oPos = require("oPos")
local oRoutine = require("oRoutine")
local once = oRoutine.once

local winSize = CCDirector.winSize
local rulerWidth = winSize.width
local rulerHeight = 30

local oRuler = class(
{
	__partial = function(self)
		return CCLayerColor(ccColor4(0),rulerWidth,rulerHeight)
	end,
	
	-- self = CCLayerColor
	__init = function(self)
		local halfW = rulerWidth*0.5
		local halfH = rulerHeight*0.5
		local origin = oVec2(
		60+(winSize.width-120-180)*0.5,
		winSize.height*0.5)

		self.cascadeOpacity = true
		self.opacity = 0.3
		self.anchor = oVec2(origin.x/winSize.width,0.5)
		self.position = oVec2(origin.x,halfH)
		
		-- borders --
		local border = oLine(
		{
			oVec2.zero,
			oVec2(rulerWidth,0)
		},ccColor4())
		self:addChild(border)
		
		-- init interval --
		local intervalNode = oLine()
		oRoutine(once(function()
			local count = math.floor(origin.x/10)
			local offsetX = origin.x-winSize.width*0.5
			local vs = {}
			for i = 0,count-1 do
				local j = count-i
				local posX = -j*10+offsetX
				table.insert(vs,oVec2(posX,halfH))
				table.insert(vs,oVec2(posX,halfH - (j%10 == 0 and 8 or 4)))
				table.insert(vs,oVec2(posX,halfH))
				if j%10 == 0 then
					local label = CCLabelTTF(tostring(-j*10),"Arial",10)
					label.texture.antiAlias = false
					label.position = oVec2(posX,halfH - 18)
					intervalNode:addChild(label)
					coroutine.yield()
				end
			end
			count = math.floor((winSize.width-origin.x)/10)
			for i = 0,count do
				local posX = i*10+offsetX
				table.insert(vs,oVec2(posX,halfH))
				table.insert(vs,oVec2(posX,halfH - (i%10 == 0 and 8 or 4)))
				table.insert(vs,oVec2(posX,halfH))
				if i%10 == 0 then
					local label = CCLabelTTF(tostring(i*10),"Arial",10)
					label.texture.antiAlias = false
					label.position = oVec2(posX,halfH - 18)
					intervalNode:addChild(label)
					coroutine.yield()
				end
			end
			coroutine.yield()
			intervalNode:set(vs)
		end))
		
		intervalNode.position = oVec2(halfW,halfH)
		self:addChild(intervalNode)
		intervalNode.data = CCDictionary()
		intervalNode.data.moveListener = oListener("viewArea.move",function(delta)
			intervalNode.positionX = intervalNode.positionX + delta.x/self.scaleX
		end)
		intervalNode.data.toOriginListener = oListener("viewArea.toOrigin",function()
			intervalNode:runAction(oPos(0.5,halfW,halfH,oEase.OutQuad))
		end)

		-- listen view scale event --
		local fadeOut = oOpacity(0.3,0)
		local fadeIn = oOpacity(0.3,0.3)
		self.data = CCDictionary()
		self.data.scaleListener = oListener("viewArea.scale",function(scale)
			self:stopAllActions()
			if scale < 1.0 and self.opacity > 0 and fadeOut.done then
				self.touchEnabled = false
				self:runAction(fadeOut)
			elseif scale >= 1.0 and self.opacity < 1 and fadeIn.done then
				self.touchEnabled = true
				self:runAction(fadeIn)
			elseif scale >= 1.0 then
				local offset = intervalNode.positionX - halfW
				intervalNode.positionX = halfW + offset*self.scaleX/scale
				self.scaleX = scale
				self.scaleY = scale
			end
		end)
		self.data.toScaleListener = oListener("viewArea.toScale",function(scale)
			self:stopAllActions()
			if scale < 1.0 and self.opacity > 0 and fadeOut.done then
				self.touchEnabled = false
				self:runAction(fadeOut)
			elseif scale >= 1.0 and self.opacity < 1 and fadeIn.done then
				self.touchEnabled = true
				self:runAction(fadeIn)
			end
			if scale >= 1.0 then
				local offset = intervalNode.positionX - halfW
				intervalNode.positionX = halfW + offset*self.scaleX/scale
				self:runAction(oScale(0.5,scale,scale,oEase.OutQuad))
			end
		end)

		-- handle touch event --
		self:registerTouchHandler(function(eventType,touch)
			if eventType == CCTouch.Began then
				local loc = self:convertToNodeSpace(touch.location)
				return CCRect(-halfW,-halfH,rulerWidth,rulerHeight):containsPoint(loc)
			elseif eventType == CCTouch.Moved then
				self.positionY = self.positionY + touch.delta.y
				if self.positionY > winSize.height-halfH then
					self.positionY = winSize.height-halfH
				elseif self.positionY < halfH then
					self.positionY = halfH
				end
			end
			return true
		end,false,-1,true)
		self.touchEnabled = true
	end,
})

return oRuler