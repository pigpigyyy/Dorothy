local oButton = require("oButton")
local CCDirector = require("CCDirector")
local CCMenu = require("CCMenu")
local oVec2 = require("oVec2")
local oLine = require("oLine")
local ccColor4 = require("ccColor4")
local CCNode = require("CCNode")
local oEditor = require("oEditor")

local function oEditMenu()
	local winSize = CCDirector.winSize
	local menu = CCMenu()
	menu.anchor = oVec2.zero
	local items =
	{
		Edit = oButton("Edit",16,50,50,35,winSize.height-35,
			function()
			end),
		Rectangle = oButton("",16,50,50,35,winSize.height-95,
			function()
			end),
		Circle = oButton("",16,50,50,35,winSize.height-155,
			function()
			end),
		Polygon = oButton("",16,50,50,35,winSize.height-215,
			function()
			end),
		Play = oButton("Play",16,50,50,winSize.width-225,35,
			function(button)
				oEditor.isPlaying = not oEditor.isPlaying
				if oEditor.isPlaying then
					button.text = "Stop"
				else
					button.text = "Play"
				end
			end),
	}

	-- Rectangle
	local paint = oLine(
	{
		oVec2(-15,15),
		oVec2(15,15),
		oVec2(15,-15),
		oVec2(-15,-15),
		oVec2(-15,15),
	},ccColor4(0xffff0080))
	local node = CCNode()
	node.cascadeColor = false
	node.position = oVec2(25,25)
	node:addChild(paint)
	items.Rectangle.face:addChild(node)

	-- Circle
	local vs = {}
	local num = 20
	for i = 0, num do
		local angle = 2*math.pi*i/num
		table.insert(vs,oVec2(18*math.cos(angle),18*math.sin(angle)))
	end
	paint = oLine(vs,ccColor4(0xffff0080))
	node = CCNode()
	node.cascadeColor = false
	node.position = oVec2(25,25)
	node:addChild(paint)
	items.Circle.face:addChild(node)

	-- Polygon
	paint = oLine(
	{
		oVec2(0,18),
		oVec2(18,-18),
		oVec2(-18,-18),
		oVec2(0,18),
	},ccColor4(0xffff0080))
	node = CCNode()
	node.cascadeColor = false
	node.position = oVec2(25,25)
	node:addChild(paint)
	items.Polygon.face:addChild(node)

	-- add buttons to menu
	for _,item in pairs(items) do
		menu:addChild(item)
	end
	menu.items = items

	return menu
end

return oEditMenu