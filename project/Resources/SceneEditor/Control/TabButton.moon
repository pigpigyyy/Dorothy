Dorothy!
Class,property = unpack require "class"
TabButtonView = require "View.Control.TabButton"

Class
	__partial: (args)=> TabButtonView args
	__init: (args)=>
		@isClipTab = args.isClipTab
		@_expanded = false
		@_checked = false
		@_isCheckMode = false
		@\slots "Tapped", ->
			if @_isCheckMode
				@_checked = not @_checked
				@\emit "Checked",@_checked
			else
				@_expanded = not @_expanded
				@\emit "Expanded",@_expanded

	expanded: property => @_expanded

	checked: property => @_checked

	isCheckMode: property => @_isCheckMode,
		(value)=>
			@_isCheckMode = value
			if not value and @_checked
				@_checked = false
				@\emit "Checked",false
				@\emit "TapEnded"
