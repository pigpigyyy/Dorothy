local require = using("ActionEditor.Script")
local CCDirector = require("CCDirector")
local CCSize = require("CCSize")
local oVec2 = require("oVec2")
local CCLayer = require("CCLayer")
local CCDrawNode = require("CCDrawNode")
local ccColor4 = require("ccColor4")
local CCClipNode = require("CCClipNode")
local CCMenu = require("CCMenu")
local CCRect = require("CCRect")
local oEase = require("oEase")
local oLine = require("oLine")
local CCMenuItem = require("CCMenuItem")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local CCSprite = require("CCSprite")
local CCSequence = require("CCSequence")
local oScale = require("oScale")
local emit = require("emit")
local thread = require("thread")
local sleep = require("sleep")
local CCNode = require("CCNode")
local oOpacity = require("oOpacity")
local oPos = require("oPos")

local function oViewPanel()
	local oEditor = require("oEditor")
	local oSd = oEditor.oSd
	local winSize = CCDirector.winSize
	local borderSize = CCSize(160,310*(winSize.height-90)/510)
	local viewWidth = 0
	local viewHeight = 0
	local moveY = 0
	local moveX = 0
	local totalDelta = oVec2.zero
	local padding = 100
	local startPos = oVec2.zero
	local time = 0
	local _s = oVec2.zero
	local _v = oVec2.zero
	local deltaMoveLength = 0
	local isHide = false
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
	panel.anchor = oVec2.zero
	panel.contentSize = borderSize
	panel.touchEnabled = true
	panel.position = oVec2(winSize.width-170,winSize.height-borderSize.height-10)
	panel.enabledMenu = true

	local border = CCDrawNode()
	border:drawPolygon(
	{
		oVec2(0,0),
		oVec2(borderSize.width,0),
		oVec2(borderSize.width,borderSize.height),
		oVec2(0,borderSize.height)
	},ccColor4(0x88100000),0.5,ccColor4(0xffffafaf))
	panel:addChild(border)

	local stencil = CCDrawNode()
	stencil:drawPolygon(
	{
		oVec2(0,0),
		oVec2(borderSize.width-2,0),
		oVec2(borderSize.width-2,borderSize.height-2),
		oVec2(0,borderSize.height-2)
	},ccColor4())
	stencil.position = oVec2(1,1)

	local view = CCClipNode(stencil)
	panel:addChild(view)

	local menu = CCMenu()
	menu.swallowTouches = true
	menu.touchPriority = CCMenu.DefaultHandlerPriority-1
	menu.contentSize = borderSize
	menu.anchor = oVec2(0,1)
	menu.positionY = borderSize.height

	local contentRect = CCRect.zero
	local itemRect = CCRect.zero
	local function moveItems(delta)
		contentRect:set(0,0,borderSize.width,borderSize.height)
		menu:eachChild(function(child)
			child.position = child.position + delta
			if child.enabled ~= nil then
				local positionX, positionY, width, height = child.positionX, child.positionY, child.width, child.height
				itemRect:set(positionX, positionY - height/2, width, height)
				child.visible = contentRect:intersectsRect(itemRect)
			end
		end)
	end

	local function updateReset(deltaTime)
		local xVal = nil
		local yVal = nil
		time = time + deltaTime
		local t = time/4.0
		if t > 1.0 then t = 1.0 end
		--[[if startPos.x > 0 then
			xVal = totalDelta.x
			totalDelta.x = oEase:func(oEase.OutExpo,t,startPos.x,0-startPos.x)
			xVal = totalDelta.x - xVal
		end]]
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

		moveItems(oVec2(xVal and xVal or 0, yVal and yVal or 0))

		if t == 1 then
			panel:unschedule()
			--panel.touchEnabled = true
			--menu.touchEnabled = true
		end
	end

	local function isReseting()
		if --[[totalDelta.x > 0 or]] totalDelta.x < moveX or totalDelta.y > moveY or totalDelta.y < 0 then
			return true
		end
		return false
	end

	local function startReset()
		startPos = totalDelta
		time = 0
		--panel.touchEnabled = false
		--menu.touchEnabled = false
		panel:schedule(updateReset)
	end

	local function setPos(delta)
		local newPos = totalDelta+delta
		if newPos.x > 0 then
			newPos.x = 0
		elseif newPos.x-moveX < 0 then
			newPos.x = moveX
		end
		if newPos.y < 0 then
			newPos.y = 0
		elseif moveY < newPos.y then
			newPos.y = moveY
		end
		delta = newPos - totalDelta
		if viewWidth < borderSize.width then delta.x = 0 end
		if viewHeight < borderSize.height then delta.y = 0 end

		totalDelta = totalDelta + delta

		moveItems(delta)
	end

	local function setOffset(deltaPos, touching)
		local newPos = totalDelta + deltaPos

		if touching then
			if newPos.x > 0 then
				newPos.x = 0
			elseif newPos.x-moveX < -padding then
				newPos.x = moveX-padding
			end
			if newPos.y < -padding then
				newPos.y = -padding
			elseif moveY-newPos.y < -padding then
				newPos.y = moveY+padding
			end
			deltaPos = newPos - totalDelta

			local lenY = 0
			local lenX = 0
			if newPos.y < 0 then
				lenY = -newPos.y/padding
			elseif newPos.y > moveY then
				lenY = (newPos.y-moveY)/padding
			end
			if newPos.x < moveX then
				lenX = (moveX-newPos.x)/padding
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
			if newPos.x > 0 then
				newPos.x = 0
			elseif newPos.x < moveX-padding then
				newPos.x = moveX-padding
			end
			if newPos.y < -padding then
				newPos.y = -padding
			elseif newPos.y > moveY+padding then
				newPos.y = moveY+padding
			end
			deltaPos = newPos - totalDelta
		end

		if viewWidth < borderSize.width then deltaPos.x = 0 end
		if viewHeight < borderSize.height then deltaPos.y = 0 end

		totalDelta = totalDelta + deltaPos

		moveItems(deltaPos)

		if not touching and (newPos.y < -padding*0.5 or newPos.y > moveY+padding*0.5 or newPos.x > padding*0.5 or newPos.x < moveX-padding*0.5) then
			startReset()
		end
	end
	view:addChild(menu)

	local function oImageView(size, x, y, clipStr, sp, root)
		local borderSelected = CCDrawNode()
		local borderHalfSize = size*0.5+1
		borderSelected:drawPolygon(
		{
			oVec2(-borderHalfSize,-borderHalfSize),
			oVec2(borderHalfSize,-borderHalfSize),
			oVec2(borderHalfSize,borderHalfSize),
			oVec2(-borderHalfSize,borderHalfSize)
		},ccColor4(0x00000000),1,ccColor4(0xff00ffff))
		borderSelected.position = oVec2(size*0.5,size*0.5)
		borderSelected.visible = false

		local borderDraw = CCDrawNode()
		borderDraw:drawPolygon(
		{
			oVec2(0,0),
			oVec2(size,0),
			oVec2(size,size),
			oVec2(0,size)
		},ccColor4(0x88000000))

		borderDraw:addChild(oLine(
		{
			oVec2(0,0),
			oVec2(size,0),
			oVec2(size,size),
			oVec2(0,size),
			oVec2(0,0)
		},ccColor4(0xffffffff)))

		local menuItem = CCMenuItem()
		menuItem.anchor = oVec2(0,0.5)
		menuItem.contentSize = CCSize(size,size)
		menuItem.position = oVec2(x, y)
		menuItem:addChild(borderSelected)
		menuItem:addChild(borderDraw)

		if root then
			local label = CCLabelTTF("Root","Arial",16)
			label.color = ccColor3(0x00ffff)
			label.position = oVec2(size*0.5, size*0.5)
			label.texture.antiAlias = false
			menuItem:addChild(label)
		else
			if clipStr ~= "" then
				local sprite = CCSprite(clipStr)
				local contentSize = sprite.contentSize
				local scale = contentSize.width > contentSize.height and (size-2)/contentSize.width or (size-2)/contentSize.height
				sprite.scaleX = scale
				sprite.scaleY = scale
				sprite.position = oVec2(size*0.5,size*0.5)
				menuItem:addChild(sprite)
			else
				local name = sp[oSd.name]
				if name == "" then
					name = "Node"
				end
				local label = CCLabelTTF(name,"Arial",16)
				label.color = ccColor3(0x00ffff)
				label.position = oVec2(size*0.5, size*0.5)
				label.texture.antiAlias = false
				menuItem:addChild(label)
				menuItem.label = label
			end
		end

		if sp[oSd.fold] then
			local flag = CCDrawNode()
			flag:drawPolygon(
			{
				oVec2.zero,
				oVec2(5,0),
				oVec2(5,5),
				oVec2(0,5)
			},ccColor4(0x8800ffff),0.5,ccColor4(0xff00ffff))
			flag.position = oVec2(size-10,size-10)
			menuItem:addChild(flag)
		end

		local seqAnim = CCSequence(
		{
			oScale(0.15,1.3,1.3,oEase.OutSine),
			oScale(0.15,1.0,1.0,oEase.InSine)
		})
		menuItem.select = function(self,selected)
			borderSelected.visible = selected
			if selected then
				borderSelected:stopAllActions()
				borderSelected:runAction(seqAnim)
				border.color = ccColor3(0x00ffff)
				menuItem.cascadeOpacity = false
			else
				border.color = ccColor3(0xffffff)
				menuItem.cascadeOpacity = true
			end
		end

		menuItem.getData = function(self)
			return sp,sp[oSd.sprite]
		end

		local isFolding = false
		menuItem:slot("Tapped",function(self)
			if oEditor.isPlaying then
				return false
			end
			menuItem:select(true)
			oEditor.settingPanel:clearSelection()
			emit("Action.ImageSelected",{sp,sp[oSd.sprite],menuItem})
			if #sp[oSd.children] > 0 then
				if isFolding then
					isFolding = false
					sp[oSd.fold] = not sp[oSd.fold]
					local model = oEditor.viewArea:getModel()
					local offset = panel:getOffset()
					panel:clearSelection()
					panel.enabledMenu = false
					menu.enabled = false
					thread(function()
						if sp[oSd.fold] then
							local function visitSprite(data)
								local children = data[oSd.children]
								if children then
									for i = 1,#children do
										local item = panel.items[children[i]]
										if item then
											item:perform(oScale(0.3,1,0,oEase.OutQuad))
											visitSprite(children[i])
										end
									end
								end
							end
							visitSprite(sp)
							sleep(0.2)
						end
						panel:updateImages(oEditor.modelData,model)
						panel:selectItem(sp)
						panel:setOffset(offset)
						if isReseting() then
							startReset()
						end
						local targetItem = panel.items[sp]
						for _,item in pairs(panel.items) do
							if item.positionY < targetItem.positionY and item.visible then
								item.scaleY = 0
								item:perform(oScale(0.3,1,1,oEase.OutBack))
							end
						end
						panel.enabledMenu = true
						menu.enabled = true
					end)
				else
					isFolding = true
					local interval = 0
					self:schedule(function(deltaTime)
						interval = interval+deltaTime
						if interval > 0.5 then
							self:unschedule()
							isFolding = false
						end
					end)
				end
			end
		end)

		menuItem.setName = function(self,name)
			if clipStr == "" then
				self.label.text = name == "" and "Node" or name
				self.label.texture.antiAlias = false
			end
		end

		return menuItem
	end

	panel.selectItem = function(self, targetSp)
		panel:clearSelection()
		if not targetSp then
			return
		end
		local item = panel.items[targetSp]
		if item then
			local sp,sprite = item:getData()
			if targetSp == sp then
				item:select(true)
				oEditor.settingPanel:clearSelection()
				emit("Action.ImageSelected",{sp,sprite,item})
				setPos(oVec2(90-item.positionX,borderSize.height*0.5+30-item.positionY))
			end
		end
	end

	local function updateSpeed(deltaTime)
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
				panel:unschedule()
			end
		end
	end

	panel.touchPriority = CCMenu.DefaultHandlerPriority-2
	panel:slot("TouchBegan",function(touch)
		if touch.id ~= 0 then
			return false
		end
		if not CCRect(oVec2.zero, panel.contentSize):containsPoint(panel:convertToNodeSpace(touch.location)) then
			return false
		end

		deltaMoveLength = 0
		menu.enabled = true
		panel:schedule(updateSpeed)
		return true
	end)

	local function touchEnded()
		if panel.enabledMenu then
			menu.enabled = true
		end
		if isReseting() then
			startReset()
		else
			if _v ~= oVec2.zero and deltaMoveLength > 10 then
				panel:schedule(updatePos)
			end
		end
	end
	panel:slot("TouchEnded",touchEnded)
	panel:slot("TouchCancelled",touchEnded)

	panel:slot("TouchMoved",function(touch)
		deltaMoveLength = deltaMoveLength + touch.delta.length
		_s = _s + touch.delta
		if deltaMoveLength > 10 then
			menu.enabled = false
			setOffset(touch.delta, true)
		end
	end)

	panel.setOffset = function(self,offset)
		local deltaPos = offset-totalDelta
		totalDelta = totalDelta + deltaPos
		moveItems(deltaPos)
		if isReseting() then
			startReset()
		end
	end

	panel.getOffset = function(self)
		return totalDelta
	end

	panel.items = nil
	panel.updateImages = function(self, data, model)
		initValues()
		panel.items = {}
		panel:showOutline(false)
		menu:removeAllChildrenWithCleanup()
		if not data then return end
		local clipFile = data[oSd.clipFile]
		local drawNode = CCDrawNode()
		menu:addChild(drawNode)
		local size = 60
		local indent = 10
		local root = model.children[1]
		local function visitSprite(sp,x,y,child)
			local clip = sp[oSd.clip]
			if not sp[oSd.sprite] then
				sp[oSd.sprite] = child -- don`t override data from updateSprite()
			end
			local isRoot = child == root
			local imageView = oImageView(size,x,y-size/2,
				clip == ""
				and "" or (clipFile.."|"..tostring(clip)),
				sp,isRoot)
			panel.items[sp] = imageView
			menu:addChild(imageView)
			local children = sp[oSd.children]
			local nextY = -size-indent
			local layer = 1
			local maxSubLayer = 0
			local lastLen = 0
			if not sp[oSd.fold] then
				local childrenSize = #children
				for i = 1, childrenSize do
					drawNode:drawSegment(oVec2(x+indent,y+nextY-size*0.5),oVec2(x+indent*2,y+nextY-size*0.5),0.5,ccColor4(0xffffffff))
					children[i][oSd.parent] = sp
					children[i][oSd.index] = i
					local sprite = children[i][oSd.sprite]
					local lenY, subLayer = visitSprite(children[i],x+indent*2,y+nextY,sprite or child.children[i]) -- reuse data computed from updateSprite()
					nextY = nextY + lenY
					if maxSubLayer < subLayer then maxSubLayer = subLayer end
					if i == childrenSize then
						lastLen = lenY
					end
				end
			end
			if nextY < -size-indent then
				drawNode:drawSegment(oVec2(x+indent,y-size),oVec2(x+indent,y+nextY-lastLen-size*0.5),0.5,ccColor4(0xffffffff))
			end
			return nextY, layer+maxSubLayer
		end

		local height, layer = visitSprite(data,indent,borderSize.height-indent,model.children[1])
		viewHeight = -height+indent
		if viewHeight < borderSize.height then viewHeight = borderSize.height end
		viewWidth = layer*indent*2+size
		if viewWidth < borderSize.width then viewWidth = borderSize.width end
		moveY = viewHeight-borderSize.height
		moveX = borderSize.width-viewWidth
		setPos(oVec2.zero)
	end

	local function oImageOutline(target, isWithFrame)
		local outline = CCNode()
		local frame = oLine({},ccColor4(0xff00a2d8))
		outline:addChild(frame)
		local anchor = oLine(
		{
			oVec2(0,-5),
			oVec2(5,0),
			oVec2(0,5),
			oVec2(-5,0),
			oVec2(0,-5)
		},ccColor4(0xffffffff))
		anchor:addChild(
			oLine({oVec2(0,-5),oVec2(0,5)},ccColor4(0xffffffff)))
		anchor:addChild(
			oLine({oVec2(-5,0),oVec2(5,0)},ccColor4(0xffffffff)))
		outline:addChild(anchor)

		outline.setNode = function(self, node, withFrame)
			local w = node.contentSize.width
			local h = node.contentSize.height
			if withFrame then
				frame:set(
				{
					oVec2(0,0),
					oVec2(w,0),
					oVec2(w,h),
					oVec2(0,h),
					oVec2(0,0),
				})
			else
				frame:set({})
			end
			anchor.position = oVec2(w*node.anchor.x, h*node.anchor.y)
			self.transformTarget = node
		end

		outline:setNode(target, isWithFrame)

		outline.updateAnchor = function(self, node)
			anchor.position = oVec2(node.contentSize.width*node.anchor.x, node.contentSize.height*node.anchor.y)
		end

		return outline
	end

	panel.updateItemName = function(self,sp)
		panel.items[sp]:setName(sp[oSd.name])
	end

	local selectedItem = nil
	local outline = nil
	panel:gslot("Action.ImageSelected",
		function(args)
			if not args then
				if selectedItem then
					selectedItem:select(false)
					selectedItem = nil
					oEditor.sprite = nil
					oEditor.spriteData = nil
					oEditor.controlBar:clearCursors()
					oEditor.settingPanel:updateValues(nil)
					if oEditor.state == oEditor.EDIT_SPRITE then
						oEditor.settingPanel:setEditEnable(false)
					end
					panel:showOutline(false)
					oEditor.keyIndex = 1
					oEditor.settingPanel:clearSelection()
					oEditor.settingPanel:update()
				end
				return
			end
			local sp = args[1]
			local node = args[2]
			local menuItem = args[3]
			local aDefs = sp[oSd.animationDefs]

			if oEditor.state == oEditor.EDIT_ANIMATION and oEditor.animation then
				local aNames = oEditor.modelData[oSd.animationNames]
				local animation = aDefs[aNames[oEditor.animation]+1]
				oEditor.animationData = animation
			end

			if selectedItem then
				selectedItem:select(false)
			end

			if selectedItem ~= menuItem then
				local withFrame = node.contentSize ~= CCSize.zero
				if not outline then
					outline = oImageOutline(node,withFrame)
					oEditor.viewArea.outline:addChild(outline)
				else
					outline:setNode(node,withFrame)
				end
				outline.visible = true

				oEditor.sprite = node
				oEditor.spriteData = sp

				if oEditor.state == oEditor.EDIT_ANIMATION then
					oEditor.controlBar:updateCursors()
				end
				selectedItem = menuItem
				if oEditor.state == oEditor.EDIT_SPRITE then
					oEditor.settingPanel:setEditEnable(true)
				end
			else
				outline.visible = false
				selectedItem = nil
				oEditor.sprite = nil
				oEditor.spriteData = nil
				oEditor.controlBar:clearCursors()
				oEditor.settingPanel:updateValues(nil)
				if oEditor.state == oEditor.EDIT_SPRITE then
					oEditor.settingPanel:setEditEnable(false)
				end
			end

			oEditor.keyIndex = 1
			oEditor.settingPanel:clearSelection()
			oEditor.settingPanel:update()
			if not sp[oSd.parent] then
				oEditor.settingPanel:setEditEnable(false)
			end
		end)

	panel.updateSprite = function(self,data,model)
		local function visitSprite(sp,child)
			if sp[oSd.sprite] == oEditor.sprite then
				oEditor.sprite = child
			end
			sp[oSd.sprite] = child
			local children = sp[oSd.children]
			for i = 1, #children do
				visitSprite(children[i],child.children[i])
			end
		end
		visitSprite(data,model.children[1])
		if selectedItem ~= nil then
			local sp,node = selectedItem:getData()
			local withFrame = node.contentSize ~= CCSize.zero
			if not outline then
				outline = oImageOutline(node,withFrame)
				oEditor.viewArea.outline:addChild(outline)
			else
				outline:setNode(node,withFrame)
			end
			outline.visible = true

			oEditor.sprite = node
			oEditor.spriteData = sp
		end
	end

	panel.showOutline = function(self, show)
		if outline then
			outline.visible = show
		end
	end

	panel.isOutlineVisible = function(self)
		if outline then
			return outline.visible
		else
			return false
		end
	end

	panel.updateAnchor = function(self,node)
		if outline then
			outline:updateAnchor(node)
		end
	end

	panel.clearSelection = function(self)
		emit("Action.ImageSelected",nil)
	end
	panel.glow = function(self)
		self:runAction(
			CCSequence
			{
				oOpacity(0.15,0.8),
				oOpacity(0.15,1)
			})
	end
	panel.updateItems = function(self,look)
		if look then
			local oldSize = borderSize
			borderSize = CCSize(160,winSize.height-20)
			local scale = borderSize.height/oldSize.height
			border.scaleY = scale
			stencil.scaleY = scale
		else
			borderSize = CCSize(160,310*(winSize.height-90)/510)
			border.scaleY = 1
			stencil.scaleY = 1
		end
		panel.contentSize = borderSize
		if not isHide then
			panel.positionX = winSize.width-170
		end
		panel.positionY = winSize.height-borderSize.height-10
		menu.contentSize = borderSize
		menu.positionY = borderSize.height
		oEditor.dirty = true
		panel:clearSelection()
		panel:updateImages(oEditor.modelData,oEditor.viewArea:getModel())
		panel:glow()
	end

	panel:gslot("Action.hideEditor",function(args)
		local hide,instant = unpack(args)
		if isHide == hide then
			return
		end
		isHide = hide
		local winWidth = CCDirector.winSize.width
		if instant then
			panel.positionX = winWidth*2-panel.positionX
		else
			panel:runAction(oPos(0.5,winWidth*2-panel.positionX,panel.positionY,oEase.OutQuad))
		end
	end)

	return panel
end

return oViewPanel
