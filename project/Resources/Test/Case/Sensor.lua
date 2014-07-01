--[[local CCScene = require("CCScene")
local oWorld = require("oWorld")
local CCLabelTTF = require("CCLabelTTF")
local oVec2 = require("oVec2")
local oBodyDef = require("oBodyDef")
local oBody = require("oBody")
local oSensor = require("oSensor")
local CCDirector = require("CCDirector")
]]
local scene = CCScene()

local world = oWorld()
world:setShouldContact(0,0,true)
world.showDebug = true
scene:addChild(world)

local label = CCLabelTTF("","Arial",24)
label.position = oVec2(400,300)
world:addChild(label)

local terrainDef = oBodyDef()
local vertices = {}
local count = 50
local radius = 300
for i = 0, count-1 do
	local angle = 2*math.pi*i/count
	table.insert(vertices,oVec2(radius*math.cos(angle),radius*math.sin(angle)))
end
terrainDef:attachLoop(vertices,0.4,0)

local sensorTag = 1
terrainDef:attachCircleSensor(sensorTag,oVec2(0,-270),30)
local terrain = oBody(terrainDef,world,oVec2(400,300))
world:addChild(terrain)

local sensor = terrain:getSensorByTag(sensorTag)
sensor:addHandler(oSensor.Enter,function(sensor,body)
	label.text = "Enter"
	body.angularRate = body.angularRate > 0 and 1000 or -1000
end)
sensor:addHandler(oSensor.Leave,function(sensor,body)
	label.text = "Leave"
end)

local circleDef = oBodyDef()
circleDef.type = oBodyDef.Dynamic
circleDef:attachCircle(20,5,0.8,0)

local circle = oBody(circleDef,world,oVec2(180,500))
circle.angularRate = -1800
world:addChild(circle)

CCDirector:run(scene)
