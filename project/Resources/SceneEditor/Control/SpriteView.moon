Dorothy!
Class,property = unpack require "class"
SpriteViewView = require "View.Control.SpriteView"
NumberDot = require "Control.NumberDot"
-- [signals]
-- "Selected",(viewItem)->
-- "Checked",(checked,viewItem)->
-- [params]
-- x, y, width, height,
-- file, spriteStr, alias, needUnload
selectedItems = {}
Class
	__partial: (args)=> SpriteViewView args
	__init: (args)=>
		{:width,:height,:file,:spriteStr,:alias,:needUnload} = args
		spriteStr or= file
		@number = 0
		@file = file
		@spriteStr = spriteStr
		@_isCheckMode = false
		@_checked = false
		@_loaded = false

		@\slots "Tapped", @_tapped
		@\slots "Cleanup",->
			oRoutine\remove @routine if @routine
			oCache.Texture\unload @_prevFile if @_prevFile
			@\_setBoxChecked false

		@\updateImage file,spriteStr,alias,needUnload
		@isCheckMode = false

	_tapped: =>
		if @isCheckMode
			@\_setBoxChecked not @_checked
		elseif @_loaded
			@\emit "Selected",@

	updateImage: (file,spriteStr,alias,needUnload)=>
		@routine = thread ->
			if @_prevFile
				oCache.Texture\unload @_prevFile
				@_prevFile = nil
			@_loaded = false
			oCache\loadAsync file,-> @_loaded = true
			if not @_loaded
				@face\addChild with CCLabelTTF "[No Item]","Arial",16
					.position = oVec2 @width/2,@height/2
					.texture.antiAlias = false
					.color = ccColor3 0x00ffff
				@routine = nil
				return
			sprite = CCSprite spriteStr
			tex = sprite.texture
			{:width,:height} = @
			scale = 1
			if width < sprite.width or height < sprite.height
				scale = math.min width/sprite.width,height/sprite.height
			sprite.scaleX = scale
			sprite.scaleY = scale
			sprite.position = oVec2 width/2,height/2
			needPrev = alias and alias*25000 < tex.size.width*tex.size.height -- preview image is smaller than target image
			if needPrev
				renderTarget = CCRenderTarget width,height
				renderTarget\beginDraw!
				renderTarget\draw sprite
				renderTarget\endDraw!
				sleep 0.1
				@_prevFile = spriteStr\match("(.*)%.[^%.\\/]*$").."Small."..spriteStr\match("%.([^%.\\/]*)$")
				tex = oCache.Texture\add renderTarget,@_prevFile
				if @sprite
					@sprite.texture = tex
					@sprite.textureRect = CCRect 0,0,width,height
					@sprite.opacity = 0
					@sprite\perform oOpacity 0.3,1
				if needUnload
					thread ->
						sleep 0.1
						oCache.Texture\removeUnused!
			elseif @sprite
				@sprite.parent\removeChild @sprite
				@face\addChild sprite
				@sprite = sprite
				@sprite.opacity = 0
				@sprite\perform oOpacity 0.3,1
			@routine = nil

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
				@\emit "Checked",true,@
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
			@\emit "Checked",false,@

	checked: property => @_checked

	isCheckMode: property => @_isCheckMode,
		(value)=>
			if @_checked
				dot = @numberDot
				for i,item in ipairs selectedItems
					if item == dot
						table.remove selectedItems,i
						break
				dot\perform CCSequence {
					oScale 0.3,0,0,oEase.OutQuad
					CCCall ->
						dot.parent\removeChild dot
				}
				@numberDot = nil
				@_checked = false
				@\emit "Checked",false,@
			@\emit "TapEnded"
			@_isCheckMode = value
