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
local oButton = require("oButton")
local ccColor3 = require("ccColor3")
local oScale = require("oScale")
local oEase = require("oEase")
local CCLabelTTF = require("CCLabelTTF")
local once = require("once")
local cycle = require("cycle")
local CCSequence = require("CCSequence")
local CCCall = require("CCCall")

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

	local layer = CCLayer()
	layer.contentSize = CCSize.zero
	layer.visible = false

	local menu = CCMenu(false)
	menu.items = nil
	menu.vs = nil
	menu.touchPriority = oEditor.touchPriorityEditControl+1
	menu.contentSize = CCSize.zero
	menu.transformTarget = oEditor.world
	menu.touchEnabled = false
	layer:addChild(menu)

	local label = CCLabelTTF("","Arial",16)
	label.color = ccColor3(0x00ffff)
	layer:addChild(label)
	
	local function setLabelPos(target)
		local pos = target.position
		label.text = string.format("%.2f",pos.x)..","..string.format("%.2f",pos.y)
		label.texture.antiAlias = false
		pos = target.parent:convertToWorldSpace(pos)
		pos = layer:convertToNodeSpace(pos)
		local scale = oEditor.world.parent.scaleX
		label.position = oVec2(pos.x,pos.y+45*scale)
	end

	label:slot("viewArea.toScale",function()
		label:schedule(once(function()
			cycle(0.5,function()
				if selectedVert then
					setLabelPos(selectedVert)
				end
			end)
		end))
	end)
	
	local function removeVertex()
		if selectedVert then
			local index = selectedVert.index
			local item
			menu:eachChild(function(child)
				child.enabled = true
				if child.index == index then
					child.index = nil
					item = child
				end
			end)
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
				menu.items[i].index = i
			end
			table.remove(menu.vs,index)
			selectedVert = nil
			label.text = ""
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
				selectedVert.opacity = 0.2
				selectedVert.highlighted = false
				selectedVert.selected = false
			end
			selectedVert = item
			setLabelPos(item)
			if item.highlighted then
				item.selected = true
			else
				item.opacity = 0.5
				item.highlighted = true
			end
			menu:eachChild(function(child)
				child.enabled = false
			end)
			item.enabled = true
		elseif eventType == CCMenuItem.Tapped then
			if vertexToAdd and lastCreateVertex and lastCreateVertex ~= item then
				return
			end
			if vertexToDel then
				removeVertex()
				return
			end
			item.selected = not item.selected
			selectedVert = item.selected and item or nil
			if not item.selected then label.text = "" end
			item.opacity = item.selected and 0.5 or 0.2
			item.highlighted = item.selected
			menu:eachChild(function(child)
				child.enabled = true
			end)
		end
	end
	local function oVertex(pos,index)
		local menuItem = CCMenuItem()
		menuItem.tapHandler = itemTapped
		menuItem.contentSize = CCSize(vertSize,vertSize)
		local circle = CCDrawNode()
		circle:drawDot(oVec2.zero,halfSize,ccColor4(0xff00ffff))
		circle.position = oVec2(halfSize,halfSize)
		menuItem:addChild(circle)
		menuItem.position = pos
		menuItem.opacity = 0.2
		menuItem.selected = false
		menuItem.index = index
		circle.scaleX = 0
		circle.scaleY = 0
		circle:runAction(oScale(0.5,1,1,oEase.OutBack))
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
	layer.touchPriority = oEditor.touchPriorityEditControl
	layer.touchHandler = function(eventType, touch)
		if eventType == CCTouch.Began then
			if vertexToAdd then
				local pos = menu:convertToNodeSpace(touch.location)
				if oEditor.isFixed then
					pos = oEditor:round(pos)
				end
				if pos ~= menu.vs[#menu.vs] then
					local item = addVertex(pos)
					setLabelPos(item)
					lastCreateVertex = item
				end
			end
			totalDelta = oVec2.zero
		elseif eventType == CCTouch.Moved then
			if touch.delta ~= oVec2.zero and selectedVert then
				selectedVert.selected = false
				local delta = menu:convertToNodeSpace(touch.location) - menu:convertToNodeSpace(touch.preLocation)
				if oEditor.fixX then delta.x = 0 end
				if oEditor.fixY then delta.y = 0 end
				local pos = selectedVert.position
				if oEditor.isFixed then
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
					setLabelPos(selectedVert)
					if vertChanged then
						vertChanged(menu.vs)
					end
				end
			end
		end
		return true
	end

	local mask = CCLayer()
	mask.contentSize = CCSize.zero
	mask.touchPriority = oEditor.touchPriorityEditControl+2
	mask.swallowTouches = true
	mask.touchHandler = function() return selectedVert ~= nil end
	layer:addChild(mask)
	
	local editMenu = CCMenu(false)
	editMenu.anchor = oVec2.zero
	editMenu.touchPriority = oEditor.touchPriorityEditControl-1
	editMenu.touchEnabled = false
	layer:addChild(editMenu)
	removeButton = oButton("-",20,50,50,winSize.width-465,winSize.height-35,function(button)	
		vertexToDel = not vertexToDel
		button.color = vertexToDel and ccColor3(0xff0080) or ccColor3(0x00ffff)
		if vertexToAdd then
			vertexToAdd = false
			addButton.color = ccColor3(0x00ffff)
		end
	end)
	editMenu:addChild(removeButton)
	addButton = oButton("+",20,50,50,winSize.width-525,winSize.height-35,function(button)
		vertexToAdd = not vertexToAdd
		button.color = vertexToAdd and ccColor3(0xff0080) or ccColor3(0x00ffff)
		if vertexToDel then
			vertexToDel = false
			removeButton.color = ccColor3(0x00ffff)
		end
	end)
	editMenu:addChild(addButton)
	
	layer.show = function(self,vs,pos,angle,callback)
		layer.touchEnabled = true
		mask.touchEnabled = true
		menu.touchEnabled = true
		editMenu.touchEnabled = true
		layer.visible = true
		menu.position = pos
		menu.angle = angle
		vs = vs or {}
		label.text = ""
		lastCreateVertex = nil
		selectedVert = nil
		vertexToAdd = false
		vertexToDel = false
		totalDelta = oVec2.zero
		addButton.color = ccColor3(0x00ffff)
		removeButton.color = ccColor3(0x00ffff)
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
	end

	return layer
end

return oVertexControl
