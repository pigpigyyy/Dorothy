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
local CCSequence = require("CCSequence")
local CCCall = require("CCCall")
local CCNode = require("CCNode")
local oRoutine = require("oRoutine")
local once = oRoutine.once

local winSize = CCDirector.winSize
local rulerWidth = winSize.width
local rulerHeight = 30

local oHRuler = class(
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
		self.position = oVec2(halfW,halfH)

		-- borders --
		local border = oLine(
		{
			oVec2.zero,
			oVec2(rulerWidth,0)
		},ccColor4())
		self:addChild(border)

		-- init interval --
		local intervalNode = oLine()
		local nPart = 0
		local nCurrentPart = 0
		local pPart = 0
		local pCurrentPart = 0
		local vs = {}
		local function updatePart(nLength,pLength)
			if nLength <= nPart and pLength <= pPart then
				return
			end
			if nLength > nPart then
				nPart = math.ceil(nLength/10)*10
			end
			if pLength > pPart then
				pPart = math.ceil(pLength/10)*10
			end
		end
		
		-- worker thread for intervals creation --
		self:schedule(once(function()
			repeat
				if nCurrentPart < nPart or pCurrentPart < pPart then
					local start = math.floor(nPart/10)
					local count = math.floor(nCurrentPart/10)
					local length = #vs
					if start > count then
						for i = count,start do
							if i ~= 0 then
								local posX = -i*10
								table.insert(vs,1,oVec2(posX,halfH))
								table.insert(vs,1,oVec2(posX,halfH - (i%10 == 0 and 8 or 4)))
								table.insert(vs,1,oVec2(posX,halfH))
								if i%10 == 0 then
									local label = CCLabelTTF(tostring(-i*10),"Arial",10)
									label.texture.antiAlias = false
									label.scaleX = 1/intervalNode.scaleX
									label.position = oVec2(posX,halfH - 18)
									intervalNode:addChild(label)
									coroutine.yield()
								end
							end
							nCurrentPart = nCurrentPart + 10
						end
					end
					start = math.floor(pCurrentPart/10)
					count = math.floor(pPart/10)
					if start < count then
						for i = start,count do
							local posX = i*10
							table.insert(vs,oVec2(posX,halfH))
							table.insert(vs,oVec2(posX,halfH - (i%10 == 0 and 8 or 4)))
							table.insert(vs,oVec2(posX,halfH))
							if i%10 == 0 then
								local label = CCLabelTTF(tostring(i*10),"Arial",10)
								label.texture.antiAlias = false
								label.scaleX = 1/intervalNode.scaleX
								label.position = oVec2(posX,halfH - 18)
								intervalNode:addChild(label)
								coroutine.yield()
							end
							pCurrentPart = pCurrentPart + 10
						end
					end
					if #vs ~= length then
						intervalNode:set(vs)
					end
				end
				coroutine.yield()
			until false
		end))

		-- set default interval negtive & positive part length --
		updatePart(origin.x, winSize.width-origin.x)
		intervalNode.position = oVec2(origin.x,halfH)
		intervalNode.data = CCDictionary()
		self:addChild(intervalNode)
		
		-- listen view move event --
		intervalNode.data.moveListener = oListener("viewArea.move",function(delta)
			intervalNode.positionX = intervalNode.positionX + delta.x
			updatePart(delta.x > 0 and intervalNode.positionX or 0,
				delta.x < 0 and winSize.width-intervalNode.positionX or 0)
		end)
		intervalNode.data.toOriginListener = oListener("viewArea.toOrigin",function()
			intervalNode:runAction(oPos(0.5,origin.x,halfH,oEase.OutQuad))
		end)

		-- listen view scale event --
		local function updateIntervalTextScale(scale)
			local children = intervalNode.children
			for i = 1, children.count do
				children[i].scaleX = scale
			end
		end
		local fadeOut = CCSequence({oOpacity(0.3,0),CCCall(function()
			intervalNode.scaleX = 1
			updateIntervalTextScale(1)
		end)})
		local fadeIn = oOpacity(0.3,0.3)
		self.data = CCDictionary()
		self.data.scaleListener = oListener("viewArea.scale",function(scale)
			if scale < 1.0 and self.opacity > 0 and fadeOut.done then
				self.touchEnabled = false
				self:stopAllActions()
				self:runAction(fadeOut)
			elseif scale >= 1.0 then
				if self.opacity == 0 and fadeIn.done then
					self.touchEnabled = true
					self:stopAllActions()
					self:runAction(fadeIn)
				end
				intervalNode.scaleX = scale
				-- unscale interval text --
				updateIntervalTextScale(1/scale)
			end
		end)
		self.data.toScaleListener = oListener("viewArea.toScale",function(scale)
			if scale < 1.0 and self.opacity > 0 and fadeOut.done then
				self.touchEnabled = false
				self:stopAllActions()
				self:runAction(fadeOut)
			elseif scale >= 1.0 and self.opacity == 0 and fadeIn.done then
				self.touchEnabled = true
				self:stopAllActions()
				self:runAction(fadeIn)
			end
			if scale >= 1.0 then
				intervalNode:runAction(oScale(0.5,scale,1,oEase.OutQuad))
				-- manually update and unscale interval text --
				local time = 0
				local begin = intervalNode.children[1].scaleX
				local change = 1/scale-begin
				intervalNode:schedule(function(self,deltaTime)
					time = time + deltaTime
					local t = math.min(time/0.5,1)
					updateIntervalTextScale(oEase:func(oEase.OutQuad,t,begin,change))
					if t == 1 then
						self:unschedule()
					end
				end)
			end
		end)

		-- handle touch event --
		self:registerTouchHandler(function(eventType,touch)
			if eventType == CCTouch.Began then -- check touch area
				local loc = self:convertToNodeSpace(touch.location)
				return CCRect(-halfW,-halfH,rulerWidth,rulerHeight):containsPoint(loc)
			elseif eventType == CCTouch.Moved then -- move up and down
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

return oHRuler