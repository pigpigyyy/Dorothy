local function oButton(text, fontSize, width, height, x, y,tapped)
	local label = CCLabelTTF(text,"Arial",fontSize)
	label.position = oVec2(width*0.5, height*0.5)
	label.texture.antiAlias = false

	local node = CCNode()
	node.cascadeColor = false
	local drawNode = CCDrawNode()
	drawNode:drawPolygon(
	{
		oVec2(0,0),
		oVec2(width,0),
		oVec2(width,height),
		oVec2(0,height)
	},ccColor4(0x88000000),0,ccColor4(0x00000000))
	node:addChild(drawNode)
	
	local face = CCNode()
	face.anchorPoint = oVec2(0.5,0.5)
	face.contentSize = CCSize(width,height)
	face.position = oVec2(width*0.5,height*0.5)
	face:addChild(node)
	face:addChild(oLine(
	{
		oVec2(0,0),
		oVec2(width,0),
		oVec2(width,height),
		oVec2(0,height),
		oVec2(0,0)
	},ccColor4()))
	face:addChild(label)

	local menuItem = CCMenuItem()
	menuItem.contentSize = CCSize(width,height)
	menuItem.anchorPoint = oVec2(0.5,0.5)
	menuItem:addChild(face)

	face.opacity = 0.3
	local scale = oScale(0.3,1.0,1.0,oEase.OutBack)
	local fade = oOpacity(0.3,0.3,oEase.InExpo)
	menuItem.label = label
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
	menuItem.position = oVec2(x,y)
	menuItem.color = ccColor3(0x00ffff)
	return menuItem
end

return oButton