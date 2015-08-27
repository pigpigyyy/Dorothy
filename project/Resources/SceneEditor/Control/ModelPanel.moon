Dorothy!
Class,property = unpack require "class"
ModelPanelView = require "View.Control.ModelPanel"
ModelView = require "Control.ModelView"
MessageBox = require "Control.MessageBox"
import CompareTable from require "Data.Utils"
-- [params]
-- x, y, width, height
Class
	__partial: (args)=> ModelPanelView args
	__init: (args)=>
		@_isCheckMode = true
		@modelItems = {}
		@_selectedItem = nil
		@selected = (item)->
			if @_isCheckMode
				if @_selectedItem
					viewItem = @modelItems[@_selectedItem]
					if viewItem and viewItem ~= item
						viewItem.checked = false
						viewItem\emit "TapEnded" 
					@_selectedItem = nil
				item.checked = not item.checked
				if item.checked
					@_selectedItem = item.file

		contentRect = CCRect.zero
		itemRect = CCRect.zero

		@scrollArea\slots "Scrolled",(delta)->
			contentRect\set 0,0,@scrollArea.width,@scrollArea.height
			@menu\eachChild (child)->
				child.position += delta
				{:positionX,:positionY,:width,:height} = child
				itemRect\set positionX-width/2,positionY-height/2,width,height
				child.visible = contentRect\intersectsRect itemRect -- reduce draw calls

		@scrollArea\slots "ScrollStart",->
			@menu.enabled = false

		@scrollArea\slots "ScrollEnd",->
			@menu.enabled = true

		@\slots "Cleanup",->
			oRoutine\remove @routine if @routine

		@\gslot "Editor.LoadModel",(paths)->
			@\runThread ->
				-- get model files
				models = {}
				visitResource = (path)->
					return unless oContent\exist path
					path = path\gsub("[\\/]*$","")
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
				for path in *paths do visitResource path

				{:width,:height} = @scrollArea

				i = 0
				if @models
					modelsToAdd,modelsToDel = CompareTable @models,models
					for model in *modelsToDel
						item = @modelItems[model]
						item.parent\removeChild item
						@modelItems[model] = nil
					for model in *modelsToAdd
						viewItem = ModelView {
							width: 100
							height: 100
							file: model
						}
						viewItem.visible = false
						viewItem\slots "Selected",@selected
						@menu\addChild viewItem
						@modelItems[model] = viewItem
						viewItem.opacity = 0
						viewItem\perform CCSequence {
							CCDelay i*0.1
							oOpacity 0.3,1
						}
						i += 1
				else
					if @modelItems
						for _,item in pairs @modelItems
							item.parent\removeChild item
					@modelItems = {}
					for model in *models
						viewItem = ModelView {
							width: 100
							height: 100
							file: model
						}
						viewItem\slots "Selected",@selected
						viewItem.visible = false
						@menu\addChild viewItem
						@modelItems[model] = viewItem
						viewItem.opacity = 0
						viewItem\perform CCSequence {
							CCDelay i*0.1
							oOpacity 0.3,1
						}
						i += 1
				@models = models

				y = height
				startY = height
				for i,model in ipairs @models
					i -= 1
					x = 60+(i%4)*110
					y = startY-60-math.floor(i/4)*110
					viewItem = @modelItems[model]
					viewItem.position = oVec2(x,y) + @scrollArea.offset
				y -= 60 if #@models > 0
				@scrollArea.viewSize = CCSize width,height-y

		@addBtn\slots "Tapped",->
			return unless @_selectedItem
			actionEditor = editor.actionEditor
			actionEditor\slots("Activated")\clear!
			actionEditor\slots "Activated",->
				actionEditor\edit @_selectedItem
			CCDirector\replaceScene CCScene\zoomFlip(0.5,actionEditor,CCOrientation.Down),false

	runThread: (task)=>
		oRoutine\remove @routine if @routine
		@routine = thread ->
			@scrollArea.touchEnabled = false
			@menu.enabled = false
			@opMenu.enabled = false
			@hint.visible = true
			@hint.opacity = 1
			@hint\perform @loopFade
			task!
			@hint\stopAction @loopFade
			@hint\perform CCSequence {
				oOpacity 0.3,0,oEase.OutQuad
				CCHide!
			}
			@opMenu.enabled = true
			@menu.enabled = true
			@scrollArea.touchEnabled = true
			@routine = nil
