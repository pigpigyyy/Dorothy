local require = using("BodyEditor.Script")
local CCDirector = require("CCDirector")
local CCSize = require("CCSize")
local oSelectionPanel = require("oSelectionPanel")
local oEditor = require("oEditor")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local emit = require("emit")
local oSettingItem = require("oSettingItem")
local CCTextAlign = require("CCTextAlign")
local CCUserDefault = require("CCUserDefault")
local oBodyDef = require("oBodyDef")
local oPos = require("oPos")
local oEase = require("oEase")

local function oSettingPanel()
	local winSize = CCDirector.winSize
	local borderSize = CCSize(180,260*(winSize.height-30)/(600-30))
	local self = oSelectionPanel(borderSize,false,true,true)
	self.touchPriority = oEditor.touchPrioritySettingPanel
	local menu = self.menu
	menu.touchPriority = oEditor.touchPrioritySettingPanel+1
	local border = self.border
	local halfBW = borderSize.width*0.5
	local halfBH = borderSize.height*0.5
	local itemWidth = borderSize.width
	local itemHeight = 30
	local background = CCDrawNode()
	background:drawPolygon(
	{
		oVec2(-halfBW,-halfBH),
		oVec2(halfBW,-halfBH),
		oVec2(halfBW,halfBH),
		oVec2(-halfBW,halfBH)
	},ccColor4(0x88100000),0.5,ccColor4(0x88ffafaf))
	border:addChild(background,-1)
	self.position = oVec2(winSize.width*0.5-100,-winSize.height*0.5+halfBH+10)

	local label = CCLabelTTF("","Arial",16)
	label.position = oVec2(halfBW,borderSize.height-18)
	label.color = ccColor3(0x00ffff)
	menu:addChild(label)

	local function genPosY()
		local index = 0
		return function()
			local v = index
			index = index + 1
			return borderSize.height-30-itemHeight*v
		end
	end

	local itemNames =
	{
		-- text field
		{"Name","%s"},
		-- body chooser
		{"BodyA","%s"},
		{"BodyB","%s"},
		-- joint chooser
		{"JointA","%s"},
		{"JointB","%s"},
		-- move point
		{"WorldPos","%d"},
		{"GroundA","%s"},
		{"GroundB","%s"},
		{"AnchorA","%d"},
		{"AnchorB","%d"},
		{"Offset","%d"},
		-- move axis
		{"Axis","%d"},
		-- float
		{"MaxForce","%d"},
		{"MaxTorque","%d"},
		{"Ratio","%.1f"},
		{"AngularOffset","%d"},
		{"CorrectionFactor","%.1f"},
		{"Lower","%d"},
		{"Upper","%d"},
		{"MaxMotorForce","%d"},
		{"MotorSpeed","%d"},
		{"LowerAngle","%d"},
		{"UpperAngle","%d"},
		{"MaxMotorTorque","%d"},
		{"MaxLength","%d"},
		{"Frequency","%d"},
		{"Damping","%.2f"},
		{"Angle","%d"},
		{"Radius","%d"},
		{"GravityScale","%.1f"},
		{"LinearDamping","%.1f"},
		{"AngularDamping","%.1f"},
		{"Density","%.1f"},
		{"Friction","%.2f"},
		{"Restitution","%.2f"},
		-- selector
		{"Type","%s"},
		-- boolean
		{"Bullet","%s"},
		{"FixedRotation","%s"},
		{"Collision","%s"},
		-- rect maker
		{"Size","%d"},
		-- move position
		{"Position","%d"},
		{"Center","%d"},
		-- vertices editor
		{"Vertices","%s"},
		-- face chooser
		{"Face","%s"},
		-- move position
		{"FacePos","%d"},
		-- boolean
		{"Sensor","%s"},
		-- int
		{"SensorTag","%d"},
		{"G","%d"},
	}

	local items = {}
	local getPosY = genPosY()
	local currentItem = nil
	local function editCallback(settingItem)
		emit("Body.editMenu.created")
		if currentItem then
			currentItem.selected = false
			emit("Body.settingPanel.edit",currentItem)
			currentItem = nil
		end
		if settingItem.selected then
			currentItem = settingItem
			emit("Body.settingPanel.edit",currentItem)
		end
	end
	for i = 1,#itemNames do
		local itemName = itemNames[i][1]
		local valueFormat = itemNames[i][2]
		items[itemName] = oSettingItem(itemName.." :",itemWidth,itemHeight,-itemWidth,getPosY(),i == 1,valueFormat,editCallback)
		items[itemName].name = itemName
	end
	for _,item in pairs(items) do
		item.visible = false
		menu:addChild(item)
	end
	items.Vertices.value = ". . ."
	items.Face._label.positionX = 54
	items.Face._label.anchor = oVec2(0,0.5)
	items.Face._label.horizontalAlignment = CCTextAlign.HLeft
	items.G.value = CCUserDefault.G == "" and -10 or CCUserDefault.G
	self.items = items

	local itemsRectangle =
	{
		items.Name,
		items.Type,
		items.Size,
		items.Angle,
		items.Center,
		items.Position,
		items.Density,
		items.Friction,
		items.Restitution,
		items.LinearDamping,
		items.AngularDamping,
		items.FixedRotation,
		items.GravityScale,
		items.Bullet,
		items.Sensor,
		items.SensorTag,
		items.Face,
		items.FacePos,
		items.G,
	}
	self.Rectangle = itemsRectangle

	local itemsCircle =
	{
		items.Name,
		items.Type,
		items.Radius,
		items.Angle,
		items.Center,
		items.Position,
		items.Density,
		items.Friction,
		items.Restitution,
		items.LinearDamping,
		items.AngularDamping,
		items.FixedRotation,
		items.GravityScale,
		items.Bullet,
		items.Sensor,
		items.SensorTag,
		items.Face,
		items.FacePos,
		items.G,
	}
	self.Circle = itemsCircle

	local itemsPolygon =
	{
		items.Name,
		items.Type,
		items.Vertices,
		items.Angle,
		items.Position,
		items.Density,
		items.Friction,
		items.Restitution,
		items.LinearDamping,
		items.AngularDamping,
		items.FixedRotation,
		items.GravityScale,
		items.Bullet,
		items.Sensor,
		items.SensorTag,
		items.Face,
		items.FacePos,
		items.G,
	}
	self.Polygon = itemsPolygon

	local itemsChain =
	{
		items.Name,
		items.Type,
		items.Position,
		items.Angle,
		items.Vertices,
		items.Friction,
		items.Restitution,
		items.LinearDamping,
		items.AngularDamping,
		items.FixedRotation,
		items.GravityScale,
		items.Bullet,
		items.Face,
		items.FacePos,
		items.G,
	}
	self.Chain = itemsChain

	local itemsLoop =
	{
		items.Name,
		items.Type,
		items.Position,
		items.Angle,
		items.Vertices,
		items.Friction,
		items.Restitution,
		items.LinearDamping,
		items.AngularDamping,
		items.FixedRotation,
		items.GravityScale,
		items.Bullet,
		items.Face,
		items.FacePos,
		items.G,
	}
	self.Loop = itemsLoop

	local itemsSubRectangle =
	{
		items.Center,
		items.Angle,
		items.Size,
		items.Density,
		items.Friction,
		items.Restitution,
		items.Sensor,
		items.SensorTag,
	}
	self.SubRectangle = itemsSubRectangle

	local itemsSubCircle =
	{
		items.Center,
		items.Radius,
		items.Density,
		items.Friction,
		items.Restitution,
		items.Sensor,
		items.SensorTag,
	}
	self.SubCircle = itemsSubCircle

	local itemsSubPolygon =
	{
		items.Vertices,
		items.Density,
		items.Friction,
		items.Restitution,
		items.Sensor,
		items.SensorTag,
	}
	self.SubPolygon = itemsSubPolygon

	local itemsSubChain =
	{
		items.Vertices,
		items.Friction,
		items.Restitution,
	}
	self.SubChain = itemsSubChain

	local itemsSubLoop =
	{
		items.Vertices,
		items.Friction,
		items.Restitution,
	}
	self.SubLoop = itemsSubLoop

	local itemsDistance =
	{
		items.Name,
		items.Collision,
		items.BodyA,
		items.BodyB,
		items.AnchorA,
		items.AnchorB,
		items.Frequency,
		items.Damping,
	}
	self.Distance = itemsDistance

	local itemsFriction =
	{
		items.Name,
		items.Collision,
		items.BodyA,
		items.BodyB,
		items.WorldPos,
		items.MaxForce,
		items.MaxTorque,
	}
	self.Friction = itemsFriction

	local itemsGear =
	{
		items.Name,
		items.Collision,
		items.JointA,
		items.JointB,
		items.Ratio,
	}
	self.Gear = itemsGear

	local itemsSpring =
	{
		items.Name,
		items.Collision,
		items.BodyA,
		items.BodyB,
		items.Offset,
		items.AngularOffset,
		items.MaxForce,
		items.MaxTorque,
		items.CorrectionFactor,
	}
	self.Spring = itemsSpring

	local itemsPrismatic =
	{
		items.Name,
		items.Collision,
		items.BodyA,
		items.BodyB,
		items.WorldPos,
		items.Axis,
		items.Lower,
		items.Upper,
		items.MaxMotorForce,
		items.MotorSpeed,
	}
	self.Prismatic = itemsPrismatic

	local itemsPulley =
	{
		items.Name,
		items.Collision,
		items.BodyA,
		items.BodyB,
		items.AnchorA,
		items.AnchorB,
		items.GroundA,
		items.GroundB,
		items.Ratio,
	}
	self.Pulley = itemsPulley

	local itemsRevolute =
	{
		items.Name,
		items.Collision,
		items.BodyA,
		items.BodyB,
		items.WorldPos,
		items.LowerAngle,
		items.UpperAngle,
		items.MaxMotorTorque,
		items.MotorSpeed,
	}
	self.Revolute = itemsRevolute

	local itemsRope =
	{
		items.Name,
		items.Collision,
		items.BodyA,
		items.BodyB,
		items.AnchorA,
		items.AnchorB,
		items.MaxLength,
	}
	self.Rope = itemsRope

	local itemsWeld =
	{
		items.Name,
		items.Collision,
		items.BodyA,
		items.BodyB,
		items.WorldPos,
		items.Frequency,
		items.Damping,
	}
	self.Weld = itemsWeld

	local itemsWheel =
	{
		items.Name,
		items.Collision,
		items.BodyA,
		items.BodyB,
		items.WorldPos,
		items.Axis,
		items.MaxMotorTorque,
		items.MotorSpeed,
		items.Frequency,
		items.Damping,
	}
	self.Wheel = itemsWheel

	local currentGroup = nil
	local function selectGroup(groupName)
		if currentGroup then
			for _,item in ipairs(currentGroup) do
				item.positionX = -itemWidth
				item.visible = false
			end
		end
		label.visible = true
		label.text = groupName
		label.texture.antiAlias = false
		label.position = oVec2(halfBW,borderSize.height-18)
		currentGroup = self[groupName]
		local getPosY = genPosY()
		local contentHeight = 40
		for _,item in ipairs(currentGroup) do
			item.visible = true
			item.positionX = 0
			item.positionY = getPosY()
			contentHeight = contentHeight + itemHeight
		end
		self:reset(borderSize.width,contentHeight,0,50)
		local data = oEditor.currentData
		if data and data:get("ItemType") == groupName then
			for k,v in pairs(oEditor[groupName]) do
				if k ~= "SubShapes"
					and k ~= "Vertices"
					and k ~= "ItemType"
					and k ~= "create"
					and k ~= "rename"
					and k ~= "reset"
					and k ~= "parent"
					and k ~= "set"
					and k ~= "get" then
					local value = data[v]
					if k == "Type" then
						if value == oBodyDef.Dynamic then
							items[k].value = "Dynamic"
						elseif value == oBodyDef.Static then
							items[k].value = "Static"
						elseif value == oBodyDef.Kinematic then
							items[k].value = "Kinematic"
						end
					elseif k == "Face" then
						items[k].value = value:match("[^\\/]*%.[^%.\\/]*$")
					else
						items[k].value = value
					end
				end
			end
		end
	end

	self:gslot("Body.settingPanel.toState",function(state)
		emit("Body.settingPanel.edit",nil)
		if state then
			selectGroup(state)
		else
			label.visible = false
			if currentGroup then
				for _,item in ipairs(currentGroup) do
					item.positionX = -itemWidth
					item.visible = false
				end
			end
		end
	end)
	self:gslot("Body.settingPanel.cancel",function()
		if currentItem and currentItem.selected then
			currentItem.selected = false
			editCallback(currentItem)
		end
	end)
	self:gslot("Body.settingPanel.edit",function(item)
		if currentItem ~= item then
			currentItem.selected = false
			currentItem = nil
			if item then
				item.selected = true
				currentItem = item
			end
		end
	end)
	self:gslot("Body.settingPanel.enable",function(enable)
		for _,item in pairs(items) do
			item.enabled = enable
		end
	end)
	local isHide = false
	self:gslot("Body.hideEditor",function(args)
		local hide,instant = unpack(args)
		if isHide == hide then
			return
		end
		isHide = hide
		local winWidth = CCDirector.winSize.width
		if instant then
			self.positionX = winWidth*2-self.positionX
		else
			self:perform(oPos(0.5,winWidth*2-self.positionX,self.positionY,oEase.OutQuad))
		end
	end)
	return self
end

return oSettingPanel
