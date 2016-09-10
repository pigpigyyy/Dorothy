Dorothy!
AttributePanelView = require "View.Control.Unit.AttributePanel"

Class AttributePanelView,
	__init:=>
		@setupMenuScroll @attributeMenu
		updateSize = -> @adjustScrollSize @attributeMenu,0,"vertical"
		updateSize!

		updateEnableState = ->
			@characterSetting.isEnabled = @attributeMenu.enabled
			@physicsSetting.isEnabled = @attributeMenu.enabled
		@slot "ScrollStart",updateEnableState
		@slot "ScrollTouchEnded",updateEnableState

		@characterSetting\slot "SizeChanged",updateSize
		@physicsSetting\slot "SizeChanged",updateSize
