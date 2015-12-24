local require = using("BodyEditor.Script")
local CCLayer = require("CCLayer")
local oVec2 = require("oVec2")
local CCDrawNode = require("CCDrawNode")
local ccColor4 = require("ccColor4")
local oEditor = require("oEditor")
local once = require("once")
local wait = require("wait")
local seconds = require("seconds")
local oLine = require("oLine")

local function oPointControl()
	local control = CCLayer()
	control.visible = false
	
	local circle = CCDrawNode()
	circle:drawDot(oVec2.zero,20,ccColor4(0xff00ffff))
	circle:addChild(oLine({oVec2(-10,0),oVec2(10,0)},ccColor4()))
	circle:addChild(oLine({oVec2(0,10),oVec2(0,-10)},ccColor4()))
	circle.opacity = 0.5
	control:addChild(circle)

	local target = nil
	local targetPos = oVec2.zero
	local totalDelta = oVec2.zero
	local posChanged = nil
	local jump = false
	local jumpNow = false
	control.touchPriority = oEditor.touchPriorityEditControl
	control.swallowTouches = true
	control:slot("TouchBegan",function(touch)
		if not jump then
			jump = true
			jumpNow = true
			control:schedule(once(function()
				wait(seconds(0.4))
				jump = false
				jumpNow = false
			end))
		elseif jumpNow then
			jump = false
			control:unschedule()
			targetPos = target:convertToNodeSpace(touch.location)
			if oEditor.isFixed then
				targetPos = oEditor:round(targetPos)
			end
			circle.position = targetPos
			if posChanged then
				posChanged(targetPos)
			end
		end
		return true
	end)
	control:slot("TouchMoved",function(touch)
		local delta = target:convertToNodeSpace(touch.location) - target:convertToNodeSpace(touch.preLocation)
		if oEditor.isFixed then
			totalDelta = totalDelta + delta
			if totalDelta.x > 1 or totalDelta.x < -1 then
				local posX = targetPos.x+totalDelta.x
				targetPos.x = oEditor:round(posX)
				totalDelta.x = 0
			end
			if totalDelta.y > 1 or totalDelta.y < -1 then
				local posY = targetPos.y+totalDelta.y
				targetPos.y = oEditor:round(posY)
				totalDelta.y = 0
			end
		else
			targetPos = targetPos + delta
		end
		circle.position = targetPos
		if posChanged then
			posChanged(targetPos)
		end
	end)

	control.show = function(self,pos,callback,controlTarget)
		control.visible = true
		control.touchEnabled = true
		target = nil
		if controlTarget then
			target = controlTarget
		else
			target = oEditor.world
		end
		circle.transformTarget = target
		circle.position = pos
		targetPos = pos
		totalDelta = oVec2.zero
		posChanged = callback
		jump = false
		jumpNow = false
	end
	control.hide = function(self)
		if not control.visible then return end
		control.visible = false
		control.touchEnabled = false
		posChanged = nil
		target = nil
	end
	return control
end

return oPointControl