local CCDirector = require("CCDirector")
local CCMenu = require("CCMenu")
local oEditor = require("oEditor")
local oVec2 = require("oVec2")
local oButton = require("oButton")
local oEvent = require("oEvent")
local oFileChooser = require("oFileChooser")
local CCArray = require("CCArray")
local oListener = require("oListener")
local oPos = require("oPos")
local oEase = require("oEase")
local CCSequence = require("CCSequence")
local oScale = require("oScale")
local CCHide = require("CCHide")
local CCDelay = require("CCDelay")

local function oEditMenu()
	local winSize = CCDirector.winSize
	
	local menu = CCMenu(false)
	menu.touchPriority = oEditor.touchPriorityEditMenu
	menu.anchor = oVec2.zero

	-- init menu items --
	local items =
	{
		Edit = oButton("Edit",16,50,50,35,winSize.height-35,function(button)
			if not oEditor.dirty then
				oEditor:addChild(oFileChooser(),oEditor.topMost)
			else
				if oEditor.currentFile then
					oEditor.dirty = false
					button.text = "Edit"
					oEditor:dumpData(oEditor.currentFile)
				end
			end
		end),

		Origin = oButton("Origin",16,50,50,winSize.width-240-45-60,winSize.height-35,function(button)
			oEvent:send("viewArea.toOrigin",oEditor.origin)
		end),

		Zoom = oButton("100%",16,50,50,winSize.width-240-45,winSize.height-35,function(button)
			button.mode = button.mode or 0
			local scale = 0
			if button.mode == 0 then
				scale = 2.0
			elseif button.mode == 1 then
				scale = 0.5
			elseif button.mode == 2 then
				scale = 1.0
			end
			button.mode = button.mode + 1
			button.mode = button.mode % 3
			button.text = tostring(scale*100).."%"
			oEvent:send("viewArea.toScale",scale)
		end),

		Play = oButton("Play",16,50,50,winSize.width-240-45,35,function(button)
			oEvent:send("settingPanel.cancel")
			oEvent:send("viewArea.play")
		end),
	}

	-- add buttons to menu --
	for _,item in pairs(items) do
		menu:addChild(item)
	end
	menu.items = items

	menu.data = CCArray()
	menu.data:add(oListener("editMenu.place",function(flag)
		items.Play:stopAllActions()
		if flag then
			items.Play:runAction(oPos(0.5,winSize.width-240-45,105,oEase.OutBack))
		else
			items.Play:runAction(oPos(0.5,winSize.width-240-45,35,oEase.InBack))
		end
	end))
	menu.data:add(oListener("oEditor.particle",function()
		if items.Origin.visible then
			items.Origin:stopAllActions()
			items.Origin:runAction(CCSequence({CCDelay(0.3),oPos(0.3,winSize.width-240-45,winSize.height-35,oEase.OutBack)}))
			items.Zoom:stopAllActions()
			items.Zoom:runAction(CCSequence({oScale(0.3,0,0,oEase.InBack),CCHide()}))
		end
	end))
	menu.data:add(oListener("oEditor.frame",function()
		if not items.Origin.visible then
			items.Origin:stopAllActions()
			items.Origin.visible = true
			items.Origin:runAction(oPos(0.3,winSize.width-240-45-60,winSize.height-35,oEase.InBack))
			items.Zoom:stopAllActions()
			items.Zoom:runAction(CCSequence({CCDelay(0.3),oScale(0.3,1,1,oEase.OutBackBack)}))
		end
	end))
	menu.data:add(oListener("oEditor.change",function()
		if not oEditor.dirty then
			oEditor.dirty = true
			items.Edit.text = "Save"
		end
	end))

	return menu
end

return oEditMenu