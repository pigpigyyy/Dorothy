Dorothy!
Class,property = unpack require "class"
OperationPanelView = require "View.Control.Operation.OperationPanel"

Class
	__partial: (args)=> OperationPanelView args
	__init: (args)=>
		@opacity = 0.4
		@_menuEnabled = true

		fadeOut = CCSequence {
			CCDelay 1
			oOpacity 0.5,0.4,oEase.InExpo
		}

		@\slots "ScrollTouchBegan",->
			@\stopAction fadeOut
			@opacity = 1

		@\slots "ScrollEnd",->
			@perform fadeOut

		@\slots "ScrollStart",->
			@menu.enabled = false

		@\slots "ScrollTouchEnded",->
			if @_menuEnabled
				@menu.enabled = true

		contentRect = CCRect.zero
		itemRect = CCRect.zero
		@\slots "Scrolled",(delta)->
			contentRect\set 0,0,@width,@height
			@menu\eachChild (child)->
				child.position += delta
				{:positionX,:positionY,:width,:height} = child
				itemRect\set positionX-width/2,positionY-height/2,width,height
				if width ~= 0 and height ~= 0
					child.visible = contentRect\intersectsRect itemRect

	menuEnabled: property => @_menuEnabled,
		(value)=>
			@_menuEnabled = value
			@menu.enabled = value
