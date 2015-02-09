local CCDirector = require("CCDirector")
local CCLayerColor = require("CCLayerColor")
local ccColor4 = require("ccColor4")
local oVec2 = require("oVec2")
local oStar = require("oStar")
local CCRenderTarget = require("CCRenderTarget")
local oCache = require("oCache")
local CCSprite = require("CCSprite")
local CCProgressTimer = require("CCProgressTimer")
local CCProgress = require("CCProgress")
local CCRepeatForever = require("CCRepeatForever")
local CCSequence = require("CCSequence")
local CCCall = require("CCCall")
local CCDelay = require("CCDelay")

local function oViewArea()
	local winSize = CCDirector.winSize

	local view = CCLayerColor(ccColor4(0xff1a1a1a))
	view.anchor = oVec2.zero
	--view:resetColor(ccColor4(0xff00ffff),ccColor4(0xff0000ff),ccColor4(0xff00ff00),ccColor4(0xff000000))
	local radius = 50
	local star = oStar(radius,ccColor4(0x6600ffff),0.5,ccColor4(0xff00ffff))
	star.position = oVec2(radius,radius)
	local renderTarget = CCRenderTarget(radius*2+2,radius*2+2,true)
	renderTarget:beginPaint(ccColor4(0))
	renderTarget:draw(star)
	renderTarget:endPaint()
	oCache.Texture:add(renderTarget,"star.png")
	
	local sprite = CCSprite("star.png")
	local progressTimer = CCProgressTimer(sprite)
	progressTimer.reverseDirection = true
	progressTimer.percentage = 100
	progressTimer:runAction(
		CCRepeatForever(
			CCSequence
			{
				CCCall(function()
					progressTimer.reverseDirection = false
				end),
				CCProgress(10,0,100),
				CCCall(function()
					progressTimer.reverseDirection = true
					progressTimer.percentage = 0
					progressTimer.percentage = 100
				end),
				CCProgress(10,100,0),
			}))
	progressTimer.position = oVec2(winSize.width*0.5,winSize.height*0.5)
	view:addChild(progressTimer)

	return view
end

return oViewArea
