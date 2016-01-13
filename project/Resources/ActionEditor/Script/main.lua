local require = using("ActionEditor.Script")
local oEditor = require("oEditor")
local CCDirector = require("CCDirector")

oEditor.quitable = CCDirector.sceneStackSize > 0
oEditor:slot("Quit",function()
	CCDirector:popScene()
end)

CCDirector:run(oEditor)
