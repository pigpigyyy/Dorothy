local CCDirector = require("CCDirector")
local ccColor4 = require("ccColor4")
local oVec2 = require("oVec2")
local CCDrawNode = require("CCDrawNode")
local CCSize = require("CCSize")
local oSelectionPanel = require("oSelectionPanel")
local oEditor = require("oEditor")
local CCArray = require("CCArray")
local oListener = require("oListener")
local CCSequence = require("CCSequence")
local CCDelay = require("CCDelay")
local oPos = require("oPos")
local oEase = require("oEase")
local CCHide = require("CCHide")
local oButton = require("oButton")
local CCSprite = require("CCSprite")
local oLine = require("oLine")

local function oClipViewer(clipStr)
	local width = 130
	local sprite = CCSprite(clipStr)
	local contentSize = sprite.contentSize
	if contentSize.width > width or contentSize.height > width then
		local scale = contentSize.width > contentSize.height and (width-2)/contentSize.width or (width-2)/contentSize.height
		sprite.scaleX = scale
		sprite.scaleY = scale
	end
	local frame = oLine(
	{
		oVec2.zero,
		oVec2(width,0),
		oVec2(width,width),
		oVec2(0,width),
		oVec2.zero
	},ccColor4(0xff00ffff))
	
end

local function oFrameViewer()
	local winSize = CCDirector.winSize
	local halfW = winSize.width*0.5
	local halfH = winSize.height*0.5
	local borderW = halfW*2 - 240 - 30
	local borderH = 150

	local borderSize = CCSize(borderW,borderH)
	local panel = oSelectionPanel(borderSize,false,true,true)
	panel.touchPriority = oEditor.touchPrioritySettingPanel
	local menu = panel.menu
	menu.touchPriority = oEditor.touchPrioritySettingPanel+1
	local border = panel.border
	local halfBW = borderSize.width*0.5
	local halfBH = borderSize.height*0.5
	local itemWidth = borderSize.width
	local itemHeight = 30
	local endPos = oVec2(10-halfW+borderW*0.5,10-halfH+borderH*0.5)
	local startPos = oVec2(endPos.x,endPos.y-borderH-10)
	local background = CCDrawNode()
	background:drawPolygon(
	{
		oVec2(-halfBW,-halfBH),
		oVec2(halfBW,-halfBH),
		oVec2(halfBW,halfBH),
		oVec2(-halfBW,halfBH)
	},ccColor4(0xe5100000),0.5,ccColor4(0x88ffafaf))
	border:addChild(background,-1)
	panel.position = startPos
	panel.visible = false

	local button = oButton("Button",17,130,130,0,0,function() print("tepped") end)
	button.anchor = oVec2.zero
	button.position = oVec2(10,10)
	menu:addChild(button)

	local viewHeight = 100
	local viewWidth = borderSize.width+100
	panel:reset(viewWidth,viewHeight,25,0)

	panel.data = CCArray()
	panel.data:add(oListener("oEditor.particle",function()
		if panel.visible then
			panel:stopAllActions()
			panel:runAction(CCSequence({CCDelay(0.3),oPos(0.5,startPos.x,startPos.y,oEase.InBack),CCHide()}))
		end
	end))
	panel.data:add(oListener("oEditor.frame",function()
		panel:stopAllActions()
		panel.position = startPos
		panel.visible = true
		panel:runAction(oPos(0.5,endPos.x,endPos.y,oEase.OutBack))
	end))

	return panel
end

return oFrameViewer
