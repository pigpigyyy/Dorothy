Dorothy!
Class,property,classfield = unpack require "class"
EditorView = require "View.Scene.Editor"

Class
	__partial: => EditorView!
	__init: =>
		@_gameName = ""
		@_grahicPath = ""
		@_physicsPath = ""
		@_logicPath = ""
		@game = "Test"
		emit "Editor.LoadSprite", {
			@graphicPath
		}
		_G["editor"] = @
		builtin["editor"] = @

	game: property => @_gameName,
		(name)=>
			@_gameName = name
			root = oContent.writablePath..name
			@_grahicPath = root.."/Graphic/"
			@_physicsPath = root.."/Physics/"
			@_logicPath = root.."/Logic/"
			oContent\mkdir root unless oContent\exist root
			oContent\mkdir @_grahicPath unless oContent\exist @_grahicPath
			oContent\mkdir @_physicsPath unless oContent\exist @_physicsPath
			oContent\mkdir @_logicPath unless oContent\exist @_logicPath

	graphicPath: property => @_grahicPath
	physicsPath: property => @_physicsPath
	logicPath: property => @_logicPath
