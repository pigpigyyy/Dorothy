Dorothy!
Class = unpack require "class"
GroupEditorView = require "View.Control.Edit.GroupEditor"

Class GroupEditorView,
	__init: =>
		sceneData = editor.sceneData
		for i  = 1,12
			item = @["p#{i}"]
			item\slots "Inputed",(newName)->
				editor\updateGroupName i,newName

		@scrollArea.viewSize = CCSize 0,@menu\alignItemsVertically!
