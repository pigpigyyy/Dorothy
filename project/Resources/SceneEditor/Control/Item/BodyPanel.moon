emit = require("emit")
CCRect = require("CCRect")
oRoutine = require "oRoutine"
oCache = require "oCache"
oContent = require "oContent"
CCSequence = require "CCSequence"
CCDelay = require "CCDelay"
oOpacity = require "oOpacity"
oVec2 = require "oVec2"
CCSize = require "CCSize"
CCScene = require "CCScene"
oEase = require "oEase"
CCHide = require "CCHide"
ccColor3 = require "ccColor3"
CCShow = require "CCShow"
oScale = require "oScale"
CCSpawn = require "CCSpawn"
CCCall = require "CCCall"
sleep = require "sleep"
thread = require "thread"
Class,property = unpack require "class"
BodyPanelView = require "View.Control.Item.BodyPanel"
BodyView = require "Control.Item.BodyView"
MessageBox = require "Control.Basic.MessageBox"
InputBox = require "Control.Basic.InputBox"
import CompareTable from require "Data.Utils"
Reference = require "Data.Reference"

-- [signals]
-- "Selected",(BodyFile)->
-- "Hide",->
-- [params]
-- x, y, width, height
Class
	__partial: (args)=> BodyPanelView args
	__init: =>
		@_isCheckMode = false
		@bodyItems = {}
		@_selectedItem = nil
		@selected = (item)->
			file = item.file
			if @_isCheckMode
				@clearSelection! if @_selectedItem ~= file
				item.checked = not item.checked
				@_selectedItem = if item.checked then file else nil
			elseif item.isLoaded
				@hide!
				emit "Scene.BodySelected",file
			else
				MessageBox text:"Broken Body\nWith Data Error",okOnly:true

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

		@scrollArea\slots "ScrollTouchEnded",->
			@menu.enabled = true

		@slots "Cleanup",->
			oRoutine\remove @routine if @routine

		@gslot "Scene.ViewBody",->
			@show!

		@gslot "Scene.ClearBody",->
			@bodies = nil

		@gslot "Scene.BodyUpdated",(target)->
			if oCache.Body
				oCache.Body\unload target
			viewItem = @bodyItems[target]
			if viewItem and @bodies
				for i,body in ipairs @bodies
					if body == target
						table.remove @bodies,i
						break
				viewItem.parent\removeChild viewItem
				@bodyItems[target] = nil

		@gslot "Scene.LoadBody",(resPath)->
			@runThread ->
				-- get body files
				bodies = {}
				resPath = resPath\gsub("[\\/]*$","")
				visitResource = (path)->
					return unless oContent\exist path
					files = oContent\getEntries path,false
					sleep!
					for file in *files
						extension = file\match "%.([^%.\\/]*)$"
						extension = extension\lower! if extension
						if extension == "body"
							filename = path.."/"..file
							table.insert bodies,filename
					folders = oContent\getEntries path,true
					for folder in *folders
						if folder ~= "." and folder ~= ".."
							visitResource path.."/"..folder
					if #files == 0 and #folders == 2 and path ~= resPath
						oContent\remove path
				visitResource resPath

				{:width,:height} = @scrollArea

				index = 0
				if @bodies
					bodiesToAdd,bodiesToDel = CompareTable @bodies,bodies
					for body in *bodiesToDel
						item = @bodyItems[body]
						item.parent\removeChild item
						@bodyItems[body] = nil
						@playUpdateHint!
					for body in *bodiesToAdd
						viewItem = BodyView {
							width: 100
							height: 100
							file: body
						}
						viewItem.visible = false
						viewItem\slots "Selected",@selected
						@menu\addChild viewItem
						@playUpdateHint!
						sleep!
						@bodyItems[body] = viewItem
						viewItem.opacity = 0
						viewItem\perform CCSequence {
							CCDelay index*0.1
							oOpacity 0.3,1
						}
						index += 1
				else
					if @bodyItems
						@playUpdateHint!
						for _,item in pairs @bodyItems
							item.parent\removeChild item
					@bodyItems = {}
					for body in *bodies
						viewItem = BodyView {
							width: 100
							height: 100
							file: body
						}
						viewItem\slots "Selected",@selected
						viewItem.visible = false
						@menu\addChild viewItem
						@playUpdateHint!
						sleep!
						@bodyItems[body] = viewItem
						viewItem.opacity = 0
						viewItem\perform CCSequence {
							CCDelay index*0.1
							oOpacity 0.3,1
						}
						index += 1
				@bodies = bodies

				itemCount = math.floor (@panel.width-10)/110
				startY = height-40
				y = startY
				for i,body in ipairs @bodies
					i -= 1
					x = 60+(i%itemCount)*110
					y = startY-60-math.floor(i/itemCount)*110
					viewItem = @bodyItems[body]
					viewItem.position = oVec2(x,y) + @scrollArea.offset
				y -= 60 if #@bodies > 0
				@scrollArea.viewSize = CCSize width,height-y

		@modeBtn\slots "Tapped",->
			return if Reference.isUpdating!
			@isCheckMode = not @isCheckMode

		@addBtn\slots "Tapped",->
			@clearSelection!
			with InputBox text:"New Body Name"
				\slots "Inputed",(name)->
					return unless name
					if name == "" or name\match("[\\/|:*?<>\"%.]")
						MessageBox text:"Invalid Name!",okOnly:true
						return
					for body,_ in pairs @bodyItems
						if name == body\match("([^\\/]*)%.[^%.\\/]*$")
							MessageBox text:"Name Exist!",okOnly:true
							return
					bodyEditor = editor.bodyEditor
					bodyEditor\slots("Activated")\set ->
						bodyEditor\new editor.physicsFolder..name..".body"
					CCScene\forward "bodyEditor","rollOut"

		@delBtn\slots "Tapped",->
			if not @_selectedItem
				MessageBox text:"No Body Selected",okOnly:true
				return
			return unless Reference.isRemovable @_selectedItem
			with MessageBox text:"Delete Body\n"..@_selectedItem\match("([^\\/]*)%.[^%.\\/]*$")
				\slots "OK",(result)->
					return unless result
					MessageBox(text:"Confirm This\nDeletion")\slots "OK",(result)->
						return unless result
						@runThread ->
							oCache.Body\unload @_selectedItem
							oContent\remove @_selectedItem
							Reference.removeRef @_selectedItem
							@clearSelection!
							sleep 0.3
							editor\updateBodies!

		@editBtn\slots "Tapped",->
			if not @_selectedItem
				MessageBox text:"No Body Selected",okOnly:true
				return
			targetItem = @_selectedItem
			viewItem = @bodyItems[targetItem]
			if viewItem.isLoaded
				@clearSelection!
				bodyEditor = editor.bodyEditor
				bodyEditor\slots("Activated")\set ->
					bodyEditor\edit targetItem
				CCScene\forward "bodyEditor","rollOut"
			else
				MessageBox text:"Broken Body\nWith Data Error",okOnly:true

		@closeBtn\slots "Tapped",->
			@hide!

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
			viewItem = @bodyItems[@_selectedItem]
			if viewItem
				viewItem.checked = false
				viewItem.face\runAction oOpacity 0.3,0.5,oEase.OutQuad
				@_selectedItem = nil

	isCheckMode: property => @_isCheckMode,
		(value)=>
			return if @_isCheckMode == value
			@_isCheckMode = value
			@clearSelection! unless value
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
				editor\updateBodies!
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
