Dorothy!
ScenePanelView = require "View.Control.Item.ScenePanel"
MessageBox = require "Control.Basic.MessageBox"
InputBox = require "Control.Basic.InputBox"
Button = require "Control.Basic.Button"

local ScenePanel
ScenePanel = Class
	__partial: =>
		itemNum = 3
		itemWidth = 120
		itemHeight = 50
		winSize = CCDirector.winSize
		while (itemWidth+10)*itemNum+10 > winSize.width and itemNum > 1
			itemNum = itemNum - 1
		args = {
			x:winSize.width/2
			y:winSize.height/2
			height:winSize.height*0.6
			width:10+itemNum*(itemWidth+10)
		}
		@itemNum = itemNum
		@itemWidth = itemWidth
		@itemHeight = itemHeight
		ScenePanelView args

	__init: =>
		@slot "Show",-> @displayItems!
		@quitBtn\slot "Tapped",-> editor\emit "Quit"

	displayItems: =>
		@panel\schedule once ->
			{:width,:height} = @panel
			{:itemNum,:itemWidth,:itemHeight} = @
			xStart = itemWidth/2 -- left
			yStart = height -- top
			y = yStart
			-- create scene items
			if editor.game
				-- function to get scene files
				sceneFiles = {}
				visitResource = (path)->
					files = oContent\getEntries path,false
					sleep!
					for file in *files
						filename = path.."/"..file
						filename = filename\gsub(editor.gameFullPath,"")
						if filename\lower! ~= "scene/ui.scene"
							table.insert sceneFiles,filename
						sleep!
					folders = oContent\getEntries path,true
					for folder in *folders
						if folder ~= "." and folder ~= ".."
							visitResource path.."/"..folder
				-- create title for scene
				yStart = @createTitle "Select  Scene",editor.scene,yStart
				-- get scene files
				scenePath = editor.sceneFullPath\gsub "[\\/]*$",""
				visitResource scenePath if oContent\exist scenePath
				-- create button for scenes
				for i,sceneFile in ipairs sceneFiles
					sleep 0.05
					sceneName = sceneFile\match "([^\\/]*)%..*$"
					x = xStart+10+((i-1)%itemNum)*(itemWidth+10)
					y = yStart-itemHeight/2-10-math.floor((i-1)/itemNum)*60
					@createItem sceneName,x,y,itemWidth,itemHeight,->
						editor.currentSceneFile = sceneFile
						@hide!
				i = #sceneFiles
				x = xStart+10+(i%itemNum)*(itemWidth+10)
				y = yStart-itemHeight/2-10-math.floor(i/itemNum)*60
				button = @createItem "<NEW>",x,y,itemWidth,itemHeight,->
					with InputBox text:"New Scene Name"
						\slot "Inputed",(name)->
							return unless name
							if name == "" or name\match("[\\/|:*?<>\"%.]") or oContent\exist(editor.sceneFolder..name..".scene")
								MessageBox text:"Invalid Name!",okOnly:true
								return
							editor\newScene name
							@hide!
				button.color = ccColor3 0x80ff00
				if editor.scene
					x = xStart+10+((i+1)%itemNum)*(itemWidth+10)
					y = yStart-itemHeight/2-10-math.floor((i+1)/itemNum)*60
					button = @createItem "<DEL>",x,y,itemWidth,itemHeight,->
						with MessageBox text:"Delete Scene\n"..editor.scene
							\slot "OK",(result)->
								return unless result
								MessageBox(text:"Confirm This\nDeletion")\slot "OK",(result)->
									return unless result
									editor\deleteCurrentScene!
									@hide!
									thread ->
										sleep 0.3
										ScenePanel!
					button.color = ccColor3 0xff0080
				yStart = y - itemHeight/2
			-- function to get game folders
			games = {}
			visitResource = (path)->
				folders = oContent\getEntries path,true
				sleep!
				for folder in *folders
					if folder ~= "." and folder ~= ".."
						table.insert games,folder
			-- create title for game
			yStart = @createTitle "Select  Game",editor.game,yStart
			-- get game folders
			gamesPath = editor.gamesFullPath\gsub "[\\/]*$",""
			visitResource gamesPath if oContent\exist gamesPath
			-- create button for games
			for i,game in ipairs games
				sleep 0.05
				x = xStart+10+((i-1)%itemNum)*(itemWidth+10)
				y = yStart-itemHeight/2-10-math.floor((i-1)/itemNum)*60
				@createItem game,x,y,itemWidth,itemHeight,->
					editor.game = game
					@hide!
					thread ->
						sleep 0.3
						ScenePanel!
			i = #games
			x = xStart+10+(i%itemNum)*(itemWidth+10)
			y = yStart-itemHeight/2-10-math.floor(i/itemNum)*60
			button = @createItem "<NEW>",x,y,itemWidth,itemHeight,->
				with InputBox text:"New Game Name"
					\slot "Inputed",(name)->
						return unless name
						if name == "" or name\match("[\\/|:*?<>\"%.]") or oContent\exist(editor.gamesFullPath..name)
							MessageBox text:"Invalid Name!",okOnly:true
							return
						editor.game = name
						@hide!
						thread ->
							sleep 0.3
							ScenePanel!
			button.color = ccColor3 0x80ff00
			if editor.game
				x = xStart+10+((i+1)%itemNum)*(itemWidth+10)
				y = yStart-itemHeight/2-10-math.floor((i+1)/itemNum)*60
				button = @createItem "<DEL>",x,y,itemWidth,itemHeight,->
					with MessageBox text:"Delete Game\n"..editor.game
						\slot "OK",(result)->
							return unless result
							MessageBox(text:"Confirm This\nDeletion")\slot "OK",(result)->
								return unless result
								editor\deleteCurrentGame!
								@hide!
								thread ->
									sleep 0.3
									ScenePanel!
				button.color = ccColor3 0xff0080
			yStart = y - itemHeight/2
			@scrollArea.viewSize = CCSize width,height-yStart+10

	createTitle: (title,currentItem,yStart)=>
		y = yStart-20
		title = with CCLabelTTF title,"Arial",24
			.texture.antiAlias = false
			.color = ccColor3 0x00ffff
			.opacity = 0
			\runAction oOpacity 0.3,1
		title.position = oVec2 @panel.width/2,y-title.height/2
		@menu\addChild title
		yStart = y-title.height-(currentItem and -10 or 20)
		if currentItem
			y = yStart-20
			text = "(Current: "..currentItem..")"
			title = with CCLabelTTF text,"Arial",16
				.texture.antiAlias = false
				.color = ccColor3 0x00ffff
				.position = oVec2 @panel.width/2,y
				.opacity = 0
				\runAction oOpacity 0.3,1
			title.position = oVec2 @panel.width/2,y-title.height/2
			@menu\addChild title
			yStart = y-title.height-10
		yStart

	createItem: (name,x,y,width,height,callback)=>
		name = #name > 10 and name\sub(1,7).."..." or name
		button = with Button {
				x:x
				y:y
				width:width
				height:height
				fontSize:16
				text:name
			}
			.opacity = 0
			\runAction oOpacity 0.2,1
			\slot "Tapped",callback
		@menu\addChild button
		button

	show: =>
		@__base.show @
		@quitBtn.scaleX = 0
		@quitBtn.scaleY = 0
		@quitBtn\perform oScale 0.3,1,1,oEase.OutBack

	hide: =>
		@__base.hide @
		@quitBtn\perform oScale 0.3,0,0,oEase.InBack

ScenePanel
