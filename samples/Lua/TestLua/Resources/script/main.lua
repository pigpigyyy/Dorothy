collectgarbage("setpause", 100)
collectgarbage("setstepmul", 5000)

oSd =
{
	sprite = 0,
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

local oViewArea = require("script/oViewArea")
local oEditMenu = require("script/oEditMenu")
local oViewPanel = require("script/oViewPanel")
local oControlBar = require("script/oControlBar")
local oSettingPanel = require("script/oSettingPanel")

oEditor =
{
	-- Animation oEditor
	viewArea = oViewArea(),
	editMenu = oEditMenu(),
	viewPanel = oViewPanel(),
	controlBar = oControlBar(),
	settingPanel = oSettingPanel(),
}

local scene = CCScene()
scene.anchorPoint = oVec2.zero
for _,item in pairs(oEditor) do
	scene:addChild(item)
end

oEditor.model = "jixienv.model"
oEditor.look = "happy"
oEditor.animation = "attack"
oEditor.animationData = nil
oEditor.keyIndex = 1
oEditor.sprite = nil
oEditor.spriteData = nil
oEditor.dirty = false
oEditor.loop = false
oEditor.isPlaying = false
oEditor.data = oCache.Model:getData(oEditor.model)

CCDirector:run(scene)
