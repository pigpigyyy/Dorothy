Dorothy!
MessageBox = require "Control.Basic.MessageBox"

downRefMap = nil
upRefMap = nil

update = ()->
	visitResource = (path)->
		return unless oContent\exist path
		files = oContent\getEntries path,false
		sleep!
		for file in *files
			extension = file\match "%.([^%.\\/]*)$"
			extension = extension\lower! if extension
			switch extension
				when "body"
					filename = path.."/"..file
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
					filename = path.."/"..file
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
					filename = path.."/"..file
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
					filename = path.."/"..file
					frameFile = filename\gsub editor.gameFullPath,""
					file = io.open filename,"r"
					texFile = (file\read "*a")\match "<A A=\"([^\"]*)"
					file\close!
					texFile = (path.."/"..texFile)\gsub editor.gameFullPath,""
					if not downRefMap[frameFile]
						downRefMap[frameFile] = {}
					table.insert downRefMap[frameFile],texFile
					if not upRefMap[texFile]
						upRefMap[texFile] = {}
					table.insert upRefMap[texFile],frameFile
				when "par"
					filename = path.."/"..file
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
		folders = oContent\getEntries path,true
		for folder in *folders
			if folder ~= "." and folder ~= ".."
				visitResource path.."/"..folder

	thread ->
		downRefMap = {}
		upRefMap = {}
		resPath = editor.gameFullPath\gsub("[\\/]*$","")
		visitResource resPath
		sleep 0.5
		collectgarbage!
		sleep 0.5
		oCache\removeUnused!

getUpRefs = (item)->
	upRefMap[item] or {}

getDownRefs = (item)->
	downRefMap[item] or {}

isRemovable = (item)->
	upRefs = upRefMap[item]
	if upRefs and #upRefs > 0
		refStr = ""
		for ref in *upRefs do refStr ..= ref.."\n"
		with MessageBox text:"Selected Item\n"..item.."\nIs Referenced!",okOnly:true
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

{:update,:getUpRefs,:getDownRefs,:isRemovable,:removeRef}
