local require = using("EffectEditor.Script")
local CCDirector = require("CCDirector")
local CCSize = require("CCSize")
local oSelectionPanel = require("oSelectionPanel")
local oEditor = require("oEditor")
local CCDrawNode = require("CCDrawNode")
local oVec2 = require("oVec2")
local CCLabelTTF = require("CCLabelTTF")
local ccColor3 = require("ccColor3")
local emit = require("emit")
local oSettingItem = require("oSettingItem")
local ccBlendFunc = require("ccBlendFunc")
local CCRect = require("CCRect")
local thread = require("thread")
local sleep = require("sleep")
local oPos = require("oPos")
local oEase = require("oEase")
local ccColor4 = require("ccColor4")
local oRoutine = require("oRoutine")
local once = require("once")
local wait = require("wait")
local seconds = require("seconds")

local function oSettingPanel()
	local winSize = CCDirector.winSize
	local borderSize = CCSize(240,winSize.height-20)
	local self = oSelectionPanel(borderSize,false,true,true)
	self.touchPriority = oEditor.touchPrioritySettingPanel
	local menu = self.menu
	menu.touchPriority = oEditor.touchPrioritySettingPanel+1
	local border = self.border
	local halfBW = borderSize.width*0.5
	local halfBH = borderSize.height*0.5
	local itemWidth = borderSize.width
	local itemHeight = 30
	local background = CCDrawNode()
	border:addChild(background,-1)
	local startPos = oVec2(winSize.width*0.5+halfBW,0)
	local particlePos = oVec2(winSize.width*0.5-halfBW-10,0)
	local framePos = oVec2(winSize.width*0.5-halfBW-10,-winSize.height+170)
	self.position = startPos

	local label = CCLabelTTF("","Arial",16)
	label.position = oVec2(halfBW,borderSize.height-18)
	label.color = ccColor3(0x00ffff)
	menu:addChild(label)

	local function genPosY()
		local index = 0
		return function()
			local v = index
			index = index + 1
			return borderSize.height-30-itemHeight*v
		end
	end

	local itemNames =
	{
		"name",
		"file",
		"maxParticles",
		"angle",
		"angleVar",
		"duration",
		"blendFuncSrc",
		"blendFuncDst",
		"startColor",
		"startRedVar",
		"startGreenVar",
		"startBlueVar",
		"startAlphaVar",
		"finishColor",
		"finishRedVar",
		"finishGreenVar",
		"finishBlueVar",
		"finishAlphaVar",
		"startSize",
		"startSizeVar",
		"finishSize",
		"finishSizeVar",
		"sourcePosXVar",
		"sourcePosYVar",
		"rotationStart",
		"rotationStartVar",
		"rotationEnd",
		"rotationEndVar",
		"lifeTime",
		"lifeTimeVar",
		"emissionRate",
		"textureFile",
		"textureRect",
		"emitterType",
		"gravityX",
		"gravityY",
		"speed",
		"speedVar",
		"radialAccel",
		"radialAccelVar",
		"tangentAccel",
		"tangentAccelVar",
		"rotationIsDir",
		"startRadius",
		"startRadiusVar",
		"endRadius",
		"endRadiusVar",
		"angularSpeed",
		"angularSpeedVar",
		"interval",
	}

	local currentItem = nil
	local function editCallback(settingItem)
		if currentItem and settingItem.selected then
			currentItem.selected = false
		end
		currentItem = settingItem.selected and settingItem or nil
		emit("Effect.settingPanel.edit",settingItem)
	end
	local items = {}
	local getPosY = genPosY()
	for i = 1,#itemNames do
		local itemName = itemNames[i]
		local item = oSettingItem(itemName.." :",itemWidth,itemHeight,0,getPosY(),i == 1,editCallback)
		item.name = itemName
		items[itemName] = item
	end
	items.textureRect.enabled = false
	items.file.enabled = false

	local handlers = {}
	local function listen(itemName,name,getter)
		if not getter and type(name) == "function" then
			getter = name
			name = itemName
		end
		handlers[name] = function(val)
			local item = items[itemName]
			item.value = getter and getter(val[2]) or val[2]
		end
	end

	self:gslot("Effect.attr",function(val)
		if not handlers[val[1]] then
			local item = items[val[1]]
			if item then
				item.value = val[2]
			end
		else
			handlers[val[1]](val)
		end
	end)

	local finishColorA = 0
	local finishColorR = 0
	local finishColorG = 0
	local finishColorB = 0
	local function shiftColor(v,bit) return math.floor(v*255+0.5)*math.pow(2,bit) end
	local function getFinishColorStr()
		return string.format("0x%.8X",finishColorA+finishColorR+finishColorG+finishColorB)
	end
	listen("finishColor","finishColorAlpha",function(a) finishColorA = shiftColor(a,24);return getFinishColorStr() end)
	listen("finishColor","finishColorRed",function(r) finishColorR = shiftColor(r,16);return getFinishColorStr() end)
	listen("finishColor","finishColorGreen",function(g) finishColorG = shiftColor(g,8);return getFinishColorStr() end)
	listen("finishColor","finishColorBlue",function(b) finishColorB = shiftColor(b,0);return getFinishColorStr() end)
	local function getChanel(var) return string.format("%d",var*255) end
	listen("finishRedVar","finishColorVarianceRed",getChanel)
	listen("finishGreenVar","finishColorVarianceGreen",getChanel)
	listen("finishBlueVar","finishColorVarianceBlue",getChanel)
	listen("finishAlphaVar","finishColorVarianceAlpha",getChanel)

	local startColorA = 0
	local startColorR = 0
	local startColorG = 0
	local startColorB = 0
	local function getStartColorStr()
		return string.format("0x%.8X",startColorA+startColorR+startColorG+startColorB)
	end
	listen("startColor","startColorAlpha",function(a) startColorA = shiftColor(a,24);return getStartColorStr() end)
	listen("startColor","startColorRed",function(r) startColorR = shiftColor(r,16);return getStartColorStr() end)
	listen("startColor","startColorGreen",function(g) startColorG = shiftColor(g,8);return getStartColorStr() end)
	listen("startColor","startColorBlue",function(b) startColorB = shiftColor(b,0);return getStartColorStr() end)
	listen("startRedVar","startColorVarianceRed",getChanel)
	listen("startGreenVar","startColorVarianceGreen",getChanel)
	listen("startBlueVar","startColorVarianceBlue",getChanel)
	listen("startAlphaVar","startColorVarianceAlpha",getChanel)

	local function getBlend(value)
		for k,v in pairs(ccBlendFunc) do
			if v == value then
				return k
			end
		end
		return ""
	end
	listen("maxParticles",function(var) return string.format("%d",var) end)
	listen("blendFuncSrc","blendFuncSource",function(var) return getBlend(var) end)
	listen("blendFuncDst","blendFuncDestination",function(var) return getBlend(var) end)
	listen("duration",function(var) return var < 0 and "Infinite" or var end)
	listen("angleVar","angleVariance")
	listen("startSize","startParticleSize")
	listen("startSizeVar","startParticleSizeVariance")
	listen("finishSize","finishParticleSize")
	listen("finishSizeVar","finishParticleSizeVariance")
	listen("sourcePosXVar","sourcePositionVariancex")
	listen("sourcePosYVar","sourcePositionVariancey")
	listen("rotationStartVar","rotationStartVariance")
	listen("rotationEndVar","rotationEndVariance")
	listen("lifeTime","particleLifespan")
	listen("lifeTimeVar","particleLifespanVariance")
	listen("startRadius","maxRadius")
	listen("startRadiusVar","maxRadiusVariance")
	listen("endRadius","minRadius")
	listen("endRadiusVar","minRadiusVariance")
	listen("angularSpeed","rotatePerSecond")
	listen("angularSpeedVar","rotatePerSecondVariance")
	listen("speedVar","speedVariance")
	listen("radialAccel","radialAcceleration")
	listen("radialAccelVar","radialAccelVariance")
	listen("gravityX","gravityx")
	listen("gravityY","gravityy")
	listen("tangentAccel","tangentialAcceleration")
	listen("tangentAccelVar","tangentialAccelVariance")
	listen("textureFile","textureFileName",function(name) return name == "__firePngData" and "Built-In" or name:match("[^\\/]*%.[^%.\\/]*$") end)
	local rc = CCRect()
	local function getRectStr()
		return rc == CCRect.zero and "Full" or string.format("%d,%d,%d,%d",rc.origin.x,rc.origin.y,rc.size.width,rc.size.height)
	end
	listen("textureRect","textureRectx",function(x) rc.origin = oVec2(x,rc.origin.y);return getRectStr() end)
	listen("textureRect","textureRecty",function(y) rc.origin = oVec2(rc.origin.x,y);return getRectStr() end)
	listen("textureRect","textureRectw",function(w) rc.size = CCSize(w,rc.size.height);return getRectStr() end)
	listen("textureRect","textureRecth",function(h) rc.size = CCSize(rc.size.width,h);return getRectStr() end)

	local modeGravity =
	{
		items.name,
		items.file,
		items.maxParticles,
		items.angle,
		items.angleVar,
		items.duration,
		items.blendAdditive,
		items.blendFuncSrc,
		items.blendFuncDst,
		items.startColor,
		items.startRedVar,
		items.startGreenVar,
		items.startBlueVar,
		items.startAlphaVar,
		items.finishColor,
		items.finishRedVar,
		items.finishGreenVar,
		items.finishBlueVar,
		items.finishAlphaVar,
		items.startSize,
		items.startSizeVar,
		items.finishSize,
		items.finishSizeVar,
		items.sourcePosition,
		items.sourcePosXVar,
		items.sourcePosYVar,
		items.rotationStart,
		items.rotationStartVar,
		items.rotationEnd,
		items.rotationEndVar,
		items.lifeTime,
		items.lifeTimeVar,
		items.emissionRate,
		items.textureFile,
		items.textureRect,
		items.emitterType,
		items.gravityX,
		items.gravityY,
		items.speed,
		items.speedVar,
		items.radialAccel,
		items.radialAccelVar,
		items.tangentAccel,
		items.tangentAccelVar,
	}

	local modeRadius =
	{
		items.name,
		items.file,
		items.maxParticles,
		items.angle,
		items.angleVar,
		items.duration,
		items.blendAdditive,
		items.blendFuncSrc,
		items.blendFuncDst,
		items.startColor,
		items.startColorRVar,
		items.startColorGVar,
		items.startColorBVar,
		items.startColorAVar,
		items.finishColor,
		items.finishColorRVar,
		items.finishColorGVar,
		items.finishColorBVar,
		items.finishColorAVar,
		items.startSize,
		items.startSizeVar,
		items.finishSize,
		items.finishSizeVar,
		items.sourcePosition,
		items.sourcePosXVar,
		items.sourcePosYVar,
		items.rotationStart,
		items.rotationStartVar,
		items.rotationEnd,
		items.rotationEndVar,
		items.lifeTime,
		items.lifeTimeVar,
		items.emissionRate,
		items.textureFile,
		items.textureRect,
		items.emitterType,
		items.startRadius,
		items.startRadiusVar,
		items.endRadius,
		items.endRadiusVar,
		items.angularSpeed,
		items.angularSpeedVar,
	}

	local modeFrame =
	{
		items.name,
		items.file,
		items.interval,
	}

	for _,item in pairs(items) do
		item.visible = false
		menu:addChild(item)
	end

	local isHide = false
	local transforming = false
	local function transformingEndAfter(time)
		thread(function()
			sleep(time)
			transforming = false
		end)
	end
	local function hidePanel(instant)
		local posX = framePos.x+borderSize.width+10
		if instant then
			self.positionX = posX
		else
			self:perform(oPos(0.3,posX,self.positionY,oEase.OutQuad))
		end
	end
	local targetPos = nil
	local currentGroup = nil
	local function setGroup(group)
		if group == currentGroup then return end
		for _,item in pairs(items) do
			item.visible = false
			item.positionX = -itemWidth
		end
		transforming = true
		if group == nil then
			isHide = true
			label.visible = false
			label.positionX = -itemWidth
			hidePanel(false)
			transformingEndAfter(0.3)
			currentGroup = group
			return
		else
			isHide = false
		end
		local y = items.emitterType.positionY
		self:setOffset(oVec2.zero)
		label.visible = true
		label.positionY = borderSize.height - 18
		local contentHeight = 40
		local getPosY = genPosY()
		for _,item in pairs(group) do
			item.positionX = 0
			item.positionY = getPosY()
			item.visible = true
			contentHeight = contentHeight + itemHeight
		end
		if group == modeFrame then
			label.text = "Frame"
			label.texture.antiAlias = false
			if not currentGroup then
				background:clear()
				background:drawPolygon(
				{
					oVec2(-halfBW,halfBH-150),
					oVec2(halfBW,halfBH-150),
					oVec2(halfBW,halfBH),
					oVec2(-halfBW,halfBH)
				},ccColor4(0x88100000),0.5,ccColor4(0xffffafaf))
				self.position = oVec2(framePos.x+borderSize.width+10,framePos.y)
				targetPos = framePos
				self:runAction(oPos(0.3,framePos.x,framePos.y,oEase.OutQuad))
				transformingEndAfter(0.3)
			else
				oRoutine(once(function()
					self:runAction(oPos(0.3,startPos.x,startPos.y,oEase.OutQuad))
					wait(seconds(0.3))
					background:clear()
					background:drawPolygon(
					{
						oVec2(-halfBW,halfBH-150),
						oVec2(halfBW,halfBH-150),
						oVec2(halfBW,halfBH),
						oVec2(-halfBW,halfBH)
					},ccColor4(0x88100000),0.5,ccColor4(0xffffafaf))
					targetPos = framePos
					self.position = oVec2(framePos.x+borderSize.width+10,framePos.y)
					self:runAction(oPos(0.3,framePos.x,framePos.y,oEase.OutQuad))
					transformingEndAfter(0.3)
				end))
			end
			self:reset(borderSize.width,contentHeight,0,0)
			oEditor.origin = oVec2(winSize.width*0.5,(winSize.height-150)*0.5+150)
			emit("Effect.editor.frame")
		elseif group ~= nil then
			self:reset(borderSize.width,contentHeight,0,50)
			if currentGroup == nil or currentGroup == modeFrame then
				label.text = "Particle"
				label.texture.antiAlias = false
				background:clear()
				if not currentGroup then
					background:drawPolygon(
					{
						oVec2(-halfBW,-halfBH),
						oVec2(halfBW,-halfBH),
						oVec2(halfBW,halfBH),
						oVec2(-halfBW,halfBH)
					},ccColor4(0x88100000),0.5,ccColor4(0xffffafaf))
					targetPos = particlePos
					self:runAction(oPos(0.3,particlePos.x,particlePos.y,oEase.OutQuad))
					transformingEndAfter(0.3)
				else
					oRoutine(once(function()
						self:runAction(oPos(0.3,framePos.x+borderSize.width+10,framePos.y,oEase.OutQuad))
						wait(seconds(0.3))
						background:clear()
						background:drawPolygon(
						{
							oVec2(-halfBW,-halfBH),
							oVec2(halfBW,-halfBH),
							oVec2(halfBW,halfBH),
							oVec2(-halfBW,halfBH)
						},ccColor4(0x88100000),0.5,ccColor4(0xffffafaf))
						targetPos = particlePos
						self.position = oVec2(startPos.x,startPos.y)
						self:runAction(oPos(0.3,particlePos.x,particlePos.y,oEase.OutQuad))
						transformingEndAfter(0.3)
					end))
				end
				oEditor.origin = oVec2(60+(winSize.width-300)*0.5,winSize.height*0.5)
				emit("Effect.editor.particle")
			else
				self:setOffset(oVec2(0,y-items.emitterType.positionY))
			end
		end
		currentGroup = group
	end

	listen("emitterType",function(var)
		if var == oEditor.EmitterGravity then
			setGroup(modeGravity)
			return "Gravity"
		elseif var == oEditor.EmitterRadius then
			setGroup(modeRadius)
			return "Radius"
		end
	end)

	listen("interval",function(var)
		setGroup(modeFrame)
		return var
	end)

	self:gslot("Effect.settingPanel.cancel",function()
		if currentItem then
			currentItem.selected = false
		end
	end)
	self:gslot("Effect.settingPanel.hide",function()
		setGroup(nil)
		emit("Effect.settingPanel.cancel")
	end)

	self:gslot("Effect.hideEditor",function(args)
		local hide,instant = unpack(args)
		if isHide == hide then
			return
		end
		isHide = hide
		if hide then
			if transforming then
				thread(function()
					wait(function() return transforming end)
					hidePanel(instant)
				end)
			else
				hidePanel(instant)
			end
		elseif not transforming and targetPos then
			if instant then
				self.positionX = targetPos
			else
				self:perform(oPos(0.3,targetPos.x,targetPos.y,oEase.OutQuad))
			end
		end
	end)
	return self
end

return oSettingPanel
