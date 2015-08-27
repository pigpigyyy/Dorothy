Dorothy!
Class,property = unpack require "class"
SpriteViewView = require "View.Control.SpriteView"
-- [params]
-- x, y, width, height, file
Class
	__partial: (args)=> SpriteViewView args
	__init: (args)=>
		{:width,:height,:file} = args
		@_loaded = false
		@file = file

		@\slots "Tapped",->
			if @_loaded
				@\emit "Selected",@

		thread ->
			@_loaded = false
			oCache\loadAsync file,-> @_loaded = true
			if not @_loaded
				name = file\match "[\\/]([^\\/]*)%.[^%.\\/]*$"
				@face\addChild with CCLabelTTF "[Model]\n"..name.."\n[Broken]","Arial",16
					.position = oVec2 width/2,height/2
					.texture.antiAlias = false
					.color = ccColor3 0x00ffff
				@routine = nil
				return
			model = oModel file
			minX = nil
			minY = nil
			maxX = nil
			maxY = nil
			model\traverse (child)->
				vs = {
					oVec2 0,0
					oVec2 0,child.height
					oVec2 child.width,child.height
					oVec2 child.width,0
				}
				for i,v in ipairs vs
					v = child\convertToWorldSpace v
					minX = v.x if not minX
					maxX = v.x if not maxX
					minY = v.y if not minY
					maxY = v.y if not maxY
					minX = v.x if v.x < minX
					maxX = v.x if v.x > maxX
					minY = v.y if v.y < minY
					maxY = v.y if v.y > maxY
			sizeW = maxX-minX
			sizeH = maxY-minY
			scale = 1
			if width < sizeW or height < sizeH
				scale = math.min width/sizeW,height/sizeH
			scale *= 1.2
			model.scaleX = scale
			model.scaleY = scale
			model.position = oVec2 width/2,height/2
			renderTarget = CCRenderTarget width,height
			renderTarget\beginDraw!
			renderTarget\draw model
			renderTarget\endDraw!
			@_prevFile = file\match("(.*)%.[^%.\\/]*$").."Small."..file\match("%.([^%.\\/]*)$")
			tex = oCache.Texture\add renderTarget,@_prevFile
			if @sprite
					@sprite.texture = tex
					@sprite.textureRect = CCRect 0,0,width,height
					@sprite.opacity = 0
					@sprite\perform oOpacity 0.3,1
					thread ->
						sleep 0.1
						oCache.Texture\removeUnused!
