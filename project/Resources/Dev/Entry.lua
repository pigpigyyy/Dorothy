local oContent = require("oContent")
oContent:addSearchPath("Lib")

local moonscript = require("moonscript")
local Set = require("moonscript.data").Set
local LintGlobal = require("LintGlobal")

local oButton = require("ActionEditor.Script.oButton")
local oSelectionPanel = require("ActionEditor.Script.oSelectionPanel")
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
local tolua = require("tolua")
local CCNode = require("CCNode")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local CCLayer = require("CCLayer")
local builtin = require("builtin")
local ubox = require("ubox")
local xmlToLua = require("xmlToLua")

debug.traceback = function(err)
	local STP = require("StackTracePlus")
	STP.dump_locals = false
	STP.simplified = true
	return STP.stacktrace(err, 1)
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
_G.require = require
builtin.require = require

local scene = CCScene()

local winSize = CCDirector.winSize
local panel = oSelectionPanel(winSize,true)
local menu = panel.menu

local background = CCLayerColor(ccColor4(0xff000000))
panel.border:addChild(background,-1)

local opMenu = CCMenu()
opMenu.swallowTouches = true
opMenu.contentSize = CCSize(60,60)
opMenu.touchPriority = CCMenu.DefaultHandlerPriority-5
opMenu.position = oVec2(winSize.width-40,40)
panel:addChild(opMenu)
if CCApplication.targetPlatform ~= CCTargetPlatform.Ipad and CCApplication.targetPlatform ~= CCTargetPlatform.Iphone then
	local endButton = oButton("Exit",17,60,false,0,0,function()
		CCDirector:stop()
	end)
	endButton.anchor = oVec2.zero
	opMenu:addChild(endButton)
end

opMenu = CCMenu()
opMenu.contentSize = CCSize(200,130)
opMenu.touchPriority = CCMenu.DefaultHandlerPriority-5
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
		for k,_ in pairs(itemMap) do
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
		--[[
		print("Loaded Modules:")
		for k,_ in pairs(package.loaded) do
			print(k)
		end
		--]]
		--[[
		print("Global Values:")
		for k,v in pairs(_G) do
			print(k,v)
		end
		--]]
	end)
gcButton.anchor = oVec2.zero
opMenu:addChild(gcButton)

local allowedUseOfGlobals =
{
	"editor"
}
allowedUseOfGlobals = Set(allowedUseOfGlobals)

local function LintMoonGlobals(moonCodes,entry)
	local globals = LintGlobal(moonCodes)
	local requireModules = {}
	for name,_ in pairs(globals) do
		if not allowedUseOfGlobals[name] then
			if builtin[name] then
				table.insert(requireModules,string.format("local %s = require(\"%s\")",name,name))
			else
				error("Used invalid global value \""..name.."\" in "..entry)
			end
		end
	end
	return table.concat(requireModules,"\n")
end

local totalFiles = 0
local totalMoonTime = 0
local totalXmlTime = 0
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
				local requires = LintMoonGlobals(moonCodes,entry)
				local startTime = CCDirector.eclapsedInterval
				local codes,err = moonscript.to_lua(moonCodes)
				totalMoonTime = totalMoonTime + CCDirector.eclapsedInterval - startTime
				if not codes then
					print("Compile errors in "..entry)
					print(err)
					return false
				else
					codes = requires..codes:gsub("Dorothy%(%)","")
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
				local startTime = CCDirector.eclapsedInterval
				local codes = xmlToLua(xmlCodes)
				totalXmlTime = totalXmlTime + CCDirector.eclapsedInterval - startTime
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

local function doCompile(minify)
	totalFiles = 0
	totalMoonTime = 0
	totalXmlTime = 0
	compile(".",false,minify)
	print(string.format("Compile "..(minify and "and minify " or "").."done. %d files in total.\nCompile time, Moon %.3fs, Xml %.3fs.",totalFiles,totalMoonTime,totalXmlTime))
end

local compileButton = oButton("Compile",13,60,false,70,70,function()
	doCompile(false)
end)
compileButton.anchor = oVec2.zero
opMenu:addChild(compileButton)

compileButton = oButton("Compile\nMinify",13,60,false,70,0,function()
	doCompile(true)
end)
compileButton.anchor = oVec2.zero
opMenu:addChild(compileButton)

local cleanButton = oButton("Clean",16,60,false,140,0,function()
	compile(".",true)
	print("Clean done.")
end)
cleanButton.anchor = oVec2.zero
opMenu:addChild(cleanButton)

panel.init = function(_)
	menu.opacity = 0
	menu.enabled = false
	menu:runAction(oOpacity(0.3,1))

	local function addTitle(title,fontSize,color)
		local width = math.floor((winSize.width-10)/210)*210-10
		local label = CCLabelTTF(title,"Arial",fontSize)
		label.texture.antiAlias = false
		label.position = oVec2(width/2,15)
		label.color = ccColor3(color)
		local node = CCNode()
		node.contentSize = CCSize(width,30)
		node:addChild(label)
		menu:addChild(node)
	end

	local function run(file)
		local result = require(file)
		if type(result) == "function" then
			result()
		elseif type(result) == "table" and result.isTest then
			local test = result()
			test:enterScene()
			test:profileRun()
		end
	end
	local function runWithBackButton(file)
		run(file)
		local endBtn = oButton("Back",17,60,false,0,0,function()
			CCDirector:replaceScene(CCScene:crossFade(0.5,scene),true)
			if CCScene.clearHistory then
				CCScene:clearHistory()
			end
		end)
		endBtn.anchor = oVec2.zero
		local backMenu = CCMenu()
		backMenu.swallowTouches = true
		backMenu.contentSize = CCSize(60,60)
		backMenu.touchPriority = CCMenu.DefaultHandlerPriority-998
		backMenu.position = oVec2(winSize.width-40,40)
		backMenu:addChild(endBtn)
		CCDirector.currentScene:addChild(backMenu,998)
	end

	addTitle("Dorothy Project",24,0x00ffff)
	addTitle("Editors",20,0xff0080)
	local editors = {
		{"Action Editor","ActionEditor.Script.main"},
		{"Body Editor","BodyEditor.Script.main"},
		{"Effect Editor","EffectEditor.Script.main"},
		{"Scene Editor","SceneEditor.main"},
	}
	for i = 1,#editors do
		local editor = editors[i]
		local name,module = editor[1],editor[2]
		local button = oButton(name,16,200,50,0,0,function()
			run(module)
		end)
		button.anchor = oVec2(0,1)
		menu:addChild(button)
	end

	addTitle("Samples",20,0xff0080)
	local files = oContent:getEntries("Dev/Sample/",false)
	for i = 1,#files do files[i] = files[i]:match("^([^%.]*)") end
	files = Set(files)
	for file,_ in pairs(files) do
		if file ~= "" then
			local button = oButton(file,16,200,50,0,0,function()
				runWithBackButton("Dev/Sample/"..file)
			end)
			button.anchor = oVec2(0,1)
			menu:addChild(button)
		end
	end

	addTitle("Tests",20,0xff0080)
	files = oContent:getEntries("Dev/Test/",false)
	for i = 1,#files do files[i] = files[i]:match("^([^%.]*)") end
	files = Set(files)
	for file,_ in pairs(files) do
		if file ~= "" then
			local button = oButton(file,16,200,50,0,0,function()
				runWithBackButton("Dev/Test/"..file)
			end)
			button.anchor = oVec2(0,1)
			menu:addChild(button)
		end
	end

	local viewSize = menu:alignItems()
	local paddingX = 0
	local paddingY = 100
	menu.positionX = -viewSize.width/2
	local viewHeight = math.max(winSize.height,viewSize.height)+100
	panel:reset(viewSize.width,viewHeight,paddingX,paddingY)

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

panel:slot("Entered",function()
	for _,name in ipairs(loaded) do
		package.loaded[name] = nil
	end
end)
scene:addChild(panel)

local layerEnd = CCLayer()
layerEnd.anchor = oVec2.zero
layerEnd.keypadEnabled = true
layerEnd:slot("KeyBack",function() -- close app at anytime on keyback event
	if CCApplication.targetPlatform ~= CCTargetPlatform.Ipad or CCApplication.targetPlatform ~= CCTargetPlatform.Iphone then
		CCDirector:stop()
	end
end)
CCDirector.notificationNode = layerEnd

--CCDirector.displayStats = true

CCDirector:run(scene)
