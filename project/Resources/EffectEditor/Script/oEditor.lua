local require = using("EffectEditor.Script")
local CCScene = require("CCScene")
local CCMenu = require("CCMenu")
local oContent = require("oContent")
local CCDirector = require("CCDirector")
local oVec2 = require("oVec2")
local oCache = require("oCache")
local oRoutine = require("oRoutine")
local once = require("once")

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
	oContent:saveToFile(oEditor.output..oEditor.listFile,content)
end

oEditor.dumpData = function(self,filename)
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
		oContent:saveToFile(oEditor.output..filename,str)
		oCache.Particle:unload(oEditor.output..filename)
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
		oContent:saveToFile(oEditor.output..filename,str)
		oCache.Animation:unload(oEditor.output..filename)
	end
	oEditor:emit("Edited",filename)
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
