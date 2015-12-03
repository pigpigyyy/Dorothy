Dorothy!
Class = unpack require "class"
RulerView = require "View.Control.Edit.Ruler"

Class RulerView,
	__init: (args)=>
		{:y,:width,:height} = args
		winSize = CCDirector.winSize
		halfW = width/2
		halfH = height/2
		interval = 10
		top = math.ceil width/interval
		up = 0
		down = 1
		bottom = math.ceil width/interval
		vs = {}
		indent = 100
		@endPosY = y

		labels = {}
		labelList = {}
		setupLabels = ->
			posX = @intervalNode.anchor.x*width
			right = math.floor (posX+width+50)/100
			left = math.floor (posX-width-50)/100
			for i = left,right
				pos = i*100
				label = with CCLabelTTF tostring(pos/100*indent),"Arial",10
					--.texture.antiAlias = false
					.scaleX = 1/@intervalNode.scaleX
					.position = oVec2 pos,halfH-28
				@intervalNode\addChild label
				labels[pos] = label
				table.insert labelList,label

		moveLabel = (label,pos)->
			labels[math.ceil(tonumber(label.text)/indent)*100] = nil
			labels[pos] = with label
				.text = tostring pos/100*indent
				.texture.antiAlias = false
				.scaleX = 1/@intervalNode.scaleX
				.position = oVec2 pos,halfH-28

		updateLabels = ->
			posX = @intervalNode.anchor.x*width
			right = math.floor (posX+width)/100
			left = math.floor (posX-width)/100
			insertPos = 1
			for i = left,right
				pos = i*100
				if labels[pos]
					break
				else
					label = table.remove labelList
					table.insert labelList,insertPos,label
					insertPos = insertPos+1
					moveLabel label,pos
			for i = right,left,-1
				pos = i*100
				if labels[pos]
					break
				else
					label = table.remove labelList,1
					table.insert labelList,label
					moveLabel label,pos
			if up < top or down < bottom
				if up < top
					target = top
					for i = up,target
						posX = i*interval
						table.insert vs,1,oVec2(posX,halfH)
						table.insert vs,1,oVec2(posX,halfH-(i%10 == 0 and 16 or 8))
						table.insert vs,1,oVec2(posX,halfH)
					up = target+1
				if down < bottom
					target = bottom
					for i = down,target
						posX = -i*interval
						table.insert vs,oVec2(posX,halfH)
						table.insert vs,oVec2(posX,halfH-(i%10 == 0 and 16 or 8))
						table.insert vs,oVec2(posX,halfH)
					down = target+1
				@intervalNode\set vs

		setupLabels!

		arrow = with CCNode!
			.cascadeOpacity = false
			.position = oVec2 halfW,halfH
			\addChild oLine {
				oVec2 0,-halfH
				oVec2 0,halfH
				},ccColor4 0xff00ffff
		@addChild arrow

		updateIntervalTextScale = (scale)->
			@intervalNode\eachChild (child)->
				child.scaleX = scale

		@gslot "Scene.ViewArea.Scale",(scale)->
			scale = math.min scale,5
			@intervalNode.scaleX= scale
			-- unscale interval text --
			updateIntervalTextScale 1/scale
			posX = @intervalNode.anchor.x*width
			if posX >= 0 then
				newTop = math.ceil (posX+width/scale)/interval
				top = math.max top,newTop
			else
				newBottom = math.ceil (-posX+width/scale)/interval
				bottom = math.max bottom,newBottom
			updateLabels!

		@gslot "Scene.ViewArea.ScaleTo",(scale)->
			@intervalNode\perform oScale 0.5,scale,1,oEase.OutQuad
			-- manually update and unscale interval text --
			time = 0
			@intervalNode\schedule (deltaTime)->
				updateIntervalTextScale 1/@intervalNode.scaleX
				time = time + deltaTime
				if math.min(time/0.5,1) == 1
					@intervalNode\unschedule!

			posX = @intervalNode.anchor.x*width
			newTop = math.ceil (posX+width/scale)/interval
			top = math.max top,newTop
			newBottom = math.ceil (-posX+width/scale)/interval
			bottom = math.max bottom,newBottom
			updateLabels!

		@setIndent = (ind)=>
			indent = ind
			for i,label in pairs labels
				label.text = tostring ind*i/100
				label.texture.antiAlias = false

		_value = 0
		_max = 0
		_min = 0
		@setValue = (v)=>
			_value = v
			if _min < _max
				val = _value
				val = math.max val,_min
				val = math.min val,_max
				@emit "Changed",editor.isFixed and math.floor(val/(indent/10)+0.5)*(indent/10) or val
			else
				@emit "Changed",editor.isFixed and math.floor(_value/(indent/10)+0.5)*(indent/10) or _value

			posX = v*10*interval/indent
			@intervalNode.anchor = oVec2 posX/width,0
			scale = @intervalNode.scaleX
			if posX >= 0
				newTop = math.ceil (posX+width/scale)/interval
				top = math.max top,newTop
			else
				newBottom = math.ceil (-posX+width/scale)/interval
				bottom = math.max bottom,newBottom
			updateLabels!

		@getValue = => _value
		@getPos = => _value*10*interval/indent

		@setLimit = (min,max)=>
			_max = max
			_min = min

		time = 0
		startPos = 0
		updateReset = (deltaTime)->
			return if _min >= _max
			scale = @intervalNode.scaleX
			time = time + deltaTime
			t = time/1
			t = t/0.1 if scale < 1
			t = math.min 1,t
			yVal = nil
			if startPos < _min
				yVal = oEase\func scale < 1 and oEase.Linear or oEase.OutElastic,t,startPos,_min-startPos
			elseif startPos > _max
				yVal = oEase\func scale < 1 and oEase.Linear or oEase.OutElastic,t,startPos,_max-startPos
			@setValue ((yVal and yVal or 0)-_value)/scale+_value
			@unschedule! if t == 1.0

		isReseting = ->
			_min < _max and (_value > _max or _value < _min)

		startReset = ->
			startPos = _value
			time = 0
			@schedule updateReset

		_v = 0
		_s = 0
		updateSpeed = (deltaTime)->
			return if _s == 0
			_v = _s / deltaTime
			_s = 0

		updatePos = (deltaTime)->
			val = winSize.height*2
			a = _v > 0 and -val or val
			yR = _v > 0
			_v = _v + a*deltaTime
			if _v < 0 == yR
				_v = 0
				a = 0
			ds = _v * deltaTime + a*(0.5*deltaTime*deltaTime)
			newValue = _value-ds*indent/(interval*10)
			@setValue (newValue-_value)/@intervalNode.scaleY+_value
			if _v == 0 or (_min < _max and (_value < _min or _value > _max))
				if isReseting!
					startReset!
				else
					@unschedule!

		@slots "TouchBegan",->
			_s = 0
			_v = 0
			@schedule updateSpeed
			true

		@slots "TouchMoved",(touch)->
			v = _value-touch.delta.x*indent/(interval*10)
			padding = 0.5*indent
			if _max > _min
				d = 1
				if v > _max
					d = (v - _max)*3/padding
				elseif v < _min
					d = (_min - v)*3/padding
				v = _value+(v - _value)/(d < 1 and 1 or d*d)
			@setValue (v-_value)/@intervalNode.scaleX+_value
			_s = _s + touch.delta.x

		touchEnded = ->
			if isReseting!
				startReset!
			elseif _v ~= 0
				@schedule updatePos
		@slots "TouchEnded",touchEnded
		@slots "TouchCancelled",touchEnded

	show: (default,min,max,indent,callback)=>
		@setIndent indent
		@setLimit min,max
		@setValue default
		@slots("Changed")\set callback
		@visible = true
		@positionY = @endPosY+30
		@opacity = 0
		@perform CCSpawn {
			oPos 0.5,@positionX,@endPosY,oEase.OutBack
			oOpacity 0.3, 0.8
		}

	hide: =>
		return if not @visible
		@slots "Changed",nil
		@unschedule!
		@perform CCSequence {
			CCSpawn {
				oPos 0.5,@positionX,@endPosY+30,oEase.InBack
				oOpacity 0.5,0
			}
			CCHide!
		}
