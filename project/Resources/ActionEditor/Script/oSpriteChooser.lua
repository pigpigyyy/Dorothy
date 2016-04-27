local require = using("ActionEditor.Script")
local oEditor = require("oEditor")
local CCDirector = require("CCDirector")
local CCSize = require("CCSize")
local oSelectionPanel = require("oSelectionPanel")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCMenu = require("CCMenu")
local oButton = require("oButton")
local oCache = require("oCache")
local CCSprite = require("CCSprite")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local CCSequence = require("CCSequence")
local CCDelay = require("CCDelay")
local oOpacity = require("oOpacity")
local CCNode = require("CCNode")

local function oSpriteChooser()
	local oSd = oEditor.oSd
	local winSize = CCDirector.winSize
	local itemWidth = 100
	local itemNum = 5
	while (itemWidth+10)*itemNum+10 > winSize.width and itemNum > 1 do
		itemNum = itemNum - 1
	end
	local borderSize = CCSize((itemWidth+10)*itemNum+10,winSize.height*0.6)
	local panel = oSelectionPanel(borderSize)
	local menu = panel.menu
	local border = panel.border
	local halfBW = borderSize.width*0.5
	local halfBH = borderSize.height*0.5
	local background = CCDrawNode()
	background:drawPolygon(
	{
		oVec2(-halfBW,-halfBH),
		oVec2(halfBW,-halfBH),
		oVec2(halfBW,halfBH),
		oVec2(-halfBW,halfBH)
	},ccColor4(0xe5133333),0.5,ccColor4(0xffffafaf))
	border:addChild(background,-1)

	local opMenu = CCMenu()
	opMenu.swallowTouches = true
	opMenu.contentSize = CCSize(60,60)
	opMenu.touchPriority = CCMenu.DefaultHandlerPriority-3
	opMenu.position = oVec2(winSize.width*0.5+borderSize.width*0.5,winSize.height*0.5+borderSize.height*0.5)
	panel:addChild(opMenu)

	local cancelButton = oButton("Cancel",17,60,false,
		0,0,
		function()
			opMenu.enabled = false
			panel:fadeSprites()
			panel:hide()
		end)
	cancelButton.anchor = oVec2.zero
	local btnBk = CCDrawNode()
	btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
	btnBk.position = oVec2(30,30)
	cancelButton:addChild(btnBk,-1)
	opMenu:addChild(cancelButton)

	panel.sprites = {}
	panel.init = function(self)
		local y = 0
		local clipFile = oEditor.modelData[oSd.clipFile]
		local names = oCache.Clip:getNames(clipFile)
		table.insert(names,1,"")
		for i = 1,#names do
			y = winSize.height*0.5+halfBH-10-math.floor((i-1)/itemNum)*110
			local button = oButton(
				"",
				0,
				100,100,
				winSize.width*0.5-halfBW+10+((i-1)%itemNum)*110,y,
				function()
					if panel.selected then
						cancelButton.enabled = false
						panel:hide()
						panel:selected(names[i])
					end
				end)
			button.anchor = oVec2(0,1)
			local clipStr = clipFile.."|"..names[i]
			local sprite = nil
			if names[i] ~= "" then
				sprite = CCSprite(clipStr)
				local contentSize = sprite.contentSize
				if contentSize.width > 100 or contentSize.height > 100 then
					local scale = contentSize.width > contentSize.height and (100-2)/contentSize.width or (100-2)/contentSize.height
					sprite.scaleX = scale
					sprite.scaleY = scale
				end
			else
				sprite = CCLabelTTF("Empty","Arial",16)
				sprite.texture.antiAlias = false
				sprite.color = ccColor3(0x00ffff)
			end
			sprite.position = oVec2(100*0.5,100*0.5)
			sprite.opacity = 0
			sprite:runAction(
				CCSequence(
				{
					CCDelay(((i-1)%itemNum)*0.05),
					oOpacity(0.3,1)
				}))
			--button.color = ccColor3()
			button.clip = names[i]
			local node = CCNode()
			node.cascadeColor = false
			node.cascadeOpacity = false
			node:addChild(sprite)
			table.insert(panel.sprites,node)

			button.face:addChild(node)
			menu:addChild(button)
		end
		menu.opacity = 0
		menu:runAction(oOpacity(0.3,1))

		local yTo = winSize.height*0.5+halfBH-y+110
		local viewHeight = yTo < borderSize.height and borderSize.height or yTo
		local viewWidth = borderSize.width
		local paddingX = 0
		local paddingY = 100
		panel:reset(viewWidth,viewHeight,paddingX,paddingY)
	end

	panel.fadeSprites = function(self)
		local sprites = panel.sprites
		for i = 1,#sprites do
			sprites[i].cascadeOpacity = true
		end
		panel.sprites = nil
	end

	panel:show()
	oEditor:addChild(panel)
	return panel
end

return oSpriteChooser
