Dorothy!
Class,property = unpack require "class"
SpriteViewView = require "View.Control.SpriteView"
NumberDot = require "View.Control.NumberDot"

selectedNumber = 0

Class
	__partial: (args)=> SpriteViewView args
	__init: (args)=>
		{:width,:height,:file,:spriteStr} = args
		spriteStr or= file
		@number = 0
		@file = file
		@_isCheckMode = false
		@_checked = false

		@\slots "Tapped", @_tapped
		@\slots "Cleanup", ->
			oRoutine\remove @routine
			oCache.Texture\unload @_prevFile if @_prevFile

		@\updateImage file,spriteStr
		@isCheckMode = true

	_tapped: =>
		if @isCheckMode
			@\_setBoxChecked not @_checked
		else
			@\emit "Selected",@

	updateImage: (file,spriteStr)=>
		@routine = go ->
			oCache.Texture\unload @_prevFile if @_prevFile
			oCache\loadAsync file
			sprite = CCSprite spriteStr
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
			@_prevFile = spriteStr\match("(.*)%.[^%.\\/]*$").."Small."..spriteStr\match("%.([^%.\\/]*)$")
			tex = oCache.Texture\add renderTarget,@_prevFile
			if @sprite
				@sprite.texture = tex
				@sprite.textureRect = CCRect 0,0,width,height
				@sprite.opacity = 0
				@sprite\perform oOpacity 0.3,1

	_setBoxChecked: (checked)=>
		if checked
			if selectedNumber < 99
				selectedNumber += 1
				@number = selectedNumber
				@numberDot = NumberDot x:@width-17.5, y:17.5, number:selectedNumber
				@numberDot.cascadeOpacity = false
				@numberDot.cascadeColor = false
				@numberDot.scaleX = 0
				@numberDot.scaleY = 0
				@numberDot\perform oScale 0.3,1,1,oEase.OutBack
				@face\addChild @numberDot
				@_checked = true
				@\emit "Checked",@
		elseif @number == selectedNumber
			selectedNumber -= 1
			dot = @numberDot
			dot\perform CCSequence {
				oScale 0.3,0,0,oEase.OutQuad
				CCCall ->
					dot.parent\removeChild dot
			}
			@numberDot = nil
			@_checked = false
			@\emit "Checked",@

	checked: property => @_checked

	isCheckMode: property => @_isCheckMode,
		(value)=>
			@_isCheckMode = value
			if not value and @_checked
				@number = selectedNumber
				@\_setBoxChecked false
