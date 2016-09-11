Dorothy!
AttributePanelView = require "View.Control.Unit.AttributePanel"

Class AttributePanelView,
	__init:=>
		@setupMenuScroll @attributeMenu
		updateSize = -> @adjustScrollSize @attributeMenu,0,"auto"
		updateSize!

		updateEnableState = ->
			enabled = @attributeMenu.enabled
			@characterSetting.isEnabled = enabled
			@physicsSetting.isEnabled = enabled
			@battleSetting.isEnabled = enabled
			@aiSetting.isEnabled = enabled
			@visualSetting.isEnabled = enabled
		@slot "ScrollStart",updateEnableState
		@slot "ScrollTouchEnded",updateEnableState

		@characterSetting\slot "SizeChanged",updateSize
		@physicsSetting\slot "SizeChanged",updateSize
		@battleSetting\slot "SizeChanged",updateSize
		@aiSetting\slot "SizeChanged",updateSize
		@visualSetting\slot "SizeChanged",updateSize
