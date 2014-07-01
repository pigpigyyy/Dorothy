local CCScene = require("CCScene")
local CCDirector = require("CCDirector")

local scene = CCScene()
CCDirector:run(CCScene:progressCW(1,scene))
