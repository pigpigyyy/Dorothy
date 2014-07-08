setfenv(1,Dorothy())
local wait = oRoutine.wait
local once = oRoutine.once
local loop = oRoutine.loop
local seconds = oRoutine.seconds
local cycle = oRoutine.cycle
local oTextField = require("ActionEditor/Script/oTextField")

oAction:add(oAction.UserID,998,0,0,
	--self=oAction
	function(self)
		return true
	end,
	function(self)
		print("begin")
		local owner = self.owner
		wait(cycle(1,
			function()
				owner.velocityX = 100
			end))
		wait(cycle(1,
			function()
				owner.velocityX = -100
			end))
	end,
	function(self)
		print("end")
	end)

local world = oPlatformWorld()

local unitDef = oUnitDef()
unitDef.model = "ActionEditor/Model/Output/xiaoli.model"
unitDef.static = false
unitDef.density = 1
unitDef.restitution = 0.4
unitDef.friction = 0.4
unitDef.move = 40
unitDef:setActions(
{
	oAction.Walk,
	oAction.UserID
})

local unit = oUnit(unitDef,world,oVec2(400,300))
unit.group = 1
unit:doIt(oAction.UserID)

--[[
local routine = loop(function()
	wait(seconds(5))
	wait(function() return not unit.onSurface end)
	unit:doIt(oAction.Walk)
end)
oRoutine(routine)
--]]

local bodyDef = oBodyDef()
bodyDef:attachPolygon(800,10,1,0.4,0.4)
local body = oBody(bodyDef,world,oVec2(400,0))
body.group = oData.GroupTerrain

local scene = CCScene()
scene:addChild(world)
world:addChild(unit)
world:addChild(body)
--scene:addChild(model)
--scene:addChild(model2)

local textField = oTextField(120,18,17,10,
	function(self)
		print(self.text)
		self.text = ""
		oRoutine(once(function()
			wait(seconds(0))
			self:attachWithIME()
		end))
	end)
textField.anchor = oVec2.zero
textField.position = oVec2(2,1)
textField:attachWithIME()
scene:addChild(textField)

CCDirector:run(scene)

--[[local class,property,classfield,classmethod = unpack(require("class"))

local ClassA = class(
{
	name = "aaaa",
	show = function(self)
		print("XXX")
	end,
})

local a = ClassA()
print(a.name)
a:show()
--]]