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
local oWorld = require("oWorld")
local CCScheduler = require("CCScheduler")
local CCDirector = require("CCDirector")
local CCNode = require("CCNode")

local winSize = CCDirector.winSize

local oEditor = CCScene()

oEditor.isPlaying = false
oEditor.origin = oVec2(
		60+(winSize.width-120-180)*0.5,
		winSize.height*0.5)
oEditor.currentData = nil
oEditor.isFixed = true
oEditor.scale = 1
oEditor.names = {}
oEditor.bodyData = {}
oEditor.items = {}
oEditor.input = oContent.writablePath.."Body/Input/"
oEditor.output = oContent.writablePath.."Body/Output/"
oEditor.topMost = 9999
oEditor.currentFile = nil
oEditor.fixX = false
oEditor.fixY = false

oEditor.round = function(self,val)
	if type(val) == "number" then
		return val > 0 and math.floor(val+0.5) or math.ceil(val-0.5)
	else
		return oVec2(val.x > 0 and math.floor(val.x+0.5) or math.ceil(val.x-0.5),
			val.y > 0 and math.floor(val.y+0.5) or math.ceil(val.y-0.5))
	end
end

if not oContent:exist(oEditor.input) then
	oContent:mkdir(oEditor.input)
end
if not oContent:exist(oEditor.output) then
	oContent:mkdir(oEditor.output)
end

local worldScheduler = CCScheduler()
worldScheduler.timeScale = 0
oEditor.worldScheduler = worldScheduler
CCDirector.scheduler:shedule(oEditor.worldScheduler)
oEditor.world = oWorld()
oEditor.world.scheduler = oEditor.worldScheduler
oEditor.world.showDebug = true
oEditor.world:setShouldContact(0,0,true)
oEditor.world:registerEventHandler(function(eventType)
	if eventType == CCNode.Exited then
		CCDirector.scheduler:unshedule(oEditor.worldScheduler)
	end
end)
local worldNode = CCNode()
oEditor.world:addChild(worldNode)
oEditor.worldNode = worldNode

oEditor.touchPriorityEditMenu = CCMenu.DefaultHandlerPriority
oEditor.touchPrioritySettingPanel = CCMenu.DefaultHandlerPriority+1
oEditor.touchPriorityViewPanel = CCMenu.DefaultHandlerPriority+3
oEditor.touchPriorityEditControl = CCMenu.DefaultHandlerPriority+5
oEditor.touchPriorityVRuler = CCMenu.DefaultHandlerPriority+8
oEditor.touchPriorityHRuler = CCMenu.DefaultHandlerPriority+9
oEditor.touchPriorityViewArea = CCMenu.DefaultHandlerPriority+10

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

local function rename(self,oldName,newName)
	local change = false
	if self:get("BodyA") == oldName then
		self:set("BodyA",newName)
		change = true
	elseif self:get("BodyB") == oldName then
		self:set("BodyB",newName)
		change = true
	end
	if change then
		oEditor:resetItem(self)
	end
end

local function reset(self,name)
	if self:get("BodyA") == name or self:get("BodyB") == name then
		oEditor:resetItem(self)
	end
end

local defaultShapeData =
{
	Rectangle =
	{
		{"ItemType","Rectangle"}, -- 1
		{"Name","rect"}, -- 2
		{"Type",oBodyDef.Dynamic}, -- 3
		{"Position",PointZero}, -- 4
		{"Angle",0}, -- 5
		{"Center",PointZero}, -- 6
		{"Size",Size(100,100)}, -- 7
		{"Density",1}, -- 8
		{"Friction",0.4}, -- 9
		{"Restitution",0.4}, -- 10
		{"LinearDamping", 0}, -- 11
		{"AngularDamping",0}, -- 12
		{"FixedRotation",false}, -- 13
		{"GravityScale",1}, -- 14
		{"Bullet",false}, -- 15
		{"Sensor",false}, -- 16
		{"SensorTag",0}, -- 17
		{"Face",""}, -- 18
		{"FaceAnchor",PointZero}, -- 19
		{"SubShapes",false}, -- 20
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
		{"ItemType","Circle"}, -- 1
		{"Name","circle"}, -- 2
		{"Type",oBodyDef.Dynamic}, -- 3
		{"Position",PointZero}, -- 4
		{"Angle",0}, -- 5
		{"Center",PointZero}, -- 6
		{"Radius",50}, -- 7
		{"Density",1}, -- 8
		{"Friction",0.4}, -- 9
		{"Restitution",0.4}, -- 10
		{"LinearDamping",0}, -- 11
		{"AngularDamping",0}, -- 12
		{"FixedRotation",false}, -- 13
		{"GravityScale",1}, -- 14
		{"Bullet",false}, -- 15
		{"Sensor",false}, -- 16
		{"SensorTag",0}, -- 17
		{"Face",""}, -- 18
		{"FaceAnchor",PointZero}, -- 19
		{"SubShapes",false}, -- 20
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
		{"ItemType","Polygon"}, -- 1
		{"Name","poly"}, -- 2
		{"Type",oBodyDef.Dynamic}, -- 3
		{"Position",PointZero}, -- 4
		{"Angle",0}, -- 5
		{"Vertices",false},  -- 6
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
		{"ItemType","Chain"}, -- 1
		{"Name","chain"}, -- 2
		{"Type",oBodyDef.Dynamic}, -- 3
		{"Position",PointZero}, -- 4
		{"Angle",0}, -- 5
		{"Vertices",false}, -- 6
		{"Friction",0.4}, -- 7
		{"Restitution",0.4}, -- 8
		{"LinearDamping",0}, -- 9
		{"AngularDamping",0}, -- 10
		{"FixedRotation",false}, -- 11
		{"GravityScale",1}, -- 12
		{"Bullet",false}, -- 13
		{"Face",""}, -- 14
		{"FaceAnchor",PointZero}, -- 15
		{"SubShapes",false}, -- 16
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
		{"ItemType","Loop"}, -- 1
		{"Name","loop"}, -- 2
		{"Type",oBodyDef.Dynamic}, -- 3
		{"Position",PointZero}, -- 4
		{"Angle",0}, -- 5
		{"Vertices",false}, -- 6
		{"Friction",0.4}, -- 7
		{"Restitution",0.4}, -- 8
		{"LinearDamping",0}, -- 9
		{"AngularDamping",0}, -- 10
		{"FixedRotation",false}, -- 11
		{"GravityScale",1}, -- 12
		{"Bullet",false}, -- 13
		{"Face",""}, -- 14
		{"FaceAnchor",PointZero}, -- 15
		{"SubShapes",false}, -- 16
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
		{"ItemType","SubRectangle"}, -- 1
		{"Center",PointZero}, -- 2
		{"Angle",0}, -- 3
		{"Size",Size(100,100)}, -- 4
		{"Density",1}, -- 5
		{"Friction",0.4}, -- 6
		{"Restitution",0.4}, -- 7
		{"Sensor",false}, -- 8
		{"SensorTag",0}, -- 9
		{"Index",0}, -- 10
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
		{"ItemType","SubCircle"}, -- 1
		{"Center",PointZero}, -- 2
		{"Radius",50}, -- 3
		{"Density",1}, -- 4
		{"Friction",0.4}, -- 5
		{"Restitution",0.4}, -- 6
		{"Sensor",false}, -- 7
		{"SensorTag",0}, -- 8
		{"Index",0}, -- 9
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
		{"ItemType","SubPolygon"}, -- 1
		{"Vertices",false}, -- 2
		{"Density",1}, -- 3
		{"Friction",0.4}, -- 4
		{"Restitution",0.4}, -- 5
		{"Sensor",false}, -- 6
		{"SensorTag",0}, -- 7
		{"Index",0}, -- 8
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
		{"ItemType","SubChain"}, -- 1
		{"Vertices",false}, -- 2
		{"Friction",0.4}, -- 3
		{"Restitution",0.4}, -- 4
		{"Index",0}, -- 5
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
		{"ItemType","SubLoop"}, -- 1
		{"Vertices",false}, -- 2
		{"Friction",0.4}, -- 3
		{"Restitution",0.4}, -- 4
		{"Index",0}, -- 5
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
		{"ItemType","Distance"}, -- 1
		{"Name","distance"}, -- 2
		{"Collision",false}, -- 3
		{"BodyA",""}, -- 4
		{"BodyB",""}, -- 5
		{"AnchorA",PointZero}, -- 6
		{"AnchorB",PointZero}, -- 7
		{"Frequency",0}, -- 8
		{"Damping",0}, -- 9
		create = function(self)
			local Distance = oEditor.Distance
			local bodyA = oEditor:getItem(self[Distance.BodyA])
			local bodyB = oEditor:getItem(self[Distance.BodyB])
			if not bodyA or not bodyB or bodyA == bodyB then
				return nil
			end
			return oJoint:collide(self[Distance.Collision]):distance(
				bodyA,bodyB,
				self[Distance.AnchorA],
				self[Distance.AnchorB],
				self[Distance.Frequency],
				self[Distance.Damping])
		end,
		rename = rename,
		reset = reset,
	},
	Friction =
	{
		{"ItemType","Friction"}, -- 1
		{"Name","friction"}, -- 2
		{"Collision",false}, -- 3
		{"BodyA",""}, -- 4
		{"BodyB",""}, -- 5
		{"WorldPos",PointZero}, -- 6
		{"MaxForce",0}, -- 7
		{"MaxTorque",0}, -- 8
		create = function(self)
			local Friction = oEditor.Friction
			local bodyA = oEditor:getItem(self[Friction.BodyA])
			local bodyB = oEditor:getItem(self[Friction.BodyB])
			if not bodyA or not bodyB or bodyA == bodyB then
				return nil
			end
			return oJoint:collide(self[Friction.Collision]):friction(
				bodyA,bodyB,
				self[Friction.WorldPos],
				self[Friction.MaxForce],
				self[Friction.MaxTorque])
		end,
		rename = rename,
		reset = reset,
	},
	Gear =
	{
		{"ItemType","Gear"}, -- 1
		{"Name","gear"}, -- 2
		{"Collision",false}, -- 3
		{"JointA",""}, -- 4
		{"JointB",""}, -- 5
		{"Ratio",1}, -- 6
		create = function(self)
			local Gear = oEditor.Gear
			local jointA = oEditor:getItem(self[Gear.JointA])
			local jointB = oEditor:getItem(self[Gear.JointB])
			if not jointA or not jointB or jointA == jointB then
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
		reset = function(self,name)
			if self:get("JointA") == name or self:get("JointB") == name then
				oEditor:resetItem(self)
			end
		end,
	},
	Spring =
	{
		{"ItemType","Spring"}, -- 1
		{"Name","spring"}, -- 2
		{"Collision",false}, -- 3
		{"BodyA",""}, -- 4
		{"BodyB",""}, -- 5
		{"Offset",PointZero}, -- 6
		{"AngularOffset",0}, -- 7
		{"MaxForce",0}, -- 8
		{"MaxTorque",0}, -- 9
		{"CorrectionFactor",0.3}, -- 10
		create = function(self)
			local Spring = oEditor.Spring
			local bodyA = oEditor:getItem(self[Spring.BodyA])
			local bodyB = oEditor:getItem(self[Spring.BodyB])
			if not bodyA or not bodyB or bodyA == bodyB then
				return nil
			end
			return oJoint:collide(self[Spring.Collision]):spring(
				bodyA,bodyB,
				self[Spring.Offset],
				self[Spring.AngularOffset],
				self[Spring.MaxForce],
				self[Spring.MaxTorque],
				self[Spring.CorrectionFactor])
		end,
		rename = rename,
		reset = reset,
	},
	Prismatic =
	{
		{"ItemType","Prismatic"}, -- 1
		{"Name","prism"}, -- 2
		{"Collision",false}, -- 3
		{"BodyA",""}, -- 4
		{"BodyB",""}, -- 5
		{"WorldPos",PointZero}, -- 6
		{"Axis",Point(1,0)}, -- 7
		{"Lower",0}, -- 8
		{"Upper",0}, -- 9
		{"MaxMotorForce",0}, -- 10
		{"MotorSpeed",0}, -- 11
		create = function(self)
			local Prismatic = oEditor.Prismatic
			local bodyA = oEditor:getItem(self[Prismatic.BodyA])
			local bodyB = oEditor:getItem(self[Prismatic.BodyB])
			if not bodyA or not bodyB or bodyA == bodyB then
				return nil
			end
			return oJoint:collide(self[Prismatic.Collision]):prismatic(
				bodyA,bodyB,
				self[Prismatic.WorldPos],
				self[Prismatic.Axis],
				self[Prismatic.Lower],
				self[Prismatic.Upper],
				self[Prismatic.MaxMotorForce],
				self[Prismatic.MotorSpeed])
		end,
		rename = rename,
		reset = reset,
	},
	Pulley =
	{
		{"ItemType","Pulley"}, -- 1
		{"Name","pulley"}, -- 2
		{"Collision",true}, -- 3
		{"BodyA",""}, -- 4
		{"BodyB",""}, -- 5
		{"AnchorA",PointZero}, -- 6
		{"AnchorB",PointZero}, -- 7
		{"GroundA",Point(-100,100)}, -- 8
		{"GroundB",Point(100,100)}, -- 9
		{"Ratio",1}, -- 9
		create = function(self)
			local Pulley = oEditor.Pulley
			local bodyA = oEditor:getItem(self[Pulley.BodyA])
			local bodyB = oEditor:getItem(self[Pulley.BodyB])
			if not bodyA or not bodyB or bodyA == bodyB then
				return nil
			end
			return oJoint:collide(self[Pulley.Collision]):pulley(
				bodyA,bodyB,
				self[Pulley.AnchorA],
				self[Pulley.AnchorB],
				self[Pulley.GroundA],
				self[Pulley.GroundB],
				self[Pulley.Ratio])
		end,
		rename = rename,
		reset = reset,
	},
	Revolute =
	{
		{"ItemType","Revolute"}, -- 1
		{"Name","revolute"}, -- 2
		{"Collision",false}, -- 3
		{"BodyA",""}, -- 4
		{"BodyB",""}, -- 5
		{"WorldPos",PointZero}, -- 6
		{"LowerAngle",0}, -- 7
		{"UpperAngle",0}, -- 8
		{"MaxMotorTorque",0}, -- 9
		{"MotorSpeed",0}, -- 10
		create = function(self)
			local Revolute = oEditor.Revolute
			local bodyA = oEditor:getItem(self[Revolute.BodyA])
			local bodyB = oEditor:getItem(self[Revolute.BodyB])
			if not bodyA or not bodyB or bodyA == bodyB then
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
		rename = rename,
		reset = reset,
	},
	Rope =
	{
		{"ItemType","Rope"}, -- 1
		{"Name","rope"}, -- 2
		{"Collision",false}, -- 3
		{"BodyA",""}, -- 4
		{"BodyB",""}, -- 5
		{"AnchorA",PointZero}, -- 6
		{"AnchorB",PointZero}, -- 7
		{"MaxLength",100}, -- 8
		create = function(self)
			local Rope = oEditor.Rope
			local bodyA = oEditor:getItem(self[Rope.BodyA])
			local bodyB = oEditor:getItem(self[Rope.BodyB])
			if not bodyA or not bodyB or bodyA == bodyB then
				return nil
			end
			return oJoint:collide(self[Rope.Collision]):rope(
				bodyA,bodyB,
				self[Rope.AnchorA],
				self[Rope.AnchorB],
				self[Rope.MaxLength])
		end,
		rename = rename,
		reset = reset,
	},
	Weld =
	{
		{"ItemType","Weld"}, -- 1
		{"Name","weld"}, -- 2
		{"Collision",false}, -- 3
		{"BodyA",""}, -- 4
		{"BodyB",""}, -- 5
		{"WorldPos",PointZero}, -- 6
		{"Frequency",0}, -- 7
		{"Damping",0}, -- 8
		create = function(self)
			local Weld = oEditor.Weld
			local bodyA = oEditor:getItem(self[Weld.BodyA])
			local bodyB = oEditor:getItem(self[Weld.BodyB])
			if not bodyA or not bodyB or bodyA == bodyB then
				return nil
			end
			return oJoint:collide(self[Weld.Collision]):weld(
				bodyA,bodyB,
				self[Weld.WorldPos],
				self[Weld.Frequency],
				self[Weld.Damping])
		end,
		rename = rename,
		reset = reset,
	},
	Wheel =
	{
		{"ItemType","Wheel"}, -- 1
		{"Name","wheel"}, -- 2
		{"Collision",false}, -- 3
		{"BodyA",""}, -- 4
		{"BodyB",""}, -- 5
		{"WorldPos",PointZero}, -- 6
		{"Axis",Point(100,0)}, -- 7
		{"MaxMotorTorque",0}, -- 8
		{"MotorSpeed",0}, -- 9
		{"Frequency",2}, -- 10
		{"Damping",0.7}, -- 11
		create = function(self)
			local Wheel = oEditor.Wheel
			local bodyA = oEditor:getItem(self[Wheel.BodyA])
			local bodyB = oEditor:getItem(self[Wheel.BodyB])
			if not bodyA or not bodyB or bodyA == bodyB then
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
		rename = rename,
		reset = reset,
	},
}

local function setFunc(data,name,value)
	data[oEditor[data[1]][name]] = value
	oEvent:send("editor.change")
end
local function getFunc(data,name)
	return data[oEditor[data[1]][name]]
end
local function hasFunc(data,name)
	return oEditor[data[1]][name] ~= nil
end

for shapeName,shapeDefine in pairs(defaultShapeData) do
	oEditor[shapeName] = {}
	for index,property in ipairs(shapeDefine) do
		local createFunc = shapeDefine.create
		local renameFunc = shapeDefine.rename
		local resetFunc = shapeDefine.reset
		oEditor[shapeName][property[1]] = index
		oEditor[shapeName].create = createFunc
		oEditor[shapeName].rename = renameFunc
		oEditor[shapeName].reset = resetFunc
		oEditor["new"..shapeName] = function(self)
			local newData = {}
			for i,v in ipairs(shapeDefine) do
				newData[i] = type(v[2]) == "function" and v[2]() or v[2]
			end
			newData.create = createFunc
			newData.set = setFunc
			newData.get = getFunc
			newData.has = hasFunc
			if renameFunc then
				newData.renameListener = oListener("editor.rename",function(args)
					renameFunc(newData,args.oldName,args.newName)
				end)
			end
			if resetFunc then
				newData.resetListener = oListener("editor.reset",function(name)
					resetFunc(newData,name)
				end)
			end
			return newData
		end
	end
end

oEditor.addSubData = function(self,data,subData)
	local subShapes = data:get("SubShapes")
	if not subShapes then
		subShapes = {subData,}
		data:set("SubShapes",subShapes)
	else
		table.insert(subShapes,subData)
	end
	for _,shape in ipairs(subShapes) do
		shape.parent = data
		shape.set = setFunc
		shape.get = getFunc
		shape.has = hasFunc
	end
	oEditor:resetItem(data)
	oEvent:send("editor.bodyData",self.bodyData)
end

oEditor.addData = function(self,data)
	if not data.resetListener then
		local bodyData = self.bodyData
		for i = #bodyData,1,-1 do
			if not bodyData[i].resetListener then
				table.insert(bodyData,i+1,data)
				break
			end
		end
	else
		table.insert(self.bodyData,data)
	end
	oEditor:checkName(data)
	local subShapes = data:get("SubShapes")
	if subShapes then
		for _,shape in ipairs(subShapes) do
			shape.parent = data
			shape.set = setFunc
			shape.get = getFunc
			shape.has = hasFunc
		end
	end
	oEditor:resetItem(data)
	oEvent:send("editor.bodyData",self.bodyData)
end
oEditor.getData = function(self,name)
	for _,data in ipairs(self.bodyData) do
		if data:get("Name") == name then
			return data
		end
	end
	return nil
end
oEditor.removeData = function(self,data)
	local item = data.parent or data
	for i,v in ipairs(self.bodyData) do
		if v == item then
			if data.parent then
				local subShapes = data.parent:get("SubShapes")
				for index,sb in ipairs(subShapes) do
					if sb == data then
						table.remove(subShapes,index)
						if #subShapes == 0 then
							data.parent:set("SubShapes",false)
						end
						break
					end
				end
				oEditor:resetItem(data.parent)
			else
				local name = data:get("Name")
				table.remove(self.bodyData,i)
				if data.renameListener then
					data.renameListener.enabled = false
				end
				if data.resetListener then
					data.resetListener.enabled = false
				end
				oEditor.names[name] = nil
				local item = oEditor.items[name]
				if item then
					item:destroy()
					oEditor.items[name] = nil
				end
			end
			oEvent:send("editor.bodyData",self.bodyData)
			break
		end
	end
end
oEditor.clearData = function(self)
	for _,data in ipairs(oEditor.bodyData) do
		if data.renameListener then
			data.renameListener.enabled = false
			data.renameListener = nil
		end
		if data.resetListener then
			data.resetListener.enabled = false
			data.resetListener = nil
		end
	end
	self.bodyData = {}
	oEditor.names = {}
	oEditor:clearItems()
	oEvent:send("editor.bodyData",self.bodyData)
end

oEditor.resetItem = function(self,data)
	if data.parent then data = data.parent end
	oEditor:removeItem(data)
	local item = data:create()
	local name = data:get("Name")
	oEditor.items[name] = item
	if item then item.dataItem = data end
	oEvent:send("editor.reset",name)
	return item
end
oEditor.resetItems = function(self)
	self:clearItems()
	for _,data in ipairs(self.bodyData) do
		self:resetItem(data)
	end
end
oEditor.removeItem = function(self,data)
	if data.parent then data = data.parent end
	local name = data:get("Name")
	local item = oEditor.items[name]
	if item then item:destroy() end
	self.items[name] = nil
end
oEditor.rename = function(self,oldName,newName)
	if oldName == newName then return end
	local item = self.items[oldName]
	self.items[oldName] = nil
	self.items[newName] = item
	self.names[oldName] = nil
	self.names[newName] = true
	oEvent:send("editor.rename",{oldName=oldName,newName=newName})
end
oEditor.getItem = function(self,arg) -- arg: name or data
	if type(arg) == "string" then
		return self.items[arg]
	else
		if arg.parent then arg = arg.parent end
		return self.items[arg:get("Name")]
	end
end
oEditor.clearItems = function(self)
	for _,item in pairs(self.items) do
		item:destroy()
	end
	self.items = {}
end
oEditor.getUsableName = function(self,originalName)
	if originalName == "" then originalName = "name" end
	if self.names[originalName] then
		local counter = 1
		local nawName = nil
		local usable = false
		repeat
			nawName = originalName..tostring(counter)
			usable = (self.names[nawName] == nil)
			counter = counter+1
		until usable
		return nawName
	else
		return originalName
	end
end
oEditor.checkName = function(self,data)
	local oldName = data:get("Name")
	local newName = oEditor:getUsableName(oldName)
	oEditor.names[newName] = true
	if newName ~= oldName then
		data:set("Name",newName)
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
				str = str..pre.."\toVec2("..string.format("%.2f",v.x)..","..string.format("%.2f",v.y).."),\n"
			elseif typeName == "table" then
				str = str..itemToString(v,pre.."\t")
			end
		end
		str = str..pre.."},\n"
	elseif typeName == "oVec2" then
		str = str.."oVec2("..string.format("%.2f",value.x)..","..string.format("%.2f",value.y).."),\n"
	elseif typeName == "CCSize" then
		str = str.."CCSize("..string.format("%d",value.width)..","..string.format("%d",value.height).."),\n"
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
	for _,v in ipairs(item) do
		str = str..valueToString(v,pre.."\t")
	end
	str = str..pre.."},\n"
	return str
end

oEditor.dumpData = function(self,filename)
	local str = [[local oVec2 = require("oVec2")
local CCSize = require("CCSize")

return
{
]]
	for _,data in ipairs(oEditor.bodyData) do
		str = str..itemToString(data,"\t")
	end
	str = str.."}\n"
	oContent:saveToFile(oEditor.output..filename,str)
end

oEditor.loadData = function(self,filename)
	self:clearData()
	oEditor.currentData = nil
	self.bodyData = dofile(oEditor.output..filename)
	if not self.bodyData then return end
	oEditor.names = {}
	for _,data in ipairs(self.bodyData) do
		local shapeName = data[1]
		local createFunc = oEditor[shapeName].create
		local renameFunc = oEditor[shapeName].rename
		local resetFunc = oEditor[shapeName].reset
		data.create = createFunc
		data.set = setFunc
		data.get = getFunc
		data.has = hasFunc
		local subShapes = data[oEditor[shapeName].SubShapes]
		if subShapes then
			for _,subShape in ipairs(subShapes) do
				subShape.create = oEditor[subShape[1]].create
				subShape.parent = data
				subShape.set = setFunc
				subShape.get = getFunc
				subShape.has = hasFunc
			end
		end
		if renameFunc then
			data.renameListener = oListener("editor.rename",function(args)
				renameFunc(data,args.oldName,args.newName)
			end)
		end
		if resetFunc then
			data.resetListener = oListener("editor.reset",function(name)
				resetFunc(data,name)
			end)
		end
		oEditor:checkName(data)
	end
	oEditor:resetItems()
	oEvent:send("editor.bodyData",self.bodyData)
	-- TODO
end

-- bodyData[1]: ShapeName
-- bodyData[2]: ItemName -- SubShapes don`t have names

return oEditor
