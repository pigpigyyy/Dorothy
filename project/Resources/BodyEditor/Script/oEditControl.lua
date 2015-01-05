local CCDirector = require("CCDirector")
local CCMenu = require("CCMenu")
local oEditor = require("oEditor")
local oVec2 = require("oVec2")
local oButton = require("oButton")
local CCNode = require("CCNode")
local oSelectionPanel = require("oSelectionPanel")
local CCSize = require("CCSize")
local CCDrawNode = require("CCDrawNode")
local ccColor4 = require("ccColor4")
local oEditRuler = require("oEditRuler")
local CCLayer = require("CCLayer")
local oLine = require("oLine")
local CCTouch = require("CCTouch")

local function oEditControl()
	local winSize = CCDirector.winSize

	local editControl = CCNode()

	-- init switch --
	-- switchMenu
	local switchMenu = CCMenu(false)
	switchMenu.touchPriority = oEditor.touchPriorityEditControl
	switchMenu.anchor = oVec2.zero
	switchMenu.visible = false
	editControl:addChild(switchMenu)

	-- switchButton
	local switched = nil
	local switchValue = true
	local switchButton = oButton("Yes",16,50,50,winSize.width-225,95,function(button)
		switchValue = not switchValue
		button.text = switchValue and "Yes" or "No"
		if switched then
			switched(switchValue)
		end
	end)
	switchMenu:addChild(switchButton)

	-- show & hide switch
	editControl.showSwitch = function(self, defaultValue, callback)
		editControl:hide()
		switchMenu.visible = true
		switchValue = defaultValue
		switchButton.text = switchValue and "Yes" or "No"
		switched = callback
	end
	editControl.hideSwitch = function(self)
		switchMenu.visible = false
	end
	coroutine.yield()
	
	-- init type selector --
	-- typeSelector
	local typeSize = CCSize(120,190)
	local halfTW = typeSize.width*0.5
	local halfTH = typeSize.height*0.5
	local typeSelector = oSelectionPanel(typeSize)
	typeSelector.position = oEditor.origin-oVec2(winSize.width*0.5,winSize.height*0.5)
	typeSelector.visible = false
	
	-- typeBackground
	local typeBackground = CCDrawNode()
	typeBackground:drawPolygon(
	{
		oVec2(-halfTW,-halfTH),
		oVec2(halfTW,-halfTH),
		oVec2(halfTW,halfTH),
		oVec2(-halfTW,halfTH)
	},ccColor4(0xe5100000),0.5,ccColor4(0x88ffafaf))
	typeSelector.border:addChild(typeBackground,-1)
	
	-- typeMenuItems
	local typeSelected = nil
	local function typeCallback(button)
		editControl:hideTypeSelector()
		if typeSelected then
			typeSelected(button.text)
		end
	end
	typeSelector.menu:addChild(oButton("Dynamic",16,100,50,60,typeSize.height-35,typeCallback))
	typeSelector.menu:addChild(oButton("Static",16,100,50,60,typeSize.height-95,typeCallback))
	typeSelector.menu:addChild(oButton("Kinematic",16,100,50,60,typeSize.height-155,typeCallback))
	editControl:addChild(typeSelector)

	-- show & hide type selector
	editControl.showTypeSelector = function(self,callback)
		editControl:hide()
		typeSelector:show()
		typeSelected = callback
	end
	editControl.hideTypeSelector = function(self)
		if not typeSelector.visible then return end
		typeSelector:hide()
	end
	coroutine.yield()

	-- init edit ruler --
	-- editRuler
	local editRuler = oEditRuler()
	editControl:addChild(editRuler)

	-- show & hide edit ruler
	editControl.showEditRuler = function(self,default,min,max,indent,callback)
		editControl:hide()
		editRuler:show(default,min,max,indent,callback)
	end
	editControl.hideEditRuler = function(self)
		editRuler:hide()
	end
	coroutine.yield()

	-- init position editor --
	-- posEditor
	local posEditor = CCLayer()
	posEditor.visible = false
	editControl:addChild(posEditor)
	local posVisual = CCNode()
	posVisual:addChild(oLine(
	{
		oVec2(0,150),
		oVec2(-20,150),
		oVec2(0,190),
		oVec2(20,150),
		oVec2(0,150),
		oVec2.zero
	},ccColor4(0xffffffff)))
	posVisual:addChild(oLine(
	{
		oVec2.zero,
		oVec2(150,0),
		oVec2(150,20),
		oVec2(190,0),
		oVec2(150,-20),
		oVec2(150,0)
	},ccColor4(0xffffffff)))
	posEditor:addChild(posVisual)

	-- posEditor touch callback
	local totalDeltaPos = oVec2.zero
	local posChanged = nil
	posEditor:registerTouchHandler(function(eventType,touch)
		if eventType == CCTouch.Moved then
			local target = posVisual.transformTarget
			if not target or not target.parent then return false end
			if oEditor.isFixed then
				totalDeltaPos = totalDeltaPos + touch.delta/oEditor.scale
				if totalDeltaPos.x > 1 or totalDeltaPos.x < -1 then
					local posX = target.positionX+totalDeltaPos.x
					target.positionX = posX > 0 and math.floor(posX+0.5) or math.ceil(posX-0.5)
					totalDeltaPos.x = 0
				end
				if totalDeltaPos.y > 1 or totalDeltaPos.y < -1 then
					local posY = target.positionY+totalDeltaPos.y
					target.positionY = posY > 0 and math.floor(posY+0.5) or math.ceil(posY-0.5)
					totalDeltaPos.y = 0
				end
			else
				target.position = target.position + touch.delta/oEditor.scale
			end
			if posChanged then
				posChanged(target.position)
			end
		end
		return true
	end,false,oEditor.touchPriorityEditControl,true)

	-- show & hide position editor
	editControl.showPosEditor = function(self,target,callback)
		editControl:hide()
		posChanged = callback
		posEditor.visible = true
		posEditor.touchEnabled = true
		posVisual.transformTarget = target--oEditor:getItem("body")
		posVisual.rotation = -target.rotation
		totalDeltaPos = oVec2.zero
	end
	editControl.hidePosEditor = function(self)
		posEditor.touchEnabled = false
		posEditor.visible = false
	end
	coroutine.yield()

	-- init rotation editor --
	-- rotEditor
	local rotEditor = CCLayer()
	rotEditor.visible = false
	editControl:addChild(rotEditor)
	local rotVisual = CCNode()
	local vs = {}
	local num = 40
	for i = 0, num do
		local angle = 2*math.pi*i/num
		table.insert(vs,oVec2(200*math.cos(angle),200*math.sin(angle)))
	end
	rotVisual:addChild(oLine(vs,ccColor4()))
	rotVisual:addChild(oLine({oVec2(-200,0),oVec2(200,0)},ccColor4()))
	rotVisual:addChild(oLine({oVec2(0,-200),oVec2(0,200)},ccColor4()))
	rotEditor:addChild(rotVisual)

	-- rotEditor touch callback
	local rotCenter = oVec2.zero
	local rotChanged = nil
	local totalRot = 0
	rotEditor:registerTouchHandler(function(eventType,touch)
		if eventType == CCTouch.Moved then
			local target = rotVisual.transformTarget
			if not target or not target.parent then return false end
			local oldPos = touch.preLocation
			local newPos = touch.location
			local v1 = rotCenter - oldPos
			local v2 = rotCenter - newPos
			local len1 = v1.length
			local len2 = v2.length
			if len1 ~= 0 and len2 ~= 0 then
				local res = (v1.x*v2.x+v1.y*v2.y)/(len1*len2)
				if res > 1 then res = 1 end
				if res < -1 then res = -1 end
				local s = (oldPos.x*(newPos.y-rotCenter.y)-oldPos.y*(newPos.x-rotCenter.x)+(newPos.x*rotCenter.y-newPos.y*rotCenter.x))
				local delta = (s>0 and -1 or 1)*math.acos(res)*180/math.pi/oEditor.scale
				if oEditor.isFixed then
					totalRot = totalRot + delta
					if totalRot < 1 and totalRot > -1 then
						delta = 0
					else
						delta = totalRot > 0 and math.floor(totalRot) or math.ceil(totalRot)
						totalRot = 0
						local rotation = target.rotation + delta
						rotation = rotation > 0 and math.floor(rotation) or math.ceil(rotation)
						target.rotation = rotation
					end
				else
					target.rotation = target.rotation + delta
				end
				if rotChanged then
					rotChanged(target.rotation)
				end
			end
		end
		return true
	end,false,oEditor.touchPriorityEditControl,true)

	-- show & hide rotation editor
	editControl.showRotEditor = function(self,target,callback)
		editControl:hide()
		rotChanged = callback
		rotEditor.visible = true
		rotEditor.touchEnabled = true
		rotVisual.transformTarget = target--oEditor:getItem("body")
		rotCenter = target:convertToWorldSpace(oVec2.zero)
		totalRot = 0
	end
	editControl.hideRotEditor = function(self)
		rotEditor.touchEnabled = false
		rotEditor.visible = false
	end
	coroutine.yield()

	-- init size editor --
	-- sizeEditor
	local sizeEditor = CCLayer()
	sizeEditor.visible = false
	editControl:addChild(sizeEditor)
	local sizeVisual = CCNode()
	sizeVisual:addChild(oLine(
	{
		oVec2(0,150),
		oVec2(-20,150),
		oVec2(0,150),
		oVec2(20,150),
		oVec2(0,150),
		oVec2.zero
	},ccColor4()))
	sizeVisual:addChild(oLine(
	{
		oVec2.zero,
		oVec2(150,0),
		oVec2(150,20),
		oVec2(150,0),
		oVec2(150,-20),
		oVec2(150,0)
	},ccColor4()))
	sizeEditor:addChild(sizeVisual)
	
	-- sizeEditor touch callback
	local totalW = 0
	local totalH = 0
	local totalSize = CCSize.zero
	local sizeChanged = nil
	sizeEditor:registerTouchHandler(function(eventType,touch)
		if eventType == CCTouch.Moved then
			local target = sizeVisual.transformTarget
			if not target or not target.parent then return false end
			local delta = touch.delta
			if delta ~= oVec2.zero then
				local x2 = delta.x
				local y2 = delta.y
				local r = target.rotation*math.pi/180
				local x3 = x2*math.cos(r)-y2*math.sin(r)
				local y3 = x2*math.sin(r)+y2*math.cos(r)
				
				if oEditor.isFixed then
					totalW = totalW + x3/oEditor.scale
					totalH = totalH + y3/oEditor.scale
					if totalW > 1 or totalW < -1 then
						local w = totalSize.width+totalW
						totalSize.width = w > 0 and math.floor(w+0.5) or math.ceil(w-0.5)
						totalW = 0
					end
					if totalH > 1 or totalH < -1 then
						local h = totalSize.height+totalH
						totalSize.height = h > 0 and math.floor(h+0.5) or math.ceil(h-0.5)
						totalH = 0
					end
				else
					totalSize.width = totalSize.width + x3/oEditor.scale
					totalSize.height = totalSize.height + y3/oEditor.scale
				end
				if sizeChanged then
					sizeChanged(sizeVisual)
				end
			end
		end
		return true
	end,false,oEditor.touchPriorityEditControl,true)
	
	-- show & hide size editor
	editControl.showSizeEditor = function(self,target,size,callback)
		editControl:hide()
		totalSize = size
		sizeChanged = callback
		sizeEditor.visible = true
		sizeEditor.touchEnabled = true
		sizeVisual.transformTarget = target--oEditor:getItem("body")
		totalW = 0
		totalH = 0
	end
	editControl.hideSizeEditor = function(self)
		sizeEditor.touchEnabled = false
		sizeEditor.visible = false
	end
	coroutine.yield()
	
	-- hide all controls
	editControl.hide = function(self)
		editControl:hideSwitch()
		editControl:hideTypeSelector()
		editControl:hideEditRuler()
		editControl:hidePosEditor()
		editControl:hideRotEditor()
		editControl:hideSizeEditor()
	end

	--local value = 0
	--editControl:showEditRuler(value,0,1000,10,function(val) if value ~= val then value=val;print(value) end end)
	--editControl:showTypeSelector()
	--editControl:showRotEditor(oEditor:getItem("body1"),function(rot) print(rot) end)
	editControl:showSizeEditor(oEditor:getItem("body1"),oEditor.bodyData[2][oEditor.Rectangle.Size],function(visual)
		oEditor:resetItem(oEditor.bodyData[2])
		visual.transformTarget = oEditor:getItem("body1")
	end)
	return editControl
end

return oEditControl