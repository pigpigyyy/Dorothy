local oVec2 = require("oVec2")
local CCDrawNode = require("CCDrawNode")

local function oStar(radius,color,borderRadius,borderColor)
	borderRadius = borderRadius or 0
	borderColor = borderColor or color
	local a = math.rad(36)
	local c = math.rad(72)
	local f = math.sin(a)*math.tan(c)+math.cos(a)

	local R = radius
	local r = R/f

	local vs = {}
	for i = 9,0,-1 do
		local angle = i*a
		if i%2 == 1 then
			table.insert(vs,oVec2(r*math.sin(angle),r*math.cos(angle)))
		else
			table.insert(vs,oVec2(R*math.sin(angle),R*math.cos(angle)))
		end
	end

	local drawNode = CCDrawNode()
	drawNode:drawPolygon(vs,color,borderRadius,borderColor)

	return drawNode
end

return oStar