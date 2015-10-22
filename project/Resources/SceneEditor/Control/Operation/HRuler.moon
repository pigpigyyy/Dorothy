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

->
	winSize = CCDirector.winSize
	center = oVec2 winSize.width*0.5,winSize.height*0.5
	rulerWidth = winSize.width
	rulerHeight = 30
	halfW = rulerWidth*0.5
	halfH = rulerHeight*0.5
	origin = editor.origin
	@ = with CCLayerColor ccColor4(0),rulerWidth,rulerHeight
		.cascadeOpacity = true
		.opacity = 0.3
		.position = oVec2 origin.x,halfH+10
		.anchor = oVec2 origin.x/rulerWidth,0.5
		.touchPriority = editor.levelHRuler
		.swallowTouches = true
		.touchEnabled = true
		\addChild oLine {
			oVec2.zero,
			oVec2 rulerWidth,0
		},ccColor4!

	intervalNode = with oLine!
		.position = oVec2 origin.x,halfH
	@\addChild intervalNode

	nPart = 0
	nCurrentPart = 0
	pPart = 0
	pCurrentPart = 0
	vs = {}
	updatePart = (nLength,pLength)->
		nLength = nLength + 10
		pLength = pLength + 10
		if nLength <= nPart and pLength <= pPart
			return
		if nLength > nPart
			nPart = math.ceil(nLength/10)*10
		if pLength > pPart
			pPart = math.ceil(pLength/10)*10

	rightOffset = (rulerWidth-origin.x)+100
	leftOffset = -origin.x-100

	labels = {}
	labelList = {}
	setupLabels = ->
		right = math.floor rightOffset/100
		left = math.ceil leftOffset/100
		for i = left,right
			pos = i*100
			label = with CCLabelTTF tostring(pos),"Arial",10
				.texture.antiAlias = false
				.scaleX = 1/@scaleX
				.position = oVec2 pos,halfH-18
			intervalNode\addChild label
			labels[pos] = label
			table.insert labelList,label

	moveLabel = (label,pos)->
		labels[tonumber(label.text)] = nil
		labels[pos] = with label
			.text = tostring pos
			.texture.antiAlias = false
			.scaleX = 1/@scaleX
			.position = oVec2 pos,halfH-18

	updateLabels = ->
		right = math.floor (rightOffset-(intervalNode.positionX-origin.x))/100
		left = math.ceil (leftOffset-(intervalNode.positionX-origin.x))/100
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

		for i = right,left,-1
			pos = i*100
			if labels[pos]
				break
			else
				label = table.remove labelList,1
				table.insert labelList,label
				moveLabel label,pos

		if nCurrentPart < nPart or pCurrentPart < pPart
			start = math.floor nPart/10
			count = math.floor nCurrentPart/10
			length = #vs
			if start > count
				for i = count,start
					if i ~= 0
						posX = -i*10
						table.insert vs,1,oVec2(posX,halfH)
						table.insert vs,1,oVec2(posX,halfH-(i%10 == 0 and 8 or 4))
						table.insert vs,1,oVec2(posX,halfH)
					nCurrentPart += 10
			start = math.floor pCurrentPart/10
			count = math.floor pPart/10
			if start < count
				for i = start,count
					posX = i*10
					table.insert vs,oVec2(posX,halfH)
					table.insert vs,oVec2(posX,halfH-(i%10 == 0 and 8 or 4))
					table.insert vs,oVec2(posX,halfH)
					pCurrentPart += 10
			if #vs ~= length
				intervalNode\set vs

	-- set default interval negtive & positive part length --
	setupLabels!
	updatePart origin.x,winSize.width-origin.x
	updateLabels!

	-- listen view move event --
	@\gslot "Scene.ViewArea.Move",(delta)->
		intervalNode.positionX += delta.x/@scaleX
		updatePart delta.x > 0 and intervalNode.positionX or 0,
			delta.x < 0 and winSize.width-intervalNode.positionX or 0
		updateLabels!

	@\gslot "Scene.ViewArea.MoveTo",(pos)->
		pos += center
		intervalNode\runAction oPos 0.5,pos.x,halfH,oEase.OutQuad
		oRoutine once -> cycle 0.5,-> updateLabels!
		updatePart pos.x,winSize.width-pos.x

	-- listen view scale event --
	updateIntervalTextScale = (scale)->
		intervalNode\eachChild (child)->
			child.scaleX = scale

	fadeOut = CCSequence {
		oOpacity 0.3,0
		CCCall ->
			layer.scaleX = 1
			updateIntervalTextScale 1
	}
	fadeIn = oOpacity 0.3,0.3
	@\gslot "Scene.ViewArea.Scale",(scale)->
		if scale < 1.0 and @opacity > 0 and fadeOut.done
			@touchEnabled = false
			@\perform fadeOut
		elseif scale >= 1.0
			if @opacity == 0 and fadeIn.done
				@touchEnabled = true
				@\perform fadeIn
			@scaleX = scale
			-- unscale interval text --
			updateIntervalTextScale 1/scale

	@\gslot "Scene.ViewArea.ScaleTo",(scale)->
		if scale < 1.0 and @opacity > 0 and fadeOut.done
			@touchEnabled = false
			@\perform fadeOut
		elseif scale >= 1.0 and self.opacity == 0 and fadeIn.done
			@touchEnabled = true
			@\perform fadeIn
		if scale >= 1.0
			@\runAction oScale 0.5,scale,1,oEase.OutQuad
			-- manually update and unscale interval text --
			time = 0
			intervalNode\schedule (deltaTime)->
				updateIntervalTextScale 1/@scaleX
				time = time + deltaTime
				if 1 == math.min time/0.5,1
					intervalNode\unschedule!

	-- handle touch event --
	@\slots "TouchBegan",(touch)->
		loc = @\convertToNodeSpace touch.location
		CCRect(-halfW,-halfH,rulerWidth,rulerHeight)\containsPoint loc
	@\slots "TouchMoved",(touch)->
		@positionY += touch.delta.y
		if @positionY > winSize.height-halfH-10
			@positionY = winSize.height-halfH-10
		elseif @positionY < halfH+10
			@positionY = halfH+10

	@ -- return
