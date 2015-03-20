collectgarbage("setpause", 100)
collectgarbage("setstepmul", 5000)

local _require = require
local loaded = {} -- save loaded module names for end clean up
require = function(modulename)
	local result = package.loaded[modulename]
	if not result then
		local name = "BodyEditor/Script/"..modulename
		result = _require(name)
		if result then
			loaded[name] = true
		end
	end
	return result
end

local CCDirector = require("CCDirector")
local CCNode = require("CCNode")
local oContent = require("oContent")
local oRoutine = require("oRoutine")
local once = require("once")

local controls =
{
	"oViewArea",
	"oEditControl",
	"oVRuler",
	"oHRuler",
	"oEditMenu",
	"oSettingPanel",
	"oViewPanel",
}

oRoutine(once(function()
	local oEditor = require("oEditor")
	oEditor:registerEventHandler(function(eventType)
		if eventType == CCNode.Exited then
			require = _require
			for k,_ in pairs(loaded) do
				package.loaded[k] = nil
			end
		elseif eventType == CCNode.Cleanup then
			oEditor:clearData()
		end
	end)
	CCDirector:run(oEditor)
	coroutine.yield()
	for index,name in ipairs(controls) do
		local createFunc = require(name)
		coroutine.yield()
		oEditor[name] = createFunc() -- keep lua reference for control items
		coroutine.yield()
		oEditor:addChild(oEditor[name],index)
		coroutine.yield()
	end
	local resPath = "BodyEditor/Body"
	local writePath = oContent.writablePath.."Body"
	if not oContent:exist(oContent.writablePath.."Body") and oContent:exist("BodyEditor/Body") then
		oContent:copyAsync(resPath,writePath)
		if not oContent:exist(oEditor.input) then
			oContent:mkdir(oEditor.input)
		end
		if not oContent:exist(oEditor.output) then
			oContent:mkdir(oEditor.output)
		end
	end
	local oFileChooser = require("oFileChooser")
	coroutine.yield()
	oEditor:addChild(oFileChooser(),oEditor.topMost)
	
	local CCUserDefault = require("CCUserDefault")
	local oVec2 = require("oVec2")
	if CCUserDefault.G == "" then
		CCUserDefault.G = -10
		
	end
	oEditor.world.gravity = oVec2(0,CCUserDefault.G)
	--dofile("BodyEditor/Script/generateLoader.lua")
end))
