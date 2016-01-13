Dorothy!
CCScene = require "Lib.CCSceneEx"
oContent\addSearchPath "SceneEditor"

Editor = require "Scene.Editor"
lastScene = CCDirector.currentScene
CCScene\add "sceneEditor",with Editor!
	\slot "Quit",->
		if lastScene
			CCDirector\replaceScene CCScene\crossFade(0.5,lastScene),true
			CCScene\clearHistory!
		else
			CCDirector\popScene!

CCScene\run "sceneEditor"
