local CCDirector = require("CCDirector")
local CCSize = require("CCSize")
local oSelectionPanel = require("oSelectionPanel")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local oContent = require("oContent")
local oEditor = require("oEditor")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local oOpacity = require("oOpacity")
local oButton = require("oButton")
local CCSequence = require("CCSequence")
local CCDelay = require("CCDelay")
local CCCall = require("CCCall")
local CCMenu = require("CCMenu")
local oBox = require("oBox")
local oEvent = require("oEvent")

local function oFileChooser(addExisted)
	local winSize = CCDirector.winSize
	local itemWidth = 120
	local itemNum = 3
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
	opMenu.contentSize = CCSize(130,60)
	opMenu.anchor = oVec2(1,0.5)
	opMenu.touchPriority = CCMenu.DefaultHandlerPriority-3
	opMenu.position = oVec2(winSize.width*0.5+borderSize.width*0.5+30,winSize.height*0.5+borderSize.height*0.5)
	panel:addChild(opMenu)

	local cancelButton = oButton("Cancel",17,60,false,
		70,0,
		function(item)
			opMenu.enabled = false
			panel:hide()
			item:unregisterTapHandler()
		end)
	cancelButton.anchor = oVec2.zero
	local btnBk = CCDrawNode()
	btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
	btnBk.position = oVec2(30,30)
	cancelButton:addChild(btnBk,-1)
	opMenu:addChild(cancelButton)

	if not oContent:exist(oEditor.output.."main.effect") then
		local file = io.open(oEditor.output.."main.effect","w")
		file:write("<A></A>")
		file:close()
	end
	local file = io.open(oEditor.output.."main.effect","r")
	for item in file:read("*a"):gmatch("%b<>") do
		if not item:sub(2,2):match("[A/]") then
			local line = item:gsub("%s","")
			local name = line:match("A=\"(.-)\"")
			local filename = line:match("B=\"(.-)\"")
			oEditor.items[name] = filename
		end
	end
	file:close()

	local n = 0
	local y = 0
	local xStart = 0 -- left
	local yStart = borderSize.height -- top
	local function resetPanel()
		local yTo = winSize.height*0.5+halfBH-y+35
		local viewHeight = yTo < borderSize.height and borderSize.height or yTo
		local viewWidth = borderSize.width
		local paddingX = 0
		local paddingY = 100
		panel:reset(viewWidth,viewHeight,paddingX,paddingY)
	end

	if addExisted then
		local title = CCLabelTTF("Add  Effect","Arial",24)
		title.texture.antiAlias = false
		title.color = ccColor3(0x00ffff)
		title.anchor = oVec2(0.5,1)
		y = yStart-20
		title.position = oVec2(halfBW,y)
		menu:addChild(title)
		title.opacity = 0
		title:runAction(oOpacity(0.3,0.5))
		yStart = y-title.contentSize.height-(oEditor.currentFile and -10 or 20)
		
		local entries = oContent:getEntries(oEditor.output,false)
		local files = {}
		for i = 1,#entries do
			local extension = string.match(entries[i], "%.([^%.\\/]*)$")
			if extension then extension = string.lower(extension) end
			if extension == "par" or extension == "frame" then
				table.insert(files,entries[i])
			end
		end

		for i = 1,#files do
			n = n+1
			y = yStart-35-math.floor((n-1)/itemNum)*60
			local itemName = files[i]:match("(.*)%.[^%.\\/]*$")
			local name = #itemName > 10 and itemName:sub(1,7).."..." or itemName
			name = name.."\n."..files[i]:match("%.([^%.\\/]*)$")
			local button = oButton(
				name,
				17,
				itemWidth,50,
				xStart+itemWidth*0.5+10+((n-1)%itemNum)*(itemWidth+10), y,
				function(item)
					panel.ended = function()
						panel.parent:removeChild(panel)
					end
					panel:hide()
					local name = oEditor:getUsableName(item.file:match("(.*)%.[^%.\\/]*$"))
					oEditor.items[name] = item.file
					oEditor:dumpEffectFile()
				end)
			button.file = files[i]
			button.enabled = false
			button.opacity = 0
			button:runAction(
				CCSequence(
				{
					CCDelay(n*0.05),
					oOpacity(0.2,1),
					CCCall(function()
						button.enabled = true
					end)
				}))
			menu:addChild(button)
		end
		
		resetPanel()
		panel:show()
		return panel
	end

	local title = CCLabelTTF("Choose  Effect","Arial",24)
	title.texture.antiAlias = false
	title.color = ccColor3(0x00ffff)
	title.anchor = oVec2(0.5,1)
	y = yStart-20
	title.position = oVec2(halfBW,y)
	menu:addChild(title)
	title.opacity = 0
	title:runAction(oOpacity(0.3,0.5))
	yStart = y-title.contentSize.height-(oEditor.currentFile and -10 or 20)

	if oEditor.currentFile then
		title = CCLabelTTF("(Current: "..oEditor.currentFile:sub(1,-6)..")","Arial",16)
		title.texture.antiAlias = false
		title.color = ccColor3(0x00ffff)
		title.anchor = oVec2(0.5,1)
		y = yStart-20
		title.position = oVec2(halfBW,y)
		menu:addChild(title)
		title.opacity = 0
		title:runAction(oOpacity(0.3,0.5))
		yStart = y-title.contentSize.height-10
	end
	
	for item in io.open(oEditor.output.."main.effect","r"):read("*a"):gmatch("%b<>") do
		if not item:sub(2,2):match("[A/]") then
			local line = item:gsub("%s","")
			local name = line:match("A=\"(.-)\"")
			local filename = line:match("B=\"(.-)\"")
			oEditor.items[name] = filename
		end
	end

	local i = 0
	for itemName,filename in pairs(oEditor.items) do
		n = n+1
		i = i+1
		y = yStart-35-math.floor((n-1)/itemNum)*60
		local name = #itemName > 10 and itemName:sub(1,7).."..." or itemName
		local button = oButton(
			name,
			17,
			itemWidth,50,
			xStart+itemWidth*0.5+10+((n-1)%itemNum)*(itemWidth+10), y,
			function(item)
				oEditor.currentFile = item.file
				panel.ended = function()
					panel.parent:removeChild(panel)
				end
				panel:hide()
			end)
		button.file = filename
		button.enabled = false
		button.opacity = 0
		button:runAction(
			CCSequence(
			{
				CCDelay(n*0.05),
				oOpacity(0.2,1),
				CCCall(function()
					button.enabled = true
				end)
			}))
		menu:addChild(button)
	end
	n = n+1
	y = yStart-35-math.floor((n-1)/itemNum)*60
	local newPButton = oButton(
		"<PARTICLE>",
		17,
		itemWidth,50,
		xStart+itemWidth*0.5+10+((n-1)%itemNum)*(itemWidth+10), y,
		function()
			panel.ended = function()
				panel.parent:removeChild(panel)
			end
			panel:hide()
			oEditor:addChild(oBox("New Particle",function(name)
				oEditor.currentFile = name..".par"
			end,true),oEditor.topMost)
		end)
	newPButton.color = ccColor3(0x80ff00)
	newPButton.enabled = false
	newPButton.opacity = 0
	newPButton:runAction(
		CCSequence(
		{
			CCDelay(n*0.05),
			oOpacity(0.2,1),
			CCCall(function()
				newPButton.enabled = true
			end)
		}))
	menu:addChild(newPButton)
	n = n+1
	y = yStart-35-math.floor((n-1)/itemNum)*60
	local newFButton = oButton(
		"<FRAME>",
		17,
		itemWidth,50,
		xStart+itemWidth*0.5+10+((n-1)%itemNum)*(itemWidth+10), y,
		function()
			panel.ended = function()
				panel.parent:removeChild(panel)
			end
			panel:hide()
			oEditor:addChild(oBox("New Frame",function(name)
				oEditor.currentFile = name..".frame"
			end,true),oEditor.topMost)
		end)
	newFButton.color = ccColor3(0x80ff00)
	newFButton.enabled = false
	newFButton.opacity = 0
	newFButton:runAction(
		CCSequence(
		{
			CCDelay(n*0.05),
			oOpacity(0.2,1),
			CCCall(function()
				newFButton.enabled = true
			end)
		}))
	menu:addChild(newFButton)

	n = n+1
	y = yStart-35-math.floor((n-1)/itemNum)*60
	local addButton = oButton(
		"<ADD>",
		17,
		itemWidth,50,
		xStart+itemWidth*0.5+10+((n-1)%itemNum)*(itemWidth+10), y,
		function()
			panel.ended = function()
				panel.parent:removeChild(panel)
			end
			panel:hide()
			oEditor:addChild(oFileChooser(true),oEditor.topMost)
		end)
	addButton.color = ccColor3(0xff8000)
	addButton.enabled = false
	addButton.opacity = 0
	addButton:runAction(
		CCSequence(
		{
			CCDelay(n*0.05),
			oOpacity(0.2,1),
			CCCall(function()
				addButton.enabled = true
			end)
		}))
	menu:addChild(addButton)

	if oEditor.currentFile then
		n = n+1
		y = yStart-35-math.floor((n-1)/itemNum)*60
		local delButton = oButton(
			"<DEL>",
			17,
			itemWidth,50,
			xStart+itemWidth*0.5+10+((n-1)%itemNum)*(itemWidth+10), y,
			function()
				panel.ended = function()
					panel.parent:removeChild(panel)
				end
				panel:hide()
				oEditor:addChild(oBox("Delete "..oEditor.currentFile:sub(1,-5),function()
					oContent:remove(oEditor.output..oEditor.currentFile)
					oEditor.currentFile = nil
					oEditor:addChild(oFileChooser(),oEditor.topMost)
				end),oEditor.topMost)
			end)
		delButton.color = ccColor3(0xff0080)
		delButton.enabled = false
		delButton.opacity = 0
		delButton:runAction(
			CCSequence(
			{
				CCDelay(n*0.05),
				oOpacity(0.2,1),
				CCCall(function()
					delButton.enabled = true
				end)
			}))
		menu:addChild(delButton)
	end

	if CCDirector.sceneStackSize > 1 then
		local backButton = oButton("Quit",17,60,false,
			0,0,
			function(item)
				opMenu.enabled = false
				item:unregisterTapHandler()
				CCDirector:popToRootScene()
			end)
		backButton.anchor = oVec2.zero
		local btnBk = CCDrawNode()
		btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
		btnBk.position = oVec2(30,30)
		backButton:addChild(btnBk,-1)
		opMenu:addChild(backButton)
	end

	resetPanel()
	panel:show()
	return panel
end

return oFileChooser
