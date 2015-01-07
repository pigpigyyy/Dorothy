local CCMenuItem = require("CCMenuItem")
local CCSize = require("CCSize")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCMenu = require("CCMenu")
local CCDirector = require("CCDirector")
local CCLayer = require("CCLayer")
local oEditor = require("oEditor")
local CCTouch = require("CCTouch")

local function oVertexControl()
	local winSize = CCDirector.winSize
	local vertSize = 40
	local halfSize = vertSize*0.5
	local selectedVert = nil
	local function itemTapped(eventType,item)
		if eventType == CCMenuItem.TapBegan then
			if selectedVert and item ~= selectedVert then
				selectedVert.opacity = 0.2
				selectedVert.tag = 0
			end
			selectedVert = item
			if item.opacity == 0.5 then
				item.tag = 1
			else
				item.opacity = 0.5
			end
		elseif eventType == CCMenuItem.Tapped then
			item.tag = item.tag == 0 and 1 or 0
			selectedVert = item.tag == 1 and item or nil
			item.opacity = item.tag == 1 and 0.5 or 0.2
		end
	end
	local function oVertex(pos)
		local menuItem = CCMenuItem()
		menuItem:registerTapHandler(itemTapped)
		menuItem.contentSize = CCSize(vertSize,vertSize)
		local circle = CCDrawNode()
		circle:drawDot(oVec2.zero,halfSize,ccColor4(0xff00ffff))
		circle.position = oVec2(halfSize,halfSize)
		menuItem:addChild(circle)
		menuItem.position = pos
		menuItem.opacity = 0.2
		return menuItem
	end
	local layer = CCLayer()
	layer.contentSize = CCSize.zero
	layer.position = oVec2(winSize.width*0.5,winSize.height*0.5)

	local menu = CCMenu(false)
	menu.touchPriority = oEditor.touchPriorityEditControl+1
	menu.contentSize = CCSize.zero
	menu:addChild(oVertex(oVec2(-100,100)))
	menu:addChild(oVertex(oVec2(100,100)))
	menu:addChild(oVertex(oVec2(-100,-100)))
	menu:addChild(oVertex(oVec2(100,-100)))
	layer:addChild(menu)

	layer:registerTouchHandler(function(eventType, touch)
		if eventType == CCTouch.Moved then
			if selectedVert then
				selectedVert.tag = 0
				selectedVert.position = selectedVert.position + touch.delta
			end
		end
		return true
	end,false,oEditor.touchPriorityEditControl,false)
	layer.touchEnabled = true
	
	local mask = CCLayer()
	mask.contentSize = CCSize.zero
	mask:registerTouchHandler(function() return selectedVert ~= nil end,false,oEditor.touchPriorityEditControl+2,true)
	mask.touchEnabled = true
	layer:addChild(mask)
	
	layer.setVertices = function(self,vs)
		menu:removeAllChildrenWithCleanup()
		for i = 1,#vs do
			menu:addChild(oVertex(vs[i]))
		end
	end

	return layer
end

return oVertexControl