Dorothy!
EditorView = require "View.Scene.Editor"
SelectionPanel = require "Control.Basic.SelectionPanel"
Model = require "Data.Model"
Reference = require "Data.Reference"
CCScene = require "Lib.CCSceneEx"
require "Lib.oBodyEx"

Class EditorView,
	__init:=>
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
		@selectedType = nil
		@selectedItem = nil
		@origin = oVec2 width/2,height/2
		@offset = oVec2 60+(width-300)/2,height/2
		@scale = 1
		@xFix = false
		@yFix = false
		@isFixed = true
		@camPos = oVec2 width/2,height/2

		-- do some hack and I know what I`m doing.
		rawset _G,"editor",@
		rawset builtin,"editor",@
		@slot "Cleanup",->
			@game = nil
			Reference.stopUpdate!
			_G.editor = nil
			builtin.editor = nil
			oCache\clear!
			CCScene\remove "actionEditor"
			CCScene\remove "bodyEditor"
			CCScene\remove "effectEditor"

		CCScene\transition "rollIn",{"zoomFlip",0.5,CCOrientation.Down}
		CCScene\transition "rollOut",{"zoomFlip",0.5,CCOrientation.Up}
		CCScene\transition "crossFade",{"crossFade",0.5}

		level = (level)-> CCMenu.DefaultHandlerPriority-level*10
		@levelViewArea = level 5
		@levelEditControl = level 6
		@levelHRuler = level 7
		@levelVRuler = level 7
		@levelEditMenu = level 8
		@levelOperationPanel = level 8
		@levelItemPanel = level 9
		@levelClipEditor = level 10
		@levelTriggerEditor = level 11
		@levelExprEditor = level 11
		@levelExprChooser = level 12
		@levelMessageBox = level 13
		@levelInputBox = level 14
		@levelSelectionPanel = level 15

		@schedule once ->
			@game = "DemoGame"
			TriggerEditor = require "Control.Trigger.TriggerEditor"
			@addChild with TriggerEditor!
				\show!
			return if true
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
			resPath = "SceneEditor/Demo/DemoGame"
			writePath = @gamesFullPath.."DemoGame"
			Manager = require "Control.Edit.Manager"
			@editManager = Manager!
			@viewArea\addChild @editManager
			sleep!
			@moveTo oVec2.zero
			if not oContent\exist(writePath) and oContent\exist(resPath)
				oContent\copyAsync resPath,writePath
			ScenePanel = require "Control.Item.ScenePanel"
			ScenePanel!
			sleep!
			TriggerEditor = require "Control.Trigger.TriggerEditor"
			@addChild TriggerEditor!

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
			hideEditor = (cam ~= nil)
			hideAllControl = false
			emit "Scene.HideEditor",{hideEditor,hideAllControl}
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
				@camPos = pos

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

		effectUpdated = (args)->
			{effect,effectFile,delete} = args
			if effectFile
				if delete
					Reference.removeRef effectFile
				else
					Reference.refreshRef effectFile
			@eachSceneItem (itemData)->
				if itemData.typeName == "Effect" and effect == itemData.effect
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

	updateSprites:=> emit "Scene.LoadSprite",@graphicFolder
	updateModels:=> emit "Scene.LoadModel",@graphicFolder
	updateBodies:=> emit "Scene.LoadBody",@physicsFolder
	updateEffects:=> emit "Scene.LoadEffect",@graphicFolder

	game:property => @_gameName,
		(name)=>
			oContent\removeSearchPath @_gameFullPath if @_gameFullPath
			oCache\clear!
			oAI\clear!
			oAction\clear!
			collectgarbage!
			@_gameName = name
			if name
				@_gameFullPath = @gamesFullPath..name.."/"
				oContent\addSearchPath @_gameFullPath
				oContent\mkdir @_gameFullPath unless oContent\exist @_gameFullPath
				oContent\mkdir @graphicFullPath unless oContent\exist @graphicFullPath
				oContent\mkdir @physicsFullPath unless oContent\exist @physicsFullPath
				oContent\mkdir @logicFullPath unless oContent\exist @logicFullPath
				oContent\mkdir @sceneFullPath unless oContent\exist @sceneFullPath
				oContent\mkdir @triggerFullPath unless oContent\exist @triggerFullPath
				oContent\mkdir @triggerLocalFullPath unless oContent\exist @triggerLocalFullPath
				oContent\mkdir @triggerGlobalFullPath unless oContent\exist @triggerGlobalFullPath
				if @_actionEditor
					@actionEditor.input = @gameFullPath
					@actionEditor.output = @gameFullPath
				if @_bodyEditor
					@bodyEditor.input = @gameFullPath
					@bodyEditor.output = @gameFullPath
				effectFile = @physicsFullPath.."list.effect"
				oCache.Effect\load effectFile if oContent\exist effectFile
			else
				@_gameFullPath = nil
			@currentSceneFile = nil
			Reference.update!

	eachSceneItem:(handler)=>
		if @sceneData
			if @sceneData.ui and @sceneData.ui.children
				for child in *@sceneData.ui.children
					handler child
			if @sceneData.children
				for layer in *@sceneData.children
					if layer.children
						for child in *layer.children
							handler child

	gamesFullPath:property => oContent.writablePath.."Game/"
	gameFullPath:property => @_gameFullPath
	graphicFolder:property => "Graphic/"
	graphicFullPath:property => @_gameFullPath.."Graphic/"
	physicsFolder:property => "Physics/"
	physicsFullPath:property => @_gameFullPath.."Physics/"
	logicFolder:property => "Logic/"
	logicFullPath:property => @_gameFullPath.."Logic/"
	triggerFolder:property => "Logic/Trigger/"
	triggerFullPath:property => @_gameFullPath.."Logic/Trigger/"
	triggerLocalFolder:property => "Logic/Trigger/Local/"
	triggerLocalFullPath:property => @_gameFullPath.."Logic/Trigger/Local/"
	triggerGlobalFolder:property => "Logic/Trigger/Global/"
	triggerGlobalFullPath:property => @_gameFullPath.."Logic/Trigger/Global/"
	sceneFolder:property => "Scene/"
	sceneFullPath:property => @_gameFullPath.."Scene/"
	uiFileFullPath:property => @sceneFullPath.."UI.scene"

	actionEditor:property =>
		if not @_actionEditor
			actionEditor = with require "ActionEditor.Script.oEditor"
				.standAlone = false
				.quitable = true
				.input = @gameFullPath
				.output = @gameFullPath
				.prefix = @graphicFolder
				.setupEvent = ->
					(\slot "Edited")\set (model)->
						emit "Scene.ModelUpdated",model
					(\slot "Quit")\set -> @updateModels!
					(\slot "Activated")\clear!
			CCScene\add "actionEditor",actionEditor
			@_actionEditor = actionEditor
		@_actionEditor

	bodyEditor:property =>
		if not @_bodyEditor
			bodyEditor = with require "BodyEditor.Script.oEditor"
				.standAlone = false
				.quitable = true
				.input = @gameFullPath
				.output = @gameFullPath
				.setupEvent = ->
					(\slot "Edited")\set (body)->
						emit "Scene.BodyUpdated",body
					(\slot "Quit")\set -> @updateBodies!
					(\slot "Activated")\clear!
			CCScene\add "bodyEditor",bodyEditor
			@_bodyEditor = bodyEditor
		@_bodyEditor

	effectEditor:property =>
		if not @_effectEditor
			effectEditor = with require "EffectEditor.Script.oEditor"
				.standAlone = false
				.quitable = true
				.listFile = @graphicFolder.."list.effect"
				.prefix = @graphicFolder
				.input = @gameFullPath
				.output = @gameFullPath
				.setupEvent = ->
					(\slot "Edited")\set (effect,effectFile,delete)->
						emit "Scene.EffectUpdated",{effect,effectFile,delete}
					(\slot "Quit")\set -> @updateEffects!
					(\slot "Activated")\clear!
			CCScene\add "effectEditor",effectEditor
			@_effectEditor = effectEditor
		@_effectEditor

	getUsableName:(originalName)=>
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

	renameData:(itemData,name)=>
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

	getItem:(itemData)=>
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

	getData:(item)=> @itemDefs[item]

	getSceneName:(itemData)=>
		item = @getItem itemData
		parentData = @getData item.parent
		if parentData.typeName == "UILayer"
			"UI.scene"
		else
			@scene..".scene"

	insertData:(parentData,newData,targetData,afterTarget=true)=>
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
			parent = @getItem parentData
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

	removeData:(itemData,parentData)=>
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

	resetData:(itemData)=>
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

	moveDataDown:(itemData,parentData)=>
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

	moveDataTop:(itemData,parentData)=>
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

	moveDataBottom:(itemData,parentData)=>
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
			parent = @getItem parentData
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

	save:=>
		return unless @sceneData
		ui = @sceneData.ui
		@sceneData.ui = false
		Model.dumpData @sceneData,@gameFullPath..@currentSceneFile
		Model.dumpData ui,@uiFileFullPath
		@sceneData.ui = ui

	scene:property => @_sceneName,
		(value)=>
			@currentSceneFile = if value
				@sceneFolder..value..".scene"
			else
				nil

	currentSceneFile:property => @_currentSceneFile,
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

	newScene:(sceneName)=>
		sceneFile = @sceneFolder..sceneName..".scene"
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

	deleteCurrentScene:=>
		return unless @currentSceneFile
		oContent\remove @currentSceneFile
		Reference.removeSceneRef @currentSceneFile,@sceneData
		@currentSceneFile = nil

	deleteCurrentGame:=>
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

	updateGroupName:(groupIndex,name)=>
		@sceneData.groups[groupIndex] = name
		emit "Scene.Dirty",true

	updateContact:(groupA,groupB,shouldContact)=>
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

	pickItem:(originPos)=>
		return unless @items
		pos = @items.Scene\getLayer(-1)\convertToNodeSpace originPos
		bodies = {}
		addBody = (body)->
			return true unless body.parent.visible
			bodyData = @getData body.parent
			bodies[bodyData] = true
			true
		@items.Scene\query CCRect(pos.x-0.5,pos.y-0.5,1,1),addBody

		if @sceneData.children
			for layerData in *@sceneData.children
				if layerData.typeName == "World"
					world = @getItem layerData
					pos = world\convertToNodeSpace originPos
					world\query CCRect(pos.x-0.5,pos.y-0.5,1,1),addBody

		uiLayer = @sceneData.ui
		if uiLayer and uiLayer.visible and uiLayer.display
			children = uiLayer.children
			if children
				pos = @items.UI\convertToNodeSpace originPos
				for j = #children,1,-1
					itemData = children[j]
					switch itemData.typeName
						when "Effect"
							return itemData if CCRect(itemData.position-oVec2(50,50),CCSize(100,100))\containsPoint pos
						else
							item = @getItem itemData
							return itemData if item.visible and item.boundingBox\containsPoint pos

		if @sceneData.children
			for i = #@sceneData.children,1,-1
				layerData = @sceneData.children[i]
				if layerData.display and layerData.visible and layerData.children
					layer = @getItem layerData
					pos = layer\convertToNodeSpace originPos
					for j = #layerData.children,1,-1
						itemData = layerData.children[j]
						switch itemData.typeName
							when "Body"
								if bodies[itemData]
									return itemData
							when "Effect"
								return itemData if CCRect(itemData.position-oVec2(50,50),CCSize(100,100))\containsPoint pos
							else
								item = @getItem itemData
								return itemData if item.visible and item.boundingBox\containsPoint pos
		nil

	getSubEditor:(typeName)=>
		switch typeName
			when "Model"
				@actionEditor,"actionEditor"
			when "Body"
				@bodyEditor,"bodyEditor"
			when "Effect"
				@effectEditor,"effectEditor"
			else
				nil,nil

	edit:(typeName,file,transitionIn="",transitionOut="")=>
		subEditor,subEditorName = @getSubEditor typeName
		if subEditor and subEditorName
			with subEditor
				\setupEvent!
				\slot "Activated",-> \edit file
				\slot "Quit",-> CCScene\back transitionOut
			CCScene\forward subEditorName,transitionIn
		subEditor

	editCurrentItemInPlace:=>
		itemData = @currentData
		if itemData
			file = if itemData.typeName == "Effect"
				itemData.effect
			else
				itemData.file
			emit "Scene.HideEditor",{true,true}
			thread ->
				if @scale ~= 1
					emit "Scene.ViewArea.ScaleReset"
					sleep 0.6
				emit "Scene.ViewPanel.Pick",itemData
				subEditor = @getSubEditor itemData.typeName
				scene = @viewArea.scene
				if itemData.typeName == "Body"
					@viewArea.sceneNode\perform oRotate 0.5,-itemData.angle,oEase.OutQuad
					scene.UILayer.transformTarget = @viewArea
				-- wait for editor to be loaded
				if not subEditor.isLoaded
					subEditor.visible = false
					@addChild subEditor
					sleep 0.6 -- wait for Scene.ViewPanel.Pick to end
					wait -> not subEditor.isLoaded
					sleep!
					@removeChild subEditor,false
					subEditor.visible = true
				else
					sleep 0.6 -- wait for Scene.ViewPanel.Pick to end
				-- save some editor data
				item = @getItem itemData
				parentData = @getData item.parent
				lastCamPos = @camPos
				lastCamZoom = @scale
				layerZoom = parentData.zoom or 1
				layerOffset = parentData.offset or oVec2.zero
				display = itemData.display
				-- edit selected item
				subEditor = @edit itemData.typeName,file
				-- make edit in place
				if parentData.typeName == "UILayer"
					scene.UILayer.transformTarget = subEditor.viewArea.viewNode
					scene.UILayer.position = oVec2.zero-itemData.position
					if @sceneData.children
						for layerData in *@sceneData.children
							layer = @getItem layerData
							layer.visible = false
				else
					scene.UILayer.transformTarget = subEditor.viewArea
				subEditor\hideEditor true,true
				itemData.display,item.visible = false,false
				scene.parent\removeChild scene,false
				subEditor.viewArea.viewNode\addChild scene,-1
				{:width,:height} = CCDirector.winSize
				scene.scaleX = 1/layerZoom
				scene.scaleY = 1/layerZoom
				with scene.camera
					.position = if parentData.typeName == "UILayer"
						oVec2.zero
					else
						oVec2(width/2,height/2)+itemData.position+layerOffset
					.scaleX = 1
					.scaleY = 1
				switch itemData.typeName
					when "Model"
						with subEditor.viewArea.itemNode
							.angle = item.angle
							.scaleX = item.scaleX
							.scaleY = item.scaleY
							.skewX = item.skewX
							.skewY = item.skewY
							.opacity = item.opacity
					when "Body"
						subEditor.viewArea.viewNode.angle = -itemData.angle
				sleep!
				sleep!
				subEditor\hideEditor false,false
				-- setup rollback function which is called when sub editer ends
				-- for in place edit
				subEditor\slot "Quit",->
					if parentData.typeName == "UILayer"
						if @sceneData.children
							for layerData in *@sceneData.children
								layer = @getItem layerData
								layer.visible = true
					emit "Scene.HideEditor",{false,true}
					itemData.display = display
					item = @getItem itemData
					item.visible = itemData.display and itemData.visible
					scene.parent\removeChild scene,false
					@viewArea.sceneNode\addChild scene
					scene.scaleX = 1
					scene.scaleY = 1
					scene.UILayer.transformTarget = nil
					{:width,:height} = CCDirector.winSize
					scene.UILayer.position = oVec2(-width/2,-height/2)
					with scene.camera
						.position = lastCamPos
						.scaleX = lastCamZoom
						.scaleY = lastCamZoom
					switch itemData.typeName
						when "Model"
							with subEditor.viewArea.itemNode
								.angle = 0
								.scaleX = 1
								.scaleY = 1
								.skewX = 0
								.skewY = 0
								.opacity = 1
						when "Body"
							scene.UILayer.transformTarget = @viewArea
							@viewArea.sceneNode\perform CCSequence {
								oRotate 0.5,0,oEase.OutQuad
								CCCall -> scene.UILayer.transformTarget = nil
							}
							subEditor.viewArea.viewNode.angle = 0
