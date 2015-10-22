CCDrawNode = require "CCDrawNode"
ccColor4 = require "ccColor4"
oVec2 = require "oVec2"
oCache = require "oCache"
thread = require "thread"
CCLabelTTF = require "CCLabelTTF"
ccColor3 = require "ccColor3"
oOpacity = require "oOpacity"
oModel = require "oModel"
CCRenderTarget = require "CCRenderTarget"
CCRect = require "CCRect"
sleep = require "sleep"
oScale = require "oScale"
oEase = require "oEase"
CCSequence = require "CCSequence"
CCHide = require "CCHide"
Class,property = unpack require "class"
SpriteViewView = require "View.Control.Item.SpriteView"
oStar = require "EffectEditor.Script.oStar"

-- [signals]
-- "Selected",(viewItem)->
-- [params]
-- x, y, width, height, file
Class
	__partial: (args)=> SpriteViewView args
	__init: (args)=>
		{:width,:height,:file} = args
		@_loaded = false
		@_checked = false
		@file = file
		@star = with CCDrawNode!
			\drawPolygon oStar(12),ccColor4(0x66ff0088),0.5,ccColor4(0xffff0088)
			.visible = false
			.position = oVec2 width-20,20
		@face\addChild @star

		@\slots "Tapped",->
			@\emit "Selected",@

		@\slots "Cleanup",->
			oCache.Texture\unload @_prevFile if @_prevFile

		thread ->
			@_loaded = false
			oCache\loadAsync file,-> @_loaded = true
			if not @_loaded
				name = file\match "([^\\/]*)%.[^%.\\/]*$"
				@face\addChild with CCLabelTTF "Broken\nModel\n"..name,"Arial",16
					.position = oVec2 width/2,height/2
					.texture.antiAlias = false
					.color = ccColor3 0x00ffff
					\perform oOpacity 0.3,1
				@face\removeChild @sprite
				@sprite = nil
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
				for v in *vs
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
			if sizeW == 0 and sizeH == 0
				name = file\match "([^\\/]*)%.[^%.\\/]*$"
				@face\addChild with CCLabelTTF "Empty\nModel\n"..name,"Arial",16
					.position = oVec2 width/2,height/2
					.texture.antiAlias = false
					.color = ccColor3 0x00ffff
					\perform oOpacity 0.3,1
				@face\removeChild @sprite
				@sprite = nil
				return
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

	isLoaded: property => @_loaded

	checked: property => @_checked,
		(value)=>
			@_checked = value
			if value
				@star.visible = true
				@star.scaleX = 0
				@star.scaleY = 0
				@star\perform oScale 0.3,1,1,oEase.OutBack
			else
				@star\perform CCSequence {
					oScale 0.3,0,0,oEase.InBack
					CCHide!
				}
