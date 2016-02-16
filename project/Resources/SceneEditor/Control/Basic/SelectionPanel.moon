Dorothy!
SelectionPanelView = require "View.Control.Basic.SelectionPanel"
Button = require "Control.Basic.Button"

-- [signals]
-- "Selected",(item,index)->
-- [params]
-- items, title="", width=120, height=0.6*@H, itemHeight=50, fontSize=16
Class
	__partial: (args)=>
		args.width = args.width or 120
		args.height = args.height or (10+#args.items*60+(args.title and 60 or 0))
		args.height = math.min CCDirector.winSize.height*0.6,args.height
		SelectionPanelView args

	__init: (args)=>
		{:width,:items,:itemHeight,:fontSize} = args
		itemHeight or= 50
		fontSize or= 16

		for i,item in ipairs items
			button = Button {
				text:item
				fontSize:fontSize
				width:width-20
				height:itemHeight
			}
			button\slot "Tapped",->
				@emit "Selected",item,i
				@hide!
			@menu\addChild button

		@cancelBtn\slot "Tapped",-> @hide!

		@scrollArea.viewSize = @menu\alignItemsVertically 10
		@scrollArea\setupMenuScroll @menu

		CCDirector.currentScene\addChild @,998

	hide:=>
		@scrollArea.touchEnabled = false
		@menu.enabled = false
		@opMenu.enabled = false
		@cancelBtn\perform oScale 0.3,0,0,oEase.InBack
		@perform oOpacity 0.3,0
		@box\perform CCSequence {
			CCSpawn {
				oScale 0.3,0,0,oEase.InBack
				oOpacity 0.3,0
			}
			CCCall -> @parent\removeChild @
		}
