local require = using("BodyEditor.Script")
local CCDirector = require("CCDirector")
local oLine = require("oLine")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCLayerColor = require("CCLayerColor")
local oScale = require("oScale")
local oEase = require("oEase")
local oOpacity = require("oOpacity")
local CCRect = require("CCRect")
local CCLabelTTF = require("CCLabelTTF")
local oPos = require("oPos")
local CCSequence = require("CCSequence")
local CCCall = require("CCCall")
local once = require("once")
local oEditor = require("oEditor")
local oRoutine = require("oRoutine")
local cycle = require("cycle")

local function oVRuler()
	local winSize = CCDirector.winSize
	local center = oVec2(winSize.width*0.5,winSize.height*0.5)
	local rulerWidth = 30
	local rulerHeight = winSize.height
	local self = CCLayerColor(ccColor4(0),rulerWidth,rulerHeight)
	local halfW = rulerWidth*0.5
	local halfH = rulerHeight*0.5
	local origin = oEditor.origin+center

	self.cascadeOpacity = true
	self.opacity = 0.3
	self.position = oVec2(winSize.width-200-halfW,halfH)

	-- borders --
	local border = oLine(
	{
		oVec2(rulerWidth,rulerHeight),
		oVec2(rulerWidth,0)
	},ccColor4())
	self:addChild(border)

	-- init interval --
	local intervalNode = oLine()
	intervalNode.position = oVec2(halfW,origin.y)
	self:addChild(intervalNode)

	local nPart = 0
	local nCurrentPart = 0
	local pPart = 0
	local pCurrentPart = 0
	local vs = {}
	local function updatePart(nLength,pLength)
		nLength = nLength + 10
		pLength = pLength + 10
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

	local rightOffset = (rulerHeight-origin.y)+100
	local leftOffset = -origin.y-100

	local labels = {}
	local labelList = {}
	local function setupLabels()
		local right = math.floor(rightOffset/100)
		local left = math.ceil(leftOffset/100)
		for i = left,right do
			local pos = i*100
			local label = CCLabelTTF(tostring(pos),"Arial",10)
			label.texture.antiAlias = false
			label.scaleX = 1/self.scaleY
			label.angle = -90
			label.position = oVec2(-halfW+18,pos)
			intervalNode:addChild(label)
			labels[pos] = label
			table.insert(labelList,label)
		end
	end
	local function moveLabel(label,pos)
		labels[tonumber(label.text)] = nil
		label.text = tostring(pos)
		label.texture.antiAlias = false
		label.scaleX = 1/self.scaleY
		label.angle = -90
		label.position = oVec2(-halfW+18,pos)
		labels[pos] = label
	end
	local function updateLabels()
		local right = math.floor((rightOffset-(intervalNode.positionY-origin.y))/100)
		local left = math.ceil((leftOffset-(intervalNode.positionY-origin.y))/100)
		local insertPos = 1
		for i = left,right do
			local pos = i*100
			if labels[pos] then
				break
			else
				local label = table.remove(labelList)
				table.insert(labelList,insertPos,label)
				insertPos = insertPos+1
				moveLabel(label,pos)
			end
		end
		insertPos = #labelList
		for i = right,left,-1 do
			local pos = i*100
			if labels[pos] then
				break
			else
				local label = table.remove(labelList,1)
				table.insert(labelList,insertPos,label)
				insertPos = insertPos-1
				moveLabel(label,pos)
			end
		end
		if nCurrentPart < nPart or pCurrentPart < pPart then
			local start = math.floor(nCurrentPart/10)
			local count = math.floor(nPart/10)
			local length = #vs
			if start < count then
				for i = start,count do
					local posY = i*10
					table.insert(vs,oVec2(-halfW,posY))
					table.insert(vs,oVec2(-halfW+(i%10 == 0 and 8 or 4),posY))
					table.insert(vs,oVec2(-halfW,posY))
					nCurrentPart = nCurrentPart + 10
				end
			end
			start = math.floor(pCurrentPart/10)
			count = math.floor(pPart/10)
			if start < count then
				for i = start,count do
					if i ~= 0 then
						local posY = -i*10
						table.insert(vs,1,oVec2(-halfW,posY))
						table.insert(vs,1,oVec2(-halfW+(i%10 == 0 and 8 or 4),posY))
						table.insert(vs,1,oVec2(-halfW,posY))
					end
					pCurrentPart = pCurrentPart + 10
				end
			end
			if #vs ~= length then
				intervalNode:set(vs)
			end
		end
	end

	-- set default interval negtive & positive part length --
	setupLabels()
	updatePart(origin.y, winSize.height-origin.y)
	updateLabels()

	-- listen view move event --
	intervalNode:gslot("Body.viewArea.move",function(delta)
		intervalNode.positionY = intervalNode.positionY + delta.y/self.scaleY
		updatePart(delta.y < 0 and winSize.height-intervalNode.positionY or 0,
			delta.y > 0 and intervalNode.positionY or 0)
		updateLabels()
	end)
	intervalNode:gslot("Body.viewArea.toPos",function(pos)
		pos = pos + center
		intervalNode:runAction(oPos(0.5,halfW,pos.y,oEase.OutQuad))
		oRoutine(once(function()
			cycle(0.5,function()
				updateLabels()
			end)
		end))
		updatePart(winSize.height-pos.y,pos.y)
	end)

	-- listen view scale event --
	local function updateIntervalTextScale(scale)
		intervalNode:eachChild(function(child)
			child.scaleX = scale
		end)
	end
	local fadeOut = CCSequence({oOpacity(0.3,0),CCCall(function()
		self.scaleY = 1
		updateIntervalTextScale(1)
	end)})
	local fadeIn = oOpacity(0.3,0.3)
	self:gslot("Body.viewArea.scale",function(scale)
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
			self.scaleY = scale
			-- unscale interval text --
			updateIntervalTextScale(1/scale)
		end
	end)
	self:gslot("Body.viewArea.toScale",function(scale)
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
			self:runAction(oScale(0.5,1,scale,oEase.OutQuad))
			-- manually update and unscale interval text --
			local time = 0
			intervalNode:schedule(function(deltaTime)
				updateIntervalTextScale(1/self.scaleY)
				time = time + deltaTime
				if math.min(time/0.5,1) == 1 then
					intervalNode:unschedule()
				end
			end)
		end
	end)

	-- handle touch event --
	self.touchPriority = oEditor.touchPriorityVRuler
	self.swallowTouches = true
	self.touchEnabled = true
	self:slots("TouchBegan",function(touch)
		local loc = self:convertToNodeSpace(touch.location)
		local hit = CCRect(-halfW,-halfH,rulerWidth,rulerHeight):containsPoint(loc)
		if hit then
			self.opacity = 1
		end
		return hit
	end)
	self:slots("TouchMoved",function(touch)
		self.positionX = self.positionX + touch.delta.x
		if self.positionX > winSize.width-190-halfW-10 then
			self.positionX = winSize.width-190-halfW-10
		elseif self.positionX < halfW+10 then
			self.positionX = halfW+10
		end
	end)
	local function touchEnded()
		self:perform(oOpacity(0.3,0.3))
	end
	self:slots("TouchCancelled",touchEnded)
	self:slots("TouchEnded",touchEnded)

	return self
end

return oVRuler