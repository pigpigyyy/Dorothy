local oButton = require("Script/oButton")
local oPacker = require("Script/oPacker")

local function oFileChooser()
	local winSize = CCDirector.winSize
	local borderSize = CCSize(670,400)
	local halfBW = borderSize.width*0.5
	local halfBH = borderSize.height*0.5
	local viewWidth = 0
	local viewHeight = 0
	local moveY = 0
	local moveX = 0
	local totalDelta = oVec2.zero
	local paddingY = 200
	local paddingX = 200
	local startPos = oVec2.zero
	local time = 0
	local _s = oVec2.zero
	local _v = oVec2.zero
	local deltaMoveLength = 0
	local function initValues()
		viewWidth = 0
		viewHeight = 0
		moveY = 0
		moveX = 0
		totalDelta = oVec2.zero
		startPos = oVec2.zero
		time = 0
		_s = oVec2.zero
		_v = oVec2.zero
		deltaMoveLength = 0
	end
	local panel = CCLayer()
	panel.anchorPoint = oVec2.zero
	panel.touchEnabled = true
	panel.visible = false
	local mask = CCLayer()
	mask.anchorPoint = oVec2.zero
	mask.touchEnabled = true
	mask:registerTouchHandler(function()return true end,false,CCMenu.DefaultHandlerPriority-1,true)
	panel:addChild(mask)

	local border = CCDrawNode()
	border:drawPolygon(
	{
		oVec2(-halfBW,-halfBH),
		oVec2(halfBW,-halfBH),
		oVec2(halfBW,halfBH),
		oVec2(-halfBW,halfBH)
	},ccColor4(0xe5100000),0.5,ccColor4(0x88ffafaf))
	border.position = oVec2(winSize.width*0.5,winSize.height*0.5)
	border.scaleX = 0.3
	border.scaleY = 0.3
	border.opacity = 0
	panel:addChild(border)

	local stencil = CCDrawNode()
	stencil:drawPolygon(
	{
		oVec2(-halfBW+1,-halfBH+1),
		oVec2(halfBW-1,-halfBH+1),
		oVec2(halfBW-1,halfBH-1),
		oVec2(-halfBW+1,halfBH-1)
	},ccColor4(0xffffffff),0,ccColor4(0x00000000))

	local view = CCClipNode(stencil)
	border:addChild(view)

	local menu = CCMenu(false)
	menu.contentSize = CCSize(winSize.width,winSize.height)
	menu.enabled = false
	menu.touchPriority = CCMenu.DefaultHandlerPriority-2
	menu.anchorPoint = oVec2(0,1)
	menu.position = oVec2(-winSize.width*0.5,winSize.height*0.5)
	
	local easeStarEditAction = CCSequence(
	{
		CCSpawn(
		{
			oOpacity(0.3,1),
			oScale(0.3,1,1,oEase.OutBack)
		}),
		CCCall(
			function()
				panel:updateItems()
			end)
	})
	panel.show = function(self)
		menu.enabled = true
		panel.visible = true
		mask.touchEnabled = true
		border:stopAllActions()
		border:runAction(easeStarEditAction)
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
				panel.visible = false
				mask.touchEnabled = false
				menu:removeAllChildren()
			end)
	})
	panel.hide = function(self)
		menu.enabled = false
		border:stopAllActions()
		border:runAction(easeEndEditAction)
	end

	local function updateReset(deltaTime)
		local children = menu.children
		if not children then return end

		local xVal = nil
		local yVal = nil
		time = time + deltaTime
		local t = time/4.0
		if t > 1.0 then t = 1.0 end
		if startPos.x > 0 then
			xVal = totalDelta.x
			totalDelta.x = oEase:func(oEase.OutExpo,t,startPos.x,0-startPos.x)
			xVal = totalDelta.x - xVal
		end
		if startPos.x < moveX then
			xVal = totalDelta.x
			totalDelta.x = oEase:func(oEase.OutBack,t,startPos.x,moveX-startPos.x)
			xVal = totalDelta.x - xVal
		end
		if startPos.y < 0 then
			yVal = totalDelta.y
			totalDelta.y = oEase:func(oEase.OutBack,t,startPos.y,0-startPos.y)
			yVal = totalDelta.y - yVal
		end
		if startPos.y > moveY then
			yVal = totalDelta.y
			totalDelta.y = oEase:func(oEase.OutBack,t,startPos.y,moveY-startPos.y)
			yVal = totalDelta.y - yVal
		end
		
		for i = 1, children.count do
			local node = tolua.cast(children:get(i), "CCNode")
			node.position = node.position + oVec2(xVal and xVal or 0, yVal and yVal or 0)
		end
		
		if t == 1.0 then
			panel:unscheduleUpdate()
		end
	end

	local function isReseting()
		if totalDelta.x > 0 or totalDelta.x < moveX or totalDelta.y > moveY or totalDelta.y < 0 then
			return true
		end
		return false
	end

	local function startReset()
		startPos = totalDelta
		time = 0
		panel:scheduleUpdate(updateReset)
	end

	local function setOffset(deltaPos, touching)
		local children = menu.children
		if not children then return end

		local newPos = totalDelta + deltaPos
		
		if touching then
			if newPos.x > paddingX then
				newPos.x = paddingX 
			elseif newPos.x-moveX < -paddingX then
				newPos.x = moveX-paddingX
			end
			if newPos.y < -paddingY then
				newPos.y = -paddingY
			elseif moveY-newPos.y < -paddingY then
				newPos.y = moveY+paddingY
			end
			deltaPos = newPos - totalDelta
			
			local lenY = 0
			local lenX = 0
			if newPos.y < 0 then
				lenY = -newPos.y/paddingY
			elseif newPos.y > moveY then
				lenY = (newPos.y-moveY)/paddingY
			end
			if newPos.x > 0 then
				lenX = newPos.x/paddingX
			elseif newPos.x < moveX then
				lenX = (moveX-newPos.x)/paddingX
			end
			if lenY > 0 then
				local v = 3*lenY
				deltaPos.y = deltaPos.y / (v > 1 and v*v or 1)
			end
			if lenX > 0 then
				local v = 3*lenX
				deltaPos.x = deltaPos.x / (v > 1 and v*v or 1)
			end
		else
			if newPos.x > paddingX then
				newPos.x = paddingX
			elseif newPos.x < moveX-paddingX then
				newPos.x = moveX-paddingX
			end
			if newPos.y < -paddingY then
				newPos.y = -paddingY
			elseif newPos.y > moveY+paddingY then
				newPos.y = moveY+paddingY
			end
			deltaPos = newPos - totalDelta
		end
		
		if viewWidth < borderSize.width then deltaPos.x = 0 end
		if viewHeight < borderSize.height then deltaPos.y = 0 end

		totalDelta = totalDelta + deltaPos

		for i = 1, children.count do
			local node = tolua.cast(children:get(i), "CCNode")
			node.position = node.position + deltaPos
		end
		
		if not touching and (newPos.y < -paddingY*0.5 or newPos.y > moveY+paddingY*0.5 or newPos.x > paddingX*0.5 or newPos.x < moveX-paddingX*0.5) then
			startReset()
		end
	end
	view:addChild(menu)

	local function updateSpeed(deltaTime)
		if _s == oVec2.zero then
			return
		end
		_v = _s / deltaTime
		_s = oVec2.zero
	end
	local function updatePos(deltaTime)
		local val = winSize.height*2
		local a = oVec2(_v.x > 0 and -val or val,_v.y > 0 and -val or val)
		
		local xR = _v.x > 0
		local yR = _v.y > 0
		
		_v = _v + a*deltaTime
		if _v.x < 0 == xR then _v.x = 0;a.x = 0 end
		if _v.y < 0 == yR then _v.y = 0;a.y = 0 end
		
		local ds = _v * deltaTime + a*(0.5*deltaTime*deltaTime)
		setOffset(ds, false)
		
		if _v == oVec2.zero then
			if isReseting() then
				startReset()
			else
				panel:unscheduleUpdate()
			end
		end
	end

	panel:registerTouchHandler(
		function(eventType, touch)
			--touch=CCTouch
			if touch.id ~= 0 then
				return false
			end
			if eventType == CCTouch.Began then
				if not CCRect(oVec2(winSize.width-borderSize.width,winSize.height-borderSize.height)*0.5, borderSize):containsPoint(panel:convertToNodeSpace(touch.location)) then
					return false
				end
				deltaMoveLength = 0
				menu.enabled = true
				panel:scheduleUpdate(updateSpeed)
			elseif eventType == CCTouch.Ended or eventType == CCTouch.Cancelled then
				menu.enabled = true
				if isReseting() then
					startReset()
				else
					if _v ~= oVec2.zero and deltaMoveLength > 20 then
						panel:scheduleUpdate(updatePos)
					end
				end
			elseif eventType == CCTouch.Moved then
				deltaMoveLength = deltaMoveLength + touch.delta.length
				_s = _s + touch.delta
				if deltaMoveLength > 20 then
					menu.enabled = false
					setOffset(touch.delta, true)
				end
			end
			return true
		end, false, CCMenu.DefaultHandlerPriority-3, false)
	

	local function addClip(file)
		menu:removeAllChildren()
		oCache.Clip:load(oEditor.output..file)
		local sprite = CCSprite(oEditor.output..file)
		sprite.anchorPoint = oVec2(0,1)
		sprite.position = oVec2(winSize.width*0.5-borderSize.width*0.5+10,winSize.height*0.5+borderSize.height*0.5-10)
		sprite.opacity = 0
		sprite:runAction(oOpacity(0.3,1))
		menu:addChild(sprite)
		local frame = oLine(
		{
			oVec2.zero,
			oVec2(sprite.contentSize.width,0),
			oVec2(sprite.contentSize.width,sprite.contentSize.height),
			oVec2(0,sprite.contentSize.height),
			oVec2.zero
		},ccColor4(0x44ffffff))
		local names = oCache.Clip:getNames(oEditor.output..file)
		for i = 1,#names do
			local sp = CCSprite(oEditor.output..file.."|"..names[i])
			local rc = sp.textureRect
			local line = oLine(
			{
				oVec2(rc.left,rc.bottom),
				oVec2(rc.right,rc.bottom),
				oVec2(rc.right,rc.up),
				oVec2(rc.left,rc.up),
				oVec2(rc.left,rc.bottom)
			},ccColor4(0xffffffff))
			frame:addChild(line)
		end
		frame.scaleY = -1
		frame.positionY = sprite.contentSize.height
		sprite:addChild(frame)
					
		initValues()
		local yTo = sprite.contentSize.height+20
		local xTo = sprite.contentSize.width+20
		viewHeight = yTo < borderSize.height and borderSize.height or yTo
		if yTo < borderSize.height then paddingY = 0 end
		viewWidth = xTo < borderSize.width and borderSize.width or xTo
		moveY = viewHeight-borderSize.height
		if xTo < borderSize.width then
			paddingX = 0
			sprite.positionX = sprite.positionX+borderSize.width*0.5-sprite.contentSize.width*0.5
		else
			paddingX = 100
		end
		moveX = borderSize.width-viewWidth
	end
	
	local function addImages(file)
		menu:removeAllChildren()
		local blocks = {}
		local images = oContent:getDirEntries(oEditor.input..file,false)
		for i = 1,#images do
			local sp = CCSprite(oEditor.input..file.."/"..images[i])
			sp.anchorPoint = oVec2.zero
			local block =
			{
				w = sp.contentSize.width+4,
				h = sp.contentSize.height+4,
				sp = sp,
				name = images[i]:sub(1,images[i]:find("%.")-1)
			}
			table.insert(blocks,block)
		end

		oPacker:fit(blocks)
		local w = oPacker.root.w
		local v = 2;while v < w do v = v*2	end
		w = v
		local h = oPacker.root.h
		v = 2;while v < h do v = v*2 end
		local dy = v - h
		h = v
		local frame = oLine(
		{
			oVec2.zero,
			oVec2(w,0),
			oVec2(w,h),
			oVec2(0,h),
			oVec2.zero
		},ccColor4(0x44ffffff))

		local node = CCNode()
		node:addChild(frame)
		
		for n = 1, #blocks do
			local block = blocks[n]
			if block.fit then
				block.fit.y = h-block.fit.y-block.h
				local rect = CCRect(block.fit.x, block.fit.y, block.w, block.h)
				local line = oLine(
				{
					oVec2(rect.left+2,rect.bottom+2),
					oVec2(rect.right-2,rect.bottom+2),
					oVec2(rect.right-2,rect.up-2),
					oVec2(rect.left+2,rect.up-2),
					oVec2(rect.left+2,rect.bottom+2)
				},ccColor4())
				frame:addChild(line)

				block.sp.position = rect.origin+oVec2(2,2)
				node:addChild(block.sp)
			end
		end
						
		local target = CCRenderTarget(w,h)
		target:beginPaint(ccColor4(0))
		frame.visible = false
		target:draw(node)
		frame.visible = true
		target:endPaint()
		target:save(oEditor.output..file..".png",CCImage.PNG)
		local xml = "<A A=\""..file..".png\">"
		for i = 1,#blocks do
			local block = blocks[i]
			xml = xml.."<B A=\""..block.name.."\" B=\""..tostring(block.fit.x+2)..","..tostring(h-block.fit.y-2-block.h+4)..","..tostring(block.w-4)..","..tostring(block.h-4).."\"/>"
		end
		xml = xml.."</A>"

		local clipFile = oEditor.output..file..".clip"
		local modelFile = oEditor.output..file..".model"
		local texFile = oEditor.output..file..".png"
		oContent:saveToFile(clipFile,xml)
		oCache.Clip:update(clipFile,xml)
		oCache.Model:unload(modelFile)
		CCTextureCache:remove(texFile)
		CCTextureCache:add(target,texFile)
	
		node.opacity = 0
		node:runAction(oOpacity(0.3,1))
		node.position = oVec2(winSize.width*0.5-borderSize.width*0.5+10,winSize.height*0.5-borderSize.height*0.5-h+borderSize.height-10)
		menu:addChild(node)
						
		initValues()
		local yTo = h+20
		local xTo = w+20
		viewHeight = yTo < borderSize.height and borderSize.height or yTo
		if yTo < borderSize.height then paddingY = 0 end
		viewWidth = xTo < borderSize.width and borderSize.width or xTo
		moveY = viewHeight-borderSize.height
		if xTo < borderSize.width then
			paddingX = 0
			node.positionX = node.positionX+borderSize.width*0.5-w*0.5
		else
			paddingX = 100
		end
		moveX = borderSize.width-viewWidth
	end

	local opMenu = CCMenu()
	opMenu.contentSize = CCSize(130,60)
	opMenu.touchPriority = CCMenu.DefaultHandlerPriority-3
	opMenu.position = oVec2(winSize.width*0.5+borderSize.width*0.5-35,winSize.height*0.5+borderSize.height*0.5)
	panel:addChild(opMenu)

	local cancelButton = oButton("Cancel",17,60,false,
		70,0,
		function(item)
			opMenu.enabled = false
			panel:hide()
			if item.editTarget then
				oEditor.controlBar:clearCursors()
				oEditor.model = oEditor.output..item.editTarget..".model"
				oEditor.data = oCache.Model:getData(oEditor.model)

				if oEditor.data then
					local isBatchUsed = oEditor.data[oSd.isBatchUsed]
					oEditor.data[oSd.isBatchUsed] = false
					oCache.Model:loadData(oEditor.model, oEditor.data)
					oEditor.data[oSd.isBatchUsed] = isBatchUsed
				else
					oEditor.data =
					{
						0.5,--anchorX
						0.5,--anchorY
						"",--clip
						"",--name
						1,--opacity
						CCRect.zero,--rect
						0,--rotation
						1,--scaleX
						1,--scaleY
						0,--skewX
						0,--skewY
						0,--x
						0,--y
						true,--visible
						{},--looks
						{},--animationDefs
						{},--children
						true,--isFaceRight
						false,--isBatchUsed
						oEditor.output..item.editTarget..".clip",--clipFile
						{},--keys
						{},--animationNames
						{}--lookNames
					}
					oCache.Model:loadData(oEditor.model, oEditor.data)
				end

				local model = oModel(oEditor.model)
				oEditor.look = pairs(oEditor.data[oSd.lookNames])(oEditor.data[oSd.lookNames])
				oEditor.animation = pairs(oEditor.data[oSd.animationNames])(oEditor.data[oSd.animationNames])
				if oEditor.look then
					model.look = oEditor.look
				end
				model.loop = oEditor.loop
				oEditor.viewArea:setModel(model)
				oEditor.viewPanel:updateImages(oEditor.data,model)
				oEditor.controlBar:setTime(0)
				
				oEditor.editMenu:startToAnimation()
			end
		end)
	cancelButton.anchorPoint = oVec2.zero
	local btnBk = CCDrawNode()
	btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
	btnBk.position = oVec2(30,30)
	cancelButton:addChild(btnBk,-1)
	opMenu:addChild(cancelButton)

	local updateButton = oButton("Update",17,60,false,
		0,0,
		function(item)
			addImages(item.targetFile)
		end)
	updateButton.anchorPoint = oVec2.zero
	btnBk = CCDrawNode()
	btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
	btnBk.position = oVec2(30,30)
	updateButton:addChild(btnBk,-1)
	updateButton.visible = false
	opMenu:addChild(updateButton)

	panel.updateItems = function(self)
		initValues()
		local dirs = oContent:getDirEntries(oEditor.input,true)
		local files = oContent:getDirEntries(oEditor.output,false)
		local dirDict = {}
		for i = 1,#dirs do
			dirDict[dirs[i]] = true
		end
		local fileDict = {}
		for i = 1,#files do
			local name = nil
			if files[i]:sub(-5,-1) == ".clip" then
				name = files[i]:sub(1,-6)
			end
			if name then
				fileDict[name] = true
				if not dirDict[name] then
					table.insert(dirs,name)
				end
			end
		end
		local n = 0
		local y = 0
		for i = 1, #dirs do
			if dirs[i] ~= "." and dirs[i] ~= ".." then
				n = n+1
				y = winSize.height*0.5+halfBH-35-math.floor((n-1)/6)*60
				local name = #dirs[i] > 10 and dirs[i]:sub(1,7).."..." or dirs[i]
				local button = oButton(
				name,
				17,
				100,50,
				winSize.width*0.5-halfBW+60+((n-1)%6)*110, y,
				function(item)
					cancelButton.label.text = "Edit"
					cancelButton.label.texture.antiAlias = false
					menu:removeAllChildren()
					if item.file:sub(-5,-1) == ".clip" then
						cancelButton.editTarget = item.file:sub(1,-6)
						addClip(item.file)
					else
						cancelButton.editTarget = item.file
						if fileDict[item.file] then
							updateButton.targetFile = item.file
							addClip(item.file..".clip")
							updateButton.visible = true
						else
							addImages(item.file)
						end
					end
				end)
				button.file = dirDict[dirs[i]] and dirs[i] or dirs[i]..".clip"
				button.color = ccColor3(0xffffff)
				button.enabled = false
				button.opacity = 0
				button:runAction(
					CCSequence(
					{
						CCDelay(n*0.1),
						oOpacity(0.3,1),
						CCCall(
							function()
								button.enabled = true
							end)
					}))
				menu:addChild(button)
			end
		end
		
		local yTo = winSize.height*0.5+halfBH-y-35
		viewHeight = yTo < borderSize.height and borderSize.height or yTo
		viewWidth = borderSize.width
		moveY = viewHeight-borderSize.height
		moveX = borderSize.width-viewWidth
		paddingX = 0
		paddingY = 100
	end
	
	return panel
end

return oFileChooser