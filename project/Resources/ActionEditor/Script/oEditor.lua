local require = using("ActionEditor.Script")
local CCScene = require("CCScene")
local oContent = require("oContent")
local oVec2 = require("oVec2")
local oRoutine = require("oRoutine")
local once = require("once")
local CCSize = require("CCSize")
local oCache = require("oCache")
local oOpacity = require("oOpacity")
local oEase = require("oEase")
local CCSpawn = require("CCSpawn")
local oScale = require("oScale")

local oSd =
{
	anchorX = 1,
	anchorY = 2,
	clip = 3,
	name = 4,
	opacity = 5,
	angle = 6,
	scaleX = 7,
	scaleY = 8,
	skewX = 9,
	skewY = 10,
	x = 11,
	y = 12,
	looks = 13,
	animationDefs = 14,
	children = 15,
	front = 16,
	isFaceRight = 17,
	isBatchUsed = 18,
	size = 19,
	clipFile = 20,
	keys = 21,
	animationNames = 22,
	lookNames = 23,
	-- extra
	sprite = 24,
	parent = 25,
	index = 26,
	fold = 27,
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
	angle = 7,
	opacity = 8,
	visible = 9,
	easeOpacity = 10,
	easePos = 11,
	easeAngle = 12,
	easeScale = 13,
	easeSkew = 14,
	duration = 15
}

local oFd =
{
	file = 2,
	beginTime = 3,
}

local oEditor = CCScene()
oEditor.isLoaded = false
oEditor.standAlone = true
oEditor.quitable = false
oEditor.prefix = ""
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
oEditor.modelData = nil
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
local res = oContent.writablePath.."Model/"
oEditor.input = res.."Input/"
oEditor.output = res.."Output/"
oEditor.EDIT_NONE = 0
oEditor.EDIT_START = 1
oEditor.EDIT_SPRITE = 2
oEditor.EDIT_ANIMTION = 3
oEditor.EDIT_LOOK = 4
oEditor.state = oEditor.EDIT_NONE
oEditor.needSave = false
oEditor.oSd = oSd
oEditor.oAd = oAd
oEditor.oKd = oKd
oEditor.oFd = oFd
oEditor.round = function(self,val)
	if type(val) == "number" then
		return val > 0 and math.floor(val+0.5) or math.ceil(val-0.5)
	else
		return oVec2(val.x > 0 and math.floor(val.x+0.5) or math.ceil(val.x-0.5),
			val.y > 0 and math.floor(val.y+0.5) or math.ceil(val.y-0.5))
	end
end
function oEditor:edit(modelFile,clipFile)
	oEditor.modelFile = modelFile
	oEditor.model = oEditor.output..modelFile
	oCache:removeUnused()
	oEditor.modelData = oCache.Model:getData(oEditor.model)
	oEditor.look = ""
	oEditor.animation = ""
	oEditor.animationData = nil
	oEditor.keyIndex = nil
	oEditor.currentFramePos = nil
	oEditor.sprite = nil
	oEditor.spriteData = nil
	oEditor.dirty = false
	--oEditor.needSave = false
	oEditor.editMenu:markEditButton(not oEditor.modelData)
	if not oEditor.modelData then
		oEditor.modelData =
		{
			0.5,--anchorX 1
			0.5,--anchorY 2
			"",--clip 3
			"",--name 4
			1,--opacity 5
			0,--angle 6
			1,--scaleX 7
			1,--scaleY 8
			0,--skewX 9
			0,--skewY 10
			0,--x 11
			0,--y 12
			{},--looks 13
			{},--animationDefs 14
			{},--children 15
			true,--front 16
			true,--isFaceRight 17
			false,--isBatchUsed 18
			CCSize.zero, --size 19
			oEditor.output..clipFile,--clipFile 20
			{},--keys 21
			{},--animationNames 22
			{},--lookNames 23
		}
	end
	oEditor.dirty = true
	local model = oEditor.viewArea:getModel()
	model.opacity = 0
	model.scaleX = 0
	model.scaleY = 0
	model:perform(CCSpawn({
		oOpacity(0.3,1,oEase.OutQuad),
		oScale(0.3,1,1,oEase.OutBack)
	}))
	oEditor.controlBar:clearCursors()
	oEditor.settingPanel:resetItems()
	oEditor.viewPanel:clearSelection()
	oEditor.viewPanel:updateImages(oEditor.modelData,model)
	oEditor.viewArea:setModelSize(oEditor.modelData[oSd.size])
	oEditor.viewArea:originReset()
	oEditor.editMenu.items.Size.visible = false
	oEditor.editMenu:toSprite()
end

local controls =
{
	"oViewArea",
	"oEditMenu",
	"oViewPanel",
	"oControlBar",
	"oSettingPanel",
}

oRoutine(once(function() -- load UI asynchronously
	for i = 1,#controls do
		local controlName = controls[i]
		controls[i] = require(controlName) -- load codes
		coroutine.yield()
		controls[i] = controls[i]() -- create instance
		controlName = controlName:sub(2,2):lower()..controlName:sub(3,-1)
		oEditor[controlName] = controls[i]
		coroutine.yield()
		oEditor:addChild(controls[i]) -- add to scene
		coroutine.yield()
	end
	oEditor.editMenu:toStart()
	coroutine.yield()
	oEditor.vertexControl = require("oVertexControl")() -- one more control to load
	coroutine.yield()
	oEditor:addChild(oEditor.vertexControl)
	coroutine.yield()

	if oEditor.standAlone then
		local resPath = "res/Model"
		local writePath = oContent.writablePath.."Model"
		if not oContent:exist(oContent.writablePath.."Model") and oContent:exist("res/Model") then
			oContent:copyAsync(resPath,writePath) -- copy some prepared contents
		end
		if not oContent:exist(oEditor.input) then
			oContent:mkdir(oEditor.input)
		end
		if not oContent:exist(oEditor.output) then
			oContent:mkdir(oEditor.output)
		end
		local oFileChooser = require("oFileChooser")
		oFileChooser(true)
	end
	if not oEditor.isLoaded then
		oEditor.isLoaded = true
	end
end))

oEditor:slot("Entering",function()
	oRoutine(once(function()
		repeat
			coroutine.yield()
		until oEditor.isLoaded
		oEditor:emit("Activated")
	end))
end)

return oEditor
