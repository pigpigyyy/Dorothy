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

	control.data = oListener("settingPanel.edit",function(item)
		local name = item.name
		if item.selected then
			if name == "maxParticles" then
				ruler:show(oEditor.effectData.maxParticles,0,10000,10,function(value)
					value = math.floor(value+0.5)
					oEditor.effectData.maxParticles = value
					oEvent:send("maxParticles",value)
				end)
			elseif name == "angle" then
				ruler:show(oEditor.effectData.angle,0,360,10,function(value)
					value = math.floor(value+0.5)
					oEditor.effectData.angle = value
					oEvent:send("angle",value)
				end)
			elseif name == "angleVar" then
				ruler:show(oEditor.effectData.angleVariance,-360,360,10,function(value)
					value = math.floor(value+0.5)
					oEditor.effectData.angleVariance = value
					oEvent:send("angleVariance",value)
				end)
			elseif name == "duration" then
				ruler:show(oEditor.effectData.duration,-1,60,1,function(value)
					value = value < 0 and -1 or math.floor(value*10+0.5)/10
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
			elseif name == "startColor" then
				local color = ccColor4(
					oEditor.effectData.startColorRed*255,
					oEditor.effectData.startColorGreen*255,
					oEditor.effectData.startColorBlue*255,
					oEditor.effectData.startColorAlpha*255)
				control:addChild(oColorPicker(color,function(r,g,b,a)
					oEditor.effectData.startColorRed = r/255
					oEditor.effectData.startColorGreen = g/255
					oEditor.effectData.startColorBlue = b/255
					oEditor.effectData.startColorAlpha = a/255
					oEvent:send("startColorRed",oEditor.effectData.startColorRed)
					oEvent:send("startColorGreen",oEditor.effectData.startColorGreen)
					oEvent:send("startColorBlue",oEditor.effectData.startColorBlue)
					oEvent:send("startColorAlpha",oEditor.effectData.startColorAlpha)
					oEvent:send("settingPanel.cancel")
				end))
			end
		else
			if name == "name" then
				oEditor.items[oEditor.currentName] = nil
				local newName = oEditor:getUsableName(item.value)
				oEditor.items[newName] = oEditor.currentFile
				oEditor.currentName = newName
				oEditor:dumpEffectFile()
			else
				if name == "blendFuncSrc" or name == "blendFuncDst" then
					control:hideTypeSelector()
				end
				oEffect:update(oEditor.effect,oEditor.effectData)
				oEditor.effect:start()
				ruler:hide()
			end
		end
	end)
	return control
end

return oEditControl