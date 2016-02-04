Dorothy!
TriggerEditorView = require "View.Control.Trigger.TriggerEditor"

Class TriggerEditorView,
	__init:(args)=>
		@localBtn.checked = true
		scopeBtn = @localBtn
		changeScope = (button)->
			scopeBtn.checked = false unless scopeBtn == button
			button.checked = true unless button.checked
			scopeBtn = button
		@localBtn\slot "Tapped",changeScope
		@globalBtn\slot "Tapped",changeScope

		triggerBtn = nil
		changeTrigger = (button)->
			triggerBtn.checked = false if triggerBtn
			triggerBtn = if button.checked then button else nil
		for child in *@listMenu.children
			if child ~= @localBtn and child ~= @globalBtn
				child\slot "Tapped",changeTrigger

		@listScrollArea\setupMenuScroll @listMenu
		@listScrollArea.viewSize = @listMenu\alignItems!

		@exprEditor\loadTrigger "Control/Trigger/TriggerDataTest.lua"

		@closeBtn\slot "Tapped",-> @hide!
		@gslot "Scene.EditMenu.Delete",-> @show!

	show:=>
		@visible = true
		@closeBtn.scaleX = 0
		@closeBtn.scaleY = 0
		@closeBtn\perform oScale 0.3,1,1,oEase.OutBack
		@panel.opacity = 0
		@panel\perform CCSequence {
			oOpacity 0.3,1,oEase.OutQuad
			CCCall ->
				@exprEditor.enabled = true
				@listScrollArea.touchEnabled = true
				@listMenu.enabled = true
				@editMenu.enabled = true
				@opMenu.enabled = true
				for control in *editor.children
					control.visible = false if control ~= @
		}

	hide:=>
		for control in *editor.children
			control.visible = true if control ~= @
		@exprEditor.enabled = false
		@listScrollArea.touchEnabled = false
		@listMenu.enabled = false
		@editMenu.enabled = false
		@opMenu.enabled = false
		@closeBtn\perform oScale 0.3,0,0,oEase.InBack
		@panel\perform oOpacity 0.3,0,oEase.OutQuad
		@perform CCSequence {
			CCDelay 0.3
			CCHide!
		}
