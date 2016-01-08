CCRect = require "CCRect"
CCSequence = require "CCSequence"
CCSpawn = require "CCSpawn"
oScale = require "oScale"
oEase = require "oEase"
oOpacity = require "oOpacity"
CCCall = require "CCCall"
CCSize = require "CCSize"
CCDirector = require "CCDirector"
Class = unpack require "class"
SelectionPanelView = require "View.Control.Basic.SelectionPanel"
Button = require "Control.Basic.Button"

-- [signals]
-- "Selected",(item,index)->
-- [params]
-- width, height, items
Class
	__partial: (args)=>
		args.width = args.width or 120
		args.height = args.height or (10+#args.items*60+(args.title and 60 or 0))
		args.height = math.min CCDirector.winSize.height*0.6,args.height
		SelectionPanelView args

	__init: (args)=>
		{:width,:items} = args

		contentRect = CCRect.zero
		itemRect = CCRect.zero
		@scrollArea\slot "Scrolled",(delta)->
			contentRect\set 0,0,@scrollArea.width,@scrollArea.height
			@menu\eachChild (child)->
				child.position += delta
				{:positionX,:positionY,:width,:height} = child
				itemRect\set positionX-width/2,positionY-height/2,width,height
				child.visible = contentRect\intersectsRect itemRect -- reduce draw calls

		@scrollArea\slot "ScrollStart",->
			@menu.enabled = false

		@scrollArea\slot "ScrollTouchEnded",->
			@menu.enabled = true

		for i,item in ipairs items
			button = Button {
				text:item
				fontSize:16
				width:width-20
				height:50
			}
			button\slot "Tapped",->
				@scrollArea.touchEnabled = false
				@menu.enabled = false
				@emit "Selected",item,i
				@box\perform CCSequence {
					CCSpawn {
						oScale 0.3,0,0,oEase.InBack
						oOpacity 0.3,0
					}
					CCCall -> @parent\removeChild @
				}
			@menu\addChild button

		@scrollArea.viewSize = @menu\alignItemsVertically 10

		CCDirector.currentScene\addChild @,998
