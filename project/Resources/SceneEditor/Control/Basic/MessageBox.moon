Dorothy!
Class,property = unpack require "class"
MessageBoxView = require "View.Control.Basic.MessageBox"
-- [signals]
-- "OK",(result)->
-- [params]
-- text, okOnly
Class
	__partial: (args)=> MessageBoxView args
	__init: (args)=>
		@okBtn\slots "Tapped", ->
			@\clicked true

		if not args.okOnly
			@cancelBtn\slots "Tapped", ->
				@\clicked false

		CCDirector.currentScene\addChild @,998

	clicked: (result)=>
		@opMenu.enabled = false
		@\perform oOpacity 0.4,0
		@box\perform CCSequence {
			CCSpawn {
				oScale 0.4,0,0,oEase.InBack
				oOpacity 0.4,0
			}
			CCCall ->
				@\emit "OK",result
				@parent\removeChild @
		}
