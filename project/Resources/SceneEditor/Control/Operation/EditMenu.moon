Dorothy!
Class,property,classfield = unpack require "class"
EditMenuView = require "View.Control.Operation.EditMenu"
SelectionPanel = require "Control.Basic.SelectionPanel"

-- [no signals]
-- [no params]
Class EditMenuView,
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
			button.event = "Scene."..upperName.."Selected"
			@gslot button.event,(item)->
				if item
					button.selected = true
					button.color = ccColor3 0xff0088
					button.face.cascadeOpacity = false
			button\slot "Tapped",->
				if not button.selected
					emit "Scene.View"..upperName
				clearSelection!

		@delBtn\slot "Tapped",-> emit "Scene.EditMenu.Delete"

		mode = 0
		@zoomBtn\slot "Tapped",->
			mode = 0 if @zoomBtn.text == "100%"
			scale = switch mode
				when 0
					2
				when 1
					0.5
				when 2
					1
			mode += 1
			mode %= 3
			@zoomBtn.text = string.format("%d%%",scale*100)
			emit "Scene.ViewArea.ScaleTo",scale

		@originBtn\slot "Tapped",-> editor\moveTo oVec2.zero

		@progressUp.visible = false
		@progressDown.visible = false

		@upBtn.visible = false
		@upBtn.enabled = false
		@upBtn\slot "TapBegan",->
			@upBtn\schedule once ->
				sleep 0.4
				@progressUp.visible = true
				@progressUp\play!
		@upBtn\slot "Tapped",->
			if @progressUp.visible
				if @progressUp.done
					emit "Scene.EditMenu.Top"
			else
				emit "Scene.EditMenu.Up"
		@upBtn\slot "TapEnded",->
			@upBtn\unschedule!
			if @progressUp.visible
				@progressUp.visible = false

		@downBtn.visible = false
		@downBtn.enabled = false
		@downBtn\slot "TapBegan",->
			@downBtn\schedule once ->
				sleep 0.4
				@progressDown.visible = true
				@progressDown\play!
		@downBtn\slot "Tapped",->
			if @progressDown.visible
				if @progressDown.done
					emit "Scene.EditMenu.Bottom"
			else
				emit "Scene.EditMenu.Down"
		@downBtn\slot "TapEnded",->
			@downBtn\unschedule!
			if @progressDown.visible
				@progressDown.visible = false

		@foldBtn.visible = false
		@foldBtn.enabled = false
		@foldBtn\slot "Tapped",->
			emit "Scene.ViewPanel.Fold",editor.currentData

		@editBtn.dirty = false
		@editBtn\slot "Tapped",->
			if not @editBtn.dirty
				ScenePanel = require "Control.Item.ScenePanel"
				ScenePanel!
			else
				editor\save!
				emit "Scene.Dirty",false
			emit "Scene.SettingPanel.Edit",nil

		@undoBtn.visible = false
		@undoBtn\slot "Tapped",->
			editor.currentSceneFile = editor.currentSceneFile
			emit "Scene.Dirty",false

		@xFixBtn.visible = false
		@xFixBtn\slot "Tapped",(button)->
			editor.xFix = not editor.xFix
			if editor.yFix
				editor.yFix = false
				@yFixBtn.color = ccColor3 0x00ffff
			button.color = ccColor3 editor.xFix and 0xff0088 or 0x00ffff
			emit "Scene.FixChange"
		@yFixBtn.visible = false
		@yFixBtn\slot "Tapped",(button)->
			editor.yFix = not editor.yFix
			if editor.xFix
				editor.xFix = false
				@xFixBtn.color = ccColor3 0x00ffff
			button.color = ccColor3 editor.yFix and 0xff0088 or 0x00ffff
			emit "Scene.FixChange"

		@iconCam.visible = false
		@camBtn.visible = false
		@camBtn.editing = false
		@camBtn\gslot "Scene.Camera.Select",(subCam)-> @camBtn.subCam = subCam
		@camBtn\slot "Tapped",->
			if @camBtn.editing
				emit "Scene.Camera.Activate",nil
			else
				emit "Scene.Camera.Activate",@camBtn.subCam

		@gslot "Scene.ShowFix",(value)->
			editor.xFix = false
			editor.yFix = false
			emit "Scene.FixChange"
			if value
				@xFixBtn.visible = true
				@xFixBtn.color = ccColor3 0x00ffff
				@xFixBtn.scaleX = 0
				@xFixBtn.scaleY = 0
				@xFixBtn\perform oScale 0.5,1,1,oEase.OutBack
				@yFixBtn.visible = true
				@yFixBtn.color = ccColor3 0x00ffff
				@yFixBtn.scaleX = 0
				@yFixBtn.scaleY = 0
				@yFixBtn\perform oScale 0.5,1,1,oEase.OutBack
			else
				@xFixBtn.visible = false
				@yFixBtn.visible = false

		@gslot "Scene.Dirty",(dirty)->
			if @editBtn.dirty ~= dirty
				@editBtn.dirty = dirty
				if dirty
					@editBtn.text = "Save"
					if not @undoBtn.visible
						@undoBtn.enabled = true
						@undoBtn.visible = true
						@undoBtn.scaleX = 0
						@undoBtn.scaleY = 0
						@undoBtn\perform oScale 0.3,1,1,oEase.OutBack
				else
					@editBtn.color = ccColor3 0x00ffff
					@editBtn.text = "Menu"
					if @undoBtn.visible
						@undoBtn.enabled = false
						@undoBtn\perform CCSequence {
							oScale 0.3,0,0,oEase.InBack
							CCHide!
						}

		itemChoosed = (itemData)->
			if @camBtn.visible or @iconCam.visible
				@iconCam.visible = false
				@camBtn.visible = false
				emit "Scene.Camera.Select",nil
				emit "Scene.Camera.Activate",nil
			emit "Scene.ViewPanel.FoldState",{
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
			}
			return unless itemData
			switch itemData.typeName
				when "Camera","PlatformWorld","UILayer"
					@setButtonVisible @upBtn,false
					@setButtonVisible @downBtn,false
					{:x,:y} = @upBtn.position
					@foldBtn\runAction oPos 0.3,x,y,oEase.OutQuad
					if itemData.typeName == "Camera"
						with @iconCam
							.visible = true
							.scaleX = 0
							.scaleY = 0
							\perform oScale 0.3,0.5,0.5,oEase.OutBack
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
			mode = 2 if scale ~= 1
			@zoomBtn.text = string.format("%d%%",scale*100)

		@gslot "Scene.Camera.Select",(subCam)->
			if subCam and not @camBtn.visible
				@iconCam.opacity = 0
				with @camBtn
					.visible = true
					.scaleX = 0
					.scaleY = 0
					\perform oScale 0.3,1,1,oEase.OutBack
			else
				@camBtn.visible = false
				with @iconCam
					.opacity = 1
					.scaleX = 0
					.scaleY = 0
					\perform oScale 0.3,0.5,0.5,oEase.OutBack

		@gslot "Scene.Camera.Activate",(subCam)->
			editing = (subCam ~= nil)
			return if editing == @camBtn.editing
			@camBtn.editing = editing
			{:width} = CCDirector.winSize
			for i = 1,#@children
				child = @children[i]
				switch child
					when @camBtn
						posX = @camBtn.editing and width-35 or width-345
						child\perform oPos 0.5,posX,child.positionY,oEase.OutQuad
					when @editBtn,@undoBtn
						continue
					else
						if child.positionX < width/2
							child\perform oPos 0.5,-child.positionX,child.positionY,oEase.OutQuad
						else
							child\perform oPos 0.5,width*2-child.positionX,child.positionY,oEase.OutQuad

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
