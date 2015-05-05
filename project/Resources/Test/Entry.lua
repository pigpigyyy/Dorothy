local oButton = require("ActionEditor/Script/oButton")
local oSelectionPanel = require("ActionEditor/Script/oSelectionPanel")
local Tests = require("Test/Tests")
local CCDirector = require("CCDirector")
local CCMenu = require("CCMenu")
local CCSize = require("CCSize")
local oVec2 = require("oVec2")
local oOpacity = require("oOpacity")
local CCScene = require("CCScene")
local CCObject = require("CCObject")
local cclog = require("cclog")
local oCache = require("oCache")
local oAI = require("oAI")
local oAction = require("oAction")
local CCKeypad = require("CCKeypad")
local CCApplication = require("CCApplication")
local CCTargetPlatform = require("CCTargetPlatform")
local CCOrientation = require("CCOrientation")
local CCNode = require("CCNode")
local CCLayerColor = require("CCLayerColor")
local ccColor4 = require("ccColor4")
local oContent = require("oContent")

local scene = CCScene()

local winSize = CCDirector.winSize
local panel = oSelectionPanel(winSize,true)
local menu = panel.menu

local background = CCLayerColor(ccColor4(0xff000000))
panel.border:addChild(background,-1)

local opMenu = CCMenu()
opMenu.contentSize = CCSize(60,60)
opMenu.touchPriority = CCMenu.DefaultHandlerPriority-3
opMenu.position = oVec2(winSize.width-40,40)
panel:addChild(opMenu)
if CCApplication.targetPlatform ~= CCTargetPlatform.Ipad and CCApplication.targetPlatform ~= CCTargetPlatform.Iphone then
	local endButton = oButton("Exit",17,60,false,
		0,0,
		function()
			CCDirector:stop()
		end)
	endButton.anchor = oVec2.zero
	opMenu:addChild(endButton)
end

opMenu = CCMenu()
opMenu.contentSize = CCSize(60,60)
opMenu.touchPriority = CCMenu.DefaultHandlerPriority-3
opMenu.position = oVec2(40,40)
panel:addChild(opMenu)
local gcButton = oButton("GC",17,60,false,
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
		local size = oCache.Pool.size
		cclog("Pool alloc : %.2f MB(%d KB)",size/1024/1024,size/1024)
		size = oCache.Pool:collect()
		cclog("Pool collect : %.2f MB(%d KB)",size/1024/1024,size/1024)
		--[[
		for i,item in pairs(ubox()) do
			print(i,item)
		end
		--]]
		--[[for k,v in pairs(_G) do
			print(k,v)
		end
		--]]
	end)
gcButton.anchor = oVec2.zero
opMenu:addChild(gcButton)

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
				local result = dofile(Tests[i][2])
				if type(result) == "function" then result() end
				if not Tests[i][3] then
					local opMenu = CCMenu()
					opMenu.contentSize = CCSize(60,60)
					opMenu.touchPriority = CCMenu.DefaultHandlerPriority-3
					opMenu.position = oVec2(winSize.width-40,40)
					CCDirector.currentScene:addChild(opMenu)
					local endBtn = oButton("Back",17,60,false,
						0,0,
						function()
							CCDirector:run(CCScene:crossFade(0.5,scene))
						end)
					endBtn.anchor = oVec2.zero
					opMenu:addChild(endBtn)
				end
			end)
		menu:addChild(button)
	end
	local yTo = winSize.height-y+60
	local viewHeight = yTo < winSize.height and winSize.height or yTo
	local viewWidth = winSize.width
	local paddingX = 0
	local paddingY = 100
	panel:reset(viewWidth,viewHeight,paddingX,paddingY)
end

panel:show()

scene:addChild(panel)

panel:registerKeypadHandler(function(eventType)
	if eventType == CCKeypad.Back then
		CCDirector:stop() -- end is Lua keyword, so this function use name stop
	end
end)
panel.keypadEnabled = true

CCDirector.displayStats = true

scene:registerEventHandler(function(eventType)
	if eventType == CCNode.Entered then
		CCDirector:popToRootScene()
	end
end)

oContent:setSearchPaths({"Lib"})

CCDirector:run(scene)
