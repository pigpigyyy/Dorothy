Dorothy!
Class = unpack require "class"
ScenePanelView = require "View.Control.Item.ScenePanel"
MessageBox = require "Control.Basic.MessageBox"
Button = require "Control.Basic.Button"

-- [signals]
-- "Selected",(spriteStr)->
-- "Hide",->
-- [params]
Class
	__partial: =>
		itemNum = 3
		itemWidth = 120
		winSize = CCDirector.winSize
		while (itemWidth+10)*itemNum+10 > winSize.width and itemNum > 1
			itemNum = itemNum - 1
		args = {
			x:winSize.width/2
			y:winSize.height/2
			height:winSize.height*0.6
			width:10+itemNum*(itemWidth+10)
		}
		ScenePanelView args

	__init: =>
		itemWidth = 120
		itemHeight = 50

		if editor.currentScene
			@subtitle.visible = true
			@subtitle.text = "(Current: "..editor.currentScene\match("([^\\/]*)%..*$")..")"
			@subtitle.texture.antiAlias = false
		else
			@subtitle.visible = false
		@titleNode.height = 20+@title.height+10+if editor.currentScene
				@subtitle.height
			else
				0
		@title.positionY = @titleNode.height-10
		@subtitle.positionY = @titleNode.height-10-@title.height-10

		contentRect = CCRect.zero
		itemRect = CCRect.zero
		@scrollArea\slots "Scrolled",(delta)->
			contentRect\set 0,0,@scrollArea.width,@scrollArea.height
			@menu\eachChild (child)->
				child.position += delta
				{:positionX,:positionY,:width,:height} = child
				itemRect\set positionX-width/2,positionY-height/2,width,height
				child.visible = contentRect\intersectsRect itemRect -- reduce draw calls
  
		@scrollArea\slots "ScrollStart",->
			@menu.enabled = false

		@scrollArea\slots "ScrollTouchEnded",->
			@menu.enabled = true

		sceneFiles = {}
		visitResource = (path)->
			files = oContent\getEntries path,false
			sleep!
			for file in *files
				filename = path.."/"..file
				filename = filename\gsub(editor.gameFullPath,"")
				table.insert sceneFiles,filename
				sleep!
			folders = oContent\getEntries path,true
			for folder in *folders
				if folder ~= "." and folder ~= ".."
					visitResource path.."/"..folder

		@panel\schedule once ->
			scenePath = editor.sceneFullPath\gsub "[\\/]*$",""
			visitResource scenePath if oContent\exist scenePath
			for sceneFile in *sceneFiles
				sceneName = sceneFile\match "([^\\/]*)%..*$"
				if sceneName ~= "UI"
					@menu\addChild with Button {
							width:itemWidth
							height:itemHeight
							fontSize:16
							text:sceneName
						}
						\slots "Tapped",->
							editor.currentScene = sceneFile
							@hide!
			@menu\alignItems!

		@closeBtn\slots "Tapped",-> @hide!
		@show!

	show: =>
		@perform CCSequence {
			CCShow!
			oOpacity 0.3,0.6,oEase.OutQuad
		}
		@closeBtn.scaleX = 0
		@closeBtn.scaleY = 0
		@closeBtn\perform oScale 0.3,1,1,oEase.OutBack
		@quitBtn.scaleX = 0
		@quitBtn.scaleY = 0
		@quitBtn\perform oScale 0.3,1,1,oEase.OutBack
		@panel.opacity = 0
		@panel.scaleX = 0
		@panel.scaleY = 0
		@panel\perform CCSequence {
			CCSpawn {
				oOpacity 0.3,1,oEase.OutQuad
				oScale 0.3,1,1,oEase.OutBack
			}
			CCCall ->
				@scrollArea.touchEnabled = true
				@menu.enabled = true
				@opMenu.enabled = true
				--editor\updateSprites!
		}

	hide: =>
		@scrollArea.touchEnabled = false
		@menu.enabled = false
		@opMenu.enabled = false
		@quitBtn\perform oScale 0.3,0,0,oEase.InBack
		@closeBtn\perform oScale 0.3,0,0,oEase.InBack
		@panel\perform CCSpawn {
			oOpacity 0.3,0,oEase.OutQuad
			oScale 0.3,0,0,oEase.InBack
		}
		@perform CCSequence {
			oOpacity 0.3,0,oEase.OutQuad
			CCCall -> @parent\removeChild @
		}
