CCDrawNode = require "CCDrawNode"
ccColor4 = require "ccColor4"
oVec2 = require "oVec2"
CCLabelTTF = require "CCLabelTTF"
ccColor3 = require "ccColor3"
oOpacity = require "oOpacity"
oScale = require "oScale"
oEase = require "oEase"
CCSequence = require "CCSequence"
CCHide = require "CCHide"
Class,property = unpack require "class"
ItemViewView = require "View.Control.Item.ItemView"
oStar = require "EffectEditor.Script.oStar"

-- [signals]
-- "Selected",(viewItem)->
-- [params]
-- x, y, width, height, file
Class ItemViewView,
	__init: (args)=>
		{:width,:height,:file,:effect} = args
		@_checked = false
		@isLoaded = true
		@file = file
		@effect = effect
		@star = with CCDrawNode!
			\drawPolygon oStar(12),ccColor4(0x66ff0088),0.5,ccColor4(0xffff0088)
			.visible = false
			.position = oVec2 width-20,20
		@face\addChild @star

		@slot "Tapped",-> @emit "Selected",@

		label = with CCLabelTTF effect,"Arial",16
			.position = oVec2 width/2,height/2
			.texture.antiAlias = false
			.color = ccColor3 0x00ffff
			\perform oOpacity 0.3,1
		@face\addChild label

		if file\sub(-3,-1)\lower! == "par"
			@face\addChild with CCDrawNode!
				\drawPolygon oStar(10,oVec2 label.positionX-label.width/2-10-2,label.positionY-label.height/2+8),ccColor4(0x6600ffff),0.5,ccColor4(0xff00ffff)
				\drawPolygon oStar(10,oVec2 label.positionX-label.width/2-10-6,label.positionY-label.height/2+8),ccColor4(0xbb00ffff),0.5,ccColor4(0xff00ffff)
				\drawPolygon oStar(10,oVec2 label.positionX-label.width/2-10-10,label.positionY-label.height/2+8),ccColor4(0xff00ffff),0.5,ccColor4(0xff00ffff)
		else
			@face\addChild with CCDrawNode!
				.position = oVec2 label.positionX-label.width/2-5-5,label.positionY-label.height/2-2
				\drawPolygon {
					oVec2 0,0
					oVec2 0,20
					oVec2 5,20
					oVec2 5,0
				}, ccColor4(0x4400ffff),0.5,ccColor4(0xff00ffff)
				\drawPolygon {
					oVec2 0-7,0
					oVec2 0-7,20
					oVec2 5-7,20
					oVec2 5-7,0
				}, ccColor4(0x9900ffff),0.5,ccColor4(0xff00ffff)
				\drawPolygon {
					oVec2 0-14,0
					oVec2 0-14,20
					oVec2 5-14,20
					oVec2 5-14,0
				}, ccColor4(0xff00ffff),0.5,ccColor4(0xff00ffff)

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
