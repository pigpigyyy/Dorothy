CCTextFieldTTF = require "CCTextFieldTTF"
oVec2 = require "oVec2"
oLine = require "oLine"
ccColor4 = require "ccColor4"
CCRepeatForever = require "CCRepeatForever"
CCSequence = require "CCSequence"
CCShow = require "CCShow"
CCDelay = require "CCDelay"
CCHide = require "CCHide"
ccColor3 = require "ccColor3"
Class = unpack require "class"

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
		@placeHolder = placeHolder or ""
		@colorPlaceHolder = ccColor3 0x00ffff

		cursor = with oLine {oVec2.zero,oVec2(0,fontSize)},ccColor4 0xff00ffff
			.visible = false
			.positionX = @width
		@addChild cursor

		blink = CCRepeatForever CCSequence {
			CCShow!
			CCDelay 0.5
			CCHide!
			CCDelay 0.5
		}

		@slots "InputAttach", ->
			with cursor
				.visible = true
				.positionX = @width
				\perform blink
			true

		@slots "InputDetach", ->
			with cursor
				.visible = false
				\stopAllActions!
				if @text ~= ""
					@emit "TextChanged",@
			true

		@slots "InputInserting",(addText)->
			string.len(@text) < limit or addText == "\n"

		inputed = ->
			with cursor
				.positionX = @width
				\perform blink
				@texture.antiAlias = false
		@slots "InputInserted",inputed
		@slots "InputDeleted",inputed
