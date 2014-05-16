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

local bk = CCLayerColor(ccColor4(0xff000000),CCDirector.winSize.width,CCDirector.winSize.height)
bk.anchorPoint = oVec2.zero
local logo = CCLabelTTF("Luv Fight","Arial",12)
logo.texture.antiAlias = false
logo.position = oVec2(CCDirector.winSize.width*0.5,CCDirector.winSize.height*0.5)
logo.scaleX = 5
logo.scaleY = 5
bk:addChild(logo)
local flower = CCDrawNode()
flower:drawPolygon(
{
	oVec2(-1,10),
	oVec2(9,10),
	oVec2(9,20),
	oVec2(-1,20),
},ccColor4(0xff00ffff))
flower:drawPolygon(
{
	oVec2(10,-1),
	oVec2(20,-1),
	oVec2(20,9),
	oVec2(10,9),
},ccColor4(0xff00ffff))
flower:drawPolygon(
{
	oVec2(21,10),
	oVec2(31,10),
	oVec2(31,20),
	oVec2(21,20),
},ccColor4(0xff00ffff))
flower:drawPolygon(
{
	oVec2(10,21),
	oVec2(20,21),
	oVec2(20,31),
	oVec2(10,31),
},ccColor4(0xff00ffff))
flower.scaleX = 0.1
flower.scaleY = 0.1
flower.position = oVec2(logo.contentSize.width+2,logo.contentSize.height-2)
logo:addChild(flower)
oEditor.scene:addChild(bk,998)

local time = 0
oEditor.scene:scheduleUpdate(
	function(deltaTime, self)
		time = time+deltaTime
		if not coroutine.resume(thread) then
			self:unscheduleUpdate()
			oEvent:send("EditorLoaded")
			if time < 1 then
				logo:runAction(
					CCSequence
					{
						CCDelay(1-time),
						oOpacity(0.3,0),
						CCCall(
							function()
								bk.visible = false
								bk.parent:removeChild(bk)
								oEditor.scene.opacity = 0
								oEditor.scene:runAction(oOpacity(0.3,1))
							end)
					})
			else
				bk.visible = false
				bk.parent:removeChild(bk)
				oEditor.scene.opacity = 0
				oEditor.scene:runAction(oOpacity(0.3,1))
			end
		end
	end)

--[[
local names = oCache.Clip:getNames(oEditor.output.."nvjing.clip")
for i = 1,#names do
	local sp = CCSprite(oEditor.output.."nvjing.clip|"..names[i])
	sp.anchorPoint = oVec2.zero
	local target = CCRenderTarget(sp.contentSize.width,sp.contentSize.height)
	target:beginPaint(ccColor4(0))
	target:draw(sp)
	target:endPaint()
	target:save(names[i]..".png",CCImage.PNG)
end
]]

--CCDirector.displayStats = true
CCDirector:run(oEditor.scene)
