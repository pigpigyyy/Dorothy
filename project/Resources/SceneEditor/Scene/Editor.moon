Dorothy!
Class,property,classfield = unpack require "class"
EditorView = require "View.Scene.Editor"

Class
	__partial: => EditorView!
	__init: =>
		@_gameName = ""
		@_gamePath = ""
		@_graphicFolders = {}
		@game = "Test"
		_G["editor"] = @
		builtin["editor"] = @
		@updateSprites!

	updateSprites: =>
		emit "Editor.LoadSprite", {
			@graphicFolder
		}
		for folder in *@_graphicFolders
			oContent\removeSearchPath folder

		@_graphicFolders = {}
		visitGraphicFolder = (path)->
			table.insert @_graphicFolders, path
			oContent\addSearchPath path
			folders = oContent\getEntries path,true
			for folder in *folders
				if folder ~= "." and folder ~= ".."
					visitGraphicFolder path.."/"..folder
		visitGraphicFolder @graphicFullPath\gsub("[\\/]*$","")

		visitGraphicFolder = (path)->
			folders = oContent\getEntries path,true
			for folder in *folders
				if folder ~= "." and folder ~= ".."
					visitGraphicFolder path.."/"..folder
			files = oContent\getEntries path,false
			if #files == 0 and #folders == 2
				oContent\remove path
		visitGraphicFolder @graphicFullPath\gsub("[\\/]*$","")

	game: property => @_gameName,
		(name)=>
			oContent\removeSearchPath oContent.writablePath..@_gameName
			@_gameName = name
			@_gamePath = oContent.writablePath..name.."/"
			oContent\addSearchPath @_gamePath
			oContent\mkdir @_gamePath unless oContent\exist @_gamePath
			oContent\mkdir @graphicFullPath unless oContent\exist @graphicFullPath
			oContent\mkdir @physicsFullPath unless oContent\exist @physicsFullPath
			oContent\mkdir @logicFullPath unless oContent\exist @logicFullPath

	gamePath: property => @_gamePath
	graphicFolder: property => "Graphic/"
	graphicFullPath: property => @_gamePath.."Graphic/"
	physicsFolder: property => "Physics/"
	physicsFullPath: property => @_gamePath.."Physics/"
	logicFolder: property => "Logic/"
	logicFullPath: property => @_gamePath.."Logic/"
