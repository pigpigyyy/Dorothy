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
	rulerWidth = winSize.width
	rulerHeight = 30
	halfW = rulerWidth*0.5
	halfH = rulerHeight*0.5
	origin = editor.origin
	@ = with CCLayerColor ccColor4(0x88000000),rulerWidth,rulerHeight
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
		.position = oVec2 0,halfH
	@addChild intervalNode

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
	updatePart intervalNode.positionX,winSize.width-intervalNode.positionX
	updateLabels!

	-- listen view move event --
	@gslot "Scene.Camera.Move",(delta)->
		deltaX = -delta.x
		intervalNode.positionX += deltaX
		updatePart deltaX > 0 and intervalNode.positionX or 0,
			deltaX < 0 and winSize.width-intervalNode.positionX or 0
		updateLabels!

	@gslot "Scene.ViewArea.MoveTo",(pos)->
		width = winSize.width
		posX = editor.origin.x-pos.x
		intervalNode\runAction oPos 0.5,posX,halfH,oEase.OutQuad
		oRoutine once -> cycle 0.5,updateLabels
		updatePart posX,width-posX

	-- listen view scale event --
	updateIntervalTextScale = (scale)->
		intervalNode\eachChild (child)->
			child.scaleX = scale

	fadeOut = CCSequence {
		oOpacity 0.3,0
		CCCall ->
			@scaleX = 1
			updateIntervalTextScale 1
	}
	fadeIn = CCSequence {
		oOpacity 0.3,0.5
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
			@scaleX = scale
			-- unscale interval text --
			updateIntervalTextScale 1/scale

	@gslot "Scene.ViewArea.ScaleTo",(scale)->
		if scale < 1.0 and @opacity > 0 and fadeOut.done
			@touchEnabled = false
			@cascadeOpacity = true
			@perform fadeOut
		elseif scale >= 1.0 and self.opacity == 0 and fadeIn.done
			@touchEnabled = true
			@perform fadeIn
		if scale >= 1.0
			@runAction oScale 0.5,scale,1,oEase.OutQuad
			-- manually update and unscale interval text --
			time = 0
			intervalNode\schedule (deltaTime)->
				updateIntervalTextScale 1/@scaleX
				time = time + deltaTime
				if 1 == math.min time/0.5,1
					intervalNode\unschedule!

	-- handle touch event --
	@slot "TouchBegan",(touch)->
		loc = @convertToNodeSpace touch.location
		if CCRect(-halfW,-halfH,rulerWidth,rulerHeight)\containsPoint loc
			@opacity = 1
			true
		else
			false

	@slot "TouchMoved",(touch)->
		@positionY += touch.delta.y
		if @positionY > winSize.height-halfH-10
			@positionY = winSize.height-halfH-10
		elseif @positionY < halfH+10
			@positionY = halfH+10

	touchEnded = -> @perform oOpacity 0.3,0.5
	@slot "TouchCancelled",touchEnded
	@slot "TouchEnded",touchEnded

	@gslot "Scene.Camera.Activate",(subCam)->
		return if (subCam == nil) == (@positionY > 0)
		@touchEnabled = (subCam == nil)
		@perform oPos 0.5,@positionX,-@positionY,oEase.OutQuad

	@ -- return
