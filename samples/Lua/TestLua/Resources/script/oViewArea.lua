local oButton = require("script/oButton")

local function oViewArea()
	local winSize = CCDirector.winSize
	local view = CCLayerColor(ccColor4(0xff1a1a1a), winSize.width, winSize.height)
	view.anchorPoint = oVec2.zero
	view.touchEnabled = true
	view.cascadeOpacity = true
	
	local crossNode = CCNode()
	local origin = oVec2(
		60+(winSize.width-120-170)*0.5,
		120+(winSize.height-60-120)*0.5)
	crossNode.position = origin
	view:addChild(crossNode)

	local cross = oLine(
	{
		oVec2(0,-winSize.height*2),
		oVec2(0,winSize.height*2)
	},ccColor4())
	cross.opacity = 0.2
	crossNode:addChild(cross)
	cross = oLine(
	{
		oVec2(-winSize.width*2,0),
		oVec2(winSize.width*2,0)
	},ccColor4())
	cross.opacity = 0.2
	crossNode:addChild(cross)
	
	local scrollNode = CCNode()
	crossNode:addChild(scrollNode)

	view.outline = CCNode()
	crossNode:addChild(view.outline)

	--0: scale = 2.0
	--1: scale = 0.5
	--2: scale = 1.0
	local mode = 0
	
	local EDIT_NONE = 0
	local EDIT_ROT = 1
	local EDIT_POSX = 2
	local EDIT_POSY = 3
	local EDIT_POSXY = 4
	local EDIT_SCALEX = 5
	local EDIT_SCALEY = 6
	local EDIT_SCALEXY = 7
	local EDIT_OPACITY = 8
	local EDIT_SKEWX = 9
	local EDIT_SKEWY = 10
	local EDIT_SKEWXY = 11
	local EDIT_VISIBLE = 12
	local EDIT_EASE = 13
	local EDIT_ANCHORX = 14
	local EDIT_ANCHORY = 15
	local EDIT_ANCHORXY = 16

	local editState = EDIT_NONE
	view:registerTouchHandler(
		function(eventType, touches)
			if eventType == CCTouch.Moved then
				-- touch = CCTouch
				if not view:isControlEnabled() then
					return
				end
				if editState ~= EDIT_NONE then
					if editState == EDIT_ROT then
						view:updateRot(touches[1].preLocation,touches[1].location)
					elseif editState == EDIT_POSX or editState == EDIT_POSY or editState == EDIT_POSXY then
						view:updatePos(touches[1].delta)
					elseif editState == EDIT_SCALEX or editState == EDIT_SCALEY or editState == EDIT_SCALEXY then
						view:updateScale(touches[1].delta)
					elseif editState == EDIT_OPACITY then
						view:updateOpacity(touches[1].delta)
					elseif editState == EDIT_SKEWX or editState == EDIT_SKEWY or editState == EDIT_SKEWXY then
						view:updateSkew(touches[1].delta)
					elseif editState == EDIT_ANCHORX or editState == EDIT_ANCHORY or editState == EDIT_ANCHORXY then
						view:updateAnchor(touches[1].delta)
					end
					return
				end
				if #touches == 1 then
					crossNode.position = crossNode.position + touches[1].delta
				elseif #touches >= 2 then
					mode = 2
					local preDistance = touches[1].preLocation:distance(touches[2].preLocation)
					local distance = touches[1].location:distance(touches[2].location)
					local delta = (distance - preDistance) * 4 / winSize.height
					local scale = crossNode.scaleX + delta
					if scale <= 0.5 then
						scale = 0.5
					end
					crossNode.scaleX = scale
					crossNode.scaleY = scale
					
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
		crossNode:runAction(oScale(0.5,scale,scale,oEase.OutQuad))
		
		local zoomButton = oEditor.editMenu.items.Zoom
		zoomButton.label.text = tostring(scale*100).."%"
		zoomButton.label.texture.antiAlias = false
	end

	view.originReset = function(self)
		crossNode:runAction(oPos(0.5,origin.x,origin.y,oEase.OutQuad))
	end
	
	view.setModel = function(self,model)
		self._model = model
		scrollNode:removeAllChildren(true)
		if model ~= nil then
			scrollNode:addChild(model)
		end
	end
	view.getModel = function(self)
		if self._model and oEditor.dirty then
			oEditor.dirty = false
			local isBatchUsed = oEditor.data[oSd.isBatchUsed]
			oEditor.data[oSd.isBatchUsed] = false
			oCache.Model:loadData(oEditor.model,oEditor.data)
			oEditor.data[oSd.isBatchUsed] = isBatchUsed
			local model = oModel(oEditor.model)
			model.look = oEditor.look
			model.loop = oEditor.loop
			if oEditor.state == oEditor.EDIT_ANIMATION then
				local time = oEditor.controlBar:getTime()
				model:play(oEditor.animation)
				model:pause()
				if model.duration > 0 then
					model.time = time/model.duration
				end
			end
			view:setModel(model)
			oEditor.viewPanel:updateSprite(oEditor.data,model)
		end
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
	
	local editorView = nil
	local editTarget = nil
	local function setEditorView(editor)
		if editor then
			local pos = editTarget.position
			local parent = editTarget.parent
			--parent=CCNode
			pos = pos-oVec2(
				parent.contentSize.width*parent.anchorPoint.x,
				parent.contentSize.height*parent.anchorPoint.y)
			pos = parent:convertToWorldSpace(pos)
			pos = crossNode:convertToNodeSpace(pos)
			editor.position = pos
			editor:setTarget(editTarget)
			editor.visible = true
		else
			editorView:setTarget(nil)
			editorView.visible = false
		end
		editorView = editor
	end

	local posRotFix = 0
	local function getEditorRot()
		posRotFix = editTarget.rotation
		local p = editTarget.parent
		while p and p ~= scrollNode do
			posRotFix = posRotFix + p.rotation
			p = p.parent
		end
		return posRotFix
	end
--[[
	local renderTarget = CCRenderTarget(winSize.width,winSize.height)
	renderTarget.position = oVec2(winSize.width*0.5,winSize.height*0.5)
	renderTarget:scheduleUpdate(
		function()
			renderTarget:beginPaint()
			crossNode.opacity = 0
			if editorView then
				editorView.visible = true
			end
			oEditor.viewPanel:showOutline(true)
			renderTarget:draw(crossNode)
			oEditor.viewPanel:showOutline(false)
			if editorView then
				editorView.visible = false
			end
			crossNode.opacity = 1
			renderTarget:endPaint()
		end)
	view:addChild(renderTarget)
]]
	view.isValueFixed = false
	local valueChanged = false
	local function updateModel()
		if valueChanged then
			valueChanged = false
			oEditor.dirty = true
			view:getModel()
		end
	end

	local rotEditor = CCNode()
	local vs = {}
	local num = 40
	for i = 0, num do
		local angle = 2*math.pi*i/num
		table.insert(vs,oVec2(200*math.cos(angle),200*math.sin(angle)))
	end
	rotEditor:addChild(oLine(vs,ccColor4()))
	rotEditor:addChild(oLine({oVec2(-200,0),oVec2(200,0)},ccColor4()))
	rotEditor:addChild(oLine({oVec2(0,-200),oVec2(0,200)},ccColor4()))
	rotEditor.cascadeOpacity = false
	rotEditor.cascadeColor = false
	rotEditor.visible = false
	crossNode:addChild(rotEditor)
	rotEditor.setTarget = function(self,target)
		if target then
			self:scheduleUpdate(
				function(deltaTime,self)
					local rot = 0
					local p = target
					while p and p ~= crossNode do
						rot = rot + p.rotation
						p = p.parent
					end
					self.rotation = rot
				end,-1)
		else
			self:unscheduleUpdate()
		end
	end

	-- rot
	local rotCenter = oVec2.zero
	local totalRot = 0
	view.editRot = function(self)
		if editState == EDIT_NONE then
			editTarget = oEditor.sprite
			setEditorView(rotEditor)
			rotCenter = rotEditor:convertToWorldSpace(oVec2.zero)
			totalRot = 0
			editState = EDIT_ROT
		end
	end
	
	view.stopEditRot = function(self)
		if editState == EDIT_ROT then
			updateModel()
			setEditorView(nil)
			editTarget = nil
			editState = EDIT_NONE
		end
	end

	view.updateRot = function(self, oldPos, newPos)
		if oldPos ~= newPos then
			local v1 = rotCenter - oldPos
			local v2 = rotCenter - newPos
			local len1 = v1.length
			local len2 = v2.length
			if len1 ~= 0 and len2 ~= 0 then
				local res = (v1.x*v2.x+v1.y*v2.y)/(len1*len2)
				if res > 1 then res = 1 end
				if res < -1 then res = -1 end
				local s = (oldPos.x*(newPos.y-rotCenter.y)-oldPos.y*(newPos.x-rotCenter.x)+(newPos.x*rotCenter.y-newPos.y*rotCenter.x))
				local delta = (s>0 and -1 or 1)*math.acos(res)*180/math.pi/crossNode.scaleX
				totalRot = totalRot + delta
				if view.isValueFixed then
					if totalRot < 1 and totalRot > -1 then
						delta = 0
					else
						delta = totalRot > 0 and math.floor(totalRot) or math.ceil(totalRot)
						totalRot = 0
						editTarget.rotation = editTarget.rotation > 0 and math.floor(editTarget.rotation) or math.ceil(editTarget.rotation)
					end
				end
				local rotation = editTarget.rotation + delta
				editTarget.rotation = rotation
				oEditor.settingPanel.items.Rotation:setValue(rotation)
				if oEditor.state == oEditor.EDIT_ANIMATION then
					oEditor.animationData[oEditor.keyIndex][oKd.rotation] = rotation
				elseif oEditor.state == oEditor.EDIT_SPRITE then
					oEditor.spriteData[oSd.rotation] = rotation
				end
				oEditor.editMenu:markEditButton(true)
				valueChanged = true
			end
		end
	end

	-- pos
	local posEditor = CCNode()
	local yArrow = oLine(
	{
		oVec2(0,150),
		oVec2(-20,150),
		oVec2(0,190),
		oVec2(20,150),
		oVec2(0,150),
		oVec2.zero
	},ccColor4(0xffffffff))
	yArrow.visible = false
	local xArrow = oLine(
	{
		oVec2.zero,
		oVec2(150,0),
		oVec2(150,20),
		oVec2(190,0),
		oVec2(150,-20),
		oVec2(150,0)
	},ccColor4(0xffffffff))
	xArrow.visible = false
	posEditor:addChild(yArrow)
	posEditor:addChild(xArrow)
	posEditor.cascadeOpacity = false
	posEditor.cascadeColor = false
	posEditor.visible = false
	crossNode:addChild(posEditor)
	posEditor.setTarget = function(self,target)
		if target then
			local parent = target.parent
			local off = oVec2(
					parent.contentSize.width*parent.anchorPoint.x,
					parent.contentSize.height*parent.anchorPoint.y)
			self:scheduleUpdate(
				function(deltaTime,self)
					self.position = crossNode:convertToNodeSpace(
						parent:convertToWorldSpace(
							target.position-off))
				end,-2)
			getEditorRot()
		else
			self:unscheduleUpdate()
		end
	end
	
	local totalX = 0
	local totalY = 0

	view.editPosX = function(self)
		if editState == EDIT_NONE then
			editTarget = oEditor.sprite
			setEditorView(posEditor)
			totalX = 0
			xArrow.visible = true
			editState = EDIT_POSX
		end
	end

	view.stopEditPosX = function(self)
		if editState == EDIT_POSX then
			updateModel()
			setEditorView(nil)
			editTarget = nil
			xArrow.visible = false
			editState = EDIT_NONE
		end
	end

	view.editPosY = function(self)
		if editState == EDIT_NONE then
			editTarget = oEditor.sprite
			setEditorView(posEditor)
			totalY = 0
			yArrow.visible = true
			editState = EDIT_POSY
		end
	end

	view.stopEditPosY = function(self)
		if editState == EDIT_POSY then
			updateModel()
			setEditorView(nil)
			editTarget = nil
			yArrow.visible = false
			editState = EDIT_NONE
		end
	end

	view.editPosXY = function(self)
		if editState == EDIT_NONE then
			editTarget = oEditor.sprite
			setEditorView(posEditor)
			totalX = 0
			totalY = 0
			xArrow.visible = true
			yArrow.visible = true
			editState = EDIT_POSXY
		end
	end

	view.stopEditPosXY = function(self)
		if editState == EDIT_POSXY then
			updateModel()
			setEditorView(nil)
			editTarget = nil
			xArrow.visible = false
			yArrow.visible = false
			editState = EDIT_NONE
		end
	end

	view.updatePos = function(self, delta)
		if delta ~= oVec2.zero then
			--editTarget=CCNode
			if editState == EDIT_POSX then
				delta.y = 0
			elseif editState == EDIT_POSY then
				delta.x = 0
			end
			local x2 = delta.x
			local y2 = delta.y
			x2 = x2/crossNode.scaleX
			y2 = y2/crossNode.scaleX
			totalX = totalX + x2
			totalY = totalY + y2
			if view.isValueFixed then
				if totalX < 1 and totalX > -1 then
					x2 = 0
				else
					x2 = totalX > 0 and math.floor(totalX) or math.ceil(totalX)
					totalX = 0
				end
				if totalY < 1 and totalY > -1 then
					y2 = 0
				else
					y2 = totalY > 0 and math.floor(totalY) or math.ceil(totalY)
					totalY = 0
				end
			end

			local r = -(editTarget.rotation-posRotFix)*math.pi/180
			local x1 = x2*math.cos(r)-y2*math.sin(r)
			local y1 = x2*math.sin(r)+y2*math.cos(r)
			editTarget.positionX = editTarget.positionX + x1
			editTarget.positionY = editTarget.positionY + y1
			local x = editTarget.positionX
			local y = editTarget.positionY
			oEditor.settingPanel.items.PosX:setValue(x)
			oEditor.settingPanel.items.PosY:setValue(y)

			if oEditor.state == oEditor.EDIT_ANIMATION then
				oEditor.animationData[oEditor.keyIndex][oKd.x] = x
				oEditor.animationData[oEditor.keyIndex][oKd.y] = y
			elseif oEditor.state == oEditor.EDIT_SPRITE then
				oEditor.spriteData[oSd.x] = x
				oEditor.spriteData[oSd.y] = y
			end
			
			oEditor.editMenu:markEditButton(true)
			valueChanged = true
		end
	end

	-- scale
	local scaleEditor = CCNode()
	local yHandle = oLine(
	{
		oVec2(0,150),
		oVec2(-20,150),
		oVec2(-20,190),
		oVec2(20,190),
		oVec2(20,150),
		oVec2(0,150),
		oVec2.zero
	},ccColor4(0xffffffff))
	yHandle.visible = false
	local xHandle = oLine(
	{
		oVec2.zero,
		oVec2(150,0),
		oVec2(150,20),
		oVec2(190,20),
		oVec2(190,-20),
		oVec2(150,-20),
		oVec2(150,0)
	},ccColor4(0xffffffff))
	xHandle.visible = false
	scaleEditor:addChild(yHandle)
	scaleEditor:addChild(xHandle)
	scaleEditor.cascadeOpacity = false
	scaleEditor.cascadeColor = false
	scaleEditor.visible = false
	crossNode:addChild(scaleEditor)
	scaleEditor.setTarget = function(self,target)
		if target then
			self.rotation = getEditorRot()
		end
	end

	local totalScaleX = 0
	local totalScaleY = 0

	view.editScaleX = function(self)
		if editState == EDIT_NONE then
			editTarget = oEditor.sprite
			setEditorView(scaleEditor)
			totalScaleX = 0
			xHandle.visible = true
			editState = EDIT_SCALEX
		end
	end

	view.stopEditScaleX = function(self)
		if editState == EDIT_SCALEX then
			updateModel()
			setEditorView(nil)
			editTarget = nil
			xHandle.visible = false
			editState = EDIT_NONE
		end
	end

	view.editScaleY = function(self)
		if editState == EDIT_NONE then
			editTarget = oEditor.sprite
			setEditorView(scaleEditor)
			totalScaleY = 0
			yHandle.visible = true
			editState = EDIT_SCALEY
		end
	end

	view.stopEditScaleY = function(self)
		if editState == EDIT_SCALEY then
			updateModel()
			setEditorView(nil)
			editTarget = nil
			yHandle.visible = false
			editState = EDIT_NONE
		end
	end

	view.editScaleXY = function(self)
		if editState == EDIT_NONE then
			editTarget = oEditor.sprite
			setEditorView(scaleEditor)
			totalScaleX = 0
			totalScaleY = 0
			xHandle.visible = true
			yHandle.visible = true
			editState = EDIT_SCALEXY
		end
	end

	view.stopEditScaleXY = function(self)
		if editState == EDIT_SCALEXY then
			updateModel()
			setEditorView(nil)
			editTarget = nil
			xHandle.visible = false
			yHandle.visible = false
			editState = EDIT_NONE
		end
	end

	view.updateScale = function(self, delta)
		if delta ~= oVec2.zero then
			--editTarget=CCNode
			local x2 = delta.x
			local y2 = delta.y
			local r = posRotFix*math.pi/180
			local x3 = x2*math.cos(r)-y2*math.sin(r)
			local y3 = x2*math.sin(r)+y2*math.cos(r)
			if editState == EDIT_SCALEX then
				y3 = 0
			elseif editState == EDIT_SCALEY then
				x3 = 0
			end
			local f = 2/crossNode.scaleX/winSize.height
			local x1 = x3*f
			local y1 = y3*f
			totalScaleX = totalScaleX + x1
			totalScaleY = totalScaleY + y1
			if view.isValueFixed then
				if totalScaleX < 0.1 and totalScaleX > -0.1 then
					x1 = 0
				else
					x1 = totalScaleX > 0 and math.floor(totalScaleX*10)*0.1 or math.ceil(totalScaleX*10)*0.1
					totalScaleX = 0
					editTarget.scaleX = (editTarget.scaleX>0 and 1 or -1)*math.floor(math.abs(editTarget.scaleX*10)+0.5)*0.1
				end
				if totalScaleY < 0.1 and totalScaleY > -0.1 then
					y1 = 0
				else
					y1 = totalScaleY > 0 and math.floor(totalScaleY*10)*0.1 or math.ceil(totalScaleY*10)*0.1
					totalScaleY = 0
					
					editTarget.scaleY = (editTarget.scaleY>0 and 1 or -1)*math.floor(math.abs(editTarget.scaleY*10)+0.5)*0.1
				end
			end
			if x1 == 0 and y1 == 0 then
				return
			end
			editTarget.scaleX = editTarget.scaleX + x1
			editTarget.scaleY = editTarget.scaleY + y1
			local x = editTarget.scaleX
			local y = editTarget.scaleY
			oEditor.settingPanel.items.ScaleX:setValue(x)
			oEditor.settingPanel.items.ScaleY:setValue(y)
			
			if oEditor.state == oEditor.EDIT_ANIMATION then
				oEditor.animationData[oEditor.keyIndex][oKd.scaleX] = x
				oEditor.animationData[oEditor.keyIndex][oKd.scaleY] = y
			elseif oEditor.state == oEditor.EDIT_SPRITE then
				oEditor.spriteData[oSd.scaleX] = x
				oEditor.spriteData[oSd.scaleY] = y
			end

			oEditor.editMenu:markEditButton(true)
			valueChanged = true
		end
	end
	
	local opacityEditor = CCNode()
	opacityEditor:addChild(oLine(
	{
		oVec2(0,0),
		oVec2(36,0),
		oVec2(36,156),
		oVec2(0,156),
		oVec2(0,0)
	},ccColor4(0xffffffff)))
	local yBar = CCDrawNode()
	yBar:drawPolygon({
		oVec2(0,0),
		oVec2(24,0),
		oVec2(24,144),
		oVec2(0,144)
	},ccColor4(0xff00ffff),0,ccColor4(0x00000000))
	yBar.position = oVec2(6,6)
	opacityEditor:addChild(yBar)
	opacityEditor.position = oVec2(winSize.width-223,winSize.height*0.5-48)
	opacityEditor.visible = false
	view:addChild(opacityEditor)
	
	-- opacity
	local totalOpacity = 0
	view.editOpacity = function(self)
		if editState == EDIT_NONE then
			editTarget = oEditor.sprite
			opacityEditor.visible = true
			totalOpacity = 0
			editState = EDIT_OPACITY
		end
	end
	
	view.stopEditOpacity = function(self)
		if editState == EDIT_OPACITY then			
			updateModel()
			opacityEditor.visible = false
			editTarget = nil
			editState = EDIT_NONE
		end
	end

	view.updateOpacity = function(self, delta)
		if delta.y ~= 0 then
			local f = 4/crossNode.scaleX/winSize.height
			local deltaOp = delta.y*f
			totalOpacity = totalOpacity + deltaOp
			if view.isValueFixed then
				if totalOpacity < 0.1 and totalOpacity > -0.1 then
					deltaOp = 0
				else
					deltaOp = totalOpacity > 0 and math.floor(totalOpacity*10)*0.1 or math.ceil(totalOpacity*10)*0.1
					totalOpacity = 0
					editTarget.opacity = (editTarget.opacity>0 and 1 or -1)*math.floor(math.abs(editTarget.opacity*10)+0.5)*0.1
				end
			end
			local opacity = editTarget.opacity + deltaOp
			if opacity < 0 then opacity = 0 end
			if opacity > 1 then opacity = 1 end
			editTarget.opacity = opacity
			yBar.scaleY = opacity
			
			oEditor.settingPanel.items.Opacity:setValue(opacity)

			if oEditor.state == oEditor.EDIT_ANIMATION then
				oEditor.animationData[oEditor.keyIndex][oKd.opacity] = opacity
			elseif oEditor.state == oEditor.EDIT_SPRITE then
				oEditor.spriteData[oSd.opacity] = opacity
			end

			oEditor.editMenu:markEditButton(true)
			valueChanged = true
		end
	end

	-- skew
	local skewEditor = CCNode()
	local yLine = oLine(
	{
		oVec2(-20,100),
		oVec2(0,140),
		oVec2(20,100),
		oVec2(0,140),
		oVec2(0,-140),
		oVec2(-20,-100),
		oVec2(0,-140),
		oVec2(20,-100),
	},ccColor4())
	yLine.visible = false
	local xLine = oLine(
	{
		oVec2(100,20),
		oVec2(140,0),
		oVec2(100,-20),
		oVec2(140,0),
		oVec2(-140,0),
		oVec2(-100,20),
		oVec2(-140,0),
		oVec2(-100,-20),
	},ccColor4(0xffffffff))
	xLine.visible = false
	skewEditor:addChild(yLine)
	skewEditor:addChild(xLine)
	skewEditor.cascadeOpacity = false
	skewEditor.cascadeColor = false
	skewEditor.visible = false
	crossNode:addChild(skewEditor)
	skewEditor.setTarget = function(self,target)
		if target then
			self.rotation = getEditorRot()
		end
	end

	local totalSkewX = 0
	local totalSkewY = 0

	view.editSkewX = function(self)
		if editState == EDIT_NONE then
			editTarget = oEditor.sprite
			setEditorView(skewEditor)
			totalSkewX = 0
			xLine.visible = true
			editState = EDIT_SKEWX
		end
	end

	view.stopEditSkewX = function(self)
		if editState == EDIT_SKEWX then
			updateModel()
			setEditorView(nil)
			editTarget = nil
			xLine.visible = false
			editState = EDIT_NONE
		end
	end

	view.editSkewY = function(self)
		if editState == EDIT_NONE then
			editTarget = oEditor.sprite
			setEditorView(skewEditor)
			totalSkewY = 0
			yLine.visible = true
			editState = EDIT_SKEWY
		end
	end

	view.stopEditSkewY = function(self)
		if editState == EDIT_SKEWY then
			updateModel()
			setEditorView(nil)
			editTarget = nil
			yLine.visible = false
			editState = EDIT_NONE
		end
	end

	view.editSkewXY = function(self)
		if editState == EDIT_NONE then
			editTarget = oEditor.sprite
			setEditorView(skewEditor)
			totalSkewX = 0
			totalSkewY = 0
			xLine.visible = true
			yLine.visible = true
			editState = EDIT_SKEWXY
		end
	end

	view.stopEditSkewXY = function(self)
		if editState == EDIT_SKEWXY then
			updateModel()
			setEditorView(nil)
			editTarget = nil
			xLine.visible = false
			yLine.visible = false
			editState = EDIT_NONE
		end
	end

	view.updateSkew = function(self, delta)
		if delta ~= oVec2.zero then
			--editTarget=CCNode
			if editState == EDIT_SKEWX then
				delta.y = 0
			elseif editState == EDIT_SKEWY then
				delta.x = 0
			end
			local f = 200/crossNode.scaleX/winSize.height
			local x1 = delta.x*f
			local y1 = delta.y*f
			totalSkewX = totalSkewX + x1
			totalSkewY = totalSkewY + y1
			if view.isValueFixed then
				if totalSkewX < 1 and totalSkewX > -1 then
					x1 = 0
				else
					x1 = totalSkewX > 0 and math.floor(totalSkewX) or math.ceil(totalSkewX)
					totalSkewX = 0
					editTarget.skewX = (editTarget.skewX>0 and 1 or -1)*math.floor(math.abs(editTarget.skewX)+0.5)
				end
				if totalSkewY < 1 and totalSkewY > -1 then
					y1 = 0
				else
					y1 = totalSkewY > 0 and math.floor(totalSkewY) or math.ceil(totalSkewY)
					totalSkewY = 0
					
					editTarget.skewY = (editTarget.skewY>0 and 1 or -1)*math.floor(math.abs(editTarget.skewY)+0.5)
				end
			end
			if x1 == 0 and y1 == 0 then
				return
			end
			editTarget.skewX = editTarget.skewX + x1
			editTarget.skewY = editTarget.skewY + y1
			local x = editTarget.skewX
			local y = editTarget.skewY
			oEditor.settingPanel.items.SkewX:setValue(x)
			oEditor.settingPanel.items.SkewY:setValue(y)
			if oEditor.state == oEditor.EDIT_ANIMATION then
				oEditor.animationData[oEditor.keyIndex][oKd.skewX] = x
				oEditor.animationData[oEditor.keyIndex][oKd.skewY] = y
			elseif oEditor.state == oEditor.EDIT_SPRITE then
				oEditor.spriteData[oSd.skewX] = x
				oEditor.spriteData[oSd.skewY] = y
			end

			oEditor.editMenu:markEditButton(true)
			valueChanged = true
		end
	end
	
	-- visible
	local visibleEditor = CCMenu()
	visibleEditor.contentSize = CCSize(50,50)
	visibleEditor.anchorPoint = oVec2.zero
	visibleEditor.position = oVec2(winSize.width-230,190)
	local vButton = oButton("Show",16,50,50,0,0,
		function(item)
			editTarget.visible = not editTarget.visible
			item.label.text = editTarget.visible and "Show" or "Hide"
			item.label.texture.antiAlias = false
			oEditor.settingPanel.items.Visible:setValue(editTarget.visible)
			if oEditor.state == oEditor.EDIT_ANIMATION then
				oEditor.animationData[oEditor.keyIndex][oKd.visible] = editTarget.visible
			end

			oEditor.editMenu:markEditButton(true)
			valueChanged = true
		end)
	vButton.anchorPoint = oVec2.zero
	visibleEditor:addChild(vButton)
	visibleEditor.visible = false
	view:addChild(visibleEditor)

	view.editVisible = function(self)
		if editState == EDIT_NONE then
			editTarget = oEditor.sprite
			visibleEditor.visible = true
			vButton.label.text = editTarget.visible and "Show" or "Hide"
			vButton.label.texture.antiAlias = false
			editState = EDIT_VISIBLE
		end
	end

	view.stopEditVisible = function(self)
		if editState == EDIT_VISIBLE then		
			updateModel()
			visibleEditor.visible = false
			editTarget = nil
			editState = EDIT_NONE
		end
	end

	local board = CCMenu(true)
	board.contentSize = CCSize(winSize.width,winSize.height)
	local border = CCDrawNode()
	border:drawPolygon({
		oVec2(-335,-185),
		oVec2(335,-185),
		oVec2(335,185),
		oVec2(-335,185)
	},ccColor4(0xe5100000),0.5,ccColor4(0x88ffafaf))
	border.position = oVec2(winSize.width*0.5,winSize.height*0.5)
	board:addChild(border)
	board.position = oVec2(winSize.width*0.5,winSize.height*0.5)
	board.enabled = false
	board.visible = false
	board.scaleX = 0.3
	board.scaleY = 0.3
	board.opacity = 0
	board.touchPriority = CCMenu.DefaultHandlerPriority-1

	-- oKd.easePos
	-- oKd.easeScale
	-- oKd.easeSkew
	-- oKd.easeRotation
	-- oKd.easeOpacity
	local easeType = 0
	local easeMenuItem = nil

	local easeStarEditAction = CCSpawn(
	{
		oOpacity(0.3,1),
		oScale(0.3,1,1,oEase.OutBack)
	})
	view.editEase = function(self,eType,menuItem)
		if editState == EDIT_NONE then
			easeType = eType
			easeMenuItem = menuItem
			editTarget = oEditor.sprite
			board.enabled = true
			board.visible = true
			board:stopAllActions()
			board:runAction(easeStarEditAction)
			editState = EDIT_EASE
		end
	end

	local easeEndEditAction = CCSequence(
	{
		CCSpawn(
		{
			oOpacity(0.3,0),
			oScale(0.3,0.3,0.3,oEase.InBack)
		}),
		CCCall(
			function()
				board.visible = false
			end)
	})
	view.stopEditEase = function(self)
		if editState == EDIT_EASE then
			updateModel()
			board:stopAllActions()
			board.enabled = false
			board:runAction(easeEndEditAction)
			editTarget = nil
			editState = EDIT_NONE
		end
	end

	local function onItemClick(item)
		if oEditor.state == oEditor.EDIT_ANIMATION then
			oEditor.animationData[oEditor.keyIndex][easeType] = item.easeId
		end
		easeMenuItem:setValue(item.easeName)
		oEditor.editMenu:markEditButton(true)
		valueChanged = true
		oEvent:send("SettingSelected",easeMenuItem)
	end

	for i = 1,#oEditor.easeNames do
		local easeName = oEditor.easeNames[i]
		local button = oButton(
			easeName,
			17,
			100,50,
			winSize.width*0.5-275+((i-1)%6)*110,
			winSize.height*0.5-90+math.floor((i-1)/6)*60,
			onItemClick)
		button.easeId = i
		button.easeName = easeName
		button.color = ccColor3(0xffffff)
		board:addChild(button)
	end

	local button = oButton(oEditor.easeNames[0],17,100,50,
		500+winSize.width*0.5-335,
		35+winSize.height*0.5-185,
		onItemClick)
	button.easeId = 0
	button.easeName = oEditor.easeNames[0]
	button.color = ccColor3(0xffffff)
	board:addChild(button)

	button = oButton("Cancel",17,100,50,
		610+winSize.width*0.5-335,
		35+winSize.height*0.5-185,
		function(item)
			oEvent:send("SettingSelected",easeMenuItem)
		end)
	button.color = ccColor3(0xffffff)
	board:addChild(button)

	oEditor.scene:addChild(board,1)

	-- anchor
	local anchorEditor = CCNode()
	local yAnchor = oLine(
	{
		oVec2(0,150),
		oVec2(-20,150),
		oVec2(0,190),
		oVec2(20,150),
		oVec2(0,150),
		oVec2.zero
	},ccColor4())
	yAnchor.visible = false
	local xAnchor = oLine(
	{
		oVec2.zero,
		oVec2(150,0),
		oVec2(150,20),
		oVec2(190,0),
		oVec2(150,-20),
		oVec2(150,0)
	},ccColor4())
	xAnchor.visible = false
	anchorEditor:addChild(xAnchor)
	anchorEditor:addChild(yAnchor)
	anchorEditor.cascadeOpacity = false
	anchorEditor.cascadeColor = false
	anchorEditor.visible = false
	anchorEditor.scaleX = 0.5
	anchorEditor.scaleY = 0.5
	crossNode:addChild(anchorEditor)
	anchorEditor.setTarget = function(self,target)
		if target then
			local parent = target.parent
			local off = oVec2(
					parent.contentSize.width*parent.anchorPoint.x,
					parent.contentSize.height*parent.anchorPoint.y)
			self.position = crossNode:convertToNodeSpace(
				parent:convertToWorldSpace(
					target.position-off))
			getEditorRot()
		end
	end
	
	local totalAnchorX = 0
	local totalAnchorY = 0

	view.editAnchorX = function(self)
		if editState == EDIT_NONE then
			editTarget = oEditor.sprite
			setEditorView(anchorEditor)
			totalAnchorX = 0
			xAnchor.visible = true
			editState = EDIT_ANCHORX
		end
	end

	view.stopEditAnchorX = function(self)
		if editState == EDIT_ANCHORX then
			updateModel()
			setEditorView(nil)
			editTarget = nil
			xAnchor.visible = false
			editState = EDIT_NONE
		end
	end

	view.editAnchorY = function(self)
		if editState == EDIT_NONE then
			editTarget = oEditor.sprite
			setEditorView(anchorEditor)
			totalAnchorY = 0
			yAnchor.visible = true
			editState = EDIT_ANCHORY
		end
	end

	view.stopEditAnchorY = function(self)
		if editState == EDIT_ANCHORY then
			updateModel()
			setEditorView(nil)
			editTarget = nil
			yAnchor.visible = false
			editState = EDIT_NONE
		end
	end

	view.editAnchorXY = function(self)
		if editState == EDIT_NONE then
			editTarget = oEditor.sprite
			setEditorView(anchorEditor)
			totalAnchorX = 0
			totalAnchorY = 0
			xAnchor.visible = true
			yAnchor.visible = true
			editState = EDIT_ANCHORXY
		end
	end

	view.stopEditAnchorXY = function(self)
		if editState == EDIT_ANCHORXY then
			updateModel()
			setEditorView(nil)
			editTarget = nil
			xAnchor.visible = false
			yAnchor.visible = false
			editState = EDIT_NONE
		end
	end

	view.updateAnchor = function(self, delta)
		if delta ~= oVec2.zero and editTarget.contentSize ~= CCSize.zero then
			--editTarget=CCNode
			if editState == EDIT_ANCHORX then
				delta.y = 0
			elseif editState == EDIT_ANCHORY then
				delta.x = 0
			end
			local x2 = delta.x
			local y2 = delta.y
			x2 = x2/crossNode.scaleX
			y2 = y2/crossNode.scaleX
			totalAnchorX = totalAnchorX + x2
			totalAnchorY = totalAnchorY + y2
			if view.isValueFixed then
				if totalAnchorX < 1 and totalAnchorX > -1 then
					x2 = 0
				else
					x2 = totalAnchorX > 0 and math.floor(totalAnchorX) or math.ceil(totalAnchorX)
					totalAnchorX = 0
				end
				if totalAnchorY < 1 and totalAnchorY > -1 then
					y2 = 0
				else
					y2 = totalAnchorY > 0 and math.floor(totalAnchorY) or math.ceil(totalAnchorY)
					totalAnchorY = 0
				end
			end

			local r = -(editTarget.rotation-posRotFix)*math.pi/180
			local x1 = x2*math.cos(r)-y2*math.sin(r)
			local y1 = x2*math.sin(r)+y2*math.cos(r)
			x1 = x1/editTarget.contentSize.width
			y1 = y1/editTarget.contentSize.height
			editTarget.anchorPoint = editTarget.anchorPoint - oVec2(x1,y1)

			local x = editTarget.anchorPoint.x
			local y = editTarget.anchorPoint.y
			oEditor.settingPanel.items.AnchorX:setValue(x)
			oEditor.settingPanel.items.AnchorY:setValue(y)

			if oEditor.state == oEditor.EDIT_SPRITE then
				oEditor.spriteData[oSd.anchorX] = x
				oEditor.spriteData[oSd.anchorY] = y
			end
			oEditor.viewPanel:updateAnchor(editTarget)
			oEditor.editMenu:markEditButton(true)
			valueChanged = true
		end
	end
	
	view.stopEdit = function(self)
		view:stopEditAnchorX()
		view:stopEditAnchorY()
		view:stopEditAnchorXY()
		view:stopEditEase()
		view:stopEditVisible()
		view:stopEditSkewX()
		view:stopEditSkewY()
		view:stopEditSkewXY()
		view:stopEditOpacity()
		view:stopEditScaleX()
		view:stopEditScaleY()
		view:stopEditScaleXY()
		view:stopEditPosX()
		view:stopEditPosY()
		view:stopEditPosXY()
		view:stopEditRot()
	end

	return view
end

return oViewArea
