local CCSize = require("CCSize")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCDirector = require("CCDirector")
local oSettingItem = require("oSettingItem")
local oSelectionPanel = require("oSelectionPanel")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local CCDictionary = require("CCDictionary")
local oEvent = require("oEvent")
local oListener = require("oListener")
local oEditor = require("oEditor")
local tolua = require("tolua")
local oBodyDef = require("oBodyDef")
local CCTextAlign = require("CCTextAlign")
local CCUserDefault = require("CCUserDefault")

local function oSettingPanel()
	local winSize = CCDirector.winSize
	local borderSize = CCSize(180,winSize.height-20)
	local self = oSelectionPanel(borderSize,false,true,true)
	self.touchPriority = oEditor.touchPrioritySettingPanel
	local menu = self.menu
	menu.touchPriority = oEditor.touchPrioritySettingPanel+1
	local border = self.border
	local halfBW = borderSize.width*0.5
	local halfBH = borderSize.height*0.5
	local itemWidth = borderSize.width
	local itemHeight = 30
	local background = CCDrawNode()
	background:drawPolygon(
	{
		oVec2(-halfBW,-halfBH),
		oVec2(halfBW,-halfBH),
		oVec2(halfBW,halfBH),
		oVec2(-halfBW,halfBH)
	},ccColor4(0xe5100000),0.5,ccColor4(0x88ffafaf))
	border:addChild(background,-1)
	self.position = oVec2(winSize.width*0.5-100,0)
	
	local label = CCLabelTTF("","Arial",16)
	label.position = oVec2(halfBW,borderSize.height-18)
	label.color = ccColor3(0x00ffff)
	menu:addChild(label)
	
	local function genPosY()
		local index = 0
		return function()
			local v = index
			index = index + 1
			return borderSize.height-30-itemHeight*v
		end
	end

	local itemNames =
	{
		-- text field
		"Name",
		-- body chooser
		"BodyA",
		"BodyB",
		-- joint chooser
		"JointA",
		"JointB",
		-- move point
		"WorldPos",
		"GroundA",
		"GroundB",
		"AnchorA",
		"AnchorB",
		"Offset",
		-- move axis
		"Axis",
		-- float
		"MaxForce",
		"MaxTorque",
		"Ratio",
		"AngularOffset", 
		"CorrectionFactor",
		"Lower",
		"Upper",
		"MaxMotorForce",
		"MotorSpeed",
		"LowerAngle",
		"UpperAngle",
		"MaxMotorTorque",
		"MaxLength",
		"Frequency",
		"Damping",
		"Angle",
		"Radius",
		"GravityScale",
		"LinearDamping",
		"AngularDamping",
		"Density",
		"Friction",
		"Restitution",
		-- selector
		"Type",
		-- boolean
		"Bullet",
		"FixedRotation",
		"Collision",
		-- rect maker
		"Size",
		-- move position
		"Position",
		"Center",
		-- vertices editor
		"Vertices",
		-- face chooser
		"Face",
		-- move position
		"FacePos",
		-- boolean
		"Sensor",
		-- int
		"SensorTag",
		"G",
	}

	local items = {}
	local getPosY = genPosY()
	local function editCallback(settingItem)
		oEvent:send("settingPanel.edit",settingItem)
	end
	for i = 1,#itemNames do
		items[itemNames[i]] = oSettingItem(itemNames[i].." :",itemWidth,itemHeight,0,getPosY(),i == 1,editCallback)
		items[itemNames[i]].name = itemNames[i]
	end
	
	local contentHeight = 40
	for _,item in pairs(items) do
		menu:addChild(item)
		contentHeight = contentHeight + itemHeight
	end
	
	self:reset(borderSize.width,contentHeight,0,50)

	return self
end

return oSettingPanel
