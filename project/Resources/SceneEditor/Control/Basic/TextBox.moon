Class,property = unpack require "class"
TextBoxView = require "View.Control.Basic.TextBox"

-- [signals]
-- "Inputed",(text)->
-- [params]
-- x, y, width, height, fontSize, placeHolder = ""
Class TextBoxView,
	__init: =>
		@textField.opacity = 0.3
		@textField\slots "TextChanged",(text)-> @emit "TextChanged",text

	attachWithIME: => @textField\attachWithIME!
	detachWithIME: => @textField\detachWithIME!
	text: property => @textField.text
