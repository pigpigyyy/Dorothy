Dorothy!
Class,property = unpack require "class"
ViewAreaView = require "View.Control.Operation.ViewArea"

Class
	__partial: => ViewAreaView!
	__init: =>
		{:width,:height} = CCDirector.winSize

		@\gslot "Scene.ViewArea.ScaleTo",(scale)->
			editor.scale = scale
			@touchEnabled = false
			@scaleNode\runAction CCSequence {
				oScale 0.5,scale,scale,oEase.OutQuad
				CCCall ()->
					if @scaleNode.numberOfRunningActions+
						@crossNode.numberOfRunningActions == 1
						@touchEnabled = true
			}

		@\gslot "Scene.ViewArea.MoveTo",(pos)->
			@\unschedule!
			@touchEnabled = false
			@crossNode\runAction CCSequence {
				oPos 0.5,pos.x,pos.y,oEase.OutQuad
				CCCall ()->
					if @scaleNode.numberOfRunningActions+
						@crossNode.numberOfRunningActions == 1
						@touchEnabled = true
			}
			@xcross\runAction oPos 0.5,0,-pos.y,oEase.OutQuad
			@ycross\runAction oPos 0.5,-pos.x,0,oEase.OutQuad

		@\gslot "Scene.ViewArea.Move",(delta)->
			delta = delta/@scaleNode.scaleX
			@crossNode.position += delta
			@xcross.positionY -= delta.y
			@ycross.positionX -= delta.x

		S = oVec2.zero
		V = oVec2.zero
		accel = height*2
		updateDragSpeed = (dt)->
			V = S / dt
			if V.length > accel
				V\normalize!
				V = V * accel
			S = oVec2.zero

		updateDragPos = (dt)->
			dir = oVec2 V.x,V.y
			dir\normalize!
			A = dir * -accel
			incX = V.x > 0
			incY = V.y > 0
			V = V + A * dt * 0.5
			decX = V.x < 0
			decY = V.y < 0
			if incX == decX and incY == decY
				@\unschedule!
			else
				emit "Scene.ViewArea.Move",V*dt

		pick = false
		@\slots "TouchBegan",(touches)->
			pick = true
			S = oVec2.zero
			V = oVec2.zero
			@\schedule updateDragSpeed
			true

		@\slots "TouchMoved",(touches)->
			if #touches == 1 -- move view
				delta = touches[1].delta
				if delta ~= oVec2.zero
					S = delta
					pick = false
					emit "Scene.ViewArea.Move",delta
			elseif #touches >= 2 -- scale view
				preDistance = touches[1].preLocation\distance touches[2].preLocation
				distance = touches[1].location\distance touches[2].location
				delta = (distance - preDistance) * 4 / height
				scale = @scaleNode.scaleX + delta
				if scale <= 0.5
					scale = 0.5
				@scaleNode.scaleX = scale
				@scaleNode.scaleY = scale
				editor.scale = scale
				pick = false
				emit "Scene.ViewArea.Scale",scale

		touchEnded = (touches)->
			if pick then
				@\unschedule!
				loc = touches[1].location
				emit "Scene.ViewArea.Pick",loc
			elseif V ~= oVec2.zero
					@\schedule updateDragPos
		@\slots "TouchEnded",touchEnded
		@\slots "TouchCancelled",touchEnded
