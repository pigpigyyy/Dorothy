Dorothy!
ActionChooserView = require "View.Control.AI.ActionChooser"
SelectionItem = require "Control.Basic.SelectionItem"
import Set,Path from require "Lib.Utils"

Class ActionChooserView,
	__init:=>
		@curGroupBtn = nil
		@curActionBtn = nil

		selectItem = (button)->
			@curActionBtn.checked = false if @curActionBtn and @curActionBtn ~= button
			button.checked = true unless button.checked
			@curActionBtn = button

		selectGroup = (button)->
			@curGroupBtn.checked = false if @curGroupBtn and @curGroupBtn ~= button
			button.checked = true unless button.checked
			@curGroupBtn = button
			if not button.items
				files = if button.group == "Built-In"
					Path.getFiles editor.builtinActionPath,"action"
				else
					Path.getFiles editor.actionFullPath..button.group,"action"
				button.items = for file in *files
					with SelectionItem {
							text:Path.getName file
							fontSize:18
							width:180
							height:35
						}
						.file = button.group.."/"..file
						\slot "Tapped",selectItem
				button\slot "Cleanup",->
					if button.items
						for item in *button.items
							if item.parent
								item.parent\removeChild item
							else
								item\cleanup!
			@apiMenu\removeAllChildrenWithCleanup false
			for item in *button.items
				@apiMenu\addChild item
			with @apiScrollArea
				.offset = oVec2.zero
				.viewSize = @apiMenu\alignItems!

		groups = Path.getFolders editor.actionFullPath
		table.insert groups,1,"Built-In"
		for group in *groups
			@catMenu\addChild with SelectionItem {
					text:Path.getName group
					fontSize:18
					width:80
					height:35
				}
				.group = group
				\slot "Tapped",selectGroup
		@catScrollArea.viewSize = @catMenu\alignItems!
		@catScrollArea\setupMenuScroll @catMenu
		@apiScrollArea\setupMenuScroll @apiMenu
		selectGroup @catMenu.children[1] if @catMenu.children

		@selectBtn\slot "Tapped",->
			@hide!
			if @curActionBtn
				@emit "Selected",@curActionBtn.file
			else
				@emit "Selected",nil

		@show!
		editor\addChild @,editor.topMost

	show:=>
		@visible = true
		with @mask
			.opacity = 0
			\perform oOpacity 0.3,1,oEase.OutQuad
		with @panel
			.opacity = 0
			\perform CCSequence {
				oOpacity 0.3,1,oEase.OutQuad
				CCCall ->
					@catScrollArea.touchEnabled = true
					@apiScrollArea.touchEnabled = true
					@catMenu.enabled = true
					@apiMenu.enabled = true
					@opMenu.enabled = true
		}

	hide:=>
		@catScrollArea.touchEnabled = false
		@apiScrollArea.touchEnabled = false
		@catMenu.enabled = false
		@apiMenu.enabled = false
		@opMenu.enabled = false
		@panel\perform CCSequence {
			oOpacity 0.3,0,oEase.OutQuad
			CCCall -> @parent\removeChild @
		}
		@mask\perform CCSequence {
			oOpacity 0.3,0,oEase.OutQuad
			CCCall -> @mask.touchEnabled = false
		}
