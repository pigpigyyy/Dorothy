oVec2 = require "oVec2"
CCDirector = require "CCDirector"
oOpacity = require "oOpacity"
CCSequence = require "CCSequence"
CCSpawn = require "CCSpawn"
oScale = require "oScale"
oEase = require "oEase"
CCCall = require "CCCall"
Class = unpack require "class"
MessageBoxView = require "View.Control.Basic.MessageBox"

-- [signals]
-- "OK",(result)->
-- [params]
-- text, okOnly
Class MessageBoxView,
	__init: (args)=>
		@okBtn\slots "Tapped", ->
			@clicked true

		if not args.okOnly
			@cancelBtn\slots "Tapped", ->
				@clicked false

		@scrollArea\slots "Scrolled",(delta)->
			@scrollArea.view\eachChild (child)->
				child.position += delta

		if @title.height > 90 or @title.width > 240
			@scrollArea.viewSize = @title.contentSize
			xPos = math.max @title.width/2,120
			@title.position = oVec2 xPos,90-@title.height/2
			@scrollArea.offset = oVec2 120-xPos,0

		CCDirector.currentScene\addChild @,998

	clicked: (result)=>
		@opMenu.enabled = false
		@perform oOpacity 0.4,0
		@box\perform CCSequence {
			CCSpawn {
				oScale 0.4,0,0,oEase.InBack
				oOpacity 0.4,0
			}
			CCCall ->
				@emit "OK",result
				@parent\removeChild @
		}
