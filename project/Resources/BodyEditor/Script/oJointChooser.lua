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
	
local joints =
{
	"Distance",
	"Friction",
	"Gear",
	"Spring",
	"Prismatic",
	"Pulley",
	"Revolute",
	"Rope",
	"Weld",
	"Wheel",
}
local function oJointChooser()
	local winSize = CCDirector.winSize
	local itemWidth = 120
	local itemHeight = 60
	local itemNum = 3
	local paddingX = 0
	local paddingY = 100
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

	local n = 0
	local y = 0
	local xStart = 0 -- left
	local yStart = borderSize.height -- top

	local title = CCLabelTTF("New  Joint","Arial",24)
	title.texture.antiAlias = false
	title.color = ccColor3(0x00ffff)
	title.anchor = oVec2(0.5,1)
	y = yStart-20
	title.position = oVec2(halfBW,y)
	menu:addChild(title)
	title.opacity = 0
	title:runAction(oOpacity(0.3,0.5))
	yStart = y-title.contentSize.height-10

	for i = 1,#joints do
		n = n+1
		y = yStart-(itemHeight*0.5+10)-math.floor((n-1)/itemNum)*(itemHeight+10)
		local name = joints[i]
		local button = oButton(
			name,
			17,
			itemWidth,itemHeight,
			xStart+itemWidth*0.5+10+((n-1)%itemNum)*(itemWidth+10), y,
			function(item)
				local joint = item.joint
				local data = oEditor["new"..joint](oEditor)
				oEditor:addData(data)
				oEvent:send("viewPanel.choose",data)
				oEvent:send("editor.change")
				panel.ended = function()
					panel.parent:removeChild(panel)
				end
				panel:hide()
			end)
		button.joint = joints[i]
		button.enabled = false
		button.opacity = 0
		button:runAction(
			CCSequence(
			{
				CCDelay(n*0.05),
				oOpacity(0.2,1),
				CCCall(
					function()
						button.enabled = true
					end)
			}))
		menu:addChild(button)
	end

	local yTo = borderSize.height+itemHeight*0.5+10-y
	local viewHeight = yTo < borderSize.height and borderSize.height or yTo
	local viewWidth = borderSize.width
	panel:reset(viewWidth,viewHeight,paddingX,paddingY)
	
	local opMenu = CCMenu()
	opMenu.contentSize = CCSize(60,60)
	opMenu.anchor = oVec2(1,0.5)
	opMenu.touchPriority = CCMenu.DefaultHandlerPriority-3
	opMenu.position = oVec2(winSize.width*0.5+borderSize.width*0.5+(itemHeight*0.5+10),winSize.height*0.5+borderSize.height*0.5)
	panel:addChild(opMenu)

	local cancelButton = oButton("Cancel",17,60,false,
		0,0,
		function(item)
			opMenu.enabled = false
			panel:hide()
			item.tapHandler = nil
		end)
	cancelButton.anchor = oVec2.zero
	local btnBk = CCDrawNode()
	btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
	btnBk.position = oVec2(30,30)
	cancelButton:addChild(btnBk,-1)
	opMenu:addChild(cancelButton)

	panel:show()
	return panel
end

return oJointChooser
