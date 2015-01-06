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

	-- self = CCMenuItem
	__init = function(self,name,width,height, x, y, isInput, toggled)
		local halfW = width*0.5
		local halfH = height*0.5
		
		self._isInput = isInput
		self._toggled = toggled
		self.anchor = oVec2(0,1)
		self.contentSize = CCSize(width,height)
		self.position = oVec2(x, y)
		
		local label = CCLabelTTF(name,"Arial",14)
		label.color = ccColor3(0xffffff)
		label.position = oVec2(10+label.contentSize.width*0.5,halfH)
		label.texture.antiAlias = false
		self:addChild(label)

		local nextCenterX = label.position.x + label.contentSize.width*0.5
		nextCenterX = (width-10-nextCenterX)*0.5+nextCenterX
		if isInput then
			local fontSize = 14
			local limit = 8
			local x = nextCenterX
			local y = halfH-fontSize*0.5-2
			label = oTextField(x,y,fontSize,limit,
				function(textField)
					self._value = textField.text
					self.selected = false
				end)
		else
			label = CCLabelTTF("","Arial",14)
			label.position = oVec2(nextCenterX,halfH)
		end
		label.color = ccColor3(0xffffff)
		self:addChild(label)
		self._label = label

		local border = oLine(
		{
			oVec2(0,0),
			oVec2(width-10,0),
			oVec2(width-10,height),
			oVec2(0,height),
			oVec2(0,0),
		},ccColor4(0xff00ffff))
		border.positionX = 5
		border.visible = false
		self:addChild(border)
		self._border = border
		
		self:registerTapHandler(function(eventType,item)
			if eventType == CCMenuItem.Tapped then
				item.selected = not item.selected
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
			if self._selected == value then return end
			self._selected = value
			self.highlighted = value
			if self._isInput then
				if value then
					self._label:attachWithIME()
				else
					self._label:detachWithIME()
				end
			end
			if self._toggled then
				self._toggled(self)
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
