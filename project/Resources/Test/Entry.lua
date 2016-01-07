Dorothy()

local oButton = require("ActionEditor.Script.oButton")
local oSelectionPanel = require("ActionEditor.Script.oSelectionPanel")
local Tests = require("Test.Tests")

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
opMenu.contentSize = CCSize(200,130)
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

local totalFiles = 0
local function compile(dir,clean,minify)
	local ParseLua = require("luaminify.ParseLua").ParseLua
	local FormatMini = require("luaminify.FormatMini")
	local entries = oContent:getEntries(dir,true)
	for _,item in ipairs(entries) do
		local entry = dir.."/"..item
		if item ~= "." and item ~= ".." then
			if not compile(entry,clean,minify) then
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
				local moonCodes = oContent:loadFile(entry)
				local codes,err = moonscript.to_lua(moonCodes)
				if not codes then
					print("Compile errors in "..entry)
					print(err)
					return false
				else
					if minify then
						local st, ast = ParseLua(codes)
						if not st then
							print(ast)
							return false
						end
						codes = FormatMini(ast)
					end
					oContent:saveToFile(dir.."/"..name..".lua",codes)
					print("Moon compiled: "..entry)
					totalFiles = totalFiles+1
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
				local xmlCodes = oContent:loadFile(entry)
				local codes = xmlToLua(xmlCodes)
				if not codes then
					print("Compile errors in "..entry)
					return false
				else
					if minify then
						local st, ast = ParseLua(codes)
						if not st then
							print(ast)
							return false
						end
						codes = FormatMini(ast)
					end
					oContent:saveToFile(dir.."/"..name..".lua",codes)
					print("xml compiled: "..entry)
					totalFiles = totalFiles+1
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
	70,70,
	function()
		totalFiles = 0
		compile(".",false)
		print(string.format("Compile done. %d files in total.",totalFiles))
	end)
compileButton.anchor = oVec2.zero
opMenu:addChild(compileButton)
compileButton = oButton("Compile\nMinify",12,60,false,
	70,0,
	function()
		totalFiles = 0
		compile(".",false,true)
		print(string.format("Compile and Minify done. %d files in total.",totalFiles))
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

	local function goto(conf)
		local result = require(conf[2])
		package.loaded[conf[2]] = nil

		if not conf[3] then
			CCDirector:run(CCScene:crossFade(0.5, result()))

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
	end

	for i, conf in ipairs(Tests) do
		local button = oButton(conf[1], 16, 200,50, 0,0,function() goto(conf) end)
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
