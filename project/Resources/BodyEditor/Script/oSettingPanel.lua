local class,property = unpack(require("class"))
local oSelectionPanel = require("oSelectionPanel")
local CCSize = require("CCSize")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")

local oSettingPanel = class(
{
	__partial = function(self)
		self._borderSize = CCSize(180,310)
		return oSelectionPanel(self._borderSize,false,true)
	end,
	__init = function(self)
		local menu = self.menu
		local border = self.border
		local halfBW = self._borderSize.width*0.5
		local halfBH = self._borderSize.height*0.5
		local background= CCDrawNode()
		background:drawPolygon(
		{
			oVec2(-halfBW,-halfBH),
			oVec2(halfBW,-halfBH),
			oVec2(halfBW,halfBH),
			oVec2(-halfBW,halfBH)
		},ccColor4(0xe5100000),0.5,ccColor4(0x88ffafaf))
		border:addChild(background,-1)
		self:show()
		self.position = oVec2(300,0)
	end,
})

return oSettingPanel
