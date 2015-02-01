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

write("----")
write("--- The Dorothy Module")
write("-- @module Dorothy")
write("local M = {}\n")

local funcStr = ""

--local types = {}
for i=1,#orderedDorothy do
	local className = orderedNames[i]
	local class = orderedDorothy[i]
	write("--------")
	if class.type == "class" then
		if class.parents then
			write("-- Derived from @{"..class.parents[1].."}")
		end
		write("-- @type "..className)
		write("M."..className.." = {}\n")
		local classDesc = class.description
		for args in classDesc:gsub("%s+",""):gmatch("args%d*%-%-%(([%w:,%.{}|=]*)%)") do
			local newDesc = classDesc:gsub("args.+%)",""):gsub("class.-%.","")
			write("--- "..(newDesc:gsub("%s","") == "" and "ctor" or "ctor<br>\n -- "..newDesc:gsub("^[\n%s]+",""):gsub("\n","\n-- <br>\n-- ")))
			local argNames = ""
			for nextItem in args:gsub("%s",""):gmatch("([%w|]+:[%w{}|=%.]+)") do
				local default = nextItem:match("=(.+)")
				local nullable = nextItem:match("nil|")
				local typeName = nextItem:match(":([%w{}|]+)")
				local varName = nextItem:gsub("nil|",""):match("(%w+):")
				argNames = argNames..varName..","
				write("-- @tparam "..typeName.." "..varName..(default and " = "..default or "")..(nullable and " (optional)" or ""))
			end
			argNames = argNames:sub(1,-2)
			write("function "..className..":__init("..argNames..")\nend\n")
		end
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
				local desc = class.childs[item].description:gsub("\n\n","\n")
				if args then
					local newDesc = desc:gsub("args.+%)","")
					newDesc = newDesc:gsub("^[\n%s]+","")
					if class.childs[item].static then
						if newDesc:match("%[Class Method%]") then
							newDesc = newDesc:gsub("%[Class Method%]","")
							newDesc = newDesc:gsub("^[\n%s]+","")
						end
						newDesc = "[Class Method]"..(newDesc == "" and "" or "\n")..newDesc
					end
					write("--- "..(newDesc == "" and "method" or (not newDesc:match("%[Class Method%]") and "method<br>\n-- " or "")..newDesc:gsub("\n","\n-- <br>\n-- ")))
					for nextItem in args:gsub("%s",""):gmatch("([%w|]+:[%w{}|=%.]+)") do
						--types[nextItem:match(":([%w{}]+)")] = true
						local default = nextItem:match("=(.+)")
						local nullable = nextItem:match("nil|")
						local typeName = nextItem:match(":([%w{}|%.]+)")
						local varName = nextItem:gsub("nil|",""):match("(%w+):")
						argNames = argNames..varName..","
						write("-- @tparam "..typeName.." "..varName..(default and " = "..default or "")..(nullable and " (optional)" or ""))
					end
					argNames = argNames:sub(1,-2)
				else
					local varType = desc:match("%[([%w{}|]+)%]")
					local newDesc = desc:gsub("%[([%w{}|]+)%]","",1)
					local shortDesc = newDesc:match("%b[]") or ""
					local restDesc = newDesc:sub(#shortDesc+1,-1)
					if class.childs[item].static and not (shortDesc:match("%[Class Field%]") or shortDesc:match("%[Const%]")) then
						shortDesc = "[Class Field]"..shortDesc
					end
					write("--- "..varType.." "..shortDesc)
					write("-- @field "..item.." "..varType.." "..restDesc:gsub("\n","\n-- <br>\n-- "))
				end
				if returns then
					for nextItem in returns:gsub("%s",""):gmatch("(%w+:[%w{}|]+)") do
						--types[nextItem:match(":([%w{}]+)")] = true
						write("-- @treturn "..nextItem:match(":([%w{}|]+)").." "..nextItem:match("(%w+):"))
					end
				end
				if args then
					write("function "..className..(class.childs[item].type == "function" and "." or ":")..item.."("..argNames..")\nend\n")
				else
					write(className.."."..item.." = nil")
				end
				write("")
				if args then
					for args in desc:gsub("%s+",""):gmatch("args%d*%-%-%(([%w:,%.{}=]*)%)") do
						write("--- method")
						local argNames = ""
						for nextItem in args:gsub("%s",""):gmatch("([%w|]+:[%w{}=%.]+)") do
							local default = nextItem:match("=(.+)")
							local nullable = nextItem:match("nil|")
							local typeName = nextItem:match(":([%w{}%.]+)")
							local varName = nextItem:gsub("nil|",""):match("(%w+):")
							argNames = argNames..varName..","
							write("-- @tparam "..typeName.." "..varName..(default and " = "..default or "")..(nullable and " (optional)" or ""))
						end
						argNames = argNames:sub(1,-2)
						write("function "..className..(class.childs[item].type == "function" and "." or ":")..item.."("..argNames..")\nend\n")
					end
				end
			end
		end
	elseif class.type == "function" then
		local str = ""
		local function fwrite(text)
			str = str..text.."\n"
		end
		local modName = (className:sub(1,1) == "o" and "Dorothy_Functions" or "Cocos2dx_Functions")
		fwrite("-- @within "..modName)
		local returns = class.returns
		local args = class.args
		local argNames = ""
		local desc = class.description:gsub("\n\n","\n")

		local newDesc = desc:gsub("args.+%)","")
		newDesc = newDesc:gsub("^[\n%s]+","")
		if newDesc ~= "" then
			fwrite("-- <p>"..newDesc:gsub("\n","\n-- <br>\n-- ").."</p>")
		end
		for nextItem in args:gsub("%s",""):gmatch("([%w|]+:[%w{}|=%.]+)") do
			local default = nextItem:match("=(.+)")
			local nullable = nextItem:match("nil|")
			local typeName = nextItem:match(":([%w{}|%.]+)")
			local varName = nextItem:gsub("nil|",""):match("(%w+):")
			argNames = argNames..varName..","
			fwrite("-- @tparam "..typeName.." "..varName..(default and " = "..default or "")..(nullable and " (optional)" or ""))
		end
		argNames = argNames:sub(1,-2)
					
		for nextItem in returns:gsub("%s",""):gmatch("(%w+:[%w{}|]+)") do
			fwrite("-- @treturn "..nextItem:match(":([%w{}|]+)").." "..nextItem:match("(%w+):"))
		end

		fwrite("function M."..className.."("..argNames..")\nend\n")
		
		str = "--- <strong><a href=\"#"..modName:gsub("_Functions","_func").."\" style=\"font-weight: bold;\">function</a> "..className.." ("..argNames..")</strong><br>\n"..str
		funcStr = funcStr..str
	end
end

write(funcStr)
--[[
write("\nreturns & args types:\n")
for name,_ in pairs(types) do
	write(name)
end
--]]
local file = io.open("../../../../document/Dorothy/bin/doc.lua","w+")
file:write(result)
file:close()

