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
		.touchEnabled = true
		.swallowTouches = true
		.touchPriority = editor.levelEditControl
		.position = oVec2 width/2,height/2
		\addChild with oLine line,ccColor4 0xff00ffff
			.position = oVec2(width,height)*(oVec2(1,1)-anchor)
		\slots "TouchBegan",(touch)->
			loc = \convertToNodeSpace touch.location
			x = vertical and 0 or -width/2
			y = vertical and -height/2 or 0
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
		{:width,:height} = CCDirector.winSize
		@addChild BoundaryBar 40,true,true
		@addChild BoundaryBar 40,true,false
		@addChild BoundaryBar 40,false,true
		@addChild BoundaryBar 40,false,false
		@gslot "Scene.DataLoaded",(sceneData)->
			return unless sceneData
			area = sceneData.camera.area
			center = oVec2 width/2,height/2
			origin = editor.origin
			print string.format("%d,%d",editor.items.Camera.position.x,editor.items.Camera.position.y)
			pos = center-editor.items.Camera.position+origin
			@children[1].positionX = area.left+pos.x
			@children[2].positionX = area.right+pos.x
			@children[3].positionY = area.top+pos.y
			@children[4].positionY = area.bottom+pos.y
			print @children[1].positionX,
				@children[2].positionX,
				@children[3].positionY,
				@children[4].positionY
		@gslot "Scene.Camera.Move",(delta)->
			@children[1].positionX += delta.x
			@children[2].positionX += delta.x
			@children[3].positionY += delta.y
			@children[4].positionY += delta.y
			