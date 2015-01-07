local oButton = require("oButton")
local CCDirector = require("CCDirector")
local CCMenu = require("CCMenu")
local oVec2 = require("oVec2")
local oLine = require("oLine")
local ccColor4 = require("ccColor4")
local ccColor3 = require("ccColor3")
local CCNode = require("CCNode")
local oEditor = require("oEditor")
local oPlayButton = require("oPlayButton")
local oListener = require("oListener")
local oEvent = require("oEvent")
local class,property = unpack(require("class"))

local function oEditMenu()
	local winSize = CCDirector.winSize
	
	local menu = CCMenu(false)
	menu.touchPriority = oEditor.touchPriorityEditMenu
	menu.anchor = oVec2.zero
	
	local lastSelected = nil
	local oShapeButton = class(oButton,
	{
		__partial = function(self)
			self._selected = false
			return oButton.__partial(self)
		end,
		__init = function(self,name,x,y)
			oButton.__init(self,"",0,50,50,x,y,self.onTapped)
			self._name = name
		end,
		onTapped = function(self)
			self.selected = not self.selected
		end,
		selected = property(
			function(self)
				return self._selected
			end,
			function(self,value)
				self._selected = value
				oEvent:send("editControl.hide")
				if value then
					self.color = ccColor3(0xff0080)
					if lastSelected then
						lastSelected.selected = false
					end
					lastSelected = self
					oEvent:send("editMenu.create",self._name)
				else
					self.color = ccColor3(0x00ffff)
					if lastSelected == self then
						oEvent:send("editMenu.create",nil)
					end
					lastSelected = nil
				end
			end),
	})

	-- init menu items --
	local items =
	{
		Edit = oButton("Edit",16,50,50,35,winSize.height-35,function()
			oEditor:addChild(require("oBox")("Name It",function(text)
				if text ~= "" then
					local oRoutine = require("oRoutine")
					local once = oRoutine.once
					oRoutine(once(function()
						coroutine.yield()
						oEditor:dumpData(text..".lua")
						coroutine.yield()
						CCDirector:popToRootScene()
					end))
				end
			end,true),999)
		end),
		Rectangle = oShapeButton("Rectangle",35,winSize.height-95),
		Circle = oShapeButton("Circle",35,winSize.height-155),
		Polygon = oShapeButton("Polygon",35,winSize.height-215),
		Chain = oShapeButton("Chain",35,winSize.height-275),
		Loop = oShapeButton("Loop",35,winSize.height-335),
		Del = oButton("Delete",16,50,50,35,winSize.height-395,function()
			if oEditor.currentData then
				oEvent:send("settingPanel.toState",nil)
				oEditor:removeData(oEditor.currentData)
				oEditor.currentData = nil
			end
		end),
		Joint = oButton("",0,50,50,35,35,function() end),

		Origin = oButton("Origin",16,50,50,winSize.width-285,winSize.height-35,function()
			oEvent:send("viewArea.toPos",oEditor.origin)
		end),

		Zoom = oButton("100%",16,50,50,winSize.width-225,winSize.height-35,function(button)
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

		Play = oPlayButton(50,winSize.width-225,35,function(button)
			oEditor.isPlaying = button.isPlaying
			oEditor.worldScheduler.timeScale = oEditor.isPlaying and 1 or 0
			if not oEditor.isPlaying then
				oEditor:resetItems()
			end
			oEvent:send("editControl.hide")
			oEvent:send("settingPanel.edit",nil)
			oEvent:send("settingPanel.enable",not oEditor.isPlaying)
		end),
	}

	-- rectangle button --
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

	-- circle button --
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

	-- polygon button --
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
	
	-- chain button --
	paint = oLine(
	{
		oVec2(-15,15),
		oVec2(0,15),
		oVec2(0,-15),
		oVec2(15,-15),
	},ccColor4(0xffff0080))
	node = CCNode()
	node.cascadeColor = false
	node.position = oVec2(25,25)
	node:addChild(paint)
	items.Chain.face:addChild(node)

	-- loop button --
	paint = oLine(
	{
		oVec2(-16,0),
		oVec2(-8,16),
		oVec2(4,8),
		oVec2(8,16),
		oVec2(16,0),
		oVec2(8,-16),
		oVec2(-8,-16),
		oVec2(-16,0),
	},ccColor4(0xffff0080))
	node = CCNode()
	node.cascadeColor = false
	node.position = oVec2(25,25)
	node:addChild(paint)
	items.Loop.face:addChild(node)
	
	-- joint button --
	node = CCNode()
	node.cascadeColor = false
	node.position = oVec2(25,25)
	paint = oLine(
	{
		oVec2(-13,13),
		oVec2(13,-13),
	},ccColor4(0xffff0080))
	node:addChild(paint)
	paint = oLine(
	{
		oVec2(-16,16),
		oVec2(-10,16),
		oVec2(-10,10),
		oVec2(-16,10),
		oVec2(-16,16),
	},ccColor4(0xff80ff00))
	node:addChild(paint)
	paint = oLine(
	{
		oVec2(16,-16),
		oVec2(10,-16),
		oVec2(10,-10),
		oVec2(16,-10),
		oVec2(16,-16),
	},ccColor4(0xff80ff00))
	node:addChild(paint)
	items.Joint.face:addChild(node)

	-- update scale button --
	items.Zoom.mode = 0
	items.Zoom.data = oListener("viewArea.scale",function(scale)
		if scale ~= 1 then items.Zoom.mode = 2 end
		items.Zoom.text = tostring(math.floor(scale*100)).."%"
	end)
	menu.data = oListener("editMenu.created",function()
		if lastSelected then
			lastSelected.selected = false
			lastSelected = nil
		end
	end)

	-- add buttons to menu --
	for _,item in pairs(items) do
		menu:addChild(item)
	end
	menu.items = items

	return menu
end

return oEditMenu