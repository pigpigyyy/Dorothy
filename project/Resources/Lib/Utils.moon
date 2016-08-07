Dorothy!
{:type,:tostring,:setmetatable,:table,:rawset,:rawget} = _G
import insert,remove,concat from table
import floor,ceil from math

StructToString = =>
	content = [(type(item) == 'string' and '\"'..item..'\"' or tostring item) for item in *@]
	"{"..(concat content,',').."}"
StructDefMeta = {
	set:(index,item)=>
		index += 1
		if 1 <= index and index <= #@
			@[index] = item
			notify = rawget @,"__notify"
			if notify
				notify "Changed",index-1,item
		else
			error "Access index out of range."
	get:(index)=>
		if 1 <= index and index < #@
			@[index+1]
		else
			nil
	insert:(argA,argB)=>
		local item
		local index
		if argB
			item = argB
			index = argA+1
			if index > #@
				index = #@+1
			elseif index < 1
				index = 1
		else
			item = argA
			index = #@+1
		insert @,index,item
		notify = rawget @,"__notify"
		if notify
			notify "Added",index-1,item
	removefor:(arg)=>
		local item,index
		for i = 2,#@
			if @[i] == arg
				item = arg
				index = i
				remove @,index
				break
		if index
			notify = rawget @,"__notify"
			if notify
				notify "Removed",index-1,item
	remove:(index)=>
		length = #@
		item = if index
			if 0 < index and index < length
				index += 1
				remove @,index
			else
				nil
		else
			if length > 1
				index = length
				remove @,index
			else
				nil
		if item
			notify = rawget @,"__notify"
			if notify
				notify "Removed",index-1,item
	clear:=>
		notify = rawget @,"__notify"
		for index = #@,2,-1
			item = remove @
			if notify
				notify "Removed",index-1,item
	each:(handler)=>
		for index = 2,#@
			handler @[index],index-1
	__call:(data)=>
		item = {@__name}
		if data
			for k,v in pairs data
				key = @[k]
				if key
					item[key] = v
				else
					item[k+1] = v
		setmetatable item,@
		item
	__tostring:=>
		content = {}
		for k,v in pairs @
			if "number" == type v
				content[v-1] = k
		if #content > 1
			concat {"Struct.",@__name,"{\"",concat(content,"\",\""),"\"}"}
		else
			"Struct."..@__name.."()"
}
StructDefs = {}
local StructHelper
StructHelper = {
	__call:(...)=>
		structName = @path..@name
		local tupleDef
		tupleDef = setmetatable {
			__name:structName
			__index:(key)=>
				item = tupleDef[key]
				if item
					rawget @,item
				elseif key == "count"
					#@-1
				else
					StructDefMeta[key]
			__newindex:(key,value)=>
				index = tupleDef[key]
				if index
					rawset @,index,value
					notify = rawget @,"__notify"
					if notify
						notify key,value
				elseif key ~= "__notify"
					error "Access invalid key \"#{ key }\" for #{ tupleDef }"
				else
					rawset @,"__notify",value
			__tostring:StructToString
		},StructDefMeta
		for i = 1,select("#",...)
			name = select i,...
			tupleDef[name] = i+1
		StructDefs[structName] = tupleDef
		tupleDef
	__index:(key)=>
		@path ..= @name
		@path ..= "."
		@name = key
		@
	__tostring:=>
		content = {}
		path = @path..@name.."."
		length = #path
		i = 1
		for k,v in pairs StructDefs
			if k\find path,1,true
				content[i] = tostring v
				i += 1
		concat content,"\n"
}
setmetatable StructHelper,StructHelper
local Struct
StructLoad = (data)->
	if "table" == type data
		setmetatable data,Struct[data[1]]
		for item in *data
			StructLoad item
Struct = setmetatable {
	load:(arg)=>
		data = switch type arg
			when "string"
				if arg\sub(1,6) ~= "return"
					arg = "return "..arg
				(loadstring arg)!
			when "table"
				arg
		StructLoad data
		data
},{
	__index:(name)=>
		def = StructDefs[name]
		if not def
			StructHelper.name = name
			StructHelper.path = ""
			def = StructHelper
		def
	__tostring:=>
		concat [tostring v for _,v in pairs StructDefs],"\n"
}

Set = (list)-> {item,true for item in *list}

CompareTable = (olds,news)->
	itemsToDel = {}
	itemSet = Set news
	for item in *olds
		if not itemSet[item]
			insert itemsToDel,item
	itemsToAdd = {}
	itemSet = Set olds
	for item in *news
		if not itemSet[item]
			insert itemsToAdd,item
	return itemsToAdd,itemsToDel

Round = (val)->
	if type(val) == "number"
		val > 0 and floor(val+0.5) or ceil(val-0.5)
	else
		oVec2 val.x > 0 and floor(val.x+0.5) or ceil(val.x-0.5),
			val.y > 0 and floor(val.y+0.5) or ceil(val.y-0.5)

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
					insert result,path..file
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
	:Struct
}
