local require = using("BodyEditor.Script")
local Class = require("Class")
local oButton = require("oButton")
local oScale = require("oScale")
local oEase = require("oEase")
local CCNode = require("CCNode")
local oVec2 = require("oVec2")
local CCDrawNode = require("CCDrawNode")
local ccColor4 = require("ccColor4")
local property = require("property")

local oPlayButton = Class(oButton,
{
	__partial = function(self)
		self._playIcon = nil
		self._pauseIcon = nil
		self._isPlaying = false
		return oButton.__partial(self)
	end,

	__init = function(self,radius,x,y,tapped)
		oButton.__init(self,"",0,radius,nil,x,y,
			function(item)
				item.isPlaying = not item.isPlaying
				if tapped then
					tapped(item)
				end
			end)

		self._scale = oScale(0.5,1,1,oEase.OutBack)

		local node = CCNode()
		node.position = oVec2(25,25)
		node.cascadeColor = false
		self.face:addChild(node)

		local playIcon = CCDrawNode()
		playIcon:drawPolygon(
		{
			oVec2(-12,14),
			oVec2(12,0),
			oVec2(-12,-14),
		},ccColor4(0xff80ff00),0.5,ccColor4(0xff80ff00))
		playIcon.positionX = 2
		node:addChild(playIcon)
		self._playIcon = playIcon

		local pauseIcon = CCDrawNode()
		pauseIcon:drawPolygon(
		{
			oVec2(-9,12),
			oVec2(-3,12),
			oVec2(-3,-12),
			oVec2(-9,-12),
		},ccColor4(0xff80ff00),0.5,ccColor4(0xff80ff00))
		pauseIcon:drawPolygon(
		{
			oVec2(3,12),
			oVec2(9,12),
			oVec2(9,-12),
			oVec2(3,-12),
		},ccColor4(0xff80ff00),0.5,ccColor4(0xff80ff00))
		pauseIcon.visible = false
		node:addChild(pauseIcon)
		self._pauseIcon = pauseIcon
	end,

	isPlaying = property(
		function(self)
			return self._isPlaying
		end,
		function(self,value)
			if value == self._isPlaying then return end
			self._isPlaying = value
				if value then
					self._playIcon:stopAllActions()
					self._pauseIcon.scaleX = 0
					self._pauseIcon.scaleY = 0
					self._pauseIcon:runAction(self._scale)
				else
					self._pauseIcon:stopAllActions()
					self._playIcon.scaleX = 0
					self._playIcon.scaleY = 0
					self._playIcon:runAction(self._scale)
				end
				self._playIcon.visible = not self._playIcon.visible
				self._pauseIcon.visible = not self._pauseIcon.visible
		end),
})

return oPlayButton
