local ccColor4 = require("ccColor4")
local oNode3D = require("oNode3D")
local oVec2 = require("oVec2")
local CCLayerColor = require("CCLayerColor")
local oLine = require("oLine")
local CCLayer = require("CCLayer")
local CCMenu = require("CCMenu")
local CCDrawNode = require("CCDrawNode")
local ccColor3 = require("ccColor3")
local CCLabelTTF = require("CCLabelTTF")
local oButton = require("oButton")
local once = require("once")
local cycle = require("cycle")
local oEase = require("oEase")
local CCTouch = require("CCTouch")
local CCRect = require("CCRect")
local oEditor = require("oEditor")

local function oColorPicker(color,callback)
	color = color or ccColor4()
	local changed = callback
	local panelSize = 270
	local barWidth = 20
	local finalColorSize = 140
	local borderWidth = (panelSize+20)+(barWidth+20)+(finalColorSize+20)
	local borderHeight = panelSize+20
	local halfW = borderWidth*0.5
	local halfH = borderHeight*0.5
	local buttonWidth = finalColorSize-20

	local panel = oNode3D()
	panel.position = oEditor.origin

	local background = CCLayerColor(ccColor4(0x88000000),borderWidth,borderHeight)
	panel:addChild(background)

	local border = oLine({oVec2(-halfW,halfH),oVec2(halfW,halfH),oVec2(halfW,-halfH),oVec2(-halfW,-halfH),oVec2(-halfW,halfH)},ccColor4(0x88ffafaf))
	border.position = oVec2(halfW,halfH)
	background:addChild(border)

	local mask = CCLayer()
	mask.contentSize = background.contentSize
	mask.anchor = oVec2.zero
	mask.touchPriority = CCMenu.DefaultHandlerPriority-1
	mask.swallowTouches = true
	mask.touchEnabled = true
	mask.touchHandler = function(eventType, touch)
		if eventType == CCTouch.Began then
			if CCRect(oVec2.zero,mask.contentSize):containsPoint(mask:convertToNodeSpace(touch.location)) then
				return panel.visible
			end
		end
		return false
	end
	background:addChild(mask)

	local ChanelR,ChanelG,ChanelB = 1,2,3
	local currentChanel = ChanelR

	local r,g,b,a = color.r,color.g,color.b,color.a
	local function shiftColor(v,bit)
		return v*math.pow(2,bit)
	end
	local function getColorStr()
		return string.format("0x%.8X",shiftColor(a,24)+shiftColor(r,16)+shiftColor(g,8)+shiftColor(b,0))
	end

	local colorPanel = CCLayerColor(ccColor4(),panelSize,panelSize)
	colorPanel.anchor = oVec2.zero
	colorPanel.position = oVec2(10,10)
	background:addChild(colorPanel)
	local function resetPanelColor()
		local c0,c1,c2,c3
		if currentChanel == ChanelR then
			c0,c1,c2,c3 = ccColor4(r,0xff,0xff,0xff),ccColor4(r,0xff,0,0xff),ccColor4(r,0,0,0xff),ccColor4(r,0,0xff,0xff)
		elseif currentChanel == ChanelG then
			c0,c1,c2,c3 = ccColor4(0xff,g,0xff,0xff),ccColor4(0xff,g,0,0xff),ccColor4(0,g,0,0xff),ccColor4(0,g,0xff,0xff)
		elseif currentChanel == ChanelB then
			c0,c1,c2,c3 = ccColor4(0xff,0xff,b,0xff),ccColor4(0xff,0,b,0xff),ccColor4(0,0,b,0xff),ccColor4(0,0xff,b,0xff)
		end
		colorPanel:resetColor(c1,c2,c0,c3)
	end

	local redBar = CCLayerColor(ccColor4(),barWidth,panelSize)
	redBar.anchor = oVec2.zero
	redBar.position = oVec2((panelSize+20)+10,10)
	background:addChild(redBar)
	local function resetBarColor()
		local c0,c1
		if currentChanel == ChanelR then
			c0,c1 = ccColor4(255,g,b,255),ccColor4(0,g,b,255)
		elseif currentChanel == ChanelG then
			c0,c1 = ccColor4(r,255,b,255),ccColor4(r,0,b,255)
		elseif currentChanel == ChanelB then
			c0,c1 = ccColor4(r,g,255,255),ccColor4(r,g,0,255)
		end
		redBar:resetColor(c1,c1,c0,c0)
	end

	local target = CCDrawNode()
	target:drawPolygon({oVec2(-5,5),oVec2(5,5),oVec2(5,-5),oVec2(-5,-5)},ccColor4(0),1,ccColor4())
	target.position = oVec2((255-g)*panelSize/255,b*panelSize/255)
	colorPanel:addChild(target)
	local function updateTargetPos()
		if currentChanel == ChanelR then
			target.position = oVec2((255-g)*panelSize/255,b*panelSize/255)
		elseif currentChanel == ChanelG then
			target.position = oVec2((255-r)*panelSize/255,b*panelSize/255)
		elseif currentChanel == ChanelB then
			target.position = oVec2((255-r)*panelSize/255,g*panelSize/255)
		end
	end
	local function getCurrentPosColor()
		local x = math.floor(255-255*target.positionX/panelSize+0.5)
		local y = math.floor(255*target.positionY/panelSize+0.5)
		return x,y
	end
	local function updateTargetColor()
		local whiteDiff = math.abs(255-r)+math.abs(255-g)+math.abs(255-b)+math.abs(255-a)
		local blackDiff = math.abs(0-r)+math.abs(0-g)+math.abs(0-b)+math.abs(0-a)
		if whiteDiff > blackDiff+255 then
			target.color = ccColor3()
		else
			target.color = ccColor3(0)
		end
	end

	local arrow = CCDrawNode()
	arrow:drawSegment(oVec2(0,0),oVec2(10,0),1,ccColor4(0xfffcfcfc))
	background:addChild(arrow)
	local function updateArrowPos()
		if currentChanel == ChanelR then
			arrow.position = oVec2(panelSize+20-1,10+r*panelSize/255)
		elseif currentChanel == ChanelG then
			arrow.position = oVec2(panelSize+20-1,10+g*panelSize/255)
		elseif currentChanel == ChanelB then
			arrow.position = oVec2(panelSize+20-1,10+b*panelSize/255)
		end
	end

	local halfSize = finalColorSize*0.5
	local finalColor = CCDrawNode()
	finalColor:drawPolygon({oVec2(-halfSize,halfSize),oVec2(halfSize,halfSize),oVec2(halfSize,-halfSize),oVec2(-halfSize,-halfSize)},ccColor4())
	finalColor.color = ccColor3(r,g,b)
	finalColor.opacity = a/255
	finalColor.position = oVec2(borderWidth-10-halfSize,borderHeight-10-halfSize)
	background:addChild(finalColor)

	local label = CCLabelTTF("","Arial",18)
	label.color = ccColor3(0x00ffff)
	label.position = oVec2(borderWidth-10-halfSize,borderHeight-20-finalColorSize-9)
	background:addChild(label)
	label.text = getColorStr()
	label.texture.antiAlias = false
	local function updateDisplayColor()
		finalColor.color = ccColor3(r,g,b)
		finalColor.opacity = a/255
		label.text = getColorStr()
		label.texture.antiAlias = false
	end

	local alphaBar = CCLayerColor(ccColor4(),finalColorSize,barWidth)
	alphaBar.anchor = oVec2.zero
	local alphaBarY = borderHeight-20-finalColorSize-label.contentSize.height-barWidth-10
	alphaBar.position = oVec2(borderWidth-finalColorSize-10,alphaBarY)
	background:addChild(alphaBar)
	local function resetAlphaColor()
		local c0,c1 = ccColor4(r,g,b,255),ccColor4(r,g,b,0)
		alphaBar:resetColor(c0,c1,c0,c1)
	end

	local alphaArrow = CCDrawNode()
	alphaArrow:drawSegment(oVec2(0,0),oVec2(0,-10),1,ccColor4(0xfffcfcfc))
	alphaBar:addChild(alphaArrow)
	local function updateAlphaArrowPos()
		alphaArrow.position = oVec2(0+(255-a)*finalColorSize/255,0)
	end

	local menu = CCMenu(false)
	menu.anchor = oVec2.zero
	menu.contentSize = panel.contentSize
	menu.touchPriority = CCMenu.DefaultHandlerPriority-2
	background:addChild(menu)

	local channelButtonWidth = buttonWidth/3
	local channelButtonHeight = alphaBarY-30
	local channelButtonY = alphaBarY-20-channelButtonHeight*0.5
	local rButton,gButton,bButton
	rButton = oButton("R",16,
		channelButtonWidth,
		channelButtonHeight,
		borderWidth-10-finalColorSize+buttonWidth/6,
		channelButtonY,function()
		rButton.color = ccColor3(0xff88cc)
		gButton.color = ccColor3(0x00ffff)
		bButton.color = ccColor3(0x00ffff)
		currentChanel = ChanelR
		resetPanelColor()
		resetBarColor()
		resetAlphaColor()
		updateTargetPos()
		updateTargetColor()
		updateArrowPos()
	end)
	rButton.color = ccColor3(0xff88cc)
	menu:addChild(rButton)

	gButton = oButton("G",16,
		channelButtonWidth,
		channelButtonHeight,
		borderWidth-10-finalColorSize*0.5,
		channelButtonY,function()
		rButton.color = ccColor3(0x00ffff)
		gButton.color = ccColor3(0xff88cc)
		bButton.color = ccColor3(0x00ffff)
		currentChanel = ChanelG
		resetPanelColor()
		resetBarColor()
		resetAlphaColor()
		updateTargetPos()
		updateTargetColor()
		updateArrowPos()
	end)
	menu:addChild(gButton)

	bButton = oButton("B",16,
		channelButtonWidth,
		channelButtonHeight,
		borderWidth-10-buttonWidth/6,
		channelButtonY,function()
		rButton.color = ccColor3(0x00ffff)
		gButton.color = ccColor3(0x00ffff)
		bButton.color = ccColor3(0xff88cc)
		currentChanel = ChanelB
		resetPanelColor()
		resetBarColor()
		resetAlphaColor()
		updateTargetPos()
		updateTargetColor()
		updateArrowPos()
	end)
	menu:addChild(bButton)

	colorPanel.touchPriority = CCMenu.DefaultHandlerPriority-2
	colorPanel.touchEnabled = true
	colorPanel.touchHandler = function(eventType,touch)
		if eventType == CCTouch.Began then
			return CCRect(oVec2.zero,colorPanel.contentSize):containsPoint(colorPanel:convertToNodeSpace(touch.location))
		elseif eventType == CCTouch.Moved then
			target.position = target.position + touch.delta
			target.positionX = math.min(target.positionX,panelSize)
			target.positionX = math.max(target.positionX,0)
			target.positionY = math.min(target.positionY,panelSize)
			target.positionY = math.max(target.positionY,0)
			local x,y = getCurrentPosColor()
			if currentChanel == ChanelR then
				g,b = x,y
			elseif currentChanel == ChanelG then
				r,b = x,y
			elseif currentChanel == ChanelB then
				r,g = x,y
			end
			resetBarColor()
			updateTargetColor()
			resetAlphaColor()
			updateDisplayColor()
		end
		return true
	end

	redBar.touchPriority = CCMenu.DefaultHandlerPriority-2
	redBar.touchEnabled = true
	redBar.touchHandler = function(eventType,touch)
		if eventType == CCTouch.Began then
			local size = redBar.contentSize
			size.width = size.width+40
			size.height = size.height+20
			return CCRect(oVec2(-20,-10),size):containsPoint(redBar:convertToNodeSpace(touch.location))
		elseif eventType == CCTouch.Moved then
			arrow.positionY = arrow.positionY + touch.delta.y
			arrow.positionY = math.min(arrow.positionY,panelSize+10)
			arrow.positionY = math.max(arrow.positionY,10)
			local value = math.floor((arrow.positionY-10)*255/panelSize+0.5)
			if currentChanel == ChanelR then
				r = value
			elseif currentChanel == ChanelG then
				g = value
			elseif currentChanel == ChanelB then
				b = value
			end
			resetPanelColor()
			updateTargetColor()
			resetAlphaColor()
			updateDisplayColor()
		end
		return true
	end

	alphaBar.touchEnabled = true
	alphaBar.touchPriority = CCMenu.DefaultHandlerPriority-2
	alphaBar.touchHandler = function(eventType,touch)
		if eventType == CCTouch.Began then
			local size = alphaBar.contentSize
			size.width = size.width+20
			size.height = size.height+20
			return CCRect(oVec2(-10,-10),size):containsPoint(alphaBar:convertToNodeSpace(touch.location))
		elseif eventType == CCTouch.Moved then
			alphaArrow.positionX = alphaArrow.positionX + touch.delta.x
			alphaArrow.positionX = math.min(alphaArrow.positionX,finalColorSize)
			alphaArrow.positionX = math.max(alphaArrow.positionX,0)
			a = 255-math.floor(alphaArrow.positionX*255/finalColorSize+0.5)
			resetAlphaColor()
			updateDisplayColor()
		end
		return true
	end

	local function setColor(self,oldVal)
		r,g,b,a = oldVal.r,oldVal.g,oldVal.b,oldVal.a
		resetPanelColor()
		resetBarColor()
		resetAlphaColor()
		updateTargetPos()
		updateTargetColor()
		updateArrowPos()
		updateAlphaArrowPos()
		updateDisplayColor()
	end
	panel.setColor = setColor
	panel:setColor(color)

	panel.hide = function(self)
		if changed then
			changed(r,g,b,a)
			changed = nil
		end
		self:schedule(once(function()
			local begin = self.angleX
			local time = 0
			cycle(0.3,function(deltaTime)
				time = time + deltaTime
				self.angleX = oEase:func(oEase.OutBack,time/0.3,begin,-90)
			end)
			self.angleX = -90
			self.visible = false
		end))
	end

	panel.show = function(self,color,callback)
		self.visible = true
		self:setColor(color)
		changed = callback
		self:schedule(once(function()
			self.angleX = -90
			local time = 0
			cycle(0.3,function(deltaTime)
				time = time + deltaTime
				self.angleX = oEase:func(oEase.OutBack,time/0.3,-90,90)
			end)
			self.angleX = 0
		end))
	end

	return panel
end

return oColorPicker
