Dorothy!
ExprEditorView = require "View.Control.Trigger.ExprEditor"
ExprItem = require "Control.Trigger.ExprItem"
ExprChooser = require "Control.Trigger.ExprChooser"
PopupPanel = require "Control.Basic.PopupPanel"
MessageBox = require "Control.Basic.MessageBox"
TriggerDef = require "Data.TriggerDef"
import Path from require "Lib.Utils"

Class ExprEditorView,
	__init:=>
		@type = "AINode"
		@extension = ".node"

		@exprData = nil
		@filename = nil
		@asyncLoad = false

		createExprItem = (_,...)-> @createExprItem ...

		@newName = nil
		@modified = false

		@codeMode = (CCUserDefault.TriggerMode == "Code")

		for child in *@editMenu.children
			child.scale = oScale 0.3,1,1,oEase.OutQuad

		@_selectedExprItem = nil
		@changeExprItem = (button)->
			@_selectedExprItem.checked = false if @_selectedExprItem
			@_selectedExprItem = button.checked and button or nil
			if button.checked
				if @_selectedExprItem.errorInfo
					@errorInfoBtn\display true
				else
					@errorInfoBtn\display false
				@editMenu.visible = true
				@editMenu.transformTarget = button
				@editMenu.position = oVec2 button.width,0
				{:expr,:index,:parentExpr} = @_selectedExprItem
				subExprItem = false
				rootItem = switch expr[1]
					when "ConditionNode" then true
					else false
				edit = not subExprItem
				insert = if rootItem then false
					elseif subExprItem then false
					elseif #@triggerMenu.children >= 999 then false
					else true
				add = switch expr[1]
					when "ConditionNode" then true
					else
						if rootItem or #@triggerMenu.children >= 999 then false
						else true
				del = if rootItem then false
					elseif parentExpr and
						parentExpr[1] == "ConditionNode" and
						#parentExpr == 2
						false
					else
						not subExprItem
				mode = expr[1] == "ConditionNode"
				up = index and index > 2 and not subExprItem and not rootItem
				down = index and index < #parentExpr and not subExprItem and not rootItem
				buttons = for v,k in pairs {:edit,:insert,:add,:del,:up,:down,:mode}
					if k then v
					else continue
				@showEditButtons buttons
			else
				@errorInfoBtn\display false
				@editMenu.visible = false
				@editMenu.transformTarget = nil

		@setupMenuScroll @triggerMenu

		mode = (code,text)-> TriggerDef.CodeMode and code or text

		nextExpr = (parentExpr,index,indent)->
			expr = index and parentExpr[index] or parentExpr
			switch expr[1]
				when "ConditionNode"
					if TriggerDef.CodeMode
						@createExprItem "return",indent
						with @createExprItem tostring(expr),indent,expr
							.itemType = "Start"
							.actionExpr = expr
					else
						@createExprItem "AI Condition Node",indent
						with @createExprItem tostring(expr),indent+1,expr
							.itemType = "Start"
							.actionExpr = expr
						indent += 1
					for i = 3,#expr
						nextExpr expr,i,indent+1
					with @createExprItem mode("end )"," "),indent
						.itemType = "End"
				else
					@createExprItem tostring(expr),indent,expr,parentExpr,index

		@nextExpr = (parentExpr,indent,index)=>
			nextExpr parentExpr,index,indent -- params order changed

		addNewItem = (selectedExprItem,indent,parentExpr,index,delExpr=true,insertAfter=false)->
			-- update triggerMenu
			children = @triggerMenu.children
			itemIndex = children\index selectedExprItem
			startIndex = #children+1
			@nextExpr parentExpr,indent,index
			stopIndex = #children
			-- get new items
			newItems = [child for child in *children[startIndex,stopIndex]]
			-- unselect item
			targetItem = selectedExprItem
			selectedExprItem.checked = false
			@.changeExprItem selectedExprItem
			-- remove old expr items
			if delExpr
				@triggerMenu\removeChild targetItem
			elseif insertAfter
				itemIndex += 1
			-- insert new expr items in right position
			for item in *newItems
				children\insert item,itemIndex
				itemIndex += 1
			-- separate condition exprs by comma
			if not delExpr and
				parentExpr[1] == "ConditionNode" and
				selectedExprItem.expr[1] ~= "ConditionNode"
				selectedExprItem\updateText!
			-- remove duplicated new exprs
			for i = startIndex,stopIndex
				children\removeLast!
			-- update items position
			offset = @offset
			@offset = oVec2.zero
			@viewSize = @triggerMenu\alignItems 0
			@offset = offset
			-- select new expr item
			newItems[1].checked = true
			@.changeExprItem newItems[1]
			@scrollToPosY newItems[1].positionY
			@notifyEdit!

		@editBtn\slot "Tapped",->
			selectedExprItem = @_selectedExprItem
			if selectedExprItem
				{:expr,:parentExpr,:index} = selectedExprItem
				valueType = (expr.TypeIgnore or expr.Type == "None") and "Action" or expr.Type
				with ExprChooser {
						valueType:valueType
						expr:expr
						parentExpr:parentExpr
						owner:@
					}
					\slot "Result",(newExpr)->
						if parentExpr
							parentExpr[index] = newExpr
							addNewItem selectedExprItem,selectedExprItem.indent,parentExpr,index
						elseif expr[1] == "ConditionNode"
							if @newName
								oldFileFullname = editor.gameFullPath..@filename
								filePath = Path.getPath oldFileFullname
								newFileFullname = filePath..@newName..@extension
								return if oldFileFullname == newFileFullname
								if oContent\exist newFileFullname
									MessageBox text:"Node Name Exist!",okOnly:true
									oldName = Path.getName @filename
									@triggerName = oldName
									emit "Scene.#{ @type }.ChangeName",oldName
								elseif not Path.isValid Path.getFilename newFileFullname
									MessageBox text:"Invalid Name!",okOnly:true
									oldName = Path.getName @filename
									@triggerName = oldName
									emit "Scene.#{ @type }.ChangeName",oldName
								else
									oContent\saveToFile newFileFullname,TriggerDef.ToEditText @exprData
									oContent\remove oldFileFullname
									@filename = Path.getPath(@filename)..@newName..@extension
								@newName = nil
							selectedExprItem.text = tostring expr
							@notifyEdit!

		insertNewExpr = (after)-> ->
			selectedExprItem = @_selectedExprItem
			{:expr,:indent,:parentExpr,:index} = selectedExprItem
			parentExpr or= expr
			if after
				index += 1
			else
				index or= #parentExpr
			valueType = switch parentExpr[1]
				when "ConditionNode" then "Boolean"
				else "Action"
			with ExprChooser {
					valueType:valueType
					parentExpr:parentExpr
					owner:@
				}
				\slot "Result",(newExpr)->
					return unless newExpr
					table.insert parentExpr,index,newExpr
					addNewItem selectedExprItem,indent,parentExpr,index,false,after

		@insertBtn\slot "Tapped",insertNewExpr false
		@addBtn\slot "Tapped",insertNewExpr true

		@delBtn\slot "Tapped",->
			selectedExprItem = @_selectedExprItem
			{:expr,:parentExpr,:index} = selectedExprItem
			selectedExprItem.checked = false
			@.changeExprItem selectedExprItem
			table.remove parentExpr,index
			children = @triggerMenu.children
			startIndex = children\index(selectedExprItem)
			@triggerMenu\removeChild selectedExprItem
			offset = @offset
			@offset = oVec2.zero
			@viewSize = @triggerMenu\alignItems 0
			@offset = offset
			prevItem = children[startIndex-1]
			prevItem.checked = true if prevItem.expr
			@.changeExprItem prevItem
			if prevItem.expr and
				prevItem.expr[1] ~= "ConditionNode" and
				prevItem.parentExpr and
				prevItem.parentExpr[1] == "ConditionNode"
				prevItem\updateText!
			@notifyEdit!

		@upBtn\slot "Tapped",->
			selectedExprItem = @_selectedExprItem
			{:expr,:parentExpr,:index} = selectedExprItem
			selectedExprItem.checked = false
			@.changeExprItem selectedExprItem
			table.remove parentExpr,index
			table.insert parentExpr,index-1,expr
			children = @triggerMenu.children
			startIndex = children\index(selectedExprItem)
			if parentExpr[1] == "ConditionNode"
				children[startIndex-1]\updateText!
				selectedExprItem\updateText!
			prevIndex = startIndex-1
			children\remove selectedExprItem
			children\insert selectedExprItem,prevIndex
			offset = @offset
			@offset = oVec2.zero
			@viewSize = @triggerMenu\alignItems 0
			@offset = offset
			selectedExprItem.checked = true
			@.changeExprItem selectedExprItem
			@scrollToPosY selectedExprItem.positionY
			@notifyEdit!

		@downBtn\slot "Tapped",->
			selectedExprItem = @_selectedExprItem
			{:expr,:parentExpr,:index} = selectedExprItem
			selectedExprItem.checked = false
			@.changeExprItem selectedExprItem
			table.remove parentExpr,index
			table.insert parentExpr,index+1,expr
			children = @triggerMenu.children
			startIndex = children\index(selectedExprItem)
			if parentExpr[1] == "ConditionNode"
				children[startIndex+1]\updateText!
				selectedExprItem\updateText!
			nextIndex = startIndex+1
			nextItem = children[nextIndex]
			nextItems = {nextItem}
			for item in *nextItems
				children\remove item
				children\insert item,startIndex
				startIndex += 1
			offset = @offset
			@offset = oVec2.zero
			@viewSize = @triggerMenu\alignItems 0
			@offset = offset
			selectedExprItem.checked = true
			@.changeExprItem selectedExprItem
			@scrollToPosY selectedExprItem.positionY
			@notifyEdit!

		@modeBtn\slot "Tapped",->
			thread ->
				sleep 0.3
				@codeMode = not @codeMode
				CCUserDefault.TriggerMode = @codeMode and "Code" or "Text"
				TriggerDef.CodeMode = @codeMode
				@loadExpr @exprData
				@modeBtn\schedule once ->
					wait -> @asyncLoad
					for child in *@triggerMenu.children
						if child.expr == @exprData
							child.checked = true
							@.changeExprItem child
							break

		displayButton = (button,display)->
			if display
				with button
					.visible = true
					.scaleX,.scaleY = 0,0
					\perform oScale 0.3,1,1,oEase.OutQuad
			elseif button.visible
				button\perform CCSequence {
					oScale 0.3,0,0,oEase.InBack
					CCHide!
				}

		with @errorBtn
			.visible = false
			.color = ccColor3 0xff0080
			\slot "Tapped",->
				item = @errorBtn.errorItems[@errorBtn.currentIndex]
				if item.checked
					@errorBtn.currentIndex %= #@errorBtn.errorItems
					@errorBtn.currentIndex += 1
					item = @errorBtn.errorItems[@errorBtn.currentIndex]
				if @errorBtn.currentIndex > #@errorBtn.errorItems
					@errorBtn.currentIndex = 1
				else
					item.checked = true
					@.changeExprItem item
				@scrollToPosY item.positionY
				@errorBtn.currentIndex %= #@errorBtn.errorItems
				@errorBtn.currentIndex += 1
			.display = displayButton

		with @errorInfoBtn
			.visible = false
			.color = ccColor3 0xff0080
			.display = displayButton
			\slot "Tapped",->
				{:width,:height} = CCDirector.winSize
				panelWidth = 350
				with PopupPanel {
						x:width/2
						y:height/2
						width:panelWidth
						height:300
					}
					.menu\addChild with CCNode!
						.contentSize = CCSize panelWidth-20,40
						\addChild with CCLabelTTF "Error In Line #{@_selectedExprItem.lineNumber}","Arial",24
							.color = ccColor3 0x00ffff
							.position = oVec2 (panelWidth-20)/2,10
					.menu\addChild with ExprItem text:@_selectedExprItem.errorInfo,width:panelWidth-40
						.enabled = false
					.scrollArea.viewSize = .menu\alignItemsVertically!

		checkReload = ->
			codeMode = (CCUserDefault.TriggerMode == "Code")
			if @codeMode ~= codeMode
				@codeMode = codeMode
				@loadExpr @exprData
			else
				@lintCode!

		@slot "Entered",checkReload

		@gslot "Scene.#{ @type }.ChangeName",(newName)-> @newName = newName
		@gslot "Scene.#{ @type }.Open",checkReload

	notifyEdit:=>
		children = @triggerMenu.children
		for i = 1,#children
			children[i].lineNumber = i
		@modified = true
		@lintCode!
		emit "Scene.#{ @type }.Edited",@filename

	createExprItem:(text,indent,expr,parentExpr,index)=>
		children = @triggerMenu.children
		lastItem = children and children.last or nil
		lineNumber = children and #children+1 or 1
		exprItem = with ExprItem {
				:indent
				:text
				:expr
				:parentExpr
				:index
				:lineNumber
				width:@triggerMenu.width
			}
			.position = lastItem and
				(lastItem.position-oVec2(0,lastItem.height/2+.height/2)) or
				oVec2(@triggerMenu.width/2,@triggerMenu.height-.height/2)+@offset
			\slot "Tapped",@changeExprItem if expr
		@triggerMenu\addChild exprItem
		{:width,:height} = @viewSize
		@viewSize = CCSize width,@height+@offset.y-exprItem.positionY+exprItem.height/2
		sleep! if @asyncLoad
		exprItem

	loadExpr:(arg)=>
		if @_selectedExprItem
			@_selectedExprItem.checked = false
			@.changeExprItem @_selectedExprItem
		@exprData = switch type arg
			when "table" then arg
			when "string"
				@filename = arg
				TriggerDef.SetExprMeta dofile arg
		@view\schedule once ->
			@triggerMenu.enabled = false
			@triggerMenu\removeAllChildrenWithCleanup!
			@offset = oVec2.zero
			@asyncLoad = true
			@nextExpr @exprData,0
			@asyncLoad = false
			@triggerMenu.enabled = true
			@lintCode!
		@exprData

	codeMode:property => @_codeMode,
		(value)=>
			@_codeMode = value
			@modeBtn.text = value and "Text" or "Code"
			@modeBtn.color = ccColor3 value and 0xffff88 or 0xff88cc

	save:=>
		triggerText = TriggerDef.ToEditText @exprData
		oContent\saveToFile editor.gameFullPath..@filename,triggerText
		if not @isCodeHasError
			codeFile = editor.gameFullPath..@filename
			codeFile = Path.getPath(codeFile)..Path.getName(codeFile)..".lua"
			triggerCode = TriggerDef.ToCodeText @exprData
			oContent\saveToFile codeFile,triggerCode

	isInAction:property => false
	isInCondition:property => true
	isInEvent:property => false

	getPrevLocalVars:(targetType)=> {}

	markLocalVarRename:(fromName,toName)=> nil

	showEditButtons:(names)=>
		buttonSet = {@["#{ name }Btn"],true for name in *names}
		posX = @editMenu.width-35-(buttonSet[@modeBtn] and 60 or 0)
		for i = #@editMenu.children,1,-1
			child = @editMenu.children[i]
			if buttonSet[child]
				child.positionX = posX
				child.visible = true
				child.scaleX = 0
				child.scaleY = 0
				child\perform child.scale
				posX -= 60
			else
				child.visible = false

	triggerName:property => @exprData[2][2],
		(value)=> @exprData[2][2] = value

	enabled:property => @touchEnabled,
		(value)=>
			@touchEnabled = value
			@triggerMenu.enabled = value
			@editMenu.enabled = value

	isCodeHasError:property => #@errorBtn.errorItems > 0

	lintCode:=>
		return unless @triggerMenu.children
		@errorBtn.errorItems = {}
		@errorBtn.currentIndex = 1

		locals = {}
		globals = {expr[2][2],expr[3].Type for expr in *editor\getGlobalExpr![2,]}
		lintFunc = TriggerDef.GetLintFunction locals,globals

		checkError = (item)->
			if item.expr
				errorInfo = lintFunc item.expr,item.parentExpr,item.itemType
				if errorInfo == ""
					item\markError false
				else
					item\markError true,errorInfo
					table.insert @errorBtn.errorItems,item
			elseif item.itemType == "End"
				lintFunc nil,nil,"End"

		for item in *@triggerMenu.children
			checkError item

		@errorBtn\display #@errorBtn.errorItems > 0
		@errorInfoBtn\display false if #@errorBtn.errorItems == 0

		if @_selectedExprItem and @_selectedExprItem.errorInfo
			@errorInfoBtn\display true

		if @isCodeHasError
			codeFile = editor.gameFullPath..@filename
			codeFile = Path.getPath(codeFile)..Path.getName(codeFile)..".lua"
			oContent\remove codeFile if oContent\exist codeFile
