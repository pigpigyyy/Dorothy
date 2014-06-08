-- authors: Luxinia Dev (Eike Decker & Christoph Kubisch)
---------------------------------------------------------
local ide = ide
local statusBar = ide.frame.statusBar

-- api loading depends on Lua interpreter
-- and loaded specs

------------
-- API

local function newAPI(api)
	api = api or {}
	for i in pairs(api) do
		api[i] = nil
	end
	-- tool tip info and reserved names
	api.tip = {
		staticnames = {},
		keys = {},
		finfo = {},
		finfoclass = {},
		shortfinfo = {},
		shortfinfoclass = {},
	}
	-- autocomplete hierarchy
	api.ac = {
		childs = {},
	}

	return api
end

local apis = {
	none = newAPI(),
	lua = newAPI(),
}

function GetApi(apitype)
	return apis[apitype] or apis["none"]
end

----------
-- API loading

local function addAPI(apifile,only,subapis,known) -- relative to API directory
	local ftype, fname = apifile:match("api[/\\]([^/\\]+)[/\\](.*)%.")
	if not ftype or not fname then
		DisplayOutputLn(TR("The API file must be located in a subdirectory of the API directory."))
		return
	end
	if ((only and ftype ~= only) or (known and not known[ftype])) then 
		return 
	end
	if (subapis and not subapis[fname]) then return end

	local fn,err = loadfile(apifile)
	if err then
		DisplayOutputLn(TR("Error while loading API file: %s"):format(err))
		return
	end
	local env = apis[ftype] or newAPI()
	apis[ftype] = env
	env = env.ac.childs
	local suc,res = pcall(function()return fn(env) end)
	if (not suc) then
		DisplayOutputLn(TR("Error while processing API file: %s"):format(res))
	elseif (res) then
		local function gennames(tab,prefix)
			for i,v in pairs(tab) do
				v.classname = (prefix and (prefix..".") or "")..i
				if(v.childs) then
					gennames(v.childs,v.classname)
				end
			end
		end
		gennames(res)
		for i,v in pairs(res) do
			env[i] = v
		end
	end
end

local function loadallAPIs (only,subapis,known)
	for _, file in ipairs(FileSysGetRecursive("api", true, "*.lua")) do
		if not file:match(string_Pathsep.."$") then addAPI(file,only,subapis,known) end
	end
end

---------
-- ToolTip and reserved words list
-- also fixes function descriptions

local tipwidth = math.max(20, ide.config.acandtip.width or 60)
local widthmask = ("[^\n]"):rep(tipwidth-10)..("[^\n]?"):rep(10)
local function fillTips(api,apibasename,apiname)
	local apiac = api.ac
	local tclass = api.tip

	tclass.staticnames = {}
	tclass.keys = {}
	tclass.finfo = {}
	tclass.finfoclass = {}
	tclass.shortfinfo = {}
	tclass.shortfinfoclass = {}

	local staticnames = tclass.staticnames
	local keys = tclass.keys
	local finfo = tclass.finfo
	local finfoclass = tclass.finfoclass
	local shortfinfo = tclass.shortfinfo
	local shortfinfoclass = tclass.shortfinfoclass

	local function traverse (tab,libname)
		--DisplayOutputLn(tab, libname)
		if tab.type == "class" or tab.type == "lib" then
			if not finfoclass[libname] then finfoclass[libname] = {} end
			if not shortfinfoclass[libname] then shortfinfoclass[libname] = {} end
			-- fix description
			-- build info
			local inf = tab.description
			local sentence = inf:match("^(.-)%. ?\n")
			local infshort = (sentence and sentence.."..." or inf)
			finfoclass[libname]._desc_ = inf
			shortfinfoclass[libname]._desc_ = infshort
		end
		if not tab.childs then return end
		for key,info in pairs(tab.childs) do
			local fullname
			if not libname or libname == "" then
				fullname = key
			else
				fullname = libname.."."..key
			end
			traverse(info, fullname)
			if info.type == "function" or info.type == "method" or info.type == "value" then
				local libstr = libname ~= "" and libname.."." or ""
				local desc = info.description
				-- fix description
				local frontname = (info.returns or "(?)").." "
				if info.className then
					frontname = frontname..info.className.."."
					if info.type == "value" and info.className ~= libname then
						desc = "[From "..info.className.."]"..desc
					end
				else
					frontname = frontname..libstr
				end
				frontname = frontname..key.." "..(info.args or "(?)")
				
				frontname = frontname
					:gsub("\n"," ")
					:gsub("\t","")
					:gsub("("..widthmask..")[ \t]([^%)])","%1\n %2")

				desc = (desc or "")
					:gsub("\n\n","<br>"):gsub("\n"," "):gsub("<br>","\n")
					:gsub("[ \t]+"," ")
					:gsub("("..widthmask..") ","%1\n")

				-- build info
				local inf = (info.type == "value" and "" or frontname.."\n")
					..desc
				local sentence = desc:match("^(.-)%. ?\n")
				local infshort = (info.type == "value" and "" or frontname.."\n")
					..(sentence and sentence.."..." or desc)
				local infshortbatch = (info.returns and info.args) and frontname or infshort

				-- add to infoclass
				if not finfoclass[libname] then finfoclass[libname] = {} end
				if not shortfinfoclass[libname] then shortfinfoclass[libname] = {} end
				finfoclass[libname][key] = inf
				shortfinfoclass[libname][key] = infshort
				
				if info.type ~= "method" and libname == "" then
					-- add to info
					if not finfo[key] or #finfo[key] < 200 then
						if finfo[key] then finfo[key] = finfo[key] .. "\n\n"
						else finfo[key] = "" end
						finfo[key] = finfo[key] .. inf
					elseif not finfo[key]:match("\n %(%.%.%.%)$") then
						finfo[key] = finfo[key].."\n (...)"
					end

					-- add to shortinfo
					if not shortfinfo[key] or #shortfinfo[key] < 200 then
						if shortfinfo[key] then shortfinfo[key] = shortfinfo[key] .. "\n"
						else shortfinfo[key] = "" end
						shortfinfo[key] = shortfinfo[key] .. infshortbatch
					elseif not shortfinfo[key]:match("\n %(%.%.%.%)$") then
						shortfinfo[key] = shortfinfo[key].."\n (...)"
					end
				end
			end
			if info.type == "keyword" then
				keys[key] = true
			end
			staticnames[key] = true
		end
	end
	traverse(apiac,apibasename)
end

local function generateAPIInfo(only)
	for i,api in pairs(apis) do
		if ((not only) or i == only) then
			fillTips(api,"",i)
		end
	end
end

function UpdateAssignCache(editor)
	if (editor.spec.typeassigns and not editor.assignscache) then
		local assigns = editor.spec.typeassigns(editor)
		editor.assignscache = {
			assigns = assigns,
			line = editor:GetCurrentLine(),
		}
	end
end

-- assumes a tidied up string (no spaces, braces..)
local function resolveAssign(editor,tx)
	local ac = editor.api.ac
	local assigns = editor.assignscache and editor.assignscache.assigns
	local function getclass(tab,a,k)
		local key,rest = a:match("([%w_]+)[%.:](.*)")
		--DisplayOutputLn("content:",a,"key:",key,"rest:",rest)
		key = tonumber(key) or key -- make this work for childs[0]
		if rest then
			local nextKey, nextRest = rest:match("([%w_]+)[%.:](.*)")
			--DisplayOutputLn("nextRest:",nextRest)
			if nextRest then
				local keyTab = tab.childs[key]
				if keyTab and keyTab.childs then
					local itemTab = keyTab.childs[nextKey]
					if itemTab and itemTab.typeName then
						return getclass(tab,itemTab.typeName.."."..nextRest,itemTab.typeName)
					end
				end
			end
		end
		if (key and rest and tab.childs and tab.childs[key]) then
			return getclass(tab.childs[key],rest,key)
		end
		--if tab.valuetype then
		--	return getclass(ac,tab.valuetype.."."..a,tab.valuetype)
		--end
		if tab.typeName then
			newTab = ac.childs[tab.typeName]
			if newTab then return newTab,a,tab.typeName end
		end
		return tab,a,k
	end
	-- DisplayOutputLn("start",ac.childs["oModel"].childs["none"].returns)
	local c
	if (assigns) then
		-- find assign
		local change = true
		while (change) do
			local classname = nil
			c = ""
			change = false
			for w,s in tx:gmatch("([%w_]+)([%.:]?)") do
				local old = classname
				-- check if what we have so far can be matched with a class name
				-- this can happen if it's a reference to a value with a known type
				classname = classname or assigns[c..w]
				--DisplayOutputLn(0,classname,assigns[c..w],c..w)
				if classname then
					classname = classname:gsub("([%w_]+)[({]*[%w_]*","%1") or classname
					--DisplayOutputLn(1,classname)
				end
				if (s ~= "" and old ~= classname) then
					c = classname..s
					change = true
				else
					c = c..w..s
				end
			end
			-- abort if the same or recursive value is returned; no need to continue.
			-- this can happen after typing "smth = smth:new(); smth:" or
			-- "line = line:gsub(...); line:" as the current algorithm attempts to
			-- replace "line" with the value that also includes "line"
			if change and c:find("^"..(tx:gsub("[.:]","[.:]"))) then break end
			tx = c
		end
	else
		c = tx
	end
	-- then work from api
	return getclass(ac,c,nil)
end

function GetTipInfo(editor, content, short, fullmatch)
	if not content then return end
	content = string.gsub(content, ":", ".")
	content = string.gsub(content, "%(", "")
	--local find = string.find(content,"\(")
	--if find then content = string.sub(content, 1, string.len(content)-1) end
	local caller = content:match("([%w_]+)%(?%s*$")
	local class = caller and (string.find(content,".") and string.sub(content,1,string.len(content)-string.len(caller)-1) or "") or ""
	--DisplayOutputLn("CONTENT：",content,"CALLER:",caller,"CLASS:",class)
	--content:match("([%w_]+)[%.:]"..caller.."%(?%s*$") or ""
	local tip = editor.api.tip
	if caller and class == "" then
		class = caller
	end
	local ac = editor.api.ac
	local tab = ac.childs[class]
	local typeName
	if not tab or tab.type ~= "function" then
		tab,_,typeName = resolveAssign(editor,class..".")
	end
	--DisplayOutputLn(typeName,tab.type)
	if typeName then
		if class == caller then
			caller = typeName
			content = typeName
		end
		class = typeName
	end
	--DisplayOutputLn("content:",content,"class:",class,"caller:",caller,"short:",short)
	local classtab = short and tip.shortfinfoclass or tip.finfoclass
	local funcstab = short and tip.shortfinfo or tip.finfo
	UpdateAssignCache(editor)

	if (editor.assignscache and not (class and classtab[class])) then
		local assigns = editor.assignscache.assigns
		class = assigns and assigns[class] or class
	end
	local res = (caller and (class and classtab[class]) and classtab[class][caller]
		or (not fullmatch and funcstab[caller] or nil))
	--DisplayOutputLn(funcstab[caller])
	-- some values may not have descriptions (for example, true/false);
	-- don't return empty strings as they are displayed as empty tooltips.
	local final = res and #res > 0 and res or nil

	return final or (classtab[content] and classtab[content]._desc_ or nil)
end

local function reloadAPI(only,subapis)
	newAPI(apis[only])
	loadallAPIs(only,subapis)
	generateAPIInfo(only)
end

function ReloadLuaAPI()
	local interpreterapi = ide.interpreter
	interpreterapi = interpreterapi and interpreterapi.api
	if (interpreterapi) then
		local apinames = {}
		for _, v in ipairs(interpreterapi) do
			apinames[v] = true
		end
		interpreterapi = apinames
	end
	reloadAPI("lua",interpreterapi)
end

do
	local known = {}
	for _, spec in pairs(ide.specs) do
		if (spec.apitype) then
			known[spec.apitype] = true
		end
	end
	-- by defaul load every known api except lua
	known.lua = false

	loadallAPIs(nil,nil,known)
	generateAPIInfo()
end

-------------
-- Dynamic Words
dywordtable = {}
local function getDynamicEntries(id)
	dywordtable[id] = dywordtable[id] or {dywordentries = {},dynamicwords = {}}
	return dywordtable[id].dywordentries, dywordtable[id].dynamicwords
end

local function addDynamicWord(api,word,id)
	local dywordentries, dynamicwords = getDynamicEntries(id)
	
end

local function addDynamicWord(api,word,id)
	local dywordentries, dynamicwords = getDynamicEntries(id)
	--if api.tip.keys[word] or api.tip.staticnames[word] then return end
	local cnt = dywordentries[word]
	if cnt then
		dywordentries[word] = cnt + 1
		--DisplayOutputLn("+", word, dywordentries[word])
		return
	end
	dywordentries[word] = 1
	local wlow = word:lower()
	for i=0,#word do
		local k = wlow : sub (1,i)
		dynamicwords[k] = dynamicwords[k] or {}
		table.insert(dynamicwords[k], word)
	end
	--DisplayOutputLn("+", word, dywordentries[word])
end

local function removeDynamicWord(api,word,id)
	local dywordentries, dynamicwords = getDynamicEntries(id)
	--if api.tip.keys[word] or api.tip.staticnames[word] then return end
	local cnt = dywordentries[word]
	if not cnt then return end

	if (cnt == 1) then
		dywordentries[word] = nil
		for i=0,#word do
			local wlow = word:lower()
			local k = wlow : sub (1,i)
			local page = dynamicwords[k]
			if page then
				local cnt = #page
				for n=1,cnt do
					if page[n] == word then
						if cnt == 1 then
							dynamicwords[k] = nil
						else
							table.remove(page,n)
						end
						break
					end
				end
			end
		end
	else
		dywordentries[word] = cnt - 1
	end
	
	--DisplayOutputLn("-", word, dywordentries[word])
end

function DynamicWordsReset(editor)
	local id = editor:GetId()
	getDynamicEntries(id)
	dywordtable[id].dywordentries = {}
	dywordtable[id].dynamicwords = {}
end

function DynamicWordsAdd(ev,editor,content)
	if ide.config.acandtip.nodynwords then return end
	for word in content:gmatch("[%.:]?%s*([a-zA-Z_]+[a-zA-Z_0-9]+)") do
		--DisplayOutputLn(word)
		addDynamicWord(editor.api,word,editor:GetId())
	end
end

function DynamicWordsRem(ev,editor,content)
	if ide.config.acandtip.nodynwords then return end
	for word in content:gmatch("[%.:]?%s*([a-zA-Z_]+[a-zA-Z_0-9]+)") do
		--DisplayOutputLn(word)
		removeDynamicWord(editor.api,word,editor:GetId())
	end
end

function DynamicWordsRemoveAll(editor)
	DynamicWordsRem("close",editor,editor:GetText())
end

------------
-- Final Autocomplete
local OP_TYPE_NONE = 0
local OP_TYPE_COLON = 1
local OP_TYPE_DOT = 2

local cachemain = {}
local cachemethod = {}
local cacheClassMethod = {}
local cacheClassMain = {}
local laststrategy
local lastmethod
local function getAutoCompApiList(childs,fragment,opType,isClass)
	fragment = fragment:lower()
	local strategy = ide.config.acandtip.strategy
	if (laststrategy ~= strategy) then
		cachemain = {}
		cachemethod = {}
		laststrategy = strategy
	end

	local cache = (opType == OP_TYPE_COLON) and (isClass and cacheClassMethod or cachemethod) or (isClass and cacheClassMain or cachemain)

	if (strategy == 2) then
		local wlist = cache[childs]
		if not wlist then
			wlist = " "
			--DisplayOutput("opType:", opType, "\n")
			for i,v in pairs(childs) do
				if not v.hide and ((v.static and isClass) or (not v.static and not isClass)) then
					-- if a:b typed, then value (type == "value") not allowed
					-- if a.b typed, then method (type == "method") not allowed
					if v.type and
						((opType == OP_TYPE_DOT and v.type ~= "method") or
							(opType == OP_TYPE_COLON and v.type == "method") or
								(opType == OP_TYPE_NONE)) then
						wlist = wlist..i.." "
					end
				end
			end
			cache[childs] = wlist
		end
		local ret = {}
		local g = string.gmatch
		local pat = fragment ~= "" and ("%s("..fragment:gsub(".",
				function(c)
					local l = c:lower()..c:upper()
					return "["..l.."][%w_]*"
				end)..")") or "([%w_]+)"
		pat = pat:gsub("%s","")
		for c in g(wlist,pat) do
			table.insert(ret,c)
		end
		
		return ret
	end

	if cache[childs] then
		return cache[childs][fragment]
	end

	local t = {}
	cache[childs] = t

	local sub = strategy == 1
	for key,v in pairs(childs) do
		if not v.hide and ((v.static and isClass) or (not v.static and not isClass)) then
			-- if a:b typed, then value (type == "value") not allowed
			-- if a.b typed, then method (type == "method") not allowed
			if v.type and
			((opType == OP_TYPE_DOT and v.type ~= "method") or
				(opType == OP_TYPE_COLON and v.type == "method") or
					(opType == OP_TYPE_NONE)) then
				local used = {}
				--
				local kl = key:lower()
				for i=0,#key do
					local k = kl:sub(1,i)
					t[k] = t[k] or {}
					used[k] = true
					table.insert(t[k],key)
				end
				if (sub) then
					-- find camel case / _ separated subwords
					-- glfwGetGammaRamp -> g, gg, ggr
					-- GL_POINT_SPRIT -> g, gp, gps
					local last = ""
					for ks in string.gmatch(key,"([A-Z%d]*[a-z%d]*_?)") do
						local k = last..(ks:sub(1,1):lower())
						last = k
						t[k] = t[k] or {}
						if (not used[k]) then
							used[k] = true
							table.insert(t[k],key)
						end
					end
				end
			end
		end
	end
	return cache[childs][fragment]
end

function ClearAutoCompCache()
	cache = {}
end

-- make syntype dependent
function CreateAutoCompList(editor,key)
	local api = editor.api
	local tip = api.tip
	local ac = api.ac
	local colon = key:match(":[^:%.]*$") ~= nil
	local colonOrDot = key:match("[:.]") ~= nil
	local opType
	if not colonOrDot then
		opType = OP_TYPE_NONE
	else
		if colon then
			opType = OP_TYPE_COLON
		else
			opType = OP_TYPE_DOT
		end
	end
	-- ignore keywords
	if tip.keys[key] then return end
	
	UpdateAssignCache(editor)
	local tab,rest,typeName = resolveAssign(editor,key)
	if rest == "" and typeName == nil then
		return ""
	end
	local progress = tab and tab.childs
	statusBar:SetStatusText(progress and tab.classname or "",1)
	if not (progress) then return end

	if (tab == ac) then
		local _, krest = rest:match("([%w_]+)[:%.]([%w_]+)%s*$")
		if (krest) then
			if (#krest < 3) then return end
			tab = tip.finfo
			rest = krest:gsub("[^%w_]","")
		else
			rest = rest:gsub("[^%w_]","")
		end
	else
		rest = rest:gsub("[^%w_]","")
	end

	local last = key:match("([%w_]+)%s*$")

	-- build dynamic word list
	-- only if api search couldnt descend
	-- ie we couldnt find matching sub items
	local dywordentries, dynamicwords = getDynamicEntries(editor:GetId())
	local dw = ""
	local list = nil
	if (tab == ac and last and #last >= (ide.config.acandtip.startat or 2)) then
		last = last:lower()
		if dynamicwords[last] then
			list = dynamicwords[last]
			table.sort(list,function(a,b)
					local ma,mb = a:sub(1,#last)==last, b:sub(1,#last)==last
					if (ma and mb) or (not ma and not mb) then return a<b end
					return ma
				end)
			-- ignore if word == last and sole user
			for i,v in ipairs(list) do
				if (v:lower() == last and dywordentries[v] == 1) then
					table.remove(list,i)
					break
				end
			end
	
			local res = table.concat(list," ")
			dw = res ~= "" and " "..res or ""
		end
	end

	-- list from api
	local isLib = tab.type == "lib"
	local isClass = typeName ~= nil and typeName == key:sub(1,#typeName) and not isLib
	local apilist = getAutoCompApiList(tab.childs or tab,rest,(isLib and OP_TYPE_NONE or opType),isClass)
	if list and apilist then
		for _, v in ipairs(list) do
			for i, va in ipairs(apilist) do
				if v == va then
					table.remove(apilist, i)
					break
				end
			end
		end
	end
	
	local compstr = ""
	if apilist then
		if (#rest > 0) then
			local strategy = ide.config.acandtip.strategy
			if (strategy == 2 and #apilist < 128) then
				local pat = rest:gsub(".",function(c)
						local l = c:lower()..c:upper()
						return "["..l.."]([^"..l.." ]*)"
					end)

				local g = string.gsub
				table.sort(apilist,function(a,b)
						local ma,mb = 0,0
						g(a,pat,function(...)
								local l = {...}
								for _, v in ipairs(l) do
									ma = ma + ((v=="") and 0 or 1)
								end
							end)
						g(b,pat,function(...)
								local l = {...}
								for _, v in ipairs(l) do
									mb = mb + ((v=="") and 0 or 1)
								end
							end)

						if (ma == mb) then return a:lower()<b:lower() end
						return ma<mb
					end)
			else
				table.sort(apilist,function(a,b)
						local ma,mb = a:sub(1,#rest)==rest, b:sub(1,#rest)==rest
						if (ma and mb) or (not ma and not mb) then return a<b end
						return ma
					end)
			end
		elseif not isLib then
			table.sort(apilist,function(a,b)
					local className = tab.childs[a].className
					local levelA = className and ac.childs[className].level or tab.level
					className = tab.childs[b].className
					local levelB = className and ac.childs[className].level or tab.level
					if levelA == nil and levelB == nil then
						return true
					end
					if levelA > levelB then
						return true
					end
					if levelA < levelB then
						return false
					end
					return a < b
				end)
		end
		compstr = table.concat(apilist," ")
	end

	-- concat final, list complete first
	local li = (dw.." "..compstr)
	if li == " " then li = "" end
	return li ~= "" and (#li > 1024 and li:sub(1,1024).."..." or li)
end
