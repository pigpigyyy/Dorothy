local CCScene = require("CCScene")
local CCMenu = require("CCMenu")
local oBodyDef = require("oBodyDef")
local oVec2 = require("oVec2")
local CCSize = require("CCSize")
local oBody = require("oBody")
local oJoint = require("oJoint")
local oEvent = require("oEvent")
local oListener = require("oListener")
local tolua = require("tolua")
local oContent = require("oContent")
local CCFileUtils = require("CCFileUtils")
local oWorld = require("oWorld")
local CCScheduler = require("CCScheduler")
local CCDirector = require("CCDirector")

local winSize = CCDirector.winSize

local oEditor = CCScene()

oEditor.isPlaying = false
oEditor.origin = oVec2(
		60+(winSize.width-120-180)*0.5,
		winSize.height*0.5)

local worldScheduler = CCScheduler()
worldScheduler.timeScale = 0
oEditor.worldScheduler = worldScheduler
CCDirector.scheduler:shedule(oEditor.worldScheduler)
oEditor.world = oWorld()
oEditor.world.scheduler = oEditor.worldScheduler
oEditor.world.showDebug = true
oEditor.world:setShouldContact(0,0,true)
oEditor.world:registerEventHandler(function(eventType)
	CCDirector.scheduler:unshedule(oEditor.worldScheduler)
end)

oEditor.touchPriorityEditMenu = CCMenu.DefaultHandlerPriority
oEditor.touchPriorityEditControl = CCMenu.DefaultHandlerPriority+1
oEditor.touchPrioritySettingPanel = CCMenu.DefaultHandlerPriority+2
oEditor.touchPriorityViewPanel = CCMenu.DefaultHandlerPriority+3
oEditor.touchPriorityVRuler = CCMenu.DefaultHandlerPriority+4
oEditor.touchPriorityHRuler = CCMenu.DefaultHandlerPriority+5
oEditor.touchPriorityViewArea = CCMenu.DefaultHandlerPriority+6

local function Point(x,y)
	return function()
		return oVec2(x,y)
	end
end
local PointZero = Point(0,0)
local function Size(width,height)
	return function()
		return CCSize(width,height)
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
		create = function(self)
			local Rectangle = oEditor.Rectangle
			if self[Rectangle.Size].width <= 0 or self[Rectangle.Size].height <= 0 then
				return nil
			end
			local bodyDef = oBodyDef()
			if self[Rectangle.Sensor] then
				bodyDef:attachPolygonSensor(
					self[Rectangle.SensorTag],
					self[Rectangle.Size].width,
					self[Rectangle.Size].height,
					self[Rectangle.Center],
					0)
			else
				bodyDef:attachPolygon(
					self[Rectangle.Center],
					self[Rectangle.Size].width,
					self[Rectangle.Size].height,
					0,
					self[Rectangle.Density],
					self[Rectangle.Friction],
					self[Rectangle.Restitution])
			end
			bodyDef.type = self[Rectangle.Type]
			bodyDef.isBullet = self[Rectangle.Bullet]
			bodyDef.gravityScale = self[Rectangle.GravityScale]
			bodyDef.fixedRotation = self[Rectangle.FixedRotation]
			bodyDef.linearDamping = self[Rectangle.LinearDamping]
			bodyDef.angularDamping = self[Rectangle.AngularDamping]
			local body = oBody(bodyDef,oEditor.world,
				self[Rectangle.Position],
				self[Rectangle.Angle])
			if self[Rectangle.SubShapes] then
				for _,subShape in ipairs(self[Rectangle.SubShapes]) do
					subShape:create(body)
				end
			end
			body.scheduler = oEditor.worldScheduler
			oEditor.world:addChild(body)
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
		create = function(self)
			local Circle = oEditor.Circle
			local bodyDef = oBodyDef()
			if self[Circle.Radius] <= 0 then return nil end
			if self[Circle.Sensor] then
				bodyDef:attachCircleSensor(
					self[Circle.SensorTag],
					self[Circle.Center],
					self[Circle.Radius])
			else
				bodyDef:attachCircle(
					self[Circle.Center],
					self[Circle.Radius],
					self[Circle.Density],
					self[Circle.Friction],
					self[Circle.Restitution])
			end
			bodyDef.type = self[Circle.Type]
			bodyDef.isBullet = self[Circle.Bullet]
			bodyDef.gravityScale = self[Circle.GravityScale]
			bodyDef.fixedRotation = self[Circle.FixedRotation]
			bodyDef.linearDamping = self[Circle.LinearDamping]
			bodyDef.angularDamping = self[Circle.AngularDamping]
			local body = oBody(bodyDef,oEditor.world,
				self[Circle.Position],
				self[Circle.Angle])
			if self[Circle.SubShapes] then
				for _,subShape in ipairs(self[Circle.SubShapes]) do
					subShape:create(body)
				end
			end
			body.scheduler = oEditor.worldScheduler
			oEditor.world:addChild(body)
			return body
		end,
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
		create = function(self)
			local Polygon = oEditor.Polygon
			local bodyDef = oBodyDef()
			if not self[Polygon.Vertices] or #self[Polygon.Vertices] < 3 then return nil end
			if self[Polygon.Sensor] then
				bodyDef:attachPolygonSensor(
					self[Polygon.SensorTag],
					self[Polygon.Vertices])
			else
				bodyDef:attachPolygon(
					self[Polygon.Vertices],
					self[Polygon.Density],
					self[Polygon.Friction],
					self[Polygon.Restitution])
			end
			bodyDef.type = self[Polygon.Type]
			bodyDef.isBullet = self[Polygon.Bullet]
			bodyDef.gravityScale = self[Polygon.GravityScale]
			bodyDef.fixedRotation = self[Polygon.FixedRotation]
			bodyDef.linearDamping = self[Polygon.LinearDamping]
			bodyDef.angularDamping = self[Polygon.AngularDamping]
			local body = oBody(bodyDef,oEditor.world,
				self[Polygon.Position],
				self[Polygon.Angle])
			if self[Polygon.SubShapes] then
				for _,subShape in ipairs(self[Polygon.SubShapes]) do
					subShape:create(body)
				end
			end
			body.scheduler = oEditor.worldScheduler
			oEditor.world:addChild(body)
			return body
		end,
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
		create = function(self)
			local Chain = oEditor.Chain
			local bodyDef = oBodyDef()
			if not self[Chain.Vertices] or #self[Chain.Vertices] < 2 then return nil end
			bodyDef:attachChain(
				self[Chain.Vertices],
				self[Chain.Friction],
				self[Chain.Restitution])
			bodyDef.type = self[Chain.Type]
			bodyDef.isBullet = self[Chain.Bullet]
			bodyDef.gravityScale = self[Chain.GravityScale]
			bodyDef.fixedRotation = self[Chain.FixedRotation]
			bodyDef.linearDamping = self[Chain.LinearDamping]
			bodyDef.angularDamping = self[Chain.AngularDamping]
			local body = oBody(bodyDef,oEditor.world,
				self[Chain.Position],
				self[Chain.Angle])
			if self[Chain.SubShapes] then
				for _,subShape in ipairs(self[Chain.SubShapes]) do
					subShape:create(body)
				end
			end
			body.scheduler = oEditor.worldScheduler
			oEditor.world:addChild(body)
			return body
		end,
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
		create = function(self)
			local Loop = oEditor.Loop
			local bodyDef = oBodyDef()
			if not self[Loop.Vertices] or #self[Loop.Vertices] < 3 then return nil end
			bodyDef:attachLoop(
				self[Loop.Vertices],
				self[Loop.Friction],
				self[Loop.Restitution])
			bodyDef.type = self[Loop.Type]
			bodyDef.isBullet = self[Loop.Bullet]
			bodyDef.gravityScale = self[Loop.GravityScale]
			bodyDef.fixedRotation = self[Loop.FixedRotation]
			bodyDef.linearDamping = self[Loop.LinearDamping]
			bodyDef.angularDamping = self[Loop.AngularDamping]
			local body = oBody(bodyDef,oEditor.world,
				self[Loop.Position],
				self[Loop.Angle])
			if self[Loop.SubShapes] then
				for _,subShape in ipairs(self[Loop.SubShapes]) do
					subShape:create(body)
				end
			end
			body.scheduler = oEditor.worldScheduler
			oEditor.world:addChild(body)
			return body
		end,
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
		create = function(self,body)
			local SubRectangle = oEditor.SubRectangle
			if self[SubRectangle.Size].width <= 0 or self[SubRectangle.Size].height <= 0 then
				return
			end
			if self[SubRectangle.Sensor] then
				body:attachSensor(
					self[SubRectangle.SensorTag],
					oBodyDef:polygon(
						self[SubRectangle.Center],
						self[SubRectangle.Size].width,
						self[SubRectangle.Size].height,
						self[SubRectangle.Angle]))
			else
				body:attach(
					oBodyDef:polygon(
						self[SubRectangle.Center],
						self[SubRectangle.Size].width,
						self[SubRectangle.Size].height,
						self[SubRectangle.Angle],
						self[SubRectangle.Density],
						self[SubRectangle.Friction],
						self[SubRectangle.Restitution]))
			end
		end,
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
		create = function(self,body)
			local SubCircle = oEditor.SubCircle
			if self[SubCircle.Radius] <= 0 then
				return
			end
			if self[SubCircle.Sensor] then
				body:attachSensor(
					self[SubCircle.SensorTag],
					oBodyDef:circle(
						self[SubCircle.Center],
						self[SubCircle.Radius]))
			else
				body:attach(
					oBodyDef:circle(
						self[SubCircle.Center],
						self[SubCircle.Radius],
						self[SubCircle.Density],
						self[SubCircle.Friction],
						self[SubCircle.Restitution]))
			end
		end,
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
		create = function(self,body)
			local SubPolygon = oEditor.SubPolygon
			if not self[SubPolygon.Vertices] or #self[SubPolygon.Vertices] < 3 then
				return
			end
			if self[SubPolygon.Sensor] then
				body:attachSensor(
					self[SubPolygon.SensorTag],
					oBodyDef:polygon(
						self[SubPolygon.Vertices]))
			else
				body:attach(
					oBodyDef:polygon(
						self[SubPolygon.Vertices],
						self[SubPolygon.Density],
						self[SubPolygon.Friction],
						self[SubPolygon.Restitution]))
			end
		end,
	},
	SubChain =
	{
		{"Vertices",false}, -- 1
		{"Friction",0.4}, -- 2
		{"Restitution",0.4}, -- 3
		{"Index",0}, -- 4
		create = function(self,body)
			local SubChain = oEditor.SubChain
			if not self[SubChain.Vertices] or #self[SubChain.Vertices] < 2 then
				return
			end
			body:attach(
				oBodyDef:chain(
					self[SubChain.Vertices],
					self[SubChain.Friction],
					self[SubChain.Restitution]))
		end,
	},
	SubLoop =
	{
		{"Vertices",false}, -- 1
		{"Friction",0.4}, -- 2
		{"Restitution",0.4}, -- 3
		{"Index",0}, -- 4
		create = function(self,body)
			local SubLoop = oEditor.SubLoop
			if not self[SubLoop.Vertices] or #self[SubLoop.Vertices] < 3 then
				return
			end
			body:attach(
				oBodyDef:loop(
					self[SubLoop.Vertices],
					self[SubLoop.Friction],
					self[SubLoop.Restitution]))
		end,
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
		create = function(self)
			local Distance = oEditor.Distance
			local bodyA = oEditor:getItem(self[Distance.BodyA])
			local bodyB = oEditor:getItem(self[Distance.BodyB])
			if not bodyA or not bodyB then
				return nil
			end
			return oJoint:collide(self[Distance.Collision]):distance(
				bodyA,bodyB,
				self[Distance.AnchorA],
				self[Distance.AnchorB],
				self[Distance.Frequency],
				self[Distance.Damping])
		end,
		rename = function(self,oldName,newName)
			local Distance = oEditor.Distance
			if self[Distance.BodyA] == oldName then self[Distance.BodyA] = newName end
			if self[Distance.BodyB] == oldName then self[Distance.BodyB] = newName end
		end,
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
		create = function(self)
			local Friction = oEditor.Friction
			local bodyA = oEditor:getItem(self[Friction.BodyA])
			local bodyB = oEditor:getItem(self[Friction.BodyB])
			if not bodyA or not bodyB then
				return nil
			end
			return oJoint:collide(self[Friction.Collision]):friction(
				bodyA,bodyB,
				self[Friction.WorldPos],
				self[Friction.MaxForce],
				self[Friction.MaxTorque])
		end,
		rename = function(self,oldName,newName)
			local Friction = oEditor.Friction
			if self[Friction.BodyA] == oldName then self[Friction.BodyA] = newName end
			if self[Friction.BodyB] == oldName then self[Friction.BodyB] = newName end
		end,
	},
	Gear =
	{
		{"Name","joint"}, -- 1
		{"Collision",false}, -- 2
		{"JointA",""}, -- 3
		{"JointB",""}, -- 4
		{"Ratio",1}, -- 5
		create = function(self)
			local Gear = oEditor.Gear
			local jointA = oEditor:getItem(self[Gear.JointA])
			local jointB = oEditor:getItem(self[Gear.JointB])
			if not jointA or not jointB then
				return nil
			end
			return oJoint:collide(self[Gear.Collision]):gear(
				jointA,jointB,
				self[Gear.Ratio])
		end,
		rename = function(self,oldName,newName)
			local Gear = oEditor.Gear
			if self[Gear.JointA] == oldName then self[Gear.JointA] = newName end
			if self[Gear.JointB] == oldName then self[Gear.JointB] = newName end
		end,
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
		create = function(self)
			local Spring = oEditor.Spring
			local bodyA = oEditor:getItem(self[Spring.BodyA])
			local bodyB = oEditor:getItem(self[Spring.BodyB])
			if not bodyA or not bodyB then
				return nil
			end
			return oJoint:collide(self[Spring.Collision]):spring(
				bodyA,bodyB,
				self[Spring.LinearOffset],
				self[Spring.AngularOffset],
				self[Spring.MaxForce],
				self[Spring.MaxTorque],
				self[Spring.CorrectionFactor])
		end,
		rename = function(self,oldName,newName)
			local Spring = oEditor.Spring
			if self[Spring.BodyA] == oldName then self[Spring.BodyA] = newName end
			if self[Spring.BodyB] == oldName then self[Spring.BodyB] = newName end
		end,
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
		create = function(self)
			local Prismatic = oEditor.Prismatic
			local bodyA = oEditor:getItem(self[Prismatic.BodyA])
			local bodyB = oEditor:getItem(self[Prismatic.BodyB])
			if not bodyA or not bodyB then
				return nil
			end
			return oJoint:collide(self[Prismatic.Collision]):prismatic(
				bodyA,bodyB,
				self[Prismatic.WorldPos],
				self[Prismatic.Axis],
				self[Prismatic.LowerTranslation],
				self[Prismatic.UpperTranslation],
				self[Prismatic.MaxMotorForce],
				self[Prismatic.MotorSpeed])
		end,
		rename = function(self,oldName,newName)
			local Prismatic = oEditor.Prismatic
			if self[Prismatic.BodyA] == oldName then self[Prismatic.BodyA] = newName end
			if self[Prismatic.BodyB] == oldName then self[Prismatic.BodyB] = newName end
		end,
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
		create = function(self)
			local Pulley = oEditor.Pulley
			local bodyA = oEditor:getItem(self[Pulley.BodyA])
			local bodyB = oEditor:getItem(self[Pulley.BodyB])
			if not bodyA or not bodyB then
				return nil
			end
			return oJoint:collide(self[Pulley.Collision]):pulley(
				bodyA,bodyB,
				self[Pulley.AnchorA],
				self[Pulley.AnchorB],
				self[Pulley.GroundAnchorA],
				self[Pulley.GroundAnchorB],
				self[Pulley.Ratio])
		end,
		rename = function(self,oldName,newName)
			local Pulley = oEditor.Pulley
			if self[Pulley.BodyA] == oldName then self[Pulley.BodyA] = newName end
			if self[Pulley.BodyB] == oldName then self[Pulley.BodyB] = newName end
		end,
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
		create = function(self)
			local Revolute = oEditor.Revolute
			local bodyA = oEditor:getItem(self[Revolute.BodyA])
			local bodyB = oEditor:getItem(self[Revolute.BodyB])
			if not bodyA or not bodyB then
				return nil
			end
			return oJoint:collide(self[Revolute.Collision]):revolute(
				bodyA,bodyB,
				self[Revolute.WorldPos],
				self[Revolute.LowerAngle],
				self[Revolute.UpperAngle],
				self[Revolute.MaxMotorTorque],
				self[Revolute.MotorSpeed])
		end,
		rename = function(self,oldName,newName)
			local Revolute = oEditor.Revolute
			if self[Revolute.BodyA] == oldName then self[Revolute.BodyA] = newName end
			if self[Revolute.BodyB] == oldName then self[Revolute.BodyB] = newName end
		end,
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
		create = function(self)
			local Rope = oEditor.Rope
			local bodyA = oEditor:getItem(self[Rope.BodyA])
			local bodyB = oEditor:getItem(self[Rope.BodyB])
			if not bodyA or not bodyB then
				return nil
			end
			return oJoint:collide(self[Rope.Collision]):rope(
				bodyA,bodyB,
				self[Rope.AnchorA],
				self[Rope.AnchorB],
				self[Rope.MaxLength])
		end,
		rename = function(self,oldName,newName)
			local Rope = oEditor.Rope
			if self[Rope.BodyA] == oldName then self[Rope.BodyA] = newName end
			if self[Rope.BodyB] == oldName then self[Rope.BodyB] = newName end
		end,
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
		create = function(self)
			local Weld = oEditor.Weld
			local bodyA = oEditor:getItem(self[Weld.BodyA])
			local bodyB = oEditor:getItem(self[Weld.BodyB])
			if not bodyA or not bodyB then
				return nil
			end
			return oJoint:collide(self[Weld.Collision]):weld(
				bodyA,bodyB,
				self[Weld.WorldPos],
				self[Weld.Frequency],
				self[Weld.Damping])
		end,
		rename = function(self,oldName,newName)
			local Weld = oEditor.Weld
			if self[Weld.BodyA] == oldName then self[Weld.BodyA] = newName end
			if self[Weld.BodyB] == oldName then self[Weld.BodyB] = newName end
		end,
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
		create = function(self)
			local Wheel = oEditor.Wheel
			local bodyA = oEditor:getItem(self[Wheel.BodyA])
			local bodyB = oEditor:getItem(self[Wheel.BodyB])
			if not bodyA or not bodyB then
				return nil
			end
			return oJoint:collide(self[Wheel.Collision]):wheel(
				bodyA,bodyB,
				self[Wheel.WorldPos],
				self[Wheel.Axis],
				self[Wheel.MaxMotorTorque],
				self[Wheel.MotorSpeed],
				self[Wheel.Frequency],
				self[Wheel.Damping])
		end,
		rename = function(self,oldName,newName)
			local Wheel = oEditor.Wheel
			if self[Wheel.BodyA] == oldName then self[Wheel.BodyA] = newName end
			if self[Wheel.BodyB] == oldName then self[Wheel.BodyB] = newName end
		end,
	},
}

for shapeName,shapeDefine in pairs(defaultShapeData) do
	oEditor[shapeName] = {ItemType=0}
	for index,property in ipairs(shapeDefine) do
		local createFunc = shapeDefine.create
		local renameFunc = shapeDefine.rename
		oEditor[shapeName][property[1]] = index
		oEditor[shapeName].create = createFunc
		oEditor[shapeName].rename = renameFunc
		oEditor["new"..shapeName] = function(self)
			local newData = {[0]=shapeName}
			for i,v in ipairs(shapeDefine) do
				newData[i] = type(v[2]) == "function" and v[2]() or v[2]
			end
			newData.create = createFunc
			if renameFunc then
				newData.renameListener = oListener("editor.rename",function(args)
					renameFunc(newData,args.oldName,args.newName)
				end)
			end
			return newData
		end
	end
end

oEditor.bodyData = {}
oEditor.addData = function(self,data)
	table.insert(self.bodyData,data)
	oEvent:send("editor.bodyData",self.bodyData)
end
oEditor.removeData = function(self,data)
	for i,v in ipairs(self.bodyData) do
		if v == data then
			table.remove(self.bodyData,i)
			local item = oEditor.items[data[1]]
			if item then
				item:destroy()
				oEditor.items[data[1]] = nil
			end
			oEvent:send("editor.bodyData",self.bodyData)
			break
		end
	end
end
oEditor.clearData = function(self)
	self.bodyData = {}
	oEvent:send("editor.bodyData",self.bodyData)
end

oEditor.items = {}
oEditor.addItem = function(self,name,item)
	if name == "" then return end
	self.items[name] = item
end
oEditor.removeItem = function(self,name)
	if name == "" then return end
	self.items[name] = nil
end
oEditor.rename = function(self,oldName,newName)
	if oldName == "" or newName == "" then return end
	local item = self.items[oldName]
	self.items[oldName] = nil
	self.items[newName] = item
	oEvent:send("editor.rename",{oldName=oldName,newName=newName})
end
oEditor.getItem = function(self,name)
	if name == "" then return nil end
	return self.items[name]
end
oEditor.clearItems = function(self)
	self.items = {}
end
oEditor.getUsableName = function(self,originalName)
	if self.items[originalName] then
		local counter = 1
		local nawName = nil
		local usable = false
		repeat
			nawName = originalName..tostring(counter)
			usable = (oEditor.items[nawName] == nil)
		until usable
		return nawName
	else
		return originalName
	end
end

local itemToString = nil
local valueToString = nil
valueToString = function(value,pre)
	local str = pre
	local typeName = tolua.type(value)
	if typeName == "table" then
		str = str.."{\n"
		for _,v in ipairs(value) do
			local typeName = tolua.type(v)
			if typeName == "oVec2" then
				str = str..pre.."\toVec2("..tostring(v.x)..","..tostring(v.y).."),\n"
			elseif typeName == "table" then
				str = str..itemToString(v,pre.."\t")
			end
		end
		str = str..pre.."},\n"
	elseif typeName == "oVec2" then
		str = str.."oVec2("..tostring(value.x)..","..tostring(value.y).."),\n"
	elseif typeName == "CCSize" then
		str = str.."CCSize("..tostring(value.width)..","..tostring(value.height).."),\n"
	elseif typeName == "string" then
		str = str.."\""..value.."\",\n"
	else
		str = str..tostring(value)..",\n"
	end
	return str
end
itemToString = function(item,pre)
	local str = ""
	str = str..pre.."{\n"
	str = str..pre.."\t[0]=\""..item[0].."\",\n"
	for _,v in ipairs(item) do
		str = str..valueToString(v,pre.."\t")
	end
	str = str..pre.."},\n"
	return str
end

oEditor.dumpData = function(self,filename)
	local str = [[local oVec2 = require("oVec2")
local CCSize = require("CCSize")

local data =
{
]]
	for _,data in ipairs(oEditor.bodyData) do
		str = str..itemToString(data,"\t")
	end
	str = str.."}\n\nreturn data\n"
	oContent:saveToFile(CCFileUtils.writablePath..filename,str)
end

oEditor.loadData = function(self,filename)
	self.bodyData = dofile(CCFileUtils.writablePath..filename)
	if not self.bodyData then return end
	for _,data in ipairs(self.bodyData) do
		local shapeName = data[0]
		local createFunc = oEditor[shapeName].create
		local renameFunc = oEditor[shapeName].rename
		data.create = createFunc
		local subShapes = data[oEditor[shapeName].SubShapes]
		if subShapes then
			for _,subShape in ipairs(subShapes) do
				subShape.create = oEditor[subShape[0]].create
			end
		end
		if renameFunc then
			data.renameListener = oListener("editor.rename",function(args)
				renameFunc(data,args.oldName,args.newName)
			end)
		end
		data[1] = oEditor:getUsableName(data[1])
		local item = data.create(data)
		self:addItem(data[1],item)
	end
	-- TODO
end

return oEditor
