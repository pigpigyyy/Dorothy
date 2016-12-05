Dorothy!
ListPanelView = require "View.Control.Unit.ListPanel"
ListItem = require "Control.Unit.ListItem"
MessageBox = require "Control.Basic.MessageBox"

Class ListPanelView,
	__init:=>
		@_itemSource = nil
		@_operated = (listItem)->
			switch listItem.opText
				when "-"
					@_itemSource\removefor listItem.item
				when "+"
					if @_itemSource.count < 999
						@emit "AddToList",@_itemSource
					else
						MessageBox text:"List is full!",okOnly:true
		@addItem\slot "Operation",@_operated

	itemSource:property => @_itemSource,
		(value)=>
			@_itemSource = value
			value.__notify = (event,index,item)->
				switch event
					when "Added"
						@menu\addChild with ListItem text:item,width:@width-20,height:30
							.visible = false
							\slot "Operation",@_operated
						@menu.children\exchange #@menu.children,#@menu.children-1
					when "Removed"
						@menu\removeChild @menu.children[index]
					when "Updated"
						size = @menu\alignItems!
						@menu.contentSize = size
						@menu\alignItems!
						for child in *@menu.children
							child.visible = true
						@contentSize = CCSize size.width,size.height+30
						@menu.positionY = @height/2-15
						@title.positionY = @height-15
						@emit "SizeChanged",@

	enabled:property => @menu.enabled,
		(value)=> @menu.enabled = value
