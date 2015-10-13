local oVec2 = require("oVec2")
local CCDrawNode = require("CCDrawNode")
local ccColor4 = require("ccColor4")

local function oStar(radius,offset)
	offset = offset or oVec2.zero
	local a = math.rad(36)
	local c = math.rad(72)
	local f = math.sin(a)*math.tan(c)+math.cos(a)

	local R = radius
	local r = R/f

	local vs = {}
	for i = 9,0,-1 do
		local angle = i*a
		if i%2 == 1 then
			table.insert(vs,oVec2(r*math.sin(angle),r*math.cos(angle))+offset)
		else
			table.insert(vs,oVec2(R*math.sin(angle),R*math.cos(angle))+offset)
		end
	end
	return vs
end

return oStar