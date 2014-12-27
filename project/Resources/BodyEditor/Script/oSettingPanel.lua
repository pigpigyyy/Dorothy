local class,property = unpack(require("class"))
local CCSize = require("CCSize")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCDirector = require("CCDirector")
local oSettingItem = require("oSettingItem")
local oSelectionPanel = require("oSelectionPanel")

local oSettingPanel = class(
{
	__partial = function(self)
		local winSize = CCDirector.winSize
		self._borderSize = CCSize(180,260*(winSize.height-30)/(600-30))
		return oSelectionPanel(self._borderSize,false,true,true)
	end,

	__init = function(self)
		local winSize = CCDirector.winSize
		local menu = self.menu
		local border = self.border
		local halfBW = self._borderSize.width*0.5
		local halfBH = self._borderSize.height*0.5
		local itemWidth = self._borderSize.width
		local itemHeight = 30
		local background= CCDrawNode()
		background:drawPolygon(
		{
			oVec2(-halfBW,-halfBH),
			oVec2(halfBW,-halfBH),
			oVec2(halfBW,halfBH),
			oVec2(-halfBW,halfBH)
		},ccColor4(0xe5100000),0.5,ccColor4(0x88ffafaf))
		border:addChild(background,-1)
		self.position = oVec2(winSize.width*0.5-100,-winSize.height*0.5+halfBH+10)
		
		local function genPosY()
			local index = 0
			return function()
				local v = index
				index = index + 1
				return self._borderSize.height-10-itemHeight*v
			end
		end
		local getPosY = genPosY()

		local itemNames =
		{
			-- text field
			{"Name",function(self,enabled) end},
			-- body chooser
			{"BodyA",function(self,enabled) end},
			{"BodyB",function(self,enabled) end},
			-- joint chooser
			{"JointA",function(self,enabled) end},
			{"JointB",function(self,enabled) end},
			-- move point
			{"WorldPos",function(self,enabled) end},
			{"GroundAnchorA",function(self,enabled) end},
			{"GroundAnchorB",function(self,enabled) end},
			{"AnchorA",function(self,enabled) end},
			{"AnchorB",function(self,enabled) end},
			{"LinearOffset",function(self,enabled) end},
			-- move axis
			{"Axis",function(self,enabled) end},
			-- float
			{"MaxForce",function(self,enabled) end},
			{"MaxTorque",function(self,enabled) end},
			{"Ratio",function(self,enabled) end},
			{"AngularOffset", function(self,enabled) end},
			{"CorrectionFactor",function(self,enabled) end},
			{"LowerTranslation",function(self,enabled) end},
			{"UpperTranslation",function(self,enabled) end},
			{"MaxMotorForce",function(self,enabled) end},
			{"MotorSpeed",function(self,enabled) end},
			{"LowerAngle",function(self,enabled) end},
			{"UpperAngle",function(self,enabled) end},
			{"MaxMotorTorque",function(self,enabled) end},
			{"MaxLength",function(self,enabled) end},
			{"Frequency",function(self,enabled) end},
			{"Damping",function(self,enabled) end},
			{"Angle",function(self,enabled) end},
			{"Radius",function(self,enabled) end},
			{"GravityScale",function(self,enabled) end},
			{"LinearDamping",function(self,enabled) end},
			{"AngularDamping",function(self,enabled) end},
			{"Density",function(self,enabled) end},
			{"Friction",function(self,enabled) end},
			{"Restitution",function(self,enabled) end},
			-- selector
			{"Type",function(self,enabled) end},
			-- boolean
			{"Bullet",function(self,enabled) end},
			{"FixedRotation",function(self,enabled) end},
			{"Collision",function(self,enabled) end},
			-- rect maker
			{"Size",function(self,enabled) end},
			-- move position
			{"Position",function(self,enabled) end},
			{"Center",function(self,enabled) end},
			-- vertices editor
			{"Vertices",function(self,enabled) end},
		}
		
		local items = {}
		items.Name = oSettingItem(itemNames[1][1].." :",itemWidth,itemHeight,0,getPosY(),true,itemNames[1][2])
		for i = 2,#itemNames do
			items[itemNames[i]] = oSettingItem(itemNames[i][1].." :",itemWidth,itemHeight,0,getPosY(),false,itemNames[i][2])
		end
		menu.items = items

		local contentHeight = 20
		for _,item in pairs(items) do
			contentHeight = contentHeight + itemHeight
			menu:addChild(item)
		end
		self:reset(self._borderSize.width,contentHeight,0,50)
	end,
})

return oSettingPanel
