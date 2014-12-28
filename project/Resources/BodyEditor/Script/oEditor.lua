local CCScene = require("CCScene")
local CCMenu = require("CCMenu")
local oBodyDef = require("oBodyDef")

local oEditor = CCScene()
oEditor.isPlaying = false

oEditor.touchPriorityEditMenu = CCMenu.DefaultHandlerPriority
oEditor.touchPriorityViewArea = CCMenu.DefaultHandlerPriority+1
oEditor.touchPrioritySettingPanel = CCMenu.DefaultHandlerPriority+3
oEditor.touchPriorityViewPanel = CCMenu.DefaultHandlerPriority+4
oEditor.touchPriorityVRuler = CCMenu.DefaultHandlerPriority+5
oEditor.touchPriorityHRuler = CCMenu.DefaultHandlerPriority+6

local function Point(x,y)
	return function()
		return {x = x,y= y}
	end
end
local PointZero = Point(0,0)
local function Size(width,height)
	return function()
		return {width=width,height=height}
	end
end

local defaultShapeData =
{
	Rectangle =
	{
		{"Name","body"}, -- 1
		{"Type",oBodyDef.Dynamic}, -- 2
		{"Position",PointZero}, -- 3
		{"Angle",0}, -- 4
		{"Center",PointZero}, -- 5
		{"Size",Size(100,100)}, -- 6
		{"Density",1}, -- 7
		{"Friction",0.4}, -- 8
		{"Restitution",0.4}, -- 9
		{"LinearDamping", 0}, -- 10
		{"AngularDamping",0}, -- 11
		{"FixedRotation",false}, -- 12
		{"GravityScale",1}, -- 13
		{"Bullet",false}, -- 14
		{"Sensor",false}, -- 15
		{"SensorTag",0}, -- 16
		{"Face",""}, -- 17
		{"FaceAnchor",PointZero}, -- 18
		{"SubShapes",false}, -- 19
		create = function(self,world)
			local Rectangle = oEditor.Rectangle
			if self[Rectangle.Size].width == 0 or self[Rectangle.Size].height == 0 then
				return nil
			end
			local bodyDef = oBodyDef()
			if self[Rectangle.Sensor] then
				bodyDef:attachPolygonSensor(
					self[Rectangle.SensorTag],
					self[Rectangle.Size].width,
					self[Rectangle.Size].height,
					self[Rectangle.Center],
					self[Rectangle.Angle])
			else
				bodyDef:attachPolygon(
					self[Rectangle.Center],
					self[Rectangle.Size].width,
					self[Rectangle.Size].height,
					self[Rectangle.Angle],
					self[Rectangle.Density],
					self[Rectangle.Friction],
					self[Rectangle.Restitution])
			end
			bodyDef.type =  self[Rectangle.Type]
			bodyDef.isBullet =  self[Rectangle.Bullet]
			bodyDef.gravityScale =  self[Rectangle.GravityScale]
			bodyDef.fixedRotation =  self[Rectangle.FixedRotation]
			bodyDef.linearDamping =  self[Rectangle.LinearDamping]
			bodyDef.angularDamping =  self[Rectangle.AngularDamping]
			local body = oBody(bodyDef,world,
				self[Rectangle.Position],
				self[Rectangle.Angle])
			if self[Rectangle.SubShapes] then
				for _,subShape in ipairs(self[Rectangle.SubShapes]) do
					subShape:apply(body)
				end
			end
			return body
		end,
	},
	Circle =
	{
		{"Name","body"}, -- 1
		{"Type",oBodyDef.Dynamic}, -- 2
		{"Position",PointZero}, -- 3
		{"Angle",0}, -- 4
		{"Center",PointZero}, -- 5
		{"Radius",50}, -- 6
		{"Density",1}, -- 7
		{"Friction",0.4}, -- 8
		{"Restitution",0.4}, -- 9
		{"LinearDamping",0}, -- 10
		{"AngularDamping",0}, -- 11
		{"FixedRotation",false}, -- 12
		{"GravityScale",1}, -- 13
		{"Bullet",false}, -- 14
		{"Sensor",false}, -- 15
		{"SensorTag",0}, -- 16
		{"Face",""}, -- 17
		{"FaceAnchor",PointZero}, -- 18
		{"SubShapes",false}, -- 19
	},
	Polygon =
	{
		{"Name","body"}, -- 1
		{"Type",oBodyDef.Dynamic}, -- 2
		{"Position",PointZero}, -- 3
		{"Angle",0}, -- 4
		{"Vertices",false},  -- 5
		{"Density",1}, -- 6
		{"Friction",0.4}, -- 7
		{"Restitution",0.4}, -- 8
		{"LinearDamping",0}, -- 9
		{"AngularDamping",0}, -- 10
		{"FixedRotation",false}, -- 11
		{"GravityScale",1}, -- 12
		{"Bullet",false}, -- 13
		{"Sensor",false}, -- 14
		{"SensorTag",0}, -- 15
		{"Face",""}, -- 16
		{"FaceAnchor",PointZero}, -- 17
		{"SubShapes",false}, -- 18
	},
	Chain =
	{
		{"Name","body"}, -- 1
		{"Type",oBodyDef.Dynamic}, -- 2
		{"Position",PointZero}, -- 3
		{"Angle",0}, -- 4
		{"Vertices",false}, -- 5
		{"Friction",0.4}, -- 6
		{"Restitution",0.4}, -- 7
		{"LinearDamping",0}, -- 8
		{"AngularDamping",0}, -- 9
		{"FixedRotation",false}, -- 10
		{"GravityScale",1}, -- 11
		{"Bullet",false}, -- 12
		{"Face",""}, -- 13
		{"FaceAnchor",PointZero}, -- 14
		{"SubShapes",false}, -- 15
	},
	Loop =
	{
		{"Name","body"}, -- 1
		{"Type",oBodyDef.Dynamic}, -- 2
		{"Position",PointZero}, -- 3
		{"Angle",0}, -- 4
		{"Vertices",false}, -- 5
		{"Friction",0.4}, -- 6
		{"Restitution",0.4}, -- 7
		{"LinearDamping",0}, -- 8
		{"AngularDamping",0}, -- 9
		{"FixedRotation",false}, -- 10
		{"GravityScale",1}, -- 11
		{"Bullet",false}, -- 12
		{"Face",""}, -- 13
		{"FaceAnchor",PointZero}, -- 14
		{"SubShapes",false}, -- 15
	},
	SubRectangle =
	{
		{"Center",PointZero}, -- 1
		{"Angle",0}, -- 2
		{"Size",Size(100,100)}, -- 3
		{"Density",1}, -- 4
		{"Friction",0.4}, -- 5
		{"Restitution",0.4}, -- 6
		{"Sensor",false}, -- 7
		{"SensorTag",0}, -- 8
		{"Index",0}, -- 9
	},
	SubCircle =
	{
		{"Center",PointZero}, -- 1
		{"Radius",50}, -- 2
		{"Density",1}, -- 3
		{"Friction",0.4}, -- 4
		{"Restitution",0.4}, -- 5
		{"Sensor",false}, -- 6
		{"SensorTag",0}, -- 7
		{"Index",0}, -- 6
	},
	SubPolygon =
	{
		{"Vertices",false}, -- 1
		{"Density",1}, -- 2
		{"Friction",0.4}, -- 3
		{"Restitution",0.4}, -- 4
		{"Sensor",false}, -- 5
		{"SensorTag",0}, -- 6
		{"Index",0}, -- 7
	},
	SubChain =
	{
		{"Vertices",false}, -- 1
		{"Friction",0.4}, -- 2
		{"Restitution",0.4}, -- 3
		{"Index",0}, -- 4
	},
	SubLoop =
	{
		{"Vertices",false}, -- 1
		{"Friction",0.4}, -- 2
		{"Restitution",0.4}, -- 3
		{"Index",0}, -- 4
	},
	Distance =
	{
		{"Name","joint"}, -- 1
		{"Collision",false}, -- 2
		{"BodyA",""}, -- 3
		{"BodyB",""}, -- 4
		{"AnchorA",PointZero}, -- 5
		{"AnchorB",PointZero}, -- 6
		{"Frequency",0}, -- 7
		{"Damping",0}, -- 8
	},
	Friction =
	{
		{"Name","joint"}, -- 1
		{"Collision",false}, -- 2
		{"BodyA",""}, -- 3
		{"BodyB",""}, -- 4
		{"WorldPos",PointZero}, -- 5
		{"MaxForce",0}, -- 6
		{"MaxTorque",0}, -- 7
	},
	Gear =
	{
		{"Name","joint"}, -- 1
		{"Collision",false}, -- 2
		{"JointA",""}, -- 3
		{"JointB",""}, -- 4
		{"Ratio",1}, -- 5
	},
	Spring =
	{
		{"Name","joint"}, -- 1
		{"Collision",false}, -- 2
		{"BodyA",""}, -- 3
		{"BodyB",""}, -- 4
		{"LinearOffset",PointZero}, -- 5
		{"AngularOffset",0}, -- 6
		{"MaxForce",0}, -- 7
		{"MaxTorque",0}, -- 8
		{"CorrectionFactor",0.3}, -- 9
	},
	Prismatic =
	{
		{"Name","joint"}, -- 1
		{"Collision",false}, -- 2
		{"BodyA",""}, -- 3
		{"BodyB",""}, -- 4
		{"WorldPos",PointZero}, -- 5
		{"Axis",Point(1,0)}, -- 6
		{"LowerTranslation",0}, -- 7
		{"UpperTranslation",0}, -- 8
		{"MaxMotorForce",0}, -- 9
		{"MotorSpeed",0}, -- 10
	},
	Pulley =
	{
		{"Name","joint"}, -- 1
		{"Collision",true}, -- 2
		{"BodyA",""}, -- 3
		{"BodyB",""}, -- 4
		{"AnchorA",PointZero}, -- 5
		{"AnchorB",PointZero}, -- 6
		{"GroundAnchorA",Point(-100,100)}, -- 7
		{"GroundAnchorB",Point(100,100)}, -- 8
		{"Ratio",1}, -- 9
	},
	Revolute =
	{
		{"Name","joint"}, -- 1
		{"Collision",false}, -- 2
		{"BodyA",""}, -- 3
		{"BodyB",""}, -- 4
		{"WorldPos",PointZero}, -- 5
		{"LowerAngle",0}, -- 6
		{"UpperAngle",0}, -- 7
		{"MaxMotorTorque",0}, -- 8
		{"MotorSpeed",0}, -- 9
	},
	Rope =
	{
		{"Name","joint"},
		{"Collision",false},
		{"BodyA",""},
		{"BodyB",""},
		{"AnchorA",PointZero},
		{"AnchorB",PointZero},
		{"MaxLength",0},
	},
	Weld =
	{
		{"Name","joint"}, -- 1
		{"Collision",false}, -- 2
		{"BodyA",""}, -- 3
		{"BodyB",""}, -- 4
		{"WorldPos",PointZero}, -- 5
		{"Frequency",0}, -- 6
		{"Damping",0}, -- 7
	},
	Wheel =
	{
		{"Name","joint"}, -- 1
		{"Collision",false}, -- 2
		{"BodyA",""}, -- 3
		{"BodyB",""}, -- 4
		{"WorldPos",PointZero}, -- 5
		{"Axis",Point(100,0)}, -- 6
		{"MaxMotorTorque",0}, -- 7
		{"MotorSpeed",0}, -- 8
		{"Frequency",2}, -- 9
		{"Damping",0.7}, -- 10
	},
}

for shapeName,shapeDefine in pairs(defaultShapeData) do
	oEditor[shapeName] = {ItemType=0}
	for index,property in ipairs(shapeDefine) do
		oEditor[shapeName][property[1]] = index
		oEditor["new"..shapeName] = function(self)
			local newData = {[0]=shapeName}
			for i,v in ipairs(shapeDefine) do
				newData[i] = type(v[2]) == "function" and v[2]() or v[2]
			end
			return newData
		end
	end
end
--[[
local rc = oEditor:newWheel()
for k,v in pairs(oEditor.Wheel) do
	print(k,rc[v])
end
--]]
return oEditor
