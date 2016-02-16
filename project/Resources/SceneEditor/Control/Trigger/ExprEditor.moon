Dorothy!
ExprEditorView = require "View.Control.Trigger.ExprEditor"
TriggerExpr = require "Control.Trigger.TriggerExpr"
ExprChooser = require "Control.Trigger.ExprChooser"
TriggerDef = require "Data.TriggerDef"

Class ExprEditorView,
	__init:(args)=>
		@exprData = nil
		@asyncLoad = false
		@actionItem = nil
		@localVarItem = nil
		@locals = nil
		@localSet = nil
		@localVarFrom = nil
		@localVarTo = nil

		@_selectedExprItem = nil
		@changeExprItem = (button)->
			@_selectedExprItem.checked = false if @_selectedExprItem
			@_selectedExprItem = button.checked and button or nil
			if button.checked
				@editMenu.visible = true
				@editMenu.transformTarget = button
				@editMenu.position = oVec2 button.width,0
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
				.positionY = @actionItem.positionY-@actionItem.height/2-.height/2-10
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
					@createExprItem "Trigger(",indent
					for i = 2,4
						nextExpr expr,i,indent+1
					@createExprItem ")",indent
				when "Event"
					@createExprItem "Event(",indent,expr
					nextExpr expr,2,indent+1
					@createExprItem "),",indent
					indent -= 1
				when "Condition"
					@createExprItem "Condition{",indent,expr
					children = @triggerMenu.children
					startIndex = #children+1
					for i = 2,#expr
						nextExpr expr,i,indent+1
					stopIndex = #children-1
					for item in *children[startIndex,stopIndex]
						item.text = item.text\gsub("^%s*","")..","
					@createExprItem "},",indent
				when "Action"
					@actionItem = @createExprItem "Action( function()",indent,expr
					children = @triggerMenu.children
					index = #children+1
					for i = 2,#expr
						nextExpr expr,i,indent+1
					if #@locals > 0
						@localVarItem = createLocalVarItem!
						moveY = @localVarItem.height+10
						start = index+1
						stop = #children
						for child in *children[start,stop]
							child.positionY -= moveY
					@createExprItem "end )",indent
				when "If"
					@createExprItem tostring(expr),indent,expr,parentExpr,index
					for i = 2,#expr[3]
						nextExpr expr[3],i,indent+1
					@createExprItem "else",indent,expr[4],expr,4
					for i = 2,#expr[4]
						nextExpr expr[4],i,indent+1
					item = @createExprItem "end",indent,expr,parentExpr,index
					item.isExprEnd = true
				when "Loopi"
					@createExprItem tostring(expr),indent,expr,parentExpr,index
					for i = 2,#expr[5]
						nextExpr expr[5],i,indent+1
					item = @createExprItem "end",indent,expr,parentExpr,index
					item.isExprEnd = true
				when "SetLocalNumber"
					if not @localSet[expr[2][2]]
						@localSet[expr[2][2]] = "Number"
						table.insert @locals,expr[2][2]
					@createExprItem tostring(expr),indent,expr,parentExpr,index
				else
					@createExprItem tostring(expr),indent,expr,parentExpr,index

		@nextExpr = (parentExpr,indent,index)=>
			nextExpr parentExpr,index,indent -- params order changed

		@editBtn\slot "Tapped",->
			selectedExprItem = @_selectedExprItem
			if selectedExprItem
				{:expr,:parentExpr,:index} = selectedExprItem
				with ExprChooser {
						valueType:expr.Type
						expr:expr
						parentExpr:parentExpr
						owner:@
					}
					\slot "Result",(newExpr)->
						if parentExpr
							parentExpr[index] = newExpr
							-- update trigger
							children = @triggerMenu.children
							itemIndex = children\index selectedExprItem
							startIndex = #children+1
							@nextExpr parentExpr,selectedExprItem.indent,index
							stopIndex = #children

							newItems = [child for child in *children[startIndex,stopIndex]]

							targetItem = selectedExprItem
							targetExpr = targetItem.expr
							selectedExprItem.checked = false
							@.changeExprItem selectedExprItem

							-- remove old exprs
							switch targetExpr[1]
								when "If","Loopi"
									endSearch = false
									targetItems = for i = itemIndex,#children
										break if endSearch
										childItem = children[i]
										if childItem.expr == targetExpr and childItem.isExprEnd
											endSearch = true
											childItem
										childItem
									for item in *targetItems
										@triggerMenu\removeChild item
								else
									@triggerMenu\removeChild targetItem
							-- insert new exprs in right position
							for item in *newItems
								children\insert item,itemIndex
								itemIndex += 1
							-- separate condition exprs by comma
							if parentExpr[1] == "Condition" and #parentExpr ~= index
								newItems[1].text ..= ","
							-- remove duplicated new exprs
							for i = startIndex,stopIndex
								children\removeLast!

							refreshLocalVars!
							if @localVarFrom
								@renameLocalVar @localVarFrom,@localVarTo
								@localVarFrom,@localVarTo = nil,nil

							offset = @offset
							@offset = oVec2.zero
							@viewSize = @triggerMenu\alignItems!
							@offset = offset

		@addBtn\slot "Tapped",->
			with ExprChooser valueType:"Action"
				\slot "Result",(expr)->
					return unless expr
					@triggerMenu\addChild with TriggerExpr {
							indent:0
							text:tostring expr
							expr:expr
							width:@triggerMenu.width-20
						}
						\slot "Tapped",@changeTriggerExpr
					offset = @offset
					@offset = oVec2.zero
					@viewSize = @triggerMenu\alignItems!
					@offset = offset

	createExprItem:(text,indent,expr,parentExpr,index)=>
		children = @triggerMenu.children
		lastItem = children and children.last or nil
		exprItem = with TriggerExpr {
				:indent
				:text
				:expr
				:parentExpr
				:index
				width:@triggerMenu.width-20
			}
			.position = lastItem and
				(lastItem.position-oVec2(0,lastItem.height/2+.height/2+10)) or
				oVec2(@triggerMenu.width/2,@triggerMenu.height-.height/2-10)+@offset
			\slot "Tapped",@changeExprItem if expr
		@triggerMenu\addChild exprItem
		{:width,:height} = @viewSize
		@viewSize = CCSize width,@height-exprItem.positionY+exprItem.height/2+10
		sleep! if @asyncLoad
		exprItem

	loadExpr:(arg)=>
		@exprData = switch type arg
			when "table" then arg
			when "string" then TriggerDef.SetExprMeta dofile arg
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

	isInActions:=>
		expr = @_selectedExprItem.expr
		parentExpr = @_selectedExprItem.parentExpr
		not parentExpr or not (parentExpr[1] == "Condition" or
			expr[1] == "Condition" or
			parentExpr[1] == "Event" or
			expr[1] == "Event")

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
			if k == varType
				v

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
		for i = startIndex,#children
			item = children[i]
			if item.expr and nextExpr item.expr
				item.text = tostring item.expr

	enabled:property => @touchEnabled,
		(value)=>
			@touchEnabled = value
			@triggerMenu.enabled = value
			@editMenu.enabled = value
