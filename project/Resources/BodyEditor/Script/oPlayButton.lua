local class,property = unpack(require("class"))
local oButton = require("oButton")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCNode = require("CCNode")
local CCDrawNode = require("CCDrawNode")
local oScale = require("oScale")
local oEase = require("oEase")

local oPlayButton = class(oButton,
{
	__partial = function(self)
		self._playIcon = nil
		self._pauseIcon = nil
		self._isPlaying = false
		return oButton.__partial(self)
	end,

	__init = function(self,radius,x,y,tapped)
		local scale = oScale(0.5,1,1,oEase.OutBack)
		oButton.__init(self,"",0,radius,nil,x,y,
			function(item)
				self._isPlaying = not self._isPlaying
				if self._isPlaying then
					item._playIcon:stopAllActions()
					item._pauseIcon.scaleX = 0
					item._pauseIcon.scaleY = 0
					item._pauseIcon:runAction(scale)
				else
					item._pauseIcon:stopAllActions()
					item._playIcon.scaleX = 0
					item._playIcon.scaleY = 0
					item._playIcon:runAction(scale)
				end
				item._playIcon.visible = not item._playIcon.visible
				item._pauseIcon.visible = not item._pauseIcon.visible
				if tapped then
					tapped(item)
				end
			end)

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
	
	isPlaying = property(function(self) return self._isPlaying end),
})

return oPlayButton
