Dorothy!

rx = require "rx"

CCNode.event = (name)=>
	subject = rx.Subject.create!
	@\slots name,(...)->
		subject ...
		true
	subject

layer = CCLayer!
layer.touchEnabled = true
layer.touchPriority = CCMenu.DefaultHandlerPriority-998
layer.keypadEnabled = true

touchBeganEvent = layer\event "TouchBegan"
touchMovedEvent = layer\event "TouchMoved"
touchEndedEvent = layer\event "TouchEnded"

touchBeganEvent\map(()-> touchMovedEvent\takeUntil touchEndedEvent)\flatten()\map((touch)-> print touch.location.x,touch.location.y)\subscribe!

CCDirector.currentScene\addChild layer