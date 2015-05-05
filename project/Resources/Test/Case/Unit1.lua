setfenv(Dorothy())

oContent:setSearchPaths({"Lib","Test/Case/Unit1"})

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

local isJumpKeyDown = oCon(function()
	return CCKeyboard:isKeyDown(CCKey.Up)
end)

local isWalkKeyPressed = oCon(function()
	return CCKeyboard:isKeyPressed(CCKey.Left) or CCKeyboard:isKeyPressed(CCKey.Right)
end)

local isFaceDirectionChanged = oCon(function()
	return oAI.self.faceRight ~= CCKeyboard:isKeyPressed(CCKey.Right)
end)

local needGoIdle = oCon(function()
	return not CCKeyboard:isKeyPressed(CCKey.Left)
		and not CCKeyboard:isKeyPressed(CCKey.Right)
		and oAI.self:isDoing("walk")
end)

local walk = oAct("walk")
local cancel = oAct("cancel")
local idle = oAct("idle")
local turn = oAct("turn")
local jump = oAct("jump")

oAI:add("keyboardControl",oSel({
	oSeq({
		isJumpKeyDown,
		jump,
	}),
	oSeq({
		isWalkKeyPressed,
		oSel({
			oSeq({
				isFaceDirectionChanged,
				turn,
			}),
			walk,
		}),
	}),
	oSeq({
		needGoIdle,
		cancel,
		idle,
	}),
	idle,
}))

oAI:add("follow",oSel({
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
					turn,
				}),
				walk,
			}),
		}),
		oSeq({
			oCon(function() return oAI.self:isDoing("walk") end),
			oSel({
				oSeq({
					cancel,
					idle
				}),
			}),
		}),
	}),
	idle,
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
world.gravity = oVec2(0,-20)
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
unitDef.density = 0.5
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

local unit = oUnit(unitDef,world,oVec2(200,300))
unit.group = 1
unit.tag = 998
unit.reflexArc = "keyboardControl"
suit(unit,"girl")
world:addChild(unit,1)
world.camera:follow(unit)

local lastUnit = unit
unit = oUnit(unitDef,world,oVec2(600,300))
unit.group = 1
unit.data = lastUnit
unit.reflexArc = "follow"
suit(unit,"miku")
world:addChild(unit)

lastUnit = unit
unit = oUnit(unitDef,world,oVec2(400,300))
unit.group = 1
unit.data = lastUnit
unit.reflexArc = "follow"
suit(unit,"boy")
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

scene.nodeHandler = function(eventType)
	if eventType == CCNode.Cleanup then
		oContent:setSearchPaths({"Lib"})
	end
end

CCDirector:run(CCScene:crossFade(0.5,scene))

print("Use arrow keys from keyboard to control character")