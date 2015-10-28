local require = using("BodyEditor.Script")
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
local ccColor3 = require("ccColor3")
local oBodyDef = require("oBodyDef")
local emit = require("emit")
local oVertexControl = require("oVertexControl")
local oScale = require("oScale")
local oEase = require("oEase")
local CCRect = require("CCRect")
local CCSequence = require("CCSequence")
local CCDelay = require("CCDelay")
local oOpacity = require("oOpacity")
local CCCall = require("CCCall")
local oPointControl = require("oPointControl")
local CCUserDefault = require("CCUserDefault")

local function oEditControl()
	local winSize = CCDirector.winSize

	local editControl = CCNode()

	-- init fix menu --
	local fixMenu = CCMenu()
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
		emit("Body.editor.fix",{fixX=fixX,fixY=fixY})
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
		emit("Body.editor.fix",{fixX=fixX,fixY=fixY})
	end)
	fixMenu:addChild(fixYButton)
	local function createArrowForButton(button,angle)
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
		fixNode.angle = angle
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
		emit("Body.editor.fix",{fixX=false,fixY=false})
	end
	editControl.hideFixButtons = function(self)
		if not fixMenu.visible then return end
		fixMenu.visible = false
		fixMenu.touchEnabled = false
	end

	-- init switch --
	-- switchMenu
	local switchMenu = CCMenu()
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
	typeSelector.position = oEditor.origin
	typeSelector.visible = false
	typeSelector.isAutoRemove = false

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
	posVisual:gslot("Body.editor.fix",function(args)
		posVisual.children[1].visible = not args.fixY
		posVisual.children[2].visible = not args.fixX
	end)

	-- posEditor touch callback
	local totalDeltaPos = oVec2.zero
	local posChanged = nil
	posEditor.touchPriority = oEditor.touchPriorityEditControl
	posEditor.swallowTouches = true

	posEditor:slots("TouchMoved",function(touch)
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
	end)

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

	-- init angle editor --
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
	rotVisual.transformTarget = worldNode
	rotEditor:addChild(rotVisual)

	-- rotEditor touch callback
	local rotCenter = oVec2.zero
	local rotChanged = nil
	local totalRot = 0
	rotEditor.touchPriority = oEditor.touchPriorityEditControl
	rotEditor.swallowTouches = true
	rotEditor:slots("TouchMoved",function(touch)
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
					local angle = rotVisual.angle + delta
					angle = angle > 0 and math.floor(angle) or math.ceil(angle)
					rotVisual.angle = angle
				end
			else
				rotVisual.angle = rotVisual.angle + delta
			end
			if rotChanged then
				rotChanged(rotVisual.angle)
			end
		end
	end)

	-- show & hide angle editor
	editControl.showRotEditor = function(self,position,angle,center,callback)
		editControl:hide()
		rotChanged = callback
		rotEditor.visible = true
		rotEditor.touchEnabled = true
		worldNode.position = position 
		rotVisual.angle = angle
		rotVisual.position = center
		rotCenter = center
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
	sizeVisual:gslot("Body.editor.fix",function(args)
		sizeVisual.children[1].visible = not args.fixY
		sizeVisual.children[2].visible = not args.fixX
	end)
	
	-- sizeEditor touch callback
	local totalW = 0
	local totalH = 0
	local totalSize = CCSize.zero
	local sizeChanged = nil
	sizeEditor.touchPriority = oEditor.touchPriorityEditControl
	sizeEditor.swallowTouches = true
	sizeEditor:slots("TouchMoved",function(touch)
		local delta = sizeVisual:convertToNodeSpace(touch.location) - 
			sizeVisual:convertToNodeSpace(touch.preLocation)
		if delta ~= oVec2.zero then
			delta = delta*oEditor.scale
			if fixX then delta.x = 0 end
			if fixY then delta.y = 0 end
			if oEditor.isFixed then
				totalW = totalW + delta.x
				totalH = totalH + delta.y
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
				totalSize.width = totalSize.width + delta.x
				totalSize.height = totalSize.height + delta.y
			end
			if totalSize.width < 10 then totalSize.width = 10 end
			if totalSize.height < 10 then totalSize.height = 10 end
			if sizeChanged then
				sizeChanged(totalSize)
			end
		end
	end)

	-- show & hide size editor
	editControl.showSizeEditor = function(self,target,angle,center,size,callback)
		editControl:hide()
		editControl:showFixButtons()
		totalSize = size
		sizeChanged = callback
		sizeEditor.visible = true
		sizeEditor.touchEnabled = true
		worldNode.position = target.position
		worldNode.angle = target.angle
		sizeVisual.position = center
		sizeVisual.angle = angle
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
	centerVisual:gslot("Body.editor.fix",function(args)
		centerVisual.children[1].visible = not args.fixY
		centerVisual.children[2].visible = not args.fixX
	end)

	-- centerEditor touch callback
	local totalDeltaCenter = oVec2.zero
	local centerPos = oVec2.zero
	local centerChanged = nil
	centerEditor.touchPriority = oEditor.touchPriorityEditControl
	centerEditor.swallowTouches = true
	centerEditor:slots("TouchMoved",function(touch)
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
	end)

	-- show & hide center editor
	editControl.showCenterEditor = function(self,target,center,callback)
		editControl:hide()
		editControl:showFixButtons()
		centerChanged = callback
		centerEditor.visible = true
		centerEditor.touchEnabled = true
		worldNode.position = target.position
		worldNode.angle = target.angle
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
	radiusEditor.touchPriority = oEditor.touchPriorityEditControl
	radiusEditor.swallowTouches = true
	radiusEditor:slots("TouchMoved",function(touch)
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
	end)

	-- show & hide size editor
	editControl.showRadiusEditor = function(self,target,center,radius,callback)
		editControl:hide()
		worldNode.position = target.position
		worldNode.angle = target.angle
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
	editControl.showVertEditor = function(self,...)
		self:hide()
		self:showFixButtons()
		vertControl:show(...)
	end
	editControl.hideVertEditor = function(self)
		self:hideFixButtons()
		vertControl:hide()
	end

	-- init body chooser --
	local bodyChooser = CCLayer()
	bodyChooser.visible = false
	editControl:addChild(bodyChooser)
	
	local bodyChoosed = nil
	bodyChooser.touchPriority = oEditor.touchPriorityEditControl
	bodyChooser.swallowTouches = true
	bodyChooser.touchEnabled = false
	bodyChooser:slots("TouchEnded",function(touch)
		local pos = oEditor.world:convertToNodeSpace(touch.location)
		oEditor.world:query(CCRect(pos.x-0.5,pos.y-0.5,1,1),function(body)
			local data = body.dataItem
			if bodyChoosed and data:has("Name") then
				bodyChoosed(data)
			end
			return true
		end)
	end)

	local function createCross(pos,long)
		local cross = oLine(
		{
			oVec2(-10,0),
			oVec2(0,10),
			oVec2(10,0),
			oVec2(0,-10),
			oVec2(-10,0),
			oVec2(10,0),
		},ccColor4(0xff00ffff))
		cross:addChild(oLine({oVec2(0,10),oVec2(0,-10)},ccColor4(0xff00ffff)))
		cross.transformTarget = oEditor.world

		local callAction = CCCall(function()
			bodyChooser:removeChild(cross)
		end)
		if long then
			cross.opacity = 1
			cross:runAction(CCSequence({CCDelay(0.7),oOpacity(0.3,0),callAction}))
		else
			cross.opacity = 0
			cross:runAction(CCSequence({oOpacity(0.3,1),oOpacity(0.3,0),callAction}))
		end
		cross.position = pos
		bodyChooser:addChild(cross)
	end

	editControl.showBodyChooser = function(self,bodyName,callback)
		self:hide()
		bodyChooser:removeAllChildrenWithCleanup()
		if bodyName == "" then
			for _,data in ipairs(oEditor.bodyData) do
				if data:has("Position") then
					createCross(data:get("Position"),false)
				end
			end
		else
			createCross(oEditor:getItem(bodyName).position,true)
		end
		bodyChoosed = callback
		bodyChooser.visible = true
		bodyChooser.touchEnabled = true
	end
	editControl.hideBodyChooser = function(self)
		if not bodyChooser.visible then return end
		bodyChoosed = nil
		bodyChooser.visible = false
		bodyChooser.touchEnabled = false
	end
	
	-- point control --
	local pointControl = oPointControl()
	editControl:addChild(pointControl)
	editControl.showPointControl = function(self,...)
		editControl:hide()
		pointControl:show(...)
	end
	editControl.hidePointControl = function(self)
		pointControl:hide()
	end
	
	-- axis control --
	local axisVisual = oLine(
	{
		oVec2(0,0),
		oVec2(0,190),
		oVec2(20,150),
		oVec2(0,190),
		oVec2(-20,150),
	},ccColor4())
	axisVisual.angle = 90
	rotVisual:addChild(axisVisual)
	axisVisual.visible = false
	
	editControl.showAxisEditor = function(self,axis,pos,axisChanged)
		axisVisual.visible = false
		local angle = -math.deg(math.atan2(axis.y,axis.x))
		editControl:showRotEditor(pos,angle,oVec2.zero,function(rot)
			rot = -math.rad(rot)
			local newAxis = oVec2(math.cos(rot),math.sin(rot))
			newAxis:normalize()
			if axisChanged then
				axisChanged(newAxis)
			end
		end)
		rotVisual.children[1].visible = false
		rotVisual.children[2].visible = false
		rotVisual.children[3].visible = false
		axisVisual.visible = true
	end
	editControl.hideAxisEditor = function(self)
		if not axisVisual.visible then return end
		rotVisual.children[1].visible = true
		rotVisual.children[2].visible = true
		rotVisual.children[3].visible = true
		axisVisual.visible = false
		editControl:hideRotEditor()
	end
	
	-- init joint chooser --
	local jointSelected = nil
	local jointChooser = CCNode()
	jointChooser:gslot("Body.editControl.joint",function(joint)
		if jointSelected then
			jointSelected(joint)
		end
	end)
	jointChooser.visible = false
	
	editControl.showJointChooser = function(self,gearName,callback)
		editControl:hide()
		jointChooser.visible = true
		jointSelected = callback
		emit("Body.viewPanel.selectJoint",gearName)
	end
	editControl.hideJointChooser = function(self)
		if not jointChooser.visible then return end
		jointChooser.visible = false
		jointSelected = nil
		emit("Body.viewPanel.selectJoint",nil)
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
		editControl:hideBodyChooser()
		editControl:hidePointControl()
		editControl:hideAxisEditor()
		editControl:hideJointChooser()
	end

	editControl:gslot("Body.editControl.hide",function()
		editControl:hide()
	end)
	local currentSetting = nil
	editControl:gslot("Body.settingPanel.edit",function(item)
		if not item then return end
		local name = item.name
		local value = item.value
		local data = oEditor.currentData
		if item.selected then
			currentSetting = name
			if name == "Name" then
				editControl:hide()
			elseif name == "Type" then
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
					emit("Body.settingPanel.edit",nil)
				end)
			elseif name == "Position" then
				editControl:showPosEditor(data:get("Position"),function(pos)
					item.value = pos
					local body = oEditor:getItem(data)
					if body then
						body.position = pos
						emit("Body.editor.reset",{name=data:get("Name"),type="Body"})
					end
					data:set("Position",pos)
				end)
			elseif name == "Angle" then
				local pos = data.parent and data.parent:get("Position") or data:get("Position")
				local angle = data:get("Angle")
				local center = (data.parent and data:has("Center")) and data:get("Center") or oVec2.zero
				editControl:showRotEditor(pos,angle,center,function(rot)
					item.value = rot
					data:set("Angle",rot)
					if data.parent then
						oEditor:resetItem(data)
					else
						local body = oEditor:getItem(data)
						if body then
							body.angle = rot
							emit("Body.editor.reset",{name=data:get("Name"),type="Body"})
						end
					end
				end)
			elseif name == "Center" then
				editControl:showCenterEditor(oEditor:getItem(data),data:get("Center"),function(center)
					item.value = center
					data:set("Center",center)
					oEditor:resetItem(data)
				end)
			elseif name == "Size" then
				local angle = data.parent and data:get("Angle") or 0
				editControl:showSizeEditor(
					oEditor:getItem(data),angle,data:get("Center"),data:get("Size"),function(size)
					item.value = size
					data:set("Size",size)
					oEditor:resetItem(data)
				end)
			elseif name == "Radius" then
				editControl:showRadiusEditor(
					oEditor:getItem(data),data:get("Center"),data:get("Radius"),function(radius)
					item.value = radius
					data:set("Radius",radius)
					oEditor:resetItem(data)
				end)
			elseif name == "Density" then
				editControl:showEditRuler(data:get("Density"),0,22.6,1,function(val)
					item.value = val
					data:set("Density",val)
				end)
			elseif name == "Restitution" or  name == "Friction" or name == "Damping" then
				editControl:showEditRuler(data:get(name),0,1,0.1,function(val)
					item.value = val
					data:set(name,val)
				end)
			elseif name == "LinearDamping" or name ==  "AngularDamping" or name == "CorrectionFactor" then
				editControl:showEditRuler(data:get(name),0,10,1,function(val)
					item.value = val
					data:set(name,val)
				end)
			elseif name == "GravityScale" then
				editControl:showEditRuler(data:get(name),-10,10,1,function(val)
					item.value = val
					data:set(name,val)
				end)
			elseif name == "MaxLength"
				or name == "AngularOffset"
				or name == "Lower"
				or name == "Upper"
				or name == "MaxMotorForce"
				or name == "MaxMotorTorque"
				or name == "MaxForce"
				or name == "MaxTorque"
				or name == "Frequency" then
				editControl:showEditRuler(data:get(name),0,10000,10,function(val)
					item.value = val
					data:set(name,val)
				end)
			elseif name == "MotorSpeed"
				or name == "LowerAngle"
				or name == "UpperAngle" then
				editControl:showEditRuler(data:get(name),0,0,10,function(val)
					item.value = val
					data:set(name,val)
				end)
			elseif name == "Ratio" then
				editControl:showEditRuler(data:get(name),0.1,10,1,function(val)
					item.value = val
					data:set(name,val)
				end)
			elseif name == "SensorTag" then
				editControl:showEditRuler(data:get("SensorTag"),0,100,10,function(val)
					val = math.floor(val)
					item.value = val
					data:set("SensorTag",val)
				end)
			elseif name == "FixedRotation" or name == "Bullet" or name == "Sensor" or name == "Collision" then
				editControl:showSwitch(data:get(name), function(val)
					item.value = val
					data:set(name,val)
					oEditor:resetItem(data)
				end)
			elseif name == "Vertices" then
				local item = data.parent or data
				editControl:showVertEditor(data:get("Vertices"),item:get("Position"),item:get("Angle"),function(vs)
					data:set("Vertices",vs)
					oEditor:resetItem(data)
				end)
			elseif name == "BodyA" or name == "BodyB" then
				local theOtherBody = data:get(name == "BodyA" and "BodyB" or "BodyA")
				local oldName = data:get(name)
				editControl:showBodyChooser(oldName,function(body)
					local bodyName = body:get("Name")
					if bodyName ~= theOtherBody and oldName ~= bodyName then
						item.value = bodyName
						data:set(name,bodyName)
						oEditor:resetItem(data)
						editControl:hideBodyChooser()
						emit("Body.viewArea.moveToData",body)
						emit("Body.settingPanel.edit",nil)
					end
				end)
			elseif name == "JointA" or name == "JointB" then
				local theOtherJoint = data:get(name == "JointA" and "JointB" or "JointA")
				editControl:showJointChooser(data:get("Name"),function(jointName)
					if theOtherJoint == jointName then
						return
					end
					local joint = oEditor:getData(jointName)
					if joint then
						local itemType = joint:get("ItemType")
						if itemType ~= "Revolute" and itemType ~= "Prismatic" then
							return
						end
					else
						return
					end
					item.value = jointName
					data:set(name,jointName)
					oEditor:resetItem(data)
					editControl:hideJointChooser()
					emit("Body.settingPanel.edit",nil)
				end)
			elseif name == "WorldPos" or name == "GroundA" or name == "GroundB" then
				editControl:showPointControl(data:get(name),function(pos)
					item.value = pos
					data:set(name,pos)
					oEditor:resetItem(data)
				end)
			elseif name == "AnchorA" or name == "AnchorB" then
				editControl:showPointControl(data:get(name),function(pos)
					item.value = pos
					data:set(name,pos)
					oEditor:resetItem(data)
				end, oEditor:getItem(data:get(name == "AnchorA" and "BodyA" or "BodyB")))
			elseif name == "Offset" then
				editControl:showPointControl(data:get(name),function(pos)
					item.value = pos
					data:set(name,pos)
					oEditor:resetItem(data)
				end,oEditor:getItem(data:get("BodyA")))
			elseif name == "Axis" then
				editControl:showAxisEditor(data:get(name), data:get("WorldPos"),function(axis)
					item.value = axis
					data:set(name,axis)
					oEditor:resetItem(data)
				end)
			elseif name == "Face" then
				editControl:hide()
				local function selected(filename)
					item.value = filename:match("[^\\/]*%.[^%.\\/]*$")
					data:set("Face",filename)
					oEditor:resetItem(data,true)
					emit("Body.settingPanel.edit",nil)
				end
				emit("Editor.ItemChooser",{"Sprite","Model","Empty",function(itemChooser)
					if not itemChooser then
						selected("")
						return
					end
					oEditor:addChild(itemChooser,oEditor.topMost)
					itemChooser:show()
					itemChooser:slots("Selected"):set(function(filename)
						if oEditor.standAlone then
							filename = filename:sub(#(oEditor.input)+1,-1)
						end
						selected(filename)
					end)
					itemChooser:slots("Hide",function()
						emit("Body.settingPanel.edit",nil)
					end)
				end})
			elseif name == "FacePos" then
				local target = oEditor:getItem(data)
				local face = target.children[1]
				editControl:showCenterEditor(oEditor:getItem(data),data:get("FacePos"),function(center)
					item.value = center
					data:set("FacePos",center)
					if face then
						face.position = center
					end
				end)
			elseif name == "G" then
				editControl:showEditRuler(CCUserDefault.G,-100,0,10,function(val)
					item.value = val
					item.G = val
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
					or name == "SensorTag"
					or name == "MaxLength"
					or name == "MaxForce"
					or name == "MaxTorque"
					or name == "AngularOffset"
					or name == "CorrectionFactor"
					or name == "Ratio"
					or name == "Lower"
					or name == "Upper"
					or name == "MaxMotorForce"
					or name == "MaxMotorTorque"
					or name == "MotorSpeed"
					or name == "Frequency"
					or name == "Damping"
					or name == "LowerAngle"
					or name == "UpperAngle" then
					oEditor:resetItem(data)
				elseif name == "G" and item.G then
					CCUserDefault.G = item.G
					oEditor.world.gravity = oVec2(0,item.G)
				end
				editControl:hide()
			end
		end
	end)

	return editControl
end

return oEditControl