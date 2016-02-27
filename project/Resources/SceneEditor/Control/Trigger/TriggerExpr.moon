Dorothy!
TriggerExprView = require "View.Control.Trigger.TriggerExpr"

Class TriggerExprView,
	__init:(args)=>
		{:text,:indent,:expr,:parentExpr,:index,:lineNumber} = args
		@_checked = false
		@_indent = indent or 0
		@_text = ""
		@_index = index
		@_lineNumber = lineNumber
		@expr = expr
		@parentExpr = parentExpr
		@text = text or ""
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
				oVec2 0,1
				oVec2 @width,1
				oVec2 @width,@height-1
				oVec2 0,@height-1
				oVec2 0,1
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

	lineNumber:property => @_lineNumber,
		(value)=>
			if value ~= @_lineNumber
				@_lineNumber = value
				@numberLabel.text = value and tostring(value) or ""

	text:property => @_text,
		(value)=>
			value = string.rep("    ",@_indent)..value
			parentExpr = @parentExpr
			if parentExpr and parentExpr[1] == "Condition"
				if #parentExpr ~= @index
					value ..= " and"
			@_text = value
			@label.text = value
			@label.texture.antiAlias = false
			@height = @label.height+10
			posY = @height-5
			@label.positionY = posY
			@numberLabel.positionY = posY if @numberLabel

	updateText:=>
		@text = tostring @expr if @expr
