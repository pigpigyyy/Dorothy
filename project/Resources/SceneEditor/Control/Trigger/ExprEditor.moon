Dorothy!
ExprEditorView = require "View.Control.Trigger.ExprEditor"
TriggerExpr = require "Control.Trigger.TriggerExpr"
ExprChooser = require "Control.Trigger.ExprChooser"
TriggerDef = require "Data.TriggerDef"

Class ExprEditorView,
	__init:(args)=>
		@exprData = nil
		@filename = nil
		@asyncLoad = false
		@actionItem = nil
		@localVarItem = nil
		@locals = nil
		@localSet = nil
		@localVarFrom = nil
		@localVarTo = nil

		for child in *@editMenu.children
			child.scale = oScale 0.3,1,1,oEase.OutQuad

		@_selectedExprItem = nil
		@changeExprItem = (button)->
			@_selectedExprItem.checked = false if @_selectedExprItem
			@_selectedExprItem = button.checked and button or nil
			if button.checked
				@editMenu.visible = true
				@editMenu.transformTarget = button
				@editMenu.position = oVec2 button.width,0
				{:expr,:index,:parentExpr} = @_selectedExprItem
				subExprItem = switch @_selectedExprItem.itemType
					when "Mid","End" then true
					else false
				rootItem = switch expr[1]
					when "Trigger","Event","Condition","Action" then true
					else false
				edit = not subExprItem
				insert = if rootItem then false
					elseif not subExprItem
						if parentExpr then (parentExpr[1] ~= "Event")
						else true
					else false
				add = switch expr[1]
					when "Trigger"
						false
					when "Event"
						#expr == 1
					else
						if parentExpr then (parentExpr[1] ~= "Event")
						else true
				del = if rootItem then false
					elseif parentExpr and parentExpr[1] == "Condition" and #parentExpr == 2
						false
					else
						not subExprItem
				up = index and index > 2 and not subExprItem
				down = index and index < #parentExpr and not subExprItem
				buttons = for v,k in pairs {:edit,:insert,:add,:del,:up,:down}
					if k then v
					else continue
				@showEditButtons buttons
			else
				@editMenu.visible = false
				@editMenu.transformTarget = nil

		@setupMenuScroll @triggerMenu

		getLocalVarText = ->
			defaultValues = for var in *@locals
				switch @localSet[var]
					when "Number" then "0"
					else "nil"
			"local "..table.concat(@locals,", ").." = "..table.concat(defaultValues,", ")

		createLocalVarItem = ->
			indent = @actionItem.indent+1
			localVarItem = with @createExprItem getLocalVarText!,indent
				.positionY = @actionItem.positionY-@actionItem.height/2-.height/2
			children = @triggerMenu.children
			index = children\index(@actionItem)+1
			children\removeLast!
			children\insert localVarItem,index
			localVarItem

		refreshLocalVars = ->
			if @actionItem
				nextExpr = (expr)->
					return unless "table" == type expr
					switch expr[1]
						when "SetLocalNumber"
							if not @localSet[expr[2][2]]
								@localSet[expr[2][2]] = "Number"
								table.insert @locals,expr[2][2]
					for i = 2,#expr
						nextExpr expr[i]
				@locals = {}
				@localSet = {}
				nextExpr @actionItem.expr
				if @localVarItem
					if #@locals > 0
						@localVarItem.text = getLocalVarText!
					else
						@localVarItem.parent\removeChild @localVarItem
						@localVarItem = nil
				else
					if #@locals > 0
						@localVarItem = createLocalVarItem!

		nextExpr = (parentExpr,index,indent)->
			expr = index and parentExpr[index] or parentExpr
			switch expr[1]
				when "Trigger"
					@createExprItem "Trigger( #{expr[2]}, #{expr[3]},",indent,expr
					for i = 4,#expr
						nextExpr expr,i,indent+1
					@createExprItem ")",indent
				when "Event"
					with @createExprItem "Event(",indent,expr
						.itemType = "Start"
						.actionExpr = expr
					for i = 2,#expr
						nextExpr expr,i,indent+1
					@createExprItem "),",indent
					indent -= 1
				when "Condition"
					with @createExprItem "Condition( function() return",indent,expr
						.itemType = "Start"
						.actionExpr = expr
					for i = 2,#expr
						nextExpr expr,i,indent+1
					@createExprItem "end ),",indent
				when "Action"
					@actionItem = with @createExprItem "Action( function()",indent,expr
						.itemType = "Start"
						.actionExpr = expr
					children = @triggerMenu.children
					index = #children+1
					for i = 2,#expr
						nextExpr expr,i,indent+1
					if #@locals > 0
						@localVarItem = createLocalVarItem!
						moveY = @localVarItem.height
						start = index+1
						stop = #children
						for child in *children[start,stop]
							child.positionY -= moveY
					@createExprItem "end )",indent
				when "If"
					with @createExprItem tostring(expr),indent,expr,parentExpr,index
						.itemType = "Start"
						.actionExpr = expr[3]
					for i = 2,#expr[3]
						nextExpr expr[3],i,indent+1
					with @createExprItem "else",indent,expr,parentExpr,index
						.itemType = "Mid"
						.actionExpr = expr[4]
					for i = 2,#expr[4]
						nextExpr expr[4],i,indent+1
					with @createExprItem "end",indent,expr,parentExpr,index
						.itemType = "End"
				when "Loopi"
					with @createExprItem tostring(expr),indent,expr,parentExpr,index
						.itemType = "Start"
						.actionExpr = expr[5]
					for i = 2,#expr[5]
						nextExpr expr[5],i,indent+1
					with @createExprItem "end",indent,expr,parentExpr,index
						.itemType = "End"
				when "SetLocalNumber"
					if not @localSet[expr[2][2]]
						@localSet[expr[2][2]] = "Number"
						table.insert @locals,expr[2][2]
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
				parentExpr[1] == "Condition" and
				selectedExprItem.expr[1] ~= "Condition"
				selectedExprItem\updateText!
			-- remove duplicated new exprs
			for i = startIndex,stopIndex
				children\removeLast!
			-- refresh local variable names
			refreshLocalVars!
			if @localVarFrom
				@renameLocalVar @localVarFrom,@localVarTo
				@localVarFrom,@localVarTo = nil,nil
			-- update items position
			offset = @offset
			@offset = oVec2.zero
			@viewSize = @triggerMenu\alignItems 0
			@offset = offset
			-- select new expr item
			newItems[1].checked = true
			@.changeExprItem newItems[1]
			@scrollToPosY newItems[1].positionY

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
						elseif expr[1] == "Trigger"
							selectedExprItem.text = "Trigger( #{expr[2]}, #{expr[3]},"

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
				when "Event"
					"Event"
				when "Condition"
					"Boolean"
				else
					"Action"
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
			if expr.Type == "None" or expr.TypeIgnore
				refreshLocalVars!
			offset = @offset
			@offset = oVec2.zero
			@viewSize = @triggerMenu\alignItems 0
			@offset = offset
			prevItem = children[startIndex-1]
			prevItem.checked = true if prevItem.expr
			@.changeExprItem prevItem
			if prevItem.expr and
				prevItem.expr[1] ~= "Condition" and
				prevItem.parentExpr and
				prevItem.parentExpr[1] == "Condition"
				prevItem\updateText!

		@upBtn\slot "Tapped",->
			selectedExprItem = @_selectedExprItem
			{:expr,:parentExpr,:index} = selectedExprItem
			selectedExprItem.checked = false
			@.changeExprItem selectedExprItem
			table.remove parentExpr,index
			table.insert parentExpr,index-1,expr
			children = @triggerMenu.children
			startIndex = children\index(selectedExprItem)
			if parentExpr[1] == "Condition"
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

		@downBtn\slot "Tapped",->
			selectedExprItem = @_selectedExprItem
			{:expr,:parentExpr,:index} = selectedExprItem
			selectedExprItem.checked = false
			@.changeExprItem selectedExprItem
			table.remove parentExpr,index
			table.insert parentExpr,index+1,expr
			children = @triggerMenu.children
			startIndex = children\index(selectedExprItem)
			if parentExpr[1] == "Condition"
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

	createExprItem:(text,indent,expr,parentExpr,index)=>
		children = @triggerMenu.children
		lastItem = children and children.last or nil
		exprItem = with TriggerExpr {
				:indent
				:text
				:expr
				:parentExpr
				:index
				width:@triggerMenu.width
			}
			.position = lastItem and
				(lastItem.position-oVec2(0,lastItem.height/2+.height/2)) or
				oVec2(@triggerMenu.width/2,@triggerMenu.height-.height/2)+@offset
			\slot "Tapped",@changeExprItem if expr
		@triggerMenu\addChild exprItem
		{:width,:height} = @viewSize
		@viewSize = CCSize width,@height-exprItem.positionY+exprItem.height/2
		sleep! if @asyncLoad
		exprItem

	loadExpr:(arg)=>
		@exprData = switch type arg
			when "table" then arg
			when "string"
				@filename = arg
				TriggerDef.SetExprMeta (loadstring oContent\loadFile arg)!
		@view\schedule once ->
			@triggerMenu\removeAllChildrenWithCleanup!
			@actionItem = nil
			@localVarItem = nil
			@locals = {}
			@localSet = {}
			@asyncLoad = true
			@nextExpr @exprData,0
			@asyncLoad = false
		@exprData

	save:(filename)=>
		triggerText = TriggerDef.ToEditText @exprData
		oContent\saveToFile editor.gameFullPath..@filename,triggerText

	isInActions:=>
		expr = @_selectedExprItem.expr
		parentExpr = @_selectedExprItem.parentExpr
		not (expr[1] == "Condition" or expr[1] == "Event") and
			parentExpr and
				not (parentExpr[1] == "Condition" or
				parentExpr[1] == "Event")

	getPrevLocalVars:(varType)=>
		targetExpr = @_selectedExprItem.expr
		varSet = {}
		nextExpr = (expr)->
			return false unless "table" == type expr
			return true if expr == targetExpr
			switch expr[1]
				when "SetLocalNumber"
					if not varSet[expr[2][2]]
						varSet[expr[2][2]] = "Number"
			for i = 2,#expr
				if nextExpr expr[i]
					return true
			false
		nextExpr @actionItem.expr
		return for v,k in pairs varSet
			if k == varType then v
			else continue

	markLocalVarRename:(fromName,toName)=>
		@localVarFrom = fromName
		@localVarTo = toName

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
		for item in *children[startIndex,]
			if item.expr and nextExpr item.expr
				item.text = tostring item.expr

	showEditButtons:(names)=>
		posX = @editMenu.width-30-(#names == 1 and names[1] == "edit" and 60 or 0)
		buttonSet = {@["#{name}Btn"],true for name in *names}
		for i = #@editMenu.children,1,-1
			child = @editMenu.children[i]
			if buttonSet[child]
				child.positionX = posX
				child.visible = true
				child.scaleX = 0
				child.scaleY = 0
				child\perform child.scale
				posX -= 50
			else
				child.visible = false

	enabled:property => @touchEnabled,
		(value)=>
			@touchEnabled = value
			@triggerMenu.enabled = value
			@editMenu.enabled = value
