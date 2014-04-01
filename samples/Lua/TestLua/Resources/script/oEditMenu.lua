local oButton = require("script/oButton")

local function oEditMenu()
    local winSize = CCDirector.winSize
    local menu = CCMenu()
	menu.anchorPoint = oVec2.zero
	menu.items =
	{
		Edit = oButton("Edit",16,50,50,35,winSize.height-35,
			function()
				oEditor.controlBar:clearCursors()
				oEditor.settingPanel:updateValues(nil)
				local isBatchUsed = oEditor.data[oSd.isBatchUsed]
				oEditor.data[oSd.isBatchUsed] = false
				oCache.Model:loadData(oEditor.model, oEditor.data)
				oEditor.data[oSd.isBatchUsed] = isBatchUsed
				local model = oModel(oEditor.model)
				model.look = oEditor.look
				model.loop = oEditor.loop
				--model.opacity = 0.3
				oEditor.viewArea:setModel(model)
				oEditor.viewPanel:updateImages(oEditor.data,model)
			end),
		Move = oButton("Move",16,50,50,35,winSize.height-95),
		Rotate = oButton("Rotate",16,50,50,35,winSize.height-155),
		Scale = oButton("Scale",16,50,50,35,winSize.height-215),
		Opacity = oButton("Opacity",14,50,50,35,winSize.height-275),
		
		New = oButton("New",16,50,50,35,95),
		Delete = oButton("Delete",16,50,50,95,95,
			function()
				oEditor.viewArea:setModel(nil)
			end),
		Copy = oButton("Copy",16,50,50,155,95),
		Paste = oButton("Paste",16,50,50,215,95),
		Clear = oButton("Clear",16,50,50,275,95),
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
				oEditor.viewArea:originReset()
			end),
		Zoom = oButton("100%",16,50,50,winSize.width-205,winSize.height-35,
			function()
				oEditor.viewArea:zoomReset()
			end),
	}
	for _,item in pairs(menu.items) do
		menu:addChild(item)
	end
    return menu
end

return oEditMenu