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
		"name",
		"maxParticles",
		"angle",
		"angleVar",
		"duration",
		"blendAdditive",
		"blendFuncSrc",
		"blendFuncDst",
		"startColor",
		"startRedVar",
		"startGreenVar",
		"startBlueVar",
		"startAlphaVar",
		"finishColor",
		"finishRedVar",
		"finishGreenVar",
		"finishBlueVar",
		"finishAlphaVar",
		"startSize",
		"startSizeVar",
		"finishSize",
		"finishSizeVar",
		"sourcePosition",
		"sourcePosXVar",
		"sourcePosYVar",
		"rotationStart",
		"rotationStartVar",
		"rotationEnd",
		"rotationEndVar",
		"lifeTime",
		"lifeTimeVar",
		"emissionRate",
		"textureFileName",
		"textureRect",
		"emitterType",
		"gravityX",
		"gravityY",
		"speed",
		"speedVar",
		"radialAccel",
		"radialAccelVar",
		"tangentAccel",
		"tangentAccelVar",
		"startRadius",
		"startRadiusVar",
		"endRadius",
		"endRadiusVar",
		"angularSpeed",
		"angularSpeedVar",
		"interval",
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

	local modeGravity =
	{
		items.name,
		items.maxParticles,
		items.angle,
		items.angleVar,
		items.duration,
		items.blendAdditive,
		items.blendFuncSrc,
		items.blendFuncDst,
		items.startColor,
		items.startColorRVar,
		items.startColorGVar,
		items.startColorBVar,
		items.startColorAVar,
		items.finishColor,
		items.finishColorRVar,
		items.finishColorGVar,
		items.finishColorBVar,
		items.finishColorAVar,
		items.startSize,
		items.startSizeVar,
		items.finishSize,
		items.finishSizeVar,
		items.sourcePosition,
		items.sourcePosXVar,
		items.sourcePosYVar,
		items.rotationStart,
		items.rotationStartVar,
		items.rotationEnd,
		items.rotationEndVar,
		items.lifeTime,
		items.lifeTimeVar,
		items.emissionRate,
		items.textureFileName,
		items.textureRect,
		items.emitterType,
		items.gravityx,
		items.gravityy,
		items.speed,
		items.speedVar,
		items.radialAccel,
		items.radialAccelVar,
		items.tangentialAccel,
		items.tangentialAccelVar,
	}

	local modeRadius =
	{
		items.name,
		items.maxParticles,
		items.angle,
		items.angleVar,
		items.duration,
		items.blendAdditive,
		items.blendFuncSrc,
		items.blendFuncDst,
		items.startColor,
		items.startColorRVar,
		items.startColorGVar,
		items.startColorBVar,
		items.startColorAVar,
		items.finishColor,
		items.finishColorRVar,
		items.finishColorGVar,
		items.finishColorBVar,
		items.finishColorAVar,
		items.startSize,
		items.startSizeVar,
		items.finishSize,
		items.finishSizeVar,
		items.sourcePosition,
		items.sourcePosXVar,
		items.sourcePosYVar,
		items.rotationStart,
		items.rotationStartVar,
		items.rotationEnd,
		items.rotationEndVar,
		items.lifeTime,
		items.lifeTimeVar,
		items.emissionRate,
		items.textureFileName,
		items.textureRect,
		items.emitterType,
		items.startRadius,
		items.startRadiusVar,
		items.endRadius,
		items.endRadiusVar,
		items.angularSpeed,
		items.angularSpeedVar,
	}

	local modeFrame =
	{
		items.name,
		items.interval
	}

	for _,item in pairs(items) do
		item.visible = false
		menu:addChild(item)
	end

	local function setGroup(group)
		for _,item in pairs(items) do
			item.visible = false
		end
		local contentHeight = 40
		local getPosY = genPosY()
		for _,item in pairs(group) do
			item.positionY = getPosY()
			item.visible = true
			contentHeight = contentHeight + itemHeight
		end
		if group == modeFrame then
			label.text = "Frame"
			label.texture.antiAlias = false
		else
			label.text = "Particle"
			label.texture.antiAlias = false
		end
		self:reset(borderSize.width,contentHeight,0,50)
	end

	setGroup(modeRadius)
	return self
end

return oSettingPanel
