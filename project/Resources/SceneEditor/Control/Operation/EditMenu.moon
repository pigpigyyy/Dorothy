Dorothy!
Class,property,classfield = unpack require "class"
EditMenuView = require "View.Control.Operation.EditMenu"
SelectionPanel = require "Control.Basic.SelectionPanel"

-- [no signals]
-- [no params]
Class EditMenuView,
	__init: =>
		{:width} = CCDirector.winSize
		isHide = false

		buttonNames = {
			"sprite"
			"model"
			"body"
			"effect"
			"layer"
		}

		clearSelection = ->
			for name in *buttonNames
				with @[name.."Btn"]
					if .selected
						.selected = false
						.color = ccColor3 0x00ffff
						.scaleX = 0
						.scaleY = 0
						\perform oScale 0.3,1,1,oEase.OutBack
						emit .event,nil

		for name in *buttonNames
			with @[name.."Btn"]
				.selected = false
				upperName = name\sub(1,1)\upper!..name\sub(2,-1)
				.event = "Scene."..upperName.."Selected"
				@gslot .event,(item)->
					if item
						.selected = true
						.color = ccColor3 0xff0088
						.scaleX = 0
						.scaleY = 0
						\perform oScale 0.3,1,1,oEase.OutBack
				\slot "Tapped",->
					if not .selected
						emit "Scene.View"..upperName
						clearSelection!
					else
						.selected = false
						.color = ccColor3 0x00ffff
						emit .event,nil

		@delBtn\slot "Tapped",->
			clearSelection!
			emit "Scene.EditMenu.Delete"

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

		with @upBtn
			.visible = false
			.enabled = false
			\slot "TapBegan",->
				clearSelection!
				\schedule once ->
					sleep 0.4
					@progressUp.visible = true
					@progressUp\play!
			\slot "Tapped",->
				if @progressUp.visible
					if @progressUp.done
						emit "Scene.EditMenu.Top"
				else
					emit "Scene.EditMenu.Up"
			\slot "TapEnded",->
				\unschedule!
				if @progressUp.visible
					@progressUp.visible = false

		with @downBtn
			.visible = false
			.enabled = false
			\slot "TapBegan",->
				clearSelection!
				\schedule once ->
					sleep 0.4
					@progressDown.visible = true
					@progressDown\play!
			\slot "Tapped",->
				if @progressDown.visible
					if @progressDown.done
						emit "Scene.EditMenu.Bottom"
				else
					emit "Scene.EditMenu.Down"
			\slot "TapEnded",->
				\unschedule!
				if @progressDown.visible
					@progressDown.visible = false

		with @foldBtn
			.visible = false
			.enabled = false
			\slot "Tapped",->
				clearSelection!
				emit "Scene.ViewPanel.Fold",editor.currentData

		with @editBtn
			.visible = false
			.enabled = false
			\slot "Tapped",->
				emit "Scene.SettingPanel.Edit",nil
				editor\editCurrentItemInPlace!

		with @menuBtn
			.dirty = false
			\slot "Tapped",->
				clearSelection!
				if .dirty
					editor\save!
					emit "Scene.Dirty",false
				else
					ScenePanel = require "Control.Item.ScenePanel"
					ScenePanel!
				emit "Scene.SettingPanel.Edit",nil

		with @undoBtn
			.visible = false
			\slot "Tapped",->
				clearSelection!
				editor.currentSceneFile = editor.currentSceneFile
				emit "Scene.Dirty",false

		with @xFixBtn
			.visible = false
			\slot "Tapped",(button)->
				editor.xFix = not editor.xFix
				if editor.yFix
					editor.yFix = false
					@yFixBtn.color = ccColor3 0x00ffff
				button.color = ccColor3 editor.xFix and 0xff0088 or 0x00ffff
				emit "Scene.FixChange"

		with @yFixBtn
			.visible = false
			\slot "Tapped",(button)->
				editor.yFix = not editor.yFix
				if editor.xFix
					editor.xFix = false
					@xFixBtn.color = ccColor3 0x00ffff
				button.color = ccColor3 editor.yFix and 0xff0088 or 0x00ffff
				emit "Scene.FixChange"

		@iconCam.visible = false

		currentSubCam = nil
		with @camBtn
			.visible = false
			.editing = false
			\gslot "Scene.Camera.Select",(subCam)->
				currentSubCam = subCam
			\slot "Tapped",->
				.editing = not .editing
				if .editing
					emit "Scene.Camera.Activate",currentSubCam
				else
					emit "Scene.Camera.Activate",nil

		with @zoomEditBtn
			.visible = false
			.editing = false
			\slot "Tapped",->
				.editing = not .editing
				if .editing and currentSubCam
					emit "Scene.Edit.ShowRuler", {currentSubCam.zoom,0.5,10,1,(value)->
						emit "Scene.ViewArea.Scale",value
					}
				else
					emit "Scene.Edit.ShowRuler",nil

		@gslot "Scene.ShowFix",(value)->
			editor.xFix = false
			editor.yFix = false
			emit "Scene.FixChange"
			if value
				with @xFixBtn
					.visible = true
					.color = ccColor3 0x00ffff
					.scaleX = 0
					.scaleY = 0
					\perform oScale 0.5,1,1,oEase.OutBack
				with @yFixBtn
					.visible = true
					.color = ccColor3 0x00ffff
					.scaleX = 0
					.scaleY = 0
					\perform oScale 0.5,1,1,oEase.OutBack
			else
				@xFixBtn.visible = false
				@yFixBtn.visible = false

		@gslot "Scene.Dirty",(dirty)->
			with @menuBtn
				if .dirty ~= dirty
					.dirty = dirty
					if dirty
						.text = "Save"
						with @undoBtn
							if not .visible
								.enabled = true
								.visible = true
								.scaleX = 0
								.scaleY = 0
								\perform oScale 0.3,1,1,oEase.OutBack
					else
						.color = ccColor3 0x00ffff
						.text = "Menu"
						with @undoBtn
							if .visible
								.enabled = false
								\perform CCSequence {
									oScale 0.3,0,0,oEase.InBack
									CCHide!
								}

		itemChoosed = (itemData)->
			return if isHide
			if @camBtn.visible or @iconCam.visible
				@iconCam.visible = false
				@camBtn.visible = false
				emit "Scene.Camera.Activate",nil
				emit "Scene.Camera.Select",nil
			emit "Scene.ViewPanel.FoldState",{
				itemData:itemData
				handler:(state)->
					if state ~= nil
						@setButtonVisible @foldBtn,true
						switch itemData.typeName
							when "Body","Model","Effect"
								@setButtonVisible @editBtn,true
							else
								@setButtonVisible @editBtn,false
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
						@setButtonVisible @editBtn,false
			}
			return unless itemData
			switch itemData.typeName
				when "Camera","PlatformWorld","UILayer"
					@setButtonVisible @upBtn,false
					@setButtonVisible @downBtn,false
					{:x,:y} = @upBtn.position
					@foldBtn\runAction oPos 0.3,x,y,oEase.OutQuad
					if itemData.typeName == "Camera"
						clearSelection!
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
						@editBtn\runAction oPos 0.3,x,y-120,oEase.OutQuad
					else
						@setButtonVisible @upBtn,false
						@setButtonVisible @downBtn,false
						{:x,:y} = @upBtn.position
						@foldBtn\runAction oPos 0.3,x,y,oEase.OutQuad
						@editBtn\runAction oPos 0.3,x,y-60,oEase.OutQuad
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

		changeDisplay = (child,hide,instant)->
			if child.positionX < width/2
				if instant
					child.positionX = -child.positionX
				else
					child\perform oPos 0.5,-child.positionX,child.positionY,oEase.OutQuad
			else
				if instant
					child.positionY = -child.positionY
				else
					child\perform oPos 0.5,width*2-child.positionX,child.positionY,oEase.OutQuad

		@gslot "Scene.HideEditor",(args)->
			{hide,all} = args
			return if isHide == hide
			isHide = hide
			@enabled = @camBtn.editing or not hide
			for i = 1,#@children
				child = @children[i]
				switch child
					when @camBtn
						posX = @camBtn.editing and width-35 or width-345
						child\perform oPos 0.5,posX,child.positionY,oEase.OutQuad
					when @menuBtn,@undoBtn,@zoomEditBtn,@iconCam
						if all
							changeDisplay child,hide,instant
						else
							continue
					else
						changeDisplay child,hide,instant

		@gslot "Scene.Camera.Activate",(subCam)->
			editor.isFixed = not @camBtn.editing
			if @camBtn.editing
				with @zoomEditBtn
					.scaleX = 0
					.scaleY = 0
					.visible = true
					\perform CCSequence {
						CCDelay 0.5
						oScale 0.3,1,1,oEase.OutBack
					}
			else
				@zoomEditBtn.visible = false
				@zoomEditBtn.editing = false
				emit "Scene.Edit.ShowRuler",nil

		@gslot "Scene.EditMenu.ClearSelection",clearSelection

	setButtonVisible:(button,visible)=>
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
