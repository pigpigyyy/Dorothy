Dorothy!
Class,property = unpack require "class"
TabButtonView = require "View.Control.TabButton"

Class
	__partial: (args)=> TabButtonView args
	__init: (args)=>
		@_checked = false
		@\slots "Tapped", ->
			@_checked = not @_checked
			@\emit "Checked",@_checked

	checked: property => @_checked
