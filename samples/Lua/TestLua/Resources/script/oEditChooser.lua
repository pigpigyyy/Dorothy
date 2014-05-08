local oButton = require("Script/oButton")
local oSelectionPanel = require("Script/oSelectionPanel")
local oFileChooser = require("Script/oFileChooser")
local oTextField = require("Script/oTextField")

local function oInputBox(text,textEntered)
	local w = CCDirector.winSize.width*0.5
	local h = CCDirector.winSize.height*0.5
	local size = 125
	local box = CCNode()

	local mask = CCLayer()
	mask.anchorPoint = oVec2.zero
	mask.touchEnabled = true
	mask:registerTouchHandler(function()return true end,false,CCMenu.DefaultHandlerPriority-4,true)
	box:addChild(mask)

	local border = CCDrawNode()
	border:drawPolygon(
	{
		oVec2(-size,-size),
		oVec2(size,-size),
		oVec2(size,size),
		oVec2(-size,size)
	},ccColor4(0xe5100000),0.5,ccColor4(0x88ffafaf))
	border.position = oVec2(w,h)
	box:addChild(border)
	local frame = CCDrawNode()
	frame:drawPolygon(
	{
		oVec2(-85,-18),
		oVec2(85,-18),
		oVec2(85,18),
		oVec2(-85,18)
	},ccColor4(0),0.5,ccColor4(0xff00ffff))
	border:addChild(frame)

	local title = CCLabelTTF(text,"Arial",24)
	title.texture.antiAlias = false
	title.position = oVec2(0,76)
	title.color = ccColor3(0x00ffff)
	border:addChild(title)

	local menu = CCMenu()
	menu.contentSize = CCSize(120,50)
	menu.touchPriority = CCMenu.DefaultHandlerPriority-5
	border:addChild(menu)

	local textField = oTextField(120,18,17,10,
		function(self)
			frame.opacity = 0.3
			self.opacity = 0.3
		end)
	--textField=CCTextFieldTTF
	textField.position = oVec2(0,-9)
	textField:attachWithIME()
	border:addChild(textField)

	local menuItem = CCMenuItem()
	menuItem.contentSize = CCSize(120,50)
	menuItem.anchorPoint = oVec2.zero
	menuItem:registerTapHandler(
		function(eventType)
			if eventType == CCMenuItem.Tapped then
				textField:attachWithIME()
				textField.opacity = 1
				frame.opacity = 1
			end
		end)
	menu:addChild(menuItem)
	
	box.show = function(self)
		border.scaleX = 0
		border.scaleY = 0
		border.opacity = 0
		border:runAction(
			CCSequence(
			{
				CCSpawn(
				{
					oOpacity(0.3,1),
					oScale(0.3,1,1,oEase.OutBack)
				}),
				CCCall(
					function()
						local opMenu = CCMenu()
						opMenu.contentSize = CCSize(130,60)
						opMenu.touchPriority = CCMenu.DefaultHandlerPriority-6
						opMenu.position = oVec2(w,h-76)
						box:addChild(opMenu)

						local okButton = oButton("OK",17,60,false,
							0,0,
							function(item)
								textField:detachWithIME()
								opMenu:removeHandlers()
								box:hide()
								if textEntered then
									textEntered(textField.text)
								end
							end)
						okButton.anchorPoint = oVec2.zero
						local btnBk = CCDrawNode()
						btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
						btnBk.position = oVec2(30,30)
						okButton:addChild(btnBk,-1)
						opMenu:addChild(okButton)

						local cancelButton = oButton("Cancel",17,60,false,
							70,0,
							function(item)
								opMenu:removeHandlers()
								box:hide()
							end)
						cancelButton.anchorPoint = oVec2.zero
						btnBk = CCDrawNode()
						btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
						btnBk.position = oVec2(30,30)
						cancelButton:addChild(btnBk,-1)
						opMenu:addChild(cancelButton)
						opMenu.removeHandlers = function(self)
							okButton:unregisterTapHandler()
							cancelButton:unregisterTapHandler()
							textField:unregisterInputHandler()
							opMenu.enabled = false
							menu.enabled = false
						end
					end)
			}))
	end

	box.hide = function(self)
		border:runAction(
			CCSequence(
			{
				CCSpawn(
				{
					oScale(0.3,0,0,oEase.InBack),
					oOpacity(0.3,0)
				}),
				CCCall(
					function()
						box.parent:removeChild(box)
					end)
			}))
	end

	return box
end

local function oEditChooser(withCancel)
	local winSize = CCDirector.winSize
	local itemWidth = 120
	local itemNum = 5
	local borderSize = CCSize((itemWidth+10)*itemNum+10,400)
	local panel = oSelectionPanel(borderSize)
	local menu = panel.menu
	local border = panel.border
	local halfBW = borderSize.width*0.5
	local halfBH = borderSize.height*0.5
	local background= CCDrawNode()
	background:drawPolygon(
	{
		oVec2(-halfBW,-halfBH),
		oVec2(halfBW,-halfBH),
		oVec2(halfBW,halfBH),
		oVec2(-halfBW,halfBH)
	},ccColor4(0xe5100000),0.5,ccColor4(0x88ffafaf))
	border:addChild(background,-1)

	local opMenu = CCMenu()
	opMenu.contentSize = CCSize(60,60)
	opMenu.touchPriority = CCMenu.DefaultHandlerPriority-3
	opMenu.position = oVec2(winSize.width*0.5+borderSize.width*0.5,winSize.height*0.5+borderSize.height*0.5)
	panel:addChild(opMenu)

	local cancelButton = oButton("Cancel",17,60,false,
		0,0,
		function(item)
			item:unregisterTapHandler()
			opMenu.enabled = false
			panel:hide()
		end)
	cancelButton.anchorPoint = oVec2.zero
	local btnBk = CCDrawNode()
	btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
	btnBk.position = oVec2(30,30)
	cancelButton:addChild(btnBk,-1)
	cancelButton.visible = withCancel
	opMenu:addChild(cancelButton)

	panel.sprites = {}
	panel.init = function(self)
		local xStart = winSize.width*0.5-halfBW -- left
		local yStart = winSize.height*0.5+halfBH -- top

		local title = CCLabelTTF("Animation","Arial",24)
		title.texture.antiAlias = false
		title.color = ccColor3(0x00ffff)
		title.anchorPoint = oVec2(0,1)
		local y = yStart-20
		title.position = oVec2(xStart+20,y)
		menu:addChild(title)
		title.opacity = 0
		title:runAction(oOpacity(0.3,0.5))
		yStart = y-title.contentSize.height
		
		local function addNewAnimation(sp,index)
			local aDefs = sp[oSd.animationDefs]
			for i = 1,index do
				if aDefs[i] == nil then
					aDefs[i] = false
				end
			end
			local children = sp[oSd.children]
			for i = 1,#children do
				addNewAnimation(children[i],index)
			end
		end
	
		local aNames = oEditor.data[oSd.animationNames]
		local i = 0
		for k,v in pairs(aNames) do
			local name = #k > 10 and k:sub(1,7).."..." or k
			y = yStart-45-math.floor(i/itemNum)*60
			local button = oButton(name,17,
				itemWidth,50,
				xStart+itemWidth*0.5+10+(i%itemNum)*(itemWidth+10),
				y,
				function(item)
					cancelButton:unregisterTapHandler()
					opMenu.enabled = false
					panel:hide()
					oEditor.animation = item.name
					oEditor.editMenu:toAnimation()
				end)
			button.name = k
			menu:addChild(button)
			button.opacity = 0
			button:runAction(
				CCSequence(
				{
					CCDelay((i%itemNum)*0.05),
					oOpacity(0.3,1)
				}))
			i = i+1
		end
		y = yStart-45-math.floor(i/itemNum)*60
		local newButton = oButton(
			"<NEW>",17,
			itemWidth,50,
			xStart+itemWidth*0.5+10+(i%itemNum)*(itemWidth+10),
			y,
			function(item)
				local box = oInputBox("New Animation",
					function(text)
						if text == "" then
							return
						end
						for k,_ in pairs(aNames) do
							if text == k then
								return
							end
						end
						local index = -1
						repeat
							local flag = true
							index = index+1
							for _,v in pairs(aNames) do
								if v == index then
									flag = false
								end
							end
						until flag
						cancelButton:unregisterTapHandler()
						aNames[text] = index
						addNewAnimation(oEditor.data,index+1)
						oEditor.dirty = true
						oEditor.viewArea:getModel()
						oEditor.editMenu:markEditButton(true)
						opMenu.enabled = false
						panel:hide()
						oEditor.animation = text
						oEditor.editMenu:toAnimation()
					end)
				box:show()
				oEditor.scene:addChild(box)
			end)
		newButton.color = ccColor3(0xffcc88)
		menu:addChild(newButton)
		newButton.opacity = 0
		newButton:runAction(
			CCSequence(
			{
				CCDelay((i%itemNum)*0.05),
				oOpacity(0.3,1)
			}))
		yStart = y-25

		title = CCLabelTTF("Look","Arial",24)
		title.texture.antiAlias = false
		title.color = ccColor3(0x00ffff)
		title.anchorPoint = oVec2(0,1)
		y = yStart-20
		title.position = oVec2(xStart+20,y)
		menu:addChild(title)
		title.opacity = 0
		title:runAction(oOpacity(0.3,0.5))
		yStart = y-title.contentSize.height

		local lNames = oEditor.data[oSd.lookNames]
		i = 0
		for k,v in pairs(lNames) do
			local name = #k > 10 and k:sub(1,7).."..." or k
			y = yStart-45-math.floor(i/itemNum)*60
			local button = oButton(name,17,
				itemWidth,50,
				xStart+itemWidth*0.5+10+(i%itemNum)*(itemWidth+10),
				y,
				function(item)
					cancelButton:unregisterTapHandler()
					opMenu.enabled = false
					panel:hide()
					oEditor.look = item.name
					local model = oEditor.viewArea:getModel()
					model.look = oEditor.look
					oEditor.editMenu:toLook()
				end)
			button.name = k
			menu:addChild(button)
			button.opacity = 0
			button:runAction(
				CCSequence(
				{
					CCDelay((i%itemNum)*0.05),
					oOpacity(0.3,1)
				}))
			i = i+1
		end
		y = yStart-45-math.floor(i/itemNum)*60
		newButton = oButton(
			"<NEW>",17,
			itemWidth,50,
			xStart+itemWidth*0.5+10+(i%itemNum)*(itemWidth+10),
			y,
			function(item)
			end)
		newButton.color = ccColor3(0xffcc88)
		menu:addChild(newButton)
		newButton.opacity = 0
		newButton:runAction(
			CCSequence(
			{
				CCDelay((i%itemNum)*0.05),
				oOpacity(0.3,1)
			}))
		yStart = y-25
	
		if oEditor.state ~= oEditor.EDIT_SPRITE then
			title = CCLabelTTF("Sprite","Arial",24)
			title.texture.antiAlias = false
			title.color = ccColor3(0x00ffff)
			title.anchorPoint = oVec2(0,1)
			y = yStart-20
			title.position = oVec2(xStart+20,y)
			menu:addChild(title)
			title.opacity = 0
			title:runAction(oOpacity(0.3,0.5))
			yStart = y-title.contentSize.height

			y = yStart-45
			newButton = oButton(
				"Edit Sprite",17,
				itemWidth,50,
				xStart+itemWidth*0.5+10,
				y,
				function(item)
					cancelButton:unregisterTapHandler()
					opMenu.enabled = false
					panel:hide()
					oEditor.editMenu:toSprite()
				end)
			newButton.color = ccColor3(0xffcc88)
			menu:addChild(newButton)
			newButton.opacity = 0
			newButton:runAction(
				CCSequence(
				{
					CCDelay((i%itemNum)*0.05),
					oOpacity(0.3,1)
				}))
			yStart = y-25
		end

		title = CCLabelTTF("Model","Arial",24)
		title.texture.antiAlias = false
		title.color = ccColor3(0x00ffff)
		title.anchorPoint = oVec2(0,1)
		y = yStart-20
		title.position = oVec2(xStart+20,y)
		menu:addChild(title)
		title.opacity = 0
		title:runAction(oOpacity(0.3,0.5))
		yStart = y-title.contentSize.height

		y = yStart-45
		newButton = oButton(
			"Change Model",17,
			itemWidth,50,
			xStart+itemWidth*0.5+10,
			y,
			function(item)
				cancelButton:unregisterTapHandler()
				opMenu.enabled = false
				panel:hide()
				local chooser = oFileChooser()
				chooser:show()
				oEditor.scene:addChild(chooser)
			end)
		newButton.color = ccColor3(0xffcc88)
		menu:addChild(newButton)
		newButton.opacity = 0
		newButton:runAction(
			CCSequence(
			{
				CCDelay((i%itemNum)*0.05),
				oOpacity(0.3,1)
			}))
		yStart = y-25

		local yTo = winSize.height*0.5+halfBH-y+60
		local viewHeight = yTo < borderSize.height and borderSize.height or yTo
		local viewWidth = borderSize.width
		local paddingX = 0
		local paddingY = 100
		panel:reset(viewWidth,viewHeight,paddingX,paddingY)
	end
	
	return panel
end

return oEditChooser