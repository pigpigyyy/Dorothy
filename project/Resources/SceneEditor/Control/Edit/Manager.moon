Dorothy!
Class = unpack require "class"
Button = require "Control.Basic.Button"
SelectionPanel = require "Control.Basic.SelectionPanel"
GroupChooser = require "Control.Edit.GroupChooser"

Class => CCNode!,
	__init:=>
		{:width,:height} = CCDirector.winSize
		stopEditing = nil

		@schedule once ->
			sleep 0.1
			Ruler = require "Control.Edit.Ruler"
			@ruler = Ruler {
				x:(width-330)/2+70
				y:100
				width:width-330
				height:60
			}
			@addChild @ruler
		showRuler = (...)->
			@ruler\show ...
			stopEditing = ->
				stopEditing = nil
				@ruler\hide!

		@boolSwitcher = with CCMenu!
			.visible = false
			.position = oVec2 width-225,95
			.contentSize = CCSize 50,50
			.touchPriority = editor.levelEditMenu
			switcher = with Button {
					text:"True"
					x:25
					y:25
					width:50
					height:50
					fontSize:18
				}
				.value = true
				\slots "Tapped",-> @boolSwitcher\setValue not .value
			\addChild switcher
			.setValue = (value)=>
				switcher.value = value
				switcher.text = value and "True" or "False"
				switcher.color = ccColor3 value and 0x00ffff or 0xff0088
				\emit "Changed",value
		@addChild @boolSwitcher
		showSwitcher = (default,callback)->
			with @boolSwitcher
				\setValue default
				\slots("Changed")\set callback
				.visible = true
				.scaleX = 0
				.scaleY = 0
				\perform oScale 0.3,1,1,oEase.OutBack
			stopEditing = ->
				stopEditing = nil
				@boolSwitcher\perform CCSequence {
					oScale 0.3,0,0,oEase.InBack
					CCHide!
				}

		@gslot "Scene.SettingPanel.Edit",(item)->
			assert editor.currentData,"Invalid editor.currentData"
			if item and item.selected
				data = editor.currentData
				switch item.name
					when "outline","loop","visible","faceRight","play"
						showSwitcher data[item.name],(value)->
							data[item.name] = value
							item.value = value
					when "ratioX","ratioY"
						showRuler data[item.name],-10,10,1,(value)->
							data[item.name] = value
							item.value = value
					when "speed"
						showRuler data[item.name],0,10,1,(value)->
							data[item.name] = value
							item.value = value
					when "look"
						file = data.file
						looks = oCache.Model\getLookNames file
						table.insert looks,1,"None"
						with SelectionPanel items:looks
							\slots "Selected",(value)->
								data[item.name] = (value == "None" and "" or value)
								item.value = value
								emit "Scene.SettingPanel.Edit",nil
					when "animation"
						file = data.file
						looks = oCache.Model\getAnimationNames file
						table.insert looks,1,"None"
						with SelectionPanel items:looks
							\slots "Selected",(value)->
								data[item.name] = (value == "None" and "" or value)
								item.value = value
								emit "Scene.SettingPanel.Edit",nil
					when "group"
						groupChooser = with GroupChooser!
							\slots "Hide",->
								emit "Scene.SettingPanel.Edit",nil
							\slots "Selected",(group)->
								data[item.name] = group
								item.value = editor.sceneData.groups[group]
								groupChooser\hide!
					when "effect"
						print 1
					when "offset","position"
						print 1
					when "simulation"
						print 1
					when "zoom","scale"
						print 1
					when "angle"
						print 1
					when "skew"
						print 1
					when "groups"
						print 1
					when "contacts"
						print 1
					when "target"
						print 1
					when "gravity"
						print 1
					when "opacity"
						print 1
			elseif stopEditing
				stopEditing!
