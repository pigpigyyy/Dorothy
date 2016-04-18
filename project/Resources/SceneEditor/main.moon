Dorothy!
CCScene = require "Lib.CCSceneEx"
oContent\addSearchPath "SceneEditor"

Editor = require "Scene.Editor"
CCScene\add "sceneEditor",with Editor!
	.lastScene = CCDirector.currentScene
	\slot "Quit",(nextScene)->
		CCScene\add "target",nextScene or .lastScene
		CCScene\run "target"

CCScene\forward "sceneEditor"
