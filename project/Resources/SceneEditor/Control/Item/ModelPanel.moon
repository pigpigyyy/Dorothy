emit = require "emit"
CCRect = require "CCRect"
oRoutine = require "oRoutine"
oContent = require "oContent"
sleep = require "sleep"
CCSequence = require "CCSequence"
CCDelay = require "CCDelay"
oOpacity = require "oOpacity"
oVec2 = require "oVec2"
CCSize = require "CCSize"
CCScene = require "CCScene"
oCache = require "oCache"
thread = require "thread"
oEase = require "oEase"
CCHide = require "CCHide"
ccColor3 = require "ccColor3"
CCShow = require "CCShow"
oScale = require "oScale"
CCSpawn = require "CCSpawn"
CCCall = require "CCCall"
Class,property = unpack require "class"
ModelPanelView = require "View.Control.Item.ModelPanel"
ModelView = require "Control.Item.ModelView"
MessageBox = require "Control.Basic.MessageBox"
InputBox = require "Control.Basic.InputBox"
import CompareTable from require "Data.Utils"
Reference = require "Data.Reference"

-- [signals]
-- "Selected",(modelFile)->
-- "Hide",->
-- [params]
-- x, y, width, height
Class ModelPanelView,
	__init: =>
		@_isCheckMode = false
		@modelItems = {}
		@_selectedItem = nil
		@selected = (item)->
			file = item.file
			if @_isCheckMode
				@clearSelection! if @_selectedItem ~= file
				item.checked = not item.checked
				@_selectedItem = if item.checked then file else nil
			elseif item.isLoaded
				@hide!
				@emit "Selected",file
			else
				MessageBox text:"Broken Model\nWith Data Error\nOr Missing Image",okOnly:true

		contentRect = CCRect.zero
		itemRect = CCRect.zero

		@scrollArea\slot "Scrolled",(delta)->
			contentRect\set 0,0,@scrollArea.width,@scrollArea.height
			@menu\eachChild (child)->
				child.position += delta
				{:positionX,:positionY,:width,:height} = child
				itemRect\set positionX-width/2,positionY-height/2,width,height
				child.visible = contentRect\intersectsRect itemRect -- reduce draw calls

		@scrollArea\slot "ScrollStart",->
			@menu.enabled = false

		@scrollArea\slot "ScrollTouchEnded",->
			@menu.enabled = true

		@slot "Cleanup",->
			oRoutine\remove @routine if @routine

		@gslot "Scene.ViewModel",->
			@show!

		@gslot "Scene.ClearModel",->
			@models = nil

		@gslot "Scene.ModelUpdated",(target)->
			viewItem = @modelItems[target]
			if viewItem and @models
				for i,model in ipairs @models
					if model == target
						table.remove @models,i
						break
				viewItem.parent\removeChild viewItem
				@modelItems[target] = nil

		@gslot "Scene.LoadModel",(resPath)->
			@runThread ->
				-- get model files
				models = {}
				resPath = resPath\gsub("[\\/]*$","")
				visitResource = (path)->
					return unless oContent\exist path
					files = oContent\getEntries path,false
					sleep!
					for file in *files
						extension = file\match "%.([^%.\\/]*)$"
						extension = extension\lower! if extension
						filename = path.."/"..file
						table.insert models,filename if extension == "model"
					folders = oContent\getEntries path,true
					for folder in *folders
						if folder ~= "." and folder ~= ".."
							visitResource path.."/"..folder
					if #files == 0 and #folders == 2 and path ~= resPath
						oContent\remove path
				visitResource resPath

				{:width,:height} = @scrollArea

				index = 0
				if @models
					modelsToAdd,modelsToDel = CompareTable @models,models
					for model in *modelsToDel
						item = @modelItems[model]
						item.parent\removeChild item
						@modelItems[model] = nil
						@playUpdateHint!
					for model in *modelsToAdd
						viewItem = ModelView {
							width: 100
							height: 100
							file: model
						}
						viewItem.visible = false
						viewItem\slot "Selected",@selected
						@menu\addChild viewItem
						@playUpdateHint!
						sleep!
						@modelItems[model] = viewItem
						viewItem.opacity = 0
						viewItem\perform CCSequence {
							CCDelay index*0.1
							oOpacity 0.3,1
						}
						index += 1
				else
					if @modelItems
						@playUpdateHint!
						for _,item in pairs @modelItems
							item.parent\removeChild item
					@modelItems = {}
					for model in *models
						viewItem = ModelView {
							width: 100
							height: 100
							file: model
						}
						viewItem\slot "Selected",@selected
						viewItem.visible = false
						@menu\addChild viewItem
						@playUpdateHint!
						sleep!
						@modelItems[model] = viewItem
						viewItem.opacity = 0
						viewItem\perform CCSequence {
							CCDelay index*0.1
							oOpacity 0.3,1
						}
						index += 1
				table.sort models,(a,b)->
					a\match("[\\/]([^\\/]*)$") < b\match("[\\/]([^\\/]*)$")
				@models = models

				itemCount = math.floor (@panel.width-10)/110
				startY = height-40
				y = startY
				for i,model in ipairs @models
					i -= 1
					x = 60+(i%itemCount)*110
					y = startY-60-math.floor(i/itemCount)*110
					viewItem = @modelItems[model]
					viewItem.position = oVec2(x,y) + @scrollArea.offset
				y -= 60 if #@models > 0
				@scrollArea.viewSize = CCSize width,height-y

		@modeBtn\slot "Tapped",->
			return if Reference.isUpdating!
			@isCheckMode = not @isCheckMode

		@addBtn\slot "Tapped",->
			@clearSelection!
			with InputBox text:"New Model Name"
				\slot "Inputed",(name)->
					return unless name
					if name == "" or name\match("[\\/|:*?<>\"%.]")
						MessageBox text:"Invalid Name!",okOnly:true
						return
					for model,_ in pairs @modelItems
						if name == model\match("([^\\/]*)%.[^%.\\/]*$")
							MessageBox text:"Name Exist!",okOnly:true
							return
					actionEditor = editor.actionEditor
					actionEditor\slot("Activated")\set ->
						oFileChooser = require "ActionEditor.Script.oFileChooser"
						oFileChooser(true,true,name)
					CCScene\forward "actionEditor","rollOut"

		@delBtn\slot "Tapped",->
			if not @_selectedItem
				MessageBox text:"No Model Selected",okOnly:true
				return
			return unless Reference.isRemovable @_selectedItem
			with MessageBox text:"Delete Model\n"..@_selectedItem\match("([^\\/]*)%.[^%.\\/]*$")
				\slot "OK",(result)->
					return unless result
					MessageBox(text:"Confirm This\nDeletion")\slot "OK",(result)->
						return unless result
						@runThread ->
							oCache.Model\unload @_selectedItem
							oContent\remove @_selectedItem
							Reference.removeRef @_selectedItem
							viewItem = @clearSelection!
							viewItem\perform oOpacity 0.3,0
							sleep 0.3
							editor\updateModels!

		@editBtn\slot "Tapped",->
			if not @_selectedItem
				MessageBox text:"No Model Selected",okOnly:true
				return
			targetItem = @_selectedItem
			viewItem = @modelItems[targetItem]
			if viewItem.isLoaded
				@clearSelection!
				editor\edit "Model",targetItem
			else
				MessageBox text:"Broken Model\nWith Data Error\nOr Missing Image",okOnly:true

		@closeBtn\slot "Tapped",-> @hide!

		@addBtn.visible = false
		@delBtn.visible = false
		@editBtn.visible = false

	playUpdateHint: =>
		if not @hint.visible
			@hint.visible = true
			@hint.opacity = 1
			@hint\perform @loopFade

	runThread: (task)=>
		oRoutine\remove @routine if @routine
		@routine = thread ->
			@scrollArea.touchEnabled = false
			@menu.enabled = false
			@opMenu.enabled = false
			task!
			@hint\perform CCSequence {
				oOpacity 0.3,0,oEase.OutQuad
				CCHide!
			}
			@opMenu.enabled = true
			@menu.enabled = true
			@scrollArea.touchEnabled = true
			@routine = nil

	clearSelection: =>
		if @_selectedItem
			viewItem = @modelItems[@_selectedItem]
			if viewItem
				viewItem.checked = false
				@_selectedItem = nil
			viewItem
		else nil

	isCheckMode: property => @_isCheckMode,
		(value)=>
			return if @_isCheckMode == value
			@_isCheckMode = value
			@clearSelection! unless value
			@modeBtn.color = ccColor3(value and 0xff0088 or 0x00ffff)
			@modeBtn.face.cascadeOpacity = not value
			show = (index)-> CCSequence {
				CCDelay 0.1*index
				CCShow!
				oScale 0,0,0
				oScale 0.3,1,1,oEase.OutBack
			}
			hide = (index)-> CCSequence {
				CCDelay 0.1*index
				oScale 0.3,0,0,oEase.InBack
				CCHide!
			}
			if value
				@addBtn\perform show 0
				@delBtn\perform show 1
				@editBtn\perform show 2
				@hint.positionX = @panel.width-(@panel.width-240)/2
			else
				@addBtn\perform hide 2
				@delBtn\perform hide 1
				@editBtn\perform hide 0
				@hint.positionX = @panel.width-(@panel.width-60)/2

	show: =>
		@perform CCSequence {
			CCShow!
			oOpacity 0.3,0.6,oEase.OutQuad
		}
		@closeBtn.scaleX = 0
		@closeBtn.scaleY = 0
		@closeBtn\perform oScale 0.3,1,1,oEase.OutBack
		@panel.opacity = 0
		@panel.scaleX = 0
		@panel.scaleY = 0
		@panel\perform CCSequence {
			CCSpawn {
				oOpacity 0.3,1,oEase.OutQuad
				oScale 0.3,1,1,oEase.OutBack
			}
			CCCall ->
				@scrollArea.touchEnabled = true
				@menu.enabled = true
				@opMenu.enabled = true
				editor\updateModels!
		}

	hide: =>
		@isCheckMode = false
		@scrollArea.touchEnabled = false
		@menu.enabled = false
		@opMenu.enabled = false
		@closeBtn\perform oScale 0.3,0,0,oEase.InBack
		@panel\perform CCSpawn {
			oOpacity 0.3,0,oEase.OutQuad
			oScale 0.3,0,0,oEase.InBack
		}
		@perform CCSequence {
			oOpacity 0.3,0,oEase.OutQuad
			CCHide!
			CCCall -> @emit "Hide"
		}
