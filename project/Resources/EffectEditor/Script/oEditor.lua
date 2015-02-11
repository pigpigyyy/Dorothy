local CCScene = require("CCScene")
local CCMenu = require("CCMenu")
local oContent = require("oContent")

local oEditor = CCScene()
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

oEditor.EmitterGravity = 0
oEditor.EmitterRadius = 1

if not oContent:exist(oEditor.input) then
	oContent:mkdir(oEditor.input)
end
if not oContent:exist(oEditor.output) then
	oContent:mkdir(oEditor.output)
end

return oEditor
