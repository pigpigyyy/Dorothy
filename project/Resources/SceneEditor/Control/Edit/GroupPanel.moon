Dorothy!
GroupPanelView = require "View.Control.Edit.GroupPanel"
MessageBox = require "Control.Basic.MessageBox"

Class GroupPanelView,
	__init: =>
		sceneData = editor.sceneData
		for i  = 1,12
			groupName = sceneData.groups[i]
			with @["p#{i}"]
				btnText = .placeHolder == groupName and "" or groupName
				.text = btnText
				\slot "Inputed",(newName)->
					nameExist = false
					for n = 0,15
						if newName == sceneData.groups[n] and n ~= i
							nameExist = true
							break
					if nameExist
						.text = btnText
						MessageBox text:"Group Name Exist!", okOnly:true
					else
						btnText = newName == .placeHolder and "" or newName
						editor\updateGroupName i,newName

		@scrollArea.viewSize = @menu\alignItemsVertically!
