Dorothy!
Class,property = unpack require "class"
SpritePanelView = require "View.Control.SpritePanel"
TabButton = require "Control.TabButton"
SpriteView = require "Control.SpriteView"
import Set from require "Data.Utils"
-- [params]
-- x, y, width, height
Class
	__partial: (args)=> SpritePanelView args
	__init: (args)=>
		@_isSelecting = false
		@selectedImages = {}
		@selectedClips = {}
		@viewItemChecked = (checked,item)->
			if @selectedImages
				@selectedImages[item.file] = if checked then true else nil
		@clipItemChecked = (checked,item)->
			if @selectedClips
				@selectedClips[item.file] = if checked then true else nil

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

		@\gslot "Editor.LoadSprite",(paths)->
			if @routine and @paths
				needUpdate = false
				pathSet = Set @paths
				for path in *paths
					if not pathSet[path]
						needUpdate = true
						break
				needUpdate = true if #@paths ~= #paths
				return unless needUpdate
			else @paths = paths

			oRoutine\remove @routine if @routine
			@routine = thread ->
				@\_setCheckMode false
				@opMenu.enabled = false
				@hint.visible = true
				@hint.opacity = 1
				@hint\perform @loopFade

				images = {}
				clips = {}
				visitResource = (path)->
					return unless oContent\exist path
					path = path\gsub("[\\/]*$","")
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

				for path in *paths do visitResource path

				{:width,:height} = @scrollArea

				i = 0
				if @clips
					clipsToDel = {}
					clipSet = Set clips
					for clip in *@clips
						if not clipSet[clip]
							table.insert clipsToDel,clip
					clipsToAdd = {}
					clipSet = Set @clips
					for clip in *clips
						if not clipSet[clip]
							table.insert clipsToAdd,clip

					for clipDel in *clipsToDel
						item = @clipItems[clipDel]
						item.parent\removeChild item
						@clipItems[clipDel] = nil
						expandItems = @clipExpands[clipDel]
						if expandItems
							for expItem in *expandItems
								expItem.parent\removeChild expItem
							@clipExpands[clipDel] = nil
					for clipAdd in *clipsToAdd
						@clipItems[clipAdd] = @\_addClipTab clipAdd,i
						i += 1
				else
					if @clipItems
						for clip,item in pairs @clipItems
							item.parent\removeChild item
							expandItems = @clipExpands[clip]
							if expandItems
								for expItem in *expandItems
									expItem.parent\removeChild expItem
								@clipExpands[clip] = nil
					@clipItems = {}
					@clipExpands = {}
					table.sort clips,(a,b)-> a\match("[\\/]([^\\/]*)$") < b\match("[\\/]([^\\/]*)$")
					for clip in *clips
						sleep!
						clipTab = @\_addClipTab clip,i
						i += 1
						clipTab.visible = false
						@clipItems[clip] = clipTab
				@clips = clips

				if @images
					imagesToDel = {}
					imageSet = Set images
					for image in *@images
						if not imageSet[image]
							table.insert imagesToDel,image
					imagesToAdd = {}
					imageSet = Set @images
					for image in *images
						if not imageSet[image]
							table.insert imagesToAdd,image

					for imageDel in *imagesToDel
						item = @imageItems[imageDel]
						item.parent\removeChild item
						@imageItems[imageDel] = nil
					for imageAdd in *imagesToAdd
						sleep!
						viewItem = SpriteView {
							file: imageAdd
							width: 100
							height: 100
							needUnload: true
						}
						viewItem.visible = false
						viewItem.enabled = false
						viewItem\slots "Checked",@viewItemChecked
						@menu\addChild viewItem
						@imageItems[imageAdd] = viewItem
						viewItem.opacity = 0
						viewItem\perform CCSequence {
							CCDelay i*0.1
							oOpacity 0.3,1
						}
						i += 1
					table.sort images,(a,b)-> a\match("[\\/]([^\\/]*)$") < b\match("[\\/]([^\\/]*)$")
				else
					if @imageItems
						for _,item in pairs @imageItems
							item.parent\removeChild item
					@imageItems = {}
					table.sort images,(a,b)-> a\match("[\\/]([^\\/]*)$") < b\match("[\\/]([^\\/]*)$")
					for image in *images
						sleep!
						viewItem = SpriteView {
							file: image
							width: 100
							height: 100
							needUnload: true
						}
						viewItem\slots "Checked",@viewItemChecked
						viewItem.visible = false
						viewItem.enabled = false
						@menu\addChild viewItem
						@imageItems[image] = viewItem
						viewItem.opacity = 0
						viewItem\perform CCSequence {
							CCDelay i*0.1
							oOpacity 0.3,1
						}
						i += 1
				@images = images

				y = height
				startY = height
				for i,clip in ipairs @clips
					i -= 1
					y = startY-30-i*50
					clipTab = @clipItems[clip]
					clipTab.position = oVec2(width/2,y) + @scrollArea.offset
					expandItems = @clipExpands[clip]
					if expandItems
						startY -= clipTab.deltaY
						posY = y-20
						for i,expItem in ipairs expandItems
							i -= 1
							x = 60+(i%4)*110
							y = posY-60-math.floor(i/4)*110
							expItem.position = oVec2(x,y) + @scrollArea.offset
						y -= 30 if #expandItems > 0
				y -= 20 if #@clips > 0

				startY = y
				for i,image in ipairs @images
					i -= 1
					x = 60+(i%4)*110
					y = startY-60-math.floor(i/4)*110
					viewItem = @imageItems[image]
					viewItem.position = oVec2(x,y) + @scrollArea.offset
				y -= 60 if #@images > 0
				@scrollArea.viewSize = CCSize width,height-y

				@menu\eachChild (child)->
					if tolua.type child == "CCMenuItem"
						child.enabled = true
				@opMenu.enabled = true
				@hint\stopAction @loopFade
				@hint\perform CCSequence {
					oOpacity 0.3,0,oEase.OutQuad
					CCHide!
				}
				@routine = nil

		@addBtn.visible = false
		@delBtn.visible = false
		@groupBtn.visible = false
		@delGroupBtn.visible = false
		@modeBtn\slots "Tapped",->
			@\_setCheckMode not @_isSelecting
		@groupBtn\slots "Tapped",->
			images = [image for image,_ in pairs @selectedImages]
			if #images > 0
				ClipEditor = require "Control.ClipEditor"
				ClipEditor :images
		@delGroupBtn\slots "Tapped",->
			for clip,_ in pairs @selectedClips
				print clip

	_addClipTab: (clip,index)=>
		clipTab = TabButton {
			file: clip
			width: @scrollArea.width-20
			height: 40
			text: clip\match "[\\/]([^\\/]*)%.[^%.\\/]*$"
		}
		clipTab\slots "Expanded",(expanded)->
			if expanded
				posY = clipTab.positionY-20
				names = oCache.Clip\getNames clip
				texFile = oCache.Clip\getTextureFile clip
				@clipExpands[clip] = {}
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
						alias: #names
						needUnload: i == #names-1
					}
					viewItem.clip = clip
					@menu\addChild viewItem
					table.insert @clipExpands[clip],viewItem
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
				clipTab.deltaY = 0
				posY = clipTab.positionY-20-deltaY
				children = @menu\getChildren!
				for child in *children
					if child.clip == clip
						child.parent\removeChild child
					else
						child.positionY += deltaY if child.positionY < posY
				@clipExpands[clip] = nil
				with @scrollArea.viewSize
					@scrollArea.viewSize = CCSize .width,.height-deltaY
		clipTab\slots "Checked",@clipItemChecked
		clipTab.deltaY = 0
		clipTab.position += @scrollArea.offset
		clipTab.enabled = false
		@menu\addChild clipTab
		clipTab.opacity = 0
		clipTab\perform CCSequence {
			CCDelay (index or 0)*0.1
			oOpacity 0.3,0.4
		}
		clipTab

	_setCheckMode: (isSelecting)=>
		return if isSelecting == @_isSelecting
		@_isSelecting = isSelecting
		@modeBtn.color = ccColor3(isSelecting and 0xff0088 or 0x00ffff)
		show = -> CCSequence {
			CCShow!
			oScale 0,0,0
			oScale 0.3,1,1,oEase.OutBack
		}
		hide = -> CCSequence {
			oScale 0.3,0,0,oEase.InBack
			CCHide!
		}
		if isSelecting
			@addBtn\perform show!
			@delBtn\perform show!
			@groupBtn\perform show!
			@delGroupBtn\perform show!
		else
			@addBtn\perform hide!
			@delBtn\perform hide!
			@groupBtn\perform hide!
			@delGroupBtn\perform hide!
		@menu\eachChild (child)->
			if not child.clip
				child.isCheckMode = isSelecting
			else
				child.enabled = not isSelecting
