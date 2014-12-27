local class,property = unpack(require("class"))
local CCNode = require("CCNode")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor3 = require("ccColor3")
local ccColor4 = require("ccColor4")
local CCMenuItem = require("CCMenuItem")
local CCSize = require("CCSize")
local oLine = require("oLine")
local oScale = require("oScale")
local oEase = require("oEase")
local oOpacity = require("oOpacity")
local CCLabelTTF = require("CCLabelTTF")

local oViewItem = class({
	__partial = function(self)
		self._selected = false -- boolean
		self._node = nil -- CCNode to control cascading
		self._border = nil -- oLine
		self._borderBold = nil -- CCDrawNode
		self._tapped = nil -- function
		self._scale = nil -- oScale
		self._fade = nil -- oOpacity
		self._nameLabel = nil -- CCLabelTTF
		return CCMenuItem()
	end,

	__init = function(self,typename,name,x,y,tapped)
		local isSub = typename:sub(1,3) == "Sub"
		local width = isSub and 130 or 160
		local height = 40
		local halfW = width*0.5
		local halfH = height*0.5
		
		self._tapped = tapped
		self.contentSize = CCSize(width,height)
		self.position = oVec2(x+(isSub and 15 or 0),y)
		self:registerTapHandler(function(eventType) self:tapped(eventType) end)

		local node = CCNode()
		node.position = oVec2(halfW,halfH)
		self:addChild(node)
		self._node = node

		local typeLabel = CCNode()
		typeLabel.cascadeColor = false
		typeLabel.scaleX = 0.6
		typeLabel.scaleY = 0.6
		typeLabel.positionX = -halfW+20
		node:addChild(typeLabel)

		if typename == "Rectangle" or typename == "SubRectangle" then
			typeLabel:addChild(oLine(
			{
				oVec2(-15,15),
				oVec2(15,15),
				oVec2(15,-15),
				oVec2(-15,-15),
				oVec2(-15,15),
			},ccColor4(0xffff0080)))
		elseif typename == "Circle" or typename == "SubCircle" then
			local vs = {}
			local num = 20
			for i = 0, num do
				local angle = 2*math.pi*i/num
				table.insert(vs,oVec2(18*math.cos(angle),18*math.sin(angle)))
			end
			typeLabel:addChild(oLine(vs,ccColor4(0xffff0080)))
		elseif typename == "Polygon" or typename == "SubPolygon" then
			typeLabel:addChild(oLine(
			{
				oVec2(0,18),
				oVec2(18,-18),
				oVec2(-18,-18),
				oVec2(0,18),
			},ccColor4(0xffff0080)))
		elseif typename == "Chain" or typename == "SubChain" then
			typeLabel:addChild(oLine(
			{
				oVec2(-15,15),
				oVec2(0,15),
				oVec2(0,-15),
				oVec2(15,-15),
			},ccColor4(0xffff0080)))
		elseif typename == "Loop" or typename == "SubLoop" then
			typeLabel:addChild(oLine(
			{
				oVec2(-16,0),
				oVec2(-8,16),
				oVec2(4,8),
				oVec2(8,16),
				oVec2(16,0),
				oVec2(8,-16),
				oVec2(-8,-16),
				oVec2(-16,0),
			},ccColor4(0xffff0080)))
		else
			typeLabel.scaleX = 0.7
			typeLabel.scaleY = 0.7
			typeLabel:addChild(oLine(
			{
				oVec2(-13,13),
				oVec2(13,-13),
			},ccColor4(0xffff0080)))
			typeLabel:addChild(oLine(
			{
				oVec2(-16,16),
				oVec2(-10,16),
				oVec2(-10,10),
				oVec2(-16,10),
				oVec2(-16,16),
			},ccColor4(0xff80ff00)))
			typeLabel:addChild(oLine(
			{
				oVec2(16,-16),
				oVec2(10,-16),
				oVec2(10,-10),
				oVec2(16,-10),
				oVec2(16,-16),
			},ccColor4(0xff80ff00)))
		end

		if isSub then
			self:addChild(oLine(
			{
				oVec2(-15,height+(name == 1 and 10 or (10+halfH))),
				oVec2(-15,halfH),
				oVec2(0,halfH),
			},ccColor4()))
		else
			local nameLabel = CCLabelTTF(name,"Arial",14)
			nameLabel.positionX = 20
			nameLabel.texture.antiAlias = false
			node:addChild(nameLabel)
			self._nameLabel = nameLabel
		end

		local border = oLine(
		{
			oVec2(-halfW,halfH),
			oVec2(halfW,halfH),
			oVec2(halfW,-halfH),
			oVec2(-halfW,-halfH),
			oVec2(-halfW,halfH),
		},ccColor4())
		node:addChild(border)
		self._border = border

		local borderBold = CCDrawNode()
		borderBold:drawPolygon(
		{
			oVec2(-halfW,halfH),
			oVec2(halfW,halfH),
			oVec2(halfW,-halfH),
			oVec2(-halfW,-halfH)
		},ccColor4(0),1,ccColor4())
		borderBold.opacity = 0
		node:addChild(borderBold)
		self._borderBold = borderBold

		self._scale = oScale(0.25,1,1,oEase.OutBack)
		self._fade = oOpacity(0.5, 0)
	end,
	
	tapped = function(self,eventType)
		if eventType ~= CCMenuItem.Tapped then return end
		self.selected = not self.selected
		if self._tapped then
			self._tapped(self)
		end
	end,
	
	selected = property(
		function(self)
			return self._selected
		end,
		function(self,value)
			if self._selected == value then return end
			self._selected = value
			self._border.visible = not value
			if value then
				self._node.color = ccColor3(0x00ffff)
				self._node.cascadeOpacity = false
				self._borderBold:stopAllActions()
				self._borderBold.opacity = 1
				self._borderBold.scaleX = 0.8
				self._borderBold.scaleY = 0.8
				self._borderBold:runAction(self._scale)
			else
				self._node.color = ccColor3(0xffffff)
				self._node.cascadeOpacity = true
				self._borderBold:runAction(self._fade)
			end
		end),

	name = property(
		function(self)
			if self._nameLabel then
				return self._nameLabel.text
			else
				return self._name
			end
		end,
		function(self,value)
			if self._nameLabel then
				self._nameLabel.text = value
				self._nameLabel.texture.antiAlias = false
			else
				self._name = value
			end
		end),
})

return oViewItem