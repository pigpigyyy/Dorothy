Dorothy!
oContent\addSearchPath "SceneEditor"

_require = require
loaded = {}
reqFunc = (name)->
	result = package.loaded[name]
	if not result
		result = _require(name)
		table.insert(loaded,name)
	result
_G["require"] = reqFunc
builtin["require"] = reqFunc

Editor = require "Scene.Editor"

CCDirector\run with Editor!
	\slots "Exited",->
		_G["require"] = _require
		builtin["require"] = _require
		for name in *loaded
			package.loaded[name] = nil
