local require = using("BodyEditor.Script")
local Class = require("Class")
local CCMenuItem = require("CCMenuItem")
local oVec2 = require("oVec2")
local CCSize = require("CCSize")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local oTextField = require("oTextField")
local oLine = require("oLine")
local ccColor4 = require("ccColor4")
local property = require("property")
local tolua = require("tolua")

local oSettingItem = Class(
{
	__partial = function(self)
		self._label = nil -- CCLabelTTF
		self._border = nil -- oLine
		self._isInput = false -- boolean
		self._selected = false -- boolean
		self._toggled = nil -- function
		return CCMenuItem()
	end,

	-- self = CCMenuItem
	__init = function(self, name, width, height, x, y, isInput, valueFormat, toggled)
		--local halfW = width*0.5
		local halfH = height*0.5

		self._isInput = isInput
		self._valueFormat = valueFormat
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
				function()
					self.selected = false
					if self._toggled then
						self._toggled(self)
					end
					self:emit("TextChanged",label.text)
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

		self:slot("Tapped",function()
			self.selected = not self.selected
			if self._toggled then
				self._toggled(self)
			end
		end)
	end,

	-- string
	value = property(
		function(self)
			return self._label.text
		end,
		function(self,value)
			if value ~= nil then
				local valueFormat = self._valueFormat
				if type(value) == "boolean" then
					self._label.text = tostring(value)
				elseif tolua.type(value) == "oVec2" then
					self._label.text = string.format(valueFormat,value.x)..", "..string.format(valueFormat,value.y)
				elseif tolua.type(value) == "CCSize" then
					self._label.text = string.format(valueFormat,value.width)..", "..string.format(valueFormat,value.height)
				else
					self._label.text = string.format(valueFormat,value)
				end
				self._label.texture.antiAlias = false
			else
				self._label.text = ""
			end
		end),

	-- boolean
	highlighted = property(
		function(self)
			return self._border.visible
		end,
		function(self,value)
			self._border.visible = value
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
		end),

	-- boolean
	available = property(
		function(self)
			return self.enabled
		end,
		function(self, enabled)
			self.enabled = enabled
			if not enabled then
				self.selected = false
				if self._toggled then
					self._toggled(self)
				end
			end
		end),
})

return oSettingItem
