local Dorothy = require("dorothy")

local orderedNames = {}
local orderedDorothy = {}
for className,class in pairs(Dorothy) do
	orderedNames[class.index] = className
	orderedDorothy[class.index] = class
end

local result = ""
local function write(text)
	result = result..text.."\n"
end

local types = {}
for i=1,#orderedDorothy do
	local className = orderedNames[i]
	local class = orderedDorothy[i]
	write("## @brief "..class.description:gsub("\n","\n# "))
	write("class "..className.."("..(class.parents and class.parents[1] or "").."):\n")
	if class.childs then
		local apilist = {}
		for name,item in pairs(class.childs) do
			if not item.className or item.className == className then
				table.insert(apilist,name)
			end
		end
		table.sort(apilist,function(a,b)
			if (class.childs[a].args ~= nil) ~= (class.childs[b].args ~= nil) then
				return class.childs[b].args ~= nil
			end
			local className = class.childs[a].className
			local levelA = className and Dorothy[className].level or class.level
			className = class.childs[b].className
			local levelB = className and Dorothy[className].level or class.level
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
		for _,item in ipairs(apilist) do
			local returns = class.childs[item].returns
			local args = class.childs[item].args
			local argNames = ""
			if args then
				write("\t## @brief "..class.childs[item].description:gsub("\n","\n\t# "))
				for nextItem in args:gsub("%s",""):gmatch("(%w+:[%w<>]+)[=%w]*") do
					types[nextItem:match(":([%w<>]+)")] = true
					--if default then print("default:",default) end
					argNames = argNames..nextItem:match("(%w+):")..","
					--print(nextItem:match("(%w+):"),nextItem:match(":([%w<>]+)"))
					write("\t# @param "..nextItem:match("(%w+):").." "..nextItem:match(":([%w<>]+)"))
				end
				argNames = argNames:sub(1,-2)
			end
			if returns then
				for nextItem in returns:gsub("%s",""):gmatch("(%w+:[%w<>]+)") do
					types[nextItem:match(":([%w<>]+)")] = true
					write("\t# @return "..nextItem:match(":([%w<>]+)").." "..nextItem:match("(%w+):"))
				end
			end
			if args then
				if class.childs[item].static then
					write("\t@classmethod")
				end
				write("\tdef "..item.."(self"..(argNames == "" and "" or ",")..argNames.."):\n\t\tpass\n")
			else
				write("\t## @var "..item)
				write("\t# "..class.childs[item].description:gsub("\n","\n\t# ").."\n")
			end
		end
	end
end
--[[
write("\nreturns & args types:\n")
for name,_ in pairs(types) do
	write(name)
end
--]]
local file = io.open("Dorothy.py","w+")
file:write(result)
file:close()

