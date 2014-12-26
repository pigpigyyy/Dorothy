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
local oEditor = require("oEditor")
local oRoutine = require("oRoutine")
local once = oRoutine.once

oEditor:registerEventHandler(function(eventType)
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
	"oVRuler",
	"oHRuler",
	"oEditMenu",
	"oSettingPanel",
	"oViewPanel",
}

oRoutine(once(function()
	for _,name in ipairs(controls) do
		local createFunc = require(name)
		coroutine.yield()
		oEditor[name] = createFunc() -- keep lua reference for control items
		coroutine.yield()
		oEditor:addChild(oEditor[name])
		coroutine.yield()
	end
end))

CCDirector:run(oEditor)