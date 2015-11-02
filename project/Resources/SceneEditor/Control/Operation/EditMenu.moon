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

		@upBtn\slots "TapBegan",->
			@upBtn\schedule once ->
				sleep 0.4
				@progressUp.visible = true
				@progressUp\play!
		@upBtn\slots "Tapped",->
			if @progressUp.visible
				if @progressUp.done
					print "long tap"
			else
				print "tap"
		@upBtn\slots "TapEnded",->
			@upBtn\unschedule!
			if @progressUp.visible
				@progressUp.visible = false

		@downBtn\slots "TapBegan",->
			@downBtn\schedule once ->
				sleep 0.4
				@progressDown.visible = true
				@progressDown\play!
		@downBtn\slots "Tapped",->
			if @progressDown.visible
				if @progressDown.done
					print "long tap"
			else
				print "tap"
		@downBtn\slots "TapEnded",->
			@downBtn\unschedule!
			if @progressDown.visible
				@progressDown.visible = false

		@foldBtn\slots "Tapped",->
			emit "Scene.ViewPanel.Fold",editor.currentData

	nodeButtonVisible: property =>
		