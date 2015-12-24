Dorothy!
Class,property = unpack require "class"
OperationPanelView = require "View.Control.Operation.OperationPanel"

-- [no signals]
-- [params]
-- x, y, width, height
Class OperationPanelView,
	__init: (args)=>
		@_menuEnabled = true

		@slot "ScrollStart",->
			@menu.enabled = false

		@slot "ScrollTouchEnded",->
			if @_menuEnabled
				@menu.enabled = true

		contentRect = CCRect.zero
		itemRect = CCRect.zero
		@slot "Scrolled",(delta)->
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
