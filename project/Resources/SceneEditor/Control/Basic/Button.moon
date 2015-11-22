Class,property = unpack require "class"
ButtonView = require "View.Control.Basic.Button"

-- [signals]
-- "Tapped",(button)->
-- [params]
-- x, y, width, height, fontSize, text
Class
	__partial: (args)=> ButtonView args
	__init: (args)=>
		@_text = args.text
		@label.texture.antiAlias = false if @label

	text: property => @_text,
		(value)=>
			@_text = value
			if @label
				@label.text = value
				@label.texture.antiAlias = false
