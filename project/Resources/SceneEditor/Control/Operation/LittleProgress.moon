Class,property = unpack require "class"
LittleProgressView = require "View.Control.Operation.LittleProgress"

Class
	__partial: (args)=>
		LittleProgressView args

	play: =>
		@bar.scaleY = 0
		@bar\perform @scale

	done: property => @scale.done
