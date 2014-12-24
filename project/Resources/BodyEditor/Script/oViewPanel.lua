local class,property = unpack(require("class"))
local CCSize = require("CCSize")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCDirector = require("CCDirector")
local oSettingItem = require("oSettingItem")
local oSelectionPanel = require("oSelectionPanel")

local oViewPanel = class(
{
	__partial = function(self)
		local winSize = CCDirector.winSize
		self._borderSize = CCSize(180,310*winSize.height/600)
		return oSelectionPanel(self._borderSize,false,true,true)
	end,

	__init = function(self)
		local winSize = CCDirector.winSize
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
		self.position = oVec2(winSize.width*0.5-100,winSize.height*0.5-halfBH-10)
		
		local function genPosY()
			local index = 0
			return function()
				local v = index
				index = index + 1
				return self._borderSize.height-10-30*v
			end
		end
		local getPosY = genPosY()
		
		local items =
		{
			Name = oSettingItem("Name :",0,getPosY(),true,
				function(self, enabled)
				end),
		}
		
		local contentHeight = 20
		for _,item in pairs(items) do
			contentHeight = contentHeight + 30
			menu:addChild(item)
		end
		self:reset(self._borderSize.width,contentHeight,0,50)
	end,
})

return oViewPanel
