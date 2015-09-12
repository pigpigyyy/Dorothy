Dorothy!
Class,property = unpack require "class"
EffectPanelView = require "View.Control.EffectPanel"
EffectView = require "Control.EffectView"
MessageBox = require "Control.MessageBox"
InputBox = require "Control.InputBox"
import CompareTable from require "Data.Utils"
-- [signals]
-- "Selected",(BodyFile)->
-- "Hide",->
-- [params]
-- x, y, width, height
Class
	__partial: (args)=> EffectPanelView args
	__init: (args)=>
		@_isCheckMode = false
		@effectItems = {}
		@_selectedItem = nil
		@selected = (item)->
			file = item.file
			if @_isCheckMode
				@\clearSelection! if @_selectedItem ~= file
				item.checked = not item.checked
				@_selectedItem = if item.checked then file else nil
			elseif item.isLoaded
				@\hide!
				emit "Scene.EffectSelected",file
			else
				MessageBox text:"Broken Effect\nWith Data Error",okOnly:true

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

		@\gslot "Scene.ViewEffect",->
			@\show!

		@\gslot "Scene.ClearEffect",->
			@effects = nil

		@\gslot "Scene.EffectUpdated",(target)->
			if not oCache.Particle\unload target
				oCache.Animation\unload target
			viewItem = @effectItems[target]
			if viewItem and @effects
				for i,effect in ipairs @effects
					if effect == target
						table.remove @effects,i
						break
				viewItem.parent\removeChild viewItem
				@effectItems[target] = nil

		@\gslot "Scene.LoadEffect",->
			@\runThread ->
				-- get effect files
				effects = {}
				effectFiles = {}
				effectFilename = editor.gameFullPath..editor.graphicFolder.."list.effect"
				if not oContent\exist effectFilename
					file = io.open effectFilename,"w"
					file\write "<A></A>"
					file\close!

				file = io.open effectFilename,"r"
				for item in file\read("*a")\gmatch("%b<>")
					if not item\sub(2,2)\match("[A/]")
						line = item\gsub "%s",""
						name = line\match "A=\"(.-)\""
						filename = line\match "B=\"(.-)\""
						table.insert effects,name
						effectFiles[name] = filename
				file\close()

				{:width,:height} = @scrollArea
				itemWidth = (@scrollArea.width-30)/2

				if @effects
					effectsToAdd,effectsToDel = CompareTable @effects,effects
					for effect in *effectsToDel
						item = @effectItems[effect]
						item.parent\removeChild item
						@effectItems[effect] = nil
						@\playUpdateHint!
					for effect in *effectsToAdd
						viewItem = EffectView {
							width: itemWidth
							height: 40
							file: effect
						}
						viewItem.visible = false
						viewItem\slots "Selected",@selected
						@menu\addChild viewItem
						@\playUpdateHint!
						sleep!
						@effectItems[effect] = viewItem
						viewItem.opacity = 0
				else
					if @effectItems
						@\playUpdateHint!
						for _,item in pairs @effectItems
							item.parent\removeChild item
					@effectItems = {}
					for effect in *effects
						viewItem = EffectView {
							width: itemWidth
							height: 40
							file: effect
						}
						viewItem\slots "Selected",@selected
						viewItem.visible = false
						@menu\addChild viewItem
						@\playUpdateHint!
						sleep!
						@effectItems[effect] = viewItem
						viewItem.opacity = 0
				table.sort effects
				@effects = effects
				@effectFiles = effectFiles

				i = 0
				itemCount = 2
				startY = height-40
				y = startY
				for i,effect in ipairs @effects
					i -= 1
					x = ((itemWidth/2+10))+(i%itemCount)*(itemWidth+10)
					y = startY-30-math.floor(i/itemCount)*50
					viewItem = @effectItems[effect]
					viewItem.position = oVec2(x,y) + @scrollArea.offset
					if viewItem.opacity == 0
						viewItem\perform CCSequence {
							CCDelay i*0.1
							oOpacity 0.3,1
						}
						i += 1
				y -= 30 if #@effects > 0
				@scrollArea.viewSize = CCSize width,height-y

		@modeBtn\slots "Tapped",->
			@isCheckMode = not @isCheckMode

		@addBtn\slots "Tapped",->
			@\clearSelection!
			with InputBox text:"New Effect Name"
				\slots "Inputed",(name)->
					return unless name
					if name == "" or name\match("[\\/|:*?<>\"%.]")
						MessageBox text:"Invalid Name!",okOnly:true
						return
					for effect in *@effects
						if name == effect
							MessageBox text:"Name Exist!",okOnly:true
							return
					effectEditor = editor.effectEditor
					effectEditor\slots("Activated")\set ->
						--effectEditor\new editor.graphicFolder..name..".body"
					CCScene\run "effectEditor","rollOut"

		@delBtn\slots "Tapped",->
			if not @_selectedItem
				MessageBox text:"No Effect Selected",okOnly:true
				return
			with MessageBox text:"Delete Effect\n"..@_selectedItem
				\slots "OK",(result)->
					return unless result
					MessageBox(text:"Confirm This\nDeletion")\slots "OK",(result)->
						return unless result
						@\runThread ->
							@effectFiles[@_selectedItem] = nil
							content = "<A>"
							for k,v in pairs @effectFiles
								content = content..string.format("<B A=\"%s\" B=\"%s\"/>",k,v)
								content = content.."</A>"
							oContent\saveToFile editor.gameFullPath..editor.graphicFolder.."list.effect",content
							@\clearSelection!
							sleep 0.3
							editor\updateEffects!

		@editBtn\slots "Tapped",->
			if not @_selectedItem
				MessageBox text:"No Effect Selected",okOnly:true
				return
			targetItem = @_selectedItem
			viewItem = @effectItems[targetItem]
			if viewItem.isLoaded
				@\clearSelection!
				bodyEditor = editor.bodyEditor
				bodyEditor\slots("Activated")\set ->
					bodyEditor\edit targetItem
				CCScene\run "bodyEditor","rollOut"
			else
				MessageBox text:"Broken Effect\nWith Data Error",okOnly:true

		@closeBtn\slots "Tapped",->
			@\hide!

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
			viewItem = @effectItems[@_selectedItem]
			if viewItem and viewItem ~= item
				viewItem.checked = false
				viewItem.face\runAction oOpacity 0.3,0.5,oEase.OutQuad
				@_selectedItem = nil

	isCheckMode: property => @_isCheckMode,
		(value)=>
			return if @_isCheckMode == value
			@_isCheckMode = value
			@\clearSelection! unless value
			@modeBtn.color = ccColor3(value and 0xff0088 or 0x00ffff)
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
		@\perform CCSequence {
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
				editor\updateEffects!
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
		@\perform CCSequence {
			oOpacity 0.3,0,oEase.OutQuad
			CCHide!
			CCCall -> @\emit "Hide"
		}
