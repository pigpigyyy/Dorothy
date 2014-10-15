--[[
local CCScene = require("CCScene")
local oWorld = require("oWorld")
local CCLabelTTF = require("CCLabelTTF")
local oVec2 = require("oVec2")
local oBodyDef = require("oBodyDef")
local oBody = require("oBody")
local oSensor = require("oSensor")
local CCDirector = require("CCDirector")
]]
setfenv(Dorothy())

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
terrainDef:attachCircle(oVec2(0,-270),30,1,0,1.0)
local terrain = oBody(terrainDef,world,oVec2(400,300))
world:addChild(terrain)
--[[
local sensor = terrain:getSensorByTag(sensorTag)
--]]
local circleDef = oBodyDef()
circleDef.type = oBodyDef.Dynamic
circleDef:attachCircle(20,5,0.8,1)

local circle = oBody(circleDef,world,oVec2(180,500))
circle.angularRate = -1800
world:addChild(circle)
local drawNode = oLine({oVec2(-20,0),oVec2(20,0),oVec2.zero,oVec2(0,-20),oVec2(0,20)},ccColor4(0xff00ffff))
world:addChild(drawNode)
circle:addHandler(oBody.ContactStart,function(body,point)
	drawNode.position = point
	label.text = "Contact: "..string.format("[%d,%d]",point.x,point.y)
end)
circle:addHandler(oBody.ContactEnd,function(body,point)
	--label.text = "End"
end)

CCDirector:run(scene)
