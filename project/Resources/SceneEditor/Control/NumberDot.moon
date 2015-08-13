Dorothy!
Class,property = unpack require "class"
NumberDotView = require "View.Control.NumberDot"

Class
	__partial: (args)=> NumberDotView args
	__init: (args)=>
		@_number = args.number
		@label.texture.antiAlias = false

	number: property => @_number,
		(value)=>
			@_number = value
			@label.text = tostring value
			@label.texture.antiAlias = false
