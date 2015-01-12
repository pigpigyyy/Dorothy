local CCScene = require("CCScene")
local oPlatformWorld = require("oPlatformWorld")
local oVec2 = require("oVec2")
local oBodyLoader = require("oBodyLoader")
local CCDirector = require("CCDirector")
local CCRect = require("CCRect")

local scene = CCScene()

local world = oPlatformWorld()
world.camera.boudary = CCRect(-2500,-2500,5000,5000)
world.camera.followRatio = oVec2(0.02,0.02)
world:setShouldContact(0,0,true)
world.showDebug = true
scene:addChild(world)

local carDef = oBodyLoader:load("Test/Case/BodyData.lua")
local car = oBodyLoader:create(carDef,world,oVec2.zero)
car.data.wheel.enabled = true
world:addChild(car)
world.camera:follow(car.children[1])

CCDirector:run(scene)
