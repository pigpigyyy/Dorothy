local require = using("ActionEditor.Script")
local CCDirector = require("CCDirector")
local CCSize = require("CCSize")
local oSelectionPanel = require("oSelectionPanel")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local oCache = require("oCache")
local CCSprite = require("CCSprite")
local oOpacity = require("oOpacity")
local oLine = require("oLine")
local oContent = require("oContent")
local ccBlendFunc = require("ccBlendFunc")
local oPacker = require("oPacker")
local CCNode = require("CCNode")
local CCRect = require("CCRect")
local CCRenderTarget = require("CCRenderTarget")
local CCMenu = require("CCMenu")
local oButton = require("oButton")
local thread = require("thread")
local sleep = require("sleep")
local oBox = require("oBox")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local CCSequence = require("CCSequence")
local CCDelay = require("CCDelay")
local CCCall = require("CCCall")

local models = nil

local function oFileChooser(withCancel,clipOnly,targetModelFile,groupOnly)
	local oEditor = require("oEditor")
	local winSize = CCDirector.winSize
	local itemWidth = 120
	local itemNum = 3
	while (itemWidth+10)*itemNum+10 > winSize.width and itemNum > 1 do
		itemNum = itemNum - 1
	end
	local borderSize = CCSize((itemWidth+10)*itemNum+10,winSize.height*0.6)
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
	},ccColor4(0xe5100000),0.5,ccColor4(0xffffafaf))
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
				oVec2(rc.right,rc.top),
				oVec2(rc.left,rc.top),
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
		panel.cullItems = false
		panel:reset(viewWidth,viewHeight,paddingX,paddingY)
	end

	local function addImages(file)
		panel:removeMenuItems()
		local padding = 2
		local blocks = {}
		local images = oContent:getEntries(oEditor.input..file,false)
		local blendFunc = ccBlendFunc(ccBlendFunc.One,ccBlendFunc.Zero)
		for i = 1,#images do
			if images[i]:sub(-4,-1):lower() == ".png" then
				local texFile = oEditor.input..file.."/"..images[i]
				oCache.Texture:unload(texFile)
				local sp = CCSprite(texFile)
				if sp then
					sp.texture.antiAlias = false
					sp.blendFunc = blendFunc
					sp.anchor = oVec2.zero
					local block =
					{
						w = sp.contentSize.width+padding*2,
						h = sp.contentSize.height+padding*2,
						sp = sp,
						name = images[i]:match("([^\\/]*)%.[^%.\\/]*$")
					}
					table.insert(blocks,block)
					oCache.Texture:unload(texFile)
				end
			end
		end

		oPacker:fit(blocks)
		local w = oPacker.root.w
		--local v = 2;while v < w do v = v*2 end
		--w = v
		local h = oPacker.root.h
		--v = 2;while v < h do v = v*2 end
		--h = v
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
				local x, y, w, h = block.fit.x+padding, h-block.fit.y-block.h+padding, block.sp.width, block.sp.height
				local line = oLine(
				{
					oVec2(x,y),
					oVec2(x+w,y),
					oVec2(x+w,y+h),
					oVec2(x,y+h),
					oVec2(x,y)
				},ccColor4())
				frame:addChild(line)

				block.sp.position = oVec2(x,y)
				node:addChild(block.sp)
			end
		end

		local target = CCRenderTarget(w,h)
		target:beginDraw(ccColor4(0))
		target:draw(node)
		target:endDraw()
		target:save(oEditor.output..file..".png")
		local xml = "<A A=\""..file..".png\">"
		for i = 1,#blocks do
			local block = blocks[i]
			xml = xml.."<B A=\""..block.name.."\" B=\""..tostring(block.fit.x+padding)..","..tostring(block.fit.y+padding)..","..tostring(block.w-padding*2)..","..tostring(block.h-padding*2).."\"/>"
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
		panel.cullItems = false
		panel:reset(viewWidth,viewHeight,paddingX,paddingY)
	end

	local opMenu = CCMenu()
	opMenu.swallowTouches = true
	opMenu.contentSize = CCSize(200,60)
	opMenu.touchPriority = CCMenu.DefaultHandlerPriority-5
	opMenu.position = oVec2(winSize.width*0.5+borderSize.width*0.5-70,winSize.height*0.5+borderSize.height*0.5)
	panel:addChild(opMenu)

	local backButton
	if oEditor.quitable and not clipOnly and not groupOnly then
		backButton = oButton("Quit",17,60,false,
			70,0,
			function(item)
				item.enabled = false
				opMenu.enabled = false
				panel:hide()
				if oEditor.standAlone then
					oEditor:emit("Quit")
				else
					thread(function()
						oEditor.viewArea:originReset()
						oEditor.viewArea:zoomReset()
						oEditor:hideEditor(true,false)
						sleep(0.6)
						oEditor:emit("Quit")
					end)
				end
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
				item.enabled = false
				opMenu.enabled = false
				panel:hide()
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
			local modelFile = item.editTarget..".model"
			local clip = item.clipFile:match("[^\\/]*$")
			local prefix = ""
			if #clip < #(item.clipFile) then
				prefix = item.clipFile:sub(1,-#clip-1)
			end
			modelFile = modelFile:gsub(prefix,"")
			modelFile = prefix..modelFile
			local model = oEditor.output..modelFile
			if not oContent:exist(model) then
				oBox("Will Create Model\n"..item.editTarget,function()
					opMenu.enabled = false
					panel:hide()
					local modelText = "<A A=\""..clip.."\" D=\"0,0\"><B></B></A>"
					oContent:saveToFile(model, modelText)
					oEditor:edit(modelFile,item.clipFile)
					oEditor:emit("Edited",oEditor.modelFile)
				end)
			else
				opMenu.enabled = false
				panel:hide()
				oEditor:edit(modelFile,item.clipFile)
			end
		end)
	editButton.anchor = oVec2.zero
	editButton.visible = false
	btnBk = CCDrawNode()
	btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
	btnBk.position = oVec2(30,30)
	editButton:addChild(btnBk,-1)
	opMenu:addChild(editButton)

	panel.init = function(self)
		local items
		if groupOnly then
			items = {}
			for _,dir in ipairs(oContent:getEntries(oEditor.input,true)) do
				if dir ~= "." and dir ~= ".." then
					items[dir:match("([^\\/]*)$")] = dir
				end
			end
		else
			items = {}
			models = {}
			local function getResources(path)
				local files = oContent:getEntries(oEditor.output..oEditor.prefix..path,false)
				for _,file in ipairs(files) do
					local extension = file:match("%.([^%.\\/]*)$")
					if extension then
						extension = extension:lower()
					end
					if clipOnly then
						if extension == "clip" then
							local name = file:match("([^\\/]*)%.[^%.\\/]*$")
							items[name] = oEditor.prefix..path..file
						end
					elseif groupOnly or extension == "model" then
						local name = file:match("([^\\/]*)%.[^%.\\/]*$")
						local modelFile = oEditor.prefix..path..file
						items[name] = modelFile
						table.insert(models,modelFile)
					end
				end
				local folders = oContent:getEntries(oEditor.output..oEditor.prefix..path,true)
				for _,folder in ipairs(folders) do
					if folder ~= "." and folder ~= ".." then
						getResources(path..folder.."/")
					end
				end
			end
			getResources("")
		end

		local n = 0
		local y
		local xStart = winSize.width*0.5-halfBW -- left
		local yStart = winSize.height*0.5+halfBH -- top

		local titleText
		if groupOnly then
			titleText = "Choose Image Group"
		elseif clipOnly then
			titleText = "Choose Image"
		else
			titleText = "Choose Model"
		end
		local title = CCLabelTTF(titleText,"Arial",24)
		title.texture.antiAlias = false
		title.color = ccColor3(0x00ffff)
		title.anchor = oVec2(0.5,1)
		y = yStart-20
		title.position = oVec2(winSize.width*0.5,y)
		menu:addChild(title)
		title.opacity = 0
		title:runAction(oOpacity(0.3,1))
		yStart = y-title.contentSize.height-20

		for itemName,filename in pairs(items) do
			n = n+1
			y = yStart-10-math.floor((n-1)/itemNum)*60
			local name = #itemName > 10 and itemName:sub(1,7).."..." or itemName
			local button = oButton(name,17,
			itemWidth,50,
			xStart+10+((n-1)%itemNum)*(itemWidth+10), y,
			function(item)
				local file = item.file
				if file:sub(-5,-1) == ".clip" then
					editButton.editTarget = targetModelFile or file:sub(1,-6)
					editButton.clipFile = file
					addClip(file)
					if cancelButton then cancelButton.positionX = 70 end
				else
					if file:sub(-6,-1) == ".model" then
						local clipFile = oCache.Model:getClipFile(oEditor.output..file)
						if not oContent:exist(clipFile) then
							oBox("Broken Model!")
							return
						end
						editButton.editTarget = file:sub(1,-7)
						editButton.clipFile = clipFile:sub(#oEditor.output+1,-1)
						editButton.clipName = clipFile:match("([^\\/]*)%.[^%.\\/]*$")
					else
						editButton.editTarget = targetModelFile or file
						editButton.clipFile = file..".clip"
						editButton.clipName = file
					end
					local clipName = editButton.clipName
					updateButton.targetFile = clipName
					if not groupOnly then
						addClip(editButton.clipFile)
						if oEditor.standAlone and oContent:exist(oEditor.input..clipName) and #oContent:getEntries(oEditor.input..clipName,false) > 0 then
							updateButton.visible = true
						end
					else
						updateButton.visible = true
						addImages(clipName)
					end
				end
				if cancelButton then cancelButton.positionX = updateButton.visible and 0 or 70 end
				editButton.visible = true
				if backButton then backButton.visible = false end
			end)
			button.file = filename
			button.anchor = oVec2(0,1)
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
		if not clipOnly and not groupOnly then
			n = n+1
			y = yStart-10-math.floor((n-1)/itemNum)*60
			local button = oButton("<NEW>",17,
				itemWidth,50,
				xStart+10+((n-1)%itemNum)*(itemWidth+10), y,
				function()
					opMenu.enabled = false
					panel:hide()
					oBox("New Model",function(name)
						if name == "" or name:match("[\\/|:*?<>\"%.]") then
							oBox("Invalid Name")
						else
							for _,model in ipairs(models) do
								if model:match("([^\\/]*)%.[^%.\\/]*$") == name then
									oBox("Name Exist!")
									return
								end
							end
							oFileChooser(true,true,name)
						end
					end,true)
				end)
			button.color = ccColor3(0xffcc88)
			button.anchor = oVec2(0,1)
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

		if oEditor.standAlone and not clipOnly and not groupOnly then
			n = n+1
			y = yStart-10-math.floor((n-1)/itemNum)*60
			local button = oButton("<GROUP>",17,
				itemWidth,50,
				xStart+10+((n-1)%itemNum)*(itemWidth+10), y,
				function()
					opMenu.enabled = false
					panel:hide()
					oFileChooser(true,false,nil,true)
				end)
			button.color = ccColor3(0x88ff00)
			button.anchor = oVec2(0,1)
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

		local viewHeight = winSize.height*0.5+halfBH-y+60
		local viewWidth = borderSize.width
		local paddingX = 0
		local paddingY = 100
		panel:reset(viewWidth,viewHeight,paddingX,paddingY)
	end

	panel:show()
	oEditor:addChild(panel)
	return panel
end

return oFileChooser
