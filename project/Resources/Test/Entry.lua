local oButton = require("ActionEditor/Script/oButton")
local oSelectionPanel = require("ActionEditor/Script/oSelectionPanel")
local Tests = require("Test/Tests")
local CCDirector = require("CCDirector")
local CCMenu = require("CCMenu")
local CCSize = require("CCSize")
local oVec2 = require("oVec2")
local oOpacity = require("oOpacity")
local CCScene = require("CCScene")
--local oRoutine = require("oRoutine")
--local once = require("oRoutine").once
--local wait = require("oRoutine").wait
--local seconds = require("oRoutine").seconds
local CCObject = require("CCObject")
local cclog = require("cclog")
local oCache = require("oCache")
local oAI = require("oAI")
local oAction = require("oAction")

local winSize = CCDirector.winSize
local panel = oSelectionPanel(winSize,true)
local menu = panel.menu

local opMenu = CCMenu()
opMenu.contentSize = CCSize(60,60)
opMenu.touchPriority = CCMenu.DefaultHandlerPriority-3
opMenu.position = oVec2(winSize.width-40,40)
panel:addChild(opMenu)
local endButton = oButton("Exit",17,60,false,
	0,0,
	function()
		CCDirector:stop()
	end)
endButton.anchor = oVec2.zero
opMenu:addChild(endButton)

opMenu = CCMenu()
opMenu.contentSize = CCSize(60,60)
opMenu.touchPriority = CCMenu.DefaultHandlerPriority-3
opMenu.position = oVec2(40,40)
panel:addChild(opMenu)
endButton = oButton("GC",17,60,false,
	0,0,
	function()
		oCache:clear()
		oAI:clear()
		oAction:clear()
		collectgarbage()
		cclog("[LUA MEMORY USAGE] %d KB",collectgarbage("count"))
		cclog("Object Count: %d",CCObject.count)
		cclog("Lua Count: %d",CCObject.luaRefCount)
		cclog("Callback Count: %d", CCObject.callRefCount)
		for i,item in pairs(ubox()) do
			print(i,item)
		end
	end)
endButton.anchor = oVec2.zero
opMenu:addChild(endButton)

panel.init = function(self)
	menu.opacity = 0
	menu.enabled = false
	menu:runAction(oOpacity(0.3,1))
	local y = 0
	for i = 1,#Tests do
		y = winSize.height-60-(i-1)*60
		local button = oButton(
			Tests[i][1],
			16,
			200,50,
			winSize.width*0.5,y,
			function()
				dofile(Tests[i][2])
				if i ~= 1 then
					local opMenu = CCMenu()
					opMenu.contentSize = CCSize(60,60)
					opMenu.touchPriority = CCMenu.DefaultHandlerPriority-3
					opMenu.position = oVec2(winSize.width-40,40)
					CCDirector.currentScene:addChild(opMenu)
					local endBtn = oButton("Back",17,60,false,
						0,0,
						function()
							CCDirector:popToRootScene()
						end)
					endBtn.anchor = oVec2.zero
					opMenu:addChild(endBtn)
				end
			end)
		menu:addChild(button)
	end
	local yTo = winSize.height*0.5-y+60
	local viewHeight = yTo < winSize.height and winSize.height or yTo
	local viewWidth = winSize.width
	local paddingX = 0
	local paddingY = 100
	panel:reset(viewWidth,viewHeight,paddingX,paddingY)
end

panel:show()

local scene = CCScene()
scene:addChild(panel)

CCDirector:run(scene)
