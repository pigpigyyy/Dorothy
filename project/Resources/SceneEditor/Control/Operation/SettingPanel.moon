Dorothy!
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
		currentItem = nil
		editCallback = (settingItem)->
			emit "Scene.EditMenu.ClearSelection"
			if currentItem
				currentItem.selected = false
				emit "Scene.SettingPanel.Edit",currentItem
				currentItem = nil
			if settingItem.selected
				currentItem = settingItem
				emit "Scene.SettingPanel.Edit",currentItem

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
			emit "Scene.EditMenu.ClearSelection"
			if camItem.checked
				if currentCamItem
					currentCamItem.checked = false
					emit "Scene.Camera.Select",nil
				currentCamItem = camItem
				subCam = currentCamItem.itemData
				emit "Scene.Camera.Select",subCam
				emit "Scene.SettingPanel.Edit",nil
			else
				currentCamItem = nil
				emit "Scene.Camera.Select",nil

		items.Boundary\slot "Tapped",(button)->
			if button.selected and currentCamItem
				currentCamItem.checked = false
				camItemTapped currentCamItem

		currentGroup = nil
		selectGroup = (data,reset=true)->
			if currentGroup
				for item in *currentGroup
					item.positionX = -itemWidth
					item.visible = false
				if currentGroup == groups.Camera
					for item in *camItems
						item.positionX = -itemWidth
						item.visible = false
			if data
				@offset = oVec2.zero if reset
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
				item.positionY = getPosY!+(reset and 0 or @offset.y)
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
			if currentCamItem
				currentCamItem.checked = false
				camItemTapped currentCamItem
				currentCamItem = nil
			if data.typeName == "Camera"
				for i,item in ipairs camItems
					item.visible = true
					item.positionX = itemWidth/2
					item.positionY = getPosY!-10*i+(reset and 0 or @offset.y)
					contentHeight = contentHeight+itemHeight+10
			@viewSize = CCSize @width,contentHeight

		@gslot "Scene.ViewPanel.Select",selectGroup

		@gslot "Scene.SettingPanel.Edit",(item)->
			if currentItem ~= item
				currentItem.selected = false
				currentItem = nil
				if item
					item.selected = true
					currentItem = item

		loadCameras = (sceneData)->
			for item in *camItems
				@menu\removeChild item
			camItems = {}
			currentCamItem = nil
			emit "Scene.Camera.Activate",nil
			emit "Scene.Camera.Select",nil
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
						\slot "Tapped",camItemTapped
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
				\slot "Tapped",->
					emit "Scene.EditMenu.ClearSelection"
					emit "Scene.SettingPanel.Edit",nil
					with InputBox text:"New Camera Name"
						\slot "Inputed",(text)->
							return unless text
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
							selectGroup cameraData,false
							lastItem = camItems[#camItems-1]
							lastItem.checked = true
							camItemTapped lastItem
			@menu\addChild viewItem
			table.insert camItems,viewItem

		@gslot "Scene.DataLoaded",loadCameras

		isHide = false
		@gslot "Scene.HideEditor",(args)->
			{hide} = args
			return if isHide == hide
			isHide = hide
			winWidth = CCDirector.winSize.width
			@perform oPos 0.5,winWidth*2-@positionX,@positionY,oEase.OutQuad
