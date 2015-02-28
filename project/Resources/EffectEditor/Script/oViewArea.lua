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
local CCEase = require("CCEase")
local oContent = require("oContent")
local oEffect = require("oEffect")
local CCParticle = require("CCParticle")
local CCDictionary = require("CCDictionary")
local oEditor = require("oEditor")
local CCArray = require("CCArray")
local oListener = require("oListener")

local function oViewArea()
	local winSize = CCDirector.winSize

	local view = CCLayerColor(ccColor4(0xff1a1a1a))
	view.anchor = oVec2.zero
--[[
	local radius = 50
	local star = oStar(radius,ccColor4(0x6600ffff),0.5,ccColor4(0xff00ffff))
	star.position = oVec2(radius,radius)
	local renderTarget = CCRenderTarget(radius*2,radius*2)
	renderTarget:beginPaint(ccColor4(0))
	renderTarget:draw(star)
	renderTarget:endPaint()

	local tex = oCache.Texture:add(renderTarget,"star.png")

	local progressTimer = CCProgressTimer(CCSprite(tex))
	progressTimer:runAction(
		CCRepeatForever(
			CCSequence
			{
				CCCall(function()
					progressTimer.reverseDirection = false
				end),
				CCEase:sineInOut(CCProgress(1,0,100)),
				CCCall(function()
					progressTimer.reverseDirection = true
				end),
				CCEase:sineInOut(CCProgress(1,100,0)),
			}))
	progressTimer.position = oVec2(winSize.width*0.5,winSize.height*0.5)
	view:addChild(progressTimer)
]]
	view.data = CCArray()
	view.data:add(oListener("viewArea.changeEffect",function(effectName)
		if oEditor.effect then
			oEditor.effect:autoRemove():stop()
		end
		local extension = string.match(oEditor.items[effectName], "%.([^%.\\/]*)$")
		if extension == "par" then
			local effect = oEffect(effectName)
			effect:attachTo(view):setOffset(oEditor.origin):start()
			oEditor.effect = effect
		elseif extension == "frame" then
			-- TODO
		end
	end))

	return view
end

return oViewArea
