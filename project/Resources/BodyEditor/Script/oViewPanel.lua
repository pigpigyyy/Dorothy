local CCSize = require("CCSize")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCDirector = require("CCDirector")
local oSelectionPanel = require("oSelectionPanel")
local oViewItem = require("oViewItem")
local oEvent = require("oEvent")
local CCDictionary = require("CCDictionary")
local oListener = require("oListener")
local oEditor = require("oEditor")

local function oViewPanel()
	local winSize = CCDirector.winSize
	local borderSize = CCSize(180,310*(winSize.height-30)/(600-30))
	local self = oSelectionPanel(borderSize,false,true,true)
	self.touchPriority = oEditor.touchPriorityViewPanel
	local menu = self.menu
	menu.touchPriority = oEditor.touchPriorityViewPanel+1
	local border = self.border
	local halfBW = borderSize.width*0.5
	local halfBH = borderSize.height*0.5
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
			return borderSize.height-30-50*v
		end
	end

	local function selectCallback(item)
		oEditor.currentData = item.dataItem
		oEvent:send("viewPanel.choose",item)
		oEvent:send("settingPanel.toState",item.dataItem[0])
	end
	
	local function updateViewItems(bodyData)
		local items = {}
		local getPosY = genPosY()
		for _,data in ipairs(bodyData) do
			local item = oViewItem(data[0],data[1],90,getPosY(),selectCallback)
			item.dataItem = data
			table.insert(items,item)
			local subShapeIndex = oEditor[data[0]].SubShapes
			if subShapeIndex and data[subShapeIndex] then
				for index,subShape in ipairs(data[subShapeIndex]) do
					local item = oViewItem(subShape[0],index,90,getPosY(),selectCallback)
					item.dataItem = subShape
					item.parentData = data
					table.insert(items,item)
				end
			end
		end
		local contentHeight = 10
		menu:removeAllChildrenWithCleanup()
		for _,item in ipairs(items) do
			contentHeight = contentHeight + 50
			menu:addChild(item)
		end
		self.items = items
		self:reset(borderSize.width,contentHeight,0,50)
	end
	updateViewItems(oEditor.bodyData)

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
	self.data.bodyDataListener = oListener("editor.bodyData",function(bodyData)
		updateViewItems(bodyData)
	end)

	return self
end

return oViewPanel
