Dorothy!
Class,property = unpack require "class"
ClipEditorView = require "View.Control.ClipEditor"
Packer = require "Data.Packer"

Class
	__partial: (args)=> ClipEditorView args
	__init: (args)=>
		{:images} = args
		@\addImages images
		@scrollArea\slots "Scrolled",(delta)->
			@scrollArea.view\eachChild (child)->
				child.position += delta

		@okBtn\slots "Tapped",->
			InputBox = require "Control.InputBox"
			MessageBox = require "Control.MessageBox"
			inputBox = InputBox text:"New Group Name"
			inputBox\slots "Inputed",(name)->
				if name == "" or name\match("[\\/|:*?<>\"%.]") or oContent\exist(name..".clip")
					MessageBox text:"Invalid Name",okOnly:true
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
							oContent\saveToFile editor.gamePath..clipFile,xml
							oCache.Clip\update clipFile,xml
							-- save texture
							texFile = editor.graphicFolder..name..".png"
							@target\save editor.gamePath..texFile,CCImage.PNG
							oCache.Texture\add @target,texFile
							-- remove images
							for image in *images
								oContent\remove image
								oCache.Texture\unload image
							@\close true

		@cancelBtn\slots "Tapped",->
			@\close false

		CCDirector.currentScene\addChild @

	close: (result)=>
		@opMenu.enabled = false
		@\perform oOpacity 0.4,0
		@panel\perform CCSequence {
			CCSpawn {
				oScale 0.4,0,0,oEase.InBack
				oOpacity 0.4,0
			}
			CCCall ->
				@\emit "Grouped",result
				@parent\removeChild @
		}

	addImages: (images)=>
		@scrollArea.view\removeAllChildrenWithCleanup!
		{:width,:height} = @scrollArea
		blocks = {}
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
					oVec2 rect.right-2,rect.up-2
					oVec2 rect.left+2,rect.up-2
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
