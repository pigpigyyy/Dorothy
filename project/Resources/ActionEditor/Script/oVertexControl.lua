local CCMenuItem = require("CCMenuItem")
local CCSize = require("CCSize")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCMenu = require("CCMenu")
local CCDirector = require("CCDirector")
local CCLayer = require("CCLayer")
local oEditor = require("oEditor").oEditor
local CCTouch = require("CCTouch")
local oButton = require("oButton")
local ccColor3 = require("ccColor3")
local oScale = require("oScale")
local oEase = require("oEase")
local CCLabelTTF = require("CCLabelTTF")
local CCSequence = require("CCSequence")
local CCCall = require("CCCall")
local oLine = require("oLine")

local function oVertexControl()
	local winSize = CCDirector.winSize
	local vertSize = 40
	local halfSize = vertSize*0.5
	local vertChanged = nil
	local selectedVert = nil
	local vertexToAdd = false
	local vertexToDel = false
	local addButton = nil
	local removeButton = nil
	local lastCreateVertex = nil
	local viewNode = oEditor.viewArea.viewNode

	local layer = CCLayer()
	layer.contentSize = CCSize.zero
	layer.visible = false

	local menu = CCMenu(false)
	menu.items = nil
	menu.vs = nil
	menu.touchPriority = CCMenu.DefaultHandlerPriority+1
	menu.contentSize = CCSize.zero
	menu.transformTarget = viewNode
	menu.touchEnabled = false
	layer:addChild(menu)
	
	local function removeVertex()
		if selectedVert then
			local index = selectedVert.index
			local item
			local children = menu.children
			for i = 1,children.count do
				local child = children[i]
				child.enabled = true
				if child.index == index then
					child.index = nil
					item = child
				end
			end
			item.enabled = false
			item:runAction(CCSequence(
			{
				oScale(0.3,0,0,oEase.OutQuad),
				CCCall(function()
					item.parent:removeChild(item)
				end)
			}))
			table.remove(menu.items,index)
			for i = 1,#menu.items do
				local menuItem = menu.items[i]
				menuItem.index = i
				local text
				if i == 1 then
					text = "bullet"
				elseif i == 2 then
					text = "attack"
				elseif i == 3 then
					text = "hit"
				else
					text = tostring(i)
				end
				menuItem.label.text = text
				menuItem.label.texture.antiAlias = false
			end
			table.remove(menu.vs,index)
			selectedVert = nil
			if vertChanged then
				vertChanged(menu.vs)
			end
		end
	end

	local function itemTapped(eventType,item)
		if eventType == CCMenuItem.TapBegan then
			if selectedVert and item ~= selectedVert then
				if vertexToAdd and lastCreateVertex and lastCreateVertex ~= item then
					return
				end
				selectedVert.opacity = 0.4
				selectedVert.selected = false
			end
			selectedVert = item
			if item.opacity == 0.8 then
				item.selected = true
			else
				item.opacity = 0.8
			end
			local children = menu.children
			for i = 1,children.count do
				children[i].enabled = false
			end
			item.enabled = true
		elseif eventType == CCMenuItem.Tapped then
			if vertexToAdd and lastCreateVertex and lastCreateVertex ~= item then
				return
			end
			if vertexToDel and selectedVert and selectedVert.index == menu.items[#menu.items].index then
				removeVertex()
				return
			end
			item.selected = not item.selected
			selectedVert = item.selected and item or nil
			item.opacity = item.selected and 0.8 or 0.4
			local children = menu.children
			for i = 1,children.count do
				children[i].enabled = true
			end
		end
	end
	local function oVertex(pos,index)
		local menuItem = CCMenuItem()
		menuItem:registerTapHandler(itemTapped)
		menuItem.contentSize = CCSize(vertSize,vertSize)
		menuItem.opacity = 0.4
		menuItem.position = pos
		menuItem.index = index

		local circle = CCDrawNode()
		circle:drawDot(oVec2.zero,20,ccColor4(0xff00ffff))
		circle:addChild(oLine({oVec2(-10,0),oVec2(10,0)},ccColor4()))
		circle:addChild(oLine({oVec2(0,10),oVec2(0,-10)},ccColor4()))
		circle.position = oVec2(halfSize,halfSize)
		circle.scaleX = 0
		circle.scaleY = 0
		circle:runAction(oScale(0.5,1,1,oEase.OutBack))
		menuItem:addChild(circle)

		local text
		if index == 1 then
			text = "bullet"
		elseif index == 2 then
			text = "attack"
		elseif index == 3 then
			text = "hit"
		else
			text = tostring(index)
		end
		local label = CCLabelTTF(text,"Arial",16)
		label.texture.antiAlias = false
		label.color = ccColor3(0x00ffff)
		label.position = oVec2(0,45)
		circle:addChild(label)
		menuItem.label = label
		return menuItem
	end

	local function setVertices(vs)
		menu:removeAllChildrenWithCleanup()
		menu.vs = vs
		menu.items = {}
		for i = 1,#vs do
			local item = oVertex(vs[i],i)
			table.insert(menu.items,item)
			menu:addChild(item)
		end
	end
	
	local function addVertex(v)
		local item = oVertex(v,#(menu.items)+1)
		table.insert(menu.items,item)
		menu:addChild(item)
		table.insert(menu.vs,v)
		if vertChanged then
			vertChanged(menu.vs)
		end
		return item
	end

	local totalDelta = oVec2.zero
	layer:registerTouchHandler(function(eventType, touch)
		if eventType == CCTouch.Began then
			if vertexToAdd then
				local pos = menu:convertToNodeSpace(touch.location)
				if oEditor.viewArea.isValueFixed then
					pos = oEditor:round(pos)
				end
				if pos ~= menu.vs[#menu.vs] then
					local item = addVertex(pos)
					lastCreateVertex = item
				end
			end
			totalDelta = oVec2.zero
		elseif eventType == CCTouch.Moved then
			if touch.delta ~= oVec2.zero and selectedVert then
				selectedVert.selected = false
				local delta = menu:convertToNodeSpace(touch.location) - menu:convertToNodeSpace(touch.preLocation)
				local pos = selectedVert.position
				if oEditor.viewArea.isValueFixed then
					totalDelta = totalDelta + delta
					if totalDelta.x > 1 or totalDelta.x < -1 then
						local posX = pos.x+totalDelta.x
						pos.x = oEditor:round(posX)
						totalDelta.x = 0
					end
					if totalDelta.y > 1 or totalDelta.y < -1 then
						local posY = pos.y+totalDelta.y
						pos.y = oEditor:round(posY)
						totalDelta.y = 0
					end
				else
					pos = pos + delta
				end
				if pos ~= selectedVert.position then
					selectedVert.position = pos
					menu.vs[selectedVert.index] = pos
					if vertChanged then
						vertChanged(menu.vs)
					end
				end
			end
		end
		return true
	end,false,CCMenu.DefaultHandlerPriority,false)
	
	local mask = CCLayer()
	mask.contentSize = CCSize.zero
	mask:registerTouchHandler(function() return selectedVert ~= nil end,false,CCMenu.DefaultHandlerPriority+2,true)
	layer:addChild(mask)

	local editMenu = CCMenu(false)
	editMenu.anchor = oVec2.zero
	editMenu.touchPriority = CCMenu.DefaultHandlerPriority
	editMenu.touchEnabled = false
	layer:addChild(editMenu)
	removeButton = oButton("-",20,50,50,winSize.width-325,winSize.height-35,function(button)	
		vertexToDel = not vertexToDel
		button.color = vertexToDel and ccColor3(0xff0080) or ccColor3(0x00ffff)
		if vertexToAdd then
			vertexToAdd = false
			addButton.color = ccColor3(0x00ffff)
		end
	end)
	editMenu:addChild(removeButton)
	addButton = oButton("+",20,50,50,winSize.width-385,winSize.height-35,function(button)
		vertexToAdd = not vertexToAdd
		button.color = vertexToAdd and ccColor3(0xff0080) or ccColor3(0x00ffff)
		if vertexToDel then
			vertexToDel = false
			removeButton.color = ccColor3(0x00ffff)
		end
	end)
	editMenu:addChild(addButton)

	layer.show = function(self,vs,callback)
		layer.touchEnabled = true
		mask.touchEnabled = true
		menu.touchEnabled = true
		editMenu.touchEnabled = true
		layer.visible = true
		vs = vs or {}
		lastCreateVertex = nil
		selectedVert = nil
		vertexToAdd = false
		totalDelta = oVec2.zero
		addButton.color = ccColor3(0x00ffff)
		setVertices(vs)
		vertChanged = callback
		addButton:stopAllActions()
		addButton.scaleX = 0
		addButton.scaleY = 0
		addButton:runAction(oScale(0.5,1,1,oEase.OutBack))
		removeButton:stopAllActions()
		removeButton.scaleX = 0
		removeButton.scaleY = 0
		removeButton:runAction(oScale(0.5,1,1,oEase.OutBack))
	end
	layer.hide = function(self)
		if not layer.visible then return end
		vertChanged = nil
		selectedVert = nil
		menu.items = {}
		menu.vs = {}
		menu:removeAllChildrenWithCleanup()
		layer.touchEnabled = false
		mask.touchEnabled = false
		menu.touchEnabled = false
		editMenu.touchEnabled = false
		layer.visible = false
		oEditor.dirty = true
		oEditor.viewArea:getModel()
	end

	return layer
end

return oVertexControl
