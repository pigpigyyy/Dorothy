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
local oCon = require("oCon")

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

	stopAll = function(self)
		for _,trigger in ipairs(self._triggers) do
			trigger:stop()
		end
	end,
}

local ItemCenter = Class {
	__init = function(self,globalScope,path,keepRef)
		if keepRef == nil then
			keepRef = true
			self._items = {}
		end
		local groups = Path.getFolders(path)
		for _,group in ipairs(groups) do
			local filePath = path..group.."/"
			local files = Path.getFiles(filePath,"lua")
			for _,file in ipairs(files) do
				local loader = loadfile(filePath..file)
				local name = Path.getName(file)
				setfenv(loader,globalScope)
				local func = loader()
				if keepRef then
					self._items[group.."."..name] = func
				end
			end
		end
	end,

	get = function(self, name)
		return self._items[name]
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

		self._notPass = oCon(function() return false end)

		self.__class.weakRef._instance = self
	end,

	ref = function(self) end,

	loadScene = function(self,scene)
		if scene then self._scene = scene end
		-- load current scene tree
		local sceneData = Loader(self.sceneFile)
		sceneData.ui = Loader(self.uiFile)
		local entry = CCScene()
		local gameScene, items = sceneData()
		self._sceneData = sceneData
		self._items = items
		gameScene.position = oVec2(entry.width/2,entry.height/2)
		entry:addChild(gameScene)
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
			-- load condition nodes
			self._conditionCenter = ItemCenter(self._globalScope,self.aiNodePath)
			-- load actions
			self._actionCenter = ItemCenter(self._globalScope,self.actionPath,false)
			-- load AI trees
			self._aiCenter = ItemCenter(self._globalScope,self.aiTreePath,false)
		end
		-- load scene local triggers
		if self._localTrigger then
			self._localTrigger:unregisterAll()
			self._localTrigger:stopAll()
		end
		local localTrigger = TriggerScope(self._globalScope,self.triggerLocalPath)
		localTrigger:registerAll()
		entry:slot("Cleanup",function()
			self:ref()
			localTrigger:stopAll()
		end)
		self._localTrigger = localTrigger
		self._gameNode:emit("Initialized")
		return entry
	end,

	forward = function(self,scene,transition)
		CCScene:forward(self:loadScene(scene),transition)
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

	getCondition = function(self,name)
		return self._conditionCenter:get(name) or self._notPass
	end,

	stopAllTriggers = function(self)
		if self._localTrigger then
			self._localTrigger:stopAll()
		end
		if self._globalTrigger then
			self._globalTrigger:stopAll()
		end
	end,

}
