local oButton = require("ActionEditor.Script.oButton")
local oSelectionPanel = require("ActionEditor.Script.oSelectionPanel")
local Tests = require("Test.Tests")
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
local CCApplication = require("CCApplication")
local CCTargetPlatform = require("CCTargetPlatform")
local CCLayerColor = require("CCLayerColor")
local ccColor4 = require("ccColor4")
local oContent = require("oContent")
local tolua = require("tolua")

oContent:addSearchPath("Lib")
local moonscript = require("moonscript")
local util = require("moonscript.util")
local errors = require("moonscript.errors")

local traceback = debug.traceback
debug.traceback = function(err)
	local trace = traceback("",2)
	if trace then
		local rewritten = errors.rewrite_traceback(util.trim(trace), err)
		if rewritten then
			return rewritten
		else
			return table.concat({err, util.trim(trace)}, "\n")
		end
	end
	return ""
end

local _require = require
local loaded = {} -- save loaded module names for end clean up
local require = function(name)
	local result = package.loaded[name]
	if not result then
		result = _require(name)
		table.insert(loaded,name)
	end
	return result
end
_G["require"] = require
builtin["require"] = require

local scene = CCScene()

local winSize = CCDirector.winSize
local panel = oSelectionPanel(winSize,true)
local menu = panel.menu

local background = CCLayerColor(ccColor4(0xff000000))
panel.border:addChild(background,-1)

local opMenu = CCMenu()
opMenu.swallowTouches = true
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
opMenu.swallowTouches = true
opMenu.contentSize = CCSize(200,60)
opMenu.touchPriority = CCMenu.DefaultHandlerPriority-4
opMenu.anchor = oVec2.zero
opMenu.position = oVec2(10,10)
panel:addChild(opMenu)
local startUboxItems = {}
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
		cclog("Pool alloc: %.2f MB(%d KB)",size/1024/1024,size/1024)
		size = oCache.Pool:collect()
		cclog("Pool collect: %.2f MB(%d KB)",size/1024/1024,size/1024)
		print("Loaded:")
		for k,_ in pairs(package.loaded) do
			print(k)
		end
		local itemMap = {}
		for _,item in pairs(ubox()) do
			local typeName = tolua.type(item)
			if not itemMap[typeName] then
				itemMap[typeName] = 0
			end
			itemMap[typeName] = itemMap[typeName]+1
		end
		print("Possibly Leaked Objects:")
		local leak = false
		for k,v in pairs(itemMap) do
			if not startUboxItems[k] then
				startUboxItems[k] = 0
			end
			local count = itemMap[k] - startUboxItems[k]
			if count > 0 then
				leak = true
				print(k,count)
			end
		end
		if not leak then
			print("None!")
		end
		--]]
		--[[for k,v in pairs(_G) do
			print(k,v)
		end
		--]]
	end)
gcButton.anchor = oVec2.zero
opMenu:addChild(gcButton)

local function compile(dir,clean)
	local entries = oContent:getEntries(dir,true)
	for _,item in ipairs(entries) do
		local entry = dir.."/"..item
		if item ~= "." and item ~= ".." then
			if not compile(entry,clean) then
				return false
			end
		end
	end
	entries = oContent:getEntries(dir,false)
	for _,item in ipairs(entries) do
		local name = item:match("(.*)%.[^%.\\/]*$")
		local extension = string.match(item, "%.([^%.\\/]*)$")
		if extension == "moon" then
			if not clean then
				local entry = dir.."/"..item
				local file = io.open(entry,"r")
				local moonCodes = file:read("*a")
				local codes,err = moonscript.to_lua(moonCodes)
				file:close()
				if not codes then
					print("Compile errors in "..entry)
					print(err)
					return false
				else
					oContent:saveToFile(dir.."/"..name..".lua",codes)
					print("Moon compiled: "..entry)
				end
			else
				local filename = dir.."/"..name..".lua"
				if oContent:exist(filename) then
					print("Moon cleaned: "..filename)
					oContent:remove(filename)
				end
			end
		elseif extension == "xml" then
			if not clean then
				local entry = dir.."/"..item
				local file = io.open(entry,"r")
				local xmlCodes = file:read("*a")
				local codes = xmlToLua(xmlCodes)
				file:close()
				if not codes then
					print("Compile errors in "..entry)
					return false
				else
					oContent:saveToFile(dir.."/"..name..".lua",codes)
					print("xml compiled: "..entry)
				end
			else
				local filename = dir.."/"..name..".lua"
				if oContent:exist(filename) then
					print("Xml cleaned: "..filename)
					oContent:remove(filename)
				end
			end
		end
	end
	return true
end
local compileButton = oButton("Compile",12,60,false,
	70,0,
	function()
		compile(".",false)
		print("Compile done.")
	end)
compileButton.anchor = oVec2.zero
opMenu:addChild(compileButton)
local cleanButton = oButton("Clean",16,60,false,
	140,0,
	function()
		compile(".",true)
		print("Clean done.")
	end)
cleanButton.anchor = oVec2.zero
opMenu:addChild(cleanButton)

panel.init = function(self)
	menu.opacity = 0
	menu.enabled = false
	menu:runAction(oOpacity(0.3,1))
	for i = 1,#Tests do
		local button = oButton(
			Tests[i][1],
			16,
			200,50,
			0,0,
			function()
				local result = require(Tests[i][2])
				package.loaded[Tests[i][2]] = nil
				if type(result) == "function" then result() end
				if not Tests[i][3] then
					local opMenu = CCMenu()
					opMenu.swallowTouches = true
					opMenu.contentSize = CCSize(60,60)
					opMenu.touchPriority = CCMenu.DefaultHandlerPriority-998
					opMenu.position = oVec2(winSize.width-40,40)
					CCDirector.currentScene:addChild(opMenu,998)
					local endBtn = oButton("Back",17,60,false,
						0,0,
						function()
							CCDirector:replaceScene(CCScene:crossFade(0.5,scene),true)
							if rawget(CCScene,"clearHistory") then
								CCScene:clearHistory()
							end
						end)
					endBtn.anchor = oVec2.zero
					opMenu:addChild(endBtn)
				end
			end)
		button.anchor = oVec2(0,1)
		menu:addChild(button)
	end
	local viewHeight = menu:alignItemsVertically()
	local viewWidth = winSize.width
	local paddingX = 0
	local paddingY = 100
	panel:reset(viewWidth,viewHeight,paddingX,paddingY)

	collectgarbage()
	for _,item in pairs(ubox()) do
		local typeName = tolua.type(item)
		if not startUboxItems[typeName] then
			startUboxItems[typeName] = 0
		end
		startUboxItems[typeName] = startUboxItems[typeName]+1
	end
end

panel:show()

scene:addChild(panel)

panel.keypadEnabled = true
panel:slot("KeyBack",function()
	CCDirector:stop() -- end is Lua keyword, so this function use name stop
end)

panel:slot("Entered",function()
	for _,name in ipairs(loaded) do
		package.loaded[name] = nil
	end
end)

CCDirector.displayStats = true

CCDirector:run(scene)
