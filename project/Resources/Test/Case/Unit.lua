local oButton = require("ActionEditor/Script/oButton")

local oPlatformWorld = require("oPlatformWorld")
local oAI = require("oAI")
local oAct = require("oAct")
local oUnitDef = require("oUnitDef")
local oUnit = require("oUnit")
local oVec2 = require("oVec2")
local oBodyDef = require("oBodyDef")
local oBody = require("oBody")
local oData = require("oData")
local CCMenu = require("CCMenu")
local CCLayer = require("CCLayer")
local CCRect = require("CCRect")
local oJoint = require("oJoint")
local CCDirector = require("CCDirector")
local CCScene = require("CCScene")

local scene = CCScene()

local world = oPlatformWorld()
scene:addChild(world)

oAI:add("doNothing",oAct("idle"))

local unitDef = oUnitDef()
unitDef.model = "ActionEditor/Model/Output/jiandunA.model"
unitDef.static = false
unitDef.move = 100
unitDef.density = 1
unitDef.friction = 1
unitDef.restitution = 0
unitDef.reflexArc = "doNothing"
unitDef:setActions(
{
	"walk",
	"cancel",
	"turn",
	"idle",
	"meleeAttack",
})

local unit = oUnit(unitDef,world,oVec2(400,300))
unit.moveSpeed = 0.9
unit.group = 1
unit:slots("ActionEnd",function(name) print(name,"end") end)
world:addChild(unit)

local terrainDef = oBodyDef()
terrainDef.type = oBodyDef.Static
terrainDef:attachPolygon(800,10,1,1,0)

local terrain = oBody(terrainDef,world,oVec2(400,0))
terrain.group = oData.GroupTerrain
world:addChild(terrain)

local menu = CCMenu()
menu.anchor = oVec2.zero
world.UILayer:addChild(menu)
local btn = oButton("Walk",16,60,nil,10,10,
	function()
		if unit:isDoing("walk") then
			unit:start("cancel")
		else
			unit:start("walk")
		end
	end)
menu:addChild(btn)
btn.anchor = oVec2.zero
btn = oButton("Turn",16,60,nil,80,10,
	function()
		unit:start("turn")
	end)
btn.anchor = oVec2.zero
menu:addChild(btn)

btn = oButton("Attack",16,60,nil,150,10,
	function()
		unit:start("meleeAttack")
		--[[oRoutine(once(function()
			print("Begin loading")
			wait(seconds(3))
			oCache:loadAsync({
				"ActionEditor/Model/Output/jixienv.png",
				"ActionEditor/Model/Output/boy.png",
				"ActionEditor/Model/Output/doll.png",
				"ActionEditor/Model/Output/flandre.png",
				"ActionEditor/Model/Output/girl.png",
				"ActionEditor/Model/Output/jixienv.model",
				"ActionEditor/Model/Output/nothing",
			},function(filename) print(filename) end)
			wait(seconds(3))
			print("End loading")
		end))
		--]]
	end)
btn.anchor = oVec2.zero
menu:addChild(btn)

local layer = CCLayer()
layer.touchEnabled = true
layer.anchor = oVec2.zero
scene:addChild(layer)

local joint = nil
layer:slots("TouchBegan",function(touch)
	local pos = world:convertToNodeSpace(touch.location)
	world:query(CCRect(pos.x-0.5,pos.y-0.5,1,1),function(body)
		if oData:isTerrain(body) then
			return true
		end
		if joint then
			joint:destroy()
		end
		joint = oJoint:move(true,terrain,body,pos,1000*body.mass)
		return true
	end)
	return true
end)

layer:slots("TouchMoved",function(touch)
	local pos = world:convertToNodeSpace(touch.location)
	if joint then
		joint.position = pos
	end
end)

local function touchEnded()
	if joint then
		joint:destroy()
		joint = nil
	end
end
layer:slots("TouchEnded",touchEnded)
layer:slots("TouchCancelled",touchEnded)

CCDirector:run(CCScene:crossFade(0.5,scene))
