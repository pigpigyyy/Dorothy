local oButton = require("oButton")
local oTextField = require("oTextField")
local class = unpack(require("class"))
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

local oBox = class({
	__partial = function(self,_,okHandler,isInput)
		self._isInput = isInput
		self._okHandler = okHandler
		self._border = nil
		self._menu = nil
		self._textField = nil
		return CCNode()
	end,

	__init = function(self,text,_,isInput)
		local w = CCDirector.winSize.width*0.5
		local h = CCDirector.winSize.height*0.5
		local size = isInput and 125 or 90

		local mask = CCLayer()
		mask.anchor = oVec2.zero
		mask.touchPriority = CCMenu.DefaultHandlerPriority-4
		mask.swallowTouches = true
		mask.touchEnabled = true
		mask.touchHandler = function() return true end
		self:addChild(mask)

		local border = CCDrawNode()
		border:drawPolygon(
		{
			oVec2(-size,-size),
			oVec2(size,-size),
			oVec2(size,size),
			oVec2(-size,size)
		},ccColor4(0xe5100000),0.5,ccColor4(0x88ffafaf))
		border.position = oVec2(w,h)
		self:addChild(border)
		self._border = border

		local title = CCLabelTTF(text,"Arial",24)
		title.texture.antiAlias = false
		title.position = oVec2(0,isInput and 76 or 36)
		title.color = ccColor3(0x00ffff)
		border:addChild(title)

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

			local menu = CCMenu()
			menu.swallowTouches = true
			menu.contentSize = CCSize(120,50)
			menu.touchPriority = CCMenu.DefaultHandlerPriority-5
			border:addChild(menu)
			self._menu = menu

			local textField = oTextField(120,18,17,10,
				function(item)
					frame.opacity = 0.3
					item.opacity = 0.3
					local text = item.text
					if isInput and text ~= "" then
						item:detachWithIME()
						if self._okHandler then
							self._okHandler(item.text)
						end
						self:hide()
					end
				end)
			textField.position = oVec2(0,-9)
			textField:attachWithIME()
			border:addChild(textField)
			self._textField = textField

			local menuItem = CCMenuItem()
			menuItem.contentSize = CCSize(120,50)
			menuItem.anchor = oVec2.zero
			menuItem.tapHandler = function(eventType)
				if eventType == CCMenuItem.Tapped then
					textField:attachWithIME()
					textField.opacity = 1
					frame.opacity = 1
				end
			end
			menu:addChild(menuItem)
		end

		self.nodeHandler = function(eventType)
			if eventType == CCNode.Entered then
				self:show()
			end
		end
	end,

	show = function(self)
		local w = CCDirector.winSize.width*0.5
		local h = CCDirector.winSize.height*0.5
		self._border.scaleX = 0
		self._border.scaleY = 0
		self._border.opacity = 0
		self._border:runAction(
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
						opMenu.position = oVec2(w,h-(self._isInput and 76 or 36))
						self:addChild(opMenu)

						local okButton = oButton("OK",17,60,false,
							self._okHandler and 0 or 35,0,
							function()
								if self._isInput then
									if self._textField.text == "" then return end
									local handler = self._okHandler
									self._okHandler = nil
									self._textField:detachWithIME()
									if handler then
										handler(self._textField.text)
									end
								else
									if self._okHandler then
										self._okHandler()
									end
								end
								opMenu:removeHandlers()
								self:hide()
							end)
						okButton.anchor = oVec2.zero
						local btnBk = CCDrawNode()
						btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
						btnBk.position = oVec2(30,30)
						okButton:addChild(btnBk,-1)
						opMenu:addChild(okButton)
						
						local cancelButton
						if self._okHandler then
							cancelButton = oButton("Cancel",17,60,false,
								70,0,
								function()
									if self._isInput then
										self._okHandler = nil
										self._textField:detachWithIME()
									elseif self.cancelHandler then
										self.cancelHandler()
									end
									opMenu:removeHandlers()
									self:hide()
								end)
							cancelButton.anchor = oVec2.zero
							btnBk = CCDrawNode()
							btnBk:drawDot(oVec2.zero,30,ccColor4(0x22ffffff))
							btnBk.position = oVec2(30,30)
							cancelButton:addChild(btnBk,-1)
							opMenu:addChild(cancelButton)
						end
						opMenu.removeHandlers = function(self)
							okButton.tapHandler = nil
							if cancelButton then cancelButton.tapHandler = nil end
							if self._isInput then
								self._textField.inputHandler = nil
								self._menu.enabled = false
							end
							opMenu.enabled = false
						end
					end)
			}))
	end,

	hide = function(self)
		self._border:runAction(
			CCSequence(
			{
				CCSpawn(
				{
					oScale(0.3,0,0,oEase.InBack),
					oOpacity(0.3,0)
				}),
				CCCall(
					function()
						self.parent:removeChild(self)
					end)
			}))
	end,
})

return oBox