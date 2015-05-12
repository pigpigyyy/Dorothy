local oButton = require("oButton")
local oSelectionPanel = require("oSelectionPanel")
local CCDirector = require("CCDirector")
local CCSize = require("CCSize")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCMenu = require("CCMenu")
local oCache = require("oCache")
local CCSprite = require("CCSprite")
local oOpacity = require("oOpacity")
local CCNode = require("CCNode")
local oContent = require("oContent")
local oEditor = require("oEditor")
local oRoutine = require("oRoutine")
local once = require("once")
local ccColor3 = require("ccColor3")

local function oClipChooser(clipName)
	local winSize = CCDirector.winSize
	local itemWidth = clipName and 100 or 120
	local itemHeight = clipName and 100 or 50
	local itemNum = clipName and 5 or 3
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
	},ccColor4(clipName and 0xe5133333 or 0xe5100000),0.5,ccColor4(0x88ffafaf))
	border:addChild(background,-1)

	local opMenu = CCMenu()
	opMenu.contentSize = CCSize(60,60)
	opMenu.touchPriority = CCMenu.DefaultHandlerPriority-3
	opMenu.position = oVec2(winSize.width*0.5+borderSize.width*0.5,winSize.height*0.5+borderSize.height*0.5)
	panel:addChild(opMenu)

	local cancelButton = oButton("Cancel",17,60,false,0,0,function(item)
		item.tapHandler = nil
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

	panel.sprites = {}
	panel.init = function(self)
		local y = 0
		local n = 0
		if not clipName then
			local files = oContent:getEntries(oEditor.input,false)
			for index = 1,#files do
				local extension = string.match(files[index],"%.([^%.\\/]*)$")
				if extension then
					extension = string.lower(extension)
					if extension == "clip" then
						local filename = files[index]
						n = n + 1
						y = borderSize.height-10-itemHeight*0.5-math.floor((n-1)/itemNum)*(itemHeight+10)
						local button = oButton(filename:match("(.*)%.[^%.\\/]*$").."\n."..extension,17,
							itemWidth,itemHeight,
							itemWidth*0.5+10+((n-1)%itemNum)*(itemWidth+10),y,
							function()
								panel:hide()
								oEditor:addChild(oClipChooser(filename),oEditor.topMost)
							end)
						button.position = button.position + panel:getTotalDelta()
						menu:addChild(button)
					end
				end
			end
		else
			panel.sprites = {}
			local filename = oEditor.input..clipName
			local names = oCache.Clip:getNames(filename)
			for index = 1,#names do
				n = n + 1
				y = borderSize.height-10-itemHeight*0.5-math.floor((n-1)/itemNum)*(itemHeight+10)
				local clipStr = filename.."|"..names[index]
				local sprite = nil
				local button = oButton("",0,
					100,100,
					itemWidth*0.5+10+((n-1)%itemNum)*(itemWidth+10),y,
					function(item)
						sprite.opacity = 1
				sprite.color = ccColor3()
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
				sprite.color = ccColor3(0x888888)
				sprite:runAction(oOpacity(0.3,0.4))
				local node = CCNode()
				node.cascadeColor = false
				node.cascadeOpacity = false
				node:addChild(sprite)
				table.insert(panel.sprites,node)
				button.face:addChild(node)
				button.position = button.position + panel:getTotalDelta()
				menu:addChild(button)
			end
			panel.fadeSprites = function(self)
				local sprites = panel.sprites
				for i = 1,#sprites do
					sprites[i].cascadeOpacity = true
				end
				panel.sprites = nil
			end
		end
		
		local yTo = borderSize.height+itemHeight*0.5+10-y
		local viewHeight = yTo < borderSize.height and borderSize.height or yTo
		local viewWidth = borderSize.width
		panel:updateSize(viewWidth,viewHeight)
		menu.opacity = 0
		menu:runAction(oOpacity(0.3,1))
	end

	panel.ended = function(self)
		self.parent:removeChild(self)
	end

	panel:show()
	return panel
end

return oClipChooser
