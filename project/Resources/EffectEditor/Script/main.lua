local _require = require
local loaded = {} -- save loaded module names for end clean up
_G["require"] = function(name)
	local result = package.loaded[name]
	if not result then
		result = _require(name)
		table.insert(loaded,name)
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
	"oEditMenu",
	"oSettingPanel",
	"oEditControl",
	"oFrameViewer",
}

oRoutine(once(function()
	oContent:addSearchPath("EffectEditor/Script")

	local oEditor = require("oEditor")
	oEditor:slots("Exited",function()
		_G["require"] = _require
		for _,name in ipairs(loaded) do
			package.loaded[name] = nil
		end
	end)
	oEditor:slots("Cleanup",function()
		-- do editor cleanup
		oContent:removeSearchPath("EffectEditor/Script")
		oContent:removeSearchPath(oEditor.input)
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
	local resPath = "EffectEditor/Effect"
	local writePath = oContent.writablePath.."Effect"
	if not oContent:exist(oContent.writablePath.."Effect") and oContent:exist("EffectEditor/Effect") then
		oContent:copyAsync(resPath,writePath)
	end
	if not oContent:exist(oEditor.input) then
		oContent:mkdir(oEditor.input)
	end
	if not oContent:exist(oEditor.output) then
		oContent:mkdir(oEditor.output)
	end
	oContent:addSearchPath(oEditor.input)

	local oFileChooser = require("oFileChooser")
	oEditor:addChild(oFileChooser(),oEditor.topMost)
end))
