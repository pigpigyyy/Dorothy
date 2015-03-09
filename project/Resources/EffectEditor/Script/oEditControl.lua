local CCNode = require("CCNode")
local oEditRuler = require("oEditRuler")
local oListener = require("oListener")
local oEditor = require("oEditor")
local oEffect = require("oEffect")
local oEvent = require("oEvent")

local function oEditControl()
	local control = CCNode()
	local ruler = oEditRuler()
	control:addChild(ruler)

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
					if value < 0 then
						value = -1
					else
						value = math.floor(value*10+0.5)/10
					end
					oEditor.effectData.duration = value
					oEvent:send("duration",value)
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
				oEditor.effect:setOffset(oEditor.origin):start()
				ruler:hide()
			end
		end
	end)
	return control
end

return oEditControl