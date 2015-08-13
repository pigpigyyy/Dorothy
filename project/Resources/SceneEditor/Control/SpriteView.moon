Dorothy!
Class,property = unpack require "class"
SpriteViewView = require "View.Control.SpriteView"
NumberDot = require "Control.NumberDot"

selectedItems = {}

Class
	__partial: (args)=> SpriteViewView args
	__init: (args)=>
		{:width,:height,:file,:spriteStr} = args
		spriteStr or= file
		@number = 0
		@file = file
		@spriteStr = spriteStr
		@_isCheckMode = false
		@_checked = false

		@\slots "Tapped", @_tapped
		@\slots "Cleanup", ->
			oRoutine\remove @routine
			oCache.Texture\unload @_prevFile if @_prevFile
			@\_setBoxChecked false

		@\updateImage file,spriteStr
		@isCheckMode = false

	_tapped: =>
		if @isCheckMode
			@\_setBoxChecked not @_checked
		else
			@\emit "Selected",@

	updateImage: (file,spriteStr)=>
		@routine = thread ->
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
		if checked == @_checked
			return
		if checked
			currentNumber = #selectedItems
			if currentNumber < 99
				@numberDot = NumberDot {
					x: @width-17.5
					y: 17.5
					number: currentNumber+1
				}
				@numberDot.cascadeOpacity = false
				@numberDot.cascadeColor = false
				@numberDot.scaleX = 0
				@numberDot.scaleY = 0
				@numberDot\perform oScale 0.3,1,1,oEase.OutBack
				@face\addChild @numberDot
				table.insert selectedItems,@numberDot
				@_checked = true
				@\emit "Checked",@
		else
			dot = @numberDot
			num = dot.number + 1
			for item in *selectedItems[num,]
				item.number -= 1
			table.remove selectedItems,num - 1
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
			@\_setBoxChecked false
			@\emit "TapEnded"
			@_isCheckMode = value
