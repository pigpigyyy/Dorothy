local CCDirector = require("CCDirector")
local oLine = require("oLine")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local ccColor3 = require("ccColor3")
local CCLabelTTF = require("CCLabelTTF")
local CCDrawNode = require("CCDrawNode")
local oPos = require("oPos")
local oEase = require("oEase")
local oScale = require("oScale")
local CCSequence = require("CCSequence")
local CCDelay = require("CCDelay")
local oOpacity = require("oOpacity")
local CCHide = require("CCHide")

local function oTip()
	local winSize = CCDirector.winSize
	local border = CCDrawNode()
	border:drawPolygon(
	{
		oVec2(-130,25),
		oVec2(130,25),
		oVec2(130,-25),
		oVec2(-130,-25),
	},ccColor4(0xff000000),0.5,ccColor4(0xff00ffff))
	border.position = oVec2((winSize.width-170)*0.5,winSize.height-35)
	border.opacity = 0.5
	border.cascadeColor = false
	border.visible = false

	local label = CCLabelTTF("","Arial",18)
	label.color = ccColor3(0xff00ffff)
	border:addChild(label)
	
--[[
	local line = oLine({oVec2(-120,0),oVec2(120,0)},ccColor4(0xff00ffff))
	line.position = oVec2(0,-17)
	line.cascadeColor = false
	border:addChild(line)

	local circle = CCDrawNode()
	circle:drawPolygon({oVec2(-5,5),oVec2(5,5),oVec2(5,-5),oVec2(-5,-5)},ccColor4(0),0.5,ccColor4(0xff00ffff))
	line:addChild(circle)
--]]
	border.show = function(self,text)
		border.visible = true
		label.text = text
		label.texture.antiAlias = false
		border.positionY = winSize.height+25
		border.opacity = 0.4
		border:stopAllActions()
		border:runAction(CCSequence({oPos(0.4,(winSize.width-170)*0.5,winSize.height-35,oEase.OutBack),CCDelay(1.6),oOpacity(0.3,0),CCHide()}))
		--circle.positionX = -115
		--circle:stopAllActions()
		--circle:runAction(oPos(2,115,0,oEase.OutQuad))
	end
	return border
end

return oTip