local oButton = require("oButton")
local oTextField = require("oTextField")
local CCDirector = require("CCDirector")
local CCNode = require("CCNode")
local CCLayer = require("CCLayer")
local oVec2 = require("oVec2")
local CCMenu = require("CCMenu")
local CCDrawNode = require("CCDrawNode")
local ccColor4 = require("ccColor4")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local CCSize = require("CCSize")
local CCMenuItem = require("CCMenuItem")
local CCSequence = require("CCSequence")
local CCSpawn = require("CCSpawn")
local oOpacity = require("oOpacity")
local oScale = require("oScale")
local oEase = require("oEase")
local CCCall = require("CCCall")
local oEditor = require("oEditor").oEditor

local function oBox(text,okHandler,isInput)
	local w = CCDirector.winSize.width*0.5
	local h = CCDirector.winSize.height*0.5
	local size = isInput and 125 or 90
	local box = CCNode()

	local mask = CCLayer()
	mask.anchor = oVec2.zero
	mask.touchPriority = CCMenu.DefaultHandlerPriority-4
	mask.swallowTouches = true
	mask.touchEnabled = true
	mask:slots("TouchBegan",function() return true end)
	box:addChild(mask)

	local border = CCDrawNode()
	border:drawPolygon(
	{
		oVec2(-size,-size),
		oVec2(size,-size),
		oVec2(size,size),
		oVec2(-size,size)
	},ccColor4(0xe5100000),0.5,ccColor4(0x88ffafaf))
	border.position = oVec2(w,h)
	box:addChild(border)

	local title = CCLabelTTF(text,"Arial",24)
	title.texture.antiAlias = false
	title.position = oVec2(0,isInput and 76 or 36)
	title.color = ccColor3(0x00ffff)
	border:addChild(title)

	local menu = nil
	local textField = nil
	if isInput then
		local frame = CCDrawNode()
		frame:drawPolygon(
		{
			oVec2(-85,-18),
			oVec2(85,-18),
			oVec2(85,18),
			oVec2(-85,18)
		},ccColor4(0),0.5,ccColor4(0xff00ffff))
		border:addChild(frame)

		menu = CCMenu()
		menu.swallowTouches = true
		menu.contentSize = CCSize(120,50)
		menu.touchPriority = CCMenu.DefaultHandlerPriority-5
		border:addChild(menu)

		textField = oTextField(120,18,17,10,
			function(self)
				frame.opacity = 0.3
				self.opacity = 0.3
				box:hide()
				textField:detachWithIME()
				if okHandler then
					okHandler(textField.text)
				end
			end)
		--textField=CCTextFieldTTF
		textField.position = oVec2(0,-9)
		textField:attachWithIME()
		border:addChild(textField)

		local menuItem = CCMenuItem()
		menuItem.contentSize = CCSize(120,50)
		menuItem.anchor = oVec2.zero
		menuItem:slots("Tapped",function()
			textField:attachWithIME()
			textField.opacity = 1
			frame.opacity = 1
		end)
		menu:addChild(menuItem)
	end

	box.show = function(self)
		border.scaleX = 0
		border.scaleY = 0
		border.opacity = 0
		border:runAction(
			CCSequence(
			{
				CCSpawn(
				{
					oOpacity(0.3,1),
					oScale(0.3,1,1,oEase.OutBack)
				}),
				CCCall(
					function()
						local opMenu = CCMenu()
						opMenu.swallowTouches = true
						opMenu.contentSize = CCSize(130,60)
						opMenu.touchPriority = CCMenu.DefaultHandlerPriority-6
						opMenu.position = oVec2(w,h-(isInput and 76 or 36))
						box:addChild(opMenu)

						local okButton = oButton("OK",17,60,false,
							okHandler and 0 or 35,0,
							function()
								opMenu:removeHandlers()
								box:hide()
								if isInput then
									textField:detachWithIME()
									if okHandler then
										okHandler(textField.text)
									end
								else
									if okHandler then
										okHandler()
									end
								end
							end)
						okButton.anchor = oVec2.zero
						local btnBk = CCDrawNode()
						btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
						btnBk.position = oVec2(30,30)
						okButton:addChild(btnBk,-1)
						opMenu:addChild(okButton)
						local cancelButton
						if okHandler then
							cancelButton = oButton("Cancel",17,60,false,
								70,0,
								function(item)
									item.enabled = false
									opMenu:removeHandlers()
									box:hide()
								end)
							cancelButton.anchor = oVec2.zero
							btnBk = CCDrawNode()
							btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
							btnBk.position = oVec2(30,30)
							cancelButton:addChild(btnBk,-1)
							opMenu:addChild(cancelButton)
						end
						opMenu.removeHandlers = function(self)
							if isInput then
								textField.inputHandler = nil
								menu.enabled = false
							end
							opMenu.enabled = false
						end
					end)
			}))
	end

	box.hide = function(self)
		border:runAction(
			CCSequence(
			{
				CCSpawn(
				{
					oScale(0.3,0,0,oEase.InBack),
					oOpacity(0.3,0)
				}),
				CCCall(
					function()
						box.parent:removeChild(box)
					end)
			}))
	end

	box:show()
	oEditor.scene:addChild(box)
	return box
end

return oBox