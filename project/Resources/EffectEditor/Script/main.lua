collectgarbage("setpause", 100)
collectgarbage("setstepmul", 5000)

local _require = require
local loaded = {} -- save loaded module names for end clean up
_G["require"] = function(modulename)
	local result = package.loaded[modulename]
	if not result then
		local name = "EffectEditor/Script/"..modulename
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
	"oEditMenu",
	"oSettingPanel",
	"oEditControl",
}

oRoutine(once(function()
	local oEditor = require("oEditor")
	oEditor:registerEventHandler(function(eventType)
		if eventType == CCNode.Exited then
			_G["require"] = _require
			for k,_ in pairs(loaded) do
				package.loaded[k] = nil
			end
		elseif eventType == CCNode.Cleanup then
			-- do editor cleanup
			oContent:setSearchPaths({})
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
	oContent:setSearchPaths({oEditor.input})

	local oFileChooser = require("oFileChooser")
	oEditor:addChild(oFileChooser(),oEditor.topMost)
end))
