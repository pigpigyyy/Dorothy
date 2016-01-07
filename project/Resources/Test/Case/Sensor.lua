Dorothy()

local Sensor = class(require('Test.Case.TestBase'))

function Sensor:__init()
    local world = oWorld()
    world:setShouldContact(0,0,true)
    world.showDebug = true
    self:addChild(world)

    local layer = CCLayerColor(ccColor4(0x22cccccc),CCDirector.winSize.width,CCDirector.winSize.height)
    layer.anchor = oVec2.zero
    self:addChild(layer)

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

    local center = oVec2(CCDirector.winSize.width*0.5,CCDirector.winSize.height*0.5)
    local circle = oBody(circleDef,world,oVec2(200,480))
    circle.angularRate = -1800
    world:addChild(circle)
    local drawNode = oLine({oVec2(-20,0),oVec2(20,0),oVec2.zero,oVec2(0,-20),oVec2(0,20)},ccColor4(0xff00ffff))
    world:addChild(drawNode)
    world.data = CCDictionary()
    world.data.joint = oJoint:rope(
    	true,terrain,circle,oVec2.zero,oVec2.zero,300)

    circle.receivingContact = true
    circle:slot("ContactStart",function(body,point)
    	drawNode.position = point
    	print(string.format("[%d,%d]",point.x,point.y))
    	label.text = "Contact: "..string.format("[%d,%d]",point.x,point.y)
    end)
    circle:slot("ContactEnd",function(body,point)
    	--label.text = "End"
    end)
end

return Sensor
