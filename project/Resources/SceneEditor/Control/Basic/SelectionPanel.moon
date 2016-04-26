Dorothy!
SelectionPanelView = require "View.Control.Basic.SelectionPanel"
Button = require "Control.Basic.Button"
SelectionItem = require "Control.Basic.SelectionItem"

-- [signals]
-- "Selected",(item,index)->
-- [params]
-- items, title="", width=120, height=0.6*@H, itemHeight=50, fontSize=16, grouped=false, default=nil
Class
	__partial: (args)=>
		args.width or= 120
		args.itemHeight or= 40
		args.fontSize or= 16
		args.height = args.height or (20+#args.items*(args.itemHeight+10)+(args.title and 70 or 0)+(args.subTitle and 30 or 0))
		args.height = math.min CCDirector.winSize.height*0.6,args.height
		SelectionPanelView args

	__init: (args)=>
		{:width,:items,:itemHeight,:fontSize,:grouped} = args

		if grouped
			default = args.default
			@selectedItem = nil
			selected = (button)->
				@selectedItem.checked = false if @selectedItem and @selectedItem ~= button
				button.checked = true unless button.checked
				@selectedItem = button
			for i,item in ipairs items
				selectionItem = with SelectionItem {
						text:item
						fontSize:fontSize
						width:width-20
						height:itemHeight
					}
					.index = i
					\slot "Tapped",selected
				@menu\addChild selectionItem
				if default == item
					@selectedItem = selectionItem
					@selectedItem\makeChecked!
		else
			for i,item in ipairs items
				@menu\addChild with Button {
						text:item
						fontSize:fontSize
						width:width-20
						height:itemHeight
					}
					\slot "Tapped",->
						@emit "Selected",item,i
						@hide!

		if grouped
			@cancelBtn.text = "OK"
			@cancelBtn\slot "Tapped",->
				if @selectedItem
					@emit "Selected",@selectedItem.text,@selectedItem.index
				else
					@emit "Selected",nil,nil
				@hide!
		else
			@cancelBtn\slot "Tapped",->
				@emit "Selected",nil,nil
				@hide!

		@scrollArea.viewSize = @menu\alignItemsVertically 10
		@scrollArea\setupMenuScroll @menu
		if @selectedItem
			@scrollArea\scrollToPosY @selectedItem.positionY

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
