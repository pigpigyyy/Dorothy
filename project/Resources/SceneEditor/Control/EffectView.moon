Dorothy!
Class,property = unpack require "class"
ItemViewView = require "View.Control.ItemView"
MessageBox = require "Control.MessageBox"
oBody = require "oBodyEx"
-- [signals]
-- "Selected",(viewItem)->
-- [params]
-- x, y, width, height, file
Class
	__partial: (args)=> ItemViewView args
	__init: (args)=>
		{:width,:height,:file} = args
		@isLoaded = true
		@file = file

		@\slots "Tapped",->
			@\emit "Selected",@

		@face\addChild with CCLabelTTF file,"Arial",16
			.position = oVec2 width/2,height/2
			.texture.antiAlias = false
			.color = ccColor3 0x00ffff
			\perform oOpacity 0.3,1
