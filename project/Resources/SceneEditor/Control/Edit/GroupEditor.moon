Dorothy!
Class = unpack require "class"
GroupEditorView = require "View.Control.Edit.GroupEditor"

Class
	__partial: => GroupEditorView!
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
		@closeBtn\slots "Tapped",->
