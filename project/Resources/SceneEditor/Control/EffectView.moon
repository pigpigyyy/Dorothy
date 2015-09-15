Dorothy!
Class,property = unpack require "class"
ItemViewView = require "View.Control.ItemView"
MessageBox = require "Control.MessageBox"
oStar = require "EffectEditor.Script.oStar"
-- [signals]
-- "Selected",(viewItem)->
-- [params]
-- x, y, width, height, file
Class
	__partial: (args)=> ItemViewView args
	__init: (args)=>
		{:width,:height,:file} = args
		@_checked = false
		@isLoaded = true
		@file = file
		@star = with oStar 12,0x66ff0088,0.5,0xffff0088
			.visible = false
			.position = oVec2 width-20,20
		@face\addChild @star

		@\slots "Tapped",->
			@\emit "Selected",@

		@face\addChild with CCLabelTTF file,"Arial",16
			.position = oVec2 width/2,height/2
			.texture.antiAlias = false
			.color = ccColor3 0x00ffff
			\perform oOpacity 0.3,1

	checked: property => @_checked,
		(value)=>
			@_checked = value
			if value
				@star.visible = true
				@star.scaleX = 0
				@star.scaleY = 0
				@star\perform oScale 0.3,1,1,oEase.OutBack
			else
				@star\perform CCSequence {
					oScale 0.3,0,0,oEase.InBack
					CCHide!
				}
