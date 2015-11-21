Dorothy!
Class,property,classfield = unpack require "class"
EditMenuView = require "View.Control.Operation.EditMenu"
SelectionPanel = require "Control.Basic.SelectionPanel"

-- [no signals]
-- [no params]
Class
	__partial: => EditMenuView!
	__init: =>
		buttonNames = {
			"sprite"
			"model"
			"body"
			"effect"
			"layer"
		}

		clearSelection = ->
			for name in *buttonNames
				button = @[name.."Btn"]
				if button.selected
					button.selected = false
					button.color = ccColor3 0x00ffff
					button.face.cascadeOpacity = true
					emit button.event,nil

		for name in *buttonNames
			button = @[name.."Btn"]
			button.selected = false
			upperName = name\sub(1,1)\upper!..name\sub(2,-1)
			@gslot "Scene."..upperName.."Selected",(item)->
				if item
					button.selected = true
					button.color = ccColor3 0xff0088
					button.face.cascadeOpacity = false
			button\slots "Tapped",->
				if not button.selected
					emit "Scene.View"..upperName
				clearSelection!

		@delBtn\slots "Tapped",-> emit "Scene.EditMenu.Delete"

		mode = 0
		@zoomBtn\slots "Tapped",->
			scale = switch mode
				when 0
					2
				when 1
					0.5
				when 2
					1
			mode += 1
			mode %= 3
			@zoomBtn.text = tostring(scale*100).."%"
			emit "Scene.ViewArea.ScaleTo",scale

		@originBtn\slots "Tapped",->
			emit "Scene.ViewArea.MoveTo",editor.origin

		@progressUp.visible = false
		@progressDown.visible = false

		@upBtn.visible = false
		@upBtn.enabled = false
		@upBtn\slots "TapBegan",->
			@upBtn\schedule once ->
				sleep 0.4
				@progressUp.visible = true
				@progressUp\play!
		@upBtn\slots "Tapped",->
			if @progressUp.visible
				if @progressUp.done
					emit "Scene.EditMenu.Top"
			else
				emit "Scene.EditMenu.Up"
		@upBtn\slots "TapEnded",->
			@upBtn\unschedule!
			if @progressUp.visible
				@progressUp.visible = false

		@downBtn.visible = false
		@downBtn.enabled = false
		@downBtn\slots "TapBegan",->
			@downBtn\schedule once ->
				sleep 0.4
				@progressDown.visible = true
				@progressDown\play!
		@downBtn\slots "Tapped",->
			if @progressDown.visible
				if @progressDown.done
					emit "Scene.EditMenu.Bottom"
			else
				emit "Scene.EditMenu.Down"
		@downBtn\slots "TapEnded",->
			@downBtn\unschedule!
			if @progressDown.visible
				@progressDown.visible = false

		@foldBtn.visible = false
		@foldBtn.enabled = false
		@foldBtn\slots "Tapped",->
			emit "Scene.ViewPanel.Fold",editor.currentData

		@editBtn.dirty = false
		@editBtn\slots "Tapped",->
			if not @editBtn.dirty
				ScenePanel = require "Control.Item.ScenePanel"
				ScenePanel!
			else
				editor\save!
				emit "Scene.Dirty",false

		@undoBtn.visible = false
		@undoBtn\slots "Tapped",->
			editor.currentSceneFile = editor.currentSceneFile
			emit "Scene.Dirty",false

		@gslot "Scene.Dirty",(dirty)->
			if @editBtn.dirty ~= dirty
				@editBtn.dirty = dirty
				if dirty
					@editBtn.color = ccColor3 0xff0088
					@editBtn.text = "Save"
					if not @undoBtn.visible
						@undoBtn.enabled = true
						@undoBtn.visible = true
						@undoBtn.scaleX = 0
						@undoBtn.scaleY = 0
						@undoBtn\perform oScale 0.3,1,1,oEase.OutBack
				else
					@editBtn.color = ccColor3 0x00ffff
					@editBtn.text = "Edit"
					if @undoBtn.visible
						@undoBtn.enabled = false
						@undoBtn\perform CCSequence {
							oScale 0.3,0,0,oEase.InBack
							CCHide!
						}

		itemChoosed = (itemData)->
			emit "Scene.ViewPanel.FoldState",
				itemData:itemData
				handler:(state)->
					if state ~= nil
						@setButtonVisible @foldBtn,true
						text = @foldBtn.text
						targetText = state and "Un\nFold" or "Fold"
						if text ~= targetText
							@foldBtn.text = targetText
							if @foldBtn.scale.done
								@setButtonVisible @foldBtn,true
					else
						@setButtonVisible @foldBtn,false
						@setButtonVisible @upBtn,false
						@setButtonVisible @downBtn,false
			return unless itemData
			switch itemData.typeName
				when "Camera","PlatformWorld","UILayer"
					@setButtonVisible @upBtn,false
					@setButtonVisible @downBtn,false
					{:x,:y} = @upBtn.position
					@foldBtn\runAction oPos 0.3,x,y,oEase.OutQuad
				else
					item = editor\getItem itemData
					hasChildren = false
					if itemData.typeName == "World"
						hasChildren = #item.parent.parent.children > 1
					else
						hasChildren = #item.parent.children > 1
					if item.parent.children and hasChildren
						@setButtonVisible @upBtn,true
						@setButtonVisible @downBtn,true
						{:x,:y} = @downBtn.position
						@foldBtn\runAction oPos 0.3,x,y-60,oEase.OutQuad
					else
						@setButtonVisible @upBtn,false
						@setButtonVisible @downBtn,false
						{:x,:y} = @upBtn.position
						@foldBtn\runAction oPos 0.3,x,y,oEase.OutQuad
		@gslot "Scene.ViewPanel.Pick",itemChoosed
		@gslot "Scene.ViewPanel.Select",itemChoosed

		@gslot "Scene.ViewArea.Scale",(scale)->
			@zoomBtn.text = tostring(scale*100).."%"

	setButtonVisible: (button,visible)=>
		return if visible == button.enabled
		button.enabled = visible
		if visible
			if not button.visible
				button.visible = true
				button.scaleX = 0
				button.scaleY = 0
			button\perform oScale 0.3,1,1,oEase.OutBack
		else
			button\perform CCSequence {
				oScale 0.3,0,0,oEase.InBack
				CCHide!
			}
