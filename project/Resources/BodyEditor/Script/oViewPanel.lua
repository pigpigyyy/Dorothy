local class,property = unpack(require("class"))
local CCSize = require("CCSize")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCDirector = require("CCDirector")
local oSettingItem = require("oSettingItem")
local oSelectionPanel = require("oSelectionPanel")
local oViewItem = require("oViewItem")

local oViewPanel = class(
{
	__partial = function(self)
		local winSize = CCDirector.winSize
		self._borderSize = CCSize(180,310*(winSize.height-30)/(600-30))
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
				return self._borderSize.height-30-50*v
			end
		end
		local getPosY = genPosY()
		
		local items =
		{
			Name = oViewItem("Rectangle","WWWWWWWW",90,getPosY(),
				function(item)
					return true
				end),
			Name1 = oViewItem("Polygon","WWWWWWWW",90,getPosY(),
				function(item)
				end),
			Name2 = oViewItem("Circle"," ",90,getPosY(),
				function(item)
				end),
			Name3 = oViewItem("Loop"," ",90,getPosY(),
				function(item)
				end),
			Name4 = oViewItem("Chain"," ",90,getPosY(),
				function(item)
				end),
			Name5 = oViewItem("Rectangle"," ",90,getPosY(),
				function(item)
				end),
			Name6 = oViewItem("Circle"," ",90,getPosY(),
				function(item)
				end),
			Name7 = oViewItem("Loop"," ",90,getPosY(),
				function(item)
				end),
			Name8 = oViewItem("Chain"," ",90,getPosY(),
				function(item)
				end),
		}
		
		local contentHeight = 10
		for _,item in pairs(items) do
			contentHeight = contentHeight + 50
			menu:addChild(item)
		end
		self:reset(self._borderSize.width,contentHeight,0,50)
	end,
})

return oViewPanel
