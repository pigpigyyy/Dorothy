local oButton = require("Script/oButton")
local oSelectionPanel = require("Script/oSelectionPanel")

local function oSpriteChooser()
	local winSize = CCDirector.winSize
	local borderSize = CCSize(670,400)
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
			opMenu.enabled = false
			panel:fadeSprites()
			panel:hide()
		end)
	cancelButton.anchorPoint = oVec2.zero
	local btnBk = CCDrawNode()
	btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
	btnBk.position = oVec2(30,30)
	cancelButton:addChild(btnBk,-1)
	opMenu:addChild(cancelButton)
	
	panel.sprites = {}
	panel.init = function(self)
		local i = 2
		local y = 0
		local clipFile = oEditor.data[oSd.clipFile]
		local names = oCache.Clip:getNames(clipFile)
		for i = 1,#names do
			y = winSize.height*0.5+halfBH-60-math.floor((i-1)/6)*110
			local button = oButton(
				"",
				0,
				100,100,
				winSize.width*0.5-halfBW+60+((i-1)%6)*110,y,
				function(item)
					if panel.selected then
						panel.selected(names[i])
					end
				end)
			local clipStr = clipFile.."|"..names[i]
			local sprite = CCSprite(clipStr)
			local contentSize = sprite.contentSize
			if contentSize.width > 100 or contentSize.height > 100 then
				local scale = contentSize.width > contentSize.height and (100-2)/contentSize.width or (100-2)/contentSize.height
				sprite.scaleX = scale
				sprite.scaleY = scale
			end
			sprite.position = oVec2(100*0.5,100*0.5)
			sprite.opacity = 0
			sprite:runAction(
				CCSequence(
				{
					CCDelay(((i-1)%6)*0.05),
					oOpacity(0.3,1)
				}))

			button.color = ccColor3()
			local node = CCNode()
			node.cascadeColor = false
			node.cascadeOpacity = false
			node:addChild(sprite)
			table.insert(panel.sprites,node)
			
			button.face:addChild(node)
			menu:addChild(button)
		end
		panel.fadeSprites = function(self)
			local sprites = panel.sprites
			for i = 1,#sprites do
				sprites[i].cascadeOpacity = true
			end
			panel.sprites = nil
		end
		menu.opacity = 0
		menu:runAction(oOpacity(0.3,1))
		
		local yTo = winSize.height*0.5+halfBH-y+60
		local viewHeight = yTo < borderSize.height and borderSize.height or yTo
		local viewWidth = borderSize.width
		local paddingX = 0
		local paddingY = 100
		panel:reset(viewWidth,viewHeight,paddingX,paddingY)
	end
	
	return panel
end

return oSpriteChooser