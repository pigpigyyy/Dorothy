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
		if viewHeight < borderSize.height then deltaPos.y = 0 end

		totalDelta = totalDelta + deltaPos

		for i = 1, children.count do
			local node = tolua.cast(children:get(i), "CCNode")
			node.position = node.position + deltaPos
		end
		
		if not touching and (newPos.y < -padding*0.5 or newPos.y > moveY+padding*0.5 or newPos.x > padding*0.5 or newPos.x < moveX-padding*0.5) then
			startReset()
		end
	end
	view:addChild(menu)
	
	local function oSettingItem(name, x, y, enableFunc, disableFunc)
		local menuItem = CCMenuItem()
		menuItem.anchorPoint = oVec2(0,1)
		menuItem.contentSize = CCSize(160,30)
		menuItem.position = oVec2(x, y)
		menuItem.enabled = false
		
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
			if value ~= nil then
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

		menuItem.setHighlighted = function(self, var)
			border.visible = var
			menuItem.cascadeOpacity = not var
		end

		menuItem.selected = false
		menuItem.select = function(self, var)
			menuItem.selected = var
			menuItem:setHighlighted(var)
			if var then
				if enableFunc then
					enableFunc(menuItem)
				end
			else
				if disableFunc then
					disableFunc(menuItem)
				end
			end
		end
		
		menuItem:registerTapHandler(
			function(eventType,self)
				if eventType == CCMenuItem.TapBegan then
				elseif eventType == CCMenuItem.TapEnded then
				elseif eventType == CCMenuItem.Tapped then
					if enableFunc ~= nil and disableFunc ~= nil then
						oEvent:send("SettingSelected",menuItem)
					end
				end
			end)
		
		menuItem.setEnabled = function(self,enabled)
			menuItem.enabled = enabled
			if not enabled then menuItem:select(false) end
		end
	
		menuItem.getEnabled = function(self)
			return menuItem.enabled
		end
		
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
		self:stopAllActions()
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
			if touch.id ~= 0 or oEditor.isPlaying then
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
	
	local posItem = nil
	local posNextItem = nil
	local posXY = false
	
	local scaleItem = nil
	local scaleNextItem = nil
	local scaleXY = false
	
	local skewItem = nil
	local skewNextItem = nil
	local skewXY = false

	local skipSelection = false
	local keyItems =
	{
		Name = oSettingItem("Name :",0,getPosY()),
		Time = oSettingItem("Time :",0,getPosY()),--1
		PosX = oSettingItem("PosX :",0,getPosY(),
			function(item)
				if posItem and posItem ~= item then
					if posXY then
						oEditor.viewArea:stopEditPosXY()
						posXY = false
						posItem:setHighlighted(false)
						return
					else
						oEditor.viewArea:stopEditPosY()
						posXY = true
						posItem:setHighlighted(true)
					end
					posNextItem = posItem
				end
				posItem = item
				if posXY then
					oEditor.viewArea:editPosXY()
				else
					oEditor.viewArea:editPosX()
				end
			end,
			function(item)
				if posItem == item then
					if posXY then
						posNextItem:setHighlighted(false)
						oEditor.viewArea:stopEditPosXY()
						posXY = false
						posItem = nil
						skipSelection = true
					else
						oEditor.viewArea:stopEditPosX()
					end
				end
			end),--2
		PosY = oSettingItem("PosY :",0,getPosY(),
			function(item)
				if posItem and posItem ~= item then
					if posXY then
						oEditor.viewArea:stopEditPosXY()
						posXY = false
						posItem:setHighlighted(false)
						return
					else
						oEditor.viewArea:stopEditPosX()
						posXY = true
						posItem:setHighlighted(true)
					end
					posNextItem = posItem
				end
				posItem = item
				if posXY then
					oEditor.viewArea:editPosXY()
				else
					oEditor.viewArea:editPosY()
				end
			end,
			function(item)
				if posItem == item then
					if posXY then
						posNextItem:setHighlighted(false)
						oEditor.viewArea:stopEditPosXY()
						posXY = false
						posItem = nil
						skipSelection = true
					else
						oEditor.viewArea:stopEditPosY()
					end
				end
			end),--3
		ScaleX = oSettingItem("ScaleX :",0,getPosY(),
			function(item)
				if scaleItem and scaleItem ~= item then
					if scaleXY then
						oEditor.viewArea:stopEditScaleXY()
						scaleXY = false
						scaleItem:setHighlighted(false)
						return
					else
						oEditor.viewArea:stopEditScaleY()
						scaleXY = true
						scaleItem:setHighlighted(true)
					end
					scaleNextItem = scaleItem
				end
				scaleItem = item
				if scaleXY then
					oEditor.viewArea:editScaleXY()
				else
					oEditor.viewArea:editScaleX()
				end
			end,
			function(item)
				if scaleItem == item then
					if scaleXY then
						scaleNextItem:setHighlighted(false)
						oEditor.viewArea:stopEditScaleXY()
						scaleXY = false
						scaleItem = nil
						skipSelection = true
					else
						oEditor.viewArea:stopEditScaleX()
					end
				end
			end),--4
		ScaleY = oSettingItem("ScaleY :",0,getPosY(),
			function(item)
				if scaleItem and scaleItem ~= item then
					if scaleXY then
						oEditor.viewArea:stopEditScaleXY()
						scaleXY = false
						scaleItem:setHighlighted(false)
						return
					else
						oEditor.viewArea:stopEditScaleX()
						scaleXY = true
						scaleItem:setHighlighted(true)
					end
					scaleNextItem = scaleItem
				end
				scaleItem = item
				if scaleXY then
					oEditor.viewArea:editScaleXY()
				else
					oEditor.viewArea:editScaleY()
				end
			end,
			function(item)
				if scaleItem == item then
					if scaleXY then
						scaleNextItem:setHighlighted(false)
						oEditor.viewArea:stopEditScaleXY()
						scaleXY = false
						scaleItem = nil
						skipSelection = true
					else
						oEditor.viewArea:stopEditScaleY()
					end
				end
			end),--5
		Rotation = oSettingItem("Rotation :",0,getPosY(),--6
			function()
				oEditor.viewArea:editRot()
			end,
			function()
				oEditor.viewArea:stopEditRot()
			end),
		Opacity = oSettingItem("Opacity :",0,getPosY(),
			function()
				oEditor.viewArea:editOpacity()
			end,
			function()
				oEditor.viewArea:stopEditOpacity()
			end),--7
		SkewX = oSettingItem("SkewX :",0,getPosY(),
			function(item)
				if skewItem and skewItem ~= item then
					if skewXY then
						oEditor.viewArea:stopEditSkewXY()
						skewXY = false
						skewItem:setHighlighted(false)
						return
					else
						oEditor.viewArea:stopEditSkewY()
						skewXY = true
						skewItem:setHighlighted(true)
					end
					skewNextItem = skewItem
				end
				skewItem = item
				if skewXY then
					oEditor.viewArea:editSkewXY()
				else
					oEditor.viewArea:editSkewX()
				end
			end,
			function(item)
				if skewItem == item then
					if skewXY then
						skewNextItem:setHighlighted(false)
						oEditor.viewArea:stopEditSkewXY()
						skewXY = false
						skewItem = nil
						skipSelection = true
					else
						oEditor.viewArea:stopEditSkewX()
					end
				end
			end),--8
		SkewY = oSettingItem("SkewY :",0,getPosY(),
			function(item)
				if skewItem and skewItem ~= item then
					if skewXY then
						oEditor.viewArea:stopEditSkewXY()
						skewXY = false
						skewItem:setHighlighted(false)
						return
					else
						oEditor.viewArea:stopEditSkewX()
						skewXY = true
						skewItem:setHighlighted(true)
					end
					skewNextItem = skewItem
				end
				skewItem = item
				if skewXY then
					oEditor.viewArea:editSkewXY()
				else
					oEditor.viewArea:editSkewY()
				end
			end,
			function(item)
				if skewItem == item then
					if skewXY then
						skewNextItem:setHighlighted(false)
						oEditor.viewArea:stopEditSkewXY()
						skewXY = false
						skewItem = nil
						skipSelection = true
					else
						oEditor.viewArea:stopEditSkewY()
					end
				end
			end),--9
		Visible = oSettingItem("visible :",0,getPosY(),
			function()
				oEditor.viewArea:editVisible()
			end,
			function()
				oEditor.viewArea:stopEditVisible()
			end),--10
		EaseP = oSettingItem("EaseP :",0,getPosY(),
			function(item)
				oEditor.viewArea:editEase(oKd.easePos,item)
			end,
			function()
				oEditor.viewArea:stopEditEase()
			end),--11
		EaseS = oSettingItem("EaseS :",0,getPosY(),
			function(item)
				oEditor.viewArea:editEase(oKd.easeScale,item)
			end,
			function()
				oEditor.viewArea:stopEditEase()
			end),--12
		EaseK = oSettingItem("EaseK :",0,getPosY(),
			function(item)
				oEditor.viewArea:editEase(oKd.easeSkew,item)
			end,
			function()
				oEditor.viewArea:stopEditEase()
			end),--13
		EaseR = oSettingItem("EaseR :",0,getPosY(),
			function(item)
				oEditor.viewArea:editEase(oKd.easeRotation,item)
			end,
			function()
				oEditor.viewArea:stopEditEase()
			end),--14
		EaseO = oSettingItem("EaseO :",0,getPosY(),
			function(item)
				oEditor.viewArea:editEase(oKd.easeOpacity,item)
			end,
			function()
				oEditor.viewArea:stopEditEase()
			end),--15
	}
	panel.items = keyItems

	local keyCount = 0
	for _,item in pairs(keyItems) do
		menu:addChild(item)
		keyCount = keyCount + 1
	end

	panel.updateItems = function(self)
		initValues()
		viewHeight = 30*keyCount+20
		viewWidth = borderSize.width
		moveY = viewHeight-borderSize.height
		moveX = borderSize.width-viewWidth
	end
	
	panel.updateValues = function(self,index)
		if index == nil then
			for _,item in pairs(keyItems) do
				item:setValue(nil)
			end
			oEditor.keyIndex = nil
			oEditor.currentFramePos = nil
			return
		end
		
		local frame = oEditor.animationData[index]
		keyItems.Time:setValue(oEditor.currentFramePos/60)
		keyItems.PosX:setValue(frame[oKd.x])
		keyItems.PosY:setValue(frame[oKd.y])
		keyItems.ScaleX:setValue(frame[oKd.scaleX])
		keyItems.ScaleY:setValue(frame[oKd.scaleY])
		keyItems.Rotation:setValue(frame[oKd.rotation])
		keyItems.Opacity:setValue(frame[oKd.opacity])
		keyItems.SkewX:setValue(frame[oKd.skewX])
		keyItems.SkewY:setValue(frame[oKd.skewY])
		keyItems.Visible:setValue(frame[oKd.visible])
		keyItems.EaseP:setValue(oEditor.easeNames[frame[oKd.easePos]])
		keyItems.EaseS:setValue(oEditor.easeNames[frame[oKd.easeScale]])
		keyItems.EaseK:setValue(oEditor.easeNames[frame[oKd.easeSkew]])
		keyItems.EaseR:setValue(oEditor.easeNames[frame[oKd.easeRotation]])
		keyItems.EaseO:setValue(oEditor.easeNames[frame[oKd.easeOpacity]])
	end
	
	panel.posListener = oListener("ControlBarPos",
		function(pos)
			if not oEditor.animationData or not oEditor.sprite then
				for _,item in pairs(keyItems) do
					item:setEnabled(false)
				end
				oEvent:send("SettingSelected",nil)
				return
			end
			local total = 0
			local index = 1
			oEditor.currentFramePos = nil
			for i = 2, #oEditor.animationData do
				total = total + oEditor.animationData[i][oKd.duration]
				local curPos = math.floor(total*60+0.5)
				if pos >= curPos then
					index = i
					oEditor.currentFramePos = curPos
				end
			end

			local enable = oEditor.currentFramePos ~= nil and oEditor.currentFramePos == pos
			for _,item in pairs(keyItems) do
				item:setEnabled(enable)
			end
			if not enable then
				oEvent:send("SettingSelected",nil)
			end

			if oEditor.keyIndex and oEditor.keyIndex == index then
				oEditor.sprite.visible = oEditor.animationData[index][oKd.visible]
				return
			end
			panel:updateValues(index)
			oEditor.keyIndex = index
		end)

	panel:updateItems()

	local selectedItem = nil
	panel.listener = oListener("SettingSelected",
		function(menuItem)
			if selectedItem and selectedItem == menuItem then
				selectedItem:select(false)
				skipSelection = false
				selectedItem = nil
				if posItem and not posXY then
					posItem = nil
				end
				if scaleItem and not scaleXY then
					scaleItem = nil
				end
				if skewItem and not skewXY then
					skewItem = nil
				end
				return
			end
			if selectedItem then
				selectedItem:select(false)
			end
			if (selectedItem == keyItems.PosX or selectedItem == keyItems.PosY) and menuItem ~= keyItems.PosX and menuItem ~= keyItems.PosY then
				skipSelection = false
				posItem = nil
			end
			if (selectedItem == keyItems.ScaleX or selectedItem == keyItems.ScaleY) and menuItem ~= keyItems.ScaleX and menuItem ~= keyItems.ScaleY then
				skipSelection = false
				scaleItem = nil
			end
			if (selectedItem == keyItems.SkewX or selectedItem == keyItems.SkewY) and menuItem ~= keyItems.SkewX and menuItem ~= keyItems.SkewY then
				skipSelection = false
				skewItem = nil
			end
			if skipSelection then
				skipSelection = false
				selectedItem = nil
				return
			elseif menuItem then
				menuItem:select(true)
			end
			selectedItem = menuItem
		end)

	panel.clearSelection = function(self)
		for _,item in pairs(keyItems) do
			item:select(false)
		end
		oEvent:send("SettingSelected",nil)
	end
	
	panel.update = function(self)
		local model = oEditor.viewArea:getModel()
		oEditor.controlBar:setTime(model.time*model.duration)
	end
	
	return panel
end

return oSettingPanel