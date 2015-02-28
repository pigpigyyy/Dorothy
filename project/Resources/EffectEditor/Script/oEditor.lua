local CCScene = require("CCScene")
local CCMenu = require("CCMenu")
local oContent = require("oContent")
local CCParticle = require("CCParticle")
local CCDirector = require("CCDirector")
local oVec2 = require("oVec2")

local winSize = CCDirector.winSize

local oEditor = CCScene()
oEditor.effectData = nil
oEditor.input = oContent.writablePath.."Effect/Input/"
oEditor.output = oContent.writablePath.."Effect/Output/"
oEditor.currentFile = nil
oEditor.topMost = 9999
oEditor.touchPriorityEditMenu = CCMenu.DefaultHandlerPriority
oEditor.touchPrioritySettingPanel = CCMenu.DefaultHandlerPriority+1
oEditor.touchPriorityViewPanel = CCMenu.DefaultHandlerPriority+3
oEditor.touchPriorityEditControl = CCMenu.DefaultHandlerPriority+5
oEditor.touchPriorityVRuler = CCMenu.DefaultHandlerPriority+8
oEditor.touchPriorityHRuler = CCMenu.DefaultHandlerPriority+9
oEditor.touchPriorityViewArea = CCMenu.DefaultHandlerPriority+10
oEditor.origin = oVec2((winSize.width-240-10)*0.5,winSize.height*0.5)

oEditor.EmitterGravity = 0
oEditor.EmitterRadius = 1

oEditor.items = {}

oEditor.getUsableName = function(self,originalName)
	if originalName == "" then originalName = "name" end
	if self.items[originalName] then
		local counter = 1
		local nawName = nil
		local usable = false
		repeat
			nawName = originalName..tostring(counter)
			usable = (self.items[nawName] == nil)
			counter = counter+1
		until usable
		return nawName
	else
		return originalName
	end
end

oEditor.dumpEffectFile = function(self)
	local content = "<A>"
	for k,v in pairs(self.items) do
		content = content..string.format("<B A=\"%s\" B=\"%s\"/>",k,v)
	end
	content = content.."</A>"
	oContent:saveToFile(oEditor.output.."main.effect",content)
end

if not oContent:exist(oEditor.input) then
	oContent:mkdir(oEditor.input)
end
if not oContent:exist(oEditor.output) then
	oContent:mkdir(oEditor.output)
end

return oEditor
