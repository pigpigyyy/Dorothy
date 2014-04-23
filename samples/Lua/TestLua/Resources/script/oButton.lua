local function oButton(text, fontSize, width, height, x, y,tapped)
	
	local node = CCNode()
	node.cascadeColor = false
	local drawNode = CCDrawNode()
	if not height then
		drawNode:drawDot(oVec2(width*0.5,width*0.5),width*0.5,ccColor4(0x88000000))
	else
		drawNode:drawPolygon(
		{
			oVec2(0,0),
			oVec2(width,0),
			oVec2(width,height),
			oVec2(0,height)
		},ccColor4(0x88000000),0,ccColor4(0x00000000))
	end
	node:addChild(drawNode)

	local face = CCNode()
	face.anchorPoint = oVec2(0.5,0.5)
	face.contentSize = CCSize(width,height and height or width)
	face.position = oVec2(width*0.5,height and height*0.5 or width*0.5)
	face:addChild(node)
	if not height then
		local vs = {}
		local num = 20
		for i = 0, num do
			local angle = 2*math.pi*i/num
			table.insert(vs,oVec2(width*0.5*math.cos(angle),width*0.5*math.sin(angle))+oVec2(width*0.5,width*0.5))
		end
		face:addChild(oLine(vs,ccColor4()))
	else
		face:addChild(oLine(
		{
			oVec2(0,0),
			oVec2(width,0),
			oVec2(width,height),
			oVec2(0,height),
			oVec2(0,0)
		},ccColor4()))
	end

	local menuItem = CCMenuItem()
	menuItem.contentSize = CCSize(width,height and height or width)
	menuItem.anchorPoint = oVec2(0.5,0.5)
	menuItem:addChild(face)
	
	if text ~= "" then
		local label = CCLabelTTF(text,"Arial",fontSize)
		label.position = oVec2(width*0.5, height and height*0.5 or width*0.5)
		label.texture.antiAlias = false
		face:addChild(label)
		menuItem.label = label
	end

	face.opacity = 0.3
	local scale = oScale(0.3,1.0,1.0,oEase.OutBack)
	local fade = oOpacity(0.3,0.3,oEase.InExpo)
	menuItem:registerTapHandler(
		function(eventType, item)
			--item = CCMenuItem
			if eventType == CCMenuItem.TapBegan then
				if not fade.done then
					face:stopAction(fade)
				end
				if not scale.done then
					face:stopAction(scale)
				end
				face.opacity = 1.0
				face.scaleX = 0.3
				face.scaleY = 0.3
				face:runAction(scale)
			elseif eventType == CCMenuItem.TapEnded then
				face:runAction(fade)
			elseif eventType == CCMenuItem.Tapped then
				if tapped then
					tapped(menuItem)
				end
			end
		end)
	menuItem.face = face
	menuItem.tapped = tapped
	menuItem.position = oVec2(x,y)
	menuItem.color = ccColor3(0x00ffff)
	return menuItem
end

return oButton