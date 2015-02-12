local CCDirector = require("CCDirector")
local CCMenu = require("CCMenu")
local oEditor = require("oEditor")
local oVec2 = require("oVec2")
local oButton = require("oButton")
local oEvent = require("oEvent")
local oFileChooser = require("oFileChooser")

local function oEditMenu()
	local winSize = CCDirector.winSize
	
	local menu = CCMenu(false)
	menu.touchPriority = oEditor.touchPriorityEditMenu
	menu.anchor = oVec2.zero

	-- init menu items --
	local items =
	{
		Edit = oButton("Edit",16,50,50,35,winSize.height-35,function(button)
			oEditor:addChild(oFileChooser(),oEditor.topMost)
		end),

		Zoom = oButton("100%",16,50,50,winSize.width-240-45,winSize.height-35,function(button)
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
	}

	-- add buttons to menu --
	for _,item in pairs(items) do
		menu:addChild(item)
	end
	menu.items = items

	return menu
end

return oEditMenu