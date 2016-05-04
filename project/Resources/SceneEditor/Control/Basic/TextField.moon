Dorothy!

-- [signals]
-- "TextChanged",(textField)->
-- [params]
-- x, y, limit, fontSize
Class
	__partial: (args)=>
		CCTextFieldTTF "","Arial",args.fontSize

	__init: (args)=>
		{:x,:y,:fontSize,:limit,:placeHolder} = args
		@anchor = oVec2 0.5,0
		@position = oVec2 x,y
		@_placeHolder = placeHolder or ""
		@placeHolder = @_placeHolder
		@colorPlaceHolder = ccColor3 0x00ffff

		@cursor = with oLine {oVec2.zero,oVec2(0,fontSize)},ccColor4 0xff00ffff
			.visible = false
			.positionX = @width
		@addChild @cursor

		blink = CCRepeatForever CCSequence {
			CCShow!
			CCDelay 0.5
			CCHide!
			CCDelay 0.5
		}

		@slot "InputAttach", ->
			@placeHolder = ""
			with @cursor
				.visible = true
				.positionX = @width
				\perform blink
			true

		@slot "InputDetach", ->
			@placeHolder = @_placeHolder
			with @cursor
				.visible = false
				\stopAllActions!
				if @text ~= ""
					@emit "TextChanged",@
			true

		@slot "InputInserting",(addText)->
			string.len(@text) < limit or addText == "\n"

		inputed = ->
			with @cursor
				.positionX = @width
				\perform blink
				@texture.antiAlias = false
		@slot "InputInserted",inputed
		@slot "InputDeleted",inputed
