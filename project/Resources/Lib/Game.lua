local oBody = require("oBody")
local oEffect = require("oEffect")
local tolua = require("tolua")
local oModel = require("oModel")
local CCScheduler = require("CCScheduler")
local oWorld = require("oWorld")
local oPlatformWorld = require("oPlatformWorld")
local CCSprite = require("CCSprite")
local oData = require("oData")
local oVec2 = require("oVec2")
local CCDirector = require("CCDirector")

local Simulation = function(level)
	if 1 == level then
		return 1, 1
	elseif 2 == level then
		return 4, 2
	elseif 3 == level then
		return 8, 3
	end
end

local Children = function(parent, data)
	local children = data.children
	if children then
		for i, child in ipairs(children) do
			child = child(parent, i)
			if child then
				parent:addChild(child)
			end
		end
	end
end

local Contact = function(world, data)
	local groups = data.groups
	local contacts = data.contacts
	if groups and contacts then
		for i = 1, #contacts do
			local contact = contacts[i]
			world:setShouldContact(unpack(contact))
		end
	end
end

local Groups = function(data)
	local default = {
		[0] = "Hide",
		"P1","P2","P3","P4",
		"P5","P6","P7","P8",
		"P9","P10","P11","P12",
		"DetectPlayer",
		"Terrain",
		"Detect"
	}
	return setmetatable(data, {__index = default})
end

local Contacts = function(data)
	return data
end

local function AlignGet(pos,align)
	if align == 1 then -- Center
		return pos
	else
		local winSize = CCDirector.winSize
		if align == 2 then -- LeftBottom
			return pos-oVec2(winSize.width/2,winSize.height/2)
		elseif align == 3 then -- LeftTop
			return oVec2(pos.x-winSize.width/2,winSize.height/2-pos.y)
		elseif align == 4 then -- RightTop
			return oVec2(winSize.width/2,winSize.height/2)-pos
		elseif align == 5 then -- RightBottom
			return oVec2(winSize.width/2-pos.x,pos.y-winSize.height/2)
		else
			return pos
		end
	end
end

local Types = {
	PlatformWorld = 1,
	UILayer = 2,
	Camera = 3,
	Layer = 4,
	World = 5,
	Body = 6,
	Model = 7,
	Sprite = 8,
	Effect = 9,
	SubCam = 10
}

local TypeNames = {}
for k, v in pairs(Types) do
	TypeNames[v] = k
end

local DataCreater = function(dataDef)
	local create = dataDef.create
	dataDef.create = nil
	local dataMt = {
		__call = function(self, parent, index)
			return create(self, parent, index)
		end,
		__index = function(self, k)
			local index = dataDef[k]
			if index then
				return self[index]
			else
				return nil
			end
		end
	}
	return function(data)
		return setmetatable(data, dataMt)
	end
end

local items
local sceneData
local GameItems = {
	PlatformWorld = DataCreater({
		itemType = 1,
		gravity = 2,
		contacts = 3,
		groups = 4,
		simulation = 5,
		camera = 6,
		ui = 7,
		children = 8,
		outline = 9,
		create = function(self)
			sceneData = self

			local world = oPlatformWorld()
			world.gravity = oVec2(0, self.gravity)
			world:setIterations(Simulation(self.simulation))
			world.scheduler = CCScheduler()
			world:slot("Cleanup", function()
				CCDirector.scheduler:unschedule(world.scheduler)
			end)
			CCDirector.scheduler:schedule(world.scheduler)
			items = {Scene = world}
			if self.camera then
				self.camera(world)
			end
			if self.ui then
				self.ui(world)
			end
			Contact(world, self)
			Children(world, self)
			return world
		end
	}),

	UILayer = DataCreater({
		itemType = 1,
		visible = 2,
		children = 3,
		display = 4,
		fold = 5,
		create = function(self, scene)
			local layer = scene.UILayer
			items.UI = layer
			layer.visible = self.visible
			Children(layer, self)
			return nil
		end
	}),

	Camera = DataCreater({
		itemType = 1,
		boundary = 2,
		area = 3,
		subCams = 4,
		create = function(self, scene)
			local camera = scene.camera
			items.Camera = camera
			return nil
		end
	}),

	SubCam = DataCreater({
		itemType = 1,
		name = 2,
		position = 3,
		zoom = 4,
		angle = 5,
		create = function(self)
			return nil
		end
	}),

	Layer = DataCreater({
		itemType = 1,
		name = 2,
		ratioX = 3,
		ratioY = 4,
		offset = 5,
		zoom = 6,
		visible = 7,
		children = 8,
		display = 9,
		fold = 10,
		create = function(self, scene, index)
			scene:setLayerOffset(index, self.offset)
			local layer = scene:getLayer(index)
			layer.scaleX = self.zoom
			layer.scaleY = self.zoom
			layer.visible = self.visible
			items[self.name] = layer
			Children(layer, self)
			return nil
		end
	}),

	World = DataCreater({
		itemType = 1,
		name = 2,
		gravity = 3,
		simulation = 4,
		ratioX = 5,
		ratioY = 6,
		offset = 7,
		zoom = 8,
		visible = 9,
		children = 10,
		outline = 11,
		display = 12,
		fold = 13,
		create = function(self, scene, index)
			scene:setLayerOffset(index, self.offset)

			local layer = scene:getLayer(index)
			layer.scaleX = self.zoom
			layer.scaleY = self.zoom

			local world = oWorld()
			world.gravity = self.gravity
			world.visible = self.visible
			world:setIterations(Simulation(self.simulation))
			layer:addChild(world)

			world.scheduler = CCScheduler()
			CCDirector.scheduler:schedule(world.scheduler)
			world:slot("Cleanup", function()
				CCDirector.scheduler:unschedule(world.scheduler)
			end)
			oData:apply(world)
			Contact(world, sceneData)
			items[self.name] = world
			Contact(world, self)
			Children(world, self)
			return nil
		end
	}),

	Body = DataCreater({
		itemType = 1,
		name = 2,
		file = 3,
		group = 4,
		position = 5,
		angle = 6,
		visible = 7,
		display = 8,
		create = function(self, parent)
			local world = items.Scene
			if "oWorld" == tolua.type(parent) then
				world = parent
			end
			local body = oBody(self.file, world, self.position, self.angle)
			body.data:each(function(_, v)
				if "oBody" == tolua.type(v) then
					v.group = self.group
				end
			end)
			body.visible = self.visible
			items[self.name] = body
			return body
		end
	}),

	Model = DataCreater({
		itemType = 1,
		name = 2,
		file = 3,
		position = 4,
		angle = 5,
		scale = 6,
		skew = 7,
		opacity = 8,
		look = 9,
		animation = 10,
		speed = 11,
		loop = 12,
		faceRight = 13,
		visible = 14,
		display = 15,
		align = 16,
		create = function(self)
			local model = oModel(self.file)
			model.position = AlignGet(self.position,self.align)
			model.angle = self.angle
			model.scaleX = self.scale.x
			model.scaleY = self.scale.y
			model.skewX = self.skew.x
			model.skewY = self.skew.y
			model.opacity = self.opacity
			model.look = self.look
			model.speed = self.speed
			model.loop = self.loop
			model.faceRight = self.faceRight
			model.visible = self.visible
			model:play(self.animation)
			items[self.name] = model
			return model
		end
	}),

	Sprite = DataCreater({
		itemType = 1,
		name = 2,
		file = 3,
		position = 4,
		angle = 5,
		scale = 6,
		skew = 7,
		opacity = 8,
		visible = 9,
		display = 10,
		align = 11,
		create = function(self)
			local sprite = CCSprite(self.file)
			sprite.position = AlignGet(self.position,self.align)
			sprite.angle = self.angle
			sprite.scaleX = self.scale.x
			sprite.scaleY = self.scale.y
			sprite.skewX = self.skew.x
			sprite.skewY = self.skew.y
			sprite.opacity = self.opacity
			sprite.visible = self.visible
			items[self.name] = sprite
			return sprite
		end
	}),

	Effect = DataCreater({
		itemType = 1,
		name = 2,
		effect = 3,
		position = 4,
		play = 5,
		visible = 6,
		display = 7,
		align = 8,
		create = function(self, parent)
			local effect = oEffect(self.effect)
			effect.visible = self.visible
			effect:attachTo(parent)
			effect:setOffset(AlignGet(self.position,self.align))
			if self.play then
				effect:start()
			end
			items[self.name] = effect
			return nil
		end
	})
}

local function loadData(filename)
	local setupData
	setupData = function(data)
		GameItems[TypeNames[data[1]]](data)
		if data.children then
			local children = data.children
			for i = 1, #children do
				local child = children[i]
				setupData(child)
			end
		end
	end
	local data = dofile(filename)
	setupData(data)
	if data.contacts then
		Contacts(data.contacts)
	end
	if data.groups then
		Groups(data.groups)
	end
	if data.camera then
		local camera = data.camera
		GameItems.Camera(camera)
		if camera.subCams then
			local subCams = camera.subCams
			for i = 1, #subCams do
				local cam = subCams[i]
				GameItems.SubCam(cam)
			end
		end
	end
	return data
end

return loadData
