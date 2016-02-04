Dorothy!
ExprEditorView = require "View.Control.Trigger.ExprEditor"
TriggerExpr = require "Control.Trigger.TriggerExpr"
ExprChooser = require "Control.Trigger.ExprChooser"
TriggerDef = require "Data.TriggerDef"

Class ExprEditorView,
	__init:(args)=>
		@trigger = nil

		triggerExpr = nil
		@changeTriggerExpr = (button)->
			triggerExpr.checked = false if triggerExpr
			triggerExpr = if button.checked then button else nil
			if button.checked
				@editMenu.visible = true
				@editMenu.transformTarget = button
				@editMenu.position = oVec2 button.width,0
			else
				@editMenu.visible = false
				@editMenu.transformTarget = nil

		@setupMenuScroll @triggerMenu

		locals = nil
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
					@createExprItem "Action( function()",indent,expr
					children = @triggerMenu.children
					index = #children+1
					for i = 2,#expr
						nextExpr expr,i,indent+1
					if #locals > 0
						exprItem = @createExprItem "local "..table.concat(locals,", "),indent+1
						children\removeLast!
						children\insert exprItem,index
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
					table.insert locals,expr[2][2]
					@createExprItem tostring(expr),indent,expr,parentExpr,index
				else
					@createExprItem tostring(expr),indent,expr,parentExpr,index
		@nextExpr = (expr,indent)=>
			locals = {}
			nextExpr expr,nil,indent
			locals = nil

		@editBtn\slot "Tapped",->
			if triggerExpr
				expr = triggerExpr.expr
				parentExpr = triggerExpr.parentExpr
				index = triggerExpr.index
				with ExprChooser valueType:expr.Type,expr:expr
					\slot "Result",(expr)->
						if parentExpr
							parentExpr[index] = expr
							triggerExpr.checked = false
							@.changeTriggerExpr triggerExpr
							@loadTrigger @trigger

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

	setupEditMenu:(expr)=>

	createExprItem:(text,indent,expr,parentExpr,index)=>
		exprItem = with TriggerExpr {
				:indent
				:text
				:expr
				:parentExpr
				:index
				width:@triggerMenu.width-20
			}
			\slot "Tapped",@changeTriggerExpr if expr
		@triggerMenu\addChild exprItem
		exprItem

	loadTrigger:(arg)=>
		@trigger = switch type arg
			when "table" then arg
			when "string" then TriggerDef.SetExprMeta dofile arg
		@triggerMenu\removeAllChildrenWithCleanup!
		offset = @offset
		@offset = oVec2.zero
		@nextExpr @trigger,0
		@viewSize = @triggerMenu\alignItems!
		@offset = offset
		@trigger

	enabled:property => @touchEnabled,
		(value)=>
			@touchEnabled = value
			@triggerMenu.enabled = value
			@editMenu.enabled = value
