Dorothy!
ExprEditorView = require "View.Control.Trigger.ExprEditor"
TriggerExpr = require "Control.Trigger.TriggerExpr"
ExprChooser = require "Control.Trigger.ExprChooser"
TriggerDef = require "Data.TriggerDef"

Class ExprEditorView,
	__init:(args)=>
		@exprData = nil
		@asyncLoad = false

		selectedExprItem = nil
		@changeExprItem = (button)->
			selectedExprItem.checked = false if selectedExprItem
			selectedExprItem = button.checked and button or nil
			if button.checked
				@editMenu.visible = true
				@editMenu.transformTarget = button
				@editMenu.position = oVec2 button.width,0
			else
				@editMenu.visible = false
				@editMenu.transformTarget = nil

		@setupMenuScroll @triggerMenu

		locals = nil
		localSet = nil
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
					actionItem = @createExprItem "Action( function()",indent,expr
					children = @triggerMenu.children
					index = #children+1
					for i = 2,#expr
						nextExpr expr,i,indent+1
					if #locals > 0
						exprItem = @createExprItem "local "..table.concat(locals,", "),indent+1
						children\removeLast!
						children\insert exprItem,index
						moveY = exprItem.height+10
						exprItem.positionY = actionItem.positionY-actionItem.height/2-exprItem.height/2-10
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
					@createExprItem "end",indent,expr,parentExpr,index
				when "Loopi"
					@createExprItem tostring(expr),indent,expr,parentExpr,index
					for i = 2,#expr[5]
						nextExpr expr[5],i,indent+1
					@createExprItem "end",indent,expr,parentExpr,index
				when "SetLocalNumber"
					if not localSet[expr[2][2]]
						localSet[expr[2][2]] = true
						table.insert locals,expr[2][2]
					@createExprItem tostring(expr),indent,expr,parentExpr,index
				else
					@createExprItem tostring(expr),indent,expr,parentExpr,index

		@nextExpr = (expr,indent)=>
			locals = {}
			localSet = {}
			nextExpr expr,nil,indent
			locals = nil
			localSet = nil

		@editBtn\slot "Tapped",->
			if selectedExprItem
				{:expr,:parentExpr,:index} = selectedExprItem
				with ExprChooser valueType:expr.Type,expr:expr
					\slot "Result",(newExpr)->
						if parentExpr
							parentExpr[index] = newExpr
							-- update trigger
							children = @triggerMenu.children
							itemIndex = children\index selectedExprItem
							startIndex = #children
							@nextExpr newExpr,selectedExprItem.indent
							stopIndex = #children-1

							targetItem = selectedExprItem
							selectedExprItem.checked = false
							@.changeExprItem selectedExprItem
							@triggerMenu\removeChild targetItem

							newItems = [child for child in *children[startIndex,stopIndex]]
							for item in *newItems
								children\insert item,itemIndex
								itemIndex += 1
							for i = startIndex,stopIndex
								children\removeLast!
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
			@asyncLoad = true
			@nextExpr @exprData,0
			@asyncLoad = false
		@exprData

	enabled:property => @touchEnabled,
		(value)=>
			@touchEnabled = value
			@triggerMenu.enabled = value
			@editMenu.enabled = value
