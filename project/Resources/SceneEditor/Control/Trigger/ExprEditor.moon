Dorothy!
ExprEditorView = require "View.Control.Trigger.ExprEditor"
ExprItem = require "Control.Trigger.ExprItem"
ExprChooser = require "Control.Trigger.ExprChooser"
PopupPanel = require "Control.Basic.PopupPanel"
MessageBox = require "Control.Basic.MessageBox"
TriggerDef = require "Data.TriggerDef"
import Path from require "Lib.Utils"

VarScope = Class
	__init:(editor)=>
		@editor = editor
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
		localVarItem = with @editor\createExprItem @getLocalVarText!,indent
			.positionY = @actionItem.positionY-@actionItem.height/2-.height/2
		children = @editor.triggerMenu.children
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
							if not @editor.args[varName]
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
		children = @editor.triggerMenu.children
		startIndex = children\index(@actionItem)+1
		indent = @actionItem.indent
		for item in *children[startIndex,]
			break if item.indent == indent
			if item.expr and nextExpr item.expr
				item.text = tostring item.expr

Class ExprEditorView,
	__init:(args)=>
		@type = args.type
		switch @type
			when "Action"
				@args = action:"UnitAction"
				@extension = ".action"
			when "Trigger"
				@args = {}
				@extension = ".trigger"
			when "AINode"
				@args = {}
				@extension = ".node"

		@exprData = nil
		@filename = nil
		@asyncLoad = false

		@currentScope = nil
		@varScopes = switch @type
			when "Action"
				{
					Run: VarScope @
					Stop: VarScope @
				}
			when "Trigger"
				Action: VarScope @
			else
				{}

		@newName = nil
		@modified = false

		@codeMode = TriggerDef.CodeMode

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
				@currentScope = @varScopes[(parentExpr or expr)[1]]
				subExprItem = switch @_selectedExprItem.itemType
					when "Mid","End" then true
					else false
				rootItem = switch expr[1]
					when "Trigger","Event","Condition","Action","ConditionNode" then true
					when "UnitAction","Available","Run","Stop" then true
					else
						if parentExpr then parentExpr[1] == "UnitAction"
						else false
				edit = not subExprItem
				insert = if rootItem then false
					elseif subExprItem then false
					elseif #@triggerMenu.children >= 999 then false
					elseif parentExpr then (parentExpr[1] ~= "Event")
					else true
				add = switch expr[1]
					when "Trigger","Event" then false
					when "UnitAction" then false
					when "Available","Run","Stop" then true
					else
						if rootItem or #@triggerMenu.children >= 999 then false
						elseif parentExpr then (parentExpr[1] ~= "Event")
						else true
				copy = add and parentExpr[1] ~= "Event"
				del = if rootItem then false
					elseif parentExpr and (switch parentExpr[1]
						when "Condition","Event","Available" then #parentExpr == 2
						when "ConditionNode" then #parentExpr == 3
						else false)
						false
					else
						not subExprItem
				mode = switch expr[1]
					when "UnitAction","Trigger","ConditionNode" then true
					else false
				up = not subExprItem and not rootItem and index and (switch parentExpr[1]
					when "ConditionNode" then index > 3
					else index > 2)
				down = index and index < #parentExpr and not subExprItem and not rootItem
				buttons = for v,k in pairs {:edit,:copy,:insert,:add,:del,:up,:down,:mode}
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
				when "Trigger"
					if TriggerDef.CodeMode
						@createExprItem "return",indent
						@createExprItem tostring(expr),indent,expr
					else
						@createExprItem "Trigger",indent
						@createExprItem tostring(expr),indent+1,expr
						@createExprItem " ",indent
						indent -= 1
					for i = 4,#expr
						nextExpr expr,i,indent+1
					@createExprItem mode(")"," "),indent
				when "Event"
					with @createExprItem mode(tostring(expr),"Event"),indent,expr
						.itemType = "Start"
						.actionExpr = expr
					for i = 2,#expr
						nextExpr expr,i,indent+1
					with @createExprItem mode("),"," "),indent
						.itemType = "End"
					indent -= 1
				when "Condition"
					@conditionItem = with @createExprItem mode(tostring(expr),"Condition"),indent,expr
						.itemType = "Start"
						.actionExpr = expr
					for i = 2,#expr
						nextExpr expr,i,indent+1
					with @createExprItem mode("end ),"," "),indent
						.itemType = "End"
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
					with @createExprItem mode(tostring(expr),"Available"),indent,expr
						.itemType = "Start"
						.actionExpr = expr
					for i = 2,#expr
						nextExpr expr,i,indent+1
					with @createExprItem mode("end,"," "),indent
						.itemType = "End"
				when "Run","Stop","Action"
					@currentScope = @varScopes[expr[1]]
					@currentScope.actionItem = with @createExprItem mode(tostring(expr),expr[1]),indent,expr
						.itemType = "Start"
						.actionExpr = expr
					if expr[1] == "Action"
						@actionItem = @currentScope.actionItem
					children = @triggerMenu.children
					index = #children+1
					for i = 2,#expr
						nextExpr expr,i,indent+1
					with @currentScope
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
					with @createExprItem mode("end"..(expr[1] == "Run" and "," or "")," "),indent
						.itemType = "End"
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
				when "Perform"
					performExpr = expr[2]
					wait = expr[3]
					with @createExprItem tostring(expr),indent,expr,parentExpr,index
						.itemType = "Start"
						.actionExpr = performExpr[3]
					for i = 2,#performExpr[3]
						nextExpr performExpr[3],i,indent+1
					with @createExprItem mode(")"..(wait and " )" or ""),"End."),indent,expr,parentExpr,index
						.itemType = "End"
				when "Sequence","Spawn"
					groupExpr = expr[2]
					with @createExprItem " ",indent,expr,parentExpr,index
						.itemType = "Start"
						.text = tostring expr
						.actionExpr = groupExpr
					for i = 2,#groupExpr
						nextExpr groupExpr,i,indent+1
					with @createExprItem " ",indent,expr,parentExpr,index
						.itemType = "End"
						.text = mode ")","End."
				when "Loop"
					with @createExprItem tostring(expr),indent,expr,parentExpr,index
						.itemType = "Start"
						.actionExpr = expr[6]
					for i = 2,#expr[6]
						nextExpr expr[6],i,indent+1
					with @createExprItem mode("end )","End."),indent,expr,parentExpr,index
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
			nextExpr parentExpr,index,indent -- param orders changed

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
				(((switch parentExpr[1]
					when "Available","Condition","ConditionNode" then true
					else false) and
				selectedExprItem.expr.Type == "Boolean") or
				(parentExpr[1] == "ActionGroup" and
				selectedExprItem.expr.Type == "Action"))
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
				valueType = (expr.TypeIgnore or expr.Type == "None") and "TriggerAction" or expr.Type
				with ExprChooser {
						valueType:valueType
						expr:expr
						parentExpr:parentExpr
						owner:@
					}
					\slot "Result",(newExpr)->
						if parentExpr
							parentExpr[index] = newExpr
							if newExpr.Type == "Event"
								@conditionItem\updateText!
								@actionItem\updateText!
								@updateArgs!
							addNewItem selectedExprItem,selectedExprItem.indent,parentExpr,index
							return

						switch expr[1]
							when "UnitAction","Trigger","ConditionNode"
								if @newName
									oldFileFullname = editor.gameFullPath..@filename
									filePath = Path.getPath oldFileFullname
									newFileFullname = filePath..@newName..@extension
									return if oldFileFullname == newFileFullname
									if oContent\exist newFileFullname
										MessageBox text:"#{ @type } Name Exist!",okOnly:true
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
				when "Event" then "Event"
				when "Available","Condition","ConditionNode" then "Boolean"
				when "ActionGroup" then "Action"
				else "TriggerAction"
			with ExprChooser {
					valueType:valueType
					parentExpr:parentExpr
					owner:@
				}
				\slot "Result",(newExpr)->
					return unless newExpr
					table.insert parentExpr,index,newExpr
					addNewItem selectedExprItem,indent,parentExpr,index,false,after

		with @copyBtn
			.copying = false
			\slot "Tapped",->
				.copying = not .copying
				if .copying
					.text = "Paste"
					.color = ccColor3 0xff88cc
					copyTable = (tb,target)->
						for i = 1,#target
							item = target[i]
							if "table" == type item
								item = copyTable {},item
							tb[i] = item
						setmetatable tb,getmetatable target
					.targetExpr = copyTable {},@_selectedExprItem.expr
				else
					selectedExprItem = @_selectedExprItem
					{:indent,:parentExpr,:index} = selectedExprItem
					switch selectedExprItem.itemType
						when "Start","Mid"
							parentExpr = selectedExprItem.actionExpr
							index = #parentExpr+1
							indent += 1
						else
							index += 1
					switch .targetExpr.Type
						when "Boolean"
							if not (switch parentExpr[1]
								when "Condition","Available","ConditionNode" then true
								else false)
								.copying = true
								MessageBox text:"Can Not Paste\nBoolean Item\nHere",okOnly:true
								return
						when "Action"
							if not (switch parentExpr[1]
								when "ActionGroup" then true
								else false)
								.copying = true
								MessageBox text:"Can Not Paste\nAction Item\nHere",okOnly:true
								return
						else
							switch parentExpr[1]
								when "Condition","Available","ConditionNode","ActionGroup"
									.copying = true
									MessageBox text:"Can Not Paste\nTrigger Action\nHere",okOnly:true
									return
					.text = "Copy"
					.color = ccColor3 0x00ffff
					table.insert parentExpr,index,.targetExpr
					addNewItem selectedExprItem,indent,parentExpr,index,false,true
					.targetExpr = nil

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
			{expr:prevExpr,parentExpr:prevParent} = prevItem
			if prevExpr and prevParent and
				((prevExpr[1] ~= "Condition" and prevParent[1] == "Condition") or
				(prevExpr[1] ~= "Available" and prevParent[1] == "Available") or
				(prevExpr[1] ~= "ConditionNode" and prevParent[1] == "ConditionNode"))
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
			targetExpr = selectedExprItem.actionExpr or parentExpr
			currentItem = selectedExprItem
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
						currentItem = item
					item
				for item in *items
					children\remove item
					children\insert item,prevIndex
					prevIndex += 1
			else
					children\remove selectedExprItem
					children\insert selectedExprItem,prevIndex
			switch targetExpr[1]
				when "Condition","Available","ConditionNode","ActionGroup"
					prevItem\updateText!
					currentItem\updateText!
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
			targetExpr = selectedExprItem.actionExpr or parentExpr
			currentItem = selectedExprItem
			nextItem = children[startIndex+1]
			nextIndex = startIndex+1
			if expr.MultiLine
				for i = startIndex,#children
					childItem = children[i]
					if childItem.expr == expr and childItem.itemType == "End"
						currentItem = childItem
						nextIndex = i+1
						break
			nextItem = children[nextIndex]
			nextItems = if nextItem.itemType == "Start"
				tmpExpr = nextItem.expr
				searchEnd = false
				for item in *children[nextIndex,]
					break if searchEnd
					if item.expr == tmpExpr and item.itemType == "End"
						nextItem = item
						searchEnd = true
					item
			else
				{nextItem}
			for item in *nextItems
				children\remove item
				children\insert item,startIndex
				startIndex += 1
			switch targetExpr[1]
				when "Condition","Available","ConditionNode","ActionGroup"
					currentItem\updateText!
					nextItem\updateText!
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
			if @codeMode ~= TriggerDef.CodeMode
				@codeMode = TriggerDef.CodeMode
				@loadExpr @exprData
			else
				@lintCode!

		@slot "Entered",checkReload

		@gslot "Scene.#{ @type }.ChangeName",(newName)-> @newName = newName
		@gslot "Scene.#{ @type }.Open",checkReload

	updateArgs:=>
		if @exprData[1] == "Trigger"
			eventExpr = @exprData[4][2]
			@args = if eventExpr.Args
				{k,v\match "^%a*" for k,v in pairs eventExpr.Args}
			else {}

	selectedLine:property =>
		if @_selectedExprItem
			@_selectedExprItem.lineNumber
		else
			nil,
		(value)=>
			item = @triggerMenu.children[value]
			item.checked = true
			@.changeExprItem item

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
		@updateArgs!
		@view\schedule once ->
			@triggerMenu.enabled = false
			@triggerMenu\removeAllChildrenWithCleanup!
			for _, scope in pairs @varScopes do scope\clear!
			@offset = oVec2.zero
			@asyncLoad = true
			@nextExpr @exprData,0
			@asyncLoad = false
			@triggerMenu.enabled = true
			@lintCode!
			if @targetLine
				@selectedLine = @targetLine
				@targetLine = nil
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

	isInAction:property => not @isInCondition and not @isInEvent

	isInCondition:property =>
		{:expr,:parentExpr} = @_selectedExprItem
		condA = expr and switch expr[1]
			when "Available","Condition","ConditionNode" then true
			else false
		condB = parentExpr and switch parentExpr[1]
			when "Available","Condition","ConditionNode" then true
			else false
		not condA and condB

	isInEvent:property =>
		{:expr,:parentExpr} = @_selectedExprItem
		switch expr[1]
			when "Event" then parentExpr and parentExpr[1] == "Event"
			when "Priority","Reaction","Recovery" then true
			else false

	getPrevLocalVars:(targetType)=>
		localVars = for k,v in pairs @args
			if v == targetType then k
			else continue
		return localVars if not @isInAction

		targetExpr = @_selectedExprItem.expr
		varScope = {}
		varInScope = (varName)->
			local result
			for scope in *varScope
				varType = scope[varName]
				result = varType if varType
			return result
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
				when "Loop"
					scope = if varInScope expr[2][2] then {}
						else {[expr[2][2]]:"Number"}
					table.insert varScope,scope
					actionExpr = expr[6]
					for i = 2,#actionExpr
						if nextExpr actionExpr[i]
							return true -- true to stop search
					table.remove varScope
				when "Action"
					table.insert varScope,{}
					for i = 2,#expr
						if nextExpr expr[i]
							return true
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
		buttonSet = {@["#{ name }Btn"],true for name in *names}
		posX = @editMenu.width-35-(buttonSet[@modeBtn] and 60 or 0)
		for i = #@editMenu.children,1,-1
			child = @editMenu.children[i]
			if buttonSet[child]
				child.positionX = posX
				child.visible = true
				with child.face
					.scaleX = 0
					.scaleY = 0
					\perform child.scale
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

		locals = {k,v for k,v in pairs @args}
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
