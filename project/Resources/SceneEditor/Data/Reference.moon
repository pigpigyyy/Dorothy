Dorothy!
MessageBox = require "Control.Basic.MessageBox"
Model = require "Data.Model"

downRefMap = nil
upRefMap = nil
sceneRefMap = nil
updating = false

addSceneItemRef = (sceneName,item)->
	file = item.file
	if file
		file = file\gsub "|.*",""
		itemNames = sceneRefMap[file] or {}
		table.insert itemNames,item.name.." of "..sceneName
		sceneRefMap[file] = itemNames

removeSceneItemRef = (sceneName,item)->
	file = item.file
	if file
		file = file\gsub "|.*",""
		name = item.name.." of "..sceneName
		itemNames = sceneRefMap[file]
		if itemNames
			for i,itemName in ipairs itemNames
				if itemName = name
					table.remove itemNames,i
					break
			sceneRefMap[file] = nil if #itemNames == 0

addSceneRef = (filename)->
	data = Model.loadData filename
	sceneName = filename\match "[^\\/]*$"
	addChildren = (parentData)->
		if parentData.children
			for childData in *parentData.children
				addSceneItemRef sceneName,childData
				addChildren childData
	addChildren data

updateItemRef = (filename)->
	extension = filename\match "%.([^%.\\/]*)$"
	extension = extension\lower! if extension
	switch extension
		when "body"
			bodyData = dofile filename
			bodyData = editor.bodyEditor\transformData bodyData
			bodyFile = filename\gsub editor.gameFullPath,""
			for data in *bodyData
				face = data\get "Face"
				if face and face ~= ""
					face = face\gsub "|.*",""
					if not downRefMap[bodyFile]
						downRefMap[bodyFile] = {}
					table.insert downRefMap[bodyFile],face
					if not upRefMap[face]
						upRefMap[face] = {}
					table.insert upRefMap[face],bodyFile
		when "model"
			modelFile = filename\gsub editor.gameFullPath,""
			clipFile = oCache.Model\getClipFile filename
			clipFile = clipFile\gsub editor.gameFullPath,""
			if not downRefMap[modelFile]
				downRefMap[modelFile] = {}
			table.insert downRefMap[modelFile],clipFile
			if not upRefMap[clipFile]
				upRefMap[clipFile] = {}
			table.insert upRefMap[clipFile],modelFile
		when "clip"
			clipFile = filename\gsub editor.gameFullPath,""
			texFile = oCache.Clip\getTextureFile filename
			texFile = texFile\gsub editor.gameFullPath,""
			if not downRefMap[clipFile]
				downRefMap[clipFile] = {}
			table.insert downRefMap[clipFile],texFile
			if not upRefMap[texFile]
				upRefMap[texFile] = {}
			table.insert upRefMap[texFile],clipFile
		when "frame"
			frameFile = filename\gsub editor.gameFullPath,""
			file = io.open filename,"r"
			texFile = (file\read "*a")\match "<A A=\"([^\"]*)"
			file\close!
			frameFileName = filename\match "[^\\/]*$"
			texFile = (filename\sub(1,-#frameFileName-1)..texFile)\gsub editor.gameFullPath,""
			if not downRefMap[frameFile]
				downRefMap[frameFile] = {}
			table.insert downRefMap[frameFile],texFile
			if not upRefMap[texFile]
				upRefMap[texFile] = {}
			table.insert upRefMap[texFile],frameFile
		when "par"
			parFile = filename\gsub editor.gameFullPath,""
			file = io.open filename,"r"
			texFile = (file\read "*a")\match "<string>([^<]*)"
			file\close!
			if texFile ~= "__firePngData"
				if not downRefMap[parFile]
					downRefMap[parFile] = {}
				table.insert downRefMap[parFile],texFile
				if not upRefMap[texFile]
					upRefMap[texFile] = {}
				table.insert upRefMap[texFile],parFile
		when "scene"
			addSceneRef filename

routine = nil
update = ()->
	return if updating
	visitResource = (path)->
		files = oContent\getEntries path,false
		sleep!
		for file in *files
			filename = path.."/"..file
			updateItemRef filename
			sleep!
		folders = oContent\getEntries path,true
		for folder in *folders
			if folder ~= "." and folder ~= ".."
				visitResource path.."/"..folder
	updating = true
	routine = thread ->
		downRefMap = {}
		upRefMap = {}
		sceneRefMap = {}
		resPath = editor.gameFullPath\gsub "[\\/]*$",""
		visitResource resPath if oContent\exist resPath
		updating = false
		sleep 0.1
		collectgarbage!
		sleep 0.1
		oCache\removeUnused!
		routine = nil

stopUpdate = ()->
	oRoutine\remove routine if routine

isUpdating = ()->
	if updating
		MessageBox text:"Please Wait While\nUpdating Reference!",okOnly:true
	updating

getUpRefs = (item)->
	upRefs = if upRefMap[item]
		[it for it in *upRefMap[item]]
	else
		{}
	if sceneRefMap and sceneRefMap[item]
		for it in *sceneRefMap[item]
			table.insert upRefs,it
	upRefs

getDownRefs = (item)->
	downRefMap[item] or {}

refreshRef = (item)->
	downRefs = getDownRefs item
	for downRef in *downRefs
		upRefs = getUpRefs downRef
		for i = 1,#upRefs
			if upRefs[i] == item
				table.remove upRefs,i
				break
	downRefMap[item] = nil
	updateItemRef item

isRemovable = (item)->
	upRefs = getUpRefs item
	if upRefs and #upRefs > 0
		refStr = ""
		for ref in *upRefs do refStr ..= ref\match("[^\\/]*$").."\n"
		with MessageBox text:"Selected Item\n"..item\match("[^\\/]*$").."\nIs Referenced!",okOnly:true
			\slots "OK",->
				MessageBox text:"By\n"..refStr,okOnly:true
		false
	else
		true

removeRef = (item)->
	upRefs = getUpRefs item
	return false if #upRefs > 0
	downRefs = getDownRefs item
	for downRef in *downRefs
		upRefs = getUpRefs downRef
		for i = 1,#upRefs
			if upRefs[i] == item
				table.remove upRefs,i
				break
	downRefMap[item] = nil
	true

{
	:update
	:stopUpdate
	:getUpRefs
	:getDownRefs
	:isRemovable
	:removeRef
	:refreshRef
	:isUpdating
	:updateSceneRef
	:addSceneItemRef
	:removeSceneItemRef
}
