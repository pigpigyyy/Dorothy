Dorothy!
CharacterSettingView = require "View.Control.Unit.CharacterSetting"
ActionChooser = require "Control.AI.ActionChooser"
import Struct from require "Lib.Utils"
MessageBox = require "Control.Basic.MessageBox"

Class CharacterSettingView,
	__init:=>
		@actionPanel.itemSource = Struct.Array!

		@actionPanel\slot "SizeChanged",->
			@updateSize!
			@emit "SizeChanged",@

		@actionPanel\slot "AddToList",(items)->
			with ActionChooser!
				\slot "Selected",(file)->
					return unless file
					if items\contains file
						MessageBox text:"Action Exist!",okOnly:true
					else
						items\insert file
