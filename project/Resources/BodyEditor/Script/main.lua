local CCScene = require("CCScene")
local CCDirector = require("CCDirector")
local CCNode = require("CCNode")

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

local layer = require("oViewArea")()
local scene = require("oEditor").scene
scene:registerEventHandler(function(eventType)
	if eventType == CCNode.Exit then
		require = _require
		for k,_ in pairs(loaded) do
			package.loaded[k] = nil
		end
	end
end)
scene:addChild(layer)
CCDirector:run(scene)
