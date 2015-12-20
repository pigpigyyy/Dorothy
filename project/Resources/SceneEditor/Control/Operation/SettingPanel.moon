Dorothy!
Class,property = unpack require "class"
SettingPanelView = require "View.Control.Operation.SettingPanel"
SettingItem = require "BodyEditor.Script.oSettingItem"
ViewItem = require "Control.Operation.ViewItem"
Button = require "Control.Basic.Button"
InputBox = require "Control.Basic.InputBox"
MessageBox = require "Control.Basic.MessageBox"
Model = require "Data.Model"

-- [no signals]
-- [no params]
Class SettingPanelView,
	__init: =>
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
			{"Gravity","%.2f"}
			{"Opacity","%.2f"}
			{"Boundary","%d"}
		}

		genPosY = ->
			index = 0
			->
				v = index
				index += 1
				@height-30-itemHeight/2-itemHeight*v

		items = {}
		getPosY = genPosY()
		editCallback = (settingItem)->
			emit "Scene.SettingPanel.Edit",settingItem

		for i = 1,#itemNames
			itemName = itemNames[i][1]
			valueFormat = itemNames[i][2]
			item = SettingItem itemName.." :",itemWidth,itemHeight,-itemWidth,getPosY(),(i == 1),valueFormat,editCallback
			item.anchor = oVec2 0.5,0.5
			item.name = itemName\sub(1,1)\lower!..itemName\sub(2,-1)
			item.visible = false
			items[itemName] = item

		for _,item in pairs items
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
				items.Boundary
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
				items.Visible
			}
		}

		camItems = {}
		currentCamItem = nil
		camItemTapped = (camItem)->
			if not camItem or camItem.checked
				if currentCamItem
					currentCamItem.checked = false
					--subCam = currentCamItem.itemData
				currentCamItem = camItem
				editor.items.Camera.boundary = editor.sceneData.camera.area
				print editor.sceneData.camera.area.left
				print editor.sceneData.camera.area.right
				print editor.sceneData.camera.area.bottom
				print editor.sceneData.camera.area.top
			else
				currentCamItem = nil
				editor.items.Camera.boundary = CCRect.zero

		currentGroup = nil
		selectGroup = (data)->
			if currentGroup
				for item in *currentGroup
					item.positionX = -itemWidth
					item.visible = false
				if currentGroup == groups.Camera
					for item in *camItems
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
					else
						data[item.name] == "" and "None" or data[item.name]
			if data.typeName == "Camera"
				currentCamItem.checked = false if currentCamItem
				for i,item in ipairs camItems
					item.visible = true
					item.positionX = itemWidth/2
					item.positionY = getPosY!-10*i
					contentHeight = contentHeight+itemHeight+10
			@viewSize = CCSize @width,contentHeight

		@gslot "Scene.ViewPanel.Select",selectGroup

		currentItem = nil
		@gslot "Scene.SettingPanel.Edit",(item)->
			if not item or item.selected
				if currentItem
					currentItem.selected = false
				currentItem = item
			else
				currentItem = nil

		loadCameras = (sceneData)->
			for item in *camItems
				@menu\removeChild item
			camItems = {}
			currentCamItem = nil
			return unless sceneData
			cameraData = sceneData.camera
			if cameraData.subCams
				for child in *cameraData.subCams
					viewItem = with ViewItem {
							text:child.name
							x:-itemWidth
							y:0
							width:itemWidth-20
							height:itemHeight
						}
						.visible = false
						.itemData = child
						\slots "Tapped",camItemTapped
					@menu\addChild viewItem
					table.insert camItems,viewItem
			viewItem = with Button {
					text:"<NEW>"
					x:-itemWidth
					y:0
					width:itemWidth-20
					height:itemHeight
					fontSize:16
				}
				.visible = false
				\slots "Tapped",->
					with InputBox text:"New Camera Name"
						\slots "Inputed",(text)->
							if cameraData.subCams
								for child in *cameraData.subCams
									if child.name == text
										MessageBox text:"Name Exist!",okOnly:true
										return
							else
								cameraData.subCams = {}
							subCam = Model.SubCam!
							subCam.name = text
							table.insert cameraData.subCams,subCam
							loadCameras sceneData
							selectGroup cameraData
			@menu\addChild viewItem
			table.insert camItems,viewItem

		@gslot "Scene.DataLoaded",loadCameras
