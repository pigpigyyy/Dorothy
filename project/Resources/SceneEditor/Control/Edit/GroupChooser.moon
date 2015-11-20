Dorothy!
Class = unpack require "class"
GroupChooserView = require "View.Control.Edit.GroupChooser"

Class
	__partial: => GroupChooserView!
	__init: =>
		contentRect = CCRect.zero
		itemRect = CCRect.zero
		@scrollArea\slots "Scrolled",(delta)->
			contentRect\set 0,0,@scrollArea.width,@scrollArea.height
			@menu\eachChild (child)->
				child.position += delta
				{:positionX,:positionY,:width,:height} = child
				itemRect\set positionX-width/2,positionY-height/2,width,height
				child.visible = contentRect\intersectsRect itemRect -- reduce draw calls
		@scrollArea\slots "ScrollStart",->
			@menu.enabled = false
		@scrollArea\slots "ScrollTouchEnded",->
			@menu.enabled = true
		@closeBtn\slots "Tapped",-> @hide!
		@show!

		Model = require "Data.Model"
		sceneData = Model.PlatformWorld!
		for i = 1,12
			item = @["p#{i}"]
			item.text = sceneData.groups[i]

		for i = 1,#@menu.children
			child = tolua.cast @menu.children[i],"CCMenuItem"
			if child
				child\slots "Tapped",(button)->
					print button.text

	show: =>
		@perform CCSequence {
			CCShow!
			oOpacity 0.3,0.6,oEase.OutQuad
		}
		@closeBtn.scaleX = 0
		@closeBtn.scaleY = 0
		@closeBtn\perform oScale 0.3,1,1,oEase.OutBack
		@panel.opacity = 0
		@panel.scaleX = 0
		@panel.scaleY = 0
		@panel\perform CCSequence {
			CCSpawn {
				oOpacity 0.3,1,oEase.OutQuad
				oScale 0.3,1,1,oEase.OutBack
			}
			CCCall ->
				@scrollArea.touchEnabled = true
				@menu.enabled = true
				@opMenu.enabled = true
		}

	hide: =>
		@scrollArea.touchEnabled = false
		@menu.enabled = false
		@opMenu.enabled = false
		@closeBtn\perform oScale 0.3,0,0,oEase.InBack
		@panel\perform CCSpawn {
			oOpacity 0.3,0,oEase.OutQuad
			oScale 0.3,0,0,oEase.InBack
		}
		@perform CCSequence {
			oOpacity 0.3,0,oEase.OutQuad
			CCCall -> @parent\removeChild @
		}
