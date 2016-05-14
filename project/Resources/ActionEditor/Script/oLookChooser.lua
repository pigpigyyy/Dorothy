local require = using("ActionEditor.Script")
local CCDirector = require("CCDirector")
local CCSize = require("CCSize")
local oSelectionPanel = require("oSelectionPanel")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local oOpacity = require("oOpacity")
local oButton = require("oButton")
local CCSequence = require("CCSequence")
local CCDelay = require("CCDelay")

local function oLookChooser()
	local oEditor = require("oEditor")
	local oSd = oEditor.oSd
	local winSize = CCDirector.winSize
	local itemWidth = 120
	local itemNum = 1
	local borderSize = CCSize((itemWidth+10)*itemNum+10,310)
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

	panel.sprites = {}
	panel.init = function(self)
		local xStart = winSize.width*0.5-halfBW -- left
		local yStart = winSize.height*0.5+halfBH -- top

		local title = CCLabelTTF("Look","Arial",24)
		title.texture.antiAlias = false
		title.color = ccColor3(0x00ffff)
		title.anchor = oVec2(0.5,1)
		local y = yStart-20
		title.position = oVec2(winSize.width*0.5,y)
		menu:addChild(title)
		title.opacity = 0
		title:runAction(oOpacity(0.3,1))
		yStart = y-title.contentSize.height

		local lNames = oEditor.modelData[oSd.lookNames]
		local i = 0
		y = yStart-45-math.floor(i/itemNum)*60
		local button = oButton("None",17,
			itemWidth,50,
			xStart+itemWidth*0.5+10+(i%itemNum)*(itemWidth+10),
			y,
			function()
				panel:hide()
				oEditor.look = ""
				oEditor.viewArea:getModel().look = ""
			end)
		menu:addChild(button)
		button.opacity = 0
		button:runAction(
			CCSequence(
			{
				CCDelay((i%itemNum)*0.05),
				oOpacity(0.3,1)
			}))
		i = i+1
		for k,_ in pairs(lNames) do
			local name = #k > 10 and k:sub(1,7).."..." or k
			y = yStart-45-math.floor(i/itemNum)*60
			button = oButton(name,17,
				itemWidth,50,
				xStart+itemWidth*0.5+10+(i%itemNum)*(itemWidth+10),
				y,
				function(item)
					panel:hide()
					oEditor.look = item.name
					oEditor.viewArea:getModel().look = item.name
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
		-- yStart = y-25

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

return oLookChooser
