Dorothy!
Class,property = unpack require "class"
SelectionPanelView = require "View.Control.SelectionPanel"
Button = require "Control.Button"

Class
	__partial: (args)=> SelectionPanelView args
	__init: (args)=>
		{:width,:items} = args
		for item in *items
			button = Button {
				text:item
				fontSize:16
				width:width-20
				height:40
			}
			button\slots "Tapped",->
				@\emit ""
			@menu\addChild button
		viewHeight = @menu\alignItemsVertically!
		@scrollArea.viewSize = CCSize width,viewHeight