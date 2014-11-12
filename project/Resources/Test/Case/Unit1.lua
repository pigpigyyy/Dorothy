setfenv(Dorothy())

local wait = oRoutine.wait
local once = oRoutine.once
local loop = oRoutine.loop
local seconds = oRoutine.seconds
local cycle = oRoutine.cycle
local oTextField = require("ActionEditor/Script/oTextField")
local oButton = require("ActionEditor/Script/oButton")
--[[
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
--]]

local CCKey =
{
	Left = 0x25,
	Up = 0x26,
	Right = 0x27,
	Down = 0x28,
}

oAI.getUnitByTag = function(self,tag)
	local units = oAI:getDetectedUnits()
	for i = 1,units.count do
		if units[i].tag == 998 then
			return units[i]
		end
	end
	return nil
end

oAI:add(1,oSel({
	oSeq({
		oCon(function()
			return CCKeyboard:isKeyDown(CCKey.Up)
		end),
		oAct(oAction.Jump),
	}),
	oSeq({
		oCon(function()
			return CCKeyboard:isKeyPressed(CCKey.Left) or CCKeyboard:isKeyPressed(CCKey.Right)
		end),
		oSel({
			oSeq({
				oCon(function()
					return oAI.self.faceRight ~= CCKeyboard:isKeyPressed(CCKey.Right)
				end),
				oAct(oAction.Turn),
			}),
			oAct(oAction.Walk),
		}),
	}),
	oSeq({
		oCon(function()
			return not CCKeyboard:isKeyPressed(CCKey.Left)
				and not CCKeyboard:isKeyPressed(CCKey.Right)
				and (oAI.self.currentAction and oAI.self.currentAction.id == oAction.Walk)
		end),
		oAct(oAction.Stop),
		oAct(oAction.Idle)
	}),
	oAct(oAction.Idle),
}))


oAI:add(2,oSel({
	oSeq({
		oCon(function()
			local target = oAI:getUnitByTag(998)
			return target and target.currentAction and target.currentAction.id == oAction.Walk and oAI.self.position:distance(target.position) > 350
		end),
		oSel({
			oSeq({
				oCon(function()
					local self = oAI.self
					local target = oAI:getUnitByTag(998)
					return target and (self.positionX < target.positionX) ~= self.faceRight
				end),
				oAct(oAction.Turn),
			}),
			oAct(oAction.Walk)
		}),
	}),
	oSeq({
		oCon(function()
			local target = oAI:getUnitByTag(998)
			return target and oAI.self.position:distance(target.position) <= 350 and target.currentAction and target.currentAction.id == oAction.Walk
		end),
		oSel({
			oSeq({
				oCon(function()
					local self = oAI.self
					local target = oAI:getUnitByTag(998)
					return target and (self.positionX < target.positionX) ~= self.faceRight
				end),
				oAct(oAction.Turn),
			}),
			oAct(oAction.Walk)
		}),
	}),
	oSeq({
		oCon(function()
			local self
			local target = oAI:getNearestUnit(oRelation.Friend)
			return target and target.currentAction and target.currentAction.id ~= oAction.Walk and oAI:getNearestUnitDistance(oRelation.Friend) < 80
		end),
		oCon(function()
			local self = oAI.self
			local units = oAI:getDetectedUnits()
			local target = nil
			local left,right = false,false
			for i = 1,units.count do
				local unit = units[i]
				if unit.tag == 998 then
					target = units[i]
				end
				if unit.positionX > self.positionX and unit.positionX - self.positionX < 90 then
					right = true
				end
				if unit.positionX < self.positionX and self.positionX - unit.positionX < 90 then
					left = true
				end
			end
			return not left or not right
		end),
		oSel({
			oSeq({
				oCon(function()
					local target = oAI:getNearestUnit(oRelation.Friend)
					local self = oAI.self
					return target and (self.positionX < target.positionX) == self.faceRight
				end),
				oSel({
					oSeq({
						oCon(function()
							local target = oAI:getUnitByTag(998)
							local self = oAI.self
							if target and (self.positionX < target.positionX) ~= self.faceRight then
								return self.position:distance(target.position) + 80 > 350
							end
						end),
						oAct(oAction.Idle),
					}),
					oAct(oAction.Turn),
				}),
			}),
			oSeq({
				oCon(function()
					local target = oAI:getUnitByTag(998)
					local self = oAI.self
					if target and (self.positionX < target.positionX) ~= self.faceRight then
						return self.position:distance(target.position) + 80 > 350
					end
				end),
				oAct(oAction.Idle),
			}),
			oAct(oAction.Walk)
		}),
	}),
	oSeq({
		oCon(function()
			local target = oAI:getUnitByTag(998)
			return target and oAI.self.position:distance(target.position) <= 350
		end),
		oCon(function() return oAI.self.currentAction and oAI.self.currentAction.id == oAction.Walk end),
		oAct(oAction.Stop),
		oAct(oAction.Idle),
	}),
	oAct(oAction.Idle),
}))

oAI:add(3,oSel({
	oSel({
		oSeq({
			oCon(function()
				local self = oAI.self
				local target = self.data
				if target then
					return self.position:distance(target.position) > 150
				end
				return false
			end),
			oSel({
				oSeq({
					oCon(function()
						local self = oAI.self
						local target = self.data
						return target and (self.positionX < target.positionX) ~= self.faceRight
					end),
					oAct(oAction.Turn),
				}),
				oAct(oAction.Walk)
			}),
		}),
		oSeq({
			oCon(function() return oAI.self.currentAction and oAI.self.currentAction.id == oAction.Walk end),
			oSel({
				oSeq({
					oAct(oAction.Stop),
					oAct(oAction.Idle)
				}),
			}),
		}),
	}),
	oAct(oAction.Idle),
}))

local function suit(unit,filename)
	local suit = loadfile(filename)()
	for name,items in pairs(suit) do
		local node = unit.model:getChildByName(name)
		if items then
			for i = 1,#items do
				local item = items[i]
				local sp = CCSprite(item[1])
				for o = 2,#item do
					sp[item[o][1]] = item[o][2]
				end
				node:addChild(sp)
			end
		end
	end
end

local world = oPlatformWorld()
world.showDebug = false
world.camera.boudary = CCRect(0,0,20480,2048)
world.camera.followRatio = oVec2(0.05,0.05)

local bk = CCSprite("bk.jpg")
bk.anchor = oVec2.zero
bk.texture.repeatX = true
bk.texture.repeatY = true
bk.textureRect = CCRect(0,0,20480,2048)
world:addChild(bk)

local unitDef = oUnitDef()
unitDef.model = "ActionEditor/Model/Output/role.model"
unitDef.static = false
unitDef.density = 1
unitDef.restitution = 0
unitDef.friction = 1
unitDef.move = 200
unitDef.jump = 550
unitDef.sensity = 0
unitDef.scale = 0.8
unitDef.detectDistance = 600
unitDef:setActions({
	oAction.Walk,
	oAction.Turn,
	oAction.Stop,
	oAction.Jump,
	oAction.Idle,
	--oAction.UserID
})
unitDef.reflexArc = 1

local unit = oUnit(unitDef,world,oVec2(200,300))
unit.group = 1
unit.tag = 998
--unit.reflexArc = 1
suit(unit,"girl.lua")
world:addChild(unit,1)
world.camera:follow(unit)

local lastUnit = unit
unit = oUnit(unitDef,world,oVec2(600,300))
unit.group = 1
unit.data = lastUnit
unit.reflexArc = 3
suit(unit,"miku.lua")
world:addChild(unit)

lastUnit = unit
unit = oUnit(unitDef,world,oVec2(400,300))
unit.group = 1
unit.data = lastUnit
unit.reflexArc = 3
suit(unit,"boy.lua")
world:addChild(unit)

--unit:doIt(oAction.UserID)

--[[
local routine = loop(function()
	wait(seconds(5))
	wait(function() return not unit.onSurface end)
	unit:doIt(oAction.Walk)
end)
oRoutine(routine)
--]]

local bodyDef = oBodyDef()
bodyDef:attachPolygon(oVec2(10240,0),20480,10,0,1,1,0)
local body = oBody(bodyDef,world,oVec2(0,0))
body.group = oData.GroupTerrain

local scene = CCScene()
scene:addChild(world)
world:addChild(body)
--scene:addChild(model)
--scene:addChild(model2)
--[[
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
--]]

local menu = CCMenu(false)
menu.anchor = oVec2.zero
world.UILayer:addChild(menu)
--[[local changed = false
local btn = oButton("Change",16,60,nil,10,10,
	function()
		if changed then
			return
		end
		changed = true
		suit(unit,"boy.lua")
	end)
btn.anchor = oVec2.zero
menu:addChild(btn)
--]]
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