Dorothy!
import Round from require "Data.Utils"

Class CCLayer,
	__init:=>
		@target = nil
		@targetPos = oVec2.zero
		@totalDelta = oVec2.zero
		@jump = false
		@jumpNow = false
		@offset = oVec2.zero

		@visible = false
		@swallowTouches = true
		@touchPriority = editor.levelEditControl
		@circle = with CCDrawNode!
			.opacity = 0.5
			\drawDot oVec2.zero,20,ccColor4 0xff00ffff
			\addChild oLine {
					oVec2 -10,0
					oVec2 10,0
				},ccColor4!
			\addChild oLine {
					oVec2 0,10
					oVec2 0,-10
				},ccColor4!
		@addChild @circle

		@slot "TouchBegan",(touch)->
			if not @jump
				@jump = true
				@jumpNow = true
				@schedule once ->
					sleep 0.4
					@jump = false
					@jumpNow = false
			elseif @jumpNow
				@jump = false
				@unschedule!
				@targetPos = @target\convertToNodeSpace touch.location
				@targetPos += oVec2 @target.width/2,@target.height/2
				if editor.isFixed
					@targetPos = Round @targetPos
				@circle.position = @targetPos
				@emit "PosChanged",@targetPos-@offset
			true

		@slot "TouchMoved",(touch)->
			delta = @target\convertToNodeSpace(touch.location) - @target\convertToNodeSpace(touch.preLocation)
			if editor.isFixed
				@totalDelta += delta
				if @totalDelta.x > 1 or @totalDelta.x < -1
					posX = @targetPos.x+@totalDelta.x
					@targetPos.x = Round posX
					@totalDelta.x = 0
				if @totalDelta.y > 1 or @totalDelta.y < -1
					posY = @targetPos.y+@totalDelta.y
					@targetPos.y = Round posY
					@totalDelta.y = 0
			else
				@targetPos += delta
			@circle.position = @targetPos
			@emit "PosChanged",@targetPos-@offset

	show:(pos, controlTarget=editor\getDummyLayer!, offset=oVec2.zero)=>
		@visible = true
		@touchEnabled = true
		@target = controlTarget
		@circle.transformTarget = @target
		@offset = offset
		@targetPos = pos+offset
		@circle.position = @targetPos
		@totalDelta = oVec2.zero
		@jump = false
		@jumpNow = false

	hide:=>
		return unless @visible
		@visible = false
		@touchEnabled = false
		@slot "PosChanged",nil
		@target = nil
