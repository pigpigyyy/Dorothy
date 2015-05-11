local oButton = require("oButton")
local oPacker = require("oPacker")
local oSelectionPanel = require("oSelectionPanel")
local CCDirector = require("CCDirector")
local CCSize = require("CCSize")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local oCache = require("oCache")
local CCSprite = require("CCSprite")
local oOpacity = require("oOpacity")
local oLine = require("oLine")
local oContent = require("oContent")
local CCNode = require("CCNode")
local CCRect = require("CCRect")
local CCRenderTarget = require("CCRenderTarget")
local CCImage = require("CCImage")
local CCMenu = require("CCMenu")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local CCSequence = require("CCSequence")
local CCDelay = require("CCDelay")
local CCCall = require("CCCall")
local oEditor = require("oEditor").oEditor
local oSd = require("oEditor").oSd
local ccBlendFunc = require("ccBlendFunc")
local oBox = require("oBox")

local function oFileChooser(withCancel,clipOnly,modelFile)
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
		sprite.anchor = oVec2(0,1)
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
		local images = oContent:getEntries(oEditor.input..file,false)
		CCImage.isPngAlphaPremultiplied = false
		local blendFunc = ccBlendFunc(ccBlendFunc.One,ccBlendFunc.Zero)
		for i = 1,#images do
			if images[i]:sub(1,1) ~= "." then
				local sp = CCSprite(oEditor.input..file.."/"..images[i])
				if sp then
					sp.texture.antiAlias = false
					sp.blendFunc = blendFunc
					sp.anchor = oVec2.zero
					local block =
					{
						w = sp.contentSize.width+4,
						h = sp.contentSize.height+4,
						sp = sp,
						name = images[i]:sub(1,images[i]:find("%.")-1)
					}
					table.insert(blocks,block)
				end
			end
		end
		CCImage.isPngAlphaPremultiplied = true

		oPacker:fit(blocks)
		local w = oPacker.root.w
		local v = 2;while v < w do v = v*2	end
		w = v
		local h = oPacker.root.h
		v = 2;while v < h do v = v*2 end
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
		target:draw(node)
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
		oCache.Texture:unload(texFile)
		local tex = oCache.Texture:add(target,texFile)

		local displaySprite = CCSprite(tex)
		displaySprite.anchor = oVec2.zero
		displaySprite:addChild(frame)
		displaySprite.opacity = 0
		displaySprite:runAction(oOpacity(0.3,1))
		displaySprite.position = oVec2(winSize.width*0.5-borderSize.width*0.5+10,winSize.height*0.5-borderSize.height*0.5-h+borderSize.height-10)
		menu:addChild(displaySprite)

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
	opMenu.contentSize = CCSize(200,60)
	opMenu.anchor = oVec2(1,0.5)
	opMenu.touchPriority = CCMenu.DefaultHandlerPriority-3
	opMenu.position = oVec2(winSize.width*0.5+borderSize.width*0.5+35,winSize.height*0.5+borderSize.height*0.5)
	panel:addChild(opMenu)

	local backButton
	if CCDirector.sceneStackSize > 1 and not clipOnly then
		backButton = oButton("Quit",17,60,false,
			70,0,
			function(item)
				opMenu.enabled = false
				item.tapHandler = nil
				CCDirector:popToRootScene()
			end)
		backButton.anchor = oVec2.zero
		local btnBk = CCDrawNode()
		btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
		btnBk.position = oVec2(30,30)
		backButton:addChild(btnBk,-1)
		opMenu:addChild(backButton)
	end

	local cancelButton 
	if withCancel then
		cancelButton = oButton("Cancel",17,60,false,
			140,0,
			function(item)
				opMenu.enabled = false
				panel:hide()
				item.tapHandler = nil
			end)
		cancelButton.anchor = oVec2.zero
		local btnBk = CCDrawNode()
		btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
		btnBk.position = oVec2(30,30)
		cancelButton:addChild(btnBk,-1)
		opMenu:addChild(cancelButton)
	end

	local updateButton = oButton("Update",17,60,false,
		70,0,
		function(item)
			addImages(item.targetFile)
		end)
	updateButton.anchor = oVec2.zero
	local btnBk = CCDrawNode()
	btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
	btnBk.position = oVec2(30,30)
	updateButton:addChild(btnBk,-1)
	updateButton.visible = false
	opMenu:addChild(updateButton)

	local editButton = oButton("Edit",17,60,false,
		140,0,
		function(item)
			opMenu.enabled = false
			panel:hide()
			item.tapHandler = nil
			oEditor.controlBar:clearCursors()
			local modelFile = item.editTarget..".model"
			oEditor.model = oEditor.output..modelFile
			oCache.clear()
			oCache.Texture:removeUnused()
			local files = oContent:getEntries(oEditor.output,false)
			local fileExist = false
			for i = 1,#files do
				if files[i] == modelFile then
					fileExist = true
				end
			end
			if not fileExist then
				local modelText = "<A A=\""..item.clipFile.."\" D=\"0,0\"><B></B></A>"
				oContent:saveToFile(oEditor.model, modelText)
			end
			oEditor.data = oCache.Model:getData(oEditor.model)
			oEditor.look = ""
			oEditor.animation = ""
			oEditor.animationData = nil
			oEditor.keyIndex = nil
			oEditor.currentFramePos = nil
			oEditor.sprite = nil
			oEditor.spriteData = nil
			oEditor.dirty = false
			--oEditor.needSave = false

			oEditor.editMenu:markEditButton(not oEditor.data)
			if not oEditor.data then
				oEditor.data =
				{
					0.5,--anchorX 1
					0.5,--anchorY 2
					"",--clip 3
					"",--name 4
					1,--opacity 5
					0,--angle 6
					1,--scaleX 7
					1,--scaleY 8
					0,--skewX 9
					0,--skewY 10
					0,--x 11
					0,--y 12
					{},--looks 13
					{},--animationDefs 14
					{},--children 15
					true,--front 16
					true,--isFaceRight 17
					false,--isBatchUsed 18
					CCSize.zero, --size 19
					oEditor.output..item.clipFile,--clipFile 20
					{},--keys 21
					{},--animationNames 22
					{},--lookNames 23
				}
			end
			oEditor.dirty = true
			local model = oEditor.viewArea:getModel()
			oEditor.settingPanel:resetItems()
			oEditor.viewPanel:clearSelection()
			oEditor.viewPanel:updateImages(oEditor.data,model)
			oEditor.viewArea:setModelSize(oEditor.data[oSd.size])
			oEditor.editMenu.items.Size.visible = false
			oEditor.editMenu:toSprite()
		end)
	editButton.anchor = oVec2.zero
	editButton.visible = false
	btnBk = CCDrawNode()
	btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
	btnBk.position = oVec2(30,30)
	editButton:addChild(btnBk,-1)
	opMenu:addChild(editButton)

	panel.init = function(self)
		local dirs = oContent:getEntries(oEditor.input,true)
		local files = oContent:getEntries(oEditor.output,false)
		local dirDict = {}
		for i = 1,#dirs do
			dirDict[dirs[i]] = true
		end
		local fileDict = {}
		local modelDict = {}
		for i = 1,#files do
			local name = nil
			if files[i]:sub(-5,-1) == ".clip" then
				name = files[i]:sub(1,-6)
				fileDict[name] = true
			elseif not clipOnly and files[i]:sub(-6,-1) == ".model" and not oContent:exist(oEditor.output..files[i]:sub(1,-7)..".clip") then
				name = files[i]:sub(1,-7)
				modelDict[name] = true
			end
			if name and not dirDict[name] then
				table.insert(dirs,name)
			end
		end
		local n = 0
		local y = 0
		local xStart = winSize.width*0.5-halfBW -- left
		local yStart = winSize.height*0.5+halfBH -- top

		local title = CCLabelTTF(clipOnly and "Choose Clip" or "Choose  Item","Arial",24)
		title.texture.antiAlias = false
		title.color = ccColor3(0x00ffff)
		title.anchor = oVec2(0.5,1)
		y = yStart-20
		title.position = oVec2(winSize.width*0.5,y)
		menu:addChild(title)
		title.opacity = 0
		title:runAction(oOpacity(0.3,0.5))
		yStart = y-title.contentSize.height-20

		for i = 1,#dirs do
			if dirs[i] ~= "." and dirs[i] ~= ".." then
				n = n+1
				y = yStart-35-math.floor((n-1)/itemNum)*60
				local name = #dirs[i] > 10 and dirs[i]:sub(1,7).."..." or dirs[i]
				local button = oButton(name,17,
				itemWidth,50,
				xStart+itemWidth*0.5+10+((n-1)%itemNum)*(itemWidth+10), y,
				function(item)
					local file = item.file
					panel:removeMenuItems()
					if cancelButton then cancelButton.positionX = 0 end
					editButton.visible = true
					if backButton then backButton.visible = false end
					if file:sub(-5,-1) == ".clip" then
						editButton.editTarget = modelFile or file:sub(1,-6)
						editButton.clipFile = file
						addClip(file)
						if cancelButton then cancelButton.positionX = 70 end
					else
						if file:sub(-6,-1) == ".model" then
							editButton.editTarget = file:sub(1,-7)
							local clipFile = io.open(oEditor.output..file,"r")
							editButton.clipFile = clipFile:read("*a"):match("%b\"\""):gsub("\"","")
							clipFile:close()
							editButton.clipName = editButton.clipFile:sub(1,-6)
						else
							editButton.editTarget = modelFile or file
							editButton.clipFile = file..".clip"
							editButton.clipName = file
						end
						local clipName = editButton.clipName
						if fileDict[clipName] then
							updateButton.targetFile = clipName
							addClip(editButton.clipFile)
							if oContent:exist(oEditor.input..clipName) and #oContent:getEntries(oEditor.input..clipName,false) > 0 then
								updateButton.visible = true
							end
							if cancelButton then cancelButton.positionX = updateButton.visible and 0 or 70 end
						else
							addImages(clipName)
							if cancelButton then cancelButton.positionX = 0 end
						end
					end
				end)
				button.file = dirDict[dirs[i]] and dirs[i] or (modelDict[dirs[i]] and dirs[i]..".model" or dirs[i]..".clip")
				button.enabled = false
				button.opacity = 0
				button:runAction(CCSequence(
				{
					CCDelay(n*0.05),
					oOpacity(0.2,1),
					CCCall(function()
						button.enabled = true
					end)
				}))
				menu:addChild(button)
			end
		end
		if not clipOnly then
			n = n+1
			y = yStart-35-math.floor((n-1)/itemNum)*60
			local button = oButton("<NEW>",17,
				itemWidth,50,
				xStart+itemWidth*0.5+10+((n-1)%itemNum)*(itemWidth+10), y,
				function(item)
					opMenu.enabled = false
					panel:hide()
					item.tapHandler = nil
					oBox("New Model",function(name)
						if name == "" or name:match("[\\/|:*?<>\"%.]") then
							oBox("Invalid Name")
						elseif oContent:exist(oEditor.output..name..".model") then
							oBox(name.." Exist")
						else
							oFileChooser(true,true,name)
						end
					end,true)
				end)
			button.color = ccColor3(0xffcc88)
			button.enabled = false
			button.opacity = 0
			button:runAction(CCSequence(
			{
				CCDelay(n*0.05),
				oOpacity(0.2,1),
				CCCall(function()
					button.enabled = true
				end)
			}))
			menu:addChild(button)
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