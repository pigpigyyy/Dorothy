local CCLayerColor = require("CCLayerColor")
local ccColor4 = require("ccColor4")
local CCDirector = require("CCDirector")
local oVec2 = require("oVec2")
local CCLabelTTF = require("CCLabelTTF")
local CCDrawNode = require("CCDrawNode")
local oEvent = require("oEvent")
local CCSequence = require("CCSequence")
local oOpacity = require("oOpacity")
local CCCall = require("CCCall")
local CCNode = require("CCNode")
local oCache = require("oCache")
local oScale = require("oScale")
local oEase = require("oEase")
local oContent = require("oContent")
local oRoutine = require("oRoutine")
local once = require("once")
local wait = require("wait")
local seconds = require("seconds")

local _require = require
local loaded = {}
_G["require"] = function(name)
	local result = package.loaded[name]
	if not result then
		result = _require(name)
		table.insert(loaded,name)
	end
	return result
end

oContent:addSearchPath("ActionEditor/Script")

local oEditor = require("oEditor").oEditor

local bk = CCLayerColor(ccColor4(0xff000000),CCDirector.winSize.width,CCDirector.winSize.height)
bk.anchor = oVec2.zero
local logo = CCLabelTTF("LUV FIGHT","Arial",48)
logo.texture.antiAlias = false
logo.position = oVec2(CCDirector.winSize.width*0.5,CCDirector.winSize.height*0.5)
logo.scaleX = 0.3
logo.scaleY = 0.3
logo.opacity= 0
logo:runAction(oScale(0.3,1,1,oEase.OutBack))
logo:runAction(oOpacity(0.3,1,oEase.OutQuad))

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
flower.scaleX = 0.5
flower.scaleY = 0.5
flower.position = oVec2(logo.contentSize.width+2,logo.contentSize.height-2)
logo:addChild(flower)
oEditor.scene:addChild(bk,998)

local controls =
{
	"oViewArea",
	"oEditMenu",
	"oViewPanel",
	"oControlBar",
	"oSettingPanel",
}

local isUILoaded = false
oRoutine(once(function() -- load UI asynchronously
	for i = 1,#controls do
		local controlName = controls[i]
		controls[i] = require(controlName) -- load codes
		coroutine.yield()
		controls[i] = controls[i]() -- create instance
		controlName = controlName:sub(2,2):lower()..controlName:sub(3,-1)
		oEditor[controlName] = controls[i]
		coroutine.yield()
	end
	for i = 1,#controls do
		oEditor.scene:addChild(controls[i]) -- add to scene
		coroutine.yield()
	end
	local resPath = "ActionEditor/Model"
	local writePath = oContent.writablePath.."Model"
	if not oContent:exist(oContent.writablePath.."Model") and oContent:exist("ActionEditor/Model") then
		oContent:copyAsync(resPath,writePath) -- copy some prepared contents
		if not oContent:exist(oEditor.input) then
			oContent:mkdir(oEditor.input)
		end
		if not oContent:exist(oEditor.output) then
			oContent:mkdir(oEditor.output)
		end
	end
	coroutine.yield()
	oEditor.vertexControl = require("oVertexControl")() -- one more control to load
	coroutine.yield()
	oEditor.scene:addChild(oEditor.vertexControl)
	isUILoaded = true
end))

oRoutine(once(function() -- thread to wait UI loaded
	wait(seconds(1)) -- wait 1 second and let UI load
	wait(function() return not isUILoaded end) -- wait when UI has not been loaded yet
	oEvent:send("EditorLoaded")
	logo:runAction(CCSequence(
	{
		oOpacity(0.3,0),
		CCCall(
			function()
				bk.visible = false
				bk.parent:removeChild(bk)
				oEditor.scene.opacity = 0
				oEditor.scene:runAction(oOpacity(0.3,1))
			end),
	}))
end))

--[[
local names = oCache.Clip:getNames(oEditor.output.."nvjing.clip")
for i = 1,#names do
	local sp = CCSprite(oEditor.output.."nvjing.clip|"..names[i])
	sp.anchor = oVec2.zero
	local target = CCRenderTarget(sp.contentSize.width,sp.contentSize.height)
	target:beginPaint(ccColor4(0))
	target:draw(sp)
	target:endPaint()
	target:save(names[i]..".png",CCImage.PNG)
end
]]

--CCDirector.displayStats = true
oEditor.scene:registerEventHandler(function(eventType)
	if eventType == CCNode.Exited then
		_G["require"] = _require
		for _,name in ipairs(loaded) do
			package.loaded[name] = nil
		end
		for k,_ in pairs(oEditor.settingPanel.items) do
			oEditor.settingPanel.items[k] = nil
		end
		for k,_ in pairs(oEditor) do
			oEditor[k] = nil
		end
		oCache:clear()
	elseif eventType == CCNode.Cleanup then
		oContent:removeSearchPath("ActionEditor/Script")
	end
end)

CCDirector:run(oEditor.scene)
