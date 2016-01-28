Dorothy!
TriggerEditorView = require "View.Control.Trigger.TriggerEditor"
TriggerExpr = require "Control.Trigger.TriggerExpr"
ExprChooser = require "Control.Trigger.ExprChooser"

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

		triggerExpr = nil
		changeTriggerExpr = (button)->
			triggerExpr.checked = false if triggerExpr
			triggerExpr = if button.checked then button else nil

		@contentLabel.textWidth = @triggerMenu.width
		@contentLabel.positionX = @contentLabel.width/2+10
		for child in *@contentLabel.children[20,27]
			child.color = ccColor3 0xff0080
		for child in *@contentLabel.children[32,39]
			child.color = ccColor3 0xff0080
		for child in *@contentLabel.children[44,51]
			child.color = ccColor3 0xff0080
		for child in *@contentLabel.children[60,67]
			child.color = ccColor3 0xff0080

		@triggerMenu\addChild with TriggerExpr {
					text:"Count numbers from [Number] to [Number] by [Number] and do [Action]."
					width:@triggerMenu.width-20
				}
			\slot "Tapped",changeTriggerExpr
		@triggerMenu\addChild with TriggerExpr {
					indent:0
					text:"If conditions meet"
					width:@triggerMenu.width-20
				}
			\slot "Tapped",changeTriggerExpr
		@triggerMenu\addChild with TriggerExpr {
					indent:1
					text:"scopeBtn == button"
					width:@triggerMenu.width-20
				}
			\slot "Tapped",changeTriggerExpr
		@triggerMenu\addChild with TriggerExpr {
					indent:0
					text:"Then do actions"
					width:@triggerMenu.width-20
				}
			\slot "Tapped",changeTriggerExpr
		@triggerMenu\addChild with TriggerExpr {
					indent:1
					text:"@contentLabel.textWidth = @triggerMenu.width"
					width:@triggerMenu.width-20
				}
			\slot "Tapped",changeTriggerExpr
		@triggerMenu\addChild with TriggerExpr {
					indent:0
					text:"Else do actions"
					width:@triggerMenu.width-20
				}
			\slot "Tapped",changeTriggerExpr
		@triggerMenu\addChild with TriggerExpr {
					indent:1
					text:"Do nothing"
					width:@triggerMenu.width-20
				}
			\slot "Tapped",changeTriggerExpr
		@triggerMenu\addChild with TriggerExpr {
					indent:0
					text:"Create model [Model] at position [Point] of layer [Layer] with angle [Number] and plays [Animation] with loop [Boolean]."
					width:@triggerMenu.width-20
				}
			\slot "Tapped",changeTriggerExpr
		@triggerMenu\alignItems!

		thread ->
			sleep!
			with ExprChooser valueType:"Action"
				\slot "Result",(expr)->
					@triggerMenu\addChild with TriggerExpr {
							indent:0
							text:tostring expr
							width:@triggerMenu.width-20
						}
						\slot "Tapped",changeTriggerExpr
					@triggerMenu\alignItems!

		@show!
		@closeBtn\slot "Tapped",-> @hide!

	show:=>
		@perform CCSequence {
			CCShow!
			oOpacity 0.3,0.6,oEase.OutQuad
		}
		@closeBtn.scaleX = 0
		@closeBtn.scaleY = 0
		@closeBtn\perform oScale 0.3,1,1,oEase.OutBack
		@panel.opacity = 0
		@panel.scaleX = 0
		@panel.scaleY = 0
		@panel\perform CCSequence {
			CCSpawn {
				oOpacity 0.3,1,oEase.OutQuad
				oScale 0.3,1,1,oEase.OutBack
			}
			CCCall ->
				@triggerScrollArea.touchEnabled = true
				@listScrollArea.touchEnabled = true
				@triggerMenu.enabled = true
				@listMenu.enabled = true
				@editMenu.enabled = true
				@opMenu.enabled = true
		}

	hide:=>
		@triggerScrollArea.touchEnabled = false
		@listScrollArea.touchEnabled = false
		@triggerMenu.enabled = false
		@listMenu.enabled = false
		@editMenu.enabled = false
		@opMenu.enabled = false
		@closeBtn\perform oScale 0.3,0,0,oEase.InBack
		@panel\perform CCSpawn {
			oOpacity 0.3,0,oEase.OutQuad
			oScale 0.3,0,0,oEase.InBack
		}
		@perform CCSequence {
			oOpacity 0.3,0,oEase.OutQuad
			CCHide!
		}
