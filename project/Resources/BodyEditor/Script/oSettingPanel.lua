local require = using("BodyEditor.Script")
local CCSize = require("CCSize")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCDirector = require("CCDirector")
local oSettingItem = require("oSettingItem")
local oSelectionPanel = require("oSelectionPanel")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local emit = require("emit")
local oEditor = require("oEditor")
local tolua = require("tolua")
local oBodyDef = require("oBodyDef")
local CCTextAlign = require("CCTextAlign")
local CCUserDefault = require("CCUserDefault")

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
	},ccColor4(0xe5100000),0.5,ccColor4(0x88ffafaf))
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
		"Name",
		-- body chooser
		"BodyA",
		"BodyB",
		-- joint chooser
		"JointA",
		"JointB",
		-- move point
		"WorldPos",
		"GroundA",
		"GroundB",
		"AnchorA",
		"AnchorB",
		"Offset",
		-- move axis
		"Axis",
		-- float
		"MaxForce",
		"MaxTorque",
		"Ratio",
		"AngularOffset", 
		"CorrectionFactor",
		"Lower",
		"Upper",
		"MaxMotorForce",
		"MotorSpeed",
		"LowerAngle",
		"UpperAngle",
		"MaxMotorTorque",
		"MaxLength",
		"Frequency",
		"Damping",
		"Angle",
		"Radius",
		"GravityScale",
		"LinearDamping",
		"AngularDamping",
		"Density",
		"Friction",
		"Restitution",
		-- selector
		"Type",
		-- boolean
		"Bullet",
		"FixedRotation",
		"Collision",
		-- rect maker
		"Size",
		-- move position
		"Position",
		"Center",
		-- vertices editor
		"Vertices",
		-- face chooser
		"Face",
		-- move position
		"FacePos",
		-- boolean
		"Sensor",
		-- int
		"SensorTag",
		"G",
	}

	local items = {}
	local getPosY = genPosY()
	local function editCallback(settingItem)
		emit("Body.settingPanel.edit",settingItem)
	end
	for i = 1,#itemNames do
		items[itemNames[i]] = oSettingItem(itemNames[i].." :",itemWidth,itemHeight,-itemWidth,getPosY(),i == 1,editCallback)
		items[itemNames[i]].name = itemNames[i]
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
					if tolua.type(value) == "oVec2" then
						items[k].value = string.format("%.2f",value.x)..","..string.format("%.2f",value.y)
					elseif tolua.type(value) == "CCSize" then
						items[k].value = string.format("%d",value.width)..","..string.format("%d",value.height)
					elseif k == "Type" then
						if value == oBodyDef.Dynamic then
							items[k].value = "Dynamic"
						elseif value == oBodyDef.Static then
							items[k].value = "Static"
						elseif value == oBodyDef.Kinematic then
							items[k].value = "Kinematic"
						end
					else
						items[k].value = tostring(value)
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
	local currentItem = nil
	self:gslot("Body.settingPanel.edit",function(item)
		if not item or item.selected then
			if currentItem then
				currentItem.selected = false
			end
			currentItem = item
		else
			currentItem = nil
		end
	end)
	self:gslot("Body.settingPanel.enable",function(enable)
		for _,item in pairs(items) do
			item.enabled = enable
		end
	end)
	return self
end

return oSettingPanel
