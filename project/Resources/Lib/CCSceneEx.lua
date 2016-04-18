--[[
CCScene:transition("cf",{"crossFade",1,CCOrientation.Left})
CCScene:add("firstScene",CCScene())
CCScene:run("firstScene","fadeIn")
CCScene:forward("firstScene","cf")
CCScene:back("crossFade")
CCScene:clearHistory()
--]]
local CCScene = require("CCScene")
local CCDirector = require("CCDirector")

local scenes = {}
local transitions = {}
local currentScene
local sceneStack = {}

function CCScene:transition(name,item)
	transitions[name] = item
end

function CCScene:add(name,scene)
	scenes[name] = scene
	scene:slot("Cleanup",function()
		scenes[name] = nil
	end)
end

function CCScene:remove(name)
	local scene = scenes[name]
	if scene then
		scene:cleanup()
		scenes[name] = nil
		return true
	end
	return false
end

local function runScene(scene,tname,cleanup)
	local data = tname and transitions[tname]
	local transition
	if data then
		local args = {data[2],scene}
		for i = 3,#data do
			args[i] = data[i]
		end
		transition = CCScene[data[1]](CCScene,unpack(args))
	end
	if CCDirector.sceneStackSize == 0 then
		CCDirector:run(transition or scene)
	else
		CCDirector:replaceScene(transition or scene,cleanup)
	end
end

function CCScene:run(sname,tname)
	local scene = scenes[sname]
	if scene then
		if #sceneStack > 0 then
			sceneStack = {}
		end
		currentScene = scene
		runScene(scene,tname,true)
	end
end

function CCScene:forward(sname,tname)
	local scene = scenes[sname]
	if scene then
		table.insert(sceneStack,currentScene)
		currentScene = scene
		runScene(scene,tname,false)
	end
end

function CCScene:back(tname)
	local lastScene = table.remove(sceneStack)
	if lastScene then
		currentScene = lastScene
		runScene(lastScene,tname,false)
	end
end

function CCScene:clearHistory()
	currentScene = CCDirector.currentScene
	sceneStack = {}
end

return CCScene
