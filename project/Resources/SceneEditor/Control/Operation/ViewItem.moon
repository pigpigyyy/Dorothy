Dorothy!
Class,property = unpack require "class"
ViewItemView = require "View.Control.Operation.ViewItem"

-- [no signals]
-- [params]
-- width, height, items
VisibleChecker = Class ViewItemView,
	__init: (args)=>
		@_checked = false
		@slots "Tapped",-> @checked = not @checked

	checked: property => @_checked,
		(value)=>
			return if value == @_checked
			@_checked = not @_checked
			@border.visible = not value
			if value then
				@label.text = "H"
				@cascadeColor = false
				@borderBold.color = ccColor3 0xff0088
				@label.color = ccColor3 0xff0088
				@cascadeOpacity = false
				with @borderBold
					.visible = true
					.opacity = 1
					.scaleX = 0
					.scaleY = 0
					\perform @scale
			else
				@label.text = "V"
				@cascadeColor = true
				@borderBold.color = ccColor3 0xffffff
				@label.color = ccColor3 0xffffff
				@cascadeOpacity = true
				@borderBold\runAction @fade

-- [no signals]
-- [params]
-- x, y, width, height, text
Class ViewItemView,
	__init: (args)=>
		@_checked = false
		@_visibleChecker = nil
		@slots "Tapped",-> @checked = not @checked

	visibleChecker: property => @_visibleChecker ~= nil,
		(value)=>
			if value
				return if @_visibleChecker
				size = @height-10
				@_visibleChecker = VisibleChecker {
						text:"V"
						x:size/2+5
						y:@height/2
						width:size
						height:size
					}
				@addChild @_visibleChecker
				@label.positionX = @width-(@width-size-5)/2
			else
				return unless @_visibleChecker
				@removeChild @_visibleChecker
				@_visibleChecker = nil
				@label.positionX = @width/2

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
