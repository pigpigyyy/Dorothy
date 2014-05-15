local oTextField = require("Script/oTextField")

local function oSettingPanel()
	local winSize = CCDirector.winSize
	local borderSize = CCSize(160,200*(winSize.height-90)/510)
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
	panel.opacity = 0.4
	panel.touchEnabled = true
	panel.position = oVec2(winSize.width-170,70)

	local border = CCDrawNode()
	border:drawPolygon(
	{
		oVec2.zero,
		oVec2(borderSize.width,0),
		oVec2(borderSize.width,borderSize.height),
		oVec2(0,borderSize.height)
	},ccColor4(0x88000000))
	border:addChild(
		oLine(
		{
			oVec2.zero,
			oVec2(borderSize.width,0),
			oVec2(borderSize.width,borderSize.height),
			oVec2(0,borderSize.height),
			oVec2.zero
		},ccColor4()))
	panel:addChild(border)

	local stencil = CCDrawNode()
	stencil:drawPolygon(
	{
		oVec2(0,0),
		oVec2(borderSize.width-2,0),
		oVec2(borderSize.width-2,borderSize.height-2),
		oVec2(0,borderSize.height-2)
	},ccColor4(0xffffffff))
	stencil.position = oVec2(1,1)

	local view = CCClipNode(stencil)
	panel:addChild(view)

	local menu = CCMenu(false)
	menu.contentSize = borderSize
	menu.anchorPoint = oVec2(0,1)
	menu.positionY = borderSize.height
	menu.visible = false

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
			local node = children:get(i)
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
			local node = children:get(i)
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

		local isInput = false
		if name == "Name :" then
			label = oTextField(108,7,14,8,
				function(item)
					oEvent:send("SettingSelected",nil)
				end)
			isInput = true
		else
			label = CCLabelTTF("","Arial",14)
			label.position = oVec2(120,15)
		end
		label.color = ccColor3(0xffffff)
		menuItem:addChild(label)
		menuItem.label = label

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
			if value ~= nil and value ~= "" then
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
				if eventType == CCMenuItem.Tapped then
					if not isInput then
						if enableFunc ~= nil and disableFunc ~= nil then
							oEvent:send("SettingSelected",menuItem)
						end
					else
						if oEditor.state == oEditor.EDIT_SPRITE and enableFunc ~= nil and disableFunc ~= nil then
							oEvent:send("SettingSelected",menuItem)
						end
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

	local opacity = oOpacity(0.5,0.4,oEase.InExpo)
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
			if touch.id ~= 0 or oEditor.isPlaying or not panel.visible then
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
	
	local function genPosY()
		local index = 0
		return function()
			local v = index
			index = index + 1
			return borderSize.height-10-30*v
		end
	end
	local getPosY = genPosY()
	
	local posItem = nil
	local posNextItem = nil
	local posXY = false
	
	local scaleItem = nil
	local scaleNextItem = nil
	local scaleXY = false
	
	local skewItem = nil
	local skewNextItem = nil
	local skewXY = false
	
	local anchorItem = nil
	local anchorNextItem = nil
	local anchorXY = false
	
	local sizeItem = nil
	local sizeNextItem = nil
	local sizeXY = false
	
	local isEditingName = false

	local skipSelection = false
	local keyItems =
	{
		Name = oSettingItem("Name :",0,getPosY(),
			function(item)
				item.label:attachWithIME()
				isEditingName = true
			end,
			function(item)
				if not isEditingName or not oEditor.spriteData then
					return
				end
				isEditingName = false
				item.label:detachWithIME()
				local text = item.label.text
				if text ~= oEditor.spriteData[oSd.name] then
					oEditor.spriteData[oSd.name] = text
					oEditor.viewPanel:updateItemName(oEditor.spriteData)
					oEditor.dirty = true
					oEditor.editMenu:markEditButton(true)
				end
			end),
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
		Visible = oSettingItem("Visible :",0,getPosY(),
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
		AnchorX = oSettingItem("AnchorX :",0,0,
			function(item)
				if anchorItem and anchorItem ~= item then
					if anchorXY then
						oEditor.viewArea:stopEditAnchorXY()
						anchorXY = false
						anchorItem:setHighlighted(false)
						return
					else
						oEditor.viewArea:stopEditAnchorY()
						anchorXY = true
						anchorItem:setHighlighted(true)
					end
					anchorNextItem = anchorItem
				end
				anchorItem = item
				if anchorXY then
					oEditor.viewArea:editAnchorXY()
				else
					oEditor.viewArea:editAnchorX()
				end
			end,
			function(item)
				if anchorItem == item then
					if anchorXY then
						anchorNextItem:setHighlighted(false)
						oEditor.viewArea:stopEditAnchorXY()
						anchorXY = false
						anchorItem = nil
						skipSelection = true
					else
						oEditor.viewArea:stopEditAnchorX()
					end
				end
			end),
		AnchorY = oSettingItem("AnchorY :",0,0,
			function(item)
				if anchorItem and anchorItem ~= item then
					if anchorXY then
						oEditor.viewArea:stopEditAnchorXY()
						anchorXY = false
						anchorItem:setHighlighted(false)
						return
					else
						oEditor.viewArea:stopEditAnchorX()
						anchorXY = true
						anchorItem:setHighlighted(true)
					end
					anchorNextItem = anchorItem
				end
				anchorItem = item
				if anchorXY then
					oEditor.viewArea:editAnchorXY()
				else
					oEditor.viewArea:editAnchorY()
				end
			end,
			function(item)
				if anchorItem == item then
					if anchorXY then
						anchorNextItem:setHighlighted(false)
						oEditor.viewArea:stopEditAnchorXY()
						anchorXY = false
						anchorItem = nil
						skipSelection = true
					else
						oEditor.viewArea:stopEditAnchorY()
					end
				end
			end),
		Width = oSettingItem("Width :",0,0,
			function(item)
				if sizeItem and sizeItem ~= item then
					if sizeXY then
						oEditor.viewArea:stopEditSizeXY()
						sizeXY = false
						sizeItem:setHighlighted(false)
						return
					else
						oEditor.viewArea:stopEditSizeY()
						sizeXY = true
						sizeItem:setHighlighted(true)
					end
					sizeNextItem = sizeItem
				end
				sizeItem = item
				if sizeXY then
					oEditor.viewArea:editSizeXY()
				else
					oEditor.viewArea:editSizeX()
				end
			end,
			function(item)
				if sizeItem == item then
					if sizeXY then
						sizeNextItem:setHighlighted(false)
						oEditor.viewArea:stopEditSizeXY()
						sizeXY = false
						sizeItem = nil
						skipSelection = true
					else
						oEditor.viewArea:stopEditSizeX()
					end
				end
			end),
		Height = oSettingItem("Height :",0,0,
			function(item)
				if sizeItem and sizeItem ~= item then
					if sizeXY then
						oEditor.viewArea:stopEditSizeXY()
						sizeXY = false
						sizeItem:setHighlighted(false)
						return
					else
						oEditor.viewArea:stopEditSizeX()
						sizeXY = true
						sizeItem:setHighlighted(true)
					end
					sizeNextItem = sizeItem
				end
				sizeItem = item
				if sizeXY then
					oEditor.viewArea:editSizeXY()
				else
					oEditor.viewArea:editSizeY()
				end
			end,
			function(item)
				if sizeItem == item then
					if sizeXY then
						sizeNextItem:setHighlighted(false)
						oEditor.viewArea:stopEditSizeXY()
						sizeXY = false
						sizeItem = nil
						skipSelection = true
					else
						oEditor.viewArea:stopEditSizeY()
					end
				end
			end),
	}
	panel.items = keyItems
	local group = {}
	for _,item in pairs(keyItems) do
		table.insert(group,item)
	end
	local function hideItems()
		for i = 1,#group do
			group[i].visible = false
		end
	end

	keyItems.AnchorX.visible = false
	keyItems.AnchorY.visible = false
	keyItems.Width.visible = false
	keyItems.Height.visible = false
	keyItems.AnchorX.positionX = keyItems.EaseP.positionX
	keyItems.AnchorY.positionY = keyItems.EaseS.positionY

	local keyCount = 0
	for _,item in pairs(keyItems) do
		menu:addChild(item)
		keyCount = keyCount + 1
	end

	panel.setEditEnable = function(self,enable)
		for _,item in pairs(keyItems) do
			item:setEnabled(enable)
		end
		if not enable and oEditor.spriteData == oEditor.data then
			keyItems.Width:setEnabled(true)
			keyItems.Height:setEnabled(true)
		end
	end
	
	local function updateSpriteItems()
		initValues()
		hideItems()
		local items =
		{
			keyItems.Name,
			keyItems.AnchorX,
			keyItems.AnchorY,
			keyItems.PosX,
			keyItems.PosY,
			keyItems.ScaleX,
			keyItems.ScaleY,
			keyItems.Rotation,
			keyItems.Opacity,
			keyItems.SkewX,
			keyItems.SkewY
		}
		local posY = genPosY()
		for i = 1,#items do
			items[i].visible = true
			items[i].positionY = posY()
		end
		viewHeight = 30*(#items)+20
		viewWidth = borderSize.width
		moveY = viewHeight-borderSize.height
		moveX = borderSize.width-viewWidth
	end

	local isShowingRoot = false
	panel.selectListener = oListener("ImageSelected",
		function(args)
			if oEditor.state ~= oEditor.EDIT_LOOK and args then
				local sp = args[1]
				if sp[oSd.parent] then
					oEditor.editMenu.items.Size.visible = false
				else
					if oEditor.editMenu.items.Size.visible then
						oEditor.editMenu.items.Size.visible = false
					else
						oEditor.editMenu.items.Size.visible = true
					end
				end
			end
			if oEditor.state == oEditor.EDIT_SPRITE then
				if args then
					local sp = args[1]
					if sp[oSd.parent] and isShowingRoot then
						isShowingRoot = false
						updateSpriteItems()
					end
					if not sp[oSd.parent] then
						if not isShowingRoot then
							isShowingRoot = true
							initValues()
							hideItems()
							local items =
							{
								keyItems.Width,
								keyItems.Height,
							}
							local posY = genPosY()
							for i = 1,#items do
								items[i].visible = true
								items[i].positionY = posY()
							end
							viewHeight = borderSize.height
							viewWidth = borderSize.width
							moveY = 0
							moveX = 0
						end
						keyItems.Width:setValue(sp[oSd.size].width)
						keyItems.Height:setValue(sp[oSd.size].height)
					end
				end
			end
		end)
	
	panel.updateItems = function(self)
		isShowingRoot = false
		if oEditor.state ~= oEditor.EDIT_START then
			menu.visible = true
		end
		if oEditor.state == oEditor.EDIT_ANIMATION then
			panel.position = oVec2(winSize.width-170,70)
			local borderH = 200*(winSize.height-90)/510
			border.scaleY = 1
			stencil.scaleY = 1
			borderSize.height = borderH
			panel.contentSize = borderSize
			menu.contentSize = borderSize
			menu.positionY = borderSize.height
			initValues()
			hideItems()
			local items = 
			{
				keyItems.Time,
				keyItems.PosX,
				keyItems.PosY,
				keyItems.ScaleX,
				keyItems.ScaleY,
				keyItems.Rotation,
				keyItems.Opacity,
				keyItems.SkewX,
				keyItems.SkewY,
				keyItems.Visible,
				keyItems.EaseP,
				keyItems.EaseS,
				keyItems.EaseK,
				keyItems.EaseR,
				keyItems.EaseO
			}
			local posY = genPosY()
			for i = 1,#items do
				items[i].visible = true
				items[i].positionY = posY()
			end
			viewHeight = 30*(#items)+20
			viewWidth = borderSize.width
			moveY = viewHeight-borderSize.height
			moveX = borderSize.width-viewWidth
		else
			panel.position = oVec2(winSize.width-170,10)
			local borderH = 200*(winSize.height-90)/510
			local scale = (borderH+60)/borderH
			border.scaleY = scale
			stencil.scaleY = scale
			borderSize.height = borderH+60
			panel.contentSize = borderSize
			menu.contentSize = borderSize
			menu.positionY = borderSize.height
			updateSpriteItems()
		end
		panel:stopAllActions()
		panel:runAction(
			CCSequence
			{
				oOpacity(0.15,0.2),
				oOpacity(0.15,0.4)
			})
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
			panel:setEditEnable(enable)
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
				if anchorItem and not anchorXY then
					anchorItem = nil
				end
				if sizeItem and not sizeXY then
					sizeItem = nil
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
			if (selectedItem == keyItems.AnchorX or selectedItem == keyItems.AnchorY) and menuItem ~= keyItems.AnchorX and menuItem ~= keyItems.AnchorY then
				skipSelection = false
				anchorItem = nil
			end
			if (selectedItem == keyItems.Width or selectedItem == keyItems.Height) and menuItem ~= keyItems.Width and menuItem ~= keyItems.Height then
				skipSelection = false
				sizeItem = nil
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
		oEvent:send("SettingSelected",nil)
		for _,item in pairs(keyItems) do
			item:select(false)
		end
	end
	
	panel.update = function(self)
		if oEditor.state == oEditor.EDIT_ANIMATION then
			local model = oEditor.viewArea:getModel()
			oEditor.controlBar:setTime(oEditor.controlBar:getTime())
		else
			local sp = nil
			if oEditor.spriteData then
				sp = oEditor.spriteData
			else
				sp = {}
			end
			-- editing root name is not allowed
			if sp ~= oEditor.data then
				keyItems.Name:setValue(sp[oSd.name])
			else
				keyItems.Name:setValue("Root")
			end
			keyItems.AnchorX:setValue(sp[oSd.anchorX])
			keyItems.AnchorY:setValue(sp[oSd.anchorY])
			keyItems.PosX:setValue(sp[oSd.x])
			keyItems.PosY:setValue(sp[oSd.y])
			keyItems.ScaleX:setValue(sp[oSd.scaleX])
			keyItems.ScaleY:setValue(sp[oSd.scaleY])
			keyItems.Rotation:setValue(sp[oSd.rotation])
			keyItems.Opacity:setValue(sp[oSd.opacity])
			keyItems.SkewX:setValue(sp[oSd.skewX])
			keyItems.SkewY:setValue(sp[oSd.skewY])
		end
	end
	
	return panel
end

return oSettingPanel