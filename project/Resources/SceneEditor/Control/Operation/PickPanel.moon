Dorothy!
SelectionPanel = require "Control.Basic.SelectionPanel"
PickPanelView = require "View.Control.Operation.PickPanel"
PointControl = require "Control.Edit.PointControl"
import Round from require "Lib.Utils"

-- [params]
-- width, height
Class PickPanelView,
	__init:=>
		@editorType = nil
		@itemType = nil
		@pickedItem = nil
		@pointControl = nil

		itemString = ->
			if tolua.type(@pickedItem) == "oVec2"
				string.format "%d,%d",@pickedItem.x,@pickedItem.y
			else
				tostring @pickedItem

		pickFunction = (editorType)->
			(args)->
				{itemType,currentItem} = args
				if itemType == "Point"
					@pointControl = with PointControl!
						\show currentItem,if editor.currentData
								editor\getItem editor.currentData
							else
								nil
						\slot "PosChanged",(pos)->
							@pickedItem = Round pos
							@label.text = itemString!
					@parent\addChild @pointControl,-1
				else
					itemName = currentItem\match "^[^%.]*"
					item = editor.items[itemName]
					itemData = item and editor\getData(item) or nil
					emit "Scene.ViewPanel.Pick",itemData
				@selectEvent.enabled = true
				@editorType = editorType
				@itemType = itemType
				@pickedItem = currentItem
				@visible = true
				@title.text = itemType
				@label.text = itemString!
				@showButton!
				with @panel
					.scaleX,.scaleY = 0,0
					\perform oScale 0.3,1,1,oEase.OutBack

		@gslot "Scene.Trigger.Picking",pickFunction "Trigger"
		@gslot "Scene.Action.Picking",pickFunction "Action"
		@gslot "Scene.AINode.Picking",pickFunction "AINode"

		@selectEvent = @gslot "Scene.ViewPanel.Select",(itemData)->
			if @itemType ~= "Point"
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
										@label.text = itemString!
										@showButton!
					when "BodySlice"
						if itemData.itemType == "Body"
							bodyGroup = editor\getItem itemData
							slices = {}
							bodyGroup.data\each (name,item)->
								if tolua.type(item) == "oBody" and not item.sensor
									table.insert slices,name
							if #slices > 0
								with SelectionPanel {
										title:"Select Slice"
										width:150
										items:slices
										itemHeight:40
										fontSize:20
									}
									\slot "Selected",(item)->
										return unless item
										@pickedItem = itemData.name.."."..item
										@label.text = itemString!
										@showButton!
					when "Point"
						isBody = itemData.itemType == "Body"
						offset = isBody and itemData.position or oVec2.zero
						with @pointControl
							\show @pickedItem,editor\getItem(itemData),offset
							if isBody
								\schedule ->
									.offset = itemData.position
									.targetPos = @pickedItem+.offset
									.circle.position = .targetPos
							else
								\unschedule!
					when itemData.itemType
						@pickedItem = itemData.name
						@label.text = itemString!
						@showButton!

		@selectEvent.enabled = false

		@pickBtn\slot "Tapped",->
			emit "Scene.#{ @editorType }.Picked",@pickedItem
			emit "Scene.#{ @editorType }.Open"
			if @visible and not @scheduled
				if @pointControl
					@pointControl.parent\removeChild @pointControl
					@pointControl = nil
				@selectEvent.enabled = false
				@panel\perform oScale 0.3,0,0,oEase.InBack
				@pickBtn\perform oScale 0.3,0,0,oEase.InBack
				@schedule once ->
					sleep 0.3
					@visible = false

	showButton:=>
		with @pickBtn
			.scaleX,.scaleY = 0,0
			\perform oScale 0.3,1,1,oEase.OutBack
