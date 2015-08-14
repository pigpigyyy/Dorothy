Dorothy!
Class,property = unpack require "class"
SpritePanelView = require "View.Control.SpritePanel"

Class
	__partial: (args)=> SpritePanelView args
	__init: (args)=>
		@_isSelecting = false
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

		images = {}
		clips = {}

		visitResource = (path)->
			return unless oContent\exist path
			files = oContent\getEntries path,false
			sleep!
			for file in *files
				extension = file\match "%.([^%.\\/]*)$"
				extension = extension\lower! if extension
				filename = path.."/"..file
				switch extension
					when "png","jpg","jpeg","tiff","webp"
						clipFile = filename\match("(.*)%.[^%.\\/]*$")..".clip"
						table.insert images,filename unless oContent\exist clipFile
					when "clip"
						table.insert clips,filename
			folders = oContent\getEntries path,true
			sleep!
			for folder in *folders
				if folder ~= "." and folder ~= ".."
					visitResource path.."/"..folder

		@routine = thread ->
			@modeBtn.enabled = false
			@groupBtn.enabled = false
			@delGroupBtn.enabled = false
			@hint\perform @loopFade

			SpriteView = require "Control.SpriteView"
			sleep!
			visitResource "ActionEditor/Model/Input"
			visitResource oContent.writablePath.."Model"
			visitResource oContent.writablePath.."Body"
			visitResource oContent.writablePath.."Effect"

			{:width,:height} = @scrollArea
			y = 0
			startY = height
			TabButton = require "Control.TabButton"
			sleep!
			for i,clip in ipairs clips
				sleep!
				i -= 1
				y = startY-30-i*50
				clipTab = TabButton {
					x: width/2
					y: y
					width: width-20
					height: 40
					text: clip\match "[\\/]([^\\/]*)$"
					isClipTab: true
				}
				clipTab\slots "Expanded",(expanded)->
					if expanded
						posY = clipTab.positionY-20
						names = oCache.Clip\getNames clip
						texFile = oCache.Clip\getTextureFile clip
						newY = posY
						for i,name in ipairs names
							i -= 1
							spriteStr = clip.."|"..name
							newX = 60+(i%4)*110
							newY = posY-60-math.floor(i/4)*110
							viewItem = SpriteView {
								file: texFile
								spriteStr: spriteStr
								x: newX
								y: newY
								width: 100
								height: 100
							}
							viewItem.clip = clip
							@menu\addChild viewItem
						newY -= 50
						deltaY = posY - newY
						clipTab.deltaY = deltaY
						@menu\eachChild (child)->
							if child.clip ~= clip
								child.positionY -= deltaY if child.positionY < posY
						with @scrollArea.viewSize
							@scrollArea.viewSize = CCSize .width,.height+deltaY
					else
						deltaY = clipTab.deltaY
						posY = clipTab.positionY-20-deltaY
						children = @menu\getChildren!
						for child in *children
							if child.clip == clip
								child.parent\removeChild child
							else
								child.positionY += deltaY if child.positionY < posY
						with @scrollArea.viewSize
							@scrollArea.viewSize = CCSize .width,.height-deltaY
				clipTab.position += @scrollArea.offset
				clipTab.enabled = false
				@menu\addChild clipTab
				@scrollArea.viewSize = CCSize width,height-y
			y -= 20

			startY = y
			for i,image in ipairs images
				sleep!
				i -= 1
				x = 60+(i%4)*110
				y = startY-60-math.floor(i/4)*110
				viewItem = SpriteView {
					file: image
					x: x
					y: y
					width: 100
					height: 100
				}
				viewItem.position += @scrollArea.offset
				viewItem.enabled = false
				@menu\addChild viewItem
				@scrollArea.viewSize = CCSize width,height-y
			y -= 60

			@scrollArea.viewSize = CCSize width,height-y

			@menu\eachChild (child)->
				if tolua.type child == "CCMenuItem"
					child.enabled = true

			@modeBtn.enabled = true
			@groupBtn.enabled = true
			@delGroupBtn.enabled = true
			@hint\stopAction @loopFade
			@hint.opacity = 0
			@routine = nil

		@groupBtn.visible = false
		@delGroupBtn.visible = false
		@modeBtn\slots "Tapped",-> @\_setCheckMode not @_isSelecting

	_setCheckMode: (isSelecting)=>
		return if isSelecting == @_isSelecting
		@_isSelecting = isSelecting
		@modeBtn.color = ccColor3(isSelecting and 0xff0088 or 0x00ffff)
		if isSelecting
			@groupBtn\perform CCSequence {
				CCShow!
				oScale 0,0,0
				oScale 0.3,1,1,oEase.OutBack
			}
			@delGroupBtn\perform CCSequence {
				CCShow!
				oScale 0,0,0
				oScale 0.3,1,1,oEase.OutBack
			}
		else
			@groupBtn\perform CCSequence {
				oScale 0.3,0,0,oEase.InBack
				CCHide!
			}
			@delGroupBtn\perform CCSequence {
				oScale 0.3,0,0,oEase.InBack
				CCHide!
			}
		@menu\eachChild (child)->
			if not child.clip and not child.isClipTab
				child.isCheckMode = isSelecting
			else
				child.enabled = not isSelecting
