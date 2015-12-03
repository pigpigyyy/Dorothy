Dorothy!
Class = unpack require "class"
GroupPanelView = require "View.Control.Edit.GroupPanel"
TextBox = require "Control.Basic.TextBox"
MessageBox = require "Control.Basic.MessageBox"

Class GroupPanelView,
	__init: =>
		sceneData = editor.sceneData
		for i  = 1,12
			groupName = sceneData.groups[i]
			with @["p#{i}"]
				btnText = .placeHolder == groupName and "" or groupName
				.text = btnText
				\slots "Inputed",(newName)->
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

		@scrollArea.viewSize = CCSize 0,@menu\alignItemsVertically!
