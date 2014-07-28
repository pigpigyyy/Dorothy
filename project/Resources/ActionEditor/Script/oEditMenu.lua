local oButton = require("oButton")
local oFileChooser = require("oFileChooser")
local oSpriteChooser = require("oSpriteChooser")
local oEditChooser = require("oEditChooser")
local oLookChooser = require("oLookChooser")
local oBox = require("oBox")
local CCDirector = require("CCDirector")
local CCMenu = require("CCMenu")
local oVec2 = require("oVec2")
local oCache = require("oCache")
local ccColor3 = require("ccColor3")
local oEvent = require("oEvent")
local cclog = require("cclog")
local CCObject = require("CCObject")
local CCSequence = require("CCSequence")
local CCDelay = require("CCDelay")
local oOpacity = require("oOpacity")
local oListener = require("oListener")
local oSd = require("oEditor").oSd
local oEditor = require("oEditor").oEditor
local oAd = require("oEditor").oAd
local oKd = require("oEditor").oKd

local function removeAnimation(sp,index)
	local aDefs = sp[oSd.animationDefs]
	table.remove(aDefs,index)
	local children = sp[oSd.children]
	for i = 1,#children do
		removeAnimation(children[i],index)
	end
end

local function removeLook(sp,index)
	local looks = sp[oSd.looks]
	for i = 1,#looks do
		if looks[i] == index then
			table.remove(looks,i)
			break
		end
	end
	local children = sp[oSd.children]
	for i = 1,#children do
		removeLook(children[i],index)
	end
end

local function oEditMenu()
    local winSize = CCDirector.winSize
    local menu = CCMenu(false)
	menu.anchor = oVec2.zero
	local frameCopy = nil
	local items =
	{
		Edit = oButton("Edit",16,50,50,35,winSize.height-35,
			function()
				oEditor.settingPanel:clearSelection()
				if oEditor.needSave then
					menu:markEditButton(false)
					oEditor.viewArea:getModel()
					oCache.Model:save(oEditor.model,oEditor.model)
					return
				end
				if oEditor.isPlaying then
					menu.items.Play:tapped()
				end
				if oEditor.state == oEditor.EDIT_START then
					oFileChooser()
				elseif oEditor.state ~= oEditor.EDIT_NONE and oEditor.state ~= oEditor.EDIT_START then
					oEditChooser(true)
				end
			end),
		Del = oButton("Del",16,50,50,95,winSize.height-35,
			function()
				if oEditor.state == oEditor.EDIT_ANIMATION then
					oBox("Delete\n"..oEditor.animation,function()
						local aNames = oEditor.data[oSd.animationNames]
						local index = aNames[oEditor.animation]
						
						removeAnimation(oEditor.data,index+1)
						for k,v in pairs(aNames) do
							if v > index then
								aNames[k] = v-1
							end
						end
						aNames[oEditor.animation] = nil
						oEditor.animation = ""
						oEditor.dirty = true
						oEditor.viewArea:getModel()
						menu:markEditButton(true)
						oEditChooser(false)
					end)
				elseif oEditor.state == oEditor.EDIT_LOOK then
					oBox("Delete\n"..oEditor.look,function()
						local lNames = oEditor.data[oSd.lookNames]
						local index = lNames[oEditor.look]
						removeLook(oEditor.data,index)
						for k,v in pairs(lNames) do
							if v > index then
								lNames[k] = v-1
							end
						end
						lNames[oEditor.look] = nil
						oEditor.look = ""
						oEditor.dirty = true
						oEditor.viewArea:getModel()
						menu:markEditButton(true)
						oEditChooser(false)
					end)
				end
			end),
		Fix = oButton("Fixed\nOn",16,50,50,35,winSize.height-95,
			function(item)
				oEditor.viewArea.isValueFixed = not oEditor.viewArea.isValueFixed
				if oEditor.viewArea.isValueFixed then
					item:setText("Fixed\nOn")
				else
					item:setText("Fixed\nOff")
				end
			end),
		Size = oButton("Size\nOff",16,50,50,35,winSize.height-155,
			function(item)
				local visible = oEditor.viewArea:getModelSizeVisible()
				if visible then
					item:setText("Size\nOff")
				else
					item:setText("Size\nOn")
				end
				oEditor.viewArea:showModelSize(not visible)
			end),
		--[[
		Move = oButton("Move",16,50,50,35,winSize.height-95),
		Rotate = oButton("Rotate",16,50,50,35,winSize.height-155,
			function()
				oEditor.viewArea:editRot()
			end),
		Scale = oButton("Scale",16,50,50,35,winSize.height-215,
			function(self)
			end),
		Opacity = oButton("Opacity",14,50,50,35,winSize.height-275),
		]]
		New = oButton("New",16,50,50,35,95,
			function()
				local pos = oEditor.controlBar:getPos()
				if oEditor.sprite and pos ~= oEditor.currentFramePos and not oEditor.spriteData[oSd.animationNames] then
					local sprite = oEditor.sprite
					local sp = oEditor.spriteData
					local animationDef = oEditor.animationData
					if not animationDef then
						animationDef = {}
						local aDefs = sp[oSd.animationDefs]
						local aNames = oEditor.data[oSd.animationNames]
						aDefs[aNames[oEditor.animation]+1] = animationDef
						oEditor.animationData = animationDef
						animationDef[oAd.type] = 1
						local curPos = oAd.frameDefs
						if pos ~= 0 then
							animationDef[curPos] =
							{
								sp[oSd.x],
								sp[oSd.y],
								sp[oSd.scaleX],
								sp[oSd.scaleY],
								sp[oSd.skewX],
								sp[oSd.skewY],
								sp[oSd.rotation],
								sp[oSd.opacity],
								true,
								0,0,0,0,0,0
							}
							curPos = curPos+1
						end
						animationDef[curPos] =
						{
							sp[oSd.x],
							sp[oSd.y],
							sp[oSd.scaleX],
							sp[oSd.scaleY],
							sp[oSd.skewX],
							sp[oSd.skewY],
							sp[oSd.rotation],
							sp[oSd.opacity],
							true,
							0,0,0,0,0,
							pos/60
						}
					else
						local duration = pos/60 - oEditor.currentFramePos/60
						local nextDef = oEditor.animationData[oEditor.keyIndex+1]
						if nextDef then	
							nextDef[oKd.duration] = nextDef[oKd.duration]-duration
						end
						local frameDef =
						{
							sprite.positionX,
							sprite.positionY,
							sprite.scaleX,
							sprite.scaleY,
							sprite.skewX,
							sprite.skewY,
							sprite.rotation,
							sprite.opacity,
							sprite.visible,
							0,0,0,0,0,
							duration
						}
						table.insert(oEditor.animationData,oEditor.keyIndex+1,frameDef)
					end	
					oEditor.dirty = true
					oEditor.viewArea:getModel()
					oEditor.controlBar:updateCursors()
					oEditor.settingPanel:clearSelection()
					oEditor.settingPanel:update()
					menu:markEditButton(true)
				end
			end),
		Delete = oButton("Delete",16,50,50,95,95,
			function()
				local pos = oEditor.controlBar:getPos()
				if oEditor.sprite and pos == oEditor.currentFramePos and (oEditor.keyIndex ~= 2 or #oEditor.animationData == 2) then
					oBox("Delete\nFrame",function()
						local sp = oEditor.spriteData
						local animationDef = oEditor.animationData
						if animationDef then
							local nextDef = animationDef[oEditor.keyIndex+1]
							local prevDef = nil
							if oEditor.keyIndex > 2 then
								prevDef = animationDef[oEditor.keyIndex-1]
							end
							local curDef = animationDef[oEditor.keyIndex]
							if prevDef then
								if nextDef then
									nextDef[oKd.duration] = 								nextDef[oKd.duration]+curDef[oKd.duration]
								end
								table.remove(animationDef, oEditor.keyIndex)
								oEditor.keyIndex = oEditor.keyIndex-1
							else
								local aDefs = sp[oSd.animationDefs]
								local aNames = oEditor.data[oSd.animationNames]
								aDefs[aNames[oEditor.animation]+1] = false
								oEditor.animationData = false
							end
							oEditor.dirty = true
							oEditor.viewArea:getModel()
							oEditor.controlBar:updateCursors()
							oEditor.settingPanel:clearSelection()
							oEditor.settingPanel:update()
							menu:markEditButton(true)
						end
					end)
				end
			end),
		Copy = oButton("Copy",16,50,50,155,95,
			function(item)
				local pos = oEditor.controlBar:getPos()
				if oEditor.sprite and pos == oEditor.currentFramePos then
					local frameDef = oEditor.animationData[oEditor.keyIndex]
					frameCopy =
					{
						frameDef[oKd.x],
						frameDef[oKd.y],
						frameDef[oKd.scaleX],
						frameDef[oKd.scaleY],
						frameDef[oKd.skewX],
						frameDef[oKd.skewY],
						frameDef[oKd.rotation],
						frameDef[oKd.opacity],
						frameDef[oKd.visible],
						frameDef[oKd.easeOpacity],
						frameDef[oKd.easePos],
						frameDef[oKd.easeRotation],
						frameDef[oKd.easeScale],
						frameDef[oKd.easeSkew],
						0,
					}
					item.color = ccColor3(0xff88cc)
				end
			end),
		Paste = oButton("Paste",16,50,50,215,95,
			function()
				local pos = oEditor.controlBar:getPos()
				if oEditor.sprite and pos ~= oEditor.currentFramePos then
					local sp = oEditor.spriteData
					local animationDef = oEditor.animationData
					if not animationDef then
						animationDef = {}
						local aDefs = sp[oSd.animationDefs]
						local aNames = oEditor.data[oSd.animationNames]
						aDefs[aNames[oEditor.animation]+1] = animationDef
						oEditor.animationData = animationDef
						animationDef[oAd.type] = 1
						local curPos = oAd.frameDefs
						if pos ~= 0 then
							animationDef[curPos] =
							{
								sp[oSd.x],
								sp[oSd.y],
								sp[oSd.scaleX],
								sp[oSd.scaleY],
								sp[oSd.skewX],
								sp[oSd.skewY],
								sp[oSd.rotation],
								sp[oSd.opacity],
								sp[oSd.visible],
								0,0,0,0,0,0
							}
							curPos = curPos+1
						end
						frameCopy[oKd.duration] = pos/60
						animationDef[curPos] = frameCopy
					else
						local duration = pos/60 - oEditor.currentFramePos/60
						local nextDef = oEditor.animationData[oEditor.keyIndex+1]
						if nextDef then	
							nextDef[oKd.duration] = nextDef[oKd.duration]-duration
						end
						frameCopy[oKd.duration] = duration
						table.insert(oEditor.animationData,oEditor.keyIndex+1,frameCopy)
					end	
					oEditor.dirty = true
					oEditor.viewArea:getModel()
					oEditor.controlBar:updateCursors()
					oEditor.settingPanel:clearSelection()
					oEditor.settingPanel:update()
					menu:markEditButton(true)
					frameCopy = nil
					menu.items.Copy.color = ccColor3(0x00ffff)
				end
			end),
		Clear = oButton("Clear",16,50,50,275,95,
			function()
				if oEditor.sprite and oEditor.animationData then
					oBox("Clear\nFrames",function()
						local sp = oEditor.spriteData
						local aDefs = sp[oSd.animationDefs]
						local aNames = oEditor.data[oSd.animationNames]
						aDefs[aNames[oEditor.animation]+1] = false
						oEditor.animationData = false
						oEditor.keyIndex = 1
						oEditor.dirty = true
						oEditor.viewArea:getModel()
						oEditor.controlBar:updateCursors()
						oEditor.settingPanel:clearSelection()
						oEditor.settingPanel:update()
						menu:markEditButton(true)
					end)
				end
			end),
		Look = oButton("Look",16,50,50,winSize.width-205,215,
			function()
				oLookChooser()
			end),
		Loop = oButton("Once",16,50,50,winSize.width-205,155,
			function(item)
				if oEditor.loop then
					oEditor.loop = false
					item.label.text = "Once"
					item.label.texture.antiAlias = false
					oEvent:send("LoopState",false)
				else
					oEditor.loop = true
					item.label.text = "Loop"
					item.label.texture.antiAlias = false
					oEvent:send("LoopState",true)
				end
			end),
		Play = oButton("Play",16,50,50,winSize.width-205,95,
			function(item)
				-- item = CCNode
				if not oEditor.animation then return end
				oEditor.settingPanel:clearSelection()
				local model = oEditor.viewArea:getModel()
				if model then
					if not oEditor.isPlaying then
						oEditor.isPlaying = true
						item.label.text = "Pause"
						item.label.texture.antiAlias = false
						model:resume(oEditor.animation)
						-- update controlBar progress
						item:schedule(
							function(self)
								--model = oModel
								if model.playing then
									local time = model.time * model.duration
									oEditor.controlBar:setTime(time)
								else
									oEditor.controlBar:setTime(model.duration)
									oEditor.isPlaying = false
									item.label.text = "Play"
									item.label.texture.antiAlias = false
									self:unschedule()
									oEvent:send("PlayState","Stop")
								end
							end)
						oEvent:send("PlayState","Play")
					else
						oEditor.isPlaying = false
						item.label.text = "Play"
						item.label.texture.antiAlias = false
						model:pause()
						item:unschedule()
						oEvent:send("PlayState","Pause")
					end
				end
			end),

		Origin = oButton("Origin",16,50,50,winSize.width-265,winSize.height-35,
			function()
				collectgarbage()
				cclog("[LUA MEMORY USAGE] %d KB",collectgarbage("count"))
				cclog("Object Count: %d",CCObject.count)
				cclog("Lua Count: %d",CCObject.luaRefCount)
				cclog("Callback Count: %d", CCObject.callRefCount)
				oEditor.viewArea:originReset()
			end),
		Zoom = oButton("100%",16,50,50,winSize.width-205,winSize.height-35,
			function()
				oEditor.viewArea:zoomReset()
			end),

		Batch = oButton("Batch\nUsed",16,54,50,35,35,
			function(item)
				if oEditor.data[oSd.isBatchUsed] then
					item:setText("Batch\nUnused")
					oEditor.data[oSd.isBatchUsed] = false
				else
					item:setText("Batch\nUsed")
					oEditor.data[oSd.isBatchUsed] = true
				end
				oCache.Model:loadData(oEditor.model,oEditor.data)
				menu:markEditButton(true)
			end),
		Face = oButton("Face\nRight",16,54,50,97,35,
			function(item)
				if oEditor.data[oSd.isFaceRight] then
					item:setText("Face\nLeft")
					oEditor.data[oSd.isFaceRight] = false
				else
					item:setText("Face\nRight")
					oEditor.data[oSd.isFaceRight] = true
				end
				oCache.Model:loadData(oEditor.model,oEditor.data)
				menu:markEditButton(true)
			end),
		Add = oButton("Add",16,50,50,winSize.width-205,95,
			function()
				-- item = CCNode
				if oEditor.spriteData then
					local chooser = oSpriteChooser()
					chooser.selected = function(self, name)
						local children = oEditor.spriteData[oSd.children]
						local sp =
						{
							0.5,--anchorX
							0.5,--anchorY
							name,--clip
							"",--name
							1,--opacity
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
							true,--front
						}
						table.insert(children,sp)
						oEditor.dirty = true
						local model = oEditor.viewArea:getModel()
						oEditor.viewPanel:clearSelection()
						oEditor.viewPanel:updateImages(oEditor.data,model)
						oEditor.viewPanel:selectItem(sp)
						menu:markEditButton(true)
					end
				end
			end),
		Remove = oButton("Delete",16,50,50,winSize.width-205,35,
			function()
				-- item = CCNode
				if oEditor.spriteData and  oEditor.spriteData[oSd.parent] then
					local name = oEditor.spriteData[oSd.name]
					if name == "" then
						name = oEditor.spriteData[oSd.clip] == "" and "Node" or "Sprite"
					end
					oBox("Delete\n"..name,function()
						local parent = oEditor.spriteData[oSd.parent]
						local index = oEditor.spriteData[oSd.index]
						table.remove(parent[oSd.children],index)
						oEditor.dirty = true
						local model = oEditor.viewArea:getModel()
						oEditor.viewPanel:clearSelection()
						oEditor.viewPanel:updateImages(oEditor.data,model)
						menu:markEditButton(true)
					end)
				end
			end),
		Up = oButton("Up",16,50,50,winSize.width-205,215,
			function()
				if oEditor.spriteData and  oEditor.spriteData[oSd.parent] then
					local sp = oEditor.spriteData
					local parent = oEditor.spriteData[oSd.parent]
					local index = 
oEditor.spriteData[oSd.index]
					local children = parent[oSd.children]
					if index > 1 then
						local prev = children[index-1]
						children[index-1] = sp
						children[index] = prev
						oEditor.dirty = true
						local model = oEditor.viewArea:getModel()
						oEditor.viewPanel:clearSelection()
						oEditor.viewPanel:updateImages(oEditor.data,model)
						oEditor.viewPanel:selectItem(sp)
						menu:markEditButton(true)
					end
				end
			end),
		Down = oButton("Down",16,50,50,winSize.width-205,155,
			function()
				if oEditor.spriteData and  oEditor.spriteData[oSd.parent] then
					local sp = oEditor.spriteData
					local parent = oEditor.spriteData[oSd.parent]
					local index = oEditor.spriteData[oSd.index]
					local children = parent[oSd.children]
					if index < #children then
						local next = children[index+1]
						children[index+1] = sp
						children[index] = next
						oEditor.dirty = true
						local model = oEditor.viewArea:getModel()
						oEditor.viewPanel:clearSelection()
						oEditor.viewPanel:updateImages(oEditor.data,model)
						oEditor.viewPanel:selectItem(sp)
						menu:markEditButton(true)
					end
				end
			end),
		
		Change = oButton("Rep",16,50,50,winSize.width-205,275,
			function()
				if oEditor.spriteData and oEditor.spriteData[oSd.parent] then
					local sp = oEditor.spriteData
					local chooser = oSpriteChooser()
					chooser.selected = function(self, name)
						sp[oSd.clip] = name
						oEditor.dirty = true
						local model = oEditor.viewArea:getModel()
						oEditor.viewPanel:clearSelection()
						oEditor.viewPanel:updateImages(oEditor.data,model)
						oEditor.viewPanel:selectItem(sp)
						menu:markEditButton(true)
					end
				end
			end),
		
		Move = oButton("Move",16,50,50,winSize.width-205,335,
			function(item)
				if oEditor.spriteData and oEditor.spriteData[oSd.parent] then
					if item.isMoving then
						item.color = ccColor3(0x00ffff)
						item:setText("Move")
						item.isMoving = false
						if item.sp ~= oEditor.spriteData then
							local sp = oEditor.spriteData
							local parent = item.sp[oSd.parent]
							table.remove(parent[oSd.children],item.sp[oSd.index])
							table.insert(sp[oSd.children],item.sp)
							item.sp[oSd.parent] = sp
							item.sp[oSd.index] = #sp[oSd.children]
							oEditor.dirty = true
							local model = oEditor.viewArea:getModel()
							oEditor.viewPanel:clearSelection()
							oEditor.viewPanel:updateImages(oEditor.data,model)
							oEditor.viewPanel:selectItem(item.sp)
							menu:markEditButton(true)
						end
					else
						item.sp = oEditor.spriteData
						item.color = ccColor3(0xff88cc)
						item:setText("Mov\ning")
						item.isMoving = true
					end
				end
			end),
		Visible = oButton("Hide",16,50,50,winSize.width-205,35,
			function(item)
				-- item = CCNode
				if oEditor.sprite and oEditor.spriteData then
					local sp = oEditor.spriteData
					local lname = oEditor.data[oSd.lookNames]
					local index = lname[oEditor.look]
					local looks = sp[oSd.looks]
					if not looks then
						looks = {}
						sp[oSd.looks] = looks
					end
					if oEditor.sprite.visible then
						table.insert(looks,index)
						oEditor.sprite.visible = false
						item:setText("Show")
					else
						for i = 1,#looks do
							if looks[i] == index then
								table.remove(looks,i)
								break
							end
						end
						oEditor.sprite.visible = true
						item:setText("Hide")
					end
					oEditor.dirty = true
					menu:markEditButton(true)
				end
			end),
	}
	for _,item in pairs(items) do
		menu:addChild(item)
	end
	menu.items = items

	menu.markEditButton = function(self,flag)
		if oEditor.needSave == flag then
			return
		end
		local label = items.Edit.label
		if flag then
			label.text = "Save"
			label.texture.antiAlias = false
		else
			label.text = "Edit"
			label.texture.antiAlias = false
		end
		oEditor.needSave = flag
	end

	local function hideItems()
		local group = {
			items.Del,
			items.Fix,
			items.Size,
			items.New,
			items.Delete,
			items.Copy,
			items.Paste,
			items.Clear,
			items.Loop,
			items.Play,
			items.Add,
			items.Remove,
			items.Up,
			items.Down,
			items.Change,
			items.Visible,
			items.Look,
			items.Batch,
			items.Face,
			items.Move,
		}
		for i = 1,#group do
			group[i].visible = false
		end
		if items.Move.isMoving then
			items.Move.color = ccColor3(0x00ffff)
			items.Move:setText("Move")
			items.Move.isMoving = false
		end
	end

	menu.toStart = function(self)
		if oEditor.state == oEditor.EDIT_START then
			return
		end
		items.Origin.visible = false
		items.Zoom.visible = false
		hideItems()
		oEditor.state = oEditor.EDIT_START
		oEditor.settingPanel:updateItems()
		oEditor.controlBar.visible = false
		oEditor.settingPanel.touchEnabled = false
		oEditor.viewPanel.touchEnabled = false
		oEditor.viewArea.touchEnabled = false
	end

	menu.toSprite = function(self)
		local function updateBF()
			items.Batch:setText(oEditor.data[oSd.isBatchUsed] and "Batch\nUsed" or "Batch\nUnused")
			items.Face:setText(oEditor.data[oSd.isFaceRight] and "Face\nRight" or "Face\nLeft")
		end
		if oEditor.state == oEditor.EDIT_SPRITE then
			updateBF()
			return
		end
		hideItems()
		local group = {
			items.Fix,
			items.Batch,
			items.Face,
			items.Remove,
			items.Add,
			items.Down,
			items.Up,
			items.Change,
			items.Move,
		}
		if oEditor.state == oEditor.EDIT_ANIMATION then
			table.remove(group,1)
			items.Fix.visible = true
		end
		if oEditor.state == oEditor.EDIT_START then
			table.insert(group,items.Zoom)
			table.insert(group,items.Origin)
			oEditor.settingPanel.touchEnabled = true
			oEditor.viewPanel.touchEnabled = true
			oEditor.viewArea.touchEnabled = true
		end
		for i = 1,#group do
			group[i].visible = true
			group[i].opacity = 0
			group[i]:runAction(
				CCSequence(
				{
					CCDelay(i*0.1),
					oOpacity(0.3,1)
				}))
		end
		if oEditor.state == oEditor.EDIT_LOOK then
			oEditor.viewPanel:updateItems(false)
			oEditor.settingPanel.visible = true
		end
		oEditor.state = oEditor.EDIT_SPRITE
		updateBF()
		local model = oEditor.viewArea:getModel()
		model.look = ""
		model:reset()
		local sp = oEditor.spriteData
		oEditor.settingPanel:updateItems()
		oEditor.viewPanel:selectItem(sp)
		oEditor.viewPanel:glow()
		oEditor.controlBar.visible = false
	end

	menu.toAnimation = function(self)
		if oEditor.state == oEditor.EDIT_ANIMATION then
			oEditor.viewPanel:clearSelection()
			local model = oEditor.viewArea:getModel()
			model:play(oEditor.animation)
			model:pause()
			model.time = 0
			oEditor.controlBar:setTime(0)
			return
		end
		hideItems()
		local group = {
			items.Del,
			items.Fix,
			items.New,
			items.Delete,
			items.Copy,
			items.Paste,
			items.Clear,
			items.Play,
			items.Loop,
			items.Look,
		}
		if oEditor.state == oEditor.EDIT_SPRITE then
			table.remove(group,2)
			items.Fix.visible = true
		end
		for i = 1,#group do
			group[i].visible = true
			group[i].opacity = 0
			group[i]:runAction(
				CCSequence(
				{
					CCDelay(i*0.1),
					oOpacity(0.3,1)
				}))
		end
		if oEditor.state == oEditor.EDIT_LOOK then
			oEditor.viewPanel:updateItems(false)
			oEditor.settingPanel.visible = true
		end
		oEditor.state = oEditor.EDIT_ANIMATION
		oEditor.settingPanel:updateItems()
		oEditor.viewPanel:selectItem(oEditor.spriteData)
		oEditor.viewPanel:glow()
		oEditor.controlBar:updateCursors()
		oEditor.controlBar:setTime(0)
		oEditor.controlBar.visible = true
		oEditor.controlBar.opacity = 0
		oEditor.controlBar:runAction(oOpacity(0.3,0.3))
		local model = oEditor.viewArea:getModel()
		model.look = oEditor.look
		model:play(oEditor.animation)
		model:pause()
		model.time = 0
	end

	menu.toLook = function(self)
		if oEditor.state == oEditor.EDIT_LOOK then
			if oEditor.sprite then
				items.Visible:setText(oEditor.sprite.visible and "Hide" or "Show")
			else
				items.Visible:setText("Visible")
			end
			return
		end
		hideItems()
		local group = {
			items.Del,
			items.Visible,
		}
		for i = 1,#group do
			group[i].visible = true
			group[i].opacity = 0
			group[i]:runAction(
				CCSequence(
				{
					CCDelay(i*0.1),
					oOpacity(0.3,1)
				}))
		end
		items.Size.visible = false
		items.Visible:setText("Visible")
		menu.selectListener.enabled = true
		oEditor.state = oEditor.EDIT_LOOK
		oEditor.settingPanel.visible = false
		oEditor.controlBar.visible = false
		oEditor.viewPanel:updateItems(true)
		oEditor.viewPanel:selectItem(oEditor.spriteData)
	end
	
	menu.selectListener = oListener("ImageSelected",
		function(args)
			if not args then
				return
			end
			items.Visible:setText(args[2].visible and "Hide" or "Show")
		end)
	menu.selectListener.enabled = false

	menu.loadListener = oListener("EditorLoaded",
		function()
			menu:toStart()
		end)
    return menu
end

return oEditMenu