Dorothy!
Class,property = unpack require "class"
SettingPanelView = require "View.Control.Operation.SettingPanel"
SettingItem = require "BodyEditor.Script.oSettingItem"

Class
	__partial: (args)=> SettingPanelView args
	__init: (args)=>
		itemNames = {
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
			{"Animation","%s"}
			{"FaceRight","%s"}
			{"Contact","%s"}
			{"Index","%d"}
			{"Target","%s"}
			{"Gravity","%.2f"}
			{"Name","%s"}
			{"Opacity","%.2f"}
		}

		genPosY = ->
			index = 0
			()->
				v = index
				index += 1
				@height-30-itemHeight*v

		items = {}
		getPosY = genPosY()
		editCallback = (settingItem)->
			emit "Scene.settingPanel.edit",settingItem

		for i = 1,#itemNames
			itemName = itemNames[i][1]
			valueFormat = itemNames[i][2]
			items[itemName] = SettingItem itemName.." :",itemWidth,itemHeight,-itemWidth,getPosY(),i == 1,valueFormat,editCallback
			items[itemName].name = itemName

		for _,item in pairs items
			item.visible = false
			@menu\addChild item

		groups = {
			PlatformWorld: {
				items.Name
				items.Gravity
				items.Contact
				items.Simulation
				items.Outline
			}
			UILayer: {
				items.Name
			}
			Camera: {
				items.Name
				items.RatioX
				items.RatioY
				items.Target
				items.Position
				items.Zoom
			}
			Layer: {
				items.Name
				items.Index
				items.RatioX
				items.RatioY
				items.Offset
				items.Zoom
			}
			World: {
				items.Name
				items.Gravity
				items.Contact
				items.Simulation
				items.Outline
			}
			Body: {
				items.Name
				items.File
				items.Position
				items.Angle
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
			}
			Sprite: {
				items.Name
				items.File
				items.Position
				items.Angle
				items.Scale
				items.Skew
				items.Opacity
			}
			Effect: {
				items.Name
				items.Effect
				items.Offset
				items.Play
			}
		}
