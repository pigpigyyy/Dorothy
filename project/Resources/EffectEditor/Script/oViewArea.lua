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

local function oViewArea()
	local winSize = CCDirector.winSize

	local view = CCLayerColor(ccColor4(0xff1a1a1a))
	view.anchor = oVec2.zero
	--view:resetColor(ccColor4(0xff00ffff),ccColor4(0xff0000ff),ccColor4(0xff00ff00),ccColor4(0xff000000))
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

	oContent:saveToFile(oEditor.output.."fire.par",[[
<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
  <dict>
    <key>angle</key>
    <real>90</real>
    <key>angleVariance</key>
    <real>360</real>
    <key>blendAdditive</key>
    <real>1</real>
    <key>blendFuncDestination</key>
    <integer>1</integer>
    <key>blendFuncSource</key>
    <integer>770</integer>
    <key>duration</key>
    <real>-1</real>
    <key>emitterType</key>
    <real>0</real>
    <key>emissionRate</key>
    <real>350</real>
    <key>finishColorAlpha</key>
    <real>1</real>
    <key>finishColorBlue</key>
    <real>0</real>
    <key>finishColorGreen</key>
    <real>0</real>
    <key>finishColorRed</key>
    <real>0</real>
    <key>finishColorVarianceAlpha</key>
    <real>0</real>
    <key>finishColorVarianceBlue</key>
    <real>0</real>
    <key>finishColorVarianceGreen</key>
    <real>0</real>
    <key>finishColorVarianceRed</key>
    <real>0</real>
    <key>rotationStart</key>
    <real>0</real>
    <key>rotationStartVariance</key>
    <real>0</real>
    <key>rotationEnd</key>
    <real>0</real>
    <key>rotationEndVariance</key>
    <real>0</real>
    <key>finishParticleSize</key>
    <real>-1</real>
    <key>finishParticleSizeVariance</key>
    <real>0</real>
    <key>gravityx</key>
    <real>0</real>
    <key>gravityy</key>
    <real>0</real>
    <key>maxParticles</key>
    <real>100</real>
    <key>maxRadius</key>
    <real>0</real>
    <key>maxRadiusVariance</key>
    <real>0</real>
    <key>minRadius</key>
    <real>0</real>
    <key>minRadiusVariance</key>
    <real>0</real>
    <key>particleLifespan</key>
    <real>1</real>
    <key>particleLifespanVariance</key>
    <real>0.5</real>
    <key>radialAccelVariance</key>
    <real>0</real>
    <key>radialAcceleration</key>
    <real>0</real>
    <key>rotatePerSecond</key>
    <real>0</real>
    <key>rotatePerSecondVariance</key>
    <real>0</real>
    <key>sourcePositionVariancex</key>
    <real>0</real>
    <key>sourcePositionVariancey</key>
    <real>0</real>
    <key>sourcePositionx</key>
    <real>0</real>
    <key>sourcePositiony</key>
    <real>0</real>
    <key>speed</key>
    <real>20</real>
    <key>speedVariance</key>
    <real>5</real>
    <key>startColorAlpha</key>
    <real>1</real>
    <key>startColorBlue</key>
    <real>0.1176471</real>
    <key>startColorGreen</key>
    <real>0.2431373</real>
    <key>startColorRed</key>
    <real>0.7568628</real>
    <key>startColorVarianceAlpha</key>
    <real>0</real>
    <key>startColorVarianceBlue</key>
    <real>0</real>
    <key>startColorVarianceGreen</key>
    <real>0</real>
    <key>startColorVarianceRed</key>
    <real>0</real>
    <key>startParticleSize</key>
    <real>30</real>
    <key>startParticleSizeVariance</key>
    <real>10</real>
    <key>tangentialAccelVariance</key>
    <real>0</real>
    <key>tangentialAcceleration</key>
    <real>0</real>
    <key>rotationIsDir</key>
    <real>0</real>
    <key>textureFileName</key>
    <string>__firePngData</string>
  </dict>
</plist>]])

	oContent:saveToFile(oEditor.output.."main.effect",[[
<A>
	<B A="fire" B="fire.par"/>
</A>]])

	for item in io.open(oEditor.output.."main.effect","r"):read("*a"):gmatch("%b<>") do
		if not item:sub(2,2):match("[A/]") then
			local line = item:gsub("%s","")
			local name = line:match("A=\"(.-)\"")
			local filename = line:match("B=\"(.-)\"")
			oEditor.items[name] = filename
		end
	end
	local dict = CCDictionary(oEditor.output.."fire.par")
	local keys = dict.keys
	local parData = {}
	for _,v in ipairs(keys) do
		parData[v] = dict[v]
	end
	oEditor.effectData = parData
	oCache.Effect:load(oEditor.output.."main.effect")
	parData.startColorRed = 1
	parData.startColorGreen = 1
	parData.startColorBlue = 1
	local effect = oEffect("fire")
	oEffect:update(effect,parData)
	effect:attachTo(view):setOffset(oVec2(winSize.width*0.5,winSize.height*0.5)):autoRemove():start()
	return view
end

return oViewArea
