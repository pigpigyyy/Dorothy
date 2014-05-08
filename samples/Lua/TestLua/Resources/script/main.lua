collectgarbage("setpause", 100)
collectgarbage("setstepmul", 5000)

oSd =
{
	anchorX = 1,
	anchorY = 2,
	clip = 3,
	name = 4,
	opacity = 5,
	rotation = 6,
	scaleX = 7,
	scaleY = 8,
	skewX = 9,
	skewY = 10,
	x = 11,
	y = 12,
	looks = 13,
	animationDefs = 14,
	children = 15,
	isFaceRight = 16,
	isBatchUsed = 17,
	clipFile = 18,
	keys = 19,
	animationNames = 20,
	lookNames = 21,
	-- extra
	sprite = 23,
	parent = 24,
	index = 25,
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
	oViewArea,
	oEditMenu,
	oViewPanel,
	oControlBar,
	oSettingPanel,
}

local controlNames =
{
	"viewArea",
	"editMenu",
	"viewPanel",
	"controlBar",
	"settingPanel",
}

oEditor.scene.anchorPoint = oVec2.zero
oEditor.scene.visible = false

local thread = coroutine.create(
	function()
		for i = 1,#controls do
			controls[i] = controls[i]()
			oEditor[controlNames[i]] = controls[i]
			coroutine.yield()
		end
		for i = 1,#controls do
			oEditor.scene:addChild(controls[i])
		end
	end)

oEditor.scene:scheduleUpdate(
	function(deltaTime, self)
		if not coroutine.resume(thread) then
			self:unscheduleUpdate()
			oEvent:send("EditorLoaded")
			oEditor.scene.visible = true
			oEditor.scene.opacity = 0
			oEditor.scene:runAction(oOpacity(0.3,1))
		end
	end)

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

cclog(tolua.type(CCClipNode))

CCDirector:run(oEditor.scene)
