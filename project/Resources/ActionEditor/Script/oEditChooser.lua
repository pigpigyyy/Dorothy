local oButton = require("oButton")
local oSelectionPanel = require("oSelectionPanel")
local oFileChooser = require("oFileChooser")
local oBox = require("oBox")
local CCDirector = require("CCDirector")
local CCSize = require("CCSize")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCMenu = require("CCMenu")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local oOpacity = require("oOpacity")
local CCSequence = require("CCSequence")
local CCDelay = require("CCDelay")
local oSd = require("oEditor").oSd
local oEditor = require("oEditor").oEditor

local function oEditChooser(withCancel)
	local winSize = CCDirector.winSize
	local itemWidth = 120
	local itemNum = 2
	local borderSize = CCSize((itemWidth+10)*itemNum+10,winSize.height-200)
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
	cancelButton.anchor = oVec2.zero
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

		local title = CCLabelTTF("Edit  Animation","Arial",24)
		title.texture.antiAlias = false
		title.color = ccColor3(0x00ffff)
		title.anchor = oVec2(0.5,1)
		local y = yStart-20
		title.position = oVec2(winSize.width*0.5,y)
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
		for k,_ in pairs(aNames) do
			local name = #k > 10 and k:sub(1,7).."..." or k
			y = yStart-45-math.floor(i/itemNum)*60
			local button = oButton(name,17,
				itemWidth,50,
				xStart+itemWidth*0.5+10+(i%itemNum)*(itemWidth+10),
				y,
				function(item)
					cancelButton:unregisterTapHandler()
					panel.touchEnabled = false
					menu.enabled = false
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
			function()
				oBox("New Animation",
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
					end,true)	
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

		title = CCLabelTTF("Edit  Look","Arial",24)
		title.texture.antiAlias = false
		title.color = ccColor3(0x00ffff)
		title.anchor = oVec2(0.5,1)
		y = yStart-20
		title.position = oVec2(winSize.width*0.5,y)
		menu:addChild(title)
		title.opacity = 0
		title:runAction(oOpacity(0.3,0.5))
		yStart = y-title.contentSize.height

		local lNames = oEditor.data[oSd.lookNames]
		i = 0
		for k,_ in pairs(lNames) do
			local name = #k > 10 and k:sub(1,7).."..." or k
			y = yStart-45-math.floor(i/itemNum)*60
			local button = oButton(name,17,
				itemWidth,50,
				xStart+itemWidth*0.5+10+(i%itemNum)*(itemWidth+10),
				y,
				function(item)
					cancelButton:unregisterTapHandler()
					panel.touchEnabled = false
					menu.enabled = false
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
			function()
				oBox("New Look",
					function(text)
						if text == "" then
							return
						end
						for k,_ in pairs(lNames) do
							if text == k then
								return
							end
						end
						local index = -1
						repeat
							local flag = true
							index = index+1
							for _,v in pairs(lNames) do
								if v == index then
									flag = false
								end
							end
						until flag
						cancelButton:unregisterTapHandler()
						lNames[text] = index
						oEditor.editMenu:markEditButton(true)
						opMenu.enabled = false
						panel:hide()
						oEditor.look = text
						oEditor.editMenu:toLook()
					end,true)
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
			title = CCLabelTTF("Edit  Sprite","Arial",24)
			title.texture.antiAlias = false
			title.color = ccColor3(0x00ffff)
			title.anchor = oVec2(0.5,1)
			y = yStart-20
			title.position = oVec2(winSize.width*0.5,y)
			menu:addChild(title)
			title.opacity = 0
			title:runAction(oOpacity(0.3,0.5))
			yStart = y-title.contentSize.height

			y = yStart-45
			newButton = oButton(
				"Edit",17,
				itemWidth,50,
				xStart+itemWidth*0.5+10,
				y,
				function()
					cancelButton:unregisterTapHandler()
					panel.touchEnabled = false
					menu.enabled = false
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

		title = CCLabelTTF("Change  Model","Arial",24)
		title.texture.antiAlias = false
		title.color = ccColor3(0x00ffff)
		title.anchor = oVec2(0.5,1)
		y = yStart-20
		title.position = oVec2(winSize.width*0.5,y)
		menu:addChild(title)
		title.opacity = 0
		title:runAction(oOpacity(0.3,0.5))
		yStart = y-title.contentSize.height

		y = yStart-45
		newButton = oButton(
			"Change",17,
			itemWidth,50,
			xStart+itemWidth*0.5+10,
			y,
			function()
				cancelButton:unregisterTapHandler()
				panel.touchEnabled = false
				menu.enabled = false
				opMenu.enabled = false
				panel:hide()
				oFileChooser()
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

		if CCDirector.sceneStackSize > 1 then
			title = CCLabelTTF("Back to Menu","Arial",24)
			title.texture.antiAlias = false
			title.color = ccColor3(0x00ffff)
			title.anchor = oVec2(0.5,1)
			y = yStart-20
			title.position = oVec2(winSize.width*0.5,y)
			menu:addChild(title)
			title.opacity = 0
			title:runAction(oOpacity(0.3,0.5))
			yStart = y-title.contentSize.height

			y = yStart-45
			newButton = oButton(
				"Back",17,
				itemWidth,50,
				xStart+itemWidth*0.5+10,
				y,
				function()
					cancelButton:unregisterTapHandler()
					panel.touchEnabled = false
					menu.enabled = false
					opMenu.enabled = false
					panel:hide()
					CCDirector:popScene()
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

		local yTo = winSize.height*0.5+halfBH-y+60
		local viewHeight = yTo < borderSize.height and borderSize.height or yTo
		local viewWidth = borderSize.width
		local paddingX = 0
		local paddingY = 100
		panel:reset(viewWidth,viewHeight,paddingX,paddingY)
	end

	panel:show()
	oEditor.scene:addChild(panel)
	return panel
end

return oEditChooser