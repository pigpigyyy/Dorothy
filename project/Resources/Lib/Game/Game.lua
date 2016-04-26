local Loader = require("Lib.Game.Loader")
local Utils = require("Lib.Utils")
local Path = Utils.Path
local CCScene = require("Lib.CCSceneEx")
local property = require("property")
local Class = require("Class")
local oContent = require("oContent")
local oVec2 = require("oVec2")
local classfield = require("classfield")
local CCNode = require("CCNode")

local TriggerScope = Class {
	__init = function(self,globalScope,triggerPath)
		self._triggers = {}
		local triggerFiles = Path.getAllFiles(triggerPath,"lua")
		for _,triggerFile in ipairs(triggerFiles) do
			local triggerLoader = loadfile(triggerPath..triggerFile)
			setfenv(triggerLoader,globalScope)
			table.insert(self._triggers,triggerLoader())
		end
	end,

	registerAll = function(self)
		for _,trigger in ipairs(self._triggers) do
			trigger:register()
		end
	end,

	unregisterAll = function(self)
		for _,trigger in ipairs(self._triggers) do
			trigger:unregister()
		end
	end,
}

local function readOnlyPath(subPath)
	if subPath then
		return property(function(self) return self._gamePath..subPath end)
	else
		return property(function(self) return self._gamePath end)
	end
end

return Class {
	instance = classfield(function(cls)
		return cls.weakRef._instance
	end),
	__initc = function(cls)
		cls.weakRef = setmetatable({},{__mode="v"})
	end,

	gamePath = readOnlyPath(),
	graphicPath = readOnlyPath("Graphic/"),
	physicsPath = readOnlyPath("Physics/"),
	actionPath = readOnlyPath("Logic/Action/"),
	triggerGlobalPath = readOnlyPath("Logic/Trigger/Global/"),
	aiPath = readOnlyPath("Logic/AI/"),
	aiNodePath = readOnlyPath("Logic/AI/Node/"),
	aiTreePath = readOnlyPath("Logic/AI/Tree/"),
	scenePath = readOnlyPath("Scene/"),

	uiFile = readOnlyPath("Scene/UI.scene"),
	globalVarFile = readOnlyPath("Logic/Variable.lua"),
	settingFile = readOnlyPath("Logic/Settings.lua"),
	sceneFile = property(function(self)
		return self.scenePath..self.scene..".scene"
	end),

	triggerLocalPath = property(function(self)
		return self.gamePath.."Logic/Trigger/Local/"..self.scene.."/"
	end),

	settings = property(function(self)
		if not self._settings then
			if oContent:exist(self.settingFile) then
				self._settings = dofile(self.settingFile)
			else
				self._settings = {}
			end
		end
		return self._settings
	end),

	scene = property(function(self)
		return self._scene
	end),

	__init = function(self, name, standAlone)
		if standAlone == nil then standAlone = true end
		self.standAlone = standAlone
		self.name = name
		self._gamePath = table.concat {
			oContent.writablePath,
			"Game/",self.name,"/"
		}
		self._scene = self.settings.StartupScene

		local gameNode = CCNode()
		gameNode:schedule(function()
			gameNode:emit("Update")
		end)
		self._gameNode = gameNode

		self.__class.weakRef._instance = self
	end,

	clearScene = function(self,sceneData)
		print("clearScene",sceneData)
	end,

	loadScene = function(self)
		-- load current scene tree
		local sceneData = Loader(self.sceneFile)
		sceneData.ui = Loader(self.uiFile)
		local entry = CCScene()
		local gameScene, items = sceneData()
		self._sceneData = sceneData
		self._items = items
		gameScene.position = oVec2(entry.width/2,entry.height/2)
		entry:addChild(gameScene)
		entry:slot("Cleanup",function()
			self:clearScene(sceneData)
		end)
		self._entry = entry
		-- move game node
		if self._gameNode.parent then
			self._gameNode.parent:removeChild(self._gameNode,false)
		end
		entry:addChild(self._gameNode)
		-- load global variables
		if not self._globalScope then
			self._globalScope = setmetatable({},{__index=require("Lib.Game.APIs")})
			local globalVarLoader = loadfile(self.globalVarFile)
			setfenv(globalVarLoader,self._globalScope)
			globalVarLoader()
			-- load global triggers
			self._globalTrigger = TriggerScope(self._globalScope,self.triggerGlobalPath)
			self._globalTrigger:registerAll()
		end
		-- load scene local triggers
		if self._localTrigger then
			self._localTrigger:unregisterAll()
		end
		self._localTriggers = TriggerScope(self._globalScope,self.triggerLocalPath)
		self._localTriggers:registerAll()
		self._gameNode:emit("Initialized")
		return entry
	end,

	forward = function(self,transition)
		CCScene:forward(self._entry,transition)
	end,

	slot = function(self,name)
		return self._gameNode:slot(name)
	end,

	getItem = function(self,name)
		if name ~= "InvalidName" then
			return self._items[name]
		end
		return nil
	end,
}
