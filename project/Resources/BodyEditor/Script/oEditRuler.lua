local CCDirector = require("CCDirector")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local ccColor4 = require("ccColor4")
local CCClipNode = require("CCClipNode")
local CCLayerColor = require("CCLayerColor")
local oEditor = require("oEditor")
local oLine = require("oLine")
local CCNode = require("CCNode")
local CCLabelTTF = require("CCLabelTTF")
local oScale = require("oScale")
local oEase = require("oEase")
local CCSize = require("CCSize")
local once = require("once")
local CCTouch = require("CCTouch")
local CCSpawn = require("CCSpawn")
local oOpacity = require("oOpacity")
local CCSequence = require("CCSequence")
local CCCall = require("CCCall")

local function oEditRuler()
	local winSize = CCDirector.winSize
	local center = oVec2(winSize.width*0.5,winSize.height*0.5)
	local width = 100
	local height = 460*winSize.height/600
	local halfW = width*0.5
	local halfH = height*0.5

	local ruler = CCLayerColor(ccColor4(0),width,height)
	ruler.visible = false
	ruler.opacity = 0.8
	ruler.cascadeOpacity = true
	ruler.position = oEditor.origin+center
	
	local border = oLine(
	{
		oVec2(-halfW,halfH),
		oVec2(halfW,halfH),
		oVec2(halfW,-halfH),
		oVec2(-halfW,-halfH),
		oVec2(-halfW,halfH),
	},ccColor4())
	border.position = oVec2(halfW,halfH)
	ruler:addChild(border)

	local stencil = CCDrawNode()
	stencil:drawPolygon(
	{
		oVec2(-halfW,halfH-1),
		oVec2(halfW,halfH-1),
		oVec2(halfW,-halfH+1),
		oVec2(-halfW,-halfH+1),
	},ccColor4(0))

	local clipNode = CCClipNode(stencil)
	clipNode.position = oVec2(halfW,halfH)
	ruler:addChild(clipNode)
	
	local content = CCNode()
	clipNode:addChild(content)
	
	local intervalNode = oLine()
	intervalNode.contentSize = CCSize(width,height)

	local interval = 10
	local top = math.ceil(halfH/interval)
	local up = 0
	local down = 1
	local bottom = math.ceil(halfH/interval)
	local vs = {}
	local indent = 100
	local labels = {}
	ruler.labels = labels
	content:schedule(once(function()
		repeat
			if up < top or down < bottom then
				if up < top then
					local target = top
					for i = up,target do
						local posY = i*interval
						table.insert(vs,1,oVec2(-halfW,posY))
						table.insert(vs,1,oVec2(-halfW+(i%10 == 0 and 16 or 8),posY))
						table.insert(vs,1,oVec2(-halfW,posY))
						if i%10 == 0 then
							local label = CCLabelTTF(tostring(i*indent/10),"Arial",12)
							label.texture.antiAlias = false
							label.scaleX = 1/intervalNode.scaleY
							label.angle = -90
							label.position = oVec2(-halfW+28,posY)
							intervalNode:addChild(label)
							labels[i/10] = label
							coroutine.yield()
						end
					end
					up = target+1
				end
				if down < bottom then
					local target = bottom
					for i = down,target do
						local posY = -i*interval
						table.insert(vs,oVec2(-halfW,posY))
						table.insert(vs,oVec2(-halfW+(i%10 == 0 and 16 or 8),posY))
						table.insert(vs,oVec2(-halfW,posY))
						if i%10 == 0 then
							local label = CCLabelTTF(tostring(-i*indent/10),"Arial",12)
							label.texture.antiAlias = false
							label.scaleX = 1/intervalNode.scaleY
							label.angle = -90
							label.position = oVec2(-halfW+28,posY)
							intervalNode:addChild(label)
							labels[-i/10] = label
							coroutine.yield()
						end
					end
					down = target+1
				end
				coroutine.yield()
				intervalNode:set(vs)
			end
			coroutine.yield()
		until false
	end))
	content:addChild(intervalNode)
	
	local arrow = CCNode()
	arrow.cascadeOpacity = false
	arrow:addChild(oLine({oVec2(-halfW,0),oVec2(halfW,0)},ccColor4(0xff00ffff)))
	arrow.position = oVec2(halfW,halfH)
	ruler:addChild(arrow)

	local function updateIntervalTextScale(scale)
		intervalNode:eachChild(function(child)
			child.scaleX = scale
		end)
	end
	ruler:gslot("viewArea.scale",function(scale)
		if scale > 5 then scale = 5 end
		intervalNode.scaleY = scale
		-- unscale interval text --
		updateIntervalTextScale(1/scale)
		local posY = intervalNode.anchor.y*height
		if posY >= 0 then
			local newTop = math.ceil((posY+halfH/scale)/interval)
			if top < newTop then top = newTop end
		else
			local newBottom = math.ceil((-posY+halfH/scale)/interval)
			if bottom < newBottom then bottom = newBottom end
		end
	end)
	ruler:gslot("viewArea.toScale",function(scale)
		intervalNode:runAction(oScale(0.5,1,scale,oEase.OutQuad))
		-- manually update and unscale interval text --
		local time = 0
		intervalNode:schedule(function(deltaTime)
			updateIntervalTextScale(1/intervalNode.scaleY)
			time = time + deltaTime
			if math.min(time/0.5,1) == 1 then
				intervalNode:unschedule()
			end
		end)
		local posY = intervalNode.anchor.y*height
		local newTop = math.ceil((posY+halfH/scale)/interval)
		if top < newTop then top = newTop end
		local newBottom = math.ceil((-posY+halfH/scale)/interval)
		if bottom < newBottom then bottom = newBottom end
	end)
	
	ruler.setIndent = function(self,ind)
		indent = ind
		for i,label in pairs(labels) do
			label.text = tostring(ind*i)
			label.texture.antiAlias = false
		end
	end

	local _value = 0
	local _max = 0
	local _min = 0
	ruler.setValue = function(self,v)
		if v == _value then return end
		_value = v
		if self.changed then
			if _min < _max then
				local val = _value
				if val < _min then val = _min end
				if val > _max then val = _max end
				self.changed(oEditor.isFixed and math.floor(val/(indent/10)+0.5)*(indent/10) or val)
			else
				self.changed(oEditor.isFixed and math.floor(_value/(indent/10)+0.5)*(indent/10) or _value)
			end
		end
		local posY = (v*10*interval/indent)
		intervalNode.anchor = oVec2(0,posY/height)
		local scale = intervalNode.scaleY
		if posY >= 0 then
			local newTop = math.ceil((posY+halfH/scale)/interval)
			if top < newTop then top = newTop end
		else
			local newBottom = math.ceil((-posY+halfH/scale)/interval)
			if bottom < newBottom then bottom = newBottom end
		end
	end
	ruler.getValue = function(self)
		return _value--intervalNode.anchor.y*height*indent/(10*interval)
	end

	ruler.setLimit = function(self,min,max)
		_max = max
		_min = min
	end

	local time = 0
	local startPos = 0
	local function updateReset(deltaTime)
		if _min >= _max then return end

		local scale = intervalNode.scaleY

		time = time + deltaTime
		local t = time/1
		if scale < 1 then
			t = t/0.1
		end
		if t > 1.0 then t = 1.0 end

		local yVal = nil
		if startPos < _min then
			yVal = oEase:func(scale < 1 and oEase.Linear or oEase.OutElastic,t,startPos,_min-startPos)
		elseif startPos > _max then
			yVal = oEase:func(scale < 1 and oEase.Linear or oEase.OutElastic,t,startPos,_max-startPos)
		end
		ruler:setValue(((yVal and yVal or 0)-_value)/scale+_value)

		if t == 1.0 then
			ruler:unschedule()
		end
	end

	local function isReseting()
		if _min < _max and (_value > _max or _value < _min) then
			return true
		end
		return false
	end

	local function startReset()
		startPos = _value
		time = 0
		ruler:schedule(updateReset)
	end

	local _v = 0
	local _s = 0
	local function updateSpeed(deltaTime)
		if _s == 0 then
			return
		end
		_v = _s / deltaTime
		_s = 0
	end

	local function updatePos(deltaTime)
		local val = winSize.height*2
		local a = _v > 0 and -val or val

		local yR = _v > 0

		_v = _v + a*deltaTime
		if _v < 0 == yR then _v = 0;a = 0 end

		local ds = _v * deltaTime + a*(0.5*deltaTime*deltaTime)

		local newValue = _value-ds*indent/(interval*10)
		ruler:setValue((newValue-_value)/intervalNode.scaleY+_value)

		if _v == 0 or (_min < _max and (_value < _min or _value > _max)) then
			if isReseting() then
				startReset()
			else
				ruler:unschedule()
			end
		end
	end

	ruler.touchPriority = oEditor.touchPriorityEditControl
	ruler.swallowTouches = true
	ruler.touchHandler = function(eventType,touch)
		--touch=CCTouch
		if eventType == CCTouch.Began then
			_s = 0
			_v = 0
			ruler:schedule(updateSpeed)
		elseif eventType == CCTouch.Moved then
			local v = _value-touch.delta.y*indent/(interval*10)
			local padding = 0.5*indent
			if _max > _min then
				local d = 1
				if v > _max then
					d = (v - _max)*3/padding
				elseif v < _min then
					d = (_min - v)*3/padding
				end
				v = _value+(v - _value)/(d < 1 and 1 or d*d)
			end
			ruler:setValue((v-_value)/intervalNode.scaleY+_value)
			_s = _s + touch.delta.y
		elseif eventType == CCTouch.Ended or eventType == CCTouch.Cancelled then
			if isReseting() then
				startReset()
			elseif _v ~= 0 then
				ruler:schedule(updatePos)
			end
		end
		return true
	end

	ruler.show = function(self,default,min,max,indent,callback)
		self:setIndent(indent)
		self:setLimit(min,max)
		self:setValue(default)
		self.changed = callback
		self.visible = true
		self.scaleX = 0
		self.scaleY = 0
		self.opacity = 0
		self:stopAllActions()
		self:runAction(CCSpawn({oScale(0.5,1,1,oEase.OutBack),oOpacity(0.5,0.8)}))
		self.touchEnabled = true
	end
	ruler.hide = function(self)
		if not ruler.visible then return end
		self.changed = nil
		self.touchEnabled = false
		self:stopAllActions()
		self:runAction(CCSequence(
		{
			CCSpawn(
			{
				oScale(0.5,0,0,oEase.InBack),
				oOpacity(0.5,0)
			}),
			CCCall(function()
				ruler.visible = false
			end),
		}))
	end
	return ruler
end

return oEditRuler
