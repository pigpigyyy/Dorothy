local CCMenuItem = require("CCMenuItem")
local oVec2 = require("oVec2")
local CCSize = require("CCSize")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local oTextField = require("oTextField")
local oEvent = require("oEvent")
local oLine = require("oLine")
local ccColor4 = require("ccColor4")
local oEditor = require("oEditor")
local class,property = unpack(require("class"))

local oSettingItem = class(
{
	__partial = function(self)
		self._label = nil -- CCLabelTTF
		self._value = nil -- string
		self._border = nil -- oLine
		self._isInput = false -- boolean
		self._selected = false -- boolean
		self._toggled = nil -- function
		return CCMenuItem()
	end,

	__init = function(self, name, x, y, isInput, toggled)
		self._isInput = isInput
		self.anchor = oVec2(0,1)
		self.contentSize = CCSize(160,30)
		self.position = oVec2(x, y)
		self.enabled = false
		
		local label
		if isInput then
			label = oTextField(108,7,14,8,
				function()
					self.selected = false
				end)
		else
			label = CCLabelTTF("","Arial",14)
			label.position = oVec2(120,15)
		end
		label.color = ccColor3(0xffffff)
		self:addChild(label)
		self._label = label

		local border = oLine(
		{
			oVec2(0,0),
			oVec2(150,0),
			oVec2(150,30),
			oVec2(0,30),
			oVec2(0,0),
		},ccColor4(0xff00ffff))
		border.positionX = 5
		border.visible = false
		self:addChild(border)
		self._border = border
		
		self:registerTapHandler(
			function(eventType,self)
				if eventType == CCMenuItem.Tapped then
					if not self._isInput then
						self.selected = not self.selected
					end
				end
			end)
	end,

	-- string
	value = property(
		function(self)
			return self._value
		end,
		function(self,value)
			if value ~= nil and value ~= "" then
				if type(value) == "number" then
					self._label.text = string.format("%.2f",value)
				else
					self._label.text = tostring(value)
				end
				self._label.texture.antiAlias = false
				self._value = value
			else
				self._label.text = ""
				self._value = nil
			end
		end),

	-- boolean
	highlighted = property(
		function(self)
			return self._border.visible
		end,
		function(self,value)
			self._border.visible = value
			self.cascadeOpacity = not value
		end),

	-- boolean
	selected = property(
		function(self)
			return self._selected
		end,
		function(self,value)
			self._selected = value
			self.highlighted = value
			if self._toggled then
				self._toggled(self, value)
			end
		end),

	-- boolean
	available = property(
		function(self)
			return self.enabled
		end,
		function(self, enabled)
			self.enabled = enabled
			if not enabled then self.selected = false end
		end),
})

return oSettingItem
