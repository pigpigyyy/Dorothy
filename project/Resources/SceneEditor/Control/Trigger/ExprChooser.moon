Dorothy!
ExprChooserView = require "View.Control.Trigger.ExprChooser"
TriggerDef = require "Data.TriggerDef"
TriggerItem = require "Control.Trigger.TriggerItem"
SolidRect = require "View.Shape.SolidRect"
import Set from require "Data.Utils"

local ExprChooser
ExprChooser = Class
	__initc:=>
		@level = 1

	__partial:(args)=>
		{:width,:height} = CCDirector.winSize
		args.width or= width*0.8
		args.height or= height*0.6
		args.level = @@level
		@@level += 1
		ExprChooserView args

	__init:(args)=>
		{:valueType,:expr} = args
		@exprButtons = {}
		@valueButtons = {}
		@exprs = {}
		@curGroupBtn = nil
		@curExprBtn = nil
		@curExpr = expr
		@exprs[getmetatable expr] = expr if expr

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
			for btn in *@valueButtons
				@bodyMenu\removeChild btn
			@valueButtons = {}
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
								exprDef = @curExprBtn.exprDef
								with ExprChooser valueType:@curExpr[index].Type,expr:@curExpr[index]
									\slot "Show",-> @visible = false
									\slot "Hide",-> @visible = true
									\slot "Result",(expr)->
										if expr
											@curExpr[index] = expr
											updateContent exprDef
						table.insert @valueButtons,menuItem
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

		@curGroupBtn = @catMenu.children[1]
		@curGroupBtn\makeChecked!

		@catScrollArea\setupMenuScroll @catMenu
		@catScrollArea.viewSize = @catMenu\alignItems!
		@apiScrollArea\setupMenuScroll @apiMenu
		@apiScrollArea.viewSize = @apiMenu\alignItems!
		@bodyScrollArea\setupMenuScroll @bodyMenu,oVec2(0,1)

		if @curExpr
			exprItem = @exprButtons[getmetatable @curExpr]
			exprItem\makeChecked!
			selectExpr exprItem
			@apiScrollArea\scrollToPosY exprItem.positionY

		@okBtn\slot "Tapped",->
			@@level -= 1
			@emit "Result",@curExpr
			@hide!

		editor\addChild @
		@show!

	show:=>
		@visible = true
		with @okBtn
			.scaleX = 0
			.scaleY = 0
			\perform oScale 0.3,1,1,oEase.OutBack
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
		@okBtn\perform oScale 0.3,0,0,oEase.InBack
		@panel\perform CCSequence {
			oOpacity 0.3,0,oEase.OutQuad
			CCCall -> @parent\removeChild @
		}

ExprChooser
