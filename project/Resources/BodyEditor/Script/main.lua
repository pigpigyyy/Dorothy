collectgarbage("setpause", 100)
collectgarbage("setstepmul", 5000)

local _require = require
local loaded = {}
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
local oEditor = require("oEditor")
local oRoutine = require("oRoutine")
local once = oRoutine.once

oEditor.scene:registerEventHandler(function(eventType)
	if eventType == CCNode.Exited then
		require = _require
		for k,_ in pairs(loaded) do
			package.loaded[k] = nil
		end
	end
end)

local controls =
{
	"oViewArea",
	"oRuler",
	"oEditMenu",
	"oSettingPanel",
	"oViewPanel",
}

oRoutine(once(function()
	for _,name in ipairs(controls) do
		local createFunc = require(name)
		coroutine.yield()
		oEditor[name] = createFunc()
		coroutine.yield()
		oEditor.scene:addChild(oEditor[name])
		coroutine.yield()
	end
end))

CCDirector:run(oEditor.scene)