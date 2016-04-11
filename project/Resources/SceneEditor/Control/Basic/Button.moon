Dorothy!
ButtonView = require "View.Control.Basic.Button"

-- [signals]
-- "Tapped",(button)->
-- [params]
-- x, y, width, height, fontSize, text
Class ButtonView,
	__init:(args)=>
		@_text = @label.text if @label
		@label.texture.antiAlias = false if @label

	text:property => @_text,
		(value)=>
			@_text = value
			if @label
				@label.text = value
				@label.texture.antiAlias = false
