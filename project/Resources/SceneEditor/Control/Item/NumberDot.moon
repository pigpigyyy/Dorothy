Dorothy!
NumberDotView = require "View.Control.Item.NumberDot"

-- [params]
-- x, y, number
Class NumberDotView,
	__init: (args)=>
		@_number = args.number
		@label.texture.antiAlias = false

	number: property => @_number,
		(value)=>
			@_number = value
			@label.text = tostring value
			@label.texture.antiAlias = false
