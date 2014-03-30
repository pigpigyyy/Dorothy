local function oViewArea()
	local winSize = CCDirector.winSize
	local view = CCLayerColor(ccColor4(0xff1a1a1a), winSize.width, winSize.height)
	view.anchorPoint = oVec2.zero
	view.touchEnabled = true
	
	local crossNode = CCNode()
	local origin = oVec2(
		60+(winSize.width-120-170)*0.5,
		120+(winSize.height-60-120)*0.5)
	crossNode.position = origin
	view:addChild(crossNode)
	
	local cross = CCDrawNode()
	cross:drawSegment(oVec2(0,-winSize.height*2),oVec2(0,winSize.height*2),0.5,ccColor4(0xffffffff))
	cross:drawSegment(oVec2(-winSize.width*2,0),oVec2(winSize.width*2,0),0.5,ccColor4(0xffffffff))
	cross.opacity = 0.2
	crossNode:addChild(cross)
	
	local scrollNode = CCNode()
	crossNode:addChild(scrollNode)
		
	--0: scale = 2.0
	--1: scale = 0.5
	--2: scale = 1.0
	local mode = 0

	view:registerTouchHandler(
		function(eventType, touches)
			if eventType == CCTouch.Moved then
				-- touch = CCTouch
				if not view:isControlEnabled() then
					return
				end
				if #touches == 1 then
					crossNode.position = crossNode.position + touches[1].delta
				elseif #touches >= 2 then
					mode = 2
					local preDistance = touches[1].preLocation:distance(touches[2].preLocation)
					local distance = touches[1].location:distance(touches[2].location)
					local delta = (distance - preDistance) * 4 / winSize.height
					local scale = scrollNode.scaleX + delta
					if scale <= 0.5 then
						scale = 0.5
					end
					scrollNode.scaleX = scale
					scrollNode.scaleY = scale
					
					local zoomButton = oEditor.editMenu.items.Zoom
					zoomButton.label.text = tostring(math.floor(scale*100)).."%"
					zoomButton.label.texture.antiAlias = false
				end
			end
		end,true)

	view.zoomReset = function(self)
		local scale = 0
		if mode == 0 then
			scale = 2.0
		elseif mode == 1 then
			scale = 0.5
		elseif mode == 2 then
			scale = 1.0
		end
		mode = mode + 1
		mode = mode % 3
		scrollNode:runAction(oScale(0.5,scale,scale,oEase.OutQuad))
		
		local zoomButton = oEditor.editMenu.items.Zoom
		zoomButton.label.text = tostring(scale*100).."%"
		zoomButton.label.texture.antiAlias = false
	end

	view.originReset = function(self)
		crossNode:runAction(oPos(0.5,origin.x,origin.y,oEase.OutQuad))
	end
	
	view.setModel = function(self,model)
		self._model = model
		scrollNode:removeAllChildrenWithCleanup(true)
		if model ~= nil then
			scrollNode:addChild(model)
		end
	end
	view.getModel = function(self)
		return self._model
	end
	view.loopListener = oListener("LoopState",
		function(loop)
			if view._model then
				view._model.loop = loop
			end
		end)
	
	view._enabled = true
	view.setControlEnabled = function(self,enable)
		self._enabled = enable
	end
	view.isControlEnabled = function(self)
		return self._enabled
	end
	
	return view
end

return oViewArea