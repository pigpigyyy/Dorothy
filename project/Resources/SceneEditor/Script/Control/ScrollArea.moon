Dorothy!
Class,property = unpack require "class"
ScrollAreaView = require "View.Control.ScrollArea"

Class
	__partial: (args)=> ScrollAreaView args
	__init: (args)=>
		{:width,:height,:touchPriority} = args
		touchPriority = touchPriority or CCMenu.DefaultHandlerPriority
		winHeight = CCDirector.winSize.height
		viewWidth = args.viewWidth or width
		viewHeight = args.winHeight or height
		moveY = viewHeight - height
		moveX = width - viewWidth
		deltaX,deltaY = 0,0
		paddingX = args.paddingX or 200
		paddingY = args.paddingX or 200
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
				if posX > 0
					tmp = deltaX
					deltaX = \func .OutBack,t,posX,0-posX
					x = deltaX - tmp
				elseif posX < moveX
					tmp = deltaX
					deltaX = \func .OutBack,t,posX,moveX-posX
					x = deltaX - tmp
				if posY < 0
					tmp = deltaY
					deltaY = \func .OutBack,t,posY,0-posY
					y = deltaY - tmp
				elseif posY > moveY
					tmp = deltaY
					deltaY = \func .OutBack,t,posY,moveY-posY
					y = deltaY - tmp
			x or= 0
			y or= 0
			@\emit "scroll",oVec2(x,y)
			@\unschedule! if t == 1

		isReseting = ->
			deltaX > 0 or deltaX < moveX or deltaY > moveY or deltaY < 0

		startReset = ->
			posX = deltaX
			posY = deltaY
			timePassed = 0
			@\schedule updateReset

		setOffset = (delta, touching)->
			dPosX = delta.x
			dPosY = delta.y
			newPosX = deltaX + dPosX
			newPosY = deltaY + dPosY
			
			newPosX = math.min newPosX, paddingX
			newPosX = math.max newPosX, moveX-paddingX
			newPosY = math.max newPosY, -paddingY
			newPosY = math.min newPosY, moveY+paddingY
			dPosX = newPosX - deltaX
			dPosY = newPosY - deltaY

			if touching
				lenY = if newPosY < 0
					(newPosY-0)/paddingY
				elseif newPosY > moveY
					(newPosY-moveY)/paddingY
				else 0
				
				lenX = if newPosX > 0
					(newPosX-0)/paddingX
				elseif newPosX < moveX
					(moveX-newPosX)/paddingX
				else 0
				
				if lenY > 0
					v = lenY*3
					dPosY = dPosY / math.max v*v,1
				if lenX > 0
					v = lenX*3
					dPosX = dPosX / math.max v*v,1
			
			dPosX = 0 if viewWidth < width
			dPosY = 0 if viewHeight < height
			
			deltaX += dPosX
			deltaY += dPosY
			
			@\emit "scroll",oVec2(dPosX,dPosY)
			
			startReset! if not touching and
			(newPosY < -paddingY*0.5 or 
			newPosY > moveY+paddingY*0.5 or
			newPosX > paddingX*0.5 or
			newPosX < moveX-paddingX*0.5)

		updateSpeed = (dt)->
			if S == oVec2.zero then return
			V = S / dt
			S = oVec2.zero

		updatePos = (dt)->
			accel = winHeight*2
			A = oVec2 (V.x > 0 and accel or -accel),
								(V.y > 0 and accel or -accel)

			xInc = V.x > 0
			yInc = V.y > 0
			V += A * dt
			xDec = V.x < 0
			yDec = V.y < 0

			if xInc and xDec then V.x,A.x = 0,0
			if yInc and yDec then V.y,A.y = 0,0

			dS = V * dt + A * (0.5 * dt * dt)

			setOffset dS,false

			if V == oVec2.zero
				if isReseting! then startReset! else @\unschedule!
		
		@touchEnabled = true
		@touchPriority = touchPriority
		@\slots "TouchBegan",(touch)->
			if touch.id ~= 0 then return false

			pos = @\convertToNodeSpace touch.location
			rect = CCRect oVec2(-width*0.5,-height*0.5),CCSize(width,height)
			if not rect\containsPoint pos then return false

			deltaMoveLength = 0
			S = oVec2.zero
			V = oVec2.zero
			@\schedule updateSpeed
			return true
		
		touchEnded = ->
			if isReseting!
				startReset!
			elseif V ~= oVec2.zero and deltaMoveLength > 10
				@\schedule updatePos

		@\slots "TouchEnded",touchEnded
		@\slots "TouchCancelled",touchEnded
		@\slots "TouchMoved",(touch)->
			deltaMoveLength += touch.delta.length
			S += touch.delta
			if deltaMoveLength > 10 then setOffset touch.delta,true

		@scroll = (dX, dY)=>
			newPosX = deltaX + dX
			newPosY = deltaY + dY

			newPosX = math.min newPosX, 0
			newPosX = math.max newPosX, moveX
			newPosY = math.max newPosY, 0
			newPosY = math.min newPosY, moveY
			
			dX = newPosX - deltaX
			dY = newPosY - deltaY
			
			@\emit "scroll",oVec2(dX,dY)

		@updateViewSize = (wView,hView)=>
			viewWidth = math.max wView,width
			viewHeight = math.max hView,height
			moveY = viewHeight - height
			moveX = width - viewWidth

		@reset = (wView,hView,padX,padY)=>
			@\updateViewSize wView,hView
			paddingX = padX
			paddingY = padY
			deltaX,deltaY = 0,0
			posX,posY = 0,0
			timePassed = 0
			S = oVec2.zero
			V = oVec2.zero
			deltaMoveLength = 0
