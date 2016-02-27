Dorothy!
ExprChooserView = require "View.Control.Trigger.ExprChooser"
TriggerDef = require "Data.TriggerDef"
TriggerItem = require "Control.Trigger.TriggerItem"
SolidRect = require "View.Shape.SolidRect"
Button = require "Control.Basic.Button"
GroupButton = require "Control.Basic.GroupButton"
SelectionPanel = require "Control.Basic.SelectionPanel"
InputBox = require "Control.Basic.InputBox"
MessageBox = require "Control.Basic.MessageBox"
TextBox = require "Control.Basic.TextBox"
import Set from require "Data.Utils"

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
		{:valueType,:expr,:parentExpr,:owner,:prev} = args
		@exprButtons = {}
		@exprs = {}
		@curGroupBtn = nil
		@curExprBtn = nil
		@curExpr = expr
		@parentExpr = parentExpr
		@owner = owner
		@prev = prev
		@exprs[getmetatable expr] = expr if expr
		if args.level == 1
			@@preview = with @previewItem
				.owner = @
				\update!

		@backBtn\slot "TapBegan",nil
		@okBtn\slot "TapBegan",nil

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
						for i = startIndex,stopIndex
							child = @bodyLabel\getChar i
							child.color = color
						char = @bodyLabel\getChar startIndex
						charPoint = oVec2 char.width,char.height
						upperY = (labelPos+char.position+charPoint*(oVec2(1,1)-char.anchor)).y+10
						char = @bodyLabel\getChar stopIndex
						lowerY = (labelPos+char.position-charPoint*char.anchor).y-10
						itemText = text\sub startIndex,stopIndex
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
										prev:@
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
				when "LocalName"
					switch @parentExpr[1]
						when "SetLocalNumber","LocalNumber"
							isSetVar = @parentExpr[1] == "SetLocalNumber"
							localNames = @owner\getPrevLocalVars "Number"
							table.insert localNames,"<NEW>" if isSetVar
							localVarButton = with GroupButton {
									text:@curExpr[2]
									width:math.min(170,@bodyMenu.width-20)
									height:35
								}
								.position = oVec2 @bodyMenu.width/2,
									@bodyLabel.positionY-@bodyLabel.height/2-20-.height/2
								\slot "Tapped",(button)->
									with SelectionPanel {
											title:"Select Name"
											width:150
											items:localNames
											itemHeight:35
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
															oldName = @curExpr[2]
															isNameFirstAppear = true
															for name in *localNames
																isNameFirstAppear = false if oldName == name
																if name == result
																	MessageBox text:"Name Exist!",okOnly:true
																	return
															if isNameFirstAppear and oldName ~= "invalidName"
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
				when "Number"
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
				when "String","TriggerName"
					inputed = (_,textBox)->
						text = textBox.text
						@curExpr[2] = text
						@updatePreview!
						if @curExpr[1] == "TriggerName"
							emit "Scene.Trigger.ChangeName",text
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

		isAction = @owner\isInActions!

		for groupName in *groupNames
			@catMenu\addChild with TriggerItem {
					text:groupName
					fontSize:18
					width:80
					height:35
				}
				\slot "Tapped",selectGroup
			for exprDef in *TriggerDef.Groups[groupName]
				if exprDefSet[exprDef]
					-- LocalNumber is not allowed to appear outside the actions
					continue if not isAction and exprDef.Name == "LocalNumber"
					exprItem = with TriggerItem {
							text:exprDef.Name
							fontSize:18
							width:180
							height:35
						}
						.exprDef = exprDef
						\slot "Tapped",selectExpr
					@exprButtons[exprDef] = exprItem
					@apiMenu\addChild exprItem

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

		editor\addChild @
		@show!

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
		showBtn @okBtn

	hideButtons:=>
		@okBtn\perform oScale 0.3,0,0,oEase.OutQuad
		@backBtn\perform oScale 0.3,0,0,oEase.OutQuad

	show:=>
		@visible = true
		@showButtons!
		if @previewItem
			with @previewItem
				.opacity = 0
				\perform oOpacity 0.3,1,oEase.OutQuad
		if @mask
			@mask\perform oOpacity 0.3,1,oEase.OutQuad
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
