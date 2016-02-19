Dorothy!
TextBoxView = require "View.Control.Basic.TextBox"

-- [signals]
-- "Inputed",(text)->
-- [params]
-- x, y, width, height, fontSize, placeHolder = ""
Class TextBoxView,
	__init:=>
		@textField.opacity = 0.6
		@textField\slot "TextChanged",-> @emit "Inputed",@text

	attachWithIME:=> @textField\attachWithIME!
	detachWithIME:=> @textField\detachWithIME!
	text:property => @textField.text,
		(value)=>
			@textField.text = value
			@textField.texture.antiAlias = false if @textField.texture
	placeHolder:property => @textField.placeHolder,
		(value)=> @textField.placeHolder = value
