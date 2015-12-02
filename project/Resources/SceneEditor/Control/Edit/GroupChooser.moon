Dorothy!
Class = unpack require "class"
GroupChooserView = require "View.Control.Edit.GroupChooser"
Button = require "Control.Basic.Button"

Class GroupChooserView,
	__init: =>
		indices = [i for i = 1,12]
		for i in *{oData.GroupTerrain,oData.GroupDetectPlayer,oData.GroupDetect,oData.GroupHide}
			table.insert indices,i
		sceneData = editor.sceneData
		for i in *indices
			@menu\addChild with Button {
					text:sceneData.groups[i]
					tag:i
					width:180
					height:40
					fontSize:18
				}
				\slots "Tapped",(button)->
					@emit "Selected",button.tag

		@scrollArea.viewSize = CCSize 0,@menu\alignItemsVertically!
