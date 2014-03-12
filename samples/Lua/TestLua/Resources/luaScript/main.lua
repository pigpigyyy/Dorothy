collectgarbage("setpause", 100)
collectgarbage("setstepmul", 50000)

local function oButton(text, fontSize, width, height, x, y, tapped)
	local label = CCLabelTTF(text,"Arial",fontSize)
	label.color = ccColor3(0x00ffff)
	label.position = oVec2(width*0.5, height*0.5)
	label.texture.antiAlias = false
	local drawNode = CCDrawNode()
	drawNode:drawPolygon(
	{
		oVec2(0,0),
		oVec2(width,0),
		oVec2(width,height),
		oVec2(0,height)
	},ccColor4(0x88000000),0.5,ccColor4(0xff00ffff))

	local face = CCNode()
	face.anchorPoint = oVec2(0.5,0.5)
	face.contentSize = CCSize(width,height)
	face.position = oVec2(width*0.5,height*0.5)
	face:addChild(drawNode)
	face:addChild(label)

	local menuItem = CCMenuItem()
	menuItem.contentSize = CCSize(width,height)
	menuItem.anchorPoint = oVec2(0.5,0.5)
	menuItem:addChild(face)
	
	face.opacity = 0.3
	local scale = oScale(0.3, 1.0, 1.0, oEase.OutBack)
	local fade = oOpacity(0.3, 0.3)
	menuItem.label = label
	menuItem:registerTapHandler(
		function(eventType, item)
			--item = CCMenuItem
			if eventType == CCMenuItem.TapBegan then
				if not fade.done then
					face:stopAction(fade)
				end
				if not scale.done then
					face:stopAction(scale)
				end
				face.opacity = 1.0
				face.scaleX = 0.5
				face.scaleY = 0.5
				face:runAction(scale)
				if tapped then
					tapped(menuItem)
				end
			elseif eventType == CCMenuItem.TapEnded then
				face:runAction(fade)
			end
		end)
	menuItem.position = oVec2(x,y)
	return menuItem
end

local function oEditMenu()
    local size = CCDirector.winSize
    local menu = CCMenu()
	CCDirector.listener = oListener("one",
		function(args)
			cclog(args)
			menu:runAction(
				CCSequence
				{
					oScale(3,0,0,oEase.InElastic),
					oScale(3,1,1,oEase.OutElastic)
				})
		end)
	menu.anchorPoint = oVec2.zero
	menu.items =
	{
		Edit = oButton("Edit",16,50,50,35,size.height-35,function() oEvent:send("one", "apple") end),
		Move = oButton("Move",16,50,50,35,size.height-95),
		Rotate = oButton("Rotate",16,50,50,35,size.height-155),
		Scale = oButton("Scale",16,50,50,35,size.height-215),
		Opacity = oButton("Opacity",14,50,50,35,size.height-275),
		
		New = oButton("New",16,50,50,35,95),
		Delete = oButton("Delete",16,50,50,95,95),
		Copy = oButton("Copy",16,50,50,155,95),
		Paste = oButton("Paste",16,50,50,215,95),
		Clear = oButton("Clear",16,50,50,275,95),
		Play = oButton("Play",16,50,50,size.width-205,95,
			function(item)
				item.label.text = "Pause"
				item.label.texture.antiAlias = false
			end),
		
		Origin = oButton("Origin",16,50,50,size.width-265,size.height-40),
		Zoom = oButton("100%",16,50,50,size.width-205,size.height-40),
	}
	for _,item in pairs(menu.items) do
		menu:addChild(item)
	end
    return menu
end

local function oControlBar()
    local size = CCDirector.winSize
	local barDragPos = 50
	
	-- controlBar
	local controlBar = CCLayer()
	controlBar.anchorPoint = oVec2.zero
	controlBar.contentSize = CCSize(size.width,60)
	controlBar.opacity = 0.3
	controlBar.touchEnabled = true
	
	-- border
	local border = CCDrawNode()
	border:drawPolygon(
	{
		oVec2(0,0),
		oVec2(size.width-20,0),
		oVec2(size.width-20,50),
		oVec2(0,50)
	},ccColor4(0x88000000),0.5,ccColor4(0xffffffff))
	border.position = oVec2(10,10)

	-- Notice label
	local notice = CCDrawNode()
	notice:drawPolygon(
	{
		oVec2(0,0),
		oVec2(barDragPos,0),
		oVec2(barDragPos,6),
		oVec2(0,6)
	},ccColor4(0x33ffffff),0,ccColor4(0x00000000))
	notice.anchorPoint = oVec2.zero
	notice.contentSize = CCSize(barDragPos,5)
	notice.position = oVec2(30,20)
	notice._scaleIn = oScale(0.3,0.0,1.0,oEase.InBack)
	notice._scaleOut = oScale(0.3,1.0,1.0,oEase.OutBack)
	notice.scaleX = 0.0

	-- bar
	local barLength = size.width-60
	local barIterval = barLength/60
	local bar = CCDrawNode()
	bar:drawPolygon(
	{
		oVec2(0,0),
		oVec2(barLength,0),
		oVec2(barLength,6),
		oVec2(0,6)
	},ccColor4(0xffffffff),0,ccColor4(0x00000000))
	bar.setPos = function(self,pos)
		self._pos = pos
		self.scaleX = math.floor(pos)/60.0
		if self.scaleX == 0.0 then
			if notice.scaleX ~= 1.0 then
				if notice._scaleOut.done then
					notice:stopAllActions()
					notice:runAction(notice._scaleOut)
				end
			end
		else
			if notice.scaleX ~= 0.0 then
				if notice._scaleIn.done then
					notice:stopAllActions()
					notice:runAction(notice._scaleIn)
				end
			end
		end
	end
	bar.getPos = function(self)
		return self._pos
	end
	bar.anchorPoint = oVec2.zero
	bar.contentSize = CCSize(barLength,5)
	bar.position = oVec2(30,20)
	bar:setPos(0)

	-- ruler
	local ruler = CCDrawNode()
	ruler._size = 0
	ruler.setSize = function(self,size)
		local delta = barIterval
		if size < self._size then
			self:removeAllChildrenWithCleanup(true)
			self:clear()
			self:drawSegment(oVec2.zero,oVec2(delta*size,0),0.5,ccColor4(0xffffffff))
		else
			self:drawSegment(oVec2(delta*self._size,0),oVec2(delta*size),0.5,ccColor4(0xffffffff))
		end
		for i = self._size, size do
			local posX = delta*i
			if i == 0 or (i%10 == 0 and i ~= self._size) then
				local label = CCLabelAtlas(tostring(i),"rulerNum.png",7,11,string.byte("0"))
				label.texture.antiAlias = false
				label.position = oVec2(posX, 14)
				self:addChild(label)
				self:drawSegment(
					oVec2(posX,0),
					oVec2(posX,6),
					0.5,ccColor4(0xffffffff))
			elseif i%10 ~= 0 then					
				self:drawSegment(
					oVec2(posX,0),
					oVec2(posX,3),
					0.5,ccColor4(0xffffffff))
			end
		end
		self._size = size
	end
	ruler.getSize = function(self)
		return self._size
	end
	ruler:setSize(120)
	ruler.position = oVec2(30,35)

	-- controlNode
	local controlNode = CCNode()
	controlNode:addChild(ruler)
	controlNode:addChild(notice)
	controlNode:addChild(bar)
	
	-- stencil
	local stencil = CCDrawNode()
	stencil:drawPolygon(
	{
		oVec2(0,0),
		oVec2(size.width-20,0),
		oVec2(size.width-20,50),
		oVec2(0,50)
	},ccColor4(0xffffffff),0,ccColor4(0x00000000))
	stencil.position = oVec2(10,10)
	local clipNode = CCClipNode(stencil)
	clipNode:addChild(controlNode)
	
	-- build controlBar
	controlBar:addChild(border)
	controlBar:addChild(clipNode)
	local fade = oOpacity(0.3, 0.3)
	local lastPos = 0
	local offset = 0
	local moveBar = false
	local startPos = 0
	controlBar:registerTouchHandler(
		function(eventType, touch)
			--touch = CCTouch
			if touch.id ~= 0 then
				return
			end
			local loc = controlBar:convertToNodeSpace(touch.location)
			local locLength = loc.x-10
			if locLength < 0 then locLength = 0 end
			if locLength > barLength then locLength = barLength end
			
			if eventType == CCTouch.Began then
				if not CCRect(oVec2.zero, controlBar.contentSize):containsPoint(loc) then
					return false
				end
			end
			if eventType == CCTouch.Began then
				if not fade.done then
					controlBar:stopAction(fade)
				end
				controlBar.opacity = 1.0
				--cclog("Start %d,%d",lastPos,offset)
				if lastPos-barDragPos <= locLength and locLength <= lastPos+barDragPos then
					moveBar = true
				end
			elseif eventType == CCTouch.Ended or eventType == CCTouch.Cancelled then
				controlBar:runAction(fade)
				if moveBar then
					lastPos = locLength
					moveBar = false
				end
				--cclog("End %d,%d",lastPos,offset)
			elseif eventType == CCTouch.Moved then
				if moveBar then
					local pos = (locLength-offset)*60/barLength
					bar:setPos(pos)
				else
					local deltaX = touch.delta.x
					offset = offset + deltaX
					if offset > 0 then
						offset = 0
					else		
						lastPos = lastPos + deltaX
					end
					controlNode.positionX = offset
					local displaySize = math.ceil((barLength-offset)/barIterval)
					if displaySize >= ruler:getSize() then
						ruler:setSize(ruler:getSize()+60)
					end
				end
			end
			return true
		end)
	
	return controlBar
end

local scene = CCScene()
scene.anchorPoint = oVec2.zero
local layer = CCLayerColor(ccColor4(0xff1a1a1a), CCDirector.winSize.width, CCDirector.winSize.height)
layer.anchorPoint = oVec2.zero
scene:addChild(layer)
scene:addChild(oEditMenu())
scene:addChild(oControlBar())

local model = oModel("jiandunA.model")
model.look = "happy"
model.loop = true
model:play("attack1")
model.position = oVec2(CCDirector.winSize.width*0.5, CCDirector.winSize.height*0.5)
scene:addChild(model)

CCDirector:run(scene)
