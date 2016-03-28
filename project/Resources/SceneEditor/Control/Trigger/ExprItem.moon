Dorothy!
ExprItemView = require "View.Control.Trigger.ExprItem"
TriggerDef = require "Data.TriggerDef"
SolidRect = require "View.Shape.SolidRect"
import Set from require "Data.Utils"

keywords = Set {"and", "break", "do", "else", "elseif", "end", "false", "for", "function",
"if", "in", "local", "nil", "not", "or", "repeat", "return", "then", "true",
"until", "while"}

textColor = ccColor3 255,255,255
keywordColor = ccColor3 58,135,212
classColor = ccColor3 62,197,127
noteColor = ccColor3 56,142,73
errorColor = ccColor3 255,0,128

LineTag = 1
ErrorTag = 2

Class ExprItemView,
	__init:(args)=>
		{:text,:indent,:expr,:parentExpr,:index,:lineNumber} = args
		@_checked = false
		@_indent = indent or 0
		@_text = ""
		@_index = index
		@_lineNumber = lineNumber
		@errorInfo = nil
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
		line = @getChildByTag LineTag
		if not line
			line = oLine {
				oVec2 0,1
				oVec2 @width,1
				oVec2 @width,@height-1
				oVec2 0,@height-1
				oVec2 0,1
			},ccColor4 @expr and 0xff00ffff or 0xff0080
			@addChild line,0,LineTag
		line.visible = true
		line

	updateLine:=>
		line = @getChildByTag LineTag
		if line
			line\set {
				oVec2 0,1
				oVec2 @width,1
				oVec2 @width,@height-1
				oVec2 0,@height-1
				oVec2 0,1
			}

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
			if parentExpr
				switch parentExpr[1]
					when "Condition","Available","ConditionNode"
						if #parentExpr ~= @index
							value ..= " and"
			@_text = value
			@label.text = value
			@label.texture.antiAlias = false
			@height = @label.height+16
			posY = @height-8
			@label.positionY = posY
			@numberLabel.positionY = posY if @numberLabel
			label = @label
			label\colorText 1,#value,textColor
			if TriggerDef.CodeMode
				if value\match "^%s*%-%-%s"
					label\colorText 1,#value,noteColor
				else
					-- color keywords text
					for start,word,stop in value\gmatch "()([%w_]+)()"
						if keywords[word]
							label\colorText start,stop-1,keywordColor
						elseif word == "InvalidName" or word == "g_InvalidName"
							label\colorText start,stop-1,errorColor
					-- color comment text
					index = value\find "%-%-%s"
					label\colorText index,#value,noteColor if index
					start,stop = value\find "%-%-%[%[[^%]]*%]%]%s"
					label\colorText start,stop,noteColor if start
					-- color string text
					value = value\gsub "\\.","xx"
					for start,word,stop in value\gmatch "()(%b\"\")()"
						if word == "\"InvalidName\""
							label\colorText start,stop-1,errorColor
						else
							label\colorText start,stop-1,classColor
			else
				if value\match "^%s*Note"
					label\colorText 1,#value,noteColor
				else
					-- color start of expression text
					for start,word,stop in value\gmatch "()([%w_]*)()"
						if word == "InvalidName" or word == "g_InvalidName"
							label\colorText start,stop-1,errorColor
						elseif word\sub(1,1)\match "%u"
							label\colorText start,stop-1,keywordColor
							value = value\gsub "\\.","xx"
					-- color comment text
					index = value\find "note %b()"
					label\colorText index,#value,noteColor if index
					-- color string text
					for start,word,stop in value\gmatch "()(%b\"\")()"
						if word == "\"InvalidName\""
							label\colorText start,stop-1,errorColor
						else
							label\colorText start,stop-1,classColor

	updateText:=>
		@text = tostring @expr if @expr
		@updateLine!

	markError:(isError,info)=>
		@errorInfo = info
		if isError
			if not @getChildByTag ErrorTag
				@addChild with SolidRect {
						width:30
						height:@height-10
						color:0x66ff0080
					}
					.position = oVec2 5,5
					.tag = ErrorTag
					.zOrder = -1
		else
			@removeChildByTag ErrorTag
