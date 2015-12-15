oContent = require "oContent"
editor = require "editor"
oCache = require "oCache"
emit = require "emit"
CCImage = require "CCImage"
CCDirector = require "CCDirector"
oOpacity = require "oOpacity"
oScale = require "oScale"
oEase = require "oEase"
CCSequence = require "CCSequence"
CCSpawn = require "CCSpawn"
CCCall = require "CCCall"
ccBlendFunc = require "ccBlendFunc"
CCSprite = require "CCSprite"
oVec2 = require "oVec2"
oLine = require "oLine"
ccColor4 = require "ccColor4"
CCNode = require "CCNode"
CCRect = require "CCRect"
CCRenderTarget = require "CCRenderTarget"
CCSize = require "CCSize"
Class = unpack require "class"
ClipEditorView = require "View.Control.Item.ClipEditor"
InputBox = require "Control.Basic.InputBox"
MessageBox = require "Control.Basic.MessageBox"
Packer = require "Data.Packer"
Reference = require "Data.Reference"

Class ClipEditorView,
	__init: (args)=>
		{:images} = args
		@addImages images
		@scrollArea\slots "Scrolled",(delta)->
			@scrollArea.view\eachChild (child)->
				child.position += delta

		@okBtn\slots "Tapped",->
			inputBox = InputBox text:"New Group Name"
			inputBox\slots "Inputed",(name)->
				return unless name
				if name == "" or name\match("[\\/|:*?<>\"%.]")
					MessageBox text:"Invalid Name!",okOnly:true
				elseif oContent\exist(name..".clip")
					MessageBox text:"Name Exist!",okOnly:true
				else
					msgBox = MessageBox text:"Group Name\n"..name
					msgBox\slots "OK",(result)->
						if result
							-- save clip
							xml = "<A A=\""..name..".png\">"
							h = @target.height
							for block in *@blocks
								xml ..= "<B A=\""..block.name
								xml ..= "\" B=\""
								xml ..= tostring(block.fit.x+2)..","
								xml ..= tostring(h-block.fit.y-2-block.h+4)..","
								xml ..= tostring(block.w-4)..","
								xml ..= tostring(block.h-4).."\"/>"
							xml = xml.."</A>"
							clipFile = editor.graphicFolder..name..".clip"
							oContent\saveToFile editor.gameFullPath..clipFile,xml
							oCache.Clip\update clipFile,xml
							emit "Scene.ClipUpdated",clipFile
							-- save texture
							texFile = editor.graphicFolder..name..".png"
							@target\save editor.gameFullPath..texFile,CCImage.PNG
							oCache.Texture\add @target,texFile
							-- remove images
							for image in *images
								oCache.Texture\unload image
								oContent\remove image
								Reference.removeRef image
							@close true

		@cancelBtn\slots "Tapped",->
			@close false

		CCDirector.currentScene\addChild @,2

	close: (result)=>
		@opMenu.enabled = false
		@perform oOpacity 0.3,0
		@okBtn\perform oScale 0.3,0,0,oEase.InBack
		@cancelBtn\perform oScale 0.3,0,0,oEase.InBack
		@panel\perform CCSequence {
			CCSpawn {
				oScale 0.3,0,0,oEase.InBack
				oOpacity 0.3,0
			}
			CCCall ->
				@emit "Grouped",result
				@parent\removeChild @
		}

	addImages: (images)=>
		@scrollArea.view\removeAllChildrenWithCleanup!
		{:width,:height} = @scrollArea
		blocks = {}
		for image in *images
			oCache.Texture\unload image
		CCImage.isPngAlphaPremultiplied = false
		blendFunc = ccBlendFunc ccBlendFunc.One,ccBlendFunc.Zero
		for image in *images
			sp = CCSprite image
			if sp
				sp.texture.antiAlias = false
				sp.blendFunc = blendFunc
				sp.anchor = oVec2.zero
				block = {
					w: sp.width+4
					h: sp.height+4
					sp: sp
					name: image\match "[\\/]([^\\/]*)%.[^%.\\/]*$"
				}
				table.insert blocks,block
		CCImage.isPngAlphaPremultiplied = true
		for image in *images
			oCache.Texture\unload image

		Packer\fit blocks
		w = Packer.root.w
		tmp = 2
		while tmp < w do tmp = tmp*2
		w = tmp
		h = Packer.root.h
		tmp = 2
		while tmp < h do tmp = tmp*2
		h = tmp
		frame = oLine {
			oVec2.zero
			oVec2 w,0
			oVec2 w,h
			oVec2 0,h
			oVec2.zero
		}, ccColor4 0x44ffffff

		node = CCNode()
		for block in *blocks
			with block
				if .fit
					.fit.y = h-.fit.y-.h
				rect = CCRect .fit.x, .fit.y, .w, .h
				line = oLine {
					oVec2 rect.left+2,rect.bottom+2
					oVec2 rect.right-2,rect.bottom+2
					oVec2 rect.right-2,rect.top-2
					oVec2 rect.left+2,rect.top-2
					oVec2 rect.left+2,rect.bottom+2
				}, ccColor4!
				frame\addChild line
				.sp.position = rect.origin + oVec2 2,2
				node\addChild .sp
		@blocks = blocks
		target = CCRenderTarget w,h
		target\beginDraw!
		target\draw node
		target\endDraw!
		@target = target

		posX = w+20 <= width and width*0.5 or 10+w*0.5
		posY = h+20 <= height and height*0.5 or height-h*0.5-10
		@scrollArea.view\addChild with target
			.opacity = 0
			.position = oVec2 posX,posY
			\addChild frame
			\runAction oOpacity 0.3,1

		@scrollArea.viewSize = CCSize w+20,h+20
		@scrollArea.padding = oVec2 w+20 <= width and 0 or 100,
																h+20 <= height and 0 or 100
		@scrollArea.offset = oVec2.zero
