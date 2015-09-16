local require = using("EffectEditor.Script")
local CCScene = require("CCScene")
local CCMenu = require("CCMenu")
local oContent = require("oContent")
local CCDirector = require("CCDirector")
local oVec2 = require("oVec2")
local oCache = require("oCache")
local oRoutine = require("oRoutine")
local once = require("once")
local CCDictionary = require("CCDictionary")
local CCRect = require("CCRect")
local emit = require("emit")

local winSize = CCDirector.winSize

local oEditor = CCScene()
oEditor.standAlone = true
oEditor.quitable = false
oEditor.isLoaded = false
oEditor.listFile = "list.effect"
oEditor.effectData = nil
oEditor.prefix = ""
oEditor.input = oContent.writablePath.."Effect/Input/"
oEditor.output = oContent.writablePath.."Effect/Output/"
oEditor.currentName = nil
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

oEditor.dirty = false

oEditor.items = {}

oEditor.isNameExist = function(self,name)
	return self.items[name] ~= nil
end

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
	local listFile = oEditor.output..oEditor.listFile
	oContent:saveToFile(listFile,content)
	oCache.Effect:load(listFile)
end

oEditor.loadEffectFile = function(self)
	local listFile = oEditor.output..oEditor.listFile
	if not oContent:exist(listFile) then
		local file = io.open(listFile,"w")
		file:write("<A></A>")
		file:close()
	end
	local file = io.open(listFile,"r")
	for item in file:read("*a"):gmatch("%b<>") do
		if not item:sub(2,2):match("[A/]") then
			local line = item:gsub("%s","")
			local name = line:match("A=\"(.-)\"")
			local filename = line:match("B=\"(.-)\"")
			oEditor.items[name] = filename
		end
	end
	file:close()
	oCache.Effect:load(listFile)
end

oEditor.dumpData = function(self,filename)
	local file = oEditor.output..oEditor.prefix..filename
	local extension = string.match(filename, "%.([^%.\\/]*)$")
	if extension then extension = string.lower(extension) end
	if extension == "par" then
		local data = oEditor.effectData()
		local str = [[
<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
	<dict>]]
		for k,v in pairs(data) do
			if type(v) == "number" then
				str = str.."\n\t<key>"..k.."</key>\n\t<real>"..tostring(v).."</real>"
			elseif type(v) == "string" then
				str = str.."\n\t<key>"..k.."</key>\n\t<string>"..tostring(v).."</string>"
			end
		end
		str = str.."\n\t</dict>\n</plist>"
		oContent:saveToFile(file,str)
		oCache.Particle:unload(file)
	elseif extension == "frame" then
		local data = oEditor.effectData
		local str = "<A A=\""..data.file.."\" B=\""..tostring(data.interval).."\">"
		for _,it in ipairs(data) do
			str = str.."<B A=\""
				..tostring(it.rect.origin.x)..","
				..tostring(it.rect.origin.y)..","
				..tostring(it.rect.size.width)..","
				..tostring(it.rect.size.height).."\"/>"
		end
		str = str.."</A>"
		oContent:saveToFile(file,str)
		oCache.Animation:unload(file)
	end
	oEditor:emit("Edited",oEditor.prefix..filename)
end

local pair = {true,true}
local function updateAttr(name,value)
	pair[1] = name
	pair[2] = value
	emit("Effect.attr",pair)
end

oEditor.edit = function(self,name)
	oEditor:loadEffectFile()
	local file = oEditor.items[name]
	oEditor.currentName = name
	oEditor.currentFile = file
	local targetFile = oEditor.output..oEditor.prefix..file
	local extension = string.match(file, "%.([^%.\\/]*)$")
	if extension == "par" then
		local dict = CCDictionary(targetFile)
		local keys = dict:getKeys()
		local parData = {}
		local dataWrapper = {}
		setmetatable(dataWrapper,
		{
			__newindex = function(_,name,value)
				if not oEditor.dirty then
					oEditor.dirty = rawget(parData,name) ~= value
				end
				rawset(parData,name,value)
			end,
			__index = function(_,name)
				return rawget(parData,name)
			end,
			__call = function(_)
				return parData
			end
		})
		for _,v in ipairs(keys) do
			parData[v] = dict[v]
		end
		oEditor.effectData = dataWrapper
		if not parData.textureRectx then
			parData.textureRectx = 0
			parData.textureRecty = 0
			parData.textureRectw = 0
			parData.textureRecth = 0
		end
		for k,v in pairs(parData) do
			updateAttr(k,v)
		end
		updateAttr("name",name)
		updateAttr("file",file)
	elseif extension == "frame" then
		local frameFile = io.open(targetFile)
		local fileName = file:match("[^\\/]*$")
		local filePath = (#fileName < #file and file:sub(1,-#fileName-1) or "")
		local data = frameFile:read("*a")
		frameFile:close()
		local img = filePath..data:match("A%s*=%s*\"([^\"]*)\"")
		local interval = tonumber(data:match("<A.*B%s*=%s*\"([^\"]*)\""))
		local frameData = {file=img,interval=interval}
		for rc in data:gmatch("<B[^>]*A%s*=%s*\"([^\"]*)\"") do
			local rect = rc..","
			local nums = {}
			for num in rect:gmatch("(%d+),") do
				table.insert(nums,num)
			end
			table.insert(frameData,{rect = CCRect(nums[1],nums[2],nums[3],nums[4])})
		end
		oEditor.effectData = frameData
		updateAttr("name",name)
		updateAttr("file",file)
		updateAttr("interval",interval)
		emit("Effect.frameViewer.data",oEditor.effectData)
	end
	emit("Effect.viewArea.changeEffect",name)
end

oEditor.newFrame = function(self,name)
	oEditor:loadEffectFile()
	oEditor.currentName = name
	oEditor.currentFile = name..".frame"
	oEditor.items[oEditor.currentName] = oEditor.currentFile
	oEditor.effectData = {file="",interval=1}
	updateAttr("name",oEditor.currentName)
	updateAttr("file",oEditor.currentFile)
	updateAttr("interval",1)
	oContent:saveToFile(oEditor.output..oEditor.prefix..oEditor.currentFile,[[<A A="" B="1"></A>]])
	oEditor:dumpEffectFile()
	emit("Effect.viewArea.changeEffect",oEditor.currentName)
end

oEditor.newParticle = function(self,name)
	oEditor:loadEffectFile()
	local oTemplateChooser = require("oTemplateChooser")
	oEditor:addChild(oTemplateChooser(name..".par"),oEditor.topMost)
end

oEditor.addExistFile = function(self,name)
	oEditor:loadEffectFile()
	local oFileChooser = require("oFileChooser")
	oEditor:addChild(oFileChooser(true,name),oEditor.topMost)
end

local controls =
{
	"oViewArea",
	"oEditMenu",
	"oSettingPanel",
	"oEditControl",
	"oFrameViewer",
}
oRoutine(once(function()
	for index,name in ipairs(controls) do
		local createFunc = require(name)
		coroutine.yield()
		oEditor[name] = createFunc() -- keep lua reference for control items
		coroutine.yield()
		oEditor:addChild(oEditor[name],index)
		coroutine.yield()
	end

	if oEditor.standAlone then	
		oEditor:gslot("Editor.SpriteChooser",function(handler)	
			local oSpriteChooser = require("oSpriteChooser")
			handler(oSpriteChooser())
		end)

		local resPath = "EffectEditor/Effect"
		local writePath = oContent.writablePath.."Effect"
		if not oContent:exist(oContent.writablePath.."Effect") and oContent:exist("EffectEditor/Effect") then
			oContent:copyAsync(resPath,writePath)
		end
		if not oContent:exist(oEditor.input) then
			oContent:mkdir(oEditor.input)
		end
		if not oContent:exist(oEditor.output) then
			oContent:mkdir(oEditor.output)
		end

		oContent:addSearchPath(oEditor.input)

		local oFileChooser = require("oFileChooser")
		oEditor:addChild(oFileChooser(),oEditor.topMost)
	end

	if not oEditor.isLoaded then
		oEditor.isLoaded = true
	end
end))

oEditor:slots("Cleanup",function()
	-- do editor cleanup
	if oEditor.standAlone then
		oContent:removeSearchPath(oEditor.input)
	end
end)

oEditor:slots("Entering",function()
	oRoutine(once(function()
		repeat
			coroutine.yield()
		until oEditor.isLoaded
		oEditor:emit("Activated")
	end))
end)

return oEditor
