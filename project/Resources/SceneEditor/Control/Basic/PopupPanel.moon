Dorothy!
PopupPanelView = require "View.Control.Basic.PopupPanel"

-- [signals]
-- "Show",->
-- "Hide",->
-- [params]
-- width,height
Class PopupPanelView,
	__init:(args)=>
		contentRect = CCRect.zero
		itemRect = CCRect.zero
		@scrollArea\setupMenuScroll @menu
		@closeBtn\slot "Tapped",-> @hide!
		CCDirector.currentScene\addChild @,editor.topMost
		thread -> @show!

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
				@scrollArea.touchEnabled = true
				@menu.enabled = true
				@opMenu.enabled = true
				@emit "Show"
		}

	hide:=>
		@scrollArea.touchEnabled = false
		@menu.enabled = false
		@opMenu.enabled = false
		@closeBtn\perform oScale 0.3,0,0,oEase.InBack
		@panel\perform CCSpawn {
			oOpacity 0.3,0,oEase.OutQuad
			oScale 0.3,0,0,oEase.InBack
		}
		@perform CCSequence {
			oOpacity 0.3,0,oEase.OutQuad
			CCCall ->
				@emit "Hide"
				@parent\removeChild @
		}
