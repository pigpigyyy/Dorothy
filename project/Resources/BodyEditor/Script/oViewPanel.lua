local class,property = unpack(require("class"))
local CCSize = require("CCSize")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCDirector = require("CCDirector")
local oSettingItem = require("oSettingItem")
local oSelectionPanel = require("oSelectionPanel")
local oViewItem = require("oViewItem")
local oEvent = require("oEvent")
local CCDictionary = require("CCDictionary")
local oListener = require("oListener")

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
		
		local function selectCallback(item)
			oEvent:send("viewPanel.choose",item)
		end
		local items =
		{
			Name = oViewItem("Rectangle","WWWWWWWW",90,getPosY(),selectCallback),
			Name1 = oViewItem("SubPolygon",1,90,getPosY(),selectCallback),
			Name2 = oViewItem("SubCircle",2,90,getPosY(),selectCallback),
			Name3 = oViewItem("Loop","body2",90,getPosY(),selectCallback),
			Name4 = oViewItem("Chain"," ",90,getPosY(),selectCallback),
			Name5 = oViewItem("SubRectangle",1,90,getPosY(),selectCallback),
			Name6 = oViewItem("Circle"," ",90,getPosY(),selectCallback),
			Name7 = oViewItem("Pulley","joint1",90,getPosY(),selectCallback),
			Name8 = oViewItem("Weld","joint2",90,getPosY(),selectCallback),
		}
		
		local contentHeight = 10
		for _,item in pairs(items) do
			contentHeight = contentHeight + 50
			menu:addChild(item)
		end
		self:reset(self._borderSize.width,contentHeight,0,50)
		
		self.data = CCDictionary()
		local currentItem = nil
		self.data.chooseListener = oListener("viewPanel.choose",function(item)
			if item == nil then
				if currentItem then
					currentItem.selected = false
				end
				currentItem = nil
			elseif item.selected then
				if currentItem then
					currentItem.selected = false
				end
				currentItem = item
			else
				currentItem = nil
			end
		end)
	end,
})

return oViewPanel
