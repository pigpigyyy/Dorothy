Dorothy!
TriggerExprView = require "View.Control.Trigger.TriggerExpr"

Class TriggerExprView,
	__init:(args)=>
		{:text,:indent,:expr,:parentExpr,:index} = args
		@_checked = false
		@_indent = indent or 0
		@_text = ""
		@text = text or ""
		@expr = expr
		@parentExpr = parentExpr
		@index = index
		@slot "TapBegan",@tapBegan
		@slot "Tapped",->
			@checked = not @checked if @expr
		@slot "TapEnded",@tapEnded

	tapBegan:=>
		if not @checked
			with @addLazyLine!
				.opacity = 0.5

	tapEnded:=>
		if not @checked
			with @addLazyLine!
				\perform CCSequence {
					oOpacity 0.2,0
					CCHide!
				}

	addLazyLine:=>
		line = @getChildByTag 1
		if not line
			line = oLine {
				oVec2 -5,-4
				oVec2 @width+5,-4
				oVec2 @width+5,@height+4
				oVec2 -5,@height+4
				oVec2 -5,-4
			},ccColor4 @expr and 0xff00ffff or 0xff0080
			@addChild line,0,1
		line.visible = true
		line

	checked:property => @_checked,
		(value)=>
			@_checked = value
			with @addLazyLine!
				if value
					\perform oOpacity 0.2,1
				else
					\perform CCSequence {
						oOpacity 0.2,0
						CCHide!
					}

	indent:property => @_indent,
		(value)=>
			@_indent = value
			@text = @text\gsub "^%s*",""

	text:property => @_text,
		(value)=>
			@_text = value
			for i = 1,@_indent
				value = "    "..value
			@label.text = value
			@height = @label.height
			@label.positionY = @height
