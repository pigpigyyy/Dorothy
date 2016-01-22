Dorothy!
TriggerExprView = require "View.Control.Trigger.TriggerExpr"

Class TriggerExprView,
	__init:(args)=>
		{:text,:indent} = args
		@_checked = false
		@_indent = indent or 0
		@text = text
		@slot "Tapped",-> @checked = not @checked

	checked:property => @_checked,
		(value)=>
			@_checked = value
			if value
				@addChild with oLine {
							oVec2 -5,-5
							oVec2 @width+5,-5
							oVec2 @width+5,@height+5
							oVec2 -5,@height+5
							oVec2 -5,-5
						},ccColor4 0xff00ffff
					.tag = 1
			else
				@removeChildByTag 1

	indent:property => @_indent,
		(value)=>
			@_indent = value
			@text = @text\gsub "^%s*",""

	text:property => @label.text,
		(value)=>
			for i = 1,@_indent
				value = "    "..value
			@label.text = value
			@height = @label.height
			@label.positionY = @height
