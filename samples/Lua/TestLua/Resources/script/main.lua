collectgarbage("setpause", 100)
collectgarbage("setstepmul", 5000)

oSd =
{
	anchorX = 1,
	anchorY = 2,
	clip = 3,
	name = 4,
	opacity = 5,
	rect = 6,
	rotation = 7,
	scaleX = 8,
	scaleY = 9,
	skewX = 10,
	skewY = 11,
	x = 12,
	y = 13,
	visible = 14,
	looks = 15,
	animationDefs = 16,
	children = 17,
	isFaceRight = 18,
	isBatchUsed = 19,
	clipFile = 20,
	keys = 21,
	animationNames = 22,
	lookNames = 23,
	sprite = 24,
}

oAd =
{
	type = 1,
	frameDefs = 2,
}

oKd =
{
	x = 1,
	y = 2,
	scaleX = 3,
	scaleY = 4,
	skewX = 5,
	skewY = 6,
	rotation = 7,
	opacity = 8,
	visible = 9,
	easeOpacity = 10,
	easePos = 11,
	easeRotation = 12,
	easeScale = 13,
	easeSkew = 14,
	duration = 15
}

oFd =
{
	file = 2,
	beginTime = 3,
	endTime = 4
}

oEditor = {}
oEditor.model = nil
oEditor.look = nil
oEditor.animation = nil
oEditor.animationData = nil
oEditor.keyIndex = nil
oEditor.currentFramePos = nil
oEditor.sprite = nil
oEditor.spriteData = nil
oEditor.dirty = false
oEditor.loop = false
oEditor.isPlaying = false
oEditor.data = nil
oEditor.scene = CCScene()
oEditor.easeNames =
{
	"InQuad",
	"OutQuad",
	"InOutQuad",
	"InCubic",
	"OutCubic",
	"InOutCubic",
	"InQuart",
	"OutQuart",
	"InOutQuart",
	"InQuint",
	"OutQuint",
	"InOutQuint",
	"InSine",
	"OutSine",
	"InOutSine",
	"InExpo",
	"OutExpo",
	"InOutExpo",
	"InCirc",
	"OutCirc",
	"InOutCirc",
	"InElastic",
	"OutElastic",
	"InOutElastic",
	"InBack",
	"OutBack",
	"InOutBack",
	"InBounce",
	"OutBounce",
	"InOutBounce"
}
oEditor.easeNames[0] = "Linear"
oEditor.input = "Model/Input/"
oEditor.output = "Model/Output/"
oEditor.EDIT_NONE = 0
oEditor.EDIT_START = 1
oEditor.EDIT_SPRITE = 2
oEditor.EDIT_ANIMTION = 3
oEditor.EDIT_LOOK = 4
oEditor.state = oEditor.EDIT_NONE
oEditor.needSave = false

local oViewArea = require("Script/oViewArea")
local oEditMenu = require("Script/oEditMenu")
local oViewPanel = require("Script/oViewPanel")
local oControlBar = require("Script/oControlBar")
local oSettingPanel = require("Script/oSettingPanel")

local controls =
{
	-- Animation oEditor
	viewArea = oViewArea(),
	editMenu = oEditMenu(),
	viewPanel = oViewPanel(),
	controlBar = oControlBar(),
	settingPanel = oSettingPanel(),
}

oEditor.scene.anchorPoint = oVec2.zero
for key,item in pairs(controls) do
	oEditor.scene:addChild(item)
	oEditor[key] = item
end
oEvent:send("EditorLoaded")

local winSize = CCDirector.winSize
local textField = CCTextFieldTTF("Tap To Input","Arial",20)
textField.anchorPoint = oVec2.zero
textField.horizontalAlignment = CCTextAlign.HRight
cclog(tostring(textField.contentSize.width))
cclog(tostring(CCLabelTTF("Tap To Input","Arial",20).contentSize.width))
textField:attachWithIME()
textField.position = oVec2(winSize.width*0.5,winSize.height*0.5)
oEditor.scene:addChild(textField)
local cursor = oLine({oVec2(0,0),oVec2(0,20)},ccColor4(0xff00ffff))
cursor:runAction(
	CCRepeatForever(
		CCSequence(
		{
			CCShow(),
			CCDelay(0.5),
			CCHide(),
			CCDelay(0.5)
		})))
textField:scheduleUpdate(
	function()
		cursor.position = textField.position + oVec2(textField.contentSize.width,0)
	end)
oEditor.scene:addChild(cursor)

--[[
local names = oCache.Clip:getNames("jixienv.clip")
for i = 1,#names do
	local sp = CCSprite("jixienv.clip|"..names[i])
	sp.anchorPoint = oVec2.zero
	local target = CCRenderTarget(sp.contentSize.width,sp.contentSize.height)
	target:beginPaint(ccColor4(0))
	target:draw(sp)
	target:endPaint()
	target:save(names[i]..".png",CCImage.PNG)
end]]

CCDirector:run(oEditor.scene)
