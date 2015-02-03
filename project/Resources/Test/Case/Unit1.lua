setfenv(Dorothy())

local oTextField = require("ActionEditor/Script/oTextField")
local oButton = require("ActionEditor/Script/oButton")

local CCKey = {}
if CCApplication.targetPlatform == CCTargetPlatform.Windows then
	CCKey.Left = 0x25
	CCKey.Up = 0x26
	CCKey.Right = 0x27
	CCKey.Down = 0x28
elseif CCApplication.targetPlatform == CCTargetPlatform.MacOS then
	CCKey.Up = 0x0
	CCKey.Down = 0x1
	CCKey.Left = 0x2
	CCKey.Right = 0x3
else
	CCKey.Left = 0
	CCKey.Up = 0
	CCKey.Right = 0
	CCKey.Down = 0
end

oAI.getUnitByTag = function(self,tag)
	local units = self:getDetectedUnits()
	for i = 1,units.count do
		if units[i].tag == tag then
			return units[i]
		end
	end
	return nil
end

local function isJumpKeyDown()
	return CCKeyboard:isKeyDown(CCKey.Up)
end

local function isWalkKeyPressed()
	return CCKeyboard:isKeyPressed(CCKey.Left) or CCKeyboard:isKeyPressed(CCKey.Right)
end

local function isFaceDirectionChanged()
	return oAI.self.faceRight ~= CCKeyboard:isKeyPressed(CCKey.Right)
end

local function needGoIdle()
	return not CCKeyboard:isKeyPressed(CCKey.Left)
		and not CCKeyboard:isKeyPressed(CCKey.Right)
		and oAI.self:isDoing("walk")
end

oAI:add(1,oSel({
	oSeq({
		oCon(isJumpKeyDown),
		oAct("jump"),
	}),
	oSeq({
		oCon(isWalkKeyPressed),
		oSel({
			oSeq({
				oCon(isFaceDirectionChanged),
				oAct("turn"),
			}),
			oAct("walk"),
		}),
	}),
	oSeq({
		oCon(needGoIdle),
		oAct("cancel"),
		oAct("idle")
	}),
	oAct("idle"),
}))

oAI:add(2,oSel({
	oSeq({
		oCon(function()
			local target = oAI:getUnitByTag(998)
			return target and target:isDoing("walk") and oAI.self.position:distance(target.position) > 350
		end),
		oSel({
			oSeq({
				oCon(function()
					local self = oAI.self
					local target = oAI:getUnitByTag(998)
					return target and (self.positionX < target.positionX) ~= self.faceRight
				end),
				oAct("turn"),
			}),
			oAct("walk")
		}),
	}),
	oSeq({
		oCon(function()
			local target = oAI:getUnitByTag(998)
			return target and oAI.self.position:distance(target.position) <= 350 and target:isDoing("walk")
		end),
		oSel({
			oSeq({
				oCon(function()
					local self = oAI.self
					local target = oAI:getUnitByTag(998)
					return target and (self.positionX < target.positionX) ~= self.faceRight
				end),
				oAct("turn"),
			}),
			oAct("walk")
		}),
	}),
	oSeq({
		oCon(function()
			local self
			local target = oAI:getNearestUnit(oRelation.Friend)
			return target and not target:isDoing("walk") and oAI:getNearestUnitDistance(oRelation.Friend) < 80
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
						oAct("idle"),
					}),
					oAct("turn"),
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
				oAct("idle"),
			}),
			oAct("walk")
		}),
	}),
	oSeq({
		oCon(function()
			local target = oAI:getUnitByTag(998)
			return target and oAI.self.position:distance(target.position) <= 350
		end),
		oCon(function() return oAI.self:isDoing("walk") end),
		oAct("cancel"),
		oAct("idle"),
	}),
	oAct("idle"),
}))

oAI:add(3,oSel({
	oSel({
		oSeq({
			oCon(function()
				local self = oAI.self
				local target = self.data
				if target and target:get("hp") > 0 then
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
					oAct("turn"),
				}),
				oAct("walk")
			}),
		}),
		oSeq({
			oCon(function() return oAI.self:isDoing("walk") end),
			oSel({
				oSeq({
					oAct("cancel"),
					oAct("idle")
				}),
			}),
		}),
	}),
	oAct("idle"),
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
unitDef.maxHp = 10
unitDef.detectDistance = 600
unitDef:setActions({
	"walk",
	"turn",
	"cancel",
	"jump",
	"idle",
})
unitDef.reflexArc = 1

local unit = oUnit(unitDef,world,oVec2(200,300))
unit.group = 1
unit.tag = 998
unit.reflexArc = 1
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

local bodyDef = oBodyDef()
bodyDef:attachPolygon(oVec2(10240,0),20480,10,0,1,1,0)
local body = oBody(bodyDef,world,oVec2(0,0))
body.group = oData.GroupTerrain

local scene = CCScene()
scene:addChild(world)
world:addChild(body)

local menu = CCMenu(false)
menu.anchor = oVec2.zero
world.UILayer:addChild(menu)

CCDirector:run(scene)

print("Use arrow keys from keyboard to control character")