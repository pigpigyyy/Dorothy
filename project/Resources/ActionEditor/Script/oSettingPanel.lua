local require = using("ActionEditor.Script")
local CCDirector = require("CCDirector")
local CCSize = require("CCSize")
local oVec2 = require("oVec2")
local CCLayer = require("CCLayer")
local CCDrawNode = require("CCDrawNode")
local ccColor4 = require("ccColor4")
local oLine = require("oLine")
local CCClipNode = require("CCClipNode")
local CCMenu = require("CCMenu")
local CCRect = require("CCRect")
local oEase = require("oEase")
local CCMenuItem = require("CCMenuItem")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local oTextField = require("oTextField")
local emit = require("emit")
local CCSequence = require("CCSequence")
local oOpacity = require("oOpacity")
local oPos = require("oPos")

local function oSettingPanel()
	local oEditor = require("oEditor")
	local oSd = oEditor.oSd
	local oKd = oEditor.oKd
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
	local isHide = false
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
	panel.anchor = oVec2.zero
	panel.contentSize = borderSize
	panel.touchEnabled = true
	panel.position = oVec2(winSize.width-170,70)

	local background = CCDrawNode()
	background:drawPolygon(
	{
		oVec2.zero,
		oVec2(borderSize.width,0),
		oVec2(borderSize.width,borderSize.height),
		oVec2(0,borderSize.height)
	},ccColor4(0x88100000))
	background:addChild(
		oLine(
		{
			oVec2.zero,
			oVec2(borderSize.width,0),
			oVec2(borderSize.width,borderSize.height),
			oVec2(0,borderSize.height),
			oVec2.zero
		},ccColor4(0xffffafaf)))
	panel:addChild(background)

	local stencil = CCDrawNode()
	stencil:drawPolygon(
	{
		oVec2(0,0),
		oVec2(borderSize.width-2,0),
		oVec2(borderSize.width-2,borderSize.height-2),
		oVec2(0,borderSize.height-2)
	},ccColor4())
	stencil.position = oVec2(1,1)

	local view = CCClipNode(stencil)
	panel:addChild(view)

	local menu = CCMenu()
	menu.swallowTouches = true
	menu.touchPriority = CCMenu.DefaultHandlerPriority-1
	menu.contentSize = borderSize
	menu.anchor = oVec2(0,1)
	menu.positionY = borderSize.height
	menu.visible = false

	local contentRect = CCRect.zero
	local itemRect = CCRect.zero
	local function moveItems(delta)
		contentRect:set(0,0,borderSize.width,borderSize.height)
		menu:eachChild(function(child)
			child.position = child.position + delta
			local positionX, positionY, width, height = child.positionX, child.positionY, child.width, child.height
			itemRect:set(positionX, positionY - height, width, height)
			child.visible = contentRect:intersectsRect(itemRect)
		end)
	end

	local function updateReset(deltaTime)
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

		moveItems(oVec2(0, yVal and yVal or 0))

		if t == 1.0 then
			panel:unschedule()
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
		panel:schedule(updateReset)
	end

	local function setOffset(deltaPos, touching)
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

		moveItems(deltaPos)

		if not touching and (newPos.y < -padding*0.5 or newPos.y > moveY+padding*0.5 or newPos.x > padding*0.5 or newPos.x < moveX-padding*0.5) then
			startReset()
		end
	end
	view:addChild(menu)

	local function oSettingItem(name, x, y, enableFunc, disableFunc)
		local menuItem = CCMenuItem()
		menuItem.anchor = oVec2(0,1)
		menuItem.contentSize = CCSize(160,30)
		menuItem.position = oVec2(x, y)
		menuItem.enabled = false

		local label = CCLabelTTF(name,"Arial",14)
		label.color = ccColor3(0xffffff)
		label.position = oVec2(40,15)
		label.texture.antiAlias = false
		menuItem:addChild(label)

		local isInput = false
		if name == "Name :" or name == "Event :" then
			label = oTextField(108,7,14,8,
				function()
					emit("Action.SettingSelected",nil)
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

		menuItem:slot("Tapped",function()
			if not isInput then
				if enableFunc ~= nil and disableFunc ~= nil then
					emit("Action.SettingSelected",menuItem)
				end
			else
				if enableFunc ~= nil and disableFunc ~= nil then
					emit("Action.SettingSelected",menuItem)
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

	local function updateSpeed(deltaTime)
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
				panel:unschedule()
			end
		end
	end

	panel.touchPriority = CCMenu.DefaultHandlerPriority-2
	panel:slot("TouchBegan",function(touch)
		if touch.id ~= 0 or oEditor.isPlaying or not panel.visible then
			return false
		end
		if not CCRect(oVec2.zero, panel.contentSize):containsPoint(panel:convertToNodeSpace(touch.location)) then
			return false
		end

		deltaMoveLength = 0
		menu.enabled = true
		panel:schedule(updateSpeed)
		return true
	end)

	local function touchEnded()
		menu.enabled = true
		if isReseting() then
			startReset()
		else
			if _v ~= oVec2.zero and deltaMoveLength > 10 then
				panel:schedule(updatePos)
			end
		end
	end
	panel:slot("TouchEnded",touchEnded)
	panel:slot("TouchCancelled",touchEnded)

	panel:slot("TouchMoved",function(touch)
		deltaMoveLength = deltaMoveLength + touch.delta.length
		_s = _s + touch.delta
		if deltaMoveLength > 10 then
			menu.enabled = false
			setOffset(touch.delta, true)
		end
	end)

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
	local isEditingEvent = false

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
		Event = oSettingItem("Event :",0,getPosY(),
			function(item)
				item.label:attachWithIME()
				isEditingEvent = true
			end,
			function(item)
				if not isEditingEvent or not oEditor.spriteData then
					return
				end
				isEditingEvent = false
				item.label:detachWithIME()
				local text = item.label.text
				oEditor.animationData[oEditor.keyIndex][oKd.event] = text
				oEditor.dirty = true
				oEditor.editMenu:markEditButton(true)
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
			end),
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
			end),
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
			end),
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
			end),
		Angle = oSettingItem("Angle :",0,getPosY(),--6
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
			end),
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
			end),
		Visible = oSettingItem("Visible :",0,getPosY(),
			function()
				oEditor.viewArea:editVisible()
			end,
			function()
				oEditor.viewArea:stopEditVisible()
			end),
		Front = oSettingItem("Front :",0,getPosY(),
			function()
				oEditor.viewArea:editFront()
			end,
			function()
				oEditor.viewArea:stopEditFront()
			end),
		EaseP = oSettingItem("EaseP :",0,getPosY(),
			function(item)
				oEditor.viewArea:editEase(oKd.easePos,item)
			end,
			function()
				oEditor.viewArea:stopEditEase()
			end),
		EaseS = oSettingItem("EaseS :",0,getPosY(),
			function(item)
				oEditor.viewArea:editEase(oKd.easeScale,item)
			end,
			function()
				oEditor.viewArea:stopEditEase()
			end),
		EaseK = oSettingItem("EaseK :",0,getPosY(),
			function(item)
				oEditor.viewArea:editEase(oKd.easeSkew,item)
			end,
			function()
				oEditor.viewArea:stopEditEase()
			end),
		EaseA = oSettingItem("EaseA :",0,getPosY(),
			function(item)
				oEditor.viewArea:editEase(oKd.easeAngle,item)
			end,
			function()
				oEditor.viewArea:stopEditEase()
			end),
		EaseO = oSettingItem("EaseO :",0,getPosY(),
			function(item)
				oEditor.viewArea:editEase(oKd.easeOpacity,item)
			end,
			function()
				oEditor.viewArea:stopEditEase()
			end),
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
		KeyPoint = oSettingItem("Keys :",0,getPosY(),
			function()
				oEditor.vertexControl:show(oEditor.modelData[oSd.keys],function(vs)
					oEditor.modelData[oSd.keys] = vs
					oEditor.editMenu:markEditButton(true)
				end)
			end,
			function()
				oEditor.vertexControl:hide()
			end),
	}
	panel.items = keyItems
	local group = {}
	for _,item in pairs(keyItems) do
		table.insert(group,item)
	end
	local function hideItems()
		for i = 1,#group do
			group[i].positionX = -160
			group[i].visible = false
		end
	end

	keyItems.AnchorX.visible = false
	keyItems.AnchorY.visible = false
	keyItems.Width.visible = false
	keyItems.Height.visible = false
	keyItems.AnchorX.positionX = keyItems.EaseP.positionX
	keyItems.AnchorY.positionY = keyItems.EaseS.positionY
	keyItems.KeyPoint.visible = false
	keyItems.KeyPoint:setValue(". . .")

	local keyCount = 0
	for _,item in pairs(keyItems) do
		menu:addChild(item)
		keyCount = keyCount + 1
	end

	panel.setEditEnable = function(self,enable)
		for _,item in pairs(keyItems) do
			item:setEnabled(enable)
		end
		if not enable and oEditor.spriteData == oEditor.modelData then
			keyItems.Width:setEnabled(true)
			keyItems.Height:setEnabled(true)
			keyItems.KeyPoint:setEnabled(true)
		end
	end

	local spriteItems =
	{
		keyItems.Name,
		keyItems.AnchorX,
		keyItems.AnchorY,
		keyItems.PosX,
		keyItems.PosY,
		keyItems.ScaleX,
		keyItems.ScaleY,
		keyItems.Angle,
		keyItems.Opacity,
		keyItems.SkewX,
		keyItems.SkewY,
		keyItems.Front,
	}
	local function updateSpriteItems()
		initValues()
		hideItems()
		local posY = genPosY()
		for i = 1,#spriteItems do
			spriteItems[i].visible = true
			spriteItems[i].positionX = 0
			spriteItems[i].positionY = posY()
		end
		viewHeight = math.max(30*(#spriteItems)+20,borderSize.height)
		viewWidth = borderSize.width
		moveY = viewHeight-borderSize.height
		moveX = borderSize.width-viewWidth
		setOffset(oVec2.zero)
	end

	local animationItems =
	{
		keyItems.Time,
		keyItems.PosX,
		keyItems.PosY,
		keyItems.ScaleX,
		keyItems.ScaleY,
		keyItems.Angle,
		keyItems.Opacity,
		keyItems.SkewX,
		keyItems.SkewY,
		keyItems.Visible,
		keyItems.EaseP,
		keyItems.EaseS,
		keyItems.EaseK,
		keyItems.EaseA,
		keyItems.EaseO,
		keyItems.Event,
	}
	local function updateAnimationItems()
		initValues()
		hideItems()
		local posY = genPosY()
		for i = 1,#animationItems do
			animationItems[i].visible = true
			animationItems[i].positionX = 0
			animationItems[i].positionY = posY()
		end
		viewHeight = math.max(30*(#animationItems)+20,borderSize.height)
		viewWidth = borderSize.width
		moveY = viewHeight-borderSize.height
		moveX = borderSize.width-viewWidth
		setOffset(oVec2.zero)
	end

	local rootItems =
	{
		keyItems.Width,
		keyItems.Height,
		keyItems.KeyPoint,
	}
	local function updateRootItems()
		initValues()
		hideItems()
		local posY = genPosY()
		for i = 1,#rootItems do
			rootItems[i].visible = true
			rootItems[i].positionX = 0
			rootItems[i].positionY = posY()
		end
		viewHeight = borderSize.height
		viewWidth = borderSize.width
		moveY = 0
		moveX = 0
	end

	local isShowingRoot = false
	panel:gslot("Action.ImageSelected",
		function(args)
			if oEditor.state == oEditor.EDIT_SPRITE or oEditor.state == oEditor.EDIT_ANIMATION then
				if args then
					local sp = args[1]
					if sp[oSd.parent] then
						if isShowingRoot then
							isShowingRoot = false
							if oEditor.state == oEditor.EDIT_ANIMATION then
								updateAnimationItems()
							else
								updateSpriteItems()
							end
						end
					else
						if not isShowingRoot then
							isShowingRoot = true
							updateRootItems()
						end
						keyItems.Width:setValue(sp[oSd.size].width)
						keyItems.Height:setValue(sp[oSd.size].height)
						keyItems.KeyPoint:setValue(". . .")
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
			if not isHide then
				panel.positionX = winSize.width-170
			end
			panel.positionY = 70
			local borderH = 200*(winSize.height-90)/510
			background.scaleY = 1
			stencil.scaleY = 1
			borderSize.height = borderH
			panel.contentSize = borderSize
			menu.contentSize = borderSize
			menu.positionY = borderSize.height
			updateAnimationItems()
		else
			if not isHide then
				panel.positionX = winSize.width-170
			end
			panel.positionY = 10
			local borderH = 200*(winSize.height-90)/510
			local scale = (borderH+60)/borderH
			background.scaleY = scale
			stencil.scaleY = scale
			borderSize.height = borderH+60
			panel.contentSize = borderSize
			menu.contentSize = borderSize
			menu.positionY = borderSize.height
			updateSpriteItems()
		end
		panel:runAction(
			CCSequence
			{
				oOpacity(0.15,0.8),
				oOpacity(0.15,1)
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
		keyItems.Angle:setValue(frame[oKd.angle])
		keyItems.Opacity:setValue(frame[oKd.opacity])
		keyItems.SkewX:setValue(frame[oKd.skewX])
		keyItems.SkewY:setValue(frame[oKd.skewY])
		keyItems.Visible:setValue(frame[oKd.visible])
		keyItems.EaseP:setValue(oEditor.easeNames[frame[oKd.easePos]])
		keyItems.EaseS:setValue(oEditor.easeNames[frame[oKd.easeScale]])
		keyItems.EaseK:setValue(oEditor.easeNames[frame[oKd.easeSkew]])
		keyItems.EaseA:setValue(oEditor.easeNames[frame[oKd.easeAngle]])
		keyItems.EaseO:setValue(oEditor.easeNames[frame[oKd.easeOpacity]])
		keyItems.Event:setValue(frame[oKd.event])
	end

	panel:gslot("Action.ControlBarPos",
		function(pos)
			if not oEditor.animationData or not oEditor.sprite then
				for name,item in pairs(keyItems) do
					if name ~= "KeyPoint" and  name ~= "Width" and name ~= "Height" then
						item:setEnabled(false)
					end
				end
				emit("Action.SettingSelected",nil)
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
				emit("Action.SettingSelected",nil)
			end

			if oEditor.keyIndex and oEditor.keyIndex == index then
				oEditor.sprite.visible = oEditor.animationData[index][oKd.visible]
				return
			end
			panel:updateValues(index)
			oEditor.keyIndex = index
		end)

	local selectedItem = nil
	panel:gslot("Action.SettingSelected",
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
		emit("Action.SettingSelected",nil)
		for _,item in pairs(keyItems) do
			item:select(false)
		end
	end

	panel.resetItems = function(self)
		isShowingRoot = false
		panel:clearSelection()
		updateSpriteItems()
	end

	panel.update = function(self)
		if oEditor.state == oEditor.EDIT_ANIMATION then
			if oEditor.spriteData then
				local sp = oEditor.spriteData
				if sp[oSd.parent] then
					oEditor.controlBar:setTime(oEditor.controlBar:getTime())
				else
					keyItems.Width:setValue(sp[oSd.size].width)
					keyItems.Height:setValue(sp[oSd.size].height)
					keyItems.KeyPoint:setValue(". . .")
				end
			end
		else
			local sp
			if oEditor.spriteData then
				sp = oEditor.spriteData
			else
				sp = {}
			end
			-- editing root name is not allowed
			if sp ~= oEditor.modelData then
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
			keyItems.Angle:setValue(sp[oSd.angle])
			keyItems.Opacity:setValue(sp[oSd.opacity])
			keyItems.SkewX:setValue(sp[oSd.skewX])
			keyItems.SkewY:setValue(sp[oSd.skewY])
			keyItems.Front:setValue(sp[oSd.front])
		end
	end

	panel:gslot("Action.hideEditor",function(args)
		local hide,instant = unpack(args)
		if isHide == hide then
			return
		end
		isHide = hide
		local winWidth = CCDirector.winSize.width
		if instant then
			panel.positionX = winWidth*2-panel.positionX
		else
			panel:perform(oPos(0.5,winWidth*2-panel.positionX,panel.positionY,oEase.OutQuad))
		end
	end)

	return panel
end

return oSettingPanel
