local CCDirector = require("CCDirector")
local CCLayer = require("CCLayer")
local oVec2 = require("oVec2")
local CCSize = require("CCSize")
local CCDrawNode = require("CCDrawNode")
local ccColor4 = require("ccColor4")
local emit = require("emit")
local CCLabelTTF = require("CCLabelTTF")
local CCNode = require("CCNode")
local CCClipNode = require("CCClipNode")
local oOpacity = require("oOpacity")
local oEase = require("oEase")
local CCRect = require("CCRect")
local oEditor = require("oEditor").oEditor
local oSd = require("oEditor").oSd
local oAd = require("oEditor").oAd
local oKd = require("oEditor").oKd

local function oControlBar()
    local winSize = CCDirector.winSize
	local barDragPos = 50
	
	-- controlBar
	local controlBar = CCLayer()
	controlBar.anchor = oVec2.zero
	controlBar.contentSize = CCSize(winSize.width,60)
	controlBar.opacity = 0.4
	controlBar.touchEnabled = true
	controlBar.visible = false

	-- border
	local border = CCDrawNode()
	border:drawPolygon(
	{
		oVec2(0,0),
		oVec2(winSize.width-20,0),
		oVec2(winSize.width-20,50),
		oVec2(0,50)
	},ccColor4(0x88000000),0.5,ccColor4(0xffffffff))
	border.position = oVec2(10,10)

	-- bar
	local barLength = winSize.width-60
	local barIterval = barLength/60
	local bar = CCDrawNode()
	bar:drawPolygon(
	{
		oVec2(0,0),
		oVec2(barLength,0),
		oVec2(barLength,6),
		oVec2(0,6)
	},ccColor4(0xffffffff))
	bar.setPos = function(self,pos)
		self._pos = pos
		pos = math.floor(pos+0.5)
		self.scaleX = pos/60.0
		emit("ControlBarPos",pos)
	end
	bar.getPos = function(self)
		return self._pos
	end
	bar.anchor = oVec2.zero
	bar.contentSize = CCSize(barLength,5)
	bar.position = oVec2(30,20)
	bar:setPos(0)

	-- ruler
	local ruler = CCDrawNode()
	ruler._size = 0
	ruler.setSize = function(self,size)
		local delta = barIterval
		if size < self._size then
			self:removeAllChildrenWithCleanup()
			self:clear()
			self:drawSegment(oVec2.zero,oVec2(delta*size,0),0.5,ccColor4(0xffffffff))
		else
			self:drawSegment(oVec2(delta*self._size,0),oVec2(delta*size),0.5,ccColor4(0xffffffff))
		end
		local lastSize = self._size
		self._size = size
		if self._isUpdating then
			return
		end
		self._isUpdating = true
		local i = lastSize
		-- update ruler interval by step, not all at once
		self:schedule(function()
			if i <= self._size then
				local posX = delta*i
				if i == 0 or (i%10 == 0 and i ~= lastSize) then
					local label = CCLabelTTF(tostring(i),"Arial",10)--CCLabelAtlas(tostring(i),"rulerNum.png",7,11,string.byte("0"))
					label.texture.antiAlias = false
					label.position = oVec2(posX, 14)
					self:addChild(label)
					self:drawSegment(
						oVec2(posX,0),
						oVec2(posX,6),
						0.5,ccColor4(0xffffffff))
				elseif i%10 ~= 0 then					
					self:drawSegment(
						oVec2(posX,0),
						oVec2(posX,3),
						0.5,ccColor4(0xffffffff))
				end
				i = i + 1
			else
				self:unschedule()
				self._isUpdating = false
			end
		end)
	end
	ruler.getSize = function(self)
		return self._size
	end
	ruler:setSize(60)
	ruler.position = oVec2(30,35)

	local cursorNode = CCDrawNode()
	cursorNode.position = oVec2(30,35)
	controlBar.addCursor = function(self,pos)
		local x = math.floor(pos+0.5)*barIterval
		cursorNode:drawPolygon(
		{
			oVec2(x-1,-18),
			oVec2(x+1,-18),
			oVec2(x+1,6),
			oVec2(x-1,6)
		},ccColor4(0xff00a2d8))
	end
	controlBar.clearCursors = function(self)
		cursorNode:clear()
	end
	controlBar.updateCursors = function(self)
		local animationDef = oEditor.animationData
		if animationDef then
			if animationDef[oAd.type] == 1 then
				local d = 0
				oEditor.controlBar:clearCursors()
				for i = oAd.frameDefs, #animationDef do
					d = d + animationDef[i][oKd.duration]
					oEditor.controlBar:addCursor(d*60.0)
				end
			elseif animationDef[oAd.type] == 2 then
				--TODO Frame animation
			end
		elseif oEditor.spriteData and oEditor.spriteData[oSd.parent] then
			oEditor.controlBar:clearCursors()
			oEditor.settingPanel:updateValues(nil)
		end
	end

	-- controlNode
	local controlNode = CCNode()
	controlNode:addChild(ruler)
	controlNode:addChild(bar)
	controlNode:addChild(cursorNode)
	controlNode.setOffset = function(self,value)
		self.positionX = value
		local displaySize = math.floor((barLength-value)/barIterval)
		if displaySize >= ruler:getSize() then
			ruler:setSize(ruler:getSize()+60)
		end
	end
	
	-- stencil
	local stencil = CCDrawNode()
	stencil:drawPolygon(
	{
		oVec2(0,0),
		oVec2(winSize.width-20,0),
		oVec2(winSize.width-20,50),
		oVec2(0,50)
	},ccColor4(0xffffffff))
	stencil.position = oVec2(10,10)
	local clipNode = CCClipNode(stencil)
	clipNode:addChild(controlNode)
	
	-- build controlBar
	controlBar:addChild(border)
	controlBar:addChild(clipNode)
	local fade = oOpacity(0.5,0.4,oEase.InExpo)
	local lastPos = 0
	local offset = 0
	local moveBar = false
	local locLength = 0
	controlBar:gslot("PlayState",
		function(state)
			if state == "Play" then
				controlBar.touchEnabled = false
				controlBar:hide()
				if moveBar then
					lastPos = locLength
					moveBar = false
				end
			elseif state == "Pause" or state == "Stop" then
				controlBar.touchEnabled = true
			end
		end)
	
	controlBar.show = function(self)
		if not fade.done then
			self:stopAction(fade)
		end
		self.opacity = 1.0
	end
	controlBar.hide = function(self)
		if not fade.done then
			self:stopAction(fade)
		end
		self:runAction(fade)
	end

	local jumpPos = false
	controlBar.swallowTouches = true
	
	local function isTouchValid(touch)
		if not controlBar.visible or touch.id ~= 0 then
			return false
		end
		if not oEditor.viewArea:getModel() then
			return false
		end
		local loc = controlBar:convertToNodeSpace(touch.location)
		locLength = loc.x-10-barIterval
		if locLength < 0 then locLength = 0 end
		if locLength > barLength then locLength = barLength end
		return true
	end
	
	controlBar:slots("TouchBegan",function(touch)
		if not isTouchValid(touch) then return false end
		local loc = controlBar:convertToNodeSpace(touch.location)
		if not CCRect(oVec2.zero, controlBar.contentSize):containsPoint(loc) then
			return false
		end
		controlBar:show()
		--cclog("Start %d,%d",lastPos,offset)
		if lastPos-barDragPos <= locLength and locLength <= lastPos+barDragPos then
			moveBar = true
		end
		return true
	end)

	local function touchEnded(touch)
		if not isTouchValid(touch) then return end
		controlBar:hide()
		if moveBar then
			lastPos = locLength
			moveBar = false
		end
		if jumpPos then
			jumpPos = false
			oEditor.settingPanel:clearSelection()
			local model = oEditor.viewArea:getModel()
			if model then
				local pos = (locLength-offset)*60/barLength
				if pos < 0 then pos = 0 end
				if not model.doing then
					model:play(oEditor.animation)
					model:pause()
				end
				model.time = (math.floor(pos+0.5)/60.0)/model.duration
				controlBar:setPos(pos)
			end
		else
			jumpPos = true
			local interval = 0
			controlBar:schedule(function(deltaTime)
				interval = interval + deltaTime
				if interval >= 0.5 then
					jumpPos = false
					controlBar:unschedule()
				end
			end)
		end
		--cclog("End %d,%d",lastPos,offset)
	end
	controlBar:slots("TouchEnded",touchEnded)
	controlBar:slots("TouchCancelled",touchEnded)

	controlBar:slots("TouchMoved",function(touch)
		if not isTouchValid(touch) then return end
		if moveBar then
			local model = oEditor.viewArea:getModel()
			if model then
				local pos = (locLength-offset)*60/barLength
				if not model.doing then
					model:play(oEditor.animation)
					model:pause()
				end
				model.time = (math.floor(pos+0.5)/60.0)/model.duration
				bar:setPos(pos)
			end
		else
			local deltaX = touch.delta.x * 2
			offset = offset + deltaX
			if offset > 0 then
				offset = 0
			else
				lastPos = lastPos + deltaX
			end
			controlNode:setOffset(offset)
		end
	end)

	controlBar.setPos = function(self,pos)
		local deltaX = barIterval * (pos - bar:getPos())
		lastPos = lastPos + deltaX
		if lastPos > barLength then
			offset = offset + barLength - lastPos
			lastPos = barLength
			controlNode:setOffset(offset)
		elseif lastPos < 0 then
			offset = 0
			lastPos = 0
			controlNode:setOffset(0)
		end
		bar:setPos(pos)
	end
	controlBar.getPos = function(self)
		return bar:getPos()
	end
	
	-- time: model animation`s played time
	controlBar.setTime = function(self,time)
		local pos = time*60
		controlBar:setPos(pos)
	end
	
	controlBar.getTime = function(self)
		return bar:getPos()/60
	end

	return controlBar
end

return oControlBar