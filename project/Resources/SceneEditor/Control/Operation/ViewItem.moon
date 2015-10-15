Dorothy!
Class,property = unpack require "class"
ViewItemView = require "View.Control.Operation.ViewItem"

Class
	__partial: (args)=> ViewItemView args
	__init: (args)=>
		@_checked = false
		@\slots "Tapped",-> @checked = not @checked

	checked: property => @_checked,
		(value)=>
			return if value == @_checked
			@_checked = not @_checked
			@border.visible = not value
			if value then
				@color = ccColor3 0x00ffff
				@cascadeOpacity = false
				with @borderBold
					.visible = true
					.opacity = 1
					.scaleX = 0.8
					.scaleY = 0.8
					\perform @scale
			else
				@color = ccColor3 0xffffff
				@cascadeOpacity = true
				@borderBold\runAction @fade
