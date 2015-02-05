local CCDirector = require("CCDirector")
local CCLayerColor = require("CCLayerColor")
local ccColor4 = require("ccColor4")
local oVec2 = require("oVec2")

local function oViewArea()
	local winSize = CCDirector.winSize

	local view = CCLayerColor(ccColor4(0xff1a1a1a),winSize.width,winSize.height)
	view.anchor = oVec2.zero
	view:schedule(function()
		--view:resetColor(ccColor4(0xff00ffff),ccColor4(0xff0000ff),ccColor4(0xff00ff00),ccColor4(0xff000000))
		return true
	end)
	return view
end

return oViewArea
