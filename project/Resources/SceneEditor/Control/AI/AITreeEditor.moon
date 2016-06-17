Dorothy!
EditorView = require "View.Control.Trigger.Editor"
AITreeView = require "Control.AI.AITreeView"
SelectionItem = require "Control.Basic.SelectionItem"
ExprChooser = require "Control.Trigger.ExprChooser"
SelectionPanel = require "Control.Basic.SelectionPanel"
InputBox = require "Control.Basic.InputBox"
MessageBox = require "Control.Basic.MessageBox"
TriggerDef = require "Data.TriggerDef"
AINodeEditor = require "Control.AI.AINodeEditor"
import Expressions,ToEditText from TriggerDef
import CompareTable,Path from require "Lib.Utils"

TriggerScope = Class
	__initc:=>
		@scrollArea = nil
		@panel = nil
		@triggerBtn = nil
		@changeTrigger = (button)->
			if @triggerBtn
				@triggerBtn.checked = false
				@panel\removeChild @triggerBtn.exprEditor,false
			@triggerBtn = if button and button.checked then button else nil
			if @triggerBtn
				if not @triggerBtn.exprEditor
					{width:panelW,height:panelH} = @panel
					listMenuW = @scrollArea.width
					exprEditor = with AITreeView {
							x:panelW/2+listMenuW/2
							y:panelH/2
							width:panelW-listMenuW
							height:panelH-20
						}
						\loadExpr @triggerBtn.file
					@triggerBtn.exprEditor = exprEditor
					@triggerBtn\slot "Cleanup",->
						parent = exprEditor.parent
						if parent
							parent\removeChild exprEditor
						else
							exprEditor\cleanup!
				@panel\addChild @triggerBtn.exprEditor

	__init:(menu,path,prefix)=>
		@_menu = menu
		@_path = path
		@_prefix = prefix
		@_currentGroup = ""
		@_groups = nil
		@_groupOffset = {}
		@items = {}
		@files = {}

		@_menu\slot "Cleanup",->
			for _,item in pairs @items
				if item.parent
					item.parent\removeChild item
				else
					item\cleanup!

	updateItems:=>
		path = @path
		prefix = @prefix
		defaultFolder = path.."Default"
		oContent\mkdir defaultFolder unless oContent\exist defaultFolder
		@_groups = Path.getFolders path
		table.sort @_groups
		files = Path.getAllFiles path,"tree"
		for i = 1,#files
			files[i] = prefix..files[i]
		filesToAdd,filesToDel = CompareTable @files,files
		allItemsUpdated = #filesToDel == #@files
		@files = files
		for file in *filesToAdd
			appendix = Path.getFilename file
			group = file\sub #prefix+1,-#appendix-2
			item = with SelectionItem {
					text:Path.getName file
					width:@_menu.width-20
					height:35
				}
				.file = file
				.group = group
				\slot "Tapped",@@changeTrigger
			@items[file] = item
		for file in *filesToDel
			item = @items[file]
			if @@triggerBtn == item
				@@triggerBtn = nil
			if item.parent
				item.parent\removeChild item
			else
				item\cleanup!
			@items[file] = nil
		@currentGroup = (@_currentGroup == "" or allItemsUpdated) and "Default" or @_currentGroup

	currentGroup:property => @_currentGroup,
		(group)=>
			@_groupOffset[@_currentGroup] = @@scrollArea.offset
			@_currentGroup = group
			groupItems = for _,item in pairs @items
				continue if item.group ~= group
				item
			table.sort groupItems,(itemA,itemB)-> itemA.text < itemB.text
			with @_menu
				\removeAllChildrenWithCleanup false
				for item in *groupItems
					\addChild item
				@@scrollArea.offset = oVec2.zero
				@@scrollArea.viewSize = \alignItems!
				@@scrollArea.offset = @_groupOffset[@_currentGroup] or oVec2.zero

	menuItems:property => @_menu.children
	groups:property => @_groups
	prefix:property => editor[@_prefix]
	path:property => editor[@_path]
	menu:property => @_menu

Class
	__partial:=>
		EditorView title:"AI Tree Editor", scope:false

	__init:(args)=>
		{width:panelW,height:panelH} = @panel
		@firstDisplay = true

		TriggerScope.scrollArea = @listScrollArea
		TriggerScope.panel = @panel

		@localScope = TriggerScope @localListMenu,
			"aiTreeFullPath",
			"aiTreeFolder"

		@listScrollArea\setupMenuScroll @localListMenu
		@listScrollArea.viewSize = @localListMenu\alignItems!

		lastGroupListOffset = oVec2.zero
		@groupBtn\slot "Tapped",->
			scope = @localScope
			groups = for group in *scope.groups
				continue if group == "Default" or group == scope.currentGroup
				group
			table.insert groups,1,"Default" if scope.currentGroup ~= "Default"
			table.insert groups,"<NEW>"
			table.insert groups,"<DEL>"
			with SelectionPanel {
					title:"Current Group"
					subTitle:scope.currentGroup
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
									elseif oContent\exist scope.prefix..result
										MessageBox text:"Group Exist!",okOnly:true
									else
										oContent\mkdir scope.path..result
										scope\updateItems!
										scope.currentGroup = result
										@groupBtn.text = result
						when "<DEL>"
							text = if scope.currentGroup == "Default"
								"Delete AI Trees\nBut Keep Group\n#{scope.currentGroup}"
							else
								"Delete Group\n#{scope.currentGroup}\nWith AI Trees"
							with MessageBox text:text
								\slot "OK",(result)->
									return unless result
									Path.removeFolder scope.path..scope.currentGroup.."/"
									scope\updateItems!
									scope.currentGroup = "Default"
									@groupBtn.text = scope.currentGroup
						else
							scope.currentGroup = item
							@groupBtn.text = item

		@newBtn\slot "Tapped",->
			with InputBox text:"New AI Tree Name"
				\slot "Inputed",(result)->
					return unless result
					if not result\match("^[_%a][_%w]*$")
						MessageBox text:"Invalid Name!",okOnly:true
					else
						scope = @localScope
						triggerFullPath = scope.path..scope.currentGroup.."/"..result..".tree"
						if oContent\exist triggerFullPath
							MessageBox text:"AI Tree Exist!",okOnly:true
						else
							trigger = Expressions.AIRoot\Create!
							trigger[2][2] = result
							oContent\saveToFile triggerFullPath,ToEditText trigger
							codeFile = Path.getPath(triggerFullPath)..Path.getName(triggerFullPath)..".lua"
							triggerCode = TriggerDef.ToCodeText trigger
							oContent\saveToFile codeFile,triggerCode
							scope\updateItems!
							triggerFile = scope.prefix..scope.currentGroup.."/"..result..".tree"
							for item in *scope.menu.children
								if item.file == triggerFile
									item\emit "Tapped",item
									break

		@addBtn\slot "Tapped",->
			MessageBox text:"Place AI Trees In\nFolders Under\n/Logic/AI/Tree/",okOnly:true

		@delBtn\slot "Tapped",->
			triggerBtn = TriggerScope.triggerBtn
			if triggerBtn
				with MessageBox text:"Delete AI Tree\n#{triggerBtn.text}"
					\slot "OK",(result)->
						return unless result
						filename = editor.gameFullPath..triggerBtn.file
						oContent\remove filename
						oContent\remove Path.getPath(filename)..Path.getName(filename)..".lua"
						@localScope\updateItems!
			else
				MessageBox text:"No AI Tree Selected!",okOnly:true

		with @copyBtn
			.copying = false
			.targetFile = nil
			.targetData = nil
			\slot "Tapped",->
				@copyBtn.copying = not @copyBtn.copying
				if @copyBtn.copying
					@copyBtn.text = "Paste"
					@copyBtn.color = ccColor3 0xff0080
					triggerBtn = TriggerScope.triggerBtn
					if not triggerBtn
						MessageBox text:"No AI Tree Selected!",okOnly:true
						return
					@copyBtn.targetFile = triggerBtn.file
					@copyBtn.targetData = triggerBtn.exprEditor.exprData
				else
					@copyBtn.text = "Copy"
					@copyBtn.color = ccColor3 0x00ffff
					targetFilePath = editor.gameFullPath..@copyBtn.targetFile
					triggerName = Path.getName(targetFilePath).."Copy"
					scope = @localScope
					newPath = scope.path..scope.currentGroup.."/"..triggerName
					count = 0
					filename = newPath..".tree"
					while oContent\exist filename
						count += 1
						filename = newPath..tostring(count)..".tree"
					triggerName ..= tostring count if count > 1
					exprData = @copyBtn.targetData
					oldName = exprData[2][2]
					exprData[2][2] = triggerName
					oContent\saveToFile filename,ToEditText(exprData)
					exprData[2][2] = oldName
					scope\updateItems!
					@copyBtn.targetFile = nil
					@copyBtn.targetData = nil

		@closeBtn\slot "Tapped",->
			if @localScope.menuItems
				for item in *@localScope.menuItems
					exprEditor = item.exprEditor
					if exprEditor and exprEditor.modified
						exprEditor.modified = false
						exprEditor\save!
			@hide!

		@gslot "Scene.AITree.ChangeName",(triggerName)->
			TriggerScope.triggerBtn.text = triggerName
			file = TriggerScope.triggerBtn.file
			TriggerScope.triggerBtn.file = Path.getPath(file)..triggerName..".tree"

		@closeEvent = @gslot "Scene.AITree.Close",-> @hide!

		@gslot "Scene.AINode.Open",(args)->
			if not args
				@show!
				@aiNodeEditor\show!
				return
			{nodeFile,handleResult} = args
			if @aiNodeEditor
				@aiNodeEditor\show nodeFile
			else
				@aiNodeEditor = AINodeEditor!
				@aiNodeEditor\show nodeFile
				editor\addChild @aiNodeEditor
			@aiNodeEditor\slot("Selected")\set (result)->
				handleResult result
				emit "Scene.AINode.Edit"

		@gslot "Scene.AINode.Edit",->
			TriggerScope.triggerBtn.exprEditor.editBtn\emit "Tapped"

	currentTree:property =>
		if TriggerScope.triggerBtn
			TriggerScope.triggerBtn.file
		else
			nil,
		(value)=>
			item = @localScope.items[value]
			if item
				@localScope.currentGroup = item.group
				item\emit "Tapped",item

	show:=>
		@closeEvent.enabled = true
		@panel\schedule once ->
			@localScope\updateItems!
			@groupBtn.text = @localScope.currentGroup
			if @firstDisplay
				@firstDisplay = false
				if editor.startupData and editor.startupData.aiTree
					@currentTree = editor.startupData.aiTree
		@visible = true
		with @closeBtn
			.scaleX = 0
			.scaleY = 0
			\perform oScale 0.3,1,1,oEase.OutBack
		@panel.opacity = 0
		@panel\perform CCSequence {
			oOpacity 0.3,1,oEase.OutQuad
			CCCall ->
				@listScrollArea.touchEnabled = true
				@localListMenu.enabled = true
				@editMenu.enabled = true
				@opMenu.enabled = true
				for control in *editor.children
					switch control.__class
						when @@,ExprChooser,AINodeEditor
							continue
						else
							control.visibleState = control.visible
							control.visible = false
		}

	hide:=>
		@closeEvent.enabled = false
		for control in *editor.children
			switch control.__class
				when @@,ExprChooser,AINodeEditor
					continue
				else
					control.visible = control.visibleState
		@listScrollArea.touchEnabled = false
		@localListMenu.enabled = false
		@editMenu.enabled = false
		@opMenu.enabled = false
		@closeBtn\perform oScale 0.3,0,0,oEase.InBack
		@panel\perform oOpacity 0.3,0,oEase.OutQuad
		@perform CCSequence {
			CCDelay 0.3
			CCHide!
		}
