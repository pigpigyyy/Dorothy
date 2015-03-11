local CCDirector = require("CCDirector")
local CCNode = require("CCNode")
local oEditRuler = require("oEditRuler")
local CCSize = require("CCSize")
local oSelectionPanel = require("oSelectionPanel")
local oEditor = require("oEditor")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local oBodyDef = require("oBodyDef")
local oButton = require("oButton")
local oListener = require("oListener")
local oEvent = require("oEvent")
local oEffect = require("oEffect")
local ccBlendFunc = require("ccBlendFunc")
local oColorPicker = require("oColorPicker")

local function oEditControl()
	local winSize = CCDirector.winSize

	local control = CCNode()

	local ruler = oEditRuler()
	control:addChild(ruler)

	-- init type selector --
	-- typeSelector
	local typeSize = CCSize(120,370)
	local halfTW = typeSize.width*0.5
	local halfTH = typeSize.height*0.5
	local typeSelector = oSelectionPanel(typeSize,true,true,false)
	typeSelector.visible = false

	-- typeBackground
	local typeBackground = CCDrawNode()
	typeBackground:drawPolygon(
	{
		oVec2(-halfTW,-halfTH),
		oVec2(halfTW,-halfTH),
		oVec2(halfTW,halfTH),
		oVec2(-halfTW,halfTH)
	},ccColor4(0xe5100000),0.5,ccColor4(0x88ffafaf))
	typeSelector.border:addChild(typeBackground,-1)

	-- typeMenuItems
	local typeSelected = nil
	local function typeCallback(button)
		control:hideTypeSelector()
		if typeSelected then
			typeSelected(ccBlendFunc[button.text])
		end
		oEvent:send("settingPanel.cancel")
	end
	typeSelector.menu:addChild(oButton("Src",16,100,50,60,typeSize.height-35,typeCallback))
	typeSelector.menu:addChild(oButton("Dst",16,100,50,60,typeSize.height-95,typeCallback))
	typeSelector.menu:addChild(oButton("One",16,100,50,60,typeSize.height-155,typeCallback))
	typeSelector.menu:addChild(oButton("Zero",16,100,50,60,typeSize.height-215,typeCallback))
	typeSelector.menu:addChild(oButton("OneMinSrc",16,100,50,60,typeSize.height-275,typeCallback))
	typeSelector.menu:addChild(oButton("OneMinDst",16,100,50,60,typeSize.height-335,typeCallback))
	control:addChild(typeSelector)

	-- show & hide type selector
	control.showTypeSelector = function(self,callback)
		typeSelector:show()
		typeSelected = callback
	end
	control.hideTypeSelector = function(self)
		if not typeSelector.visible then return end
		typeSelector:hide()
	end

	local varNames =
	{
		startSize = "startParticleSize",
		startSizeVar = "startParticleSizeVariance",
		finishSize = "finishParticleSize",
		finishSizeVar = "finishParticleSizeVariance",
		sourcePosXVar = "sourcePositionVariancex",
		sourcePosYVar = "sourcePositionVariancey",
		rotationStart = "rotationStart",
		rotationEnd = "rotationEnd",
		rotationStartVar = "rotationStartVariance",
		rotationEndVar = "rotationEndVariance",
		emissionRate = "emissionRate",
	}

	local lifeNames =
	{
		lifeTime = "particleLifespan",
		lifeTimeVar = "particleLifespanVariance",
	}
	
	control.data = oListener("settingPanel.edit",function(item)
		local name = item.name
		if item.selected then
			if name == "maxParticles" then
				ruler:show(oEditor.effectData.maxParticles,0,10000,10,function(value)
					oEditor.effectData.maxParticles = value
					oEvent:send("maxParticles",value)
				end)
			elseif name == "angle" then
				ruler:show(oEditor.effectData.angle,0,360,10,function(value)
					oEditor.effectData.angle = value
					oEvent:send("angle",value)
				end)
			elseif name == "angleVar" then
				ruler:show(oEditor.effectData.angleVariance,0,360,10,function(value)
					oEditor.effectData.angleVariance = value
					oEvent:send("angleVariance",value)
				end)
			elseif name == "duration" then
				ruler:show(oEditor.effectData.duration,-1,60,1,function(value)
					value = value < 0 and -1 or value
					oEditor.effectData.duration = value
					oEvent:send("duration",value)
				end)
			elseif name == "blendFuncSrc" or name == "blendFuncDst" then
				control:showTypeSelector(function(value)
					if name == "blendFuncSrc" then
						oEditor.effectData.blendFuncSource = value
						oEvent:send("blendFuncSource",value)
					else
						oEditor.effectData.blendFuncDestination = value
						oEvent:send("blendFuncDestination",value)
					end
				end)
			elseif name == "startColor" or name == "finishColor" then
				local isStart = name:sub(1,5) == "start"
				local sr = isStart and "startColorRed" or "finishColorRed"
				local sg = isStart and "startColorGreen" or "finishColorGreen"
				local sb = isStart and "startColorBlue" or "finishColorBlue"
				local sa = isStart and "startColorAlpha" or "finishColorAlpha"
				local color = ccColor4(
					oEditor.effectData[sr]*255,
					oEditor.effectData[sg]*255,
					oEditor.effectData[sb]*255,
					oEditor.effectData[sa]*255)
				control:addChild(oColorPicker(color,function(r,g,b,a)
					oEditor.effectData[sr] = r/255
					oEditor.effectData[sg] = g/255
					oEditor.effectData[sb] = b/255
					oEditor.effectData[sa] = a/255
					oEvent:send(sr,oEditor.effectData[sr])
					oEvent:send(sg,oEditor.effectData[sg])
					oEvent:send(sb,oEditor.effectData[sb])
					oEvent:send(sa,oEditor.effectData[sa])
					oEvent:send("settingPanel.cancel")
				end))
			elseif name == "startRedVar"
				or name == "startBlueVar"
				or name == "startGreenVar"
				or name == "startAlphaVar"
				or name == "finishRedVar"
				or name == "finishBlueVar"
				or name == "finishGreenVar"
				or name == "finishAlphaVar" then
				local pos = name:sub(1,5) == "start" and 5 or 6
				local valueName = name:sub(1,pos).."ColorVariance"..name:sub(pos+1,-4)
				ruler:show(oEditor.effectData[valueName]*255,0,255,10,function(value)
					oEditor.effectData[valueName] = value/255
					oEvent:send(valueName,value/255)
				end)
			elseif name == "startSize" then
				ruler:show(oEditor.effectData.startParticleSize,0,10000,10,function(value)
					oEditor.effectData.startParticleSize = value
					oEvent:send("startParticleSize",value)
				end)
			elseif varNames[name] then
				local varName = varNames[name]
				ruler:show(oEditor.effectData[varName],0,10000,10,function(value)
					oEditor.effectData[varName] = value
					oEvent:send(varName,value)
				end)
			elseif lifeNames[name] then
				local varName = lifeNames[name]
				ruler:show(oEditor.effectData[varName],0,1000,1,function(value)
					oEditor.effectData[varName] = value
					oEvent:send(varName,value)
				end)
			end
		else
			if name == "name" then
				oEditor.items[oEditor.currentName] = nil
				local newName = oEditor:getUsableName(item.value)
				oEditor.items[newName] = oEditor.currentFile
				oEditor.currentName = newName
				oEditor:dumpEffectFile()
			else
				oEffect:update(oEditor.effect,oEditor.effectData)
				oEditor.effect:start()
				ruler:hide()
				control:hideTypeSelector()
			end
		end
	end)
	return control
end

return oEditControl