Dorothy!
SelectionPanel = require "Control.Basic.SelectionPanel"
PickPanelView = require "View.Control.Operation.PickPanel"

-- [params]
-- width, height
Class PickPanelView,
	__init:=>
		@itemType = nil
		@pickedItem = nil
		@gslot "Scene.Trigger.Picking",(args)->
			{itemType,currentItem} = args
			itemName = currentItem\match "^[^%.]*"
			item = editor.items[itemName]
			if item
				itemData = editor\getData item
				emit "Scene.ViewPanel.Pick",itemData if itemData
			@selectEvent.enabled = true
			@itemType = itemType
			@pickedItem = currentItem
			@visible = true
			@title.text = itemType
			@label.text = currentItem
			@showButton!
			with @panel
				.scaleX,.scaleY = 0,0
				\perform oScale 0.3,1,1,oEase.OutBack

		@selectEvent = @gslot "Scene.ViewPanel.Select",(itemData)->
			@pickedItem = nil
			@label.text = ""
			if itemData and @itemType
				switch @itemType
					when "Sensor"
						if itemData.itemType == "Body"
							bodyGroup = editor\getItem itemData
							sensors = {}
							bodyGroup.data\each (name,item)->
								if tolua.type(item) == "oBody" and item.sensor
									table.insert sensors,name
							if #sensors > 0
								with SelectionPanel {
										title:"Select Sensor"
										width:150
										items:sensors
										itemHeight:40
										fontSize:20
									}
									\slot "Selected",(item)->
										return unless item
										@pickedItem = itemData.name.."."..item
										@label.text = @pickedItem
										@showButton!
					when itemData.itemType
						@pickedItem = itemData.name
						@label.text = itemData.name
						@showButton!

		@selectEvent.enabled = false

		hide = ->
			if @visible and not @scheduled
				@selectEvent.enabled = false
				@panel\perform oScale 0.3,0,0,oEase.InBack
				@pickBtn\perform oScale 0.3,0,0,oEase.InBack
				@schedule once ->
					sleep 0.3
					@visible = false

		@pickBtn\slot "Tapped",->
			emit "Scene.Trigger.Picked",@pickedItem or ""
			emit "Scene.Trigger.Open"

		@gslot "Scene.Trigger.Open",hide

	showButton:=>
		with @pickBtn
			.scaleX,.scaleY = 0,0
			\perform oScale 0.3,1,1,oEase.OutBack
