Dorothy!
Class = unpack require "class"

BoundaryBar = (size,vertical,flip)->
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
		\slots "TouchMoved",(touch)->
			if vertical
				.positionX += touch.delta.x
			else
				.positionY += touch.delta.y
		touchEnded = ->
			\perform oOpacity 0.3,0.5
		\slots "TouchCancelled",touchEnded
		\slots "TouchEnded",touchEnded

Class => CCNode!,
	__init:=>
		@visible = false
		@rightBar = BoundaryBar 40,true,true
		@addChild @rightBar
		@leftBar = BoundaryBar 40,true,false
		@addChild @leftBar
		@bottomBar = BoundaryBar 40,false,true
		@addChild @bottomBar
		@topBar = BoundaryBar 40,false,false
		@addChild @topBar
		@onLoad = @gslot "Scene.DataLoaded",(sceneData)-> @setup! if sceneData
		@onMove = @gslot "Scene.Camera.Move",(delta)->
			@leftBar.positionX += delta.x
			@rightBar.positionX += delta.x
			@topBar.positionY += delta.y
			@bottomBar.positionY += delta.y
		@onMoveTo = @gslot "Scene.Camera.MoveTo",(camPos)->
			return unless editor.sceneData
			{:width,:height} = CCDirector.winSize
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
		origin = editor.origin
		pos = center-editor.camPos+origin
		@leftBar.positionX = area.left+pos.x
		@rightBar.positionX = area.right+pos.x
		@topBar.positionY = area.top+pos.y
		@bottomBar.positionY = area.bottom+pos.y

	show:=>
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
