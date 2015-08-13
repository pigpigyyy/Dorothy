Class,property = unpack require "class"
EditorView = require "View.Scene.Editor"

Class
	__partial: => EditorView!
	__init: =>
		@currentGame = ""
