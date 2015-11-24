Dorothy!
Class,property = unpack require "class"
ViewAreaView = require "View.Control.Operation.ViewArea"

-- [no signals]
-- [no params]
Class
	__partial: => ViewAreaView!
	__init: =>
		{:width,:height} = @

		S = oVec2.zero
		V = oVec2.zero
		accel = height*2
		updateDragSpeed = (dt)->
			V = S / dt
			if V.length > accel
				V\normalize!
				V = V * accel
			S = oVec2.zero

		updateDragPos = (dt)->
			dir = oVec2 V.x,V.y
			dir\normalize!
			A = dir * -accel
			incX = V.x > 0
			incY = V.y > 0
			V = V + A * dt * 0.5
			decX = V.x < 0
			decY = V.y < 0
			if incX == decX and incY == decY
				@unschedule!
			else
				emit "Scene.ViewArea.Move",V*dt

		tap = false
		@slots "TouchBegan",(touches)->
			tap = true
			S = oVec2.zero
			V = oVec2.zero
			@schedule updateDragSpeed
			true

		@slots "TouchMoved",(touches)->
			if #touches == 1 -- move view
				delta = touches[1].delta
				if delta ~= oVec2.zero
					S = delta
					tap = false
					emit "Scene.ViewArea.Move",delta
			elseif #touches >= 2 -- scale view
				preDistance = touches[1].preLocation\distance touches[2].preLocation
				distance = touches[1].location\distance touches[2].location
				delta = (distance - preDistance) * 4 / height
				scale = @scaleNode.scaleX + delta
				if scale <= 0.5
					scale = 0.5
				@scaleNode.scaleX = scale
				@scaleNode.scaleY = scale
				tap = false
				emit "Scene.ViewArea.Scale",scale

		touchEnded = (touches)->
			if tap then
				@unschedule!
				uiPos = touches[1].location
				worldPos = @crossNode\convertToNodeSpace uiPos
				emit "Scene.ViewArea.Tap",{uiPos,worldPos}
			elseif V ~= oVec2.zero
					@schedule updateDragPos
		@slots "TouchEnded",touchEnded
		@slots "TouchCancelled",touchEnded

		@gslot "Scene.ViewArea.ScaleTo",(scale)->
			editor.scale = scale
			@touchEnabled = false
			@scaleNode\runAction CCSequence {
				oScale 0.5,scale,scale,oEase.OutQuad
				CCCall ->
					if @scaleNode.numberOfRunningActions+
						@crossNode.numberOfRunningActions == 1
						@touchEnabled = true
			}

		@gslot "Scene.ViewArea.MoveTo",(pos)->
			pos -= editor.origin
			@unschedule!
			@touchEnabled = false
			@crossNode\runAction CCSequence {
				oPos 0.5,pos.x,pos.y,oEase.OutQuad
				CCCall ->
					if @scaleNode.numberOfRunningActions+
						@crossNode.numberOfRunningActions == 1
						@touchEnabled = true
			}
			@xcross\runAction oPos 0.5,0,-pos.y,oEase.OutQuad
			@ycross\runAction oPos 0.5,-pos.x,0,oEase.OutQuad

		@gslot "Scene.ViewArea.Move",(delta)->
			delta = delta/@scaleNode.scaleX
			@crossNode.position += delta
			@xcross.positionY -= delta.y
			@ycross.positionX -= delta.x

		itemChoosed = (itemData)->
			if itemData
				switch itemData.typeName
					when "PlatformWorld","UILayer","Camera","Layer","World"
						@cross.transformTarget = nil
						@cross.position = editor.origin
						@cross\perform @fadeCross
					when "Body"
						item = editor\getItem itemData
						if item.children
							pos = item.children[1].position
							@cross.position = pos
							@cross.transformTarget = item
							@cross\perform @fadeCross
							if item.parent ~= editor.items.UI
								parentData = editor\getData item.parent
								pos += parentData.offset
								emit "Scene.ViewArea.MoveTo",editor.origin-pos
					else
						item = editor\getItem itemData
						pos = itemData.position
						@cross.position = pos
						@cross.transformTarget = item.parent
						@cross\perform @fadeCross
						if item.parent ~= editor.items.UI
							parentData = editor\getData item.parent
							pos += parentData.offset
							emit "Scene.ViewArea.MoveTo",editor.origin-pos
		@gslot "Scene.ViewPanel.Pick",itemChoosed
		@gslot "Scene.ViewPanel.Select",itemChoosed

		@gslot "Scene.DataLoaded",(sceneData)->
			scaleNode = @scaleNode
			lastScene = nil
			if #scaleNode.children == 2
				lastScene = scaleNode.children[2]
				scaleNode\removeChild lastScene
			if sceneData
				effectFilename = editor.gameFullPath..editor.graphicFolder.."list.effect"
				oCache.Effect\load effectFilename if oContent\exist effectFilename
				newScene = sceneData!
				scaleNode\addChild newScene
				if lastScene
					newScene.camera.position = lastScene.camera.position
