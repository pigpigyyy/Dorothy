Dorothy!
Class,property = unpack require "class"
TabButtonView = require "View.Control.Item.TabButton"
-- [signal]
-- "Checked",(checked,tabButton)->
-- "Expanded",(expanded)->
-- [params]
-- x, y, width, height, text, file
Class
	__partial: (args)=> TabButtonView args
	__init: (args)=>
		@file = args.file
		@_expanded = false
		@_checked = false
		@_isCheckMode = false
		@\slots "Tapped", ->
			if @_isCheckMode
				@_checked = not @_checked
				@\emit "Checked",@_checked,@
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
				@\emit "Checked",false,@
				@\emit "TapEnded"
