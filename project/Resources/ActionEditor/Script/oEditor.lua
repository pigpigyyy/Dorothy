local CCScene = require("CCScene")

local oSd =
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
	size = 18,
	clipFile = 19,
	keys = 20,
	animationNames = 21,
	lookNames = 22,
	-- extra
	sprite = 23,
	parent = 24,
	index = 25,
	fold = 26,
}

local oAd =
{
	type = 1,
	frameDefs = 2,
}

local oKd =
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

local oFd =
{
	file = 2,
	beginTime = 3,
}

local oEditor = {}
oEditor.model = nil
oEditor.look = ""
oEditor.animation = ""
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
	[0] = "Linear",
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
oEditor.res = "ActionEditor/Model/"
oEditor.input = oEditor.res.."Input/"
oEditor.output = oEditor.res.."Output/"
oEditor.EDIT_NONE = 0
oEditor.EDIT_START = 1
oEditor.EDIT_SPRITE = 2
oEditor.EDIT_ANIMTION = 3
oEditor.EDIT_LOOK = 4
oEditor.state = oEditor.EDIT_NONE
oEditor.needSave = false

return {oEditor=oEditor,oSd=oSd,oAd=oAd,oKd=oKd,oFd=oFd}
