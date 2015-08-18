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
		file = "file"
		target = CCRenderTarget w,h
		target\beginDraw!
		target\draw node
		target\endDraw!
		--target\save file..".png",CCImage.PNG
		xml = "<A A=\""..file..".png\">"
		for block in *blocks
			xml = xml.."<B A=\""..block.name.."\" B=\""..tostring(block.fit.x+2)..","..tostring(h-block.fit.y-2-block.h+4)..","..tostring(block.w-4)..","..tostring(block.h-4).."\"/>"
		xml = xml.."</A>"

		clipFile = file..".clip"
		modelFile = file..".model"
		texFile = file..".png"
		--oContent\saveToFile clipFile,xml
		oCache.Clip\update clipFile,xml
		tex = oCache.Texture\add target,texFile

		@scrollArea.view\addChild with CCSprite tex
			.opacity = 0
			.position = oVec2(w+20 <= width and width*0.5 or 10+w*0.5, h+20 <= height and height*0.5 or height*0.5-h*0.5-10)
			\addChild frame
			\runAction oOpacity 0.3,1

		@scrollArea.viewSize = CCSize w+20,h+20
		@scrollArea.padding = oVec2 w+20 <= width and 0 or 100,
																h+20 <= height and 0 or 100
		@scrollArea.offset = oVec2.zero
