Dorothy!
Class,property = unpack require "class"
SettingPanelView = require "View.Control.Operation.SettingPanel"
SettingItem = require "BodyEditor.Script.oSettingItem"

Class
	__partial: (args)=> SettingPanelView args
	__init: (args)=>
		itemWidth = @width
		itemHeight = 30
		itemNames = {
			{"Name","%s"}
			{"Outline","%s"}
			{"RatioX","%.2f"}
			{"RatioY","%.2f"}
			{"Look","%s"}
			{"Offset","%d"}
			{"Effect","%s"}
			{"Simulation","%s"}
			{"Play","%s"}
			{"Zoom","%.2f"}
			{"Scale","%.2f"}
			{"Angle","%d"}
			{"Position","%d"}
			{"Skew","%d"}
			{"File","%s"}
			{"Speed","%.2f"}
			{"Loop","%s"}
			{"Visible","%s"}
			{"Animation","%s"}
			{"FaceRight","%s"}
			{"Group","%s"}
			{"Groups","%s"}
			{"Contacts","%s"}
			{"Target","%s"}
			{"Gravity","%.2f"}
			{"Opacity","%.2f"}
		}

		genPosY = ->
			index = 0
			()->
				v = index
				index += 1
				@height-30-itemHeight/2-itemHeight*v

		items = {}
		getPosY = genPosY()
		editCallback = (settingItem)->
			emit "Scene.settingPanel.edit",settingItem

		for i = 1,#itemNames
			itemName = itemNames[i][1]
			valueFormat = itemNames[i][2]
			item = SettingItem itemName.." :",itemWidth,itemHeight,-itemWidth,getPosY(),(i == 1),valueFormat,editCallback
			item.anchor = oVec2 0.5,0.5
			item.name = itemName\sub(1,1)\lower!..itemName\sub(2,-1)
			items[itemName] = item

		for _,item in pairs items
			item.visible = true
			@menu\addChild item

		groups = {
			PlatformWorld: {
				items.Gravity
				items.Groups
				items.Contacts
				items.Simulation
				items.Outline
			}
			UILayer: {
				items.Visible
			}
			Camera: {
				items.Position
				items.Target
				items.RatioX
				items.RatioY
				items.Zoom
			}
			Layer: {
				items.Name
				items.RatioX
				items.RatioY
				items.Offset
				items.Zoom
				items.Visible
			}
			World: {
				items.Name
				items.Gravity
				items.Simulation
				items.Outline
				items.RatioX
				items.RatioY
				items.Offset
				items.Zoom
				items.Visible
			}
			Body: {
				items.Name
				items.File
				items.Group
				items.Position
				items.Angle
				items.Visible
			}
			Model: {
				items.Name
				items.File
				items.Position
				items.Angle
				items.Scale
				items.Skew
				items.Opacity
				items.Look
				items.Animation
				items.Loop
				items.Speed
				items.FaceRight
				items.Visible
			}
			Sprite: {
				items.Name
				items.File
				items.Position
				items.Angle
				items.Scale
				items.Skew
				items.Opacity
				items.Visible
			}
			Effect: {
				items.Name
				items.Effect
				items.Position
				items.Play
			}
		}

		currentGroup = nil
		@gslot "Scene.ViewPanel.Select",(data)->
			if currentGroup
				for item in *currentGroup
					item.positionX = -itemWidth
					item.visible = false
			if data
				@offset = oVec2.zero
				with @title
					.visible = true
					.text = data.typeName
					.texture.antiAlias = false
			else
				@title.text = "Dorothy Editor"
				@title.texture.antiAlias = false
				return

			currentGroup = groups[data.typeName]
			getPosY = genPosY!
			contentHeight = 40
			for item in *currentGroup
				item.visible = true
				item.positionX = itemWidth/2
				item.positionY = getPosY!
				contentHeight = contentHeight + itemHeight
				item.value = switch item.name
					when "file"
						data[item.name]\match "[^\\/]*$"
					when "simulation"
						switch data[item.name]
							when 1
								"Low"
							when 2
								"Medium"
							when 3
								"High"
					when "contacts","groups"
						". . ."
					when "group"
						editor.sceneData.groups[data[item.name]]
					when "outline"
						data[item.name] and "Show" or "Hide"
					else
						data[item.name] == "" and "None" or data[item.name]

			@viewSize = CCSize @width,contentHeight
