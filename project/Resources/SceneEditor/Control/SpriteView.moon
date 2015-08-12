Dorothy!
Class,property = unpack require "class"
SpriteViewView = require "View.Control.SpriteView"

Class
	__partial: (args)=> SpriteViewView args
	__init: (args)=>
		{:width,:height,:file} = args
		@_isCheckMode = false
		@_checked = false
		@boxFill.visible = false
		@\slots "Tapped", ->
			if @isCheckMode
				@\_setBoxChecked not @_checked
			else
				@\emit "Selected",@
		@\slots "Cleanup", ->
			oRoutine\remove @routine
			oCache.Texture\unload @_file if @_file

		@\updateImage file
		@isCheckMode = true

	updateImage: (file)=>
		@routine = go ->
			oCache.Texture\unload @_file if @_file
			oCache\loadAsync file
			sprite = CCSprite file
			{:width,:height} = @
			scale = 1
			if width < sprite.width or height < sprite.height
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
			if @sprite
				@sprite.texture = tex
				@sprite.textureRect = CCRect 0,0,width,height
				@sprite.opacity = 0
				@sprite\perform oOpacity 0.3,1

	_setBoxChecked: (checked)=>
		@_checked = checked
		@boxFill.visible = checked
		@\emit "Checked",checked

	checked: property => @_checked

	isCheckMode: property => @_isCheckMode,
		(value)=>
			@_isCheckMode = value
			@boxFace.visible = value
			if not value
				@\_setBoxChecked false if @_checked
