Dorothy!
Class,property = unpack require "class"
OperationPanelView = require "View.Control.Operation.OperationPanel"

Class
	__partial: (args)=> OperationPanelView args
	__init: (args)=>
		@opacity = 0.4

		fadeOut = CCSequence {
			CCDelay 1
			oOpacity 0.5,0.4,oEase.InExpo
		}

		@\slots "ScrollTouchBegan",->
			@\stopAction fadeOut
			@opacity = 1

		@\slots "ScrollEnd",->
			@perform fadeOut

		contentRect = CCRect.zero
		itemRect = CCRect.zero
		@\slots "Scrolled",(delta)->
			contentRect\set 0,0,@width,@height
			@menu\eachChild (child)->
				child.position += delta
				{:positionX,:positionY,:width,:height} = child
				itemRect\set positionX-width/2,positionY-height/2,width,height
				child.visible = contentRect\intersectsRect itemRect
