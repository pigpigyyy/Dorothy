local require = using("ActionEditor.Script")
local CCDirector = require("CCDirector")
local CCSize = require("CCSize")
local oSelectionPanel = require("oSelectionPanel")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCMenu = require("CCMenu")
local oButton = require("oButton")
local thread = require("thread")
local sleep = require("sleep")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local oOpacity = require("oOpacity")
local CCSequence = require("CCSequence")
local CCDelay = require("CCDelay")
local oBox = require("oBox")
local oFileChooser = require("oFileChooser")

local function oEditChooser(withCancel)
	local oEditor = require("oEditor")
	local oSd = oEditor.oSd
	local winSize = CCDirector.winSize
	local itemWidth = 120
	local itemNum = 3
	local borderSize = CCSize((itemWidth+10)*itemNum+10,winSize.height*0.6)
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
	},ccColor4(0xe5100000),0.5,ccColor4(0xffffafaf))
	border:addChild(background,-1)

	local opMenu = CCMenu()
	opMenu.swallowTouches = true
	opMenu.contentSize = CCSize(130,60)
	opMenu.touchPriority = CCMenu.DefaultHandlerPriority-3
	opMenu.position = oVec2(winSize.width*0.5+borderSize.width*0.5-35,winSize.height*0.5+borderSize.height*0.5)
	panel:addChild(opMenu)

	if withCancel then
		local cancelButton = oButton("Cancel",17,60,false,70,0,function()
			opMenu.enabled = false
			panel:hide()
		end)
		cancelButton.anchor = oVec2.zero
		local btnBk = CCDrawNode()
		btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
		btnBk.position = oVec2(30,30)
		cancelButton:addChild(btnBk,-1)
		opMenu:addChild(cancelButton)
	end

	if oEditor.quitable then
		local quitButton = oButton("Quit",17,60,false,0,0,function()
			panel.touchEnabled = false
			menu.enabled = false
			opMenu.enabled = false
			panel:hide()
			oEditor.viewArea:originReset()
			if oEditor.standAlone then
				oEditor:emit("Quit")
			else
				thread(function()
					oEditor.viewArea:originReset()
					oEditor.viewArea:zoomReset()
					oEditor:hideEditor(true,false)
					sleep(0.6)
					oEditor:emit("Quit")
				end)
			end
		end)
		quitButton.anchor = oVec2.zero
		local btnBk = CCDrawNode()
		btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
		btnBk.position = oVec2(30,30)
		quitButton:addChild(btnBk,-1)
		opMenu:addChild(quitButton)
	end

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
		title:runAction(oOpacity(0.3,1))
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

		local aNames = oEditor.modelData[oSd.animationNames]
		local i = 0
		for k,_ in pairs(aNames) do
			local name = #k > 10 and k:sub(1,7).."..." or k
			y = yStart-20-math.floor(i/itemNum)*60
			local button = oButton(name,17,
				itemWidth,50,
				xStart+10+(i%itemNum)*(itemWidth+10),
				y,
				function(item)
					panel.touchEnabled = false
					menu.enabled = false
					opMenu.enabled = false
					panel:hide()
					oEditor.animation = item.name
					oEditor.editMenu:toAnimation()
				end)
			button.name = k
			menu:addChild(button)
			button.anchor = oVec2(0,1)
			button.opacity = 0
			button:runAction(
				CCSequence(
				{
					CCDelay((i%itemNum)*0.05),
					oOpacity(0.3,1)
				}))
			i = i+1
		end
		y = yStart-20-math.floor(i/itemNum)*60
		local newButton = oButton(
			"<NEW>",17,
			itemWidth,50,
			xStart+10+(i%itemNum)*(itemWidth+10),
			y,
			function()
				oBox("New Animation",
					function(text)
						if text == "" then
							return
						elseif text == "None" then
							oBox("Invalid Name!")
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
						aNames[text] = index
						addNewAnimation(oEditor.modelData,index+1)
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
		newButton.anchor = oVec2(0,1)
		newButton.opacity = 0
		newButton:runAction(
			CCSequence(
			{
				CCDelay((i%itemNum)*0.05),
				oOpacity(0.3,1)
			}))
		yStart = y-45

		title = CCLabelTTF("Edit  Look","Arial",24)
		title.texture.antiAlias = false
		title.color = ccColor3(0x00ffff)
		title.anchor = oVec2(0.5,1)
		y = yStart-20
		title.position = oVec2(winSize.width*0.5,y)
		menu:addChild(title)
		title.opacity = 0
		title:runAction(oOpacity(0.3,1))
		yStart = y-title.contentSize.height

		local lNames = oEditor.modelData[oSd.lookNames]
		i = 0
		for k,_ in pairs(lNames) do
			local name = #k > 10 and k:sub(1,7).."..." or k
			y = yStart-20-math.floor(i/itemNum)*60
			local button = oButton(name,17,
				itemWidth,50,
				xStart+10+(i%itemNum)*(itemWidth+10),
				y,
				function(item)
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
			button.anchor = oVec2(0,1)
			button.opacity = 0
			button:runAction(
				CCSequence(
				{
					CCDelay((i%itemNum)*0.05),
					oOpacity(0.3,1)
				}))
			i = i+1
		end
		y = yStart-20-math.floor(i/itemNum)*60
		newButton = oButton(
			"<NEW>",17,
			itemWidth,50,
			xStart+10+(i%itemNum)*(itemWidth+10),
			y,
			function()
				oBox("New Look",
					function(text)
						if text == "" then
							return
						elseif text == "None" then
							oBox("Invalid Name!")
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
		newButton.anchor = oVec2(0,1)
		newButton.opacity = 0
		newButton:runAction(
			CCSequence(
			{
				CCDelay((i%itemNum)*0.05),
				oOpacity(0.3,1)
			}))
		yStart = y-45

		if oEditor.state ~= oEditor.EDIT_SPRITE then
			title = CCLabelTTF("Edit  Sprite","Arial",24)
			title.texture.antiAlias = false
			title.color = ccColor3(0x00ffff)
			title.anchor = oVec2(0.5,1)
			y = yStart-20
			title.position = oVec2(winSize.width*0.5,y)
			menu:addChild(title)
			title.opacity = 0
			title:runAction(oOpacity(0.3,1))
			yStart = y-title.contentSize.height

			y = yStart-20
			newButton = oButton(
				"Edit",17,
				itemWidth,50,
				xStart+10,
				y,
				function()
					panel.touchEnabled = false
					menu.enabled = false
					opMenu.enabled = false
					panel:hide()
					oEditor.editMenu:toSprite()
				end)
			newButton.color = ccColor3(0xffcc88)
			menu:addChild(newButton)
			newButton.anchor = oVec2(0,1)
			newButton.opacity = 0
			newButton:runAction(
				CCSequence(
				{
					CCDelay((i%itemNum)*0.05),
					oOpacity(0.3,1)
				}))
			yStart = y-45
		end

		title = CCLabelTTF("Change  Model","Arial",24)
		title.texture.antiAlias = false
		title.color = ccColor3(0x00ffff)
		title.anchor = oVec2(0.5,1)
		y = yStart-20
		title.position = oVec2(winSize.width*0.5,y)
		menu:addChild(title)
		title.opacity = 0
		title:runAction(oOpacity(0.3,1))
		yStart = y-title.contentSize.height

		y = yStart-20
		newButton = oButton(
			"Change",17,
			itemWidth,50,
			xStart+10,
			y,
			function()
				panel.touchEnabled = false
				menu.enabled = false
				opMenu.enabled = false
				panel:hide()
				oFileChooser(true)
			end)
		newButton.color = ccColor3(0xffcc88)
		menu:addChild(newButton)
		newButton.anchor = oVec2(0,1)
		newButton.opacity = 0
		newButton:runAction(
			CCSequence(
			{
				CCDelay((i%itemNum)*0.05),
				oOpacity(0.3,1)
			}))
		-- yStart = y-45

		local yTo = winSize.height*0.5+halfBH-y+60
		local viewHeight = yTo < borderSize.height and borderSize.height or yTo
		local viewWidth = borderSize.width
		local paddingX = 0
		local paddingY = 100
		panel:reset(viewWidth,viewHeight,paddingX,paddingY)
	end

	panel:show()
	oEditor:addChild(panel)
	return panel
end

return oEditChooser
