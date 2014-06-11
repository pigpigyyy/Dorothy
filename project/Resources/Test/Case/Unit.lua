local oButton = require("ActionEditor/Script/oButton")

local scene = CCScene()

local world = oPlatformWorld()
scene:addChild(world)

local aiTag = 1
oAI:add(aiTag,oAct(oAction.Idle))

local unitDef = oUnitDef()
unitDef.model = "ActionEditor/Model/Output/xiaoli.model"
unitDef.static = false
unitDef.move = 100
unitDef.density = 1
unitDef.friction = 1
unitDef.restitution = 0
unitDef.reflexArc = aiTag
unitDef:setActions(
{
	oAction.Walk,
	oAction.Stop,
	oAction.Turn,
	oAction.Idle,
	oAction.MeleeAttack,
})

local unit = oUnit(unitDef,world)
unit.group = 1
unit.position = oVec2(400,300)
world:addChild(unit)

local terrainDef = oBodyDef()
terrainDef.type = oBodyDef.Static
terrainDef:attachPolygon(800,10,1,1,0)

local terrain = oBody(terrainDef,world)
terrain.group = oData.GroupTerrain
terrain.position = oVec2(400,0)
world:addChild(terrain)

local menu = CCMenu()
menu.anchor = oVec2.zero
world.UILayer:addChild(menu)

local btn = oButton("Walk",16,60,nil,10,10,
	function()
		if unit.currentAction and unit.currentAction.id == oAction.Walk then
			unit:doIt(oAction.Stop)
		else
			unit:doIt(oAction.Walk)
		end
	end)
menu:addChild(btn)
btn.anchor = oVec2.zero
btn = oButton("Turn",16,60,nil,80,10,
	function()
		unit:doIt(oAction.Turn)
	end)
btn.anchor = oVec2.zero
menu:addChild(btn)
btn = oButton("Attack",16,60,nil,150,10,
	function()
		unit:doIt(oAction.MeleeAttack)
	end)
btn.anchor = oVec2.zero
menu:addChild(btn)

CCDirector:run(CCScene:progressCCW(1,scene))
