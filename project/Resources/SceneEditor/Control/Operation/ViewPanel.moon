Dorothy!
Class,property = unpack require "class"
ViewPanelView = require "View.Control.Operation.ViewPanel"
ViewItem = require "Control.Operation.ViewItem"

Class
	__partial: (args)=> ViewPanelView args
	__init: (args)=>
		width = @width
		height = @height
		itemW = 120
		itemH = 40
		@items = nil

		@\gslot "Editor.DataLoaded",(data)->
			@menu\removeAllChildrenWithCleanup!
			@items = {}

			drawNode = CCDrawNode!
			@menu\addChild drawNode

			right = 0
			bottom = 0
			addItem = (x,y,text,data)->
				item = ViewItem {
					text:text
					x:x
					y:y
					width:itemW
					height:itemH
				}
				item.itemData = data
				@menu\addChild item
				right = math.max x+itemW/2+10,right
				bottom = math.max y+itemH/2+10,bottom
				@items[data] = item

			getChildCount = (parent)->
				children = parent.children
				if children
					count = #children
					for child in *children
						count += getChildCount child
					count
				else
					0

			drawVLine = (itemData,initCount)->
				initCount or= 0
				itemCount = initCount + getChildCount itemData
				if itemCount > 0
					item = @items[itemData]
					startX = item.positionX-itemW/2+10
					startY = item.positionY-itemH/2
					endX = startX
					endY = startY-(itemH/2+10)-(itemCount-1)*(itemH+10)
					drawNode\drawSegment oVec2(startX,startY),oVec2(endX,endY),0.5,ccColor4!
					itemH/2+endY-endX
				else
					0

			drawHLine = (itemData)->
				item = @items[itemData]
				startX = item.positionX-item.width/2-10
				startY = item.positionY
				endX = startX+10
				endY = startY
				drawNode\drawSegment oVec2(startX,startY),oVec2(endX,endY),0.5,ccColor4!

			traverseData = (itemData,x,y)->
				if itemData == data
					addItem x,y,"Scene",data
					dV = drawVLine data,2
					x += 20
					y -= (10+itemH)
					addItem x,y,"Camera",data.camera
					drawVLine data.camera
					drawHLine data.camera
					y -= (10+itemH)
					addItem x,y,"UI",data.ui
					y -= drawVLine data.ui
					drawHLine data.ui
					if data.children
						for child in *data.children
							y -= (10+itemH)
							y -= traverseData child,x,y
					dV
				else
					addItem x,y,itemData.name,itemData
					dV = drawVLine itemData
					drawHLine itemData
					x += 20
					if itemData.children
						for child in *itemData.children
							y -= (10+itemH)
							y -= traverseData child,x,y
					dV

			itemX = 10+itemW/2
			itemY = height-10-itemH/2
			traverseData data,itemX,itemY
