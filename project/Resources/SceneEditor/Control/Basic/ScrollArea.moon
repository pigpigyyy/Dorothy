Dorothy!
ScrollAreaView = require "View.Control.Basic.ScrollArea"

-- [signals]
-- "ScrollTouchBegan",->
-- "ScrollTouchEnded",->
-- "ScrollStart",->
-- "ScrollEnd",->
-- "Scrolled",(delta)->
-- [params]
-- x,y,width,height,
-- paddingX,paddingY,
-- viewWidth,viewHeight,
-- touchPriority
Class ScrollAreaView,
	__init: (args)=>
		{:width,:height,:touchPriority} = args
		touchPriority = touchPriority or CCMenu.DefaultHandlerPriority
		winHeight = CCDirector.winSize.height
		viewWidth = math.max args.viewWidth or width,width
		viewHeight = math.max args.viewHeight or height,height
		moveY = viewHeight - height
		moveX = viewWidth - width
		deltaX,deltaY = 0,0
		paddingX = args.paddingX or 200
		paddingY = args.paddingY or 200
		posX,posY = 0,0
		timePassed = 0
		S = oVec2.zero
		V = oVec2.zero
		deltaMoveLength = 0

		updateReset = (deltaTime)->
			x = nil
			y = nil
			timePassed += deltaTime
			t = math.min timePassed*4,1
			with oEase
				if posX < -moveX
					tmp = deltaX
					deltaX = \func .OutQuad,t,posX,-moveX-posX
					x = deltaX - tmp
				elseif posX > 0
					tmp = deltaX
					deltaX = \func .OutQuad,t,posX,0-posX
					x = deltaX - tmp
				if posY < 0
					tmp = deltaY
					deltaY = \func .OutQuad,t,posY,0-posY
					y = deltaY - tmp
				elseif posY > moveY
					tmp = deltaY
					deltaY = \func .OutQuad,t,posY,moveY-posY
					y = deltaY - tmp
			x or= 0
			y or= 0
			@emit "Scrolled",oVec2(x,y)
			if t == 1
				@unschedule!
				@emit "ScrollEnd"

		isReseting = ->
			deltaX > 0 or deltaX < -moveX or deltaY > moveY or deltaY < 0

		startReset = ->
			posX = deltaX
			posY = deltaY
			timePassed = 0
			@schedule updateReset

		setOffset = (delta, touching)->
			dPosX = delta.x
			dPosY = delta.y
			newPosX = deltaX + dPosX
			newPosY = deltaY + dPosY

			newPosX = math.min newPosX, paddingX
			newPosX = math.max newPosX, -moveX-paddingX
			newPosY = math.max newPosY, -paddingY
			newPosY = math.min newPosY, moveY+paddingY
			dPosX = newPosX - deltaX
			dPosY = newPosY - deltaY

			if touching
				lenY = if newPosY < 0
					(0-newPosY)/paddingY
				elseif newPosY > moveY
					(newPosY-moveY)/paddingY
				else 0
				lenX = if newPosX > 0
					(newPosX-0)/paddingX
				elseif newPosX < -moveX
					(-moveX-newPosX)/paddingX
				else 0

				if lenY > 0
					v = lenY*3
					dPosY = dPosY / math.max v*v,1
				if lenX > 0
					v = lenX*3
					dPosX = dPosX / math.max v*v,1

			deltaX += dPosX
			deltaY += dPosY

			@emit "Scrolled",oVec2(dPosX,dPosY)

			startReset! if not touching and
			(newPosY < -paddingY*0.5 or 
			newPosY > moveY+paddingY*0.5 or
			newPosX > paddingX*0.5 or
			newPosX < -moveX-paddingX*0.5)

		accel = winHeight*2
		updateSpeed = (dt)->
			V = S / dt
			if V.length > accel
				V\normalize!
				V = V * accel
			S = oVec2.zero

		updatePos = (dt)->
			dir = oVec2 V.x,V.y
			dir\normalize!
			A = dir * -accel
			incX = V.x > 0
			incY = V.y > 0
			V = V + A * dt * 0.5
			decX = V.x < 0
			decY = V.y < 0
			if incX == decX and incY == decY
				if isReseting!
					startReset!
				else
					@unschedule!
					@emit "ScrollEnd"
			else
				dS = V * dt
				setOffset dS,false

		@touchEnabled = true
		@touchPriority = touchPriority
		@slot "TouchBegan",(touch)->
			return false unless touch.id == 0

			pos = @convertToNodeSpace touch.location
			rect = CCRect oVec2(-@width*0.5,-@height*0.5),CCSize(@width,@height)
			return false unless rect\containsPoint pos

			deltaMoveLength = 0
			S = oVec2.zero
			V = oVec2.zero
			@schedule updateSpeed
			@emit "ScrollTouchBegan"
			true

		touchEnded = ->
			if isReseting!
				startReset!
			elseif V ~= oVec2.zero and deltaMoveLength > 10
				@schedule updatePos
			else
				@emit "ScrollEnd"
			@emit "ScrollTouchEnded"

		@slot "TouchEnded",touchEnded
		@slot "TouchCancelled",touchEnded
		@slot "TouchMoved",(touch)->
			lastMoveLength = deltaMoveLength
			S = touch.delta
			deltaMoveLength += S.length
			if deltaMoveLength > 10
				setOffset S,true
				if lastMoveLength <= 10
					@emit "ScrollStart"

		@scroll = (delta)=>
			deltaX += delta.x
			deltaY += delta.y
			@emit "Scrolled",oVec2(delta.x,delta.y)
			startReset! if isReseting!

		@scrollTo = (offset)=>
			delta = offset - oVec2 deltaX,deltaY
			deltaX = offset.x
			deltaY = offset.y
			@emit "Scrolled",delta

		@updateViewSize = (wView,hView)=>
			{:width,:height} = @
			viewWidth = math.max wView,width
			viewHeight = math.max hView,height
			moveY = viewHeight - height
			moveX = viewWidth - width
			@scroll oVec2.zero

		@reset = (wView,hView,padX,padY)=>
			@updateViewSize wView,hView
			paddingX = padX
			paddingY = padY
			deltaX,deltaY = 0,0
			posX,posY = 0,0
			timePassed = 0
			S = oVec2.zero
			V = oVec2.zero
			deltaMoveLength = 0

		@updatePadding = (padX,padY)=>
			paddingX = padX
			paddingY = padY
			@scroll oVec2.zero

		@getPadding = -> oVec2 paddingX,paddingY
		@getViewSize = -> CCSize viewWidth,viewHeight
		@getTotalDelta = -> oVec2 deltaX,deltaY

	offset: property => @getTotalDelta!,
		(offset)=> @scroll offset-@getTotalDelta!

	viewSize: property => @getViewSize!,
		(size)=> @updateViewSize size.width,size.height

	padding: property => @getPadding!,
		(padding)=> @updatePadding padding.x,padding.y
