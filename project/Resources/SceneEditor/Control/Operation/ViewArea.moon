Dorothy!
ViewAreaView = require "View.Control.Operation.ViewArea"

-- [no signals]
-- [no params]
Class ViewAreaView,
	__init: =>
		{:width,:height} = @
		@scene = nil
		isHide = false

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
		@slot "TouchBegan",(touches)->
			tap = true
			S = oVec2.zero
			V = oVec2.zero
			@schedule updateDragSpeed

		@slot "TouchMoved",(touches)->
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
				scale = editor.scale + delta
				if scale <= 0.5
					scale = 0.5
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
		@slot "TouchEnded",touchEnded
		@slot "TouchCancelled",touchEnded

		@gslot "Scene.ViewArea.Scale",(scale)->
			@scaleNode.scaleX = scale
			@scaleNode.scaleY = scale

		@gslot "Scene.ViewArea.ScaleTo",(scale)->
			@scaleNode\runAction oScale 0.5,scale,scale,oEase.OutQuad

		@gslot "Scene.ViewArea.MoveTo",-> @unschedule!

		@gslot "Scene.Camera.MoveTo",(pos)->
			pos = oVec2(width/2,height/2)-pos
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

		@gslot "Scene.Camera.Move",(delta)->
			@crossNode.position -= delta
			@xcross.positionY += delta.y
			@ycross.positionX += delta.x

		showFrame = (itemData)->
			item = editor\getItem itemData
			return unless item
			@frame.transformTarget = item.parent
			@frame.visible = true
			switch itemData.typeName
				when "Body"
					box = editor\getBodyBoundingBox item
					if box.width ~= 0 and box.height ~= 0
						@frame\set {
							oVec2 box.left-3,box.bottom-3
							oVec2 box.right+3,box.bottom-3
							oVec2 box.right+3,box.top+3
							oVec2 box.left-3,box.top+3
							oVec2 box.left-3,box.bottom-3
						}
					else @frame\set {}
				when "Effect"
					@frame\set {}
				else
					box = item.boundingBox
					@frame\set {
						oVec2 box.left-3,box.bottom-3
						oVec2 box.right+3,box.bottom-3
						oVec2 box.right+3,box.top+3
						oVec2 box.left-3,box.top+3
						oVec2 box.left-3,box.bottom-3
					}
		hideFrame = ->
			@frame.transformTarget = nil
			@frame.visible = false

		@gslot "Scene.ViewArea.Frame",(itemData)->
			switch itemData.typeName
				when "PlatformWorld","UILayer","Camera","Layer","World"
					return
			showFrame itemData

		@gslot "Scene.HideEditor",(args)->
			{hide} = args
			if hide
				@frame\perform oOpacity 0.5,0
				@cross\perform oOpacity 0.5,0
			else
				@frame\perform oOpacity 0.5,1
				@cross\perform oOpacity 0.5,1

		itemChoosed = (itemData)->
			if itemData
				if not isHide
					@cross\stopAllActions!
					@cross.visible = true
					@cross.opacity = 1
				switch itemData.typeName
					when "PlatformWorld","UILayer","Camera","Layer","World"
						@cross.transformTarget = nil
						@cross\unschedule!
						@cross.position = editor.offset
						@cross\perform @fadeCross
						hideFrame!
					when "Body"
						item = editor\getItem itemData
						pos = itemData.position
						if not isHide
							@cross.position = pos
							@cross.transformTarget = item.parent
							@cross\schedule -> @cross.position = itemData.position
							showFrame itemData
						if item.parent ~= editor.items.UI
							-- TODO: show "can`t add body" message here
							parentData = editor\getData item.parent
							editor\moveTo pos*parentData.zoom+parentData.offset
					else
						item = editor\getItem itemData
						pos = itemData.position
						if not isHide
							@cross.position = pos
							@cross.transformTarget = item.parent
							@cross\schedule -> @cross.position = itemData.position
							showFrame itemData
						if item.parent ~= editor.items.UI
							parentData = editor\getData item.parent
							editor\moveTo pos*parentData.zoom+parentData.offset
				else
					@cross.transformTarget = nil
					@cross.visible = false
					@cross\unschedule!
					hideFrame!
		@gslot "Scene.ViewPanel.Pick",itemChoosed
		@gslot "Scene.ViewPanel.Select",itemChoosed

		@gslot "Scene.DataLoaded",(sceneData)->
			@sceneNode\removeAllChildrenWithCleanup!
			@scene = nil
			if sceneData
				effectFilename = editor.gameFullPath..editor.graphicFolder.."list.effect"
				oCache.Effect\load effectFilename if oContent\exist effectFilename
				newScene = sceneData!
				@scene = newScene
				@sceneNode\addChild newScene
				with newScene.camera
					.scaleX = editor.scale
					.scaleY = editor.scale
					.position = editor.camPos
					\slot "CamMoved",(delta)->
						emit "Scene.Camera.Move",delta

		@gslot "Scene.Camera.Select",(subCam)->
			@touchEnabled = (subCam == nil)

		@gslot "Scene.HideEditor",(args)->
			{hide} = args
			return if isHide == hide
			isHide = hide
			@touchEnabled = not hide
			@unschedule! if @touchEnabled
