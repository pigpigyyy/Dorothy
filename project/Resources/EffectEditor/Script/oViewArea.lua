local CCDirector = require("CCDirector")
local CCLayerColor = require("CCLayerColor")
local ccColor4 = require("ccColor4")
local oVec2 = require("oVec2")

local function oViewArea()
	local winSize = CCDirector.winSize

	local view = CCLayerColor(ccColor4(0xff1a1a1a),winSize.width,winSize.height)
	view.anchor = oVec2.zero
	view.cascadeOpacity = true

	return view
end

return oViewArea
