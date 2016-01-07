Dorothy()

local BodyDataTest = class(require('Test.Case.TestBase'))

function BodyDataTest:__init()
    local world = oPlatformWorld()
    world.camera.boudary = CCRect(-2500,-2500,5000,5000)
    world.camera.followRatio = oVec2(0.02,0.02)
    world:setShouldContact(0,0,true)
    world.showDebug = true
    self:addChild(world)

    local car = oBody("BodyEditor/Body/Output/car.body",world)
    car.data.wheel.enabled = true
    world:addChild(car)

    world.camera:follow(car.data.rect)
end

return BodyDataTest