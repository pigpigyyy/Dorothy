local function oSettingPanel()
	local winSize = CCDirector.winSize
	local borderSize = CCSize(160,200*winSize.height/600)
	local viewWidth = 0
	local viewHeight = 0
	local moveY = 0
	local moveX = 0
	local totalDelta = oVec2.zero
	local padding = 100
	local startPos = oVec2.zero
	local time = 0
	local _s = oVec2.zero
	local _v = oVec2.zero
	local deltaMoveLength = 0
	local function initValues()
		viewWidth = 0
		viewHeight = 0
		moveY = 0
		moveX = 0
		totalDelta = oVec2.zero
		startPos = oVec2.zero
		time = 0
		_s = oVec2.zero
		_v = oVec2.zero
		deltaMoveLength = 0
	end
	local panel = CCLayer()
	panel.anchorPoint = oVec2.zero
	panel.contentSize = borderSize
	panel.opacity = 0.3
	panel.touchEnabled = true
	panel.position = oVec2(winSize.width-170,70)
	
	local border = CCDrawNode()
	border:drawPolygon(
	{
		oVec2(0,0),
		oVec2(borderSize.width,0),
		oVec2(borderSize.width,borderSize.height),
		oVec2(0,borderSize.height)
	},ccColor4(0x88000000),0.5,ccColor4(0xffffffff))
	panel:addChild(border)

	local stencil = CCDrawNode()
	stencil:drawPolygon(
	{
		oVec2(0,0),
		oVec2(borderSize.width-2,0),
		oVec2(borderSize.width-2,borderSize.height-2),
		oVec2(0,borderSize.height-2)
	},ccColor4(0xffffffff),0,ccColor4(0x00000000))
	stencil.position = oVec2(1,1)

	local view = CCClipNode(stencil)
	panel:addChild(view)

	local menu = CCMenu(false)
	menu.contentSize = borderSize
	menu.anchorPoint = oVec2(0,1)
	menu.positionY = borderSize.height

	local function updateReset(deltaTime)
		local children = menu.children
		if not children then return end

		local yVal = nil
		time = time + deltaTime
		local t = time/4.0
		if t > 1.0 then t = 1.0 end
		if startPos.y < 0 then
			yVal = totalDelta.y
			totalDelta.y = oEase:func(oEase.OutBack,t,startPos.y,0-startPos.y)
			yVal = totalDelta.y - yVal
		end
		if startPos.y > moveY then
			yVal = totalDelta.y
			totalDelta.y = oEase:func(oEase.OutBack,t,startPos.y,moveY-startPos.y)
			yVal = totalDelta.y - yVal
		end
		
		for i = 1, children.count do
			local node = tolua.cast(children:get(i), "CCNode")
			node.position = node.position + oVec2(0, yVal and yVal or 0)
		end
		
		if t == 1.0 then
			panel:unscheduleUpdate()
			panel:hide()
		end
	end

	local function isReseting()
		if totalDelta.y > moveY or totalDelta.y < 0 then
			return true
		end
		return false
	end

	local function startReset()
		startPos = totalDelta
		time = 0
		panel:scheduleUpdate(updateReset)
	end

	local function setOffset(deltaPos, touching)
		local children = menu.children
		if not children then return end

		local newPos = totalDelta + deltaPos
		
		if touching then
			if newPos.x > 0 then
				newPos.x = 0
			elseif newPos.x-moveX < 0 then
				newPos.x = moveX
			end
			if newPos.y < -padding then
				newPos.y = -padding
			elseif moveY-newPos.y < -padding then
				newPos.y = moveY+padding
			end
			deltaPos = newPos - totalDelta
			
			local lenY = 0
			if newPos.y < 0 then
				lenY = -newPos.y/padding
			elseif newPos.y > moveY then
				lenY = (newPos.y-moveY)/padding
			end
			if lenY > 0 then
				local v = 3*lenY
				deltaPos.y = deltaPos.y / (v > 1 and v*v or 1)
			end
		else
			if newPos.x > 0 then
				newPos.x = 0
			elseif newPos.x < moveX then
				newPos.x = moveX
			end
			if newPos.y < -padding then
				newPos.y = -padding
			elseif newPos.y > moveY+padding then
				newPos.y = moveY+padding
			end
			deltaPos = newPos - totalDelta
		end
		
		if viewWidth < borderSize.width then deltaPos.x = 0 end
		if viewHeight < borderSize.width then deltaPos.y = 0 end

		totalDelta = totalDelta + deltaPos

		for i = 1, children.count do
			local node = tolua.cast(children:get(i), "CCNode")
			node.position = node.position + deltaPos
		end
		
		if not touching and (newPos.y < -padding*0.5 or newPos.y > moveY+padding*0.5) then
			startReset()
		end
	end
	view:addChild(menu)
	
	local function oSettingItem(name, x, y, tapped)
		local menuItem = CCMenuItem()
		menuItem.anchorPoint = oVec2(0,1)
		menuItem.contentSize = CCSize(160,30)
		menuItem.position = oVec2(x, y)
		
		local label = CCLabelTTF(name,"Arial",14)
		label.color = ccColor3(0xffffff)
		label.position = oVec2(40,15)
		label.texture.antiAlias = false
		menuItem:addChild(label)
		
		label = CCLabelTTF("","Arial",14)
		label.color = ccColor3(0xffffff)
		label.position = oVec2(120,15)
		menuItem:addChild(label)
		
		local border = oLine(
		{
			oVec2(0,0),
			oVec2(150,0),
			oVec2(150,30),
			oVec2(0,30),
			oVec2(0,0),
		},ccColor4(0xff00ffff))
		border.positionX = 5
		border.visible = false

		menuItem:addChild(border)
		
		local _value = nil
		
		menuItem.setValue = function(self,value)
			if value then
				if type(value) == "number" then
					label.text = string.format("%.2f",value)
				else
					label.text = tostring(value)
				end
				label.texture.antiAlias = false
				_value = value
			else
				label.text = ""
				_value = nil
			end
		end
		
		menuItem.getValue = function(self)
			return _value
		end
		
		menuItem.select = function(self, var)
			border.visible = var
		end
		
		local selected = false
		
		menuItem:registerTapHandler(
			function(eventType,self)
				if eventType == CCMenuItem.TapBegan then
				elseif eventType == CCMenuItem.TapEnded then
				elseif eventType == CCMenuItem.Tapped then
					oEvent:send("SettingSelected",{menuItem,})
				end
			end)
		
		return menuItem
	end
	
	local opacity = oOpacity(0.5,0.3,oEase.InExpo)
	panel.show = function(self)
		if not opacity.done then
			self:stopAction(opacity)
		end
		self.opacity = 1.0
	end
	panel.hide = function(self)
		self:runAction(opacity)
	end

	local function updateSpeed(deltaTime)
		if _s == oVec2.zero then
			return
		end
		_v = _s / deltaTime
		_s = oVec2.zero
	end
	local function updatePos(deltaTime)
		local val = winSize.height*2
		local a = oVec2(_v.x > 0 and -val or val,_v.y > 0 and -val or val)
		
		local xR = _v.x > 0
		local yR = _v.y > 0
		
		_v = _v + a*deltaTime
		if _v.x < 0 == xR then _v.x = 0;a.x = 0 end
		if _v.y < 0 == yR then _v.y = 0;a.y = 0 end
		
		local ds = _v * deltaTime + a*(0.5*deltaTime*deltaTime)
		setOffset(ds, false)
		
		if _v == oVec2.zero then
			if isReseting() then
				startReset()
			else
				panel:hide()
				panel:unscheduleUpdate()
			end
		end
	end

	panel:registerTouchHandler(
		function(eventType, touch)
			--touch=CCTouch
			if touch.id ~= 0 then
				return false
			end
			if eventType == CCTouch.Began then
				if not CCRect(oVec2.zero, panel.contentSize):containsPoint(panel:convertToNodeSpace(touch.location)) then
					return false
				end
				
				panel:show()

				deltaMoveLength = 0
				menu.enabled = true
				panel:scheduleUpdate(updateSpeed)
			elseif eventType == CCTouch.Ended or eventType == CCTouch.Cancelled then
				menu.enabled = true
				if isReseting() then
					startReset()
				else
					if _v == oVec2.zero or deltaMoveLength <= 20 then
						panel:hide()
					else
						panel:scheduleUpdate(updatePos)
					end
				end
			elseif eventType == CCTouch.Moved then
				deltaMoveLength = deltaMoveLength + touch.delta.length
				_s = _s + touch.delta
				if deltaMoveLength > 20 then
					menu.enabled = false
					setOffset(touch.delta, true)
				end
			end
			return true
		end, false, 0, true)
	
	local getPosY = (function()
		local index = 0
		return function()
			local v = index
			index = index + 1
			return borderSize.height-10-30*v
		end
	end)()
	
	local keyItems =
	{
		oSettingItem("Time :",0,getPosY()),
		oSettingItem("PosX :",0,getPosY()),
		oSettingItem("PosY :",0,getPosY()),
		oSettingItem("ScaleX :",0,getPosY()),
		oSettingItem("ScaleY :",0,getPosY()),
		oSettingItem("Rotation :",0,getPosY()),
		oSettingItem("Opacity :",0,getPosY()),
		oSettingItem("SkewX :",0,getPosY()),
		oSettingItem("SkewY :",0,getPosY()),
		oSettingItem("visible :",0,getPosY()),
		oSettingItem("EaseP :",0,getPosY()),
		oSettingItem("EaseS :",0,getPosY()),
		oSettingItem("EaseK :",0,getPosY()),
		oSettingItem("EaseR :",0,getPosY()),
		oSettingItem("EaseO :",0,getPosY()),
	}
		
	for _,item in ipairs(keyItems) do
		menu:addChild(item)
	end

	panel.updateItems = function(self)
		initValues()
		viewHeight = 30*#keyItems+20
		viewWidth = borderSize.width
		moveY = viewHeight-borderSize.height
		moveX = borderSize.width-viewWidth
	end
	
	panel.updateValues = function(self, pos)
		if not pos then
			for _,item in ipairs(keyItems) do
				item:setValue(nil)
			end
			oEditor.keyIndex = nil
			return
		end
		if not oEditor.animationData then return end
		local time = math.floor(pos+0.5)
		local total = 0
		local index = 1
		for i = 2, #oEditor.animationData do
			total = total + oEditor.animationData[i][oKd.duration]
			if time >= math.floor(total*60+0.5) then
				index = i
			end
		end
		if oEditor.keyIndex and oEditor.keyIndex == index then
			return
		end
		local frame = oEditor.animationData[index]
		keyItems[1]:setValue(time/60)
		keyItems[2]:setValue(frame[oKd.x])
		keyItems[3]:setValue(frame[oKd.y])
		keyItems[4]:setValue(frame[oKd.scaleX])
		keyItems[5]:setValue(frame[oKd.scaleY])
		keyItems[6]:setValue(frame[oKd.rotation])
		keyItems[7]:setValue(frame[oKd.opacity])
		keyItems[8]:setValue(frame[oKd.skewX])
		keyItems[9]:setValue(frame[oKd.skewY])
		keyItems[10]:setValue(frame[oKd.visible])
		keyItems[11]:setValue(frame[oKd.easePos])
		keyItems[12]:setValue(frame[oKd.easeScale])
		keyItems[13]:setValue(frame[oKd.easeSkew])
		keyItems[14]:setValue(frame[oKd.easeRotation])
		keyItems[15]:setValue(frame[oKd.easeOpacity])
		oEditor.keyIndex = index
	end
	
	panel:updateItems()
	
	local selectedItem = nil
	
	panel.listener = oListener("SettingSelected",
		function(args)
			local menuItem = args[1]
			if selectedItem then
				selectedItem:select(false)
			end
			if selectedItem ~= menuItem then
				menuItem:select(true)
				selectedItem = menuItem
			else
				menuItem:select(false)
				selectedItem = nil
			end
		end)
	
	return panel
end

return oSettingPanel