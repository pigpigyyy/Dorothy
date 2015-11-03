Dorothy!
Class,property,classfield = unpack require "class"
EditMenuView = require "View.Control.Operation.EditMenu"

Class
	__partial: => EditMenuView!
	__init: =>
		spriteSelected = false
		modelSelected = false
		bodySelected = false
		effectSelected = false
		clearSelection = ->
			if spriteSelected
				spriteSelected = false
				@spriteBtn.color = ccColor3 0x00ffff
				emit "Scene.SpriteSelected",nil
			if modelSelected
				modelSelected = false
				@modelBtn.color = ccColor3 0x00ffff
				emit "Scene.ModelSelected",nil
			if bodySelected
				bodySelected = false
				@bodyBtn.color = ccColor3 0x00ffff
				emit "Scene.BodySelected",nil
			if effectSelected
				effectSelected = false
				@effectBtn.color = ccColor3 0x00ffff
				emit "Scene.EffectSelected",nil

		@spriteBtn\slots "Tapped",->
			emit "Scene.ViewSprite" unless spriteSelected
			clearSelection!
		@modelBtn\slots "Tapped",->
			emit "Scene.ViewModel" unless modelSelected
			clearSelection!
		@bodyBtn\slots "Tapped",->
			emit "Scene.ViewBody" unless bodySelected
			clearSelection!
		@effectBtn\slots "Tapped",->
			emit "Scene.ViewEffect" unless effectSelected
			clearSelection!

		@gslot "Scene.SpriteSelected",(item)->
			if item
				spriteSelected = true
				@spriteBtn.color = ccColor3 0xff0088
		@gslot "Scene.ModelSelected",(item)->
			if item
				modelSelected = true
				@modelBtn.color = ccColor3 0xff0088
		@gslot "Scene.BodySelected",(item)->
			if item
				bodySelected = true
				@bodyBtn.color = ccColor3 0xff0088
		@gslot "Scene.EffectSelected",(item)->
			if item
				effectSelected = true
				@effectBtn.color = ccColor3 0xff0088

		@gslot "Scene.ViewArea.Scale",(scale)->
			@zoomBtn.text = tostring(scale*100).."%"

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
			return unless itemData
			switch itemData.typeName
				when "Camera","PlatformWorld","UILayer"
					@setButtonVisible @upBtn,false
					@setButtonVisible @downBtn,false
					{:x,:y} = @upBtn.position
					@foldBtn\runAction oPos 0.3,x,y,oEase.OutQuad
				else
					@setButtonVisible @upBtn,true
					@setButtonVisible @downBtn,true
					{:x,:y} = @downBtn.position
					@foldBtn\runAction oPos 0.3,x,y-60,oEase.OutQuad
		@gslot "Scene.ViewPanel.Pick",itemChoosed
		@gslot "Scene.ViewPanel.Select",itemChoosed

	setButtonVisible: (button,visible)=>
		return if visible == button.enabled
		button.enabled = visible
		if visible
			button.visible = true
			button.scaleX = 0
			button.scaleY = 0
			button\perform oScale 0.3,1,1,oEase.OutBack
		else
			button\perform CCSequence {
				oScale 0.3,0,0,oEase.InBack
				CCHide!
			}
