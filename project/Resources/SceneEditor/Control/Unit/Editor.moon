Dorothy!
EditorView = require "View.Control.Unit.Editor"
SelectionItem = require "Control.Basic.SelectionItem"
SelectionPanel = require "Control.Basic.SelectionPanel"
AttributePanel = require "Control.Unit.AttributePanel"
InputBox = require "Control.Basic.InputBox"
MessageBox = require "Control.Basic.MessageBox"
import CompareTable,Path,Struct from require "Lib.Utils"
UnitDef = require "Control.Unit.UnitDef"
import UnitGroup,Unit from UnitDef
Array = Struct.Array

Class
	__partial:=>
		EditorView title:"Unit Editor"

	__init:(args)=>
		{width:panelW,height:panelH} = @panel
		@_groupOffset = {}
		@_currentGroup = "Default"
		@_unitGroup = nil

		@load!
		@listScrollArea\setupMenuScroll @listMenu

		lastGroupListOffset = oVec2.zero
		@groupBtn\slot "Tapped",->
			groups = for k,_ in pairs @itemGroups
				switch k
					when @currentGroup,"Default" then continue
					else k
			table.insert groups,1,"Default" if @currentGroup ~= "Default"
			table.insert groups,"<NEW>"
			table.insert groups,"<DEL>"
			with SelectionPanel {
					title:"Current Group"
					subTitle:@currentGroup
					width:180
					items:groups
					itemHeight:40
					fontSize:20
				}
				.scrollArea.offset = lastGroupListOffset
				.menu.children[#.menu.children-1].color = ccColor3 0x80ff00
				.menu.children.last.color = ccColor3 0xff0080
				\slot "Selected",(item)->
					return unless item
					lastGroupListOffset = .scrollArea.offset
					switch item
						when "<NEW>"
							with InputBox text:"New Group Name"
								\slot "Inputed",(result)->
									return unless result
									if not result\match("^[_%a][_%w]*$")
										MessageBox text:"Invalid Name!",okOnly:true
									elseif @itemGroups[result]
										MessageBox text:"Group Exist!",okOnly:true
									else
										@unitGroups\insert UnitGroup name:result,units:Array!
										@currentGroup = result
						when "<DEL>"
							text = if @currentGroup == "Default"
								"Delete Units\nBut Keep Group\n#{@currentGroup}"
							else
								"Delete Group\n#{@currentGroup}\nWith Units"
							with MessageBox text:text
								\slot "OK",(result)->
									return unless result
									@unitGroups\each (group,index)->
										if group.name == @currentGroup
											if @currentGroup == "Default"
												group\clear!
											else
												@unitGroups\remove index
									@currentGroup = "Default"
						else
							@currentGroup = item

		@closeBtn\slot "Tapped",-> @hide!

		@newBtn\slot "Tapped",->
			with InputBox text:"New Unit Name"
				\slot "Inputed",(result)->
					return unless result
					if not result\match("^[_%a][_%w]*$")
						MessageBox text:"Invalid Name!",okOnly:true
					else
						exist = false
						@_unitGroup.units\each (unit)->
							exist = true if unit.name == result
						if exist
							MessageBox text:"Unit Exist!",okOnly:true
						else
							@_unitGroup.units\insert Unit name:result

		@panel\addChild AttributePanel {
			x:panelW/2+@listMenu.width/2
			y:panelH/2
			width:panelW-@listMenu.width
			height:panelH-20
		}

	currentGroup:property => @_currentGroup,
		(value)=>
			@_currentGroup = value
			@groupBtn.text = value
			@_groupOffset[@_currentGroup] = @listScrollArea.offset
			itemGroup = @itemGroups[value]
			@_unitGroup = nil
			@unitGroups\each (unitGroup)->
				if unitGroup.name == value
					@_unitGroup = unitGroup
			return unless itemGroup
			with @listMenu
				\removeAllChildrenWithCleanup false
				for item in *itemGroup
					\addChild item
				@listScrollArea.offset = oVec2.zero
				@listScrollArea.viewSize = \alignItems!
				@listScrollArea.offset = @_groupOffset[@_currentGroup] or oVec2.zero

	load:=>
		@itemGroups = {}
		@slot "Cleanup",->
			for _,itemGroup in pairs @itemGroups
				for item in *itemGroup
					item\cleanup! unless item.parent
		notifyGroup = (groupEvent,_,group)->
			switch groupEvent
				when "Added"
					itemGroup = {}
					@itemGroups[group.name] = itemGroup
					group.units.__notify = (unitEvent,unitIndex,unit)->
						switch unitEvent
							when "Added"
								item = with SelectionItem {
										text:unit.name
										width:@listMenu.width-20
										height:35
									}
									.visible = false
									.unit = unit
									.group = group
									\slot "Tapped",(button)->
										if @selectedItem
											@selectedItem.checked = false
										@selectedItem = if button and button.checked then button else nil
								itemGroup[unitIndex] = item
								if group.name == @currentGroup
									@listMenu\addChild item
							when "Removed"
								item = itemGroup[unitIndex]
								if item.parent then item.parent\removeChild item
								else item\cleanup!
								table.remove itemGroup,unitIndex
							when "Updated"
								if @currentGroup == group.name
									offset = @listScrollArea.offset
									@listScrollArea.offset = oVec2.zero
									@listScrollArea.viewSize = @listMenu\alignItems!
									@listScrollArea.offset = offset
									@save!
				when "Removed"
					itemGroup = @itemGroups[group.name]
					for item in *itemGroup
						if item.parent then item.parent\removeChild item
						else item\cleanup!
					@itemGroups[group.name] = nil
				when "Updated"
					@save!

		unitFile = editor.dataFullPath.."Unit.def"
		if oContent\exist unitFile
			@unitGroups = Struct\loadfile unitFile
			if @unitGroups.count == 0
				@unitGroups\insert UnitGroup name:"Default",units:Array!
		else
			@unitGroups = Array!
			@unitGroups\insert UnitGroup name:"Default",units:Array!
			@save!
		@unitGroups.__notify = notifyGroup
		@currentGroup = "Default"

	save:=>
		unitFile = editor.dataFullPath.."Unit.def"
		oContent\saveToFile unitFile,"return "..tostring @unitGroups

	show:=>
		@visible = true
		@closeBtn.scaleX = 0
		@closeBtn.scaleY = 0
		@closeBtn\perform oScale 0.3,1,1,oEase.OutBack
		@panel.opacity = 0
		@panel\perform CCSequence {
			oOpacity 0.3,1,oEase.OutQuad
			CCCall ->
				@listScrollArea.touchEnabled = true
				@listMenu.enabled = true
				@editMenu.enabled = true
				@opMenu.enabled = true
		}

	hide:=>
		@listScrollArea.touchEnabled = false
		@listMenu.enabled = false
		@editMenu.enabled = false
		@opMenu.enabled = false
		@closeBtn\perform oScale 0.3,0,0,oEase.InBack
		@panel\perform oOpacity 0.3,0,oEase.OutQuad
		@perform CCSequence {
			CCDelay 0.3
			CCHide!
		}
