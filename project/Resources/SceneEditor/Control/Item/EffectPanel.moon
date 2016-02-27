Dorothy!
EffectPanelView = require "View.Control.Item.EffectPanel"
EffectView = require "Control.Item.EffectView"
MessageBox = require "Control.Basic.MessageBox"
InputBox = require "Control.Basic.InputBox"
import CompareTable from require "Data.Utils"
Reference = require "Data.Reference"

-- [signals]
-- "Selected",(BodyFile)->
-- "Hide",->
-- [params]
-- x, y, width, height
Class EffectPanelView,
	__init:=>
		@_isCheckMode = false
		@effectItems = {}
		@_selectedItem = nil
		@selected = (item)->
			effectName = item.effect
			if @_isCheckMode
				@clearSelection! if @_selectedItem ~= effectName
				item.checked = not item.checked
				@_selectedItem = if item.checked then effectName else nil
			elseif item.isLoaded
				@hide!
				@emit "Selected",effectName
			else
				MessageBox text:"Broken Effect\nWith Data Error",okOnly:true

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

		@gslot "Scene.ViewEffect",->
			@show!

		@gslot "Scene.ClearEffect",->
			@effects = nil

		@gslot "Scene.EffectUpdated",(args)->
			{effect,effectFile} = args
			return unless effectFile
			if not oCache.Particle\unload effectFile
				oCache.Animation\unload effectFile
			viewItem = @effectItems[effect]
			if viewItem and @effects
				for i,effectName in ipairs @effects
					if effectName == effect
						table.remove @effects,i
						break
				viewItem.parent\removeChild viewItem
				@effectItems[effect] = nil

		@gslot "Scene.LoadEffect",->
			@runThread ->
				-- get effect files
				effects = {}
				effectFiles = {}
				effectFilename = editor.gameFullPath..editor.graphicFolder.."list.effect"
				if not oContent\exist effectFilename
					oContent\saveToFile effectFilename,"<A></A>"

				oCache.Effect\load effectFilename

				for item in oContent\loadFile(effectFilename)\gmatch("%b<>")
					if not item\sub(2,2)\match("[A/]")
						line = item\gsub "%s",""
						name = line\match "A=\"(.-)\""
						filename = line\match "B=\"(.-)\""
						if oContent\exist editor.graphicFolder..filename
							table.insert effects,name
							effectFiles[name] = filename

				{:width,:height} = @scrollArea
				itemHeight = 40
				itemWidth = (@scrollArea.width-30)/2

				if @effects
					effectsToAdd,effectsToDel = CompareTable @effects,effects
					for effect in *effectsToDel
						item = @effectItems[effect]
						item.parent\removeChild item
						@effectItems[effect] = nil
						@playUpdateHint!
					for effect in *effectsToAdd
						viewItem = EffectView {
							width: itemWidth
							height: itemHeight
							effect: effect
							file: effectFiles[effect]
						}
						viewItem.visible = false
						viewItem\slot "Selected",@selected
						@menu\addChild viewItem
						@playUpdateHint!
						sleep!
						@effectItems[effect] = viewItem
						viewItem.opacity = 0
				else
					if @effectItems
						@playUpdateHint!
						for _,item in pairs @effectItems
							item.parent\removeChild item
					@effectItems = {}
					for effect in *effects
						viewItem = EffectView {
							width: itemWidth
							height: itemHeight
							effect: effect
							file: effectFiles[effect]
						}
						viewItem\slot "Selected",@selected
						viewItem.visible = false
						@menu\addChild viewItem
						@playUpdateHint!
						sleep!
						@effectItems[effect] = viewItem
						viewItem.opacity = 0
				table.sort effects
				@effects = effects
				@effectFiles = effectFiles

				itemCount = 2
				startY = height-40
				y = startY
				for i,effect in ipairs @effects
					i -= 1
					x = ((itemWidth/2+10))+(i%itemCount)*(itemWidth+10)
					y = startY-(itemHeight/2+10)-math.floor(i/itemCount)*(itemHeight+10)
					viewItem = @effectItems[effect]
					viewItem.position = oVec2(x,y) + @scrollArea.offset
					if viewItem.opacity == 0
						viewItem\perform CCSequence {
							CCDelay i*0.1
							oOpacity 0.3,1
						}
						i += 1
				y -= (itemHeight/2+10) if #@effects > 0
				@scrollArea.viewSize = CCSize width,height-y

		@modeBtn\slot "Tapped",->
			return if Reference.isUpdating!
			@isCheckMode = not @isCheckMode

		@newBtn\slot "Tapped",->
			@clearSelection!
			SelectionPanel = require "Control.Basic.SelectionPanel"
			with SelectionPanel items:{"Particle","Frame"}
				\slot "Selected",(itemType)->
					return unless itemType
					with InputBox text:"New "..itemType.." Name"
						\slot "Inputed",(name)->
							return unless name
							if name == "" or name\match("[\\/|:*?<>\"%.]")
								MessageBox text:"Invalid Name!",okOnly:true
								return
							for effect in *@effects
								if name == effect
									MessageBox text:"Name Exist!",okOnly:true
									return
							effectEditor = with editor.effectEditor
								\setupEvent!
								\slot "Activated",->
									effectEditor["new"..itemType] effectEditor,name
								\slot "Quit",-> CCScene\back "rollIn"
								\hideEditor false,true
							CCScene\forward "effectEditor","rollOut"

		@addBtn\slot "Tapped",->
			@clearSelection!
			with InputBox text:"New Effect Name"
				\slot "Inputed",(name)->
					return unless name
					if name == "" or name\match("[\\/|:*?<>\"%.]")
						MessageBox text:"Invalid Name!",okOnly:true
						return
					for effect in *@effects
						if name == effect
							MessageBox text:"Name Exist!",okOnly:true
							return
					effectEditor = with editor.effectEditor
						\setupEvent!
						\slot("Activated")\set ->
							effectEditor\addExistFile name
						\slot "Quit",-> CCScene\back "rollIn"
						\hideEditor false,true
					CCScene\forward "effectEditor","rollOut"

		@delBtn\slot "Tapped",->
			if not @_selectedItem
				MessageBox text:"No Effect Selected",okOnly:true
				return
			with MessageBox text:"Delete Effect\n"..@_selectedItem
				\slot "OK",(result)->
					return unless result
					MessageBox(text:"Confirm This\nDeletion")\slot "OK",(result)->
						return unless result
						@runThread ->
							@effectFiles[@_selectedItem] = nil
							content = "<A>"
							for k,v in pairs @effectFiles
								content = content..string.format("<B A=\"%s\" B=\"%s\"/>",k,v)
								content = content.."</A>"
							effectFilename = editor.gameFullPath..editor.graphicFolder.."list.effect"
							oContent\saveToFile effectFilename,content
							oCache.Effect\load effectFilename
							emit "Scene.EffectUpdated",{@_selectedItem}
							viewItem = @clearSelection!
							viewItem\perform oOpacity 0.3,0
							sleep 0.3
							editor\updateEffects!

		@editBtn\slot "Tapped",->
			if not @_selectedItem
				MessageBox text:"No Effect Selected",okOnly:true
				return
			targetItem = @_selectedItem
			viewItem = @effectItems[targetItem]
			if viewItem.isLoaded
				@clearSelection!
				subEditor = editor\edit "Effect",targetItem,"rollOut","rollIn"
				subEditor\hideEditor false,false
			else
				MessageBox text:"Broken Effect\nWith Data Error",okOnly:true

		@closeBtn\slot "Tapped",->
			@hide!

		@newBtn.visible = false
		@addBtn.visible = false
		@delBtn.visible = false
		@editBtn.visible = false

	playUpdateHint:=>
		if not @hint.visible
			@hint.visible = true
			@hint.opacity = 1
			@hint\perform @loopFade

	runThread:(task)=>
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

	clearSelection:=>
		if @_selectedItem
			viewItem = @effectItems[@_selectedItem]
			if viewItem
				viewItem.checked = false
				@_selectedItem = nil
			viewItem
		else nil

	isCheckMode:property => @_isCheckMode,
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
				@newBtn\perform show 0
				@addBtn\perform show 1
				@delBtn\perform show 2
				@editBtn\perform show 3
				@hint.positionX = @panel.width-(@panel.width-240)/2
			else
				@newBtn\perform hide 3
				@addBtn\perform hide 2
				@delBtn\perform hide 1
				@editBtn\perform hide 0
				@hint.positionX = @panel.width-(@panel.width-60)/2

	show:=>
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
				editor\updateEffects!
		}

	hide:=>
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
