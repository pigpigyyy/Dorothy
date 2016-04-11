Dorothy!
Set = (list)-> {item,true for item in *list}

CompareTable = (olds,news)->
	itemsToDel = {}
	itemSet = Set news
	for item in *olds
		if not itemSet[item]
			table.insert itemsToDel,item
	itemsToAdd = {}
	itemSet = Set olds
	for item in *news
		if not itemSet[item]
			table.insert itemsToAdd,item
	return itemsToAdd,itemsToDel

Round = (val)->
	if type(val) == "number"
		val > 0 and math.floor(val+0.5) or math.ceil(val-0.5)
	else
		oVec2 val.x > 0 and math.floor(val.x+0.5) or math.ceil(val.x-0.5),
			val.y > 0 and math.floor(val.y+0.5) or math.ceil(val.y-0.5)

local Path
Path =
	-- input: /aa/bb/file.XML
	-- output: xml
	getExtension:(filename)->
		extension = filename\match "%.([^%.\\/]*)$"
		extension = extension\lower! if extension
		extension

	-- input: /aa/bb/file.xml
	-- output: file
	getName:(filename)->
		filename\match("([^\\/]+)%.[^%.\\/]*$") or filename

	-- input: /aa/bb/file.xml
	-- output: file.xml
	getFilename:(filename)->
		filename\match "[^\\/]*$"

	-- input: /aa/bb/file.xml
	-- output: /aa/bb/
	getPath:(filename)->
		name = Path.getFilename filename
		filename\sub(1,-#name-1)

	getFiles:(path,filters)->
		filters = if "string" == type filters
			{[filters]:true}
		elseif filters
			Set filters
		else
			false
		files = oContent\getEntries path,false
		return for file in *files
			extension = Path.getExtension file
			if filters and not filters[extension]
				continue
			file

	getAllFiles:(rootPath,filters)->
		filters = if "string" == type filters
			{[filters]:true}
		elseif filters
			Set filters
		else
			false
		result = {}
		visitResource = (path)->
			currentPath = rootPath..path
			files = oContent\getEntries currentPath,false
			for file in *files
				extension = Path.getExtension file
				if not filters or filters[extension]
					table.insert result,path..file
			folders = oContent\getEntries currentPath,true
			for folder in *folders
				if folder ~= "." and folder ~= ".."
					visitResource path..folder.."/"
		visitResource ""
		result

	getFolders:(path)->
		folders = oContent\getEntries path,true
		return for folder in *folders
			if folder == "." or folder == ".."
				continue
			folder

	removeFolder:(rootPath)->
		visitResource = (path)->
			return unless oContent\exist path
			files = oContent\getEntries path,false
			for file in *files
				filename = path..file
				oContent\remove filename
			folders = oContent\getEntries path,true
			for folder in *folders
				if folder ~= "." and folder ~= ".."
					visitResource path..folder.."/"
			oContent\remove path
		visitResource rootPath

	isValid:(filename)-> not filename\match "[\\/|:*?<>\"]"

{
	:Set
	:CompareTable
	:Round
	:Path
}
