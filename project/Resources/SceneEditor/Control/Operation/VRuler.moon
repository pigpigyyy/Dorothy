CCDirector = require "CCDirector"
oLine = require "oLine"
oVec2 = require "oVec2"
ccColor4 = require "ccColor4"
CCLayerColor = require "CCLayerColor"
oScale = require "oScale"
oEase = require "oEase"
oOpacity = require "oOpacity"
CCRect = require "CCRect"
CCLabelTTF = require "CCLabelTTF"
oPos = require "oPos"
CCSequence = require "CCSequence"
CCCall = require "CCCall"
once = require "once"
oRoutine = require "oRoutine"
cycle = require "cycle"

-- [no signals]
-- [no params]
->
	winSize = CCDirector.winSize
	rulerWidth = 30
	rulerHeight = winSize.height
	halfW = rulerWidth*0.5
	halfH = rulerHeight*0.5
	origin = editor.origin
	@ = with CCLayerColor ccColor4(0x88000000),rulerWidth,rulerHeight
		.position = oVec2 winSize.width-200-halfW,halfH
		.touchPriority = editor.levelVRuler
		.swallowTouches = true
		.touchEnabled = true
		\addChild oLine {
			oVec2 rulerWidth,rulerHeight
			oVec2 rulerWidth,0
		},ccColor4!

	-- init interval --
	intervalNode = with oLine!
		.position = oVec2 halfW,0
	@addChild intervalNode

	nPart = 0
	nCurrentPart = 0
	pPart = 0
	pCurrentPart = 0
	vs = {}
	updatePart = (nLength,pLength)->
		nLength += 10
		pLength += 10
		if nLength <= nPart and pLength <= pPart
			return
		if nLength > nPart
			nPart = math.ceil(nLength/10)*10
		if pLength > pPart then
			pPart = math.ceil(pLength/10)*10

	rightOffset = (rulerHeight-origin.y)+100
	leftOffset = -origin.y-100

	labels = {}
	labelList = {}
	setupLabels = ->
		right = math.floor rightOffset/100
		left = math.ceil leftOffset/100
		for i = left,right
			pos = i*100
			label = with CCLabelTTF tostring(pos),"Arial",10
				.texture.antiAlias = false
				.scaleX = 1/@scaleY
				.angle = -90
				.position = oVec2 -halfW+18,pos
			intervalNode\addChild label
			labels[pos] = label
			table.insert labelList,label

	moveLabel = (label,pos)->
		labels[tonumber(label.text)] = nil
		labels[pos] = with label
			.text = tostring pos
			.texture.antiAlias = false
			.scaleX = 1/@scaleY
			.angle = -90
			.position = oVec2 -halfW+18,pos

	updateLabels = ->
		right = math.floor (rightOffset-(intervalNode.positionY-origin.y))/100
		left = math.ceil (leftOffset-(intervalNode.positionY-origin.y))/100
		insertPos = 1
		for i = left,right
			pos = i*100
			if labels[pos]
				break
			else
				label = table.remove labelList
				table.insert labelList,insertPos,label
				insertPos += 1
				moveLabel label,pos
		insertPos = #labelList
		for i = right,left,-1
			pos = i*100
			if labels[pos]
				break
			else
				label = table.remove labelList,1
				table.insert labelList,insertPos,label
				insertPos -= 1
				moveLabel label,pos
		if nCurrentPart < nPart or pCurrentPart < pPart
			start = math.floor nCurrentPart/10
			count = math.floor nPart/10
			length = #vs
			if start < count
				for i = start,count
					posY = i*10
					table.insert vs,oVec2(-halfW,posY)
					table.insert vs,oVec2(-halfW+(i%10 == 0 and 8 or 4),posY)
					table.insert vs,oVec2(-halfW,posY)
					nCurrentPart += 10
			start = math.floor pCurrentPart/10
			count = math.floor pPart/10
			if start < count
				for i = start,count
					if i ~= 0
						posY = -i*10
						table.insert vs,1,oVec2(-halfW,posY)
						table.insert vs,1,oVec2(-halfW+(i%10 == 0 and 8 or 4),posY)
						table.insert vs,1,oVec2(-halfW,posY)
					pCurrentPart += 10
			if #vs ~= length
				intervalNode\set vs

	-- set default interval negtive & positive part length --
	setupLabels!
	updatePart winSize.height-intervalNode.positionY, intervalNode.positionY
	updateLabels!

	-- listen view move event --
	@gslot "Scene.Camera.Move",(delta)->
		deltaY = -delta.y
		intervalNode.positionY += deltaY
		updatePart deltaY < 0 and winSize.height-intervalNode.positionY or 0,
			deltaY > 0 and intervalNode.positionY or 0
		updateLabels!

	@gslot "Scene.Camera.MoveTo",(pos)->
		height = winSize.height
		posY = editor.origin.y-pos.y
		intervalNode\runAction oPos 0.5,halfW,posY,oEase.OutQuad
		oRoutine once -> cycle 0.5,-> updateLabels!
		updatePart winSize.height-posY,posY

	-- listen view scale event --
	updateIntervalTextScale = (scale)->
		intervalNode\eachChild (child)->
			child.scaleX = scale

	fadeOut = CCSequence {
		oOpacity 0.3,0
		CCCall ->
			@scaleY = 1
			updateIntervalTextScale 1
	}
	fadeIn = CCSequence {
		oOpacity 0.3,0.3
		CCCall ->
			@cascadeOpacity = false
	}
	@gslot "Scene.ViewArea.Scale",(scale)->
		if scale < 1.0 and @opacity > 0 and fadeOut.done
			@touchEnabled = false
			@cascadeOpacity = true
			@perform fadeOut
		elseif scale >= 1.0
			if @opacity == 0 and fadeIn.done
				@touchEnabled = true
				@perform fadeIn
			@scaleY = scale
			-- unscale interval text --
			updateIntervalTextScale 1/scale

	@gslot "Scene.ViewArea.ScaleTo",(scale)->
		if scale < 1.0 and self.opacity > 0 and fadeOut.done
			@touchEnabled = false
			@cascadeOpacity = true
			@perform fadeOut
		elseif scale >= 1.0 and @opacity == 0 and fadeIn.done
			@touchEnabled = true
			@perform fadeIn
		if scale >= 1.0
			@runAction oScale 0.5,1,scale,oEase.OutQuad
			-- manually update and unscale interval text --
			time = 0
			intervalNode\schedule (deltaTime)->
				updateIntervalTextScale 1/@scaleY
				time = time + deltaTime
				if 1 == math.min time/0.5,1
					intervalNode\unschedule!

	-- handle touch event --
	@slots "TouchBegan",(touch)->
		loc = @convertToNodeSpace touch.location
		if CCRect(-halfW,-halfH,rulerWidth,rulerHeight)\containsPoint loc
			@opacity = 1
			true
		else
			false

	@slots "TouchMoved",(touch)->
		@positionX += touch.delta.x
		if @positionX > winSize.width-190-halfW-10
			@positionX = winSize.width-190-halfW-10
		elseif @positionX < halfW+10
			@positionX = halfW+10

	touchEnded = -> @perform oOpacity 0.3,0.5
	@slots "TouchCancelled",touchEnded
	@slots "TouchEnded",touchEnded

	@
