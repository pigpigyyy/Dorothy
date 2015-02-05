local CCScene = require("CCScene")
local CCMenu = require("CCMenu")

local oEditor = CCScene()

oEditor.input = "EffectEditor/Effect/Input/"
oEditor.output = "EffectEditor/Effect/Output/"
oEditor.currentFile = ""
oEditor.topMost = 2147483647
oEditor.touchPriorityEditMenu = CCMenu.DefaultHandlerPriority
oEditor.touchPrioritySettingPanel = CCMenu.DefaultHandlerPriority+1
oEditor.touchPriorityViewPanel = CCMenu.DefaultHandlerPriority+3
oEditor.touchPriorityEditControl = CCMenu.DefaultHandlerPriority+5
oEditor.touchPriorityVRuler = CCMenu.DefaultHandlerPriority+8
oEditor.touchPriorityHRuler = CCMenu.DefaultHandlerPriority+9
oEditor.touchPriorityViewArea = CCMenu.DefaultHandlerPriority+10

return oEditor
