Dorothy!
Class,property,classfield = unpack require "class"
EditorView = require "View.Scene.Editor"

Class
	__partial: => EditorView!
	__init: =>
		@_gameName = ""

		@game = "Test"
		emit "Editor.LoadSprite", {
			@graphicPath
		}
		_G["editor"] = @
		builtin["editor"] = @

	game: property => @_gameName,
		(name)=>
			oContent\removeSearchPath oContent.writablePath..@_gameName
			@_gameName = name
			root = oContent.writablePath..name
			oContent\addSearchPath root
			oContent\mkdir root unless oContent\exist root
			oContent\mkdir root..@graphicPath unless oContent\exist root..@graphicPath
			oContent\mkdir root..@physicsPath unless oContent\exist root..@physicsPath
			oContent\mkdir root..@logicPath unless oContent\exist root..@logicPath

	graphicPath: "Graphic/"
	physicsPath: "Physics/"
	logicPath: "Logic/"
