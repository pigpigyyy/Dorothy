Dorothy!
TriggerItemView = require "View.Control.Trigger.TriggerItem"

-- [params]
-- x, y, width, height, text
Class TriggerItemView,
	__init:(args)=>
		@_checked = false
		@_text = @label.text
		@slot "Tapped",-> @checked = not @checked

	makeChecked:=>
		@_checked = true
		@border.visible = false
		@opacity = 1
		with @borderBold
			.visible = true
			.opacity = 1
			.scaleX = 1
			.scaleY = 1

	checked:property => @_checked,
		(value)=>
			return if value == @_checked
			@_checked = not @_checked
			@border.visible = not value
			if value then
				@opacity = 1
				with @borderBold
					.visible = true
					.opacity = 1
					.scaleX = 0.8
					.scaleY = 0.8
					\perform @scale
			else
				@opacity = 0.6
				@borderBold\runAction @fade

	text:property => @_text,
		(value)=>
			@_text = value
			@label.text = value

	glow:=>
		@cascadeOpacity = false
		{:width,:height} = @
		tile = with CCDrawNode()
			.position = oVec2 width/2,height/2
			.zOrder = -1
			.opacity = 0
			\drawPolygon {
					oVec2 -width/2,height/2
					oVec2 width/2,height/2
					oVec2 width/2,-height/2
					oVec2 -width/2,-height/2
				},ccColor4(0x8800ffff),0.5,ccColor4(0xffffffff)
			\runAction CCSequence {
				CCRepeat (CCSequence {
						oOpacity 0.1,1
						oOpacity 0.1,0
					}),2
				CCCall ->
					.parent\removeChild tile
					@cascadeOpacity = true
			}
		@addChild tile
