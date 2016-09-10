Dorothy!
TabButtonView = require "View.Control.Item.TabButton"

-- [signal]
-- "Checked",(checked,tabButton)->
-- "Expanded",(expanded)->
-- [params]
-- x, y, width, height, text, file
Class TabButtonView,
	__init: (args)=>
		@file = args.file
		@_expanded = args.expanded == true
		@emit "Expanded",true if @_expanded
		@_checked = false
		@_isCheckMode = false
		@slot "Tapped", ->
			if @_isCheckMode
				@_checked = not @_checked
				@emit "Checked",@_checked,@
			else
				@_expanded = not @_expanded
				@emit "Expanded",@_expanded

	expanded: property => @_expanded

	checked: property => @_checked

	isCheckMode: property => @_isCheckMode,
		(value)=>
			@_isCheckMode = value
			if not value and @_checked
				@_checked = false
				@emit "Checked",false,@
				@emit "TapEnded"
