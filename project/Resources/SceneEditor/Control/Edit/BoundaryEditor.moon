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
	getCamPos = ->
		center = oVec2 winWidth/2,winHeight/2
		center-editor.camPos+editor.origin
	with CCLayerColor ccColor4(0),width,height
		.opacity = 0.5
		.anchor = anchor
		.swallowTouches = true
		.touchPriority = editor.levelEditControl
		.position = oVec2 width/2,height/2
		\addChild with oLine line,ccColor4 0xff00ffff
			.position = oVec2(width,height)*anchor
		\slots "TouchBegan",(touch)->
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
		activeArea = size*2
		\slots "TouchMoved",(touch)->
			pos = \convertToWorldSpace oVec2.zero
			if vertical
				posX = pos.x
				leftOffset = flip and 0 or size
				rightOffset = flip and winWidth-size or winWidth
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
				if .acc ~= 0
					if not .scheduled
						.scheduled = true
						\schedule (dt)->
							deltaX = winWidth*dt*.acc/activeArea
							.positionX += deltaX
							emit "Scene.ViewArea.Move",oVec2(-deltaX,0)
							\emit "ValueChanged",.positionX-getCamPos().x
				elseif .scheduled
					.scheduled = false
					\unschedule!
				\emit "ValueChanged",.positionX-getCamPos().x
			else
				posY = pos.y
				bottomOffset = flip and size or 0
				topOffset = flip and winHeight or winHeight-size
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
				if .acc ~= 0
					if not .scheduled
						.scheduled = true
						\schedule (dt)->
							deltaY = winHeight*dt*.acc/activeArea
							.positionY += deltaY
							emit "Scene.ViewArea.Move",oVec2(0,-deltaY)
							\emit "ValueChanged",.positionY-getCamPos().y
				elseif .scheduled
					.scheduled = false
					\unschedule!
				\emit "ValueChanged",.positionY-getCamPos().y
		touchEnded = ->
			\perform oOpacity 0.3,0.5
			if .scheduled
				.scheduled = false
				\unschedule!
		\slots "TouchCancelled",touchEnded
		\slots "TouchEnded",touchEnded

Class => CCNode!,
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
			\slots "ValueChanged",(value)->
				@area = getRect left:value
				editor.sceneData.camera.area = @area
		@addChild @leftBar
		@rightBar = with BoundaryBar 40,true,true
			\slots "ValueChanged",(value)->
				@area = getRect right:value
				editor.sceneData.camera.area = @area
		@addChild @rightBar
		@bottomBar = with BoundaryBar 40,false,true
			\slots "ValueChanged",(value)->
				@area = getRect bottom:value
				editor.sceneData.camera.area = @area
		@addChild @bottomBar
		@topBar = with BoundaryBar 40,false,false
			\slots "ValueChanged",(value)->
				@area = getRect top:value
				editor.sceneData.camera.area = @area
		@addChild @topBar
		@onLoad = @gslot "Scene.DataLoaded",(sceneData)-> @setup! if sceneData
		@onMove = @gslot "Scene.Camera.Move",(delta)->
			@leftBar.positionX += delta.x
			@rightBar.positionX += delta.x
			@topBar.positionY += delta.y
			@bottomBar.positionY += delta.y
		@onMoveTo = @gslot "Scene.Camera.MoveTo",(camPos)->
			return unless editor.sceneData
			area = editor.sceneData.camera.area
			center = oVec2 width/2,height/2
			origin = editor.origin
			pos = center-camPos+origin
			@leftBar\perform oPos 0.5,area.left+pos.x,@leftBar.positionY,oEase.OutQuad
			@rightBar\perform oPos 0.5,area.right+pos.x,@leftBar.positionY,oEase.OutQuad
			@topBar\perform oPos 0.5,@topBar.positionX,area.top+pos.y,oEase.OutQuad
			@bottomBar\perform oPos 0.5,@bottomBar.positionX,area.bottom+pos.y,oEase.OutQuad
		@onLoad.enabled = false
		@onMove.enabled = false
		@onMoveTo.enabled = false
		@gslot "Scene.ViewPanel.Select",(itemData)->
			if itemData and itemData.typeName == "Camera" and itemData.boundary == true
				@show!
			elseif @visible
				@hide!

	setup:=>
		{:width,:height} = CCDirector.winSize
		area = editor.sceneData.camera.area
		center = oVec2 width/2,height/2
		pos = center-editor.camPos+editor.origin
		@leftBar.positionX = area.left+pos.x
		@rightBar.positionX = area.right+pos.x
		@topBar.positionY = area.top+pos.y
		@bottomBar.positionY = area.bottom+pos.y

	show:=>
		@area = editor.sceneData.camera.area
		@visible = true
		@onLoad.enabled = true
		@onMove.enabled = true
		@onMoveTo.enabled = true
		@leftBar.touchEnabled = true
		@rightBar.touchEnabled = true
		@topBar.touchEnabled = true
		@bottomBar.touchEnabled = true
		@setup!

	hide:=>
		@visible = false
		@onLoad.enabled = false
		@onMove.enabled = false
		@onMoveTo.enabled = false
		@leftBar.touchEnabled = false
		@rightBar.touchEnabled = false
		@topBar.touchEnabled = false
		@bottomBar.touchEnabled = false
