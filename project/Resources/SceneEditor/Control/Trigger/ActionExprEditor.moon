Dorothy!
ExprEditorView = require "View.Control.Trigger.ExprEditor"
TriggerExpr = require "Control.Trigger.TriggerExpr"
ExprChooser = require "Control.Trigger.ExprChooser"
PopupPanel = require "Control.Basic.PopupPanel"
MessageBox = require "Control.Basic.MessageBox"
TriggerDef = require "Data.TriggerDef"
import Path from require "Data.Utils"

Args = action:"Action"

VarScope = Class
	__init:(triggerMenu,createExprItem)=>
		@createExprItem = createExprItem
		@triggerMenu = triggerMenu
		@actionItem = nil
		@localVarItem = nil
		@locals = nil
		@localSet = nil
		@localVarFrom = nil
		@localVarTo = nil

	clear:=>
		@actionItem = nil
		@localVarItem = nil
		@locals = {}
		@localSet = {}

	getLocalVarText:=>
		if TriggerDef.CodeMode
			"local "..table.concat(@locals,", ")
		else
			"Declare "..table.concat(@locals,", ").."."

	createLocalVarItem:=>
		indent = @actionItem.indent+1
		localVarItem = with @createExprItem @getLocalVarText!,indent
			.positionY = @actionItem.positionY-@actionItem.height/2-.height/2
		children = @triggerMenu.children
		index = children\index(@actionItem)+1
		children\removeLast!
		children\insert localVarItem,index
		localVarItem

	refreshLocalVars:=>
		if @actionItem
			nextExpr = (expr)->
				return unless "table" == type expr
				switch expr[1]
					when "SetLocal"
						assignExpr = expr[2]
						varType = assignExpr[1]\sub 9,-1
						varName = assignExpr[2][2]
						if varName ~= "InvalidName"
							if not Args[varName]
								if not @localSet[varName]
									table.insert @locals,varName
								@localSet[varName] = varType
					else
						for i = 2,#expr
							nextExpr expr[i]
			@locals = {}
			@localSet = {}
			nextExpr @actionItem.expr
			if @localVarItem
				if #@locals > 0
					@localVarItem.text = @getLocalVarText!
				else
					@localVarItem.parent\removeChild @localVarItem
					@localVarItem = nil
			else
				if #@locals > 0
					@localVarItem = @createLocalVarItem!
		if @localVarFrom
			@renameLocalVar @localVarFrom,@localVarTo
			@localVarFrom,@localVarTo = nil,nil

	renameLocalVar:(fromName,toName)=>
		nextExpr = (expr)->
			return false unless "table" == type expr
			renamed = false
			switch expr[1]
				when "Action"
					return false
				when "LocalName"
					if expr[2] == fromName
						expr[2] = toName
						renamed = true
			for i = 2,#expr
				if nextExpr expr[i]
					renamed = true
			renamed
		children = @triggerMenu.children
		startIndex = children\index(@actionItem)+1
		indent = @actionItem.indent
		for item in *children[startIndex,]
			break if item.indent == indent
			if item.expr and nextExpr item.expr
				item.text = tostring item.expr

Class ExprEditorView,
	__init:(args)=>
		@type = "Action"

		@exprData = nil
		@filename = nil
		@asyncLoad = false

		@availableItem = nil
		@runItem = nil
		@stopItem = nil

		@currentScope = nil
		createExprItem = (_,...)-> @createExprItem ...
		@runScope = VarScope @triggerMenu,createExprItem
		@stopScope = VarScope @triggerMenu,createExprItem

		@newActionName = nil
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
				@currentScope = switch (parentExpr or expr)[1]
					when "Run" then @runScope
					when "Stop" then @stopScope
					else nil
				subExprItem = switch @_selectedExprItem.itemType
					when "Mid","End" then true
					else false
				rootItem = switch expr[1]
					when "UnitAction","Available","Run","Stop" then true
					else
						if parentExpr then parentExpr[1] == "UnitAction"
						else false
				edit = not subExprItem
				insert = if rootItem then false
					elseif subExprItem then false
					elseif #@triggerMenu.children >= 999 then false
					else true
				add = switch expr[1]
					when "UnitAction" then false
					when "Available","Run","Stop" then true
					else
						if rootItem or #@triggerMenu.children >= 999 then false
						else true
				del = if rootItem then false
					elseif parentExpr and
						parentExpr[1] == "Available" and
						#parentExpr == 2
						false
					else
						not subExprItem
				mode = expr[1] == "UnitAction"
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
				when "UnitAction"
					if TriggerDef.CodeMode
						@createExprItem "return",indent
						@createExprItem tostring(expr),indent,expr
					else
						@createExprItem "Unit Action",indent
						@createExprItem tostring(expr),indent+1,expr
					for i = 3,#expr
						nextExpr expr,i,indent+1
					@createExprItem mode(")"," "),indent
				when "Available"
					@availableItem = with @createExprItem mode(tostring(expr),"Available"),indent,expr
						.itemType = "Start"
						.actionExpr = expr
					for i = 2,#expr
						nextExpr expr,i,indent+1
					with @createExprItem mode("end ),"," "),indent
						.itemType = "End"
				when "Run"
					@runScope.actionItem = with @createExprItem mode(tostring(expr),"Run"),indent,expr
						.itemType = "Start"
						.actionExpr = expr
					@currentScope = @runScope
					children = @triggerMenu.children
					index = #children+1
					for i = 2,#expr
						nextExpr expr,i,indent+1
					with @runScope
						if #.locals > 0
							.localVarItem = \createLocalVarItem!
							.localVarItem.lineNumber = index
							moveY = .localVarItem.height
							start = index+1
							stop = #children
							for i = start,stop
								child = children[i]
								child.lineNumber = i
								child.positionY -= moveY
					with @createExprItem mode("end ),"," "),indent
						.itemType = "End"
				when "Stop"
					@stopScope.actionItem = with @createExprItem mode(tostring(expr),"Stop"),indent,expr
						.itemType = "Start"
						.actionExpr = expr
					@currentScope = @stopScope
					children = @triggerMenu.children
					index = #children+1
					for i = 2,#expr
						nextExpr expr,i,indent+1
					with @stopScope
						if #.locals > 0
							.localVarItem = \createLocalVarItem!
							.localVarItem.lineNumber = index
							moveY = .localVarItem.height
							start = index+1
							stop = #children
							for i = start,stop
								child = children[i]
								child.lineNumber = i
								child.positionY -= moveY
					with @createExprItem mode("end )"," "),indent
						.itemType = "End"
				when "If"
					with @createExprItem tostring(expr),indent,expr,parentExpr,index
						.itemType = "Start"
						.actionExpr = expr[3]
					for i = 2,#expr[3]
						nextExpr expr[3],i,indent+1
					with @createExprItem mode("else","Else do."),indent,expr,parentExpr,index
						.itemType = "Mid"
						.actionExpr = expr[4]
					for i = 2,#expr[4]
						nextExpr expr[4],i,indent+1
					with @createExprItem mode("end","End."),indent,expr,parentExpr,index
						.itemType = "End"
				when "Loopi"
					with @createExprItem tostring(expr),indent,expr,parentExpr,index
						.itemType = "Start"
						.actionExpr = expr[5]
					for i = 2,#expr[5]
						nextExpr expr[5],i,indent+1
					with @createExprItem mode("end","End."),indent,expr,parentExpr,index
						.itemType = "End"
				when "SetLocal"
					assignExpr = expr[2]
					exprName = assignExpr[1]
					varType = exprName\sub 9,-1
					varName = assignExpr[2][2]
					if varName ~= "InvalidName"
						if not (@exprData[4][2].Args and @exprData[4][2].Args[varName])
							with @currentScope
								if not .localSet[varName]
									table.insert .locals,varName
								.localSet[varName] = varType
					@createExprItem tostring(expr),indent,expr,parentExpr,index
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
			targetExpr = targetItem.expr
			selectedExprItem.checked = false
			@.changeExprItem selectedExprItem
			-- remove old expr items
			if delExpr
				if targetExpr.MultiLine
					endSearch = false
					targetItems = for childItem in *children[itemIndex,]
						break if endSearch
						if childItem.expr == targetExpr and childItem.itemType == "End"
							endSearch = true
							childItem
						childItem
					for item in *targetItems
						@triggerMenu\removeChild item
				else
					@triggerMenu\removeChild targetItem
			elseif insertAfter
				currentType = selectedExprItem.itemType
				if targetExpr.MultiLine and currentType ~= "End"
					switch currentType
						when "Start","Mid"
							itemIndex += 1
					for i = itemIndex,#children
						childItem = children[i]
						isLineStop = switch childItem.itemType
							when "End","Mid" then true
							else false
						if childItem.expr == targetExpr and isLineStop
							itemIndex = i
							break
				else
					itemIndex += 1
			-- insert new expr items in right position
			for item in *newItems
				children\insert item,itemIndex
				itemIndex += 1
			-- separate condition exprs by comma
			if not delExpr and
				parentExpr[1] == "Available" and
				selectedExprItem.expr[1] ~= "Available"
				selectedExprItem\updateText!
			-- remove duplicated new exprs
			for i = startIndex,stopIndex
				children\removeLast!
			-- refresh local variable names
			@currentScope\refreshLocalVars! if @currentScope
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
						elseif expr[1] == "UnitAction"
							if @newActionName
								oldFileFullname = editor.gameFullPath..@filename
								filePath = Path.getPath oldFileFullname
								newFileFullname = filePath..@newActionName..".trigger"
								return if oldFileFullname == newFileFullname
								if oContent\exist newFileFullname
									MessageBox text:"Action Name Exist!",okOnly:true
									oldName = Path.getName @filename
									@triggerName = oldName
									emit "Scene.Action.ChangeName",oldName
								elseif not Path.isValid Path.getFilename newFileFullname
									MessageBox text:"Invalid Name!",okOnly:true
									oldName = Path.getName @filename
									@triggerName = oldName
									emit "Scene.Action.ChangeName",oldName
								else
									oContent\saveToFile newFileFullname,TriggerDef.ToEditText @exprData
									oContent\remove oldFileFullname
									@filename = Path.getPath(@filename)..@newActionName..".trigger"
								@newActionName = nil
							selectedExprItem.text = tostring expr
							@notifyEdit!

		insertNewExpr = (after)-> ->
			selectedExprItem = @_selectedExprItem
			{:expr,:indent,:parentExpr,:index} = selectedExprItem
			parentExpr or= expr
			if after
				switch selectedExprItem.itemType
					when "Start","Mid"
						parentExpr = selectedExprItem.actionExpr
						index = #parentExpr+1
						indent += 1
						if index > 2
							lastExpr = parentExpr[#parentExpr]
							isMultiLine = lastExpr.MultiLine
							children = @triggerMenu.children
							startIndex = children\index(selectedExprItem)+1
							for childItem in *children[startIndex,]
								if childItem.expr == lastExpr and (isMultiLine == (childItem.itemType == "End"))
									selectedExprItem = childItem
									break
					else
						index += 1
			else
				indent += (parentExpr.MultiLine and 1 or 0)
				index or= #parentExpr
			valueType = switch parentExpr[1]
				when "Available" then "Boolean"
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
			if expr.MultiLine
				isMultiLine = expr.MultiLine
				searchEnd = false
				delItems = for childItem in *children[startIndex,]
					break if searchEnd
					if childItem.expr == expr and (isMultiLine == (childItem.itemType == "End"))
						searchEnd = true
					childItem
				for item in *delItems
					@triggerMenu\removeChild item
			else
				@triggerMenu\removeChild selectedExprItem
			if @currentScope and expr.Type == "None" or expr.TypeIgnore
				@currentScope\refreshLocalVars!
			offset = @offset
			@offset = oVec2.zero
			@viewSize = @triggerMenu\alignItems 0
			@offset = offset
			prevItem = children[startIndex-1]
			prevItem.checked = true if prevItem.expr
			@.changeExprItem prevItem
			if prevItem.expr and
				prevItem.expr[1] ~= "Available" and
				prevItem.parentExpr and
				prevItem.parentExpr[1] == "Available"
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
			if parentExpr[1] == "Available"
				children[startIndex-1]\updateText!
				selectedExprItem\updateText!
			prevIndex = startIndex-1
			prevItem = children[prevIndex]
			if prevItem.itemType == "End"
				prevExpr = prevItem.expr
				for i = startIndex,1,-1
					item = children[i]
					if item.expr == prevExpr and item.itemType == "Start"
						prevIndex = i
						break
			if expr.MultiLine
				searchEnd = false
				items = for item in *children[startIndex,]
					break if searchEnd
					if item.expr == expr and item.itemType == "End"
						searchEnd = true
					item
				for item in *items
					children\remove item
					children\insert item,prevIndex
					prevIndex += 1
			else
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
			if parentExpr[1] == "Available"
				children[startIndex+1]\updateText!
				selectedExprItem\updateText!
			nextIndex = startIndex+1
			if expr.MultiLine
				for i = startIndex,#children
					childItem = children[i]
					if childItem.expr == expr and childItem.itemType == "End"
						nextIndex = i+1
						break
			nextItem = children[nextIndex]
			nextItems = if nextItem.itemType == "Start"
				tmpExpr = nextItem.expr
				searchEnd = false
				for item in *children[nextIndex,]
					break if searchEnd
					if item.expr == tmpExpr and item.itemType == "End"
						searchEnd = true
					item
			else
				{nextItem}
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
					.menu\addChild with TriggerExpr text:@_selectedExprItem.errorInfo,width:panelWidth-40
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

		@gslot "Scene.Action.ChangeName",(newName)-> @newActionName = newName
		@gslot "Scene.Action.Open",checkReload

	notifyEdit:=>
		children = @triggerMenu.children
		for i = 1,#children
			children[i].lineNumber = i
		@modified = true
		@lintCode!
		emit "Scene.Action.Edited",@filename

	createExprItem:(text,indent,expr,parentExpr,index)=>
		children = @triggerMenu.children
		lastItem = children and children.last or nil
		lineNumber = children and #children+1 or 1
		exprItem = with TriggerExpr {
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
			@runScope\clear!
			@stopScope\clear!
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
		triggerCode = TriggerDef.ToCodeText @exprData
		-- TODO: validata code here
		codeFile = editor.gameFullPath..@filename
		codeFile = Path.getPath(codeFile)..Path.getName(codeFile)..".lua"
		oContent\saveToFile codeFile,triggerCode

	isInAction:=>
		not @isInCondition! and not @isInEvent!

	isInCondition:=>
		expr = @_selectedExprItem.expr
		parentExpr = @_selectedExprItem.parentExpr
		expr[1] == "Available" or (parentExpr and parentExpr[1] == "Available")

	isInEvent:=>
		expr = @_selectedExprItem.expr
		switch expr[1]
			when "Priority","Reaction","Recovery"
				true
			else
				false

	getPrevLocalVars:(targetType)=>
		localVars = {k,v for k,v in pairs Args}
		return localVars if not @isInAction!

		targetExpr = @_selectedExprItem.expr
		varScope = {}
		nextExpr = (expr)->
			return false unless "table" == type expr
			switch expr[1]
				when "SetLocal"
					assignExpr = expr[2]
					exprName = assignExpr[1]
					varType = exprName\sub 9,-1
					varName = assignExpr[2][2]
					scope = varScope[#varScope]
					if varName ~= "InvalidName"
						scope[varName] = varType
				when "Action"
					table.insert varScope,{}
					for i = 2,#expr
						if nextExpr expr[i]
							return true -- true to stop search
					table.remove varScope
				else
					for i = 2,#expr
						if nextExpr expr[i]
							return true
			expr == targetExpr
		table.insert varScope,{}
		nextExpr @currentScope.actionItem.expr
		for scope in *varScope
			for v,k in pairs scope
				if k == targetType
					table.insert localVars,v
		localVars

	markLocalVarRename:(fromName,toName)=>
		@currentScope.localVarFrom = fromName
		@currentScope.localVarTo = toName

	showEditButtons:(names)=>
		buttonSet = {@["#{name}Btn"],true for name in *names}
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

	lintCode:=>
		return unless @triggerMenu.children
		@errorBtn.errorItems = {}
		@errorBtn.currentIndex = 1

		locals = {k,v for k,v in pairs Args}
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
