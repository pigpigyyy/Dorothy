Dorothy!
Class,property = unpack require "class"
InputBoxView = require "View.Control.InputBox"
-- [signals]
-- "Inputed",(text)->
-- [params]
-- text
Class
	__partial: (args)=> InputBoxView args
	__init: (args)=>
		@textField\attachWithIME!
		@textField\slots "TextChanged", ->
			if @textField.text ~= ""
				@\inputed @textField.text

		@okBtn\slots "Tapped", ->
			@\inputed @textField.text

		@cancelBtn\slots "Tapped", ->
			@\inputed ""

	inputed: (text)=>
		@activateArea.enabled = false
		@opMenu.enabled = false
		@\perform CCSequence {
			CCSpawn {
				oScale 0.3,0,0,oEase.InBack
				oOpacity 0.3,0
			}
			CCCall ->
				@parent\removeChild @
		}
		@\emit "Inputed",text
