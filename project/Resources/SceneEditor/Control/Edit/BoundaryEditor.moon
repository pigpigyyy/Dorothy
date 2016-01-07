Dorothy!
Class = unpack require "class"

BoundaryBar = (size,vertical,flip)->
	winWidth = CCDirector.winSize.width
	winHeight = CCDirector.winSize.height
	width,height,line = if vertical
		h = CCDirector.winSize.height
		size,h,{oVec2(0,-h/2),oVec2(0,h/2)}
	else
		w = CCDirector.winSize.width
		w,size,{oVec2(-w/2,0),oVec2(w/2,0)}
	anchor = if vertical
		oVec2(flip and 0 or 1,0.5)
	else
		oVec2(0.5,flip and 1 or 0)
	getPos = (worldPos)->
		dummyLayer = editor.items.Scene\getLayer -1
		dummyLayer\convertToNodeSpace worldPos
	with CCLayerColor ccColor4(0),width,height
		.opacity = 0.5
		.anchor = anchor
		.swallowTouches = true
		.touchPriority = editor.levelEditControl
		.position = oVec2 width/2,height/2
		\addChild with oLine line,ccColor4 0xff00ffff
			.position = oVec2(width,height)*anchor
		dir = if vertical
			if flip then "right" else "left"
		else
			if flip then "bottom" else "top"
		\addChild with CCLabelTTF dir,"Arial",16
			.position = oVec2 width/2,height/2
			.texture.antiAlias = false
		\slot "TouchBegan",(touch)->
			loc = \convertToNodeSpace touch.location
			x,y = if vertical
				flip and 0 or -width,-height/2
			else
				-width/2,flip and -height or 0
			if CCRect(x,y,width,height)\containsPoint loc
				.opacity = 0.8
				true
			else
				false
		activeArea = size*1.5
		\slot "TouchMoved",(touch)->
			pos = \convertToWorldSpace oVec2.zero
			if vertical
				posX = pos.x
				leftOffset = flip and 70 or size+70
				rightOffset = flip and winWidth-size-240 or winWidth-240
				if (posX >= leftOffset and posX <= rightOffset) or
					(posX < leftOffset and touch.delta.x > 0) or
					(posX > rightOffset and touch.delta.x < 0)
					.positionX += touch.delta.x
				.acc = if posX < activeArea+leftOffset
					-math.min activeArea+leftOffset-posX,activeArea
				elseif posX > rightOffset-activeArea
					math.min posX-rightOffset+activeArea,activeArea
				else
					0
				.acc /= 2*math.max editor.scale,1
				if .acc ~= 0
					if not .scheduled
						\schedule (dt)->
							deltaX = winWidth*dt*.acc/activeArea
							.positionX += deltaX
							emit "Scene.ViewArea.Move",oVec2(-deltaX,0)
							\emit "ValueChanged",getPos(\convertToWorldSpace oVec2.zero).x
				elseif .scheduled
					\unschedule!
				\emit "ValueChanged",getPos(\convertToWorldSpace oVec2.zero).x
			else
				posY = pos.y
				bottomOffset = flip and size+50 or 50
				topOffset = flip and winHeight-70 or winHeight-size-70
				if (posY >= bottomOffset and posY <= topOffset) or
					(posY < bottomOffset and touch.delta.y > 0) or
					(posY > topOffset and touch.delta.y < 0)
					.positionY += touch.delta.y
				.acc = if posY < activeArea+bottomOffset
					-math.min activeArea+bottomOffset-posY,activeArea
				elseif posY > topOffset-activeArea
					math.min posY-topOffset+activeArea,activeArea
				else
					0
				.acc /= 2*math.max editor.scale,1
				if .acc ~= 0
					if not .scheduled
						\schedule (dt)->
							deltaY = winHeight*dt*.acc/activeArea
							.positionY += deltaY
							emit "Scene.ViewArea.Move",oVec2(0,-deltaY)
							\emit "ValueChanged",getPos(\convertToWorldSpace oVec2.zero).y
				elseif .scheduled
					\unschedule!
				\emit "ValueChanged",getPos(\convertToWorldSpace oVec2.zero).y
		touchEnded = ->
			\perform oOpacity 0.3,0.5
			if .scheduled
				\unschedule!
		\slot "TouchCancelled",touchEnded
		\slot "TouchEnded",touchEnded

Class CCNode,
	__init:=>
		{:width,:height} = CCDirector.winSize
		@visible = false
		@area = nil
		getRect = (args)->
			{:left,:right,:bottom,:top} = args
			with @area
				left or= .left
				right or= .right
				bottom or= .bottom
				top or= .top
			CCRect left,bottom,right-left,top-bottom
		@leftBar = with BoundaryBar 40,true,false
			\slot "ValueChanged",(value)->
				@area = getRect left:math.floor value
				editor.sceneData.camera.area = @area
		@addChild @leftBar
		@rightBar = with BoundaryBar 40,true,true
			\slot "ValueChanged",(value)->
				@area = getRect right:math.floor value
				editor.sceneData.camera.area = @area
		@addChild @rightBar
		@bottomBar = with BoundaryBar 40,false,true
			\slot "ValueChanged",(value)->
				@area = getRect bottom:math.floor value
				editor.sceneData.camera.area = @area
		@addChild @bottomBar
		@topBar = with BoundaryBar 40,false,false
			\slot "ValueChanged",(value)->
				@area = getRect top:math.floor value
				editor.sceneData.camera.area = @area
		@addChild @topBar
		@onLoad = @gslot "Scene.DataLoaded",(sceneData)-> @setup! if sceneData
		@onMove = @gslot "Scene.Camera.Move",(delta)->
			delta *= -editor.scale
			@leftBar.positionX += delta.x
			@rightBar.positionX += delta.x
			@topBar.positionY += delta.y
			@bottomBar.positionY += delta.y
		resetPos = -> @schedule once -> cycle 0.5,-> @update!
		@onMoveTo = @gslot "Scene.Camera.MoveTo",resetPos
		@onSceleTo = @gslot "Scene.ViewArea.ScaleTo",resetPos
		@onScele = @gslot "Scene.ViewArea.Scale",-> @update!
		@onActivate = @gslot "Scene.Camera.Activate",(subCam)->
			enable = (subCam == nil)
			@leftBar.touchEnabled = enable
			@rightBar.touchEnabled = enable
			@bottomBar.touchEnabled = enable
			@topBar.touchEnabled = enable
		@gslot "Scene.ViewPanel.Select",(itemData)->
			if itemData and itemData.typeName == "Camera" and itemData.boundary == true
				@show!
			elseif @visible
				@hide!
		@hide!

	update:=>
		area = editor.sceneData.camera.area
		dummyLayer = editor.items.Scene\getLayer -1
		lower = @convertToNodeSpace dummyLayer\convertToWorldSpace oVec2 area.left,area.bottom
		upper = @convertToNodeSpace dummyLayer\convertToWorldSpace oVec2 area.right,area.top
		@leftBar.positionX = lower.x
		@rightBar.positionX = upper.x
		@topBar.positionY = upper.y
		@bottomBar.positionY = lower.y

	show:=>
		@area = editor.sceneData.camera.area
		@visible = true
		@onLoad.enabled = true
		@onMove.enabled = true
		@onMoveTo.enabled = true
		@onScele.enabled = true
		@onSceleTo.enabled = true
		@onActivate.enabled = true
		@leftBar.touchEnabled = true
		@rightBar.touchEnabled = true
		@topBar.touchEnabled = true
		@bottomBar.touchEnabled = true
		@update!

	hide:=>
		@visible = false
		@onLoad.enabled = false
		@onMove.enabled = false
		@onMoveTo.enabled = false
		@onScele.enabled = false
		@onSceleTo.enabled = false
		@onActivate.enabled = false
		@leftBar.touchEnabled = false
		@rightBar.touchEnabled = false
		@topBar.touchEnabled = false
		@bottomBar.touchEnabled = false
