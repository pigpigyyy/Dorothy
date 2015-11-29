Class,property = unpack require "class"
CircleButtonView = require "View.Control.Basic.CircleButton"

-- [signals]
-- "Tapped",(button)->
-- [params]
-- x, y, radius, fontSize, text
Class CircleButtonView,
	__init: (args)=>
		@_text = args.text
		@label.texture.antiAlias = false

	text: property => @_text,
		(value)=>
			@_text = value
			if @label
				@label.text = value
				@label.texture.antiAlias = false
