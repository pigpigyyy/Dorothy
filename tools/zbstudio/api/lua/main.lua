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
write("local _M = {}\n")

local types = {}
for i=1,#orderedDorothy do
	local className = orderedNames[i]
	local class = orderedDorothy[i]
	write("--- "..class.description:gsub("\n","\n-- "):gsub("class ",""))
	write("-- @type "..className)
	write("_M."..className.." = class()\n")
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
			write("--- "..class.childs[item].description:gsub("\n","\n-- "))
			if args then
				for nextItem in args:gsub("%s",""):gmatch("(%w+:[%w<>]+)[=%w]*") do
					types[nextItem:match(":([%w<>]+)")] = true
					--if default then print("default:",default) end
					argNames = argNames..nextItem:match("(%w+):")..","
					--print(nextItem:match("(%w+):"),nextItem:match(":([%w<>]+)"))
					write("-- @param "..nextItem:match("(%w+):").." "..nextItem:match(":([%w<>]+)"))
				end
				argNames = argNames:sub(1,-2)
			end
			if returns then
				for nextItem in returns:gsub("%s",""):gmatch("(%w+:[%w<>]+)") do
					types[nextItem:match(":([%w<>]+)")] = true
					write("-- @treturn "..nextItem:match(":([%w<>]+)").." "..nextItem:match("(%w+):"))
				end
			end
			if args then
				write("function "..className..":"..item.."("..argNames..") end\n")
			else
				write(className.."."..item.." = nil\n")
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
local file = io.open("result.lua","w+")
file:write(result)
file:close()

