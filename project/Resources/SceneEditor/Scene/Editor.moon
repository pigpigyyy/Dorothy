Dorothy!
CCScene = require "CCSceneEx"
Class,property,classfield = unpack require "class"
EditorView = require "View.Scene.Editor"

Class
	__partial: => EditorView!
	__init: =>
		@_gameName = ""
		@_gameFullPath = ""
		@_actionEditor = nil
		@game = "Test"

		_G["editor"] = @
		builtin["editor"] = @

		@\slots "Cleanup",->
			_G["editor"] = nil
			builtin["editor"] = nil
			oCache\clear!
			CCScene\remove "actionEditor"

		CCScene\add "sceneEditor",@
		CCScene\add "actionEditor",@actionEditor
		CCScene\transition "rollIn",{"zoomFlip",0.5,CCOrientation.Down}
		CCScene\transition "rollOut",{"zoomFlip",0.5,CCOrientation.Up}

		thread ->
			width = 10+110*4
			height = @height-20
			sleep!
			SpritePanel = require "Control.SpritePanel"
			sleep!
			@spritePanel = SpritePanel {
				x:-10-width/2
				y:10+height/2
				width:width
				height:height
			}
			@\addChild @spritePanel,1
			sleep!
			ModelPanel = require "Control.ModelPanel"
			sleep!
			@modelPanel = ModelPanel {
				x:-10-width/2
				y:10+height/2
				width:width
				height:height
			}
			@\addChild @modelPanel,1
			sleep!
			BodyPanel = require "Control.BodyPanel"
			sleep!
			@bodyPanel = BodyPanel {
				x:-10-width/2
				y:10+height/2
				width:width
				height:height
			}
			@\addChild @bodyPanel,1
			sleep!
			EditMenu = require "Control.EditMenu"
			sleep!
			@editMenu = EditMenu!
			@\addChild @editMenu

	updateSprites: =>
		emit "Scene.LoadSprite", { @graphicFolder }
		visitGraphicFolder = (path)->
			folders = oContent\getEntries path,true
			for folder in *folders
				if folder ~= "." and folder ~= ".."
					visitGraphicFolder path.."/"..folder
			files = oContent\getEntries path,false
			if #files == 0 and #folders == 2
				oContent\remove path
		visitGraphicFolder @graphicFullPath\gsub("[\\/]*$","")

	updateModels: =>
		emit "Scene.LoadModel", { @graphicFolder }

	updateBodies: =>
		emit "Scene.LoadBody", { @physicsFolder }

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

	gameFullPath: property => @_gameFullPath
	graphicFolder: property => "Graphic/"
	graphicFullPath: property => @_gameFullPath.."Graphic/"
	physicsFolder: property => "Physics/"
	physicsFullPath: property => @_gameFullPath.."Physics/"
	logicFolder: property => "Logic/"
	logicFullPath: property => @_gameFullPath.."Logic/"

	actionEditor: property =>
		if not @_actionEditor
			actionEditor = require("ActionEditor.Script.oEditor")
			actionEditor.standAlone = false
			actionEditor.quitable = true
			actionEditor.input = @gameFullPath
			actionEditor.output = @gameFullPath
			actionEditor\slots "Edited",(model)->
				emit "Scene.ModelUpdated",model
			actionEditor\slots "Quit",->
				CCScene\run "sceneEditor","rollIn"
				@\updateModels!
			@_actionEditor = actionEditor
		return @_actionEditor
