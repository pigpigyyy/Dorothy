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

for i=1,#orderedDorothy do
	local className = orderedNames[i]
	local class = orderedDorothy[i]
	if class.type == "class" then
		local parent = class.parents
		while parent do
			parent = Dorothy[parent[1]]
			for k,v in pairs(parent.childs) do
				class.childs[k] = v
			end
			parent = parent.parents
		end
	end
end

write("{")
for i=1,#orderedDorothy do
	local className = orderedNames[i]
	local class = orderedDorothy[i]
	if class.type == "class" then
		write("\t{")
		write("\t\t\""..className.."\",")
		write("\t\t{")
		write("\t\t\t{")
		local str = ""
		for k,v in pairs(class.childs) do
			str = str.."\t\t\t\t{\""..k.."\",{"
			if v.typeName then
				str = str.."\""..v.typeName.."\""
			else
				str = str.."\"\""
			end
			if v.static then
				str = str..",oItem::Static"
			elseif v.type == "method" then
				str = str..",oItem::Method"
			elseif v.type == "value" then
				str = str..",oItem::Field"
			end
			str = str.."}},\n"
		end
		write(str:sub(1,-2))
		write("\t\t\t},")
		write("\t\t\t"..(class.hide and "true," or "false,"))
		write("\t\t},")
		write("\t},")
	end
end
write("}\n")

print(result)
