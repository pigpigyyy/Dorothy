Dorothy!
Class,property = unpack require "class"
EditorView = require "View.Scene.Editor"
SelectionPanel = require "Control.Basic.SelectionPanel"
Model = require "Data.Model"
Reference = require "Data.Reference"

Class EditorView,
	__init: =>
		{:width,:height} = CCDirector.winSize
		@_gameName = nil
		@_gameFullPath = nil
		@_actionEditor = nil
		@_bodyEditor = nil
		@_effectEditor = nil
		@items = nil
		@itemDefs = nil
		@dirty = false
		@sceneData = nil
		@currentData = nil
		@_sceneName = nil
		@_currentSceneFile = nil
		@origin = oVec2 width/2,height/2
		@offset = oVec2 60+(width-250)/2,height/2
		@scale = 1
		@xFix = false
		@yFix = false
		@isFixed = true
		@camPos = oVec2 width/2,height/2

		_G.editor = @
		builtin.editor = @

		@slot "Cleanup",->
			Reference.stopUpdate!
			_G.editor = nil
			builtin.editor = nil
			oCache\clear!
			CCScene\remove "actionEditor"
			CCScene\remove "bodyEditor"
			CCScene\remove "effectEditor"

		CCScene\transition "rollIn",{"zoomFlip",0.5,CCOrientation.Down}
		CCScene\transition "rollOut",{"zoomFlip",0.5,CCOrientation.Up}

		level = (level)-> CCMenu.DefaultHandlerPriority-level*10
		@levelViewArea = level 5
		@levelEditControl = level 6
		@levelHRuler = level 7
		@levelVRuler = level 7
		@levelEditMenu = level 8
		@levelOperationPanel = level 8
		@levelItemPanel = level 9
		@levelClipEditor = level 10
		@levelMessageBox = level 11
		@levelInputBox = level 11
		@levelSelectionPanel = level 11

		@schedule once ->
			sleep!
			controlNames = {
				"ViewArea"
				"HRuler"
				"VRuler"
				"EditMenu"
				"ViewPanel"
				"SettingPanel"
			}
			for name in *controlNames
				Control = require "Control.Operation."..name
				sleep!
				control = Control!
				@[name\sub(1,1)\lower!..name\sub(2,-1)] = control
				@addChild control
			sleep!
			ScenePanel = require "Control.Item.ScenePanel"
			ScenePanel!
			sleep!
			Manager = require "Control.Edit.Manager"
			@editManager = Manager!
			@viewArea\addChild @editManager
			@moveTo oVec2.zero

		panelWidth = 10+110*4
		panelHeight = height*0.6
		setupPanel = (name)->
			return unless @game
			panelName = name\sub(1,1)\lower!..name\sub(2,-1).."Panel"
			if not @[panelName]
				Panel = require "Control.Item."..name.."Panel"
				panel = Panel {
					x:width/2
					y:height/2
					width:panelWidth
					height:panelHeight
				}
				panel.visible = false
				@[panelName] = panel
				@addChild panel
				eventName = "Scene.#{name}Selected"
				panel.notifyEditor = (file)-> emit eventName,file
				panel\slot "Selected",panel.notifyEditor
			@[panelName]

		@gslot "Scene.ViewSprite",-> setupPanel "Sprite"
		@gslot "Scene.ViewModel",-> setupPanel "Model"
		@gslot "Scene.ViewBody",-> setupPanel "Body"
		@gslot "Scene.ViewEffect",-> setupPanel "Effect"
		@gslot "Scene.ViewLayer",->
			return unless @game
			with SelectionPanel items:{"Layer","World"}
				\slot "Selected",(item)->
					emit "Scene.LayerSelected",item

		currentCam = nil
		@gslot "Scene.Camera.Activate",(cam)->
			if cam
				@applyCam cam
				thread ->
					sleep 0.6
					currentCam = cam
			else
				currentCam = nil
		@gslot "Scene.Camera.Select",(subCam)-> @applyCam subCam
		@gslot "Scene.ViewArea.ScaleTo",(scale)->
			if @items
				@items.Camera\perform oScale 0.5,scale,scale,oEase.OutQuad
				currentCam.zoom = scale if currentCam
			@scale = scale
		@gslot "Scene.ViewArea.Scale",(scale)->
			if @items
				with @items.Camera
					.scaleX = scale
					.scaleY = scale
				currentCam.zoom = scale if currentCam
			@scale = scale
		@gslot "Scene.ViewArea.Move",(delta)->
			delta /= -@scale
			if @items
				@items.Camera.position += delta
				currentCam.position = @items.Camera.position if currentCam
			else
				emit "Scene.Camera.Move",delta
		@gslot "Scene.Camera.Move",(delta)-> @camPos += delta
		@gslot "Scene.ViewArea.MoveTo",(pos)->
			if @items
				@items.Camera\perform oPos 0.5,pos.x,pos.y,oEase.OutQuad
				currentCam.position = pos if currentCam
			else
				emit "Scene.Camera.MoveTo",pos
		@gslot "Scene.Camera.MoveTo",(pos)-> @camPos = pos

		@gslot "Editor.ItemChooser",(args)->
			handler = args[#args]
			table.remove args
			chooseItem = (itemType)->
				switch itemType
					when "Sprite","Model","Effect","Body"
						panel = setupPanel itemType
						panel\slot "Selected",nil
						panel.parent\removeChild panel,false
						panel\slot("Hide")\set ->
							panel.parent\removeChild panel,false
							@addChild panel,1
							panel\slot("Selected")\set panel.notifyEditor
						handler panel
					else
						handler nil
			if #args == 1
				chooseItem args[1]
			else
				with SelectionPanel items:args
					\slot "Selected",(itemType)->
						chooseItem itemType

		effectUpdated = (itemName)->
			Reference.refreshRef itemName
			@eachSceneItem (itemData)->
				if itemData.typeName == "Effect" and
					itemName == oCache.Effect\getFileByName(itemData.effect)\sub(-#itemName,-1)
					@resetData itemData
		itemUpdated = (itemName)->
			Reference.refreshRef itemName
			@eachSceneItem (itemData)->
				if itemData.file == itemName
					@resetData itemData
		@gslot "Scene.ModelUpdated",itemUpdated
		@gslot "Scene.BodyUpdated",itemUpdated
		@gslot "Scene.EffectUpdated",effectUpdated
		@gslot "Scene.ClipUpdated",itemUpdated

		selectItem = (typeName,item)->
			@selectedType,@selectedItem = if item then typeName,item else nil,nil
		@gslot "Scene.SpriteSelected",(item)-> selectItem "Sprite",item
		@gslot "Scene.ModelSelected",(item)-> selectItem "Model",item
		@gslot "Scene.BodySelected",(item)-> selectItem "Body",item
		@gslot "Scene.EffectSelected",(item)-> selectItem "Effect",item
		@gslot "Scene.LayerSelected",(item)-> selectItem item,item

		@gslot "Scene.ViewPanel.Select",(itemData)-> @currentData = itemData

		setCurrentData = (itemData)-> @currentData = itemData
		@gslot "Scene.ViewPanel.Select",setCurrentData
		@gslot "Scene.ViewPanel.Pick",setCurrentData

	updateSprites: => emit "Scene.LoadSprite",@graphicFolder
	updateModels: => emit "Scene.LoadModel",@graphicFolder
	updateBodies: => emit "Scene.LoadBody",@physicsFolder
	updateEffects: => emit "Scene.LoadEffect",@graphicFolder

	game: property => @_gameName,
		(name)=>
			oContent\removeSearchPath @_gameFullPath if @_gameFullPath
			@_gameName = name
			if name
				@_gameFullPath = @gamesFullPath..name.."/"
				oContent\addSearchPath @_gameFullPath
				oContent\mkdir @_gameFullPath unless oContent\exist @_gameFullPath
				oContent\mkdir @graphicFullPath unless oContent\exist @graphicFullPath
				oContent\mkdir @physicsFullPath unless oContent\exist @physicsFullPath
				oContent\mkdir @logicFullPath unless oContent\exist @logicFullPath
				oContent\mkdir @sceneFullPath unless oContent\exist @sceneFullPath
				if @_actionEditor
					@actionEditor.input = @gameFullPath
					@actionEditor.output = @gameFullPath
				if @_bodyEditor
					@bodyEditor.input = @gameFullPath
					@bodyEditor.output = @gameFullPath
			else
				@_gameFullPath = nil
			@currentSceneFile = nil
			oCache\clear!
			Reference.update!

	eachSceneItem: (handler)=>
		if @sceneData
			if @sceneData.ui and @sceneData.ui.children
				for child in *@sceneData.ui.children
					handler child
			if @sceneData.children
				for layer in *@sceneData.children
					if layer.children
						for child in *layer.children
							handler child

	gamesFullPath: property => oContent.writablePath.."Game/"
	gameFullPath: property => @_gameFullPath
	graphicFolder: property => "Graphic/"
	graphicFullPath: property => @_gameFullPath.."Graphic/"
	physicsFolder: property => "Physics/"
	physicsFullPath: property => @_gameFullPath.."Physics/"
	logicFolder: property => "Logic/"
	logicFullPath: property => @_gameFullPath.."Logic/"
	sceneFolder: property => "Scene/"
	sceneFullPath: property => @_gameFullPath.."Scene/"
	uiFileFullPath: property => @sceneFullPath.."UI.scene"

	actionEditor: property =>
		if not @_actionEditor
			actionEditor = require "ActionEditor.Script.oEditor"
			actionEditor.standAlone = false
			actionEditor.quitable = true
			actionEditor.input = @gameFullPath
			actionEditor.output = @gameFullPath
			actionEditor.prefix = @graphicFolder
			actionEditor\slot "Edited",(model)->
				emit "Scene.ModelUpdated",model
			actionEditor\slot "Quit",->
				CCScene\back "rollIn"
				@updateModels!
			CCScene\add "actionEditor",actionEditor
			@_actionEditor = actionEditor
		@_actionEditor

	bodyEditor: property =>
		if not @_bodyEditor
			bodyEditor = require "BodyEditor.Script.oEditor"
			bodyEditor.standAlone = false
			bodyEditor.quitable = true
			bodyEditor.input = @gameFullPath
			bodyEditor.output = @gameFullPath
			bodyEditor\slot "Edited",(body)->
				emit "Scene.BodyUpdated",body
			bodyEditor\slot "Quit",->
				CCScene\back "rollIn"
				@updateBodies!
			CCScene\add "bodyEditor",bodyEditor
			@_bodyEditor = bodyEditor
		@_bodyEditor

	effectEditor: property =>
		if not @_effectEditor
			effectEditor = require "EffectEditor.Script.oEditor"
			effectEditor.standAlone = false
			effectEditor.quitable = true
			effectEditor.listFile = @graphicFolder.."list.effect"
			effectEditor.prefix = @graphicFolder
			effectEditor.input = @gameFullPath
			effectEditor.output = @gameFullPath
			effectEditor\slot "Edited",(effect)->
				emit "Scene.EffectUpdated",effect
			effectEditor\slot "Quit",->
				CCScene\back "rollIn"
				@updateEffects!
			CCScene\add "effectEditor",effectEditor
			@_effectEditor = effectEditor
		@_effectEditor

	getUsableName: (originalName)=>
		originalName = "name" if originalName == ""
		if @items[originalName]
			counter = 1
			nawName = nil
			usable = false
			while not usable
				nawName = originalName..tostring counter
				usable = (@items[nawName] == nil)
				counter += 1
			nawName
		else
			originalName

	renameData: (itemData,name)=>
		return nil if itemData.name == name
		switch itemData.typeName
			when "UILayer","PlatformWorld","Camera"
				return nil
		itemName = itemData.name
		name = @getUsableName name
		item = @items[itemName]
		@items[itemName] = nil
		@items[name] = item
		itemData.name = name
		name

	getItem: (itemData)=>
		itemName = switch itemData.typeName
			when "UILayer"
				"UI"
			when "PlatformWorld"
				"Scene"
			when "Camera"
				"Camera"
			else
				itemData.name
		@items[itemName]

	getData: (item)=> @itemDefs[item]

	getSceneName: (itemData)=>
		item = @getItem itemData
		parentData = @getData item.parent
		if parentData.typeName == "UILayer"
			"UI.scene"
		else
			@scene..".scene"

	insertData: (parentData,newData,targetData,afterTarget=true)=>
		-- insert newData to parentData.children before targetData
		parentData.children = {} unless parentData.children
		index = #parentData.children+1
		if targetData
			for i,child in ipairs parentData.children
				if child == targetData
					index = afterTarget and i+1 or i
					break
		table.insert parentData.children,index,newData
		if targetData
			parent = editor\getItem parentData
			child = newData parent,index
			if parentData.typeName == "PlatformWorld"
				if index < #parentData.children
					for i = #parentData.children,index,-1
						parent\swapLayer i,i+1
			elseif child
				parent\addChild child
				children = parent.children
				children\removeLast!
				children\insert child,index
		else
			parent = @getItem parentData
			child = newData parent,index
			if child
				parent\addChild child
		sceneName = if parentData.typeName == "UILayer"
				"UI.scene"
			else
				@scene..".scene"
		Reference.addSceneItemRef sceneName,newData
		emit "Scene.Dirty",true
		index

	removeData: (itemData,parentData)=>
		item = @getItem itemData
		parent = @getItem parentData
		index = nil
		for i,child in ipairs parentData.children
			if child == itemData
				index = i
				break
		return unless index
		@itemDefs[item] = nil
		sceneName = if parentData.typeName == "UILayer"
				"UI.scene"
			else
				@scene..".scene"
		switch itemData.typeName
			when "Layer","World"
				if itemData.children
					for childData in *itemData.children
						childItem = @items[childData.name]
						@itemDefs[childItem] = nil
						@items[childData.name] = nil
						Reference.removeSceneItemRef sceneName,childData
				parent\removeLayer index
				for i = index,#parentData.children-1
					parent\swapLayer i,i+1
			when "Effect"
				item\autoRemove!
				item\stop!
			else
				parent\removeChild item
		table.remove parentData.children,index
		parentData.children = false if #parentData.children == 0
		@items[itemData.name] = nil
		Reference.removeSceneItemRef sceneName,itemData
		emit "Scene.Dirty",true
		index

	resetData: (itemData)=>
		switch itemData.typeName
			when "Layer","World","Camera","PlatformWorld"
				return
		item = @getItem itemData
		parentData = @getData item.parent
		index = nil
		for i,child in ipairs parentData.children
			if child == itemData
				index = i
				break
		targetData = parentData.children[index+1]
		@removeData itemData,parentData
		@insertData parentData,itemData,targetData,false

	moveDataUp:(itemData,parentData)=>
		index = 1
		for i,v in ipairs parentData.children
			if itemData == v
				index = i
				break
		if index > 1
			parentData.children[index] = parentData.children[index-1]
			parentData.children[index-1] = itemData
			parent = @getItem parentData
			if parentData.typeName == "PlatformWorld"
				parent\swapLayer index,index-1
			else
				parent.children\exchange index,index-1
			emit "Scene.Dirty",true
		index

	moveDataDown: (itemData,parentData)=>
		index = #parentData.children
		for i,v in ipairs parentData.children
			if itemData == v
				index = i
				break
		if index < #parentData.children
			parentData.children[index] = parentData.children[index+1]
			parentData.children[index+1] = itemData
			parent = @getItem parentData
			if parentData.typeName == "PlatformWorld"
				parent\swapLayer index,index+1
			else
				parent.children\exchange index,index+1
			emit "Scene.Dirty",true
		index

	moveDataTop: (itemData,parentData)=>
		index = 1
		for i,v in ipairs parentData.children
			if itemData == v
				index = i
				break
		tmpIndex = index
		if index > 1
			table.remove parentData.children,index
			table.insert parentData.children,1,itemData
			parent = @getItem parentData
			if parentData.typeName == "PlatformWorld"
				prev = index-1
				while prev >= 1
					parent\swapLayer index,prev
					prev -= 1
					index -= 1
			else
				prev = index-1
				while prev >= 1
					parent.children\exchange index,prev
					prev -= 1
					index -= 1
			emit "Scene.Dirty",true
		tmpIndex

	moveDataBottom: (itemData,parentData)=>
		count = #parentData.children
		index = count
		for i,v in ipairs parentData.children
			if itemData == v
				index = i
				break
		tmpIndex = index
		if index < count
			table.remove parentData.children,index
			table.insert parentData.children,itemData
			parent = editor\getItem parentData
			if parentData.typeName == "PlatformWorld"
				nextIndex = index+1
				while nextIndex <= count
					parent\swapLayer index,nextIndex
					nextIndex += 1
					index += 1
			else
				nextIndex = index+1
				while nextIndex <= count
					parent.children\exchange index,nextIndex
					nextIndex += 1
					index += 1
			emit "Scene.Dirty",true
		tmpIndex

	save: =>
		return unless @sceneData
		ui = @sceneData.ui
		@sceneData.ui = false
		Model.dumpData @sceneData,@gameFullPath..@currentSceneFile
		Model.dumpData ui,@uiFileFullPath
		@sceneData.ui = ui

	scene: property => @_sceneName,
		(value)=>
			@currentSceneFile = if value
				editor.sceneFolder..value..".scene"
			else
				nil

	currentSceneFile: property => @_currentSceneFile,
		(sceneFile)=>
			@_currentSceneFile = sceneFile
			if sceneFile
				@_sceneName = sceneFile\match "([^\\/]*)%.[^%.\\/]*$"
				@sceneData = Model.loadData @gameFullPath..sceneFile
				@sceneData.ui = Model.loadData @uiFileFullPath
			else
				@sceneData = nil
				@items = nil
				@itemDefs = nil
				@_sceneName = nil
			emit "Scene.DataLoaded",@sceneData

	newScene: (sceneName)=>
		sceneFile = editor.sceneFolder..sceneName..".scene"
		return if oContent\exist sceneFile
		@sceneData = with Model.PlatformWorld!
			.camera = Model.Camera!
			.ui = if oContent\exist @uiFileFullPath
					Model.loadData @uiFileFullPath
				else
					Model.UILayer!
		@_sceneName = sceneFile\match "([^\\/]*)%.[^%.\\/]*$"
		@_currentSceneFile = sceneFile
		@save!
		emit "Scene.DataLoaded",@sceneData

	deleteCurrentScene: =>
		return unless @currentSceneFile
		oContent\remove @currentSceneFile
		Reference.removeSceneRef @currentSceneFile,@sceneData
		@currentSceneFile = nil

	deleteCurrentGame: =>
		return unless @game
		visitResource = (path)->
			return unless oContent\exist path
			files = oContent\getEntries path,false
			for file in *files
				filename = path..file
				oContent\remove filename
			folders = oContent\getEntries path,true
			for folder in *folders
				if folder ~= "." and folder ~= ".."
					visitResource path..folder.."/"
			oContent\remove path
		visitResource @gameFullPath
		@game = nil

	updateGroupName: (groupIndex,name)=>
		@sceneData.groups[groupIndex] = name
		emit "Scene.Dirty",true

	updateContact: (groupA,groupB,shouldContact)=>
		updated = false
		for i,contact in ipairs @sceneData.contacts
			group1,group2 = unpack contact
			if (group1 == groupA and group2 == groupB) or (group1 == groupB and group2 == groupA)
				if shouldContact
					contact[3] = shouldContact
				else
					table.remove @sceneData.contacts,i
				updated = true
				break
		if not updated
			table.insert @sceneData.contacts,{groupA,groupB,shouldContact}
		@items.Scene\setShouldContact groupA,groupB,shouldContact
		if @sceneData.children
			for child in @sceneData.children
				if child.typeName == "World"
					subWorld = @getItem child
					subWorld\setShouldContact groupA,groupB,shouldContact
		emit "Scene.Dirty",true

	moveTo:(pos)=>
		pos = oVec2.zero-pos
		{:width,:height} = CCDirector.winSize
		posX = pos.x+width/2-(width/2-@offset.x)/@scale
		posY = pos.y+height/2-(height/2-@offset.y)/@scale
		emit "Scene.ViewArea.MoveTo",oVec2(width/2-posX,height/2-posY)

	applyCam:(subCam)=>
		return unless @items
		scene = @items.Scene
		camera = @items.Camera
		if subCam
			if @sceneData.children
				lastPos = camera.position
				camera.position = oVec2.zero
				for index,layerData in ipairs @sceneData.children
					scene\setLayerRatio index,oVec2(layerData.ratioX,layerData.ratioY)
				camera.position = lastPos
			if @sceneData.camera.boundary
				camera.boundary = @sceneData.camera.area
			else
				camera.boundary = CCRect.zero
			pos = subCam.position
			camera\perform CCSpawn {
				oPos 0.5,pos.x,pos.y,oEase.OutQuad
				oScale 0.5,subCam.zoom,subCam.zoom,oEase.OutQuad
			}
			@schedule once -> cycle 0.5,->
				emit "Scene.ViewArea.Scale",camera.scaleX
		else
			camera.boundary = CCRect.zero
			if @sceneData.children
				lastPos = camera.position
				camera.position = oVec2.zero
				for index,layerData in ipairs @sceneData.children
					scene\setLayerRatio index,oVec2.zero
				camera.position = lastPos

	getBodyBoundingBox:(item)=>
		minX,minY,maxX,maxY = nil,nil,nil,nil
		item.data\each (_,child)->
			return unless tolua.type(child) == "oBody"
			rc = child.boundingBox
			minX = rc.left unless minX
			maxX = rc.right unless maxX
			minY = rc.bottom unless minY
			maxY = rc.top unless maxY
			minX = math.min minX,rc.left
			maxX = math.max maxX,rc.right
			minY = math.min minY,rc.bottom
			maxY = math.max maxY,rc.top
		minX or= 0
		minY or= 0
		maxX or= 0
		maxY or= 0
		CCRect minX,minY,maxX-minX,maxY-minY
