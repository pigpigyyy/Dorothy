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

local function oSpriteChooser()
	local winSize = CCDirector.winSize
	local borderSize = CCSize(560,400)
	local panel = oSelectionPanel(borderSize)
	local menu = panel.menu
	local border = panel.border
	local halfBW = borderSize.width*0.5
	local halfBH = borderSize.height*0.5
	local itemWidth = 100
	local itemHeight = 100
	local itemNum = 5
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
	},ccColor4(0xe5133333),0.5,ccColor4(0x88ffafaf))
	border:addChild(background,-1)

	local opMenu = CCMenu()
	opMenu.swallowTouches = true
	opMenu.contentSize = CCSize(60,60)
	opMenu.touchPriority = CCMenu.DefaultHandlerPriority-3
	opMenu.position = oVec2(winSize.width*0.5+borderSize.width*0.5,winSize.height*0.5+borderSize.height*0.5)
	panel:addChild(opMenu)

	local cancelButton = oButton("Cancel",17,60,false,0,0,function(item)
		item.tapHandler = nil
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
		local n = 0
		local files = oContent:getEntries(oEditor.input,false)
		local orderedFiles = {}
		for index = 1,#files do
			files[index] = oEditor.input..files[index]
			local extension = string.match(files[index],"%.([^%.\\/]*)$")
			if extension then
				extension = string.lower(extension)
				if extension == "png" and not oContent:exist(files[index]:sub(1,-4).."clip") then
					table.insert(orderedFiles,1,files[index])
				elseif extension == "clip" then
					table.insert(orderedFiles,files[index]:sub(1,-5).."png")
					table.insert(orderedFiles,files[index])
				end
			end
		end
		local routine
		n = n + 1
		y = borderSize.height-10-itemHeight*0.5-math.floor((n-1)/itemNum)*(itemHeight+10)
		local button = oButton("Built-In",16,100,100,
			itemWidth*0.5+10+((n-1)%itemNum)*(itemWidth+10),y,
			function()
				if panel.selected then
					cancelButton.tapHandler = nil
					oRoutine:remove(routine)
					panel:hide()
					panel.selected("__firePngData")
				end
			end)
		menu:addChild(button)
		routine = oRoutine(once(function()
			oCache:loadAsync(orderedFiles,function(filename)
				if not panel.sprites then return end
				local extension = string.match(filename,"%.([^%.\\/]*)$")
				if extension then
					extension = string.lower(extension)
					if extension == "clip" then
						local names = oCache.Clip:getNames(filename)
						for index = 1,#names do
							n = n + 1
							y = borderSize.height-10-itemHeight*0.5-math.floor((n-1)/itemNum)*(itemHeight+10)
							local clipStr = filename.."|"..names[index]
							local button = oButton("",0,
								100,100,
								itemWidth*0.5+10+((n-1)%itemNum)*(itemWidth+10),y,
								function()
									if panel.selected then
										cancelButton.tapHandler = nil
										oRoutine:remove(routine)
										panel:hide()
										panel.selected(clipStr)
									end
								end)
							local sprite = nil
							sprite = CCSprite(clipStr)
							local contentSize = sprite.contentSize
							if contentSize.width > 100 or contentSize.height > 100 then
								local scale = contentSize.width > contentSize.height and (100-2)/contentSize.width or (100-2)/contentSize.height
								sprite.scaleX = scale
								sprite.scaleY = scale
							end
							sprite.position = oVec2(100*0.5,100*0.5)
							sprite.opacity = 0
							sprite:runAction(oOpacity(0.3,1))
							local node = CCNode()
							node.cascadeColor = false
							node.cascadeOpacity = false
							node:addChild(sprite)
							table.insert(panel.sprites,node)
							button.face:addChild(node)
							button.position = button.position + panel:getTotalDelta()
							menu:addChild(button)
						end
					elseif extension == "png" then
						if not oContent:exist(filename:sub(1,-4).."clip") then
							n = n + 1
							y = borderSize.height-10-itemHeight*0.5-math.floor((n-1)/itemNum)*(itemHeight+10)
							local button = oButton("",0,
								100,100,
								itemWidth*0.5+10+((n-1)%itemNum)*(itemWidth+10),y,
								function()
									if panel.selected then
										cancelButton.tapHandler = nil
										oRoutine:remove(routine)
										panel:hide()
										panel.selected(filename)
									end
								end)
							local sprite = nil
							sprite = CCSprite(filename)
							local contentSize = sprite.contentSize
							if contentSize.width > 100 or contentSize.height > 100 then
								local scale = contentSize.width > contentSize.height and (100-2)/contentSize.width or (100-2)/contentSize.height
								sprite.scaleX = scale
								sprite.scaleY = scale
							end
							sprite.position = oVec2(100*0.5,100*0.5)
							sprite.opacity = 0
							sprite:runAction(oOpacity(0.3,1))
							local node = CCNode()
							node.cascadeColor = false
							node.cascadeOpacity = false
							node:addChild(sprite)
							table.insert(panel.sprites,node)
							button.face:addChild(node)
							button.position = button.position + panel:getTotalDelta()
							menu:addChild(button)
						end
					end
				end
				local yTo = borderSize.height+itemHeight*0.5+10-y
				local viewHeight = yTo < borderSize.height and borderSize.height or yTo
				local viewWidth = borderSize.width
				panel:updateSize(viewWidth,viewHeight)
			end)
		end))
		menu.opacity = 0
		menu:runAction(oOpacity(0.3,1))
	end

	panel.fadeSprites = function(self)
		local sprites = panel.sprites
		for i = 1,#sprites do
			sprites[i].cascadeOpacity = true
		end
		panel.sprites = nil
	end

	panel.ended = function(self)
		self.parent:removeChild(self)
		collectgarbage()
		oCache:removeUnused()
	end

	panel:show()
	return panel
end

return oSpriteChooser
