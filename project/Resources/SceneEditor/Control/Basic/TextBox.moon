Class,property = unpack require "class"
TextBoxView = require "View.Control.Basic.TextBox"

-- [signals]
-- "Inputed",(text)->
-- [params]
-- x, y, width, height, fontSize
-- placeHolder = "", fadeOpacity = 0.3
-- hideFrame = false
Class
	__partial: (args)=> TextBoxView args
	__init: (args)=>
		@textField.opacity = args.fadeOpacity or 0.3

	attachWithIME: => @textField\attachWithIME!
	detachWithIME: => @textField\detachWithIME!
	text: property => @textField.text
