Dorothy!
Class,property = unpack require "class"
ViewItemView = require "View.Control.Operation.ViewItem"

Class
	__partial: (args)=> ViewItemView args
	__init: (args)=>
		@_checked = false
		@slots "Tapped",-> @checked = not @checked

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

	fold: property => @_fold,
		(value)=>
			@_fold = value
			if value
				@addChild with CCDrawNode!
					.tag = 1
					.position = oVec2 @width-7.5,@height-7.5
					\drawPolygon {
						oVec2 -2.5,-2.5
						oVec2 2.5,-2.5
						oVec2 2.5,2.5
						oVec2 -2.5,2.5
					},ccColor4(0x88ffffff),0.5,ccColor4!
			else
				@removeChildByTag 1
