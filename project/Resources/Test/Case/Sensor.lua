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

circle:addHandler(oContact.Start,function(body,contact)
	--contact=oContact
	local points = contact.points
	if #points ~= 0 then
		label.text = "Contact:["..string.format("%d",points[1].x)..","..string.format("%d",points[1].y).."]" 
	else
		print("No contact"..string.format("[%d,%d]",contact.normal.x,contact.normal.y))
	end
end)
circle:addHandler(oContact.End,function(body,contact)
	--label.text = "End"
end)

CCDirector:run(scene)
