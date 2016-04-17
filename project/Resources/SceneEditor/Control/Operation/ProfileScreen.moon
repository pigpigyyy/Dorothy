Dorothy!
ProfileScreenView = require "View.Control.Operation.ProfileScreen"

Class ProfileScreenView,
	__init:=>
		{:width,:height} = CCDirector.winSize
		wordColor = ccColor3 0x00ffff
		numColor = ccColor3 0xff0080

		@profileLabel.texture.antiAlias = false
		totalUpdate = 0
		totalDraw = 0
		totalTime = 0
		totalFrame = 0
		totalDrawcall = 0
		loopWork = loop ->
			luaMem = collectgarbage "count"
			poolSize = oCache.Pool.size
			text = table.concat {
				"Draw Call:    #{ math.floor totalDrawcall/totalFrame }."
				"CC Object:    #{ CCObject.count }(#{ CCObject.maxCount })."
				"Lua Object:    #{ CCObject.luaRefCount }(#{ CCObject.maxLuaRefCount })."
				"Callback:    #{ CCObject.callRefCount }(#{ CCObject.maxCallRefCount })."
				"Lua Memory:    #{ string.format '%.2f MB', luaMem/1024 }."
				"Dorothy Pool:    #{ string.format '%.2f MB', poolSize/1024/1024 }."
				"Update Interval:    #{ string.format '%d ms', totalUpdate*1000/totalFrame }."
				"Draw Interval:    #{ string.format '%d ms', totalDraw*1000/totalFrame }."
				"DeltaTime:    #{ string.format '%d ms', totalTime*1000/totalFrame }."
				""
			}, "\n\n"
			@profileLabel.text = text
			for start,mid,stop in text\gmatch "()[^:\n]+():[^\n]+()%.\n"
				@profileLabel\colorText start,mid,wordColor
				@profileLabel\colorText mid+2,stop,numColor
			sleep 1
			totalUpdate = 0
			totalDraw = 0
			totalTime = 0
			totalFrame = 0
			totalDrawcall = 0

		with @screen
			.visible = false
			.opacity = 0

		startPos = nil
		with @profileBtn
			.screenOpened = false
			.opacity = 0.05

			\slot "TouchBegan",(touch)->
				loc = \convertToNodeSpace touch.location
				startPos = oVec2.zero
				hit = CCRect(-.width/2,-.height/2,.width,.height)\containsPoint loc
				\perform CCSpawn {
					oOpacity 0.3,0.8,oEase.OutQuad
					oScale 0.3,1.2,1.2,oEase.OutBack
				} if hit
				hit

			\slot "TouchMoved",(touch)->
				if startPos.length > 10
					pos = .position + touch.delta
					pos\clamp oVec2(35,35),oVec2(width-35,height-35)
					.position = pos
				else
					startPos += touch.delta

			touchEnded = ->
				\perform CCSpawn {
					oOpacity 0.3,0.05,oEase.OutQuad
					oScale 0.3,1,1,oEase.OutQuad
				}
				if startPos.length <= 10
					.screenOpened = not .screenOpened
					if .screenOpened
						@screen\perform CCSequence {
							CCShow!
							oOpacity 0.3,1,oEase.OutQuad
						}
						@schedule (deltaTime)->
							totalFrame += 1
							totalTime += deltaTime
							totalDraw += CCDirector.drawInterval
							totalUpdate += CCDirector.updateInterval
							totalDrawcall += CCDirector.numberOfDraws
							loopWork!
					else
						@screen\perform CCSequence {
							oOpacity 0.3,0,oEase.OutQuad
							CCHide!
						}
						@unschedule!
			\slot "TouchCancelled",touchEnded
			\slot "TouchEnded",touchEnded

		--editor\slot "Cleanup",->
		--	if CCDirector.notificationNode == @
		--		CCDirector.notificationNode = nil
		--	else
		--		@parent\removeChild @

		if CCDirector.notificationNode
			CCDirector.notificationNode\addChild @
		else
			CCDirector.notificationNode = @
