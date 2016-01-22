Dorothy!
ExprChooserView = require "View.Control.Trigger.ExprChooser"
TriggerDef = require "Data.TriggerDef"
TriggerItem = require "Control.Trigger.TriggerItem"
SolidRect = require "View.Shape.SolidRect"
import Set from require "Data.Utils"

Class ExprChooserView,
	__initc:=>
		@groups = {}
		@types = {}
		for exprName,expr in pairs TriggerDef.Expressions
			expr.Name = exprName
			@groups[expr.Group] or= {}
			table.insert @groups[expr.Group],expr
			@types[expr.Type] or= {}
			table.insert @types[expr.Type],expr
			if expr.Type == "None" or expr.TypeIgnore
				@types["Action"] or= {}
				table.insert @types["Action"],expr
		for groupName,group in pairs @groups
			table.sort group,(a,b)-> a.Name < b.Name
		for typeName,typeList in pairs @types
			table.sort typeList,(a,b)-> a.Name < b.Name
		@groupNames = [groupName for groupName,_ in pairs @groups]
		table.sort @groupNames

	__init:(args)=>
		{:valueType} = args
		@exprButtons = {}
		@valueButtons = {}

		curGroupBtn = nil
		selectGroup = (button)->
			curGroupBtn.checked = false unless curGroupBtn == button
			button.checked = true unless button.checked
			curGroupBtn = button
			groupName = button.text
			exprItem = nil
			for item in *@apiMenu.children
				expr = item.expr
				if expr.Group == groupName
					exprItem = @exprButtons[expr.Name]
					break
			@apiScrollArea\scrollToPosY exprItem.positionY
			thread ->
				sleep 0.3
				exprItem\glow!

		colorBodyText = (colored)->
			startIndex = 1
			text = @bodyLabel.text
			color = ccColor3 colored and 0xff0080 or 0xffffff
			if colored
				for btn in *@valueButtons
					@bodyMenu\removeChild btn
				@valueButtons = {}
			labelPos = @bodyLabel.position-oVec2(0,@bodyLabel.height)
			while startIndex
				startIndex = text\find "[",startIndex,true
				if startIndex
					stopIndex = text\find "]",startIndex,true
					for index = startIndex,stopIndex
						child = @bodyLabel\getChar index
						child.color = color
					if colored
						char = @bodyLabel\getChar startIndex
						charPoint = oVec2 char.width,char.height
						lower = labelPos+char.position-charPoint*char.anchor
						char = @bodyLabel\getChar stopIndex
						upper = labelPos+char.position+charPoint*(oVec2(1,1)-char.anchor)
						itemText = text\sub startIndex,stopIndex
						menuItem = with CCMenuItem!
							.contentSize = CCSize upper.x-lower.x,upper.y-lower.y
							.position = (upper+lower)/2
							--\addChild (SolidRect width:.width,height:.height,color:0x2200ffff),-1
							\slot "Tapped",-> print itemText
						table.insert @valueButtons,menuItem
						@bodyMenu\addChild menuItem
					startIndex = stopIndex

		setBodyText = (text)->
			text = text\gsub "%b[]",(s)-> "\n\n[( ( ( ( ( 1 + 1 ) + 99876 ) / 35 ) % 10 ) + GlobalNumber( \"var\" ) )]\n\n"
			text = text\gsub "^%s*",""
			colorBodyText false
			@bodyLabel.text = text
			colorBodyText true

		curExprBtn = nil
		selectExpr = (button)->
			curExprBtn.checked = false unless curExprBtn == button
			button.checked = true unless button.checked
			curExprBtn = button
			expr = button.expr
			setBodyText expr.Desc

		exprList = @types[valueType]
		groups = {}
		for expr in *exprList
			groups[expr.Group] = true
		groupList = {}
		for groupName,_ in pairs groups
			table.insert groupList,groupName
		table.sort groupList
		exprSet = Set exprList

		for groupName in *groupList
			@catMenu\addChild with TriggerItem {
						text:groupName
						fontSize:18
						width:80
						height:30
					}
				\slot "Tapped",selectGroup
			for expr in *@@groups[groupName]
				if exprSet[expr]
					exprItem = with TriggerItem {
								text:expr.Name
								fontSize:18
								width:130
								height:30
							}
						.expr = expr
						\slot "Tapped",selectExpr
					@exprButtons[expr.Name] = exprItem
					@apiMenu\addChild exprItem

		curGroupBtn = @catMenu.children[1]
		curGroupBtn.checked = true

		curExprBtn = @apiMenu.children[1]
		curExprBtn\emit "Tapped",curExprBtn

		@catScrollArea\setupMenuScroll @catMenu
		@catScrollArea.viewSize = @catMenu\alignItems!
		@apiScrollArea\setupMenuScroll @apiMenu
		@apiScrollArea.viewSize = @apiMenu\alignItems!
		
		@okBtn\slot "Tapped",-> @hide!
		@show!

	show:=>
		@visible = true
		with @okBtn
			.scaleX = 0
			.scaleY = 0
			\perform oScale 0.3,1,1,oEase.OutBack
		with @panel
			.opacity = 0
			.scaleX = 0
			.scaleY = 0
			\perform CCSequence {
				CCSpawn {
					oOpacity 0.3,1,oEase.OutQuad
					oScale 0.3,1,1,oEase.OutBack
				}
				CCCall ->
					@catScrollArea.touchEnabled = true
					@apiScrollArea.touchEnabled = true
					@bodyScrollArea.touchEnabled = true
					@catMenu.enabled = true
					@apiMenu.enabled = true
					@bodyMenu.enabled = true
					@opMenu.enabled = true
		}

	hide:=>
		@catScrollArea.touchEnabled = false
		@apiScrollArea.touchEnabled = false
		@bodyScrollArea.touchEnabled = false
		@catMenu.enabled = false
		@apiMenu.enabled = false
		@bodyMenu.enabled = false
		@opMenu.enabled = false
		@okBtn\perform oScale 0.3,0,0,oEase.InBack
		@panel\perform CCSequence {
			CCSpawn {
				oOpacity 0.3,0,oEase.OutQuad
				oScale 0.3,0,0,oEase.InBack
			}
			CCCall -> @parent\removeChild @
		}
