local oButton = require("ActionEditor/Script/oButton")
local wait = require("oRoutine").wait
local loop = require("oRoutine").loop
local seconds = require("oRoutine").seconds

local oPlatformWorld = require("oPlatformWorld")
local oAI = require("oAI")
local oAct = require("oAct")
local oAction = require("oAction")
local oUnitDef = require("oUnitDef")
local oUnit = require("oUnit")
local oVec2 = require("oVec2")
local oBodyDef = require("oBodyDef")
local oBody = require("oBody")
local oData = require("oData")
local CCMenu = require("CCMenu")
local CCLayer = require("CCLayer")
local CCTouch = require("CCTouch")
local CCRect = require("CCRect")
local oJoint = require("oJoint")
local CCDirector = require("CCDirector")
local CCScene = require("CCScene")
local CCTextureCache = require("CCTextureCache")

local scene = CCScene()

local world = oPlatformWorld()
scene:addChild(world)

local aiTag = 1
oAI:add(aiTag,oAct(oAction.Idle))

local unitDef = oUnitDef()
unitDef.model = "ActionEditor/Model/Output/jiandunA.model"
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
	oAction.MeleeAttack
})

local unit = oUnit(unitDef,world,oVec2(400,300))
unit.moveSpeed = 0.9
unit.group = 1
world:addChild(unit)
--[[unit:schedule(
	loop(function()
		print("start")
		wait(seconds(3))
		print("end")
	end))
--]]
local terrainDef = oBodyDef()
terrainDef.type = oBodyDef.Static
terrainDef:attachPolygon(800,10,1,1,0)

local terrain = oBody(terrainDef,world,oVec2(400,0))
terrain.group = oData.GroupTerrain
world:addChild(terrain)

local menu = CCMenu(false)
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
		print("Begin load")
		CCTextureCache:loadAsync(
			{
				"ActionEditor/Model/Output/jixienv.png",
				"ActionEditor/Model/Output/boy.png",
				"ActionEditor/Model/Output/doll.png",
				"ActionEditor/Model/Output/flandre.png",
				"ActionEditor/Model/Output/girl.png",
			},function(filename, texture) print("Loaded", filename, texture) end)
	end)
btn.anchor = oVec2.zero
menu:addChild(btn)

local layer = CCLayer()
layer.touchEnabled = true
layer.anchor = oVec2.zero
scene:addChild(layer)

local joint = nil
layer:registerTouchHandler(function(eventType, touch)
	local pos = world:convertToNodeSpace(touch.location)
	if eventType == CCTouch.Began then
		world:query(CCRect(pos.x-0.5,pos.y-0.5,1,1),function(body)
			if oData:isTerrain(body) then
				return true
			end
			if joint then
				joint:destroy()
			end
			joint = oJoint:collide(true):move(terrain,body,pos,1000*body.mass)
			return true
		end)
	elseif eventType == CCTouch.Moved then
		if joint then
			joint.position = pos
		end
	elseif eventType == CCTouch.Ended or eventType == CCTouch.Cancelled then
		if joint then
			joint:destroy()
			joint = nil
		end
	end
	return true
end)

CCDirector:run(scene)
