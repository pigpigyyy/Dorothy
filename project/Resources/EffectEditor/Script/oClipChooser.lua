local require = using("EffectEditor.Script")
local oVec2 = require("oVec2")
local oLine = require("oLine")
local ccColor4 = require("ccColor4")
local CCDrawNode = require("CCDrawNode")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local CCDirector = require("CCDirector")
local CCSize = require("CCSize")
local oSelectionPanel = require("oSelectionPanel")
local CCMenu = require("CCMenu")
local oButton = require("oButton")
local emit = require("emit")
local oContent = require("oContent")
local oCache = require("oCache")
local CCSprite = require("CCSprite")
local oScale = require("oScale")
local oEase = require("oEase")
local oOpacity = require("oOpacity")
local CCNode = require("CCNode")
local tolua = require("tolua")
local CCSequence = require("CCSequence")
local CCCall = require("CCCall")

local function oCircle(number)
	local width = 25
	local vs = {}
	local num = 20
	for i = 0, num do
		local angle = 2*math.pi*i/num
		table.insert(vs,oVec2(width*0.5*math.cos(angle),width*0.5*math.sin(angle)))
	end
	local line = oLine(vs,ccColor4(0xff00ffff))
	line.cascadeOpacity = false
	line.cascadeColor = false
	local drawNode = CCDrawNode()
	drawNode:drawDot(oVec2.zero,width*0.5,ccColor4(0x2200ffff))
	line:addChild(drawNode,-1)
	line.position = oVec2(100-width*0.5-5,width*0.5+5)
	local label = CCLabelTTF(tostring(number),"Arial",16)
	label.color = ccColor3(0x00ffff)
	label.texture.antiAlias = false
	line:addChild(label)
	return line
end

local function oClipChooser(clipName)
	local oEditor = require("oEditor")
	local winSize = CCDirector.winSize
	local itemWidth = clipName and 100 or 120
	local itemHeight = clipName and 100 or 50
	local itemNum = clipName and 5 or 3
	while (itemWidth+10)*itemNum+10 > winSize.width and itemNum > 1 do
		itemNum = itemNum - 1
	end
	local borderSize = CCSize((itemWidth+10)*itemNum+10,winSize.height-200)
	local panel = oSelectionPanel(borderSize)
	local menu = panel.menu
	local border = panel.border
	local halfBW = borderSize.width*0.5
	local halfBH = borderSize.height*0.5
	local paddingX = 0
	local paddingY = 100
	panel:reset(borderSize.width,borderSize.height,paddingX,paddingY)
	local background = CCDrawNode()
	background:drawPolygon(
	{
		oVec2(-halfBW,-halfBH),
		oVec2(halfBW,-halfBH),
		oVec2(halfBW,halfBH),
		oVec2(-halfBW,halfBH)
	},ccColor4(clipName and 0xe5133333 or 0xe5100000),0.5,ccColor4(0xffffafaf))
	border:addChild(background,-1)

	local opMenu = CCMenu()
	opMenu.swallowTouches = true
	opMenu.contentSize = CCSize(130,60)
	opMenu.anchor = oVec2(1,0.5)
	opMenu.touchPriority = CCMenu.DefaultHandlerPriority-3
	opMenu.position = oVec2(winSize.width*0.5+borderSize.width*0.5+30,winSize.height*0.5+borderSize.height*0.5)
	panel:addChild(opMenu)

	local cancelButton = oButton("Cancel",17,60,false,clipName and 0 or 70,0,function(item)
		item.enabled = false
		opMenu.enabled = false
		if panel.fadeSprites then
			panel:fadeSprites()
		end
		panel:hide()
	end)
	cancelButton.anchor = oVec2.zero
	local btnBk = CCDrawNode()
	btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
	btnBk.position = oVec2(30,30)
	cancelButton:addChild(btnBk,-1)
	opMenu:addChild(cancelButton)

	if clipName then
		local setButton = oButton("Set",17,60,false,70,0,function(item)
			item.enabled = false
			opMenu.enabled = false
			if panel.fadeSprites then
				panel:fadeSprites()
			end
			oEditor.effectData = panel.frameData
			oEditor:dumpData(oEditor.currentFile)
			emit("Effect.viewArea.changeEffect",oEditor.currentName)
			emit("Effect.frameViewer.data",oEditor.effectData)
			panel:hide()
		end)
		setButton.anchor = oVec2.zero
		local drawCircle = CCDrawNode()
		drawCircle:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
		drawCircle.position = oVec2(30,30)
		setButton:addChild(drawCircle,-1)
		opMenu:addChild(setButton)
	end

	panel.sprites = {}
	panel.init = function(self)
		local y = 0
		local n = 0
		if not clipName then
			local items = {}
			local function getResources(path)
				local files = oContent:getEntries(oEditor.input..oEditor.prefix..path,false)
				for _,file in ipairs(files) do
					local extension = file:match("%.([^%.\\/]*)$")
					if extension then
						extension = extension:lower()
					end
					if extension == "clip" then
						table.insert(items,path..file)
					end
				end
				if not oEditor.standAlone then
					local folders = oContent:getEntries(oEditor.input..oEditor.prefix..path,true)
					for _,folder in ipairs(folders) do
						if folder ~= "." and folder ~= ".." then
							getResources(path..folder.."/")
						end
					end
				end
			end
			getResources("")
			for i = 1,#items do
				local filename = items[i]
				n = n + 1
				y = borderSize.height-10-itemHeight*0.5-math.floor((n-1)/itemNum)*(itemHeight+10)
				local button = oButton(filename:match("([^%.\\/]*)%.[^%.\\/]*$"),17,
					itemWidth,itemHeight,
					itemWidth*0.5+10+((n-1)%itemNum)*(itemWidth+10),y,
					function()
						panel:hide()
						oEditor:addChild(oClipChooser(filename),oEditor.topMost)
					end)
				button.position = button.position + panel:getTotalDelta()
				menu:addChild(button)
			end
		else
			panel.number = 1
			panel.sprites = {}
			panel.frameData = {interval=oEditor.effectData.interval}
			local filename = oEditor.input..oEditor.prefix..clipName
			local names = oCache.Clip:getNames(filename)
			local file = clipName:match("[^\\/]*$")
			local prefix = (#file == #clipName and "" or clipName:sub(1,-1-#file))
			panel.frameData.file = oCache.Clip:getTextureFile(filename):match("[^\\/]*$")
			oContent:remove(oEditor.output..oEditor.currentFile)
			oEditor.currentFile = prefix..oEditor.currentFile:match("[^\\/]*$")
			oEditor.items[oEditor.currentName] = oEditor.currentFile
			oEditor:dumpEffectFile()
			for index = 1,#names do
				n = n + 1
				y = borderSize.height-10-math.floor((n-1)/itemNum)*(itemHeight+10)
				local clipStr = filename.."|"..names[index]
				local rect = CCSprite(clipStr).textureRect
				local sprite = nil
				local button = oButton("",0,
					100,100,
					10+((n-1)%itemNum)*(itemWidth+10),y,
					function(item)
						if panel.number > 99 then return end
						sprite.opacity = 1
						sprite.color = ccColor3()
						if not item.circles then item.circles = {} end
						local count = (#item.circles)
						if count < 9 then
							local circle = oCircle(panel.number)
							circle.scaleX = 0
							circle.scaleY = 0
							circle.positionX = circle.positionX - math.floor(count/3)*30
							circle.positionY = circle.positionY + (count%3)*30
							circle:runAction(oScale(0.3,1,1,oEase.OutBack))
							item.face.cascadeOpacity = false
							item.node:addChild(circle)
							table.insert(item.circles,circle)
							panel.number = panel.number + 1
							table.insert(panel.frameData,{rect=rect})
						end
					end)
				sprite = CCSprite(clipStr)
				local contentSize = sprite.contentSize
				if contentSize.width > 100 or contentSize.height > 100 then
					local scale = contentSize.width > contentSize.height and (100-2)/contentSize.width or (100-2)/contentSize.height
					sprite.scaleX = scale
					sprite.scaleY = scale
				end
				sprite.position = oVec2(100*0.5,100*0.5)
				sprite.opacity = 0
				sprite.color = ccColor3(0x666666)
				sprite:runAction(oOpacity(0.3,1))
				local node = CCNode()
				node.cascadeColor = false
				node.cascadeOpacity = false
				node:addChild(sprite)
				table.insert(panel.sprites,node)
				button.face:addChild(node)
				button.node = node
				button.anchor = oVec2(0,1)
				button.position = button.position + panel:getTotalDelta()
				menu:addChild(button)
			end

			n = n + 1
			y = borderSize.height-10-math.floor((n-1)/itemNum)*(itemHeight+10)
			local button = oButton("Clear\nSelection",17,
				100,100,
				10+((n-1)%itemNum)*(itemWidth+10),y,
				function()
					menu:eachChild(function(child)
						if tolua.type(child) == "CCMenuItem" and child.circles then
							child.face.cascadeOpacity = true
							local node = child.node.children[1]
							node.color = ccColor3(0x666666)
							local count = #panel.frameData
							while count > 0 do
								table.remove(panel.frameData)
								count = count - 1
							end
							for _,circle in ipairs(child.circles) do
								circle:runAction(CCSequence({oScale(0.3,0,0,oEase.OutQuad),CCCall(function()
									circle.parent:removeChild(circle)
								end)}))
							end
							child.circles = nil
						end
					end)
					panel.number = 1
				end)
			button.anchor = oVec2(0,1)
			button.position = button.position + panel:getTotalDelta()
			menu:addChild(button)

			panel.fadeSprites = function(self)
				local sprites = panel.sprites
				for i = 1,#sprites do
					sprites[i].cascadeOpacity = true
				end
				panel.sprites = nil
			end
		end

		local yTo = borderSize.height+itemHeight+10-y
		local viewHeight = yTo < borderSize.height and borderSize.height or yTo
		local viewWidth = borderSize.width
		panel:updateSize(viewWidth,viewHeight)
		menu.opacity = 0
		menu:runAction(oOpacity(0.3,1))
	end

	panel:show()
	return panel
end

return oClipChooser
