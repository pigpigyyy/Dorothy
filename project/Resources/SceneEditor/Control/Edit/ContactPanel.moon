Dorothy!
ContactPanelView = require "View.Control.Edit.ContactPanel"
Button = require "Control.Basic.Button"

Class ContactPanelView,
	__init: (args)=>
		groupIndex = args.group

		sceneData = editor.sceneData
		@labelName.text = "Group #{sceneData.groups[groupIndex]}"
		contactData = {}
		for i = 0,15
			shouldContact = editor.items.Scene\getShouldContact groupIndex,i
			contactData[i] = shouldContact

		for contact in *sceneData.contacts
			groupA,groupB,shouldContact = unpack contact
			if groupA == groupIndex
				contactData[groupB] = shouldContact
			elseif groupB == groupIndex
				contactData[groupA] = shouldContact

		isBuiltin = switch groupIndex
			when oData.GroupTerrain,oData.GroupDetectPlayer,oData.GroupDetect,oData.GroupHide
				true
			else
				false
		for i = 1,12
			@menu\addChild with CCNode!
				.contentSize = CCSize 160,40
				\addChild with CCLabelTTF sceneData.groups[i],"Arial",18
					.position = oVec2 80,20
					.color = ccColor3 0x00ffff
					.texture.antiAlias = false
			color = contactData[i] and 0x00ffff or 0xff0088
			if isBuiltin
				@menu\addChild with CCNode!
					.contentSize = CCSize 80,40
					\addChild with CCLabelTTF tostring(contactData[i]),"Arial",18
						.position = oVec2 40,20
						.color = ccColor3 color
			else
				button = with Button text:tostring(contactData[i]),width:80,height:40,fontSize:18
					.color = ccColor3 color
					\slot "Tapped", ->
						contactData[i] = not contactData[i]
						shouldContact = contactData[i]
						button.text = tostring shouldContact
						button.color = ccColor3 shouldContact and 0x00ffff or 0xff0088
						editor\updateContact groupIndex,i,shouldContact
				@menu\addChild button

		for i in *{oData.GroupTerrain,oData.GroupDetectPlayer,oData.GroupDetect,oData.GroupHide}
			@menu\addChild with CCNode!
				.contentSize = CCSize 160,40
				\addChild with CCLabelTTF sceneData.groups[i],"Arial",18
					.position = oVec2 80,20
					.color = ccColor3 0x00ffff
					.texture.antiAlias = false
			@menu\addChild with CCNode!
				.contentSize = CCSize 80,40
				\addChild with CCLabelTTF tostring(contactData[i]),"Arial",18
					.position = oVec2 40,20
					.color = ccColor3 contactData[i] and 0x00ffff or 0xff0088

		@scrollArea.viewSize = @menu\alignItems!
