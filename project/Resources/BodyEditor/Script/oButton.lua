local require = using("BodyEditor.Script")
local Class = require("Class")
local CCMenuItem = require("CCMenuItem")
local CCSize = require("CCSize")
local oVec2 = require("oVec2")
local CCNode = require("CCNode")
local CCDrawNode = require("CCDrawNode")
local ccColor4 = require("ccColor4")
local oLine = require("oLine")
local CCLabelTTF = require("CCLabelTTF")
local oScale = require("oScale")
local oEase = require("oEase")
local ccColor3 = require("ccColor3")
local property = require("property")

local oButton = Class(
{
	__partial = function(self)
		self._label = nil -- CCLabelTTF
		self.face = nil -- CCNode
		return CCMenuItem()
	end,
	
	__init = function(self,text,fontSize,width,height,x,y,tapped)
		self.contentSize = CCSize(width,height and height or width)
		self.anchor = oVec2(0.5,0.5)

		local node = CCNode()
		node.cascadeColor = false
		
		local drawNode = CCDrawNode()
		if not height then
			drawNode:drawDot(oVec2(width*0.5,width*0.5),width*0.5,ccColor4(0x88000000))
		else
			drawNode:drawPolygon(
			{
				oVec2(0,0),
				oVec2(width,0),
				oVec2(width,height),
				oVec2(0,height)
			},ccColor4(0x88000000))
		end
		node:addChild(drawNode)

		local face = CCNode()
		face.anchor = oVec2(0.5,0.5)
		face.contentSize = CCSize(width,height and height or width)
		face.position = oVec2(width*0.5,height and height*0.5 or width*0.5)
		face:addChild(node)
		if not height then
			local vs = {}
			local num = 20
			for i = 0, num do
				local angle = 2*math.pi*i/num
				table.insert(vs,oVec2(width*0.5*math.cos(angle),width*0.5*math.sin(angle))+oVec2(width*0.5,width*0.5))
			end
			face:addChild(oLine(vs,ccColor4()))
		else
			face:addChild(oLine(
			{
				oVec2.zero,
				oVec2(width,0),
				oVec2(width,height),
				oVec2(0,height),
				oVec2.zero
			},ccColor4()))
		end
		self:addChild(face)
		self.face = face
	
		if text ~= "" then
			local label = CCLabelTTF(text,"Arial",fontSize)
			label.position = oVec2(width*0.5, height and height*0.5 or width*0.5)
			label.texture.antiAlias = false
			face:addChild(label)
			self._label = label
		end

		local scale = oScale(0.3,1.0,1.0,oEase.OutBack)
		self:slot("TapBegan",function()
			if not scale.done then
				face:stopAction(scale)
			end
			face.scaleX = 0.3
			face.scaleY = 0.3
			face:runAction(scale)
		end)
		self:slot("Tapped",function()
			if tapped then
				tapped(self)
			end
		end)

		self.face = face
		self.tapped = tapped
		self.position = oVec2(x,y)
		self.color = ccColor3(0x00ffff)
	end,

	-- string
	text = property(
		function(self)
			return self._label.text
		end,
		function(self,value)
			self._label.text = value
			self._label.texture.antiAlias = false
		end),
})

return oButton
