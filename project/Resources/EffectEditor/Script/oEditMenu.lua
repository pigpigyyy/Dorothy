local require = using("EffectEditor.Script")
local CCDirector = require("CCDirector")
local CCMenu = require("CCMenu")
local oEditor = require("oEditor")
local oVec2 = require("oVec2")
local oButton = require("oButton")
local emit = require("emit")
local oFileChooser = require("oFileChooser")
local oPos = require("oPos")
local oEase = require("oEase")
local CCSequence = require("CCSequence")
local oScale = require("oScale")
local CCHide = require("CCHide")
local CCDelay = require("CCDelay")
local CCShow = require("CCShow")
local oClipChooser = require("oClipChooser")

local function oEditMenu()
	local winSize = CCDirector.winSize

	local menu = CCMenu()
	menu.touchPriority = oEditor.touchPriorityEditMenu
	menu.anchor = oVec2.zero

	-- init menu items --
	local items
	items =
	{
		Edit = oButton("Menu",16,50,50,35,winSize.height-35,function(button)
			if not oEditor.dirty then
				oEditor:addChild(oFileChooser(),oEditor.topMost)
			else
				if oEditor.currentFile then
					oEditor.dirty = false
					button.text = "Menu"
					oEditor:dumpData(oEditor.currentFile)
					items.Undo:hide()
					oEditor:emit("Edited",oEditor.currentName,oEditor.prefix..oEditor.currentFile)
				end
			end
			emit("Effect.settingPanel.cancel")
		end),

		Undo = oButton("Undo",16,50,50,95,winSize.height-35,function(button)
			oEditor.dirty = false
			items.Edit.text = "Menu"
			emit("Effect.settingPanel.cancel")
			oEditor:edit(oEditor.currentName)
			button:hide()
		end),

		Origin = oButton("Origin",16,50,50,winSize.width-240-105-60,winSize.height-35,function()
			emit("Effect.viewArea.toOrigin",oEditor.origin)
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
			emit("Effect.viewArea.scroll",scale)
		end),

		Play = oButton("Play",16,50,50,winSize.width-240-45,35,function()
			emit("Effect.settingPanel.cancel")
			emit("Effect.viewArea.play")
		end),

		Set = oButton("Set",16,50,50,35,45+150,function()
			if oEditor.currentFile then
				oEditor:addChild(oClipChooser(),oEditor.topMost)
			end
		end),
	}
	items.Origin.visible = false
	items.Zoom.visible = false
	items.Play.visible = false
	items.Set.visible = false

	-- add buttons to menu --
	for _,item in pairs(items) do
		menu:addChild(item)
	end
	menu.items = items

	menu:gslot("Effect.editMenu.place",function(flag)
		items.Play:stopAllActions()
		if flag then
			items.Play:runAction(oPos(0.5,winSize.width-240-45,105,oEase.OutBack))
		else
			items.Play:runAction(oPos(0.5,winSize.width-240-45,35,oEase.InBack))
		end
	end)
	menu:gslot("Effect.editor.particle",function()
		if items.Origin.visible then
			items.Origin:perform(CCSequence({CCDelay(0.3),oPos(0.3,winSize.width-240-105,winSize.height-35,oEase.OutQuad)}))
			items.Zoom:perform(CCSequence({CCDelay(0.3),oPos(0.3,winSize.width-240-45,winSize.height-35,oEase.OutQuad)}))
		else
			items.Origin.visible = true
			items.Zoom.visible = true
			items.Origin.position = oVec2(winSize.width-240-105,winSize.height-35)
			items.Zoom.position = oVec2(winSize.width-240-45,winSize.height-35)
			items.Origin:perform(CCSequence({oScale(0,0,0),oScale(0.3,1,1,oEase.OutBack)}))
			items.Zoom:perform(CCSequence({oScale(0,0,0),oScale(0.3,1,1,oEase.OutBack)}))
		end
		items.Play:stopAllActions()
		if items.Play.visible then
			items.Play:runAction(CCSequence({oPos(0.3,winSize.width-240-45,45+150,oEase.OutQuad),oPos(0.5,winSize.width-240-45,35,oEase.InBack)}))
		else
			items.Play:runAction(CCSequence({CCShow(),oScale(0,0,0),oScale(0.3,1,1,oEase.OutBack)}))
		end
		if items.Set.visible then
			items.Set:runAction(CCSequence({oScale(0.3,0,0,oEase.InBack),CCHide()}))
		end

		--emit("Effect.viewArea.pos",oEditor.origin)
	end)
	menu:gslot("Effect.editor.frame",function()
		if not items.Origin.visible then
			if items.Zoom.visible then
				items.Origin:stopAllActions()
				items.Origin.visible = true
				items.Origin:runAction(oPos(0.3,winSize.width-240-45-60,winSize.height-35,oEase.InBack))
				items.Zoom:stopAllActions()
				items.Zoom:runAction(CCSequence({CCDelay(0.3),oScale(0.3,1,1,oEase.OutBack)}))
			else
				items.Origin.visible = true
				items.Origin.position = oVec2(winSize.width-95,winSize.height-35)
				items.Origin:runAction(CCSequence({oScale(0,0,0),oScale(0.3,1,1,oEase.OutBack)}))
				items.Zoom.visible = true
				items.Zoom.position = oVec2(winSize.width-35,winSize.height-35)
				items.Zoom:runAction(CCSequence({oScale(0,0,0),oScale(0.3,1,1,oEase.OutBack)}))
			end
		else
			items.Origin:stopAllActions()
			items.Origin:runAction(oPos(0.3,winSize.width-95,winSize.height-35,oEase.OutQuad))
			items.Zoom.visible = true
			items.Zoom.position = oVec2(winSize.width-35,winSize.height-35)
			items.Zoom:runAction(CCSequence({oScale(0,0,0),oScale(0.3,1,1,oEase.OutBack)}))
		end

		if items.Play.visible then
			items.Play:runAction(CCSequence({oPos(0.5,winSize.width-240-45,45+150,oEase.OutBack),oPos(0.3,winSize.width-35,45+150,oEase.OutQuad)}))
		else
			items.Play.position = oVec2(winSize.width-35,45+150)
			items.Play:runAction(CCSequence({CCShow(),oScale(0,0,0),oScale(0.3,1,1,oEase.OutBack)}))
		end

		if not items.Set.visible then
			items.Set:runAction(CCSequence({CCShow(),oScale(0,0,0),oScale(0.3,1,1,oEase.OutBack)}))
		end

		--emit("Effect.viewArea.pos",oEditor.origin)
	end)

	items.Undo.visible = false
	items.Undo.show = function(self)
		self.visible = true
		self.enabled = true
		self.scaleX = 0
		self.scaleY = 0
		self:perform(oScale(0.3,1,1,oEase.OutBack))
	end
	items.Undo.hide = function(self)
		self.enabled = false
		self:perform(CCSequence({
			oScale(0.3,0,0,oEase.InBack),
			CCHide()
		}))
	end

	menu:gslot("Effect.editor.change",function()
		if not oEditor.dirty and items.Edit.text ~= "Save" then
			items.Edit.text = "Save"
			items.Undo:show()
		end
		oEditor.dirty = true
	end)
	menu:gslot("Effect.viewArea.scale",function(scale)
		if scale ~= 1 then items.Zoom.mode = 2 end
		items.Zoom.text = tostring(math.floor(scale*100)).."%"
	end)
	return menu
end

return oEditMenu
