Dorothy!
Class,property = unpack require "class"
CircleButtonView = require "View.Control.CircleButton"

Class
	__partial: (args)=> CircleButtonView args
	__init: (args)=>
		@_text = args.text
		@label.texture.antiAlias = false
	text: property => @_text,
		(value)=>
			@_text = value
			if @label
				@label.text = value
				@label.texture.antiAlias = false
