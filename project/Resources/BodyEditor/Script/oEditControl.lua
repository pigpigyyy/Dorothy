local CCDirector = require("CCDirector")
local CCMenu = require("CCMenu")
local oEditor = require("oEditor")
local oVec2 = require("oVec2")
local oButton = require("oButton")
local CCNode = require("CCNode")
local oSelectionPanel = require("oSelectionPanel")
local CCSize = require("CCSize")
local CCDrawNode = require("CCDrawNode")
local ccColor4 = require("ccColor4")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local CCSequence = require("CCSequence")
local CCSpawn = require("CCSpawn")
local oOpacity = require("oOpacity")
local oScale = require("oScale")
local oEase = require("oEase")
local CCCall = require("CCCall")

local function oEditControl()
	local winSize = CCDirector.winSize

	local editControl = CCNode()

	-- init switch --
	-- switchMenu
	local switchMenu = CCMenu(false)
	switchMenu.touchPriority = oEditor.touchPriorityEditControl
	switchMenu.anchor = oVec2.zero
	switchMenu.visible = false
	editControl:addChild(switchMenu)

	-- switchButton
	local switched = nil
	local switchValue = true
	local switchButton = oButton("Yes",16,50,50,winSize.width-225,95,function(button)
		switchValue = not switchValue
		button.text = switchValue and "Yes" or "No"
		if switched then
			switched(switchValue)
		end
	end)
	switchMenu:addChild(switchButton)

	-- show & hide switch
	editControl.showSwitch = function(self, defaultValue, callback)
		editControl:hide()
		switchMenu.visible = true
		switchValue = defaultValue
		switchButton.text = switchValue and "Yes" or "No"
		switched = callback
	end
	editControl.hideSwitch = function(self)
		switchMenu.visible = false
	end
	
	-- init type selector --
	-- typeSelector
	local typeSize = CCSize(120,190)
	local halfTW = typeSize.width*0.5
	local halfTH = typeSize.height*0.5
	local typeSelector = oSelectionPanel(typeSize)
	typeSelector.position = oEditor.origin-oVec2(winSize.width*0.5,winSize.height*0.5)
	typeSelector.visible = false
	local typeBackground = CCDrawNode()
	typeBackground:drawPolygon(
	{
		oVec2(-halfTW,-halfTH),
		oVec2(halfTW,-halfTH),
		oVec2(halfTW,halfTH),
		oVec2(-halfTW,halfTH)
	},ccColor4(0xe5100000),0.5,ccColor4(0x88ffafaf))
	typeSelector.border:addChild(typeBackground,-1)
	local typeSelected = nil
	local function typeCallback(button)
		editControl:hideTypeSelector()
		if typeSelected then
			typeSelected(button.text)
		end
	end
	typeSelector.menu:addChild(oButton("Dynamic",16,100,50,60,typeSize.height-35,typeCallback))
	typeSelector.menu:addChild(oButton("Static",16,100,50,60,typeSize.height-95,typeCallback))
	typeSelector.menu:addChild(oButton("Kinematic",16,100,50,60,typeSize.height-155,typeCallback))
	editControl:addChild(typeSelector)

	-- show & hide type selector
	editControl.showTypeSelector = function(self,callback)
		editControl:hide()
		typeSelector.mask.touchEnabled = true
		typeSelector.visible = true
		typeSelector:show()
		typeSelected = callback
	end
	editControl.hideTypeSelector = function(self)
		if not typeSelector.visible then return end
		typeSelector.menu.enabled = false
		typeSelector.border:stopAllActions()
		typeSelector.border:runAction(
			CCSequence(
			{
				CCSpawn(
				{
					oOpacity(0.3,0),
					oScale(0.3,0.3,0.3,oEase.InBack)
				}),
				CCCall(
					function()
						typeSelector.mask.touchEnabled = false
						typeSelector.visible = false
					end)
			}))
	end

	-- hide all controls
	editControl.hide = function(self)
		editControl:hideSwitch()
		editControl:hideTypeSelector()
	end

	editControl:showTypeSelector()
	
	return editControl
end

return oEditControl