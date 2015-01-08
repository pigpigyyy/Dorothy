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
local ccColor3 = require("ccColor3")
local CCDictionary = require("CCDictionary")
local oListener = require("oListener")
local oBodyDef = require("oBodyDef")
local oEvent = require("oEvent")
local oVertexControl = require("oVertexControl")
local oScale = require("oScale")
local oEase = require("oEase")

local function oEditControl()
	local winSize = CCDirector.winSize

	local editControl = CCNode()

	-- init fix menu --
	local fixMenu = CCMenu(false)
	fixMenu.touchPriority = oEditor.touchPriorityEditControl-1
	fixMenu.anchor = oVec2.zero
	fixMenu.visible = false
	fixMenu.touchEnabled = false
	editControl:addChild(fixMenu)
	local fixX = false
	local fixY = false
	local fixXButton,fixYButton
	fixXButton = oButton("",0,50,50,winSize.width-405,winSize.height-35,function(button)
		if fixY then
			fixY = false
			oEditor.fixY = fixY
			fixYButton.color = ccColor3(0x00ffff)
		end
		fixX = not fixX
		button.color = fixX and ccColor3(0xff0080) or ccColor3(0x00ffff)
		oEditor.fixX = fixX
	end)
	fixMenu:addChild(fixXButton)
	fixYButton = oButton("",0,50,50,winSize.width-345,winSize.height-35,function(button)
		if fixX then
			fixX = false
			oEditor.fixX = false
			fixXButton.color = ccColor3(0x00ffff)
		end
		fixY = not fixY
		button.color = fixY and ccColor3(0xff0080) or ccColor3(0x00ffff)
		oEditor.fixY = fixY
	end)
	fixMenu:addChild(fixYButton)
	local function createArrowForButton(button,rotation)
		local fixNode = CCNode()
		fixNode.cascadeColor = false
		fixNode:addChild(oLine(
		{
			oVec2(-15,0),
			oVec2(15,0),
			oVec2(10,5),
			oVec2(15,0),
			oVec2(10,-5),
			oVec2(15,0),
			oVec2(-15,0),
		},ccColor4(0xaaff0080)))
		button.face:addChild(oLine(
		{
			oVec2(25,25),
			oVec2(20,30),
			oVec2(25,25),
			oVec2(30,30),
			oVec2(25,25),
			oVec2(30,20),
			oVec2(25,25),
			oVec2(20,20),
			oVec2(25,25),
		},ccColor4(0xaaffffff)))
		fixNode.scaleX = 1.2
		fixNode.scaleY = 1.2
		fixNode.position = oVec2(25,25)
		fixNode.rotation = rotation
		button.face:addChild(fixNode)
	end
	createArrowForButton(fixXButton,0)
	createArrowForButton(fixYButton,-90)
	editControl.showFixButtons = function(self)
		fixX = false
		oEditor.fixX = false
		fixXButton.color = ccColor3(0x00ffff)
		fixXButton:stopAllActions()
		fixXButton.scaleX = 0
		fixXButton.scaleY = 0
		fixXButton:runAction(oScale(0.5,1,1,oEase.OutBack))
		fixY = false
		oEditor.fixY = false
		fixYButton.color = ccColor3(0x00ffff)
		fixYButton:stopAllActions()
		fixYButton.scaleX = 0
		fixYButton.scaleY = 0
		fixYButton:runAction(oScale(0.5,1,1,oEase.OutBack))
		fixMenu.visible = true
		fixMenu.touchEnabled = true
	end
	editControl.hideFixButtons = function(self)
		if not fixMenu.visible then return end
		fixMenu.visible = false
		fixMenu.touchEnabled = false
	end

	-- init switch --
	-- switchMenu
	local switchMenu = CCMenu(false)
	switchMenu.touchPriority = oEditor.touchPriorityEditControl
	switchMenu.anchor = oVec2.zero
	switchMenu.visible = false
	switchMenu.touchEnabled = false
	editControl:addChild(switchMenu)

	-- switchButton
	local switched = nil
	local switchValue = true
	local switchButton = oButton("true",16,50,50,winSize.width-345,winSize.height-35,function(button)
		switchValue = not switchValue
		button.text = tostring(switchValue)
		if switched then
			switched(switchValue)
		end
	end)
	switchMenu:addChild(switchButton)

	-- show & hide switch
	editControl.showSwitch = function(self, defaultValue, callback)
		editControl:hide()
		switchMenu.visible = true
		switchMenu.touchEnabled = true
		switchValue = defaultValue
		switchButton.text = tostring(switchValue)
		switchButton:stopAllActions()
		switchButton.scaleX = 0
		switchButton.scaleY = 0
		switchButton:runAction(oScale(0.5,1,1,oEase.OutBack))
		switched = callback
	end
	editControl.hideSwitch = function(self)
		if not switchMenu.visible then return end
		switchMenu.visible = false
		switchMenu.touchEnabled = false
	end
	
	-- init type selector --
	-- typeSelector
	local typeSize = CCSize(120,190)
	local halfTW = typeSize.width*0.5
	local halfTH = typeSize.height*0.5
	local typeSelector = oSelectionPanel(typeSize,true,true,false)
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
			typeSelected(oBodyDef[button.text])
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
		if not editRuler.visible then return end
		editRuler:hide()
	end

	-- world node --
	local worldNode = oEditor.worldNode

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
	},ccColor4()))
	posVisual:addChild(oLine(
	{
		oVec2.zero,
		oVec2(150,0),
		oVec2(150,20),
		oVec2(190,0),
		oVec2(150,-20),
		oVec2(150,0)
	},ccColor4()))
	posVisual.transformTarget = oEditor.world
	posEditor:addChild(posVisual)

	-- posEditor touch callback
	local totalDeltaPos = oVec2.zero
	local posChanged = nil
	posEditor:registerTouchHandler(function(eventType,touch)
		if eventType == CCTouch.Moved then
			local delta = touch.delta
			if fixX then delta.x = 0 end
			if fixY then delta.y = 0 end
			if oEditor.isFixed then
				totalDeltaPos = totalDeltaPos + delta/oEditor.scale
				if totalDeltaPos.x > 1 or totalDeltaPos.x < -1 then
					local posX = posVisual.positionX+totalDeltaPos.x
					posVisual.positionX = posX > 0 and math.floor(posX+0.5) or math.ceil(posX-0.5)
					totalDeltaPos.x = 0
				end
				if totalDeltaPos.y > 1 or totalDeltaPos.y < -1 then
					local posY = posVisual.positionY+totalDeltaPos.y
					posVisual.positionY = posY > 0 and math.floor(posY+0.5) or math.ceil(posY-0.5)
					totalDeltaPos.y = 0
				end
			else
				posVisual.position = posVisual.position + delta/oEditor.scale
			end
			if posChanged then
				posChanged(posVisual.position)
			end
		end
		return true
	end,false,oEditor.touchPriorityEditControl,true)

	-- show & hide position editor
	editControl.showPosEditor = function(self,pos,callback)
		editControl:hide()
		editControl:showFixButtons()
		posChanged = callback
		posEditor.visible = true
		posEditor.touchEnabled = true
		posVisual.position = pos
		totalDeltaPos = oVec2.zero
	end
	editControl.hidePosEditor = function(self)
		if not posEditor.visible then return end
		editControl:hideFixButtons()
		posEditor.touchEnabled = false
		posEditor.visible = false
	end

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
	rotVisual.transformTarget = oEditor.world
	rotEditor:addChild(rotVisual)

	-- rotEditor touch callback
	local rotCenter = oVec2.zero
	local rotChanged = nil
	local totalRot = 0
	rotEditor:registerTouchHandler(function(eventType,touch)
		if eventType == CCTouch.Moved then
			local oldPos = rotVisual:convertToNodeSpace(touch.preLocation)
			local newPos = rotVisual:convertToNodeSpace(touch.location)
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
						local rotation = rotVisual.rotation + delta
						rotation = rotation > 0 and math.floor(rotation) or math.ceil(rotation)
						rotVisual.rotation = rotation
					end
				else
					rotVisual.rotation = rotVisual.rotation + delta
				end
				if rotChanged then
					rotChanged(rotVisual.rotation)
				end
			end
		end
		return true
	end,false,oEditor.touchPriorityEditControl,true)

	-- show & hide rotation editor
	editControl.showRotEditor = function(self,data,callback)
		editControl:hide()
		rotChanged = callback
		rotEditor.visible = true
		rotEditor.touchEnabled = true
		rotVisual.position = data.parent and data.parent:get("Position") or data:get("Position")
		rotVisual.rotation = data:get("Angle")
		rotCenter = (data.parent and data:has("Center")) and data:get("Center") or oVec2.zero
		totalRot = 0
	end
	editControl.hideRotEditor = function(self)
		if not rotEditor.visible then return end
		rotEditor.touchEnabled = false
		rotEditor.visible = false
	end

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
	sizeVisual.transformTarget = worldNode
	sizeEditor:addChild(sizeVisual)
	
	-- sizeEditor touch callback
	local totalW = 0
	local totalH = 0
	local totalSize = CCSize.zero
	local sizeChanged = nil
	sizeEditor:registerTouchHandler(function(eventType,touch)
		if eventType == CCTouch.Moved then
			local delta = touch.delta
			if delta ~= oVec2.zero then
				local x2 = delta.x
				local y2 = delta.y
				local r = sizeVisual.rotation*math.pi/180
				local x3 = x2*math.cos(r)-y2*math.sin(r)
				local y3 = x2*math.sin(r)+y2*math.cos(r)
				if fixX then x3 = 0 end
				if fixY then y3 = 0 end
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
				if totalSize.width < 10 then totalSize.width = 10 end
				if totalSize.height < 10 then totalSize.height = 10 end
				if sizeChanged then
					sizeChanged(totalSize)
				end
			end
		end
		return true
	end,false,oEditor.touchPriorityEditControl,true)
	
	-- show & hide size editor
	editControl.showSizeEditor = function(self,target,center,size,callback)
		editControl:hide()
		editControl:showFixButtons()
		totalSize = size
		sizeChanged = callback
		sizeEditor.visible = true
		sizeEditor.touchEnabled = true
		worldNode.position = target.position
		worldNode.rotation = target.rotation
		sizeVisual.position = center
		totalW = 0
		totalH = 0
	end
	editControl.hideSizeEditor = function(self)
		if not sizeEditor.visible then return end
		editControl:hideFixButtons()
		sizeEditor.touchEnabled = false
		sizeEditor.visible = false
	end
	
	-- init center editor --
	-- centerEditor
	local centerEditor = CCLayer()
	centerEditor.visible = false
	editControl:addChild(centerEditor)
	local centerVisual = CCNode()
	centerVisual.transformTarget = oEditor.world
	centerVisual:addChild(oLine(
	{
		oVec2(0,150),
		oVec2(-20,150),
		oVec2(0,190),
		oVec2(20,150),
		oVec2(0,150),
		oVec2.zero
	},ccColor4()))
	centerVisual:addChild(oLine(
	{
		oVec2.zero,
		oVec2(150,0),
		oVec2(150,20),
		oVec2(190,0),
		oVec2(150,-20),
		oVec2(150,0)
	},ccColor4()))
	centerEditor:addChild(centerVisual)
	centerEditor.scaleX = 0.5
	centerEditor.scaleY = 0.5

	-- centerEditor touch callback
	local totalDeltaCenter = oVec2.zero
	local centerPos = oVec2.zero
	local centerChanged = nil
	centerEditor:registerTouchHandler(function(eventType,touch)
		if eventType == CCTouch.Moved then
			local delta = touch.delta
			if fixX then delta.x = 0 end
			if fixY then delta.y = 0 end
			if oEditor.isFixed then
				totalDeltaCenter = totalDeltaCenter + delta/oEditor.scale
				if totalDeltaCenter.x > 1 or totalDeltaCenter.x < -1 then
					local posX = centerPos.x+totalDeltaCenter.x
					centerPos.x = posX > 0 and math.floor(posX+0.5) or math.ceil(posX-0.5)
					totalDeltaCenter.x = 0
				end
				if totalDeltaCenter.y > 1 or totalDeltaCenter.y < -1 then
					local posY = centerPos.y+totalDeltaCenter.y
					centerPos.y = posY > 0 and math.floor(posY+0.5) or math.ceil(posY-0.5)
					totalDeltaCenter.y = 0
				end
			else
				centerPos = centerPos + delta/oEditor.scale
			end
			centerVisual.position = centerPos
			if centerChanged then
				centerChanged(worldNode:convertToNodeSpace(oEditor.world:convertToWorldSpace(centerPos)))
			end
		end
		return true
	end,false,oEditor.touchPriorityEditControl,true)

	-- show & hide center editor
	editControl.showCenterEditor = function(self,target,center,callback)
		editControl:hide()
		editControl:showFixButtons()
		centerChanged = callback
		centerEditor.visible = true
		centerEditor.touchEnabled = true
		worldNode.position = target.position
		worldNode.rotation = target.rotation
		centerPos = oEditor.world:convertToNodeSpace(target:convertToWorldSpace(center))
		centerVisual.position = centerPos
		totalDeltaCenter = oVec2.zero
	end
	editControl.hideCenterEditor = function(self)
		if not centerEditor.visible then return end
		editControl:hideFixButtons()
		centerEditor.touchEnabled = false
		centerEditor.visible = false
	end

	-- init radius editor --
	-- radiusEditor
	local radiusEditor = CCLayer()
	radiusEditor.visible = false
	editControl:addChild(radiusEditor)
	local radiusVisual = CCNode()
	radiusVisual:addChild(oLine(
	{
		oVec2.zero,
		oVec2(150,0),
		oVec2(150,20),
		oVec2(150,0),
		oVec2(150,-20),
		oVec2(150,0)
	},ccColor4()))
	radiusVisual.transformTarget = worldNode
	radiusEditor:addChild(radiusVisual)
	
	-- radiusEditor touch callback
	local radiusCenter = oVec2.zero
	local totalDeltaRadius = 0
	local totalRadius = 0
	local radiusChanged = nil
	radiusEditor:registerTouchHandler(function(eventType,touch)
		if eventType == CCTouch.Moved then
			local prevPos = touch.preLocation
			local pos = touch.location
			if pos ~= radiusCenter then
				local delta = pos:distance(radiusCenter)-prevPos:distance(radiusCenter)
				if oEditor.isFixed then
					totalDeltaRadius = totalDeltaRadius + delta/oEditor.scale
					if totalDeltaRadius > 1 or totalDeltaRadius < -1 then
						local radius = totalRadius+totalDeltaRadius
						totalRadius = radius > 0 and math.floor(radius+0.5) or math.ceil(radius-0.5)
						totalDeltaRadius = 0
					end
				else
					totalRadius = totalRadius + totalDeltaRadius/oEditor.scale
				end
				if totalRadius < 5 then totalRadius = 5 end
				if radiusChanged then
					radiusChanged(totalRadius)
				end
			end
		end
		return true
	end,false,oEditor.touchPriorityEditControl,true)
	
	-- show & hide size editor
	editControl.showRadiusEditor = function(self,target,center,radius,callback)
		editControl:hide()
		worldNode.position = target.position
		worldNode.rotation = target.rotation
		radiusVisual.position = center
		radiusCenter = target:convertToWorldSpace(radiusVisual.position)
		totalRadius = radius
		radiusChanged = callback
		radiusEditor.visible = true
		radiusEditor.touchEnabled = true
		totalDeltaRadius = 0
	end
	editControl.hideRadiusEditor = function(self)
		if not radiusEditor.visible then return end
		radiusEditor.touchEnabled = false
		radiusEditor.visible = false
	end

	-- init vertices --
	local vertControl = oVertexControl()
	editControl:addChild(vertControl)
	editControl.showVertEditor = function(self,...)			self:hide()
		self:showFixButtons()
		vertControl:show(...)
	end
	editControl.hideVertEditor = function(self)
		self:hideFixButtons()
		vertControl:hide()
	end

	-- hide all controls
	editControl.hide = function(self)
		editControl:hideSwitch()
		editControl:hideTypeSelector()
		editControl:hideEditRuler()
		editControl:hidePosEditor()
		editControl:hideRotEditor()
		editControl:hideSizeEditor()
		editControl:hideCenterEditor()
		editControl:hideRadiusEditor()
		editControl:hideVertEditor()
	end

	editControl.data = CCDictionary()
	editControl.data.hideListener = oListener("editControl.hide",function()
		editControl:hide()
	end)
	local currentSetting = nil
	editControl.data.settingListener = oListener("settingPanel.edit",function(item)
		if not item then return end
		local name = item.name
		local value = item.value
		local data = oEditor.currentData
		if item.selected then
			currentSetting = name
			if name == "Type" then
				editControl:showTypeSelector(function(bodyType)
					if data:get("Type") ~= bodyType then
						if bodyType == oBodyDef.Dynamic then
							item.value = "Dynamic"
						elseif bodyType == oBodyDef.Static then
							item.value = "Static"
						elseif bodyType == oBodyDef.Kinematic then
							item.value = "Kinematic"
						end
						data:set("Type",bodyType)
						oEditor:resetItem(data)
					end
					oEvent:send("settingPanel.edit",nil)
				end)
			elseif name == "Position" then
				editControl:showPosEditor(data:get("Position"),function(pos)
					item.value = string.format("%.2f",pos.x)..","..string.format("%.2f",pos.y)
					local item = oEditor:getItem(data)
					if item then item.position = pos end
					data:set("Position",pos)
				end)
			elseif name == "Angle" then
				editControl:showRotEditor(data,function(rot)
					item.value = string.format("%.2f",rot)
					data:set("Angle",rot)
					if data.parent then
						oEditor:resetItem(data)
					else
						local item = oEditor:getItem(data)
						if item then item.rotation = rot end
					end
				end)
			elseif name == "Center" then
				editControl:showCenterEditor(oEditor:getItem(data),data:get("Center"),function(center)
					item.value = string.format("%.2f",center.x)..","..string.format("%.2f",center.y)
					data:set("Center",center)
					oEditor:resetItem(data)
				end)
			elseif name == "Size" then
				editControl:showSizeEditor(
					oEditor:getItem(data),data:get("Center"),data:get("Size"),function(size)
					item.value = string.format("%d",size.width)..","..string.format("%d",size.height)
					data:set("Size",size)
					oEditor:resetItem(data)
				end)
			elseif name == "Radius" then
				editControl:showRadiusEditor(
					oEditor:getItem(data),data:get("Center"),data:get("Radius"),function(radius)
					item.value = string.format("%d",radius)
					data:set("Radius",radius)
					oEditor:resetItem(data)
				end)
			elseif name == "Density" then
				editControl:showEditRuler(data:get("Density"),0,22.6,1,function(val)
					item.value = string.format("%.1f",val)
					data:set("Density",val)
				end)
			elseif name == "Restitution" or  name == "Friction" then
				editControl:showEditRuler(data:get(name),0,1,0.1,function(val)
					item.value = string.format("%.2f",val)
					data:set(name,val)
				end)
			elseif name == "LinearDamping" or name ==  "AngularDamping" then
				editControl:showEditRuler(data:get(name),0,10,1,function(val)
					item.value = string.format("%.1f",val)
					data:set(name,val)
				end)
			elseif name == "GravityScale" then
				editControl:showEditRuler(data:get("GravityScale"),-10,10,1,function(val)
					item.value = string.format("%.1f",val)
					data:set("GravityScale",val)
				end)
			elseif name == "SensorTag" then
				editControl:showEditRuler(data:get("SensorTag"),0,100,10,function(val)
					val = math.floor(val)
					item.value = string.format("%d",val)
					data:set("SensorTag",val)
				end)
			elseif name == "FixedRotation" or name == "Bullet" or name == "Sensor" then
				editControl:showSwitch(data:get(name), function(val)
					item.value = tostring(val)
					data:set(name,val)
					oEditor:resetItem(data)
				end)
			elseif name == "Vertices" then
				local item = data.parent or data
				editControl:showVertEditor(data:get("Vertices"),item:get("Position"),item:get("Angle"),function(vs)
					data:set("Vertices",vs)
					oEditor:resetItem(data)
				end)
			end
		else
			if name == "Name" then
				local oldName = data:get("Name")
				if value ~= oldName then
					value = oEditor:getUsableName(value)
					item.value = value
					data:set("Name",value)
					oEditor:rename(oldName,value)
				end
			elseif currentSetting == name then
				if name == "Density"
					or name == "Friction"
					or name == "Restitution"
					or name == "LinearDamping"
					or name ==  "AngularDamping"
					or name == "GravityScale"
					or name == "SensorTag" then
					oEditor:resetItem(data)
				end
				editControl:hide()
			end
		end
	end)
	--[[
	local value = 0
	editControl:showEditRuler(value,0,1000,10,function(val) if value ~= val then value=val;print(value) end end)
	--]]
	--[[
	local data = oEditor.bodyData[1]
	editControl:showTypeSelector(function(bodyType)
		data:set("Type",bodyType)
		oEditor:resetItem(data)
	end)
	--]]
	--[[
	local data = oEditor.bodyData[3]
	editControl:showPosEditor(data:get("Position"),function(pos)
		local item = oEditor:getItem(data)
		if item then item.position = pos end
		data:set("Position",pos)
	end)
	--]]
	--[[
	local data = oEditor.bodyData[2]
	editControl:showRotEditor(data,function(rot)
		data:set("Angle",rot)
		if data.parent then
			oEditor:resetItem(data)
		else
			oEditor:getItem(data).rotation = rot
		end
	end)
	--]]
	--[[
	local data = oEditor.bodyData[1]:get("SubShapes")[1]
	editControl:showSizeEditor(
		oEditor:getItem(data),data:get("Center"),data:get("Size"),function(size)
		data:set("Size",size)
		oEditor:resetItem(data)
	end)
	--]]
	--[[
	local data = oEditor.bodyData[3]:get("SubShapes")[2]
	editControl:showRadiusEditor(
		oEditor:getItem(data),data:get("Center"),data:get("Radius"),function(radius)
		data:set("Radius",radius)
		oEditor:resetItem(data)
	end)
	--]]
	--[[
	local data = oEditor.bodyData[3]:get("SubShapes")[2]
	editControl:showCenterEditor(oEditor:getItem(data),data:get("Center"),function(center)
		data:set("Center",center)
		oEditor:resetItem(data)
	end)
	--]]
	return editControl
end

return oEditControl