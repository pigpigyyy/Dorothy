local oButton = require("Script/oButton")
local oPacker = require("Script/oPacker")
local oSelectionPanel = require("Script/oSelectionPanel")

local function oFileChooser()
	local winSize = CCDirector.winSize
	local itemWidth = 120
	local itemNum = 3
	local borderSize = CCSize((itemWidth+10)*itemNum+10,winSize.height-200)
	local panel = oSelectionPanel(borderSize)
	local menu = panel.menu
	local border = panel.border
	local halfBW = borderSize.width*0.5
	local halfBH = borderSize.height*0.5
	local background= CCDrawNode()
	background:drawPolygon(
	{
		oVec2(-halfBW,-halfBH),
		oVec2(halfBW,-halfBH),
		oVec2(halfBW,halfBH),
		oVec2(-halfBW,halfBH)
	},ccColor4(0xe5100000),0.5,ccColor4(0x88ffafaf))
	border:addChild(background,-1)

	local function addClip(file)
		panel:removeMenuItems()
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

		local yTo = sprite.contentSize.height+20
		local xTo = sprite.contentSize.width+20
		local viewHeight = yTo < borderSize.height and borderSize.height or yTo
		local paddingY = 100
		if yTo < borderSize.height then paddingY = 0 end
		local viewWidth = xTo < borderSize.width and borderSize.width or xTo
		local paddingX = 100
		if xTo < borderSize.width then
			paddingX = 0
			sprite.positionX = sprite.positionX+borderSize.width*0.5-sprite.contentSize.width*0.5
		end
		panel:reset(viewWidth,viewHeight,paddingX,paddingY)
	end
	
	local function addImages(file)
		panel:removeMenuItems()
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

		local yTo = h+20
		local xTo = w+20
		local viewHeight = yTo < borderSize.height and borderSize.height or yTo
		local paddingY = 100
		if yTo < borderSize.height then paddingY = 0 end
		local viewWidth = xTo < borderSize.width and borderSize.width or xTo
		local paddingX = 100
		if xTo < borderSize.width then
			paddingX = 0
			node.positionX = node.positionX+borderSize.width*0.5-w*0.5
		end
		panel:reset(viewWidth,viewHeight,paddingX,paddingY)
	end

	local opMenu = CCMenu()
	opMenu.contentSize = CCSize(130,60)
	opMenu.touchPriority = CCMenu.DefaultHandlerPriority-3
	opMenu.position = oVec2(winSize.width*0.5+borderSize.width*0.5-35,winSize.height*0.5+borderSize.height*0.5)
	panel:addChild(opMenu)

	local updateButton = oButton("Update",17,60,false,
		0,0,
		function(item)
			addImages(item.targetFile)
		end)
	updateButton.anchorPoint = oVec2.zero
	local btnBk = CCDrawNode()
	btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
	btnBk.position = oVec2(30,30)
	updateButton:addChild(btnBk,-1)
	updateButton.visible = false
	opMenu:addChild(updateButton)

	local cancelButton = oButton("Cancel",17,60,false,
		70,0,
		function(item)
			opMenu.enabled = false
			panel:hide()
			updateButton:unregisterTapHandler()
			item:unregisterTapHandler()
			if item.editTarget then
				oEditor.controlBar:clearCursors()
				oEditor.model = oEditor.output..item.editTarget..".model"
				oCache.clear()
				CCTextureCache:removeUnused()
				oEditor.data = oCache.Model:getData(oEditor.model)
				oEditor.look = ""
				oEditor.animation = ""
				oEditor.animationData = nil
				oEditor.keyIndex = nil
				oEditor.currentFramePos = nil
				oEditor.sprite = nil
				oEditor.spriteData = nil
				oEditor.dirty = false
				oEditor.needSave = false

				if not oEditor.data then
					oEditor.data =
					{
						0.5,--anchorX
						0.5,--anchorY
						"",--clip
						"",--name
						1,--opacity
						0,--rotation
						1,--scaleX
						1,--scaleY
						0,--skewX
						0,--skewY
						0,--x
						0,--y
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
					oEditor.editMenu:markEditButton(true)
				end
				oEditor.dirty = true
				local model = oEditor.viewArea:getModel()
				oEditor.viewPanel:clearSelection()
				oEditor.viewPanel:updateImages(oEditor.data,model)
				oEditor.viewArea:setModelSize(oEditor.data[oSd.size])
				oEditor.editMenu:toSprite()
			end
		end)
	cancelButton.anchorPoint = oVec2.zero
	btnBk = CCDrawNode()
	btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
	btnBk.position = oVec2(30,30)
	cancelButton:addChild(btnBk,-1)
	opMenu:addChild(cancelButton)

	panel.init = function(self)
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
		local xStart = winSize.width*0.5-halfBW -- left
		local yStart = winSize.height*0.5+halfBH -- top

		local title = CCLabelTTF("Choose  Model","Arial",24)
		title.texture.antiAlias = false
		title.color = ccColor3(0x00ffff)
		title.anchorPoint = oVec2(0.5,1)
		y = yStart-20
		title.position = oVec2(winSize.width*0.5,y)
		menu:addChild(title)
		title.opacity = 0
		title:runAction(oOpacity(0.3,0.5))
		yStart = y-title.contentSize.height-20

		for i = 1, #dirs do
			if dirs[i] ~= "." and dirs[i] ~= ".." then
				n = n+1
				y = yStart-35-math.floor((n-1)/itemNum)*60
				local name = #dirs[i] > 10 and dirs[i]:sub(1,7).."..." or dirs[i]
				local button = oButton(
				name,
				17,
				itemWidth,50,
				winSize.width*0.5-halfBW+itemWidth*0.5+10+((n-1)%itemNum)*(itemWidth+10), y,
				function(item)
					cancelButton.label.text = "Edit"
					cancelButton.label.texture.antiAlias = false
					panel:removeMenuItems()
					if item.file:sub(-5,-1) == ".clip" then
						cancelButton.editTarget = item.file:sub(1,-6)
						addClip(item.file)
					else
						cancelButton.editTarget = item.file
						if fileDict[item.file] then
							updateButton.targetFile = item.file
							addClip(item.file..".clip")
							if #oContent:getDirEntries(oEditor.input..item.file,false) > 0 then
								updateButton.visible = true
							end
						else
							addImages(item.file)
						end
					end
				end)
				button.file = dirDict[dirs[i]] and dirs[i] or dirs[i]..".clip"
				--button.color = ccColor3(0xffffff)
				button.enabled = false
				button.opacity = 0
				button:runAction(
					CCSequence(
					{
						CCDelay(n*0.05),
						oOpacity(0.2,1),
						CCCall(
							function()
								button.enabled = true
							end)
					}))
				menu:addChild(button)
			end
		end

		local yTo = winSize.height*0.5+halfBH-y+35
		local viewHeight = yTo < borderSize.height and borderSize.height or yTo
		local viewWidth = borderSize.width
		local paddingX = 0
		local paddingY = 100
		panel:reset(viewWidth,viewHeight,paddingX,paddingY)
	end

	panel:show()
	oEditor.scene:addChild(panel)
	return panel
end

return oFileChooser