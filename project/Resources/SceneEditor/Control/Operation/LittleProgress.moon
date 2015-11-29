Class,property = unpack require "class"
LittleProgressView = require "View.Control.Operation.LittleProgress"

-- [no signals]
-- [params]
-- x, y
Class LittleProgressView,
	play: =>
		@bar.scaleY = 0
		@bar\perform @scale

	done: property => @scale.done
