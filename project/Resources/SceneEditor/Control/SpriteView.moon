Dorothy!
Class,property = unpack require "class"
SpriteViewView = require "View.Control.SpriteView"

Class
	__partial: (args)=> SpriteViewView args
	__init: (args)=>
		{:width,:height,:file} = args
		@\updateImage file

		@_checked = false
		@checkBox\slots "Tapped", ->
			@_checked = not @_checked
			@\emit "Checked",@_checked

	updateImage: (file)=>
		go ->
			oCache.Texture\unload @_file if @_file
			oCache\loadAsync file
			sprite = CCSprite file
			{:width,:height} = @
			scale = math.min width/sprite.width,height/sprite.height
			sprite.scaleX = scale
			sprite.scaleY = scale
			sprite.position = oVec2 width/2,height/2
			renderTarget = CCRenderTarget width,height
			renderTarget\beginDraw!
			renderTarget\draw sprite
			renderTarget\endDraw!
			oCache.Texture\unload file
			sleep 0.1
			@_file = file\match("(.*)%.[^%.\\/]*$").."Small."..file\match("%.([^%.\\/]*)$")
			tex = oCache.Texture\add renderTarget,@_file
			@sprite.texture = tex
			@sprite.textureRect = CCRect 0,0,width,height
			@sprite.opacity = 0
			@sprite\perform oOpacity 0.3,1

	checked: property => @_checked
