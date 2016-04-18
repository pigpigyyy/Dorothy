Dorothy!
CCScene = require "Lib.CCSceneEx"
oContent\addSearchPath "SceneEditor"

Editor = require "Scene.Editor"
CCScene\add "sceneEditor",with Editor!
	.lastScene = CCDirector.currentScene
CCScene\forward "sceneEditor"
