Dorothy!
Class,property = unpack require "class"
MessageBoxView = require "View.Control.MessageBox"
-- [signals]
-- "OK",(result)->
-- [params]
-- text
Class
	__partial: (args)=> MessageBoxView args
	__init: (args)=>
		@okBtn\slots "Tapped", ->
			@\clicked!
			@\emit "OK",true

		if not args.okOnly
			@cancelBtn\slots "Tapped", ->
				@\clicked!
				@\emit "OK",false

	clicked: =>
		@opMenu.enabled = false
		@\perform CCSequence {
			CCSpawn {
				oScale 0.3,0,0,oEase.InBack
				oOpacity 0.3,0
			}
			CCCall ->
				@parent\removeChild @
		}
