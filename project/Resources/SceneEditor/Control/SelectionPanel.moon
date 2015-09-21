Dorothy!
Class,property = unpack require "class"
SelectionPanelView = require "View.Control.SelectionPanel"
Button = require "Control.Button"

Class
	__partial: (args)=>
		args.width = args.width or 120
		args.height = args.height or (10+#args.items*60+(args.title and 60 or 0))
		SelectionPanelView args

	__init: (args)=>
		{:width,:items} = args

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

		@scrollArea\slots "ScrollEnd",->
			@menu.enabled = true

		for item in *items
			button = Button {
				text:item
				fontSize:16
				width:width-20
				height:50
			}
			button\slots "Tapped",->
				@box\perform CCSequence {
					CCSpawn {
						oScale 0.3,0,0,oEase.InBack
						oOpacity 0.3,0
					}
					CCCall ->
						@\emit "Selected",item
						@parent\removeChild @
				}
			@menu\addChild button

		viewHeight = @menu\alignItemsVertically 10
		@scrollArea.viewSize = CCSize width,viewHeight

		CCDirector.currentScene\addChild @,998
