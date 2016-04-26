Dorothy!
GlobalPanelView = require "View.Control.Trigger.GlobalPanel"
ExprItem = require "Control.Trigger.ExprItem"
ExprChooser = require "Control.Trigger.ExprChooser"
Button = require "Control.Basic.Button"
import Expressions,SetExprMeta,ToEditText from require "Data.TriggerDef"
import Path from require "Lib.Utils"

Class GlobalPanelView,
	__init:(args)=>
		{:owner,:filterType} = args
		@curExpr = nil
		@selectedItem = nil
		@newBtn = nil
		@curIndex = nil
		@globalExpr = editor\getGlobalExpr!
		@modified = false

		selectVarItem = (exprItem)->
			@selectedItem.checked = false if @selectedItem
			@selectedItem = exprItem.checked and exprItem or nil
			if exprItem.checked
				@editMenu.visible = true
				@editMenu.transformTarget = exprItem
				@editMenu.position = oVec2 exprItem.width,0
				if filterType
					@pickBtn.visible = exprItem.expr[3].Type == filterType
				else
					@pickBtn.visible = false
				for item in *@editMenu.children
					with item
						if .visible
							.scaleX,.scaleY = 0,0
							\perform oScale 0.3,1,1,oEase.OutQuad
			else
				@editMenu.visible = false
				@editMenu.transformTarget = nil

		updatePanelSize = ->
			children = @menu.children
			items = [child for child in *children[2,]]
			table.sort items,(a,b)-> a.expr[2][2] < b.expr[2][2]
			for i = 1,#items
				item = items[i]
				item.lineNumber = i
				children[i+1] = item
				@globalExpr[i+1] = item.expr
			offset = @scrollArea.offset
			@scrollArea.offset = oVec2.zero
			size = @menu\alignItemsVertically 2
			@scrollArea.viewSize = CCSize size.width,size.height+70
			@scrollArea.offset = offset

		addNewGlobal = ->
			@modified = true
			@curExpr = Expressions.InitGlobalNumber\Create!
			table.insert @globalExpr,@curExpr
			newItem = with ExprItem {
					lineNumber:#@menu.children
					expr:@curExpr
					width:@menu.width-20
				}
				\updateText!
				\slot "Tapped",selectVarItem
			@menu\addChild newItem
			newItem\emit "Tapped",newItem
			updatePanelSize!
			@scrollArea\scrollToPosY newItem.positionY
			newItem.opacity = 0
			@initBtn\emit "Tapped"
			@schedule once ->
				sleep 0.3
				newItem.opacity = 1

		addTheNewButton = ->
			@newBtn = with Button {
					text:"<NEW>"
					width:150
					height:40
					fontName:"Arial"
					fontSize:20
				}
				.color = ccColor3 0x80ff00
				\slot "Tapped",->
					@menu\removeChild @newBtn
					addNewGlobal!
			@menu\addChild @newBtn
			updatePanelSize!

		lineNumber = 0
		for expr in *@globalExpr[2,]
			lineNumber += 1
			@menu\addChild with ExprItem {
					lineNumber:lineNumber
					expr:expr
					width:@menu.width-20
				}
				\updateText!
				\slot "Tapped",selectVarItem

		if #@globalExpr == 1
			addTheNewButton!
		else
			updatePanelSize!

		hideItem = (item)->
			item\perform CCSequence {
				oOpacity 0.3,0,oEase.OutQuad
				CCHide!
			}
		showItem = (item,opacity=1)->
			item\perform CCSequence {
				CCShow!
				oOpacity 0.3,opacity,oEase.OutQuad
			}
		@initBtn\slot "Tapped",->
			hideItem owner.panel
			hideItem owner.opMenu
			hideItem @panel
			hideItem @opMenu
			hideItem @
			@previewOwner = ExprChooser.preview.owner
			@curExpr = @selectedItem.expr
			@curIndex = @menu.children\index @selectedItem
			ExprChooser.preview.owner = @
			ExprChooser.preview\update!
			with ExprChooser {
					valueType:"GlobalInit"
					expr:@selectedItem.expr
					noVar:true
					backOnly:true
					editorType:owner.type
				}
				\slot "Result",(newExpr)->
					@modified = true
					@curExpr = newExpr
					@globalExpr[@curIndex] = newExpr
					ExprChooser.preview\update!
					@selectedItem.expr = newExpr
					@selectedItem\updateText!
					if filterType
						@pickBtn.visible = newExpr[3].Type == filterType
				\slot "Hide",->
					showItem owner.panel
					showItem owner.opMenu
					showItem @panel
					showItem @opMenu
					showItem @,0.6
					ExprChooser.preview.owner = @previewOwner
					ExprChooser.preview\update!
					updatePanelSize!

		@addBtn\slot "Tapped",addNewGlobal

		@delBtn\slot "Tapped",->
			@modified = true
			index = @menu.children\index @selectedItem
			table.remove @globalExpr,index
			item = @selectedItem
			@selectedItem.checked = false
			selectVarItem @selectedItem
			@menu\removeChild item
			index -= 1
			if index > 1
				item = @menu.children[index]
				item.checked = true
				selectVarItem item
			elseif index == 1 and #@menu.children > 1
				item = @menu.children[2]
				item.checked = true
				selectVarItem item
			else
				addTheNewButton!
			updatePanelSize!

		@pickBtn\slot "Tapped",->
			editor\saveGlobalExpr!
			@hide!
			name = @selectedItem.expr[2][2]
			name = name == "" and "InvalidName" or name
			@emit "Result",name

		@closeBtn\slot "Tapped",-> editor\saveGlobalExpr!

	hide:=>
		@__base.hide @
		if @modified
			editor\lintAllTriggers!
