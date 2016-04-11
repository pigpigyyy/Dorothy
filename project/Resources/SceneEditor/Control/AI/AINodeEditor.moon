Dorothy!
EditorView = require "View.Control.Trigger.Editor"
AINodeExprEditor = require "Control.AI.AINodeExprEditor"
MenuItem = require "Control.Trigger.MenuItem"
SelectionPanel = require "Control.Basic.SelectionPanel"
InputBox = require "Control.Basic.InputBox"
MessageBox = require "Control.Basic.MessageBox"
TriggerDef = require "Data.TriggerDef"
SolidRect = require "View.Shape.SolidRect"
import Expressions,ToEditText from TriggerDef
import CompareTable,Path from require "Data.Utils"

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
					exprEditor = with AINodeExprEditor {
							x:panelW/2+listMenuW/2
							y:panelH/2
							width:panelW-listMenuW
							height:panelH-20
							exprLevel:editor.levelAINodeExpr
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

		if CCUserDefault.TriggerMode == nil
			CCUserDefault.TriggerMode = "Text"
			TriggerDef.CodeMode = false
		else
			TriggerDef.CodeMode = (CCUserDefault.TriggerMode == "Code")

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
		files = Path.getAllFiles path,"node"
		for i = 1,#files
			files[i] = prefix..files[i]
		filesToAdd,filesToDel = CompareTable @files,files
		allItemsUpdated = #filesToDel == #@files
		@files = files
		for file in *filesToAdd
			appendix = Path.getFilename file
			group = file\sub #prefix+1,-#appendix-2
			item = with MenuItem {
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
		{:width,:height} = CCDirector.winSize
		mask = SolidRect :width,:height,color:0xaa000000
		with EditorView title:"AI Condition Node", scope:false, width:width*0.8, height:height*0.7,editorLevel:editor.levelAINodeEditor,menuLevel:editor.levelAINodeMenu
			\addChild mask,-1,-1

	__init:(args)=>
		{width:panelW,height:panelH} = @panel

		TriggerScope.scrollArea = @listScrollArea
		TriggerScope.panel = @panel

		@localScope = TriggerScope @localListMenu,
			"aiNodeFullPath",
			"aiNodeFolder"

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
								"Delete Nodes\nBut Keep Group\n#{scope.currentGroup}"
							else
								"Delete Group\n#{scope.currentGroup}\nWith Nodes"
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
			with InputBox text:"New Node Name"
				\slot "Inputed",(result)->
					return unless result
					if not result\match("^[_%a][_%w]*$")
						MessageBox text:"Invalid Name!",okOnly:true
					else
						scope = @localScope
						triggerFullPath = scope.path..scope.currentGroup.."/"..result..".node"
						if oContent\exist triggerFullPath
							MessageBox text:"Node Exist!",okOnly:true
						else
							trigger = Expressions.ConditionNode\Create!
							trigger[2][2] = result
							oContent\saveToFile triggerFullPath,ToEditText trigger
							scope\updateItems!
							triggerFile = scope.prefix..scope.currentGroup.."/"..result..".node"
							for item in *scope.menu.children
								if item.file == triggerFile
									item\emit "Tapped",item
									break

		@addBtn\slot "Tapped",->
			MessageBox text:"Place Nodes In\nFolders Under\n/Logic/AI/Node/",okOnly:true

		@delBtn\slot "Tapped",->
			triggerBtn = TriggerScope.triggerBtn
			if triggerBtn
				with MessageBox text:"Delete Node\n#{triggerBtn.text}"
					\slot "OK",(result)->
						return unless result
						oContent\remove editor.gameFullPath..triggerBtn.file
						@localScope\updateItems!
			else
				MessageBox text:"No Node Selected!",okOnly:true

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
						MessageBox text:"No Node Selected!",okOnly:true
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
					filename = newPath..".node"
					while oContent\exist filename
						count += 1
						filename = newPath..tostring(count)..".node"
					triggerName ..= tostring count if count > 1
					exprData = @copyBtn.targetData
					oldName = exprData[2][2]
					exprData[2][2] = triggerName
					oContent\saveToFile filename,ToEditText(exprData)
					exprData[2][2] = oldName
					scope\updateItems!
					@copyBtn.targetFile = nil
					@copyBtn.targetData = nil

		with @closeBtn
			.text = "Select"
			\slot "Tapped",->
				if @localScope.menuItems
					for item in *@localScope.menuItems
						exprEditor = item.exprEditor
						if exprEditor and exprEditor.modified
							exprEditor.modified = false
							exprEditor\save!
				if TriggerScope.triggerBtn
					@emit "Selected",TriggerScope.triggerBtn.file
				else
					@emit "Selected",nil
				@hide!

		@gslot "Scene.AINode.ChangeName",(triggerName)->
			TriggerScope.triggerBtn.text = triggerName
			file = TriggerScope.triggerBtn.file
			TriggerScope.triggerBtn.file = Path.getPath(file)..triggerName..".node"

		@closeEvent = @gslot "Scene.AINode.Close",-> @hide!

	show:(targetFile)=>
		@closeEvent.enabled = true
		with @getChildByTag -1
			.opacity = 0
			\perform oOpacity 0.3,1,oEase.OutQuad
		@panel\schedule once ->
			@localScope\updateItems!
			with @localScope
				files,items = .files,.items
				if targetFile and #files > 0
					for file in *files
						item = items[file]
						if file == targetFile and (not .triggerBtn or .triggerBtn.file ~= targetFile)
							item.checked = true
							TriggerScope.changeTrigger item
							.currentGroup = item.group
							@groupBtn.text = item.group
							break
		@visible = true
		@closeBtn.scaleX = 0
		@closeBtn.scaleY = 0
		@closeBtn\perform oScale 0.3,1,1,oEase.OutBack
		@panel.opacity = 0
		@panel\perform CCSequence {
			oOpacity 0.3,1,oEase.OutQuad
			CCCall ->
				@listScrollArea.touchEnabled = true
				@localListMenu.enabled = true
				@editMenu.enabled = true
				@opMenu.enabled = true
		}

	hide:=>
		@closeEvent.enabled = false
		@listScrollArea.touchEnabled = false
		@localListMenu.enabled = false
		@editMenu.enabled = false
		@opMenu.enabled = false
		@closeBtn\perform oScale 0.3,0,0,oEase.InBack
		@panel\perform oOpacity 0.3,0,oEase.OutQuad
		with @getChildByTag -1
			\perform oOpacity 0.3,0,oEase.OutQuad
		@perform CCSequence {
			CCDelay 0.3
			CCHide!
		}
