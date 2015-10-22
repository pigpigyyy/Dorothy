CCDirector = require "CCDirector"
oOpacity = require "oOpacity"
CCSequence = require "CCSequence"
CCSpawn = require "CCSpawn"
oScale = require "oScale"
oEase = require "oEase"
CCCall = require "CCCall"
Class = unpack require "class"
InputBoxView = require "View.Control.Basic.InputBox"

-- [signals]
-- "Inputed",(text)->
-- [params]
-- text
Class
	__partial: (args)=> InputBoxView args
	__init: =>
		@textField\attachWithIME!
		@textField\slots "TextChanged", ->
			if @textField.text ~= ""
				@\inputed @textField.text

		@okBtn\slots "Tapped", ->
			@\inputed @textField.text

		@cancelBtn\slots "Tapped", ->
			@\inputed nil

		CCDirector.currentScene\addChild @,998

	inputed: (text)=>
		@activateArea.enabled = false
		@opMenu.enabled = false
		@\perform oOpacity 0.4,0
		@box\perform CCSequence {
			CCSpawn {
				oScale 0.4,0,0,oEase.InBack
				oOpacity 0.4,0
			}
			CCCall ->
				@\emit "Inputed",text
				@parent\removeChild @
		}
