Dorothy!
Class,property,classfield = unpack require "class"
EditorView = require "View.Scene.Editor"
SelectionPanel = require "Control.Basic.SelectionPanel"
Model = require "Data.Model"
Reference = require "Data.Reference"

Class
	__partial: => EditorView!
	__init: =>
		{:width,:height} = CCDirector.winSize
		@_gameName = ""
		@_gameFullPath = ""
		@_actionEditor = nil
		@_bodyEditor = nil
		@_effectEditor = nil
		@game = "Test"
		@initRoutine = nil
		@origin = oVec2 60+(width-250)/2,height/2

		_G["editor"] = @
		builtin["editor"] = @

		@slots "Cleanup",->
			Reference.stopUpdate!
			oRoutine\remove @initRoutine if @initRoutine
			_G["editor"] = nil
			builtin["editor"] = nil
			oCache\clear!
			CCScene\remove "actionEditor"
			CCScene\remove "bodyEditor"
			CCScene\remove "effectEditor"

		CCScene\transition "rollIn",{"zoomFlip",0.5,CCOrientation.Down}
		CCScene\transition "rollOut",{"zoomFlip",0.5,CCOrientation.Up}

		level = (level)-> CCMenu.DefaultHandlerPriority-level*10
		@levelViewArea = level 5
		@levelHRuler = level 6
		@levelVRuler = level 6
		@levelEditMenu = level 7
		@levelOperationPanel = level 7
		@levelItemPanel = level 8
		@levelClipEditor = level 9
		@levelMessageBox = level 10
		@levelInputBox = level 10
		@levelSelectionPanel = level 10

		@initRoutine = thread ->
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

			panelWidth = 10+110*4
			panelHeight = height*0.6
			setupPanel = (name)->
				realName = name\sub(1,1)\lower!..name\sub(2,-1)
				if not @[realName]
					Panel = require "Control.Item."..name
					panel = Panel {
						x:width/2
						y:height/2
						width:panelWidth
						height:panelHeight
					}
					panel.visible = false
					@[realName] = panel
					@addChild panel
			@gslot "Scene.ViewSprite",-> setupPanel "SpritePanel"
			@gslot "Scene.ViewModel",-> setupPanel "ModelPanel"
			@gslot "Scene.ViewBody",-> setupPanel "BodyPanel"
			@gslot "Scene.ViewEffect",-> setupPanel "EffectPanel"

			@gslot "Scene.ViewArea.Move",(delta)->
				return unless @items
				@items.Camera.position -= delta/@viewArea.scaleNode.scaleX
			@gslot "Scene.ViewArea.MoveTo",(pos)->
				return unless @items
				posX = pos.x-@origin.x+width/2
				posY = pos.y-@origin.y+height/2
				@items.Camera\perform oPos 0.5,posX,posY,oEase.OutQuad

			--bodyDef = Model.Body!
			--bodyDef.file = "Physics/car.body"
			worldDef = Model.World!--with Model.World!
			--	.children = {bodyDef}
			@sceneData = with Model.PlatformWorld!
				.camera = Model.Camera!
				.ui = Model.UILayer!
				.groups = {
					[1]: "P1"
					[oData.GroupDetect]: "Detect"
					[oData.GroupDetectPlayer]: "DetectPlayer"
					[oData.GroupHide]: "Hide"
					[oData.GroupTerrain]: "Terrain"
				}
				.contacts = {{1,1,true}}
				.children = {worldDef}
			@viewArea.scaleNode\addChild @sceneData!
			emit "Scene.DataLoaded",@sceneData

		@gslot "Editor.ItemChooser",(args)->
			handler = args[#args]
			table.remove args
			chooseItem = (itemType)->
				switch itemType
					when "Sprite"
						@spritePanel\slots "Selected",nil
						@spritePanel.parent\removeChild @spritePanel,false
						@spritePanel\slots("Hide")\set ->
							@spritePanel.parent\removeChild @spritePanel,false
							@addChild @spritePanel,1
						handler @spritePanel
					when "Model"
						@modelPanel\slots "Selected",nil
						@modelPanel.parent\removeChild @modelPanel,false
						@modelPanel\slots("Hide")\set ->
							@modelPanel.parent\removeChild @modelPanel,false
							@addChild @modelPanel,1
						handler @modelPanel
					else
						handler nil
			if #args == 1
				chooseItem args[1]
			else
				with SelectionPanel items:args
					\slots "Selected",(itemType)->
						chooseItem itemType

		refreshRef = Reference.refreshRef
		@gslot "Scene.ModelUpdated",refreshRef
		@gslot "Scene.BodyUpdated",refreshRef
		@gslot "Scene.EffectUpdated",refreshRef
		@gslot "Scene.ClipUpdated",refreshRef

		selectItem = (typeName,item)->
			@selectedType,@selectedItem = if item then typeName,item else nil,nil
		@gslot "Scene.SpriteSelected",(item)-> selectItem "Sprite",item
		@gslot "Scene.ModelSelected",(item)-> selectItem "Model",item
		@gslot "Scene.BodySelected",(item)-> selectItem "Body",item
		@gslot "Scene.EffectSelected",(item)-> selectItem "Effect",item

	updateSprites: =>
		emit "Scene.LoadSprite", @graphicFolder

	updateModels: =>
		emit "Scene.LoadModel", @graphicFolder

	updateBodies: =>
		emit "Scene.LoadBody", @physicsFolder

	updateEffects: =>
		emit "Scene.LoadEffect", @graphicFolder

	game: property => @_gameName,
		(name)=>
			oContent\removeSearchPath oContent.writablePath..@_gameName
			@_gameName = name
			@_gameFullPath = oContent.writablePath..name.."/"
			oContent\addSearchPath @_gameFullPath
			oContent\mkdir @_gameFullPath unless oContent\exist @_gameFullPath
			oContent\mkdir @graphicFullPath unless oContent\exist @graphicFullPath
			oContent\mkdir @physicsFullPath unless oContent\exist @physicsFullPath
			oContent\mkdir @logicFullPath unless oContent\exist @logicFullPath
			if @_actionEditor
				actionEditor.input = @gameFullPath
				actionEditor.output = @gameFullPath
			if @_bodyEditor
				bodyEditor.input = @gameFullPath
				bodyEditor.output = @gameFullPath
			Reference.update!

	gameFullPath: property => @_gameFullPath
	graphicFolder: property => "Graphic/"
	graphicFullPath: property => @_gameFullPath.."Graphic/"
	physicsFolder: property => "Physics/"
	physicsFullPath: property => @_gameFullPath.."Physics/"
	logicFolder: property => "Logic/"
	logicFullPath: property => @_gameFullPath.."Logic/"
	sceneFolder: property => "Scene/"
	sceneFullPath: property => @_gameFullPath.."Scene/"

	actionEditor: property =>
		if not @_actionEditor
			actionEditor = require "ActionEditor.Script.oEditor"
			actionEditor.standAlone = false
			actionEditor.quitable = true
			actionEditor.input = @gameFullPath
			actionEditor.output = @gameFullPath
			actionEditor.prefix = @graphicFolder
			actionEditor\slots "Edited",(model)->
				emit "Scene.ModelUpdated",model
			actionEditor\slots "Quit",->
				CCScene\back "rollIn"
				@updateModels!
			CCScene\add "actionEditor",actionEditor
			@_actionEditor = actionEditor
		return @_actionEditor

	bodyEditor: property =>
		if not @_bodyEditor
			bodyEditor = require "BodyEditor.Script.oEditor"
			bodyEditor.standAlone = false
			bodyEditor.quitable = true
			bodyEditor.input = @gameFullPath
			bodyEditor.output = @gameFullPath
			bodyEditor\slots "Edited",(body)->
				emit "Scene.BodyUpdated",body
			bodyEditor\slots "Quit",->
				CCScene\back "rollIn"
				@updateBodies!
			CCScene\add "bodyEditor",bodyEditor
			@_bodyEditor = bodyEditor
		return @_bodyEditor

	effectEditor: property =>
		if not @_effectEditor
			effectEditor = require "EffectEditor.Script.oEditor"
			effectEditor.standAlone = false
			effectEditor.quitable = true
			effectEditor.listFile = @graphicFolder.."list.effect"
			effectEditor.prefix = @graphicFolder
			effectEditor.input = @gameFullPath
			effectEditor.output = @gameFullPath
			effectEditor\slots "Edited",(effect)->
				emit "Scene.EffectUpdated",effect
			effectEditor\slots "Quit",->
				CCScene\back "rollIn"
				@updateEffects!
			CCScene\add "effectEditor",effectEditor
			@_effectEditor = effectEditor
		return @_effectEditor

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
