Dorothy!
InputBoxView = require "View.Control.Basic.InputBox"

-- [signals]
-- "Inputed",(text)->
-- [params]
-- text
Class InputBoxView,
	__init:=>
		@textBox\attachWithIME!
		@textBox\slot "Inputed",(text) ->
			@inputed text unless text == ""

		@okBtn\slot "Tapped", ->
			@inputed @textBox.text

		@cancelBtn\slot "Tapped", ->
			@inputed nil

		CCDirector.currentScene\addChild @,editor.topMost

	inputed:(text)=>
		@activateArea.enabled = false
		@opMenu.enabled = false
		@perform oOpacity 0.6,0
		@box\perform CCSequence {
			CCSpawn {
				oScale 0.4,0,0,oEase.InBack
				oOpacity 0.6,0
			}
			CCCall ->
				@emit "Inputed",text
				@parent\removeChild @
		}
