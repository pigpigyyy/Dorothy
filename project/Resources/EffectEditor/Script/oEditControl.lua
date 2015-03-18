local CCDirector = require("CCDirector")
local CCNode = require("CCNode")
local oEditRuler = require("oEditRuler")
local CCSize = require("CCSize")
local oSelectionPanel = require("oSelectionPanel")
local oEditor = require("oEditor")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local oButton = require("oButton")
local oListener = require("oListener")
local oEvent = require("oEvent")
local oEffect = require("oEffect")
local ccBlendFunc = require("ccBlendFunc")
local oColorPicker = require("oColorPicker")
local oSpriteChooser = require("oSpriteChooser")
local CCSprite = require("CCSprite")
local oCache = require("oCache")

local function oEditControl()
	local control = CCNode()

	local ruler = oEditRuler()
	control:addChild(ruler)

	-- init blend selector --
	-- blendSelector
	local blendSize = CCSize(120,370)
	local halfTW = blendSize.width*0.5
	local halfTH = blendSize.height*0.5
	local blendSelector = oSelectionPanel(blendSize,true,true,false)
	blendSelector.visible = false

	-- blendBackground
	local blendBackground = CCDrawNode()
	blendBackground:drawPolygon(
	{
		oVec2(-halfTW,-halfTH),
		oVec2(halfTW,-halfTH),
		oVec2(halfTW,halfTH),
		oVec2(-halfTW,halfTH)
	},ccColor4(0xe5100000),0.5,ccColor4(0x88ffafaf))
	blendSelector.border:addChild(blendBackground,-1)

	-- blendMenuItems
	local blendSelected = nil
	local function blendCallback(button)
		control:hideBlendSelector()
		if blendSelected then
			blendSelected(ccBlendFunc[button.text])
		end
		oEvent:send("settingPanel.cancel")
	end
	blendSelector.menu:addChild(oButton("Src",16,100,50,60,blendSize.height-35,blendCallback))
	blendSelector.menu:addChild(oButton("Dst",16,100,50,60,blendSize.height-95,blendCallback))
	blendSelector.menu:addChild(oButton("One",16,100,50,60,blendSize.height-155,blendCallback))
	blendSelector.menu:addChild(oButton("Zero",16,100,50,60,blendSize.height-215,blendCallback))
	blendSelector.menu:addChild(oButton("OneMinSrc",16,100,50,60,blendSize.height-275,blendCallback))
	blendSelector.menu:addChild(oButton("OneMinDst",16,100,50,60,blendSize.height-335,blendCallback))
	control:addChild(blendSelector)

	-- show & hide blend selector
	control.showBlendSelector = function(self,callback)
		blendSelector:show()
		blendSelected = callback
	end
	control.hideBlendSelector = function(self)
		if not blendSelector.visible then return end
		blendSelector:hide()
	end

	-- init mode selector --
	-- modeSelector
	local modeSize = CCSize(120,130)
	halfTW = modeSize.width*0.5
	halfTH = modeSize.height*0.5
	local modeSelector = oSelectionPanel(modeSize,true,true,false)
	modeSelector.visible = false

	-- modeBackground
	local modeBackground = CCDrawNode()
	modeBackground:drawPolygon(
	{
		oVec2(-halfTW,-halfTH),
		oVec2(halfTW,-halfTH),
		oVec2(halfTW,halfTH),
		oVec2(-halfTW,halfTH)
	},ccColor4(0xe5100000),0.5,ccColor4(0x88ffafaf))
	modeSelector.border:addChild(modeBackground,-1)

	-- modeMenuItems
	local modeSelected = nil
	local function modeCallback(button)
		control:hideModeSelector()
		if modeSelected then
			modeSelected(button.text == "Gravity" and oEditor.EmitterGravity or oEditor.EmitterRadius)
		end
		oEvent:send("settingPanel.cancel")
		oEvent:send("settingPanel.moveToMode")
	end
	modeSelector.menu:addChild(oButton("Gravity",16,100,50,60,modeSize.height-35,modeCallback))
	modeSelector.menu:addChild(oButton("Radius",16,100,50,60,modeSize.height-95,modeCallback))
	control:addChild(modeSelector)

	-- show & hide mode selector
	control.showModeSelector = function(self,callback)
		modeSelector:show()
		modeSelected = callback
	end
	control.hideModeSelector = function(self)
		if not modeSelector.visible then return end
		modeSelector:hide()
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
		startRadius = "maxRadius",
		startRadiusVar = "maxRadiusVariance",
		endRadius = "minRadius",
		endRadiusVar = "minRadiusVariance",
		angularSpeed = "rotatePerSecond",
		angularSpeedVar = "rotatePerSecondVariance",
	}

	local anyNames =
	{
		gravityX = "gravityx",
		gravityY = "gravityy",
		tangentAccel = "tangentialAcceleration",
		tangentAccelVar = "tangentialAccelVariance",
		speed = "speed",
		speedVar = "speedVariance",
		radialAccel = "radialAcceleration",
		radialAccelVar = "radialAccelVariance",
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
					value = math.floor(value)
					oEditor.effectData.maxParticles = value
					oEvent:send("maxParticles",value)
				end)
			elseif name == "angle" then
				ruler:show(oEditor.effectData.angle,-360,360,10,function(value)
					value = math.floor(value)
					oEditor.effectData.angle = value
					oEvent:send("angle",value)
				end)
			elseif name == "angleVar" then
				ruler:show(oEditor.effectData.angleVariance,0,360,10,function(value)
					value = math.floor(value)
					oEditor.effectData.angleVariance = value
					oEvent:send("angleVariance",value)
				end)
			elseif name == "duration" then
				ruler:show(oEditor.effectData.duration,-1,60,1,function(value)
					value = value < 0 and -1 or math.floor(value*10)/10
					oEditor.effectData.duration = value
					oEvent:send("duration",value)
				end)
			elseif name == "blendFuncSrc" or name == "blendFuncDst" then
				control:showBlendSelector(function(value)
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
					value = math.floor(value)
					oEditor.effectData[valueName] = value/255
					oEvent:send(valueName,value/255)
				end)
			elseif name == "startSize" then
				ruler:show(oEditor.effectData.startParticleSize,0,10000,10,function(value)
					value = math.floor(value)
					oEditor.effectData.startParticleSize = value
					oEvent:send("startParticleSize",value)
				end)
			elseif varNames[name] then
				local varName = varNames[name]
				ruler:show(oEditor.effectData[varName],0,10000,10,function(value)
					value = math.floor(value)
					oEditor.effectData[varName] = value
					oEvent:send(varName,value)
				end)
			elseif anyNames[name] then
				local varName = anyNames[name]
				ruler:show(oEditor.effectData[varName],-10000,10000,10,function(value)
					value = math.floor(value)
					oEditor.effectData[varName] = value
					oEvent:send(varName,value)
				end)
			elseif lifeNames[name] then
				local varName = lifeNames[name]
				ruler:show(oEditor.effectData[varName],0,1000,1,function(value)
					value = math.floor(value*10)/10
					oEditor.effectData[varName] = value
					oEvent:send(varName,value)
				end)
			elseif name == "emitterType" then
				control:showModeSelector(function(value)
					oEditor.effectData.emitterType = value
					oEvent:send("emitterType",value)
				end)
			elseif name == "textureFile" then
				local spriteChooser = oSpriteChooser()
				spriteChooser.selected = function(filename)
					oEvent:send("textureFileName",filename)
					if filename == "__firePngData" then
						oEditor.effectData.textureFileName = filename
						oEditor.effectData.textureRectx = 0
						oEditor.effectData.textureRecty = 0
						oEditor.effectData.textureRectw = 0
						oEditor.effectData.textureRecth = 0
					else
						if filename:match("|") then
							local sprite = CCSprite(filename)
							filename = filename:match("(.+)|")
							filename = oCache.Clip:getTextureFile(filename)
							oEditor.effectData.textureRectx = sprite.textureRect.origin.x
							oEditor.effectData.textureRecty = sprite.textureRect.origin.y
							oEditor.effectData.textureRectw = sprite.textureRect.size.width
							oEditor.effectData.textureRecth = sprite.textureRect.size.height
						else
							oEditor.effectData.textureRectx = 0
							oEditor.effectData.textureRecty = 0
							oEditor.effectData.textureRectw = 0
							oEditor.effectData.textureRecth = 0
						end
						oEditor.effectData.textureFileName = filename:match("[^\\/]*%.[^%.\\/]*$")
					end
					oEvent:send("textureFileName",oEditor.effectData.textureFileName)
					oEvent:send("textureRectx",oEditor.effectData.textureRectx)
					oEvent:send("textureRecty",oEditor.effectData.textureRecty)
					oEvent:send("textureRectw",oEditor.effectData.textureRectw)
					oEvent:send("textureRecth",oEditor.effectData.textureRecth)
				end
				local ended = spriteChooser.ended
				spriteChooser.ended = function(self)
					oEvent:send("settingPanel.cancel")
					ended(self)
				end
				oEditor:addChild(spriteChooser,oEditor.topMost)
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
				control:hideBlendSelector()
				oEvent:send("oEditor.change")
			end
		end
	end)
	return control
end

return oEditControl