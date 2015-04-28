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
}

oRoutine(once(function()
	oContent:setSearchPaths({"Lib","EffectEditor/Script"})

	local oEditor = require("oEditor")
	oEditor:registerEventHandler(function(eventType)
		if eventType == CCNode.Exited then
			_G["require"] = _require
			for _,name in ipairs(loaded) do
				package.loaded[name] = nil
			end
		elseif eventType == CCNode.Cleanup then
			-- do editor cleanup
			oContent:setSearchPaths({"Lib"})
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
	oContent:setSearchPaths({"Lib","EffectEditor/Script",oEditor.input})
	
	local oFileChooser = require("oFileChooser")
	oEditor:addChild(oFileChooser(),oEditor.topMost)
end))
