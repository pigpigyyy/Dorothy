Dorothy!
ExprChooserView = require "View.Control.Trigger.ExprChooser"
TriggerDef = require "Data.TriggerDef"
MenuItem = require "Control.Trigger.MenuItem"
SolidRect = require "View.Shape.SolidRect"
GroupButton = require "Control.Basic.GroupButton"
SelectionPanel = require "Control.Basic.SelectionPanel"
InputBox = require "Control.Basic.InputBox"
MessageBox = require "Control.Basic.MessageBox"
TextBox = require "Control.Basic.TextBox"
import Set,Path from require "Data.Utils"

local ExprChooser
ExprChooser = Class
	__initc:=>
		@level = 1
		@preview = nil

	__partial:(args)=>
		args.level = @@level
		@@level += 1
		ExprChooserView args

	__init:(args)=>
		{
			:valueType
			:expr
			:parentExpr
			:owner
			:editorType
			:prev
			:noVar
			:backOnly
		} = args
		@exprButtons = {}
		@exprs = {}
		@curGroupBtn = nil
		@curExprBtn = nil
		@curExpr = expr
		@parentExpr = parentExpr
		@owner = owner
		@prev = prev
		@type = editorType or owner.type
		@exprs[getmetatable expr] = expr if expr
		@needOpen = false
		if args.level == 1
			@@preview = with @previewItem
				.owner = @
				\update!

		@backBtn\slot "TapBegan",nil
		@okBtn\slot "TapBegan",nil if @okBtn

		selectGroup = (button)->
			@curGroupBtn.checked = false unless @curGroupBtn == button
			button.checked = true unless button.checked
			@curGroupBtn = button
			groupName = button.text
			exprItem = nil
			for item in *@apiMenu.children
				exprDef = item.exprDef
				if exprDef.Group == groupName
					exprItem = @exprButtons[exprDef]
					break
			@apiScrollArea\scrollToPosY exprItem.positionY
			thread ->
				sleep 0.3
				exprItem\glow!

		local updateContent

		colorBodyText = (colored)->
			startIndex = 1
			text = @bodyLabel.text
			color = ccColor3 colored and 0xff0080 or 0xffffff
			for i = #@bodyMenu.children,2,-1
				@bodyMenu\removeChild @bodyMenu.children[i]
			labelPos = @bodyLabel.position-oVec2(0,@bodyLabel.height)
			if not colored
				for child in *@bodyLabel.children
					child.color = color
			exprIndex = 1
			while startIndex
				startIndex = text\find "[",startIndex,true
				if startIndex
					exprIndex += 1
					stopIndex = nil
					if @curExpr
						exprText = tostring @curExpr[exprIndex]
						stopIndex = startIndex+#exprText+1
					else
						stopIndex = text\find "]",startIndex,true
					if colored
						@bodyLabel\colorText startIndex,stopIndex,color
						char = @bodyLabel\getChar startIndex
						charPoint = oVec2 char.width,char.height
						upperY = (labelPos+char.position+charPoint*(oVec2(1,1)-char.anchor)).y+10
						char = @bodyLabel\getChar stopIndex
						lowerY = (labelPos+char.position-charPoint*char.anchor).y-10
						labelWidth = @bodyMenu.width-20
						menuItem = with CCMenuItem!
							.anchor = oVec2 0,1
							.contentSize = CCSize labelWidth,upperY-lowerY
							.position = oVec2 10,upperY
							\addChild (SolidRect width:.width,height:.height,color:0x2200ffff),-1
							index = exprIndex
							\slot "Tapped",->
								menuItem.enabled = false
								exprDef = @curExprBtn.exprDef
								with ExprChooser {
										valueType:@curExpr[index].Type
										expr:@curExpr[index]
										parentExpr:@curExpr
										owner:@owner
										editorType:@type
										prev:@
										:noVar
										:backOnly
									}
									\slot "Show",->
										@panel.visible = false
										@opMenu.visible = false
									\slot "Hide",->
										menuItem.enabled = true
										@panel.visible = true
										@opMenu.visible = true
										@showButtons!
										updateContent exprDef
									\slot "Result",(expr)->
										@curExpr[index] = expr if expr
								@hideButtons!
						@bodyMenu\addChild menuItem
					startIndex = stopIndex

		setBodyText = (text)->
			colorBodyText false
			@bodyLabel.text = text
			@bodyScrollArea.offset = oVec2.zero
			@bodyScrollArea.viewSize = @bodyMenu\alignItems!
			colorBodyText true

		chooseItemType = (itemType)->
			localVarButton = with GroupButton {
					text:Path.getName(@curExpr[2]) or ""
					width:math.min(170,@bodyMenu.width-20)
					height:35
				}
				.position = oVec2 @bodyMenu.width/2,
					@bodyLabel.positionY-@bodyLabel.height/2-20-.height/2
				\slot "Tapped",(button)->
					emit "Editor.ItemChooser",{itemType,(itemChooser)->
						editor\addChild with itemChooser
							\slot "Selected",(filename)->
								localVarButton.text = Path.getName filename
								@curExpr[2] = filename
								@updatePreview!
							\show!
					}
			@bodyMenu\addChild localVarButton

		editLocalVariable = (varType)->
			isSetVar = @parentExpr[1] == "SetLocal#{ varType }"
			localNames = @owner\getPrevLocalVars varType
			table.insert localNames,"<NEW>" if isSetVar
			oldName = @curExpr[2]
			localVarButton = with GroupButton {
					text:@curExpr[2]
					width:math.min(170,@bodyMenu.width-20)
					height:35
				}
				.position = oVec2 @bodyMenu.width/2,
					@bodyLabel.positionY-@bodyLabel.height-10-.height/2
				\slot "Tapped",(button)->
					with SelectionPanel {
							title:"Select Name"
							width:150
							items:localNames
							itemHeight:40
							fontSize:20
						}
						.menu.children.last.color = ccColor3 0x80ff00 if isSetVar
						\slot "Selected",(item)->
							return unless item
							if item == "<NEW>"
								with InputBox text:"New Varaible Name"
									\slot "Inputed",(result)->
										return unless result
										if not result\match("^[_%a][_%w]*$")
											MessageBox text:"Invalid Name!",okOnly:true
										else
											isNameFirstAppear = true
											for name in *localNames
												isNameFirstAppear = false if oldName == name
												if name == result
													MessageBox text:"Name Exist!",okOnly:true
													return
											if isNameFirstAppear and oldName ~= "localName"
												@owner\markLocalVarRename oldName,result
											button.text = result
											@curExpr[2] = result
											@updatePreview!
							else
								if isSetVar
									oldName = @curExpr[2]
									isNameFirstAppear = true
									for name in *localNames
										isNameFirstAppear = false if oldName == name
									if isNameFirstAppear
										@owner\markLocalVarRename oldName,item
								button.text = item
								@curExpr[2] = item
								@updatePreview!
			@bodyMenu\addChild localVarButton
			if not @bodyMenu.activate
				localVarButton\emit "Tapped",localVarButton
				@bodyMenu.activate = true

		editGlobalVariable = ->
			itemButton = with GroupButton {
					text:@curExpr[2]
					width:math.min(200,@bodyMenu.width-20)
					height:35
				}
				.position = oVec2 @bodyMenu.width/2,
					@bodyLabel.positionY-@bodyLabel.height-10-.height/2
				\slot "Tapped",->
					GlobalPanel = require "Control.Trigger.GlobalPanel"
					filterType = if @parentExpr[1]\match "^Global"
						@parentExpr.Type
					else
						@parentExpr[3].Type
					with GlobalPanel owner:@,filterType:filterType
						\slot "Result",(globalVar)->
							itemButton.text = globalVar
							@curExpr[2] = globalVar
							@updatePreview!
			@bodyMenu\addChild itemButton
			itemButton\emit "Tapped"

		chooseItemFromScene = (itemType)->
			itemButton = with GroupButton {
					text:@curExpr[2]
					width:math.min(200,@bodyMenu.width-20)
					height:35
				}
				.position = oVec2 @bodyMenu.width/2,
					@bodyLabel.positionY-@bodyLabel.height-10-.height/2
				\slot "Tapped",->
					emit "Scene.#{ @type }.Close"
					emit "Scene.#{ @type }.Picking",{itemType,@curExpr[2]}
				\gslot "Scene.#{ @type }.Picked",(result)->
					return unless result
					itemButton.text = result
					@curExpr[2] = result
					@updatePreview!
			@bodyMenu\addChild itemButton

		pickPointFromScene = ->
			localVarButton = with GroupButton {
					text:"Pick"
					width:math.min(200,@bodyMenu.width-20)
					height:35
				}
				.position = oVec2 @bodyMenu.width/2,
					@bodyLabel.positionY-@bodyLabel.height-10-.height/2
				\slot "Tapped",->
					emit "Scene.#{ @type }.Close"
					emit "Scene.#{ @type }.Picking",{"Point",oVec2(@curExpr[2][2],@curExpr[3][2])}
				\gslot "Scene.#{ @type }.Picked",(result)->
					@curExpr[2][2] = result.x
					@curExpr[3][2] = result.y
					thread ->
						updateContent @curExprBtn.exprDef
			@bodyMenu\addChild localVarButton

		editAnimationOrLook = ->
			selectItem = (modelFile)->
				return if modelFile == ""
				items = switch @curExpr[1]
					when "Animation" then oCache.Model\getAnimationNames(modelFile) or {}
					when "Look" then oCache.Model\getLookNames(modelFile) or {}
				itemButton = with GroupButton {
						text:@curExpr[2]
						width:math.min(170,@bodyMenu.width-20)
						height:35
					}
					.position = oVec2 @bodyMenu.width/2,
						@bodyLabel.positionY-@bodyLabel.height/2-20-.height/2
					\slot "Tapped",(button)->
						with SelectionPanel {
								title:@curExpr[1]
								width:150
								items:items
								itemHeight:40
								fontSize:20
							}
							\slot "Selected",(item)->
								return unless item
								button.text = item
								@curExpr[2] = item
								@updatePreview!
				@bodyMenu\addChild itemButton
				if not @bodyMenu.activate
					itemButton\emit "Tapped",itemButton
					@bodyMenu.activate = true

			switch @parentExpr[1]
				when "CreateModel"
					selectItem @parentExpr[2][2]
				when "PlayAnimation"
					if @parentExpr[3][1] == "ModelByName"
						modelName = @parentExpr[3][2][2]
						model = editor.items[modelName]
						if model
							modelData = editor\getData model
							selectItem modelData.file
							return
					inputed = (_,textBox)->
						text = textBox.text
						@curExpr[2] = text\gsub "\"","\\\""
						@updatePreview!
					@bodyMenu\addChild with TextBox {
							x:@bodyMenu.width/2
							y:@bodyLabel.positionY-@bodyLabel.height/2-20-20
							width:260
							height:35
							fontSize:17
							limit:15
						}
						.text = tostring @curExpr[2]
						.textField\slot "InputInserted",inputed
						.textField\slot "InputDeleted",inputed

		editNumber = ->
			inputed = (_,textBox)->
				@curExpr[2] = tonumber(textBox.text) or 0
				@updatePreview!
			@bodyMenu\addChild with TextBox {
					x:@bodyMenu.width/2
					y:@bodyLabel.positionY-@bodyLabel.height/2-20-20
					width:170
					height:35
					fontSize:17
					limit:15
				}
				.text = tostring @curExpr[2]
				.textField\slot "InputInserting",(addText,textBox)->
					text = textBox.text..addText
					number = tonumber text
					addText == "\n" or number ~= nil or text == "-"
				.textField\slot "InputInserted",inputed
				.textField\slot "InputDeleted",inputed

		editString = ->
			inputed = (_,textBox)->
				text = textBox.text
				@curExpr[2] = text\gsub "\"","\\\""
				@updatePreview!
				emit "Scene.#{ @type }.ChangeName",text
			@bodyMenu\addChild with TextBox {
					x:@bodyMenu.width/2
					y:@bodyLabel.positionY-@bodyLabel.height/2-20-20
					width:260
					height:35
					fontSize:17
					limit:15
				}
				.text = tostring @curExpr[2]
				.textField\slot "InputInserted",inputed
				.textField\slot "InputDeleted",inputed

		updateContent = (exprDef)->
			@curExpr = @exprs[exprDef]
			if @curExpr
				text = exprDef.Desc
				index = 1
				text = text\gsub "%b[]",(s)->
					index += 1
					"\n\n[#{ @curExpr[index] }]\n\n"
				text = text\gsub "^%s*",""
				setBodyText text
			else
				text = exprDef.Desc
				text = text\gsub "%b[]",(s)-> "\n\n#{s}\n\n"
				text = text\gsub "^%s*",""
				setBodyText text
				@curExpr = exprDef\Create!
				@exprs[exprDef] = @curExpr

			@updatePreview!

			switch @curExpr[1]
				when "ModelType"
					chooseItemType "Model"
				when "LocalName"
					editLocalVariable @parentExpr[1]\match "Local(.*)"
				when "GlobalName"
					editGlobalVariable!
				when "Animation","Look"
					editAnimationOrLook!
				when "Point"
					pickPointFromScene!
				when "Number"
					editNumber!
				when "String","TriggerName","ActionName","NodeName","Text","InitGlobalName"
					editString!
				else
					if @curExpr.Item
						chooseItemFromScene @curExpr[1]\sub 1,-5 -- "TypeName"\sub(1,-5) == "Type"

		selectExpr = (button)->
			@curExprBtn.checked = false if @curExprBtn and @curExprBtn ~= button
			button.checked = true unless button.checked
			@curExprBtn = button
			updateContent button.exprDef

		exprDefs = TriggerDef.Types[valueType]
		exprDefSet = Set exprDefs
		groups = Set [exprDef.Group for exprDef in *exprDefs]
		groupNames = [groupName for groupName in pairs groups]
		table.sort groupNames

		allowUseLocal = @owner and (@owner.isInAction or @owner.isInCondition)

		for groupName in *groupNames
			hasGroupItem = false
			for exprDef in *TriggerDef.Groups[groupName]
				if exprDefSet[exprDef]
					-- Local variable is not allowed to appear outside the actions and conditions
					exprName = exprDef.Name
					isGetLocal = exprName\match "^Local"
					isGetGlobal = exprName\match "^Global"
					isGetVar = isGetLocal or isGetGlobal
					continue if (not allowUseLocal and isGetLocal) or (noVar and isGetVar)
					exprItem = with MenuItem {
							text:exprDef.Text or exprDef.Name
							fontSize:18
							width:180
							height:35
						}
						.exprDef = exprDef
						\slot "Tapped",selectExpr
					@exprButtons[exprDef] = exprItem
					@apiMenu\addChild exprItem
					hasGroupItem = true
			if hasGroupItem
				@catMenu\addChild with MenuItem {
						text:groupName
						fontSize:18
						width:80
						height:35
					}
					\slot "Tapped",selectGroup

		@catScrollArea\setupMenuScroll @catMenu
		@catScrollArea.viewSize = @catMenu\alignItems!
		@apiScrollArea\setupMenuScroll @apiMenu
		@apiScrollArea.viewSize = @apiMenu\alignItems!
		@bodyScrollArea\setupMenuScroll @bodyMenu

		if @curExpr
			exprItem = @exprButtons[getmetatable @curExpr]
			exprItem\makeChecked!
			selectExpr exprItem
			@apiScrollArea\scrollToPosY exprItem.positionY
			for child in *@catMenu.children
				if child.text == @curExpr.Group
					child\makeChecked!
					@curGroupBtn = child
		else
			@curGroupBtn = @catMenu.children[1]
			@curGroupBtn\makeChecked!

		if not backOnly
			@okBtn\slot "Tapped",->
				@@level -= 1
				@emit "Result",@curExpr
				@@preview.parent\removeChild @@preview,false
				@addChild @@preview,-1
				@previewItem = @@preview
				@hide!
				@prev\finishEdit! if @prev

		@backBtn\slot "Tapped",->
			@@level -= 1
			@emit "Result",@curExpr
			@hide!

		@gslot "Scene.#{ @type }.Close",-> @changeDisplay false if @visible
		@gslot "Scene.#{ @type }.Open",-> @changeDisplay true

		editor\addChild @
		@show!

	changeDisplay:(display)=>
		return unless display == @needOpen
		if display
			@needOpen = false
			with @@preview
				.parent\perform CCSequence {
					CCShow!
					oOpacity 0.3,1,oEase.OutQuad
				}
				\perform CCSequence {
					CCShow!
					oOpacity 0.3,1,oEase.OutQuad
				}
				.parent.mask.touchEnabled = true
			@perform CCSequence {
				CCShow!
				oOpacity 0.3,1,oEase.OutQuad
			}
		else
			@needOpen = true
			with @@preview
				.parent\perform CCSequence {
					oOpacity 0.3,0,oEase.OutQuad
					CCHide!
				}
				\perform CCSequence {
					oOpacity 0.3,0,oEase.OutQuad
					CCHide!
				}
				.parent.mask.touchEnabled = false
			@touchEnabled = false
			@perform CCSequence {
				oOpacity 0.3,0,oEase.OutQuad
				CCHide!
			}

	updatePreview:=>
		@emit "Result",@curExpr if @@level > 2
		@@preview\update!

	finishEdit:=>
		@@level -= 1
		@emit "Result",@curExpr
		@prev\finishEdit! if @prev
		@parent\removeChild @

	showButtons:=>
		showBtn = (btn)->
			with btn
				.scaleX = 0
				.scaleY = 0
				\perform oScale 0.3,1,1,oEase.OutQuad
		showBtn @backBtn
		showBtn @okBtn if @okBtn

	hideButtons:=>
		@okBtn\perform oScale 0.3,0,0,oEase.OutQuad if @okBtn
		@backBtn\perform oScale 0.3,0,0,oEase.OutQuad

	show:=>
		@visible = true
		@showButtons!
		if @previewItem
			with @previewItem
				.opacity = 0
				\perform oOpacity 0.3,1,oEase.OutQuad
		if @mask
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
					@bodyScrollArea.touchEnabled = true
					@catMenu.enabled = true
					@apiMenu.enabled = true
					@bodyMenu.enabled = true
					@opMenu.enabled = true
					@emit "Show"
		}

	hide:=>
		@emit "Hide"
		@catScrollArea.touchEnabled = false
		@apiScrollArea.touchEnabled = false
		@bodyScrollArea.touchEnabled = false
		@catMenu.enabled = false
		@apiMenu.enabled = false
		@bodyMenu.enabled = false
		@opMenu.enabled = false
		@hideButtons!
		@panel\perform CCSequence {
			oOpacity 0.3,0,oEase.OutQuad
			CCCall -> @parent\removeChild @
		}
		if @previewItem
			@previewItem\perform oOpacity 0.3,0,oEase.OutQuad
			@@preview = nil
		if @mask
			@mask\perform oOpacity 0.3,0,oEase.OutQuad

ExprChooser
