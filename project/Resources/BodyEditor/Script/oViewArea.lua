local CCDirector = require("CCDirector")
local CCLayerColor = require("CCLayerColor")
local ccColor4 = require("ccColor4")
local oVec2 = require("oVec2")

local function oViewArea()
	local winSize = CCDirector.winSize
	local layer = CCLayerColor(ccColor4(0xff1a1a1a),winSize.width, winSize.height)
	layer.anchor = oVec2.zero
	layer.cascadeOpacity = true
	return layer
end

return oViewArea