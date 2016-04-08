Dorothy!
MenuItemView = require "View.Control.AI.MenuItem"

-- [params]
-- x, y, width, height, expr
Class MenuItemView,
	__init:(args)=>
		@_checked = false
		@_text = ""
		@_expr = nil
		@_index = args.index
		@parentExpr = args.parentExpr

		@expr = args.expr
		@slot "Tapped",-> @checked = not @checked

	makeChecked:=>
		@_checked = true

	checked:property => @_checked,
		(value)=>
			return if value == @_checked
			@_checked = not @_checked
			@border.visible = not value
			if value then
				with @borderBold
					.visible = true
					.opacity = 1
					.scaleX = 0.8
					.scaleY = 0.8
					\perform @scale
			else
				@borderBold\runAction @fade

	text:property => @_text,
		(value)=>
			@_text = value
			@label.text = value
			start,stop = value\match "()%b[]()"
			if start
				@label.cascadeColor = false
				@label\colorText start,stop,ccColor3(0xff0080)

	expr:property => @_expr,
		(value)=>
			@_expr = value
			@updateText!

	index:property =>
		parentExpr = @parentExpr
		if parentExpr
			expr = @expr
			if parentExpr[@_index] ~= expr
				for i = 2,#parentExpr
					if parentExpr[i] == expr
						@_index = i
						break
		@_index

	updateText:=>
		value = @_expr
		switch value[1]
			when "AIRoot"
				@text = "[Sel] Root"
			when "Con"
				@text = "[Con] "..value[2][2]
			when "Act"
				@text = "[Act] "..value[2][2]
			else
				@text = "[#{ value[1] }]"

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
