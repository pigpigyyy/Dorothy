local oButton = require("Script/oButton")
local oFileChooser = require("Script/oFileChooser")
local oSpriteChooser = require("Script/oSpriteChooser")

local function oEditMenu()
    local winSize = CCDirector.winSize
    local menu = CCMenu(false)
	menu.anchorPoint = oVec2.zero
	local frameCopy = nil
	local items =
	{
		Edit = oButton("Edit",16,50,50,35,winSize.height-35,
			function()
				oEditor.settingPanel:clearSelection()
				if oEditor.needSave then
					menu:markEditButton(false)
					oCache.Model:loadData(oEditor.model,oEditor.data)
					oCache.Model:save(oEditor.model,oEditor.model)
					return
				end
				if oEditor.isPlaying then
					menu.items.Play:tapped()
				end
				local chooser = oFileChooser()
				chooser:show()
				oEditor.scene:addChild(chooser)
			end),
		Fix = oButton("Fixed\nOff",16,50,50,35,winSize.height-95,
			function(item)
				oEditor.viewArea.isValueFixed = not oEditor.viewArea.isValueFixed
				if oEditor.viewArea.isValueFixed then
					item.label.text = "Fixed\nOn"
					item.label.texture.antiAlias = false
				else
					item.label.text = "Fixed\nOff"
					item.label.texture.antiAlias = false
				end
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
								sp[oSd.visible],
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
							sp[oSd.visible],
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
					local sprite = oEditor.sprite
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
				end
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
						item:scheduleUpdate(
							function(deltaTime,self)
								--model = oModel
								if model.playing then
									local time = model.time * model.duration
									oEditor.controlBar:setTime(time)
								else
									oEditor.isPlaying = false
									item.label.text = "Play"
									item.label.texture.antiAlias = false
									self:unscheduleUpdate()
									oEvent:send("PlayState","Stop")
								end
							end)
						oEvent:send("PlayState","Play")
					else
						oEditor.isPlaying = false
						item.label.text = "Play"
						item.label.texture.antiAlias = false
						model:pause()
						item:unscheduleUpdate()
						oEvent:send("PlayState","Pause")
					end
				end
			end),

		Origin = oButton("Origin",16,50,50,winSize.width-265,winSize.height-35,
			function()
				collectgarbage()
				cclog("Object Count: %d",CCObject.count)
				cclog("Lua Count: %d",CCObject.luaRefCount)
				oEditor.viewArea:originReset()
			end),
		Zoom = oButton("100%",16,50,50,winSize.width-205,winSize.height-35,
			function()
				oEditor.viewArea:zoomReset()
			end),
		
		Add = oButton("Add",16,50,50,winSize.width-205,95,
			function(item)
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
						}
						table.insert(children,sp)
						oCache.Model:loadData(oEditor.model, oEditor.data)
						local model = oModel(oEditor.model)
						model.loop = oEditor.loop
						oEditor.viewArea:setModel(model)
						oEditor.viewPanel:clearSelection()
						oEditor.viewPanel:updateImages(oEditor.data,model)
						oEditor.viewPanel:selectItem(sp)
						self:hide()
						menu:markEditButton(true)
					end
					chooser:show()
					oEditor.scene:addChild(chooser)
				end
			end),
		Remove = oButton("Delete",16,50,50,winSize.width-205,35,
			function(item)
				-- item = CCNode
				if oEditor.spriteData and  oEditor.spriteData[oSd.parent] then
					local parent = oEditor.spriteData[oSd.parent]
					local index = oEditor.spriteData[oSd.index]
					table.remove(parent[oSd.children],index)
					oCache.Model:loadData(oEditor.model, oEditor.data)
					local model = oModel(oEditor.model)
					model.loop = oEditor.loop
					oEditor.viewArea:setModel(model)
					oEditor.viewPanel:clearSelection()
					oEditor.viewPanel:updateImages(oEditor.data,model)
					menu:markEditButton(true)
				end
			end),
		Up = oButton("Up",16,50,50,winSize.width-205,215,
			function(item)
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
						oCache.Model:loadData(oEditor.model, oEditor.data)
						local model = oModel(oEditor.model)
						model.loop = oEditor.loop
						oEditor.viewArea:setModel(model)
						oEditor.viewPanel:clearSelection()
						oEditor.viewPanel:updateImages(oEditor.data,model)
						oEditor.viewPanel:selectItem(sp)
						menu:markEditButton(true)
					end
				end
			end),
		Down = oButton("Down",16,50,50,winSize.width-205,155,
			function(item)
				if oEditor.spriteData and  oEditor.spriteData[oSd.parent] then
					local sp = oEditor.spriteData
					local parent = oEditor.spriteData[oSd.parent]
					local index = oEditor.spriteData[oSd.index]
					local children = parent[oSd.children]
					if index < #children then
						local next = children[index+1]
						children[index+1] = sp
						children[index] = next
						oCache.Model:loadData(oEditor.model, oEditor.data)
						local model = oModel(oEditor.model)
						model.loop = oEditor.loop
						oEditor.viewArea:setModel(model)
						oEditor.viewPanel:clearSelection()
						oEditor.viewPanel:updateImages(oEditor.data,model)
						oEditor.viewPanel:selectItem(sp)
						menu:markEditButton(true)
					end
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
			items.Fix,
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
		}
		for i = 1,#group do
			group[i].visible = false
		end
	end
	
	menu.toStart = function(self)
		if oEditor.state == oEditor.EDIT_START then
			return
		end
		hideItems()
		oEditor.state = oEditor.EDIT_START
		oEditor.settingPanel:updateItems()
		oEditor.controlBar.visible = false
	end

	menu.toSprite = function(self)
		if oEditor.state == oEditor.EDIT_SPRITE then
			return
		end
		hideItems()
		local group = {
			items.Fix,
			items.Up,
			items.Down,
			items.Add,
			items.Remove,
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
		oEditor.state = oEditor.EDIT_SPRITE
		oEditor.settingPanel:updateItems()
		oEditor.settingPanel:update()
		oEditor.controlBar.visible = false
	end

	menu.toAnimation = function(self)
		if oEditor.state == oEditor.EDIT_ANIMATION then
			return
		end
		hideItems()
		local group = {
			items.Fix,
			items.New,
			items.Delete,
			items.Copy,
			items.Paste,
			items.Clear,
			items.Play,
			items.Loop
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
		oEditor.state = oEditor.EDIT_ANIMATION
		oEditor.settingPanel:updateItems()
		oEditor.settingPanel:clearSelection()
		oEditor.settingPanel:update()
		oEditor.controlBar:updateCursors()
		oEditor.controlBar.visible = true
		oEditor.controlBar.opacity = 0
		oEditor.controlBar:runAction(oOpacity(0.3,0.3))
		local model = oEditor.viewArea:getModel()
		model:play(oEditor.animation)
		model:pause()
		model.time = 0
	end

	menu.loadListener = oListener("EditorLoaded",
		function()
			menu:toStart()
		end)
    return menu
end

return oEditMenu