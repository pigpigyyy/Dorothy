Dorothy()
local Class = require("Class")
local TestBase = require("Dev.Test.TestBase")
local Set = require("moonscript.data").Set

return Class(TestBase,{
	run = function(self)
		local text = {}
		local realPrint = print
		local print = function(...)
			table.insert(text,table.concat({...},"\t"))
				table.insert(text,"\n")
		end

		local apiClass = {}
		local apiMember = {}
		local apiFunc = {}
		for cls,item in pairs(builtin) do
			local t = tolua.type(item)
			if t == "function" then
				apiFunc[cls] = true
			elseif cls ~= "lpeg" then
				if type(item) == "userdata" then
					item = getmetatable(item)
				end
				apiClass[cls] = true
				if type(item[4]) == "table" then
					for field,_ in pairs(item[4]) do
						apiMember[field] = true
					end
				end
				if type(item) == "table" then
					for k,_ in pairs(item) do
						apiMember[k] = true
					end
				end
			end
		end

		local fields = {}
		local classOrFunc = {
			CCArray = 100,
		}
		local filter = Set {".","..","luaminify","moonscript"}
		local function stat(dir)
			local entries = oContent:getEntries(dir,true)
			for _,item in ipairs(entries) do
				local entry = dir.."/"..item
				if not filter[item] then
					stat(entry)
				end
			end
			entries = oContent:getEntries(dir,false)
			for _,item in ipairs(entries) do
				local extension = string.match(item, "%.([^%.\\/]*)$")
				if extension == "lua" then
					local entry = dir.."/"..item
					local codes = oContent:loadFile(entry)
					for cls in codes:gmatch("(%w+)[%(%.%:]") do
						if cls ~= "builtin" and cls ~= "_G" then
							classOrFunc[cls] = classOrFunc[cls] or 0
							classOrFunc[cls] = classOrFunc[cls] + 1
						end
					end
					for fld in codes:gmatch("%.(%w+)") do
						fields[fld] = fields[fld] or 0
						fields[fld] = fields[fld] + 1
					end
				end
			end
		end

		stat(".")

		local resultClass = {}
		--print("----- CLASS -----")
		for k,_ in pairs(classOrFunc) do
			if apiClass[k] then
				table.insert(resultClass,k)
			end
		end
		table.sort(resultClass,function(a,b) return classOrFunc[b] < classOrFunc[a] end)

		local resultMember = {}
		--print("----- METHOD -----")
		for k,v in pairs(classOrFunc) do
			if apiMember[k] then
				resultMember[k] = v
			end
		end

		--print("----- FIELD -----")
		for k,v in pairs(fields) do
			if apiMember[k] then
				resultMember[k] = v
			end
		end

		local resultFunction = {}
		--print("----- FUNCTION -----")
		for k,_ in pairs(classOrFunc) do
			if apiFunc[k] then
				table.insert(resultFunction,k)
			end
		end
		table.sort(resultFunction,function(a,b) return classOrFunc[b] < classOrFunc[a] end)

		local function printModule(pattern)
			for _,cls in ipairs(resultClass) do
				if cls:lower():match(pattern) then
					local item = builtin[cls]
					if type(item) == "userdata" then
						item = getmetatable(item)
					end
					local t = tolua.type(item)
					if t ~= "function" and cls ~= "lpeg" then
						print(cls,classOrFunc[cls],"n")
						local members = {}
						if type(item[4]) == "table" then
							for field,_ in pairs(item[4]) do
								if resultMember[field] then
									table.insert(members,field)
								end
							end
						end
						if type(item) == "table" then
							for k,_ in pairs(item) do
								if resultMember[k] then
									table.insert(members,k)
								end
							end
						end
						table.sort(members,function(a,b) return resultMember[b] < resultMember[a] end)
						for _,v in ipairs(members) do
							print("",v,resultMember[v],"n")
						end
					end
				end
			end
		end

		print("----- Cocos Class-----")
		printModule("^cc")
		print("----- Dorothy Class-----")
		printModule("^o")
		print("----- Other Class-----")
		printModule("^[^co][^c]")

		local function printFunc(pattern)
			for _,v in ipairs(resultFunction) do
				if v:lower():match(pattern) then
					print(v,classOrFunc[v],"n")
				end
			end
		end

		print("----- Cocos Function-----")
		printFunc("^cc")
		print("----- Dorothy Function-----")
		printFunc("^o")
		print("----- Other Function-----")
		printFunc("^[^co][^c]")

		local result = table.concat(text)
		realPrint(result)
		oContent:saveToFile("Progress.txt",result)
	end
})
