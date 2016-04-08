Dorothy!
AITreeViewView = require "View.Control.AI.AITreeView"
MenuItem = require "Control.AI.MenuItem"
TriggerDef = require "Data.TriggerDef"
ExprChooser = require "Control.Trigger.ExprChooser"

MenuW = 200
MenuH = 40

Class AITreeViewView,
	__init:(args)=>
		@type = "AITree"
		@extension = ".tree"
		@exprData = nil
		@items = nil
		@setupMenuScroll @treeMenu

		@_selectedExprItem = nil
		@changeExprItem = (button)->
			@_selectedExprItem.checked = false if @_selectedExprItem
			@_selectedExprItem = button.checked and button or nil
			if button.checked
				@editMenu.visible = true
				{:expr,:parentExpr,:index} = button
				isRoot = (index == nil)
				isLeaf = switch expr[1]
					when "Con","Act" then true
					else false
				@addBtn.text = isLeaf and "Append" or "Add"
				edit = not isRoot
				insert = not isRoot
				add = true
				del = not isRoot
				up = index and ((isRoot and index > 3) or (not isRoot and index > 2))
				down = index and index < #parentExpr
				buttons = for v,k in pairs {:edit,:insert,:add,:del,:up,:down}
					if k then v
					else continue
				@showEditButtons buttons
			else
				@editMenu.visible = false

		@editBtn\slot "Tapped",->
			selectedExprItem = @_selectedExprItem
			if selectedExprItem
				{:expr,:parentExpr,:index} = selectedExprItem
				with ExprChooser {
						valueType:"AINode"
						expr:expr
						parentExpr:parentExpr
						owner:@
					}
					.previewItem.visible = false
					.backBtn.visible = false
					\slot "Result",(newExpr)->
						parentExpr[index] = newExpr
						selectedExprItem.expr = newExpr

		@addBtn\slot "Tapped",->
			selectedExprItem = @_selectedExprItem
			{:expr,:parentExpr,:index} = selectedExprItem
			with ExprChooser {
					valueType:"AINode"
					parentExpr:expr
					owner:@
				}
				.previewItem.visible = false
				.backBtn.visible = false
				\slot "Result",(newExpr)->
					return unless newExpr
					switch expr[1]
						when "Con","Act"
							table.insert parentExpr,index+1,newExpr
						else
							table.insert expr,newExpr
					@alignNodes!

		@insertBtn\slot "Tapped",->
			selectedExprItem = @_selectedExprItem
			{:expr,:parentExpr,:index} = selectedExprItem
			with ExprChooser {
					valueType:"AINode"
					parentExpr:expr
					owner:@
				}
				.previewItem.visible = false
				.backBtn.visible = false
				\slot "Result",(newExpr)->
					return unless newExpr
					table.insert parentExpr,index,newExpr
					@alignNodes!

	loadExpr:(arg)=>
		offset = @offset
		@offset = oVec2.zero
		@treeMenu\removeAllChildrenWithCleanup!
		@drawNode = with CCDrawNode!
			.anchor = oVec2.zero
			.contentSize = @treeMenu.contentSize
		@treeMenu\addChild @drawNode
		@items = {}
		@exprData = switch type arg
			when "table" then arg
			when "string"
				@filename = arg
				TriggerDef.SetExprMeta dofile arg
		@alignNodes!
		@offset = offset

	alignNodes:=>
		return unless @exprData
		{positionX:rootX, positionY:rootY} = @treeMenu.children[1]
		drawNode = @drawNode
		drawNode\clear!
		right,bottom = rootX,rootY
		white = ccColor4!
		drawLink = (x,y,startY)->
			start = oVec2 x-MenuW/2+20,startY+MenuH/2+10
			mid = oVec2 start.x,y
			stop = oVec2 start.x+20,y
			drawNode\drawSegment start,mid,0.5,white
			drawNode\drawSegment mid,stop,0.5,white
		nextNode = (parentExpr,index,x,y)->
			expr = index and parentExpr[index] or parentExpr
			return unless "table" == type expr
			right = math.max x,right
			bottom = math.min y,bottom
			node = @items[expr]
			if not node
				node = with MenuItem {
						expr:expr
						index:index
						parentExpr:parentExpr
						width:MenuW
						height:MenuH
					}
					\slot "Tapped",@changeExprItem
				@treeMenu\addChild node
				@items[expr] = node
			switch expr[1]
				when "AIRoot"
					node.position = oVec2 x,y
					y -= (MenuH+10)
					startY = y
					yCount = 1
					for i = 3, #expr
						drawLink x,y,startY
						yLevel = nextNode expr,i,x+40,y
						yCount += yLevel
						y -= (MenuH+10)*yLevel
					return yCount
				when "Con","Act"
					node.position = oVec2 x,y
					return 1
				else
					node.position = oVec2 x,y
					y -= (MenuH+10)
					startY = y
					yCount = 1
					for i = 2, #expr
						drawLink x,y,startY
						yLevel = nextNode expr,i,x+40,y
						yCount += yLevel
						y -= (MenuH+10)*yLevel
					return yCount
		nextNode @exprData,nil,10+MenuW/2,@treeMenu.height-10-MenuH/2
		@viewSize = CCSize right-rootX+MenuW+20,rootY-bottom+MenuH+20

	showEditButtons:(names)=>
		buttonSet = {@["#{ name }Btn"],true for name in *names}
		posY = @editMenu.height-35
		for i = 1,#@editMenu.children
			child = @editMenu.children[i]
			if buttonSet[child]
				child.positionY = posY
				child.visible = true
				child.scaleX = 0
				child.scaleY = 0
				child\perform child.scale
				posY -= 60
			else
				child.visible = false
