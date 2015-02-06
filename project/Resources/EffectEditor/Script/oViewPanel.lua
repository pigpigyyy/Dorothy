local CCSize = require("CCSize")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCDirector = require("CCDirector")
local oSelectionPanel = require("oSelectionPanel")
local oViewItem = require("oViewItem")
local oEvent = require("oEvent")
local CCDictionary = require("CCDictionary")
local oListener = require("oListener")
local oEditor = require("oEditor")
local oLine = require("oLine")
local CCSequence = require("CCSequence")
local CCDelay = require("CCDelay")
local oOpacity = require("oOpacity")

local function oViewPanel()
	local winSize = CCDirector.winSize
	local borderSize = CCSize(180,winSize.height-20)
	local self = oSelectionPanel(borderSize,false,true,true)
	self.touchPriority = oEditor.touchPriorityViewPanel
	local menu = self.menu
	menu.touchPriority = oEditor.touchPriorityViewPanel+1
	local border = self.border
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
	self.position = oVec2(-winSize.width*0.5+100,0)

	return self
end

return oViewPanel
