Dorothy!
Class = unpack require "class"
GroupPanelView = require "View.Control.Edit.GroupPanel"

Class GroupPanelView,
	__init: =>
		sceneData = editor.sceneData
		for i  = 1,12
			item = @["p#{i}"]
			item\slots "Inputed",(newName)->
				editor\updateGroupName i,newName

		@scrollArea.viewSize = CCSize 0,@menu\alignItemsVertically!
