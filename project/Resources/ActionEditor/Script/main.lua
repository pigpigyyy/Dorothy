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
		oEditor.scene:addChild(controls[i]) -- add to scene
		coroutine.yield()
	end
	oEditor.editMenu:toStart()
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
	coroutine.yield()

	local oFileChooser = require("oFileChooser")
	oFileChooser(true)
end))

--[[
local names = oCache.Clip:getNames(oEditor.output.."nvjing.clip")
for i = 1,#names do
	local sp = CCSprite(oEditor.output.."nvjing.clip|"..names[i])
	sp.anchor = oVec2.zero
	local target = CCRenderTarget(sp.contentSize.width,sp.contentSize.height)
	target:beginDraw(ccColor4(0))
	target:draw(sp)
	target:endDraw()
	target:save(names[i]..".png",CCImage.PNG)
end
]]

--CCDirector.displayStats = true
oEditor.scene.nodeHandler = function(eventType)
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
end

CCDirector:run(oEditor.scene)
