local oContent = require("oContent")
local oEditor = require("oEditor")
local Rectangle = oEditor.Rectangle
local Circle = oEditor.Circle
local Polygon = oEditor.Polygon

local loaderCodes = [[local createFuncs = nil
local function create(data,item)
	createFuncs[data[1] ](data,item)
end
local function load(bodyData)
	local itemDict = CCDictionary()
	for _,data in ipairs(bodyData) do
		create(data,itemDict)
	end
	return itemDict
end

createFuncs =
{
]]..string.format([[
	Rectangle = function(data,itemDict)
		local bodyDef = oBodyDef()
		bodyDef.type = data[%d]
		bodyDef.isBullet = data[%d]
		bodyDef.gravityScale = data[%d]
		bodyDef.fixedRotation = data[%d]
		bodyDef.linearDamping = data[%d]
		bodyDef.angularDamping = data[%d]
		bodyDef.position = data[%d]
		bodyDef.angle = data[%d]
		if data[%d] then
			bodyDef:attachPolygonSensor(
				data[%d],
				data[%d].width,
				data[%d].height,
				data[%d],
				0)
		else
			bodyDef:attachPolygon(
				data[%d],
				data[%d].width,
				data[%d].height,
				0,
				data[%d],
				data[%d],
				data[%d])
		end
		if data[%d] then
			for _,subShape in ipairs(data[%d]) do
				create(subShape,bodyDef)
			end
		end
		itemDict:set(data[%d],bodyDef)
	end,
]],
Rectangle.Type,
Rectangle.Bullet,
Rectangle.GravityScale,
Rectangle.FixedRotation,
Rectangle.LinearDamping,
Rectangle.AngularDamping,
Rectangle.Position,
Rectangle.Angle,
Rectangle.Sensor,
Rectangle.SensorTag,
Rectangle.Size,
Rectangle.Size,
Rectangle.Center,
Rectangle.Center,
Rectangle.Size,
Rectangle.Size,
Rectangle.Density,
Rectangle.Friction,
Rectangle.Restitution,
Rectangle.SubShapes,
Rectangle.SubShapes,
Rectangle.Name)..string.format([[
	Circle = function(data,itemDict)
		local bodyDef = oBodyDef()
		bodyDef.type = data[%d]
		bodyDef.isBullet = data[%d]
		bodyDef.gravityScale = data[%d]
		bodyDef.fixedRotation = data[%d]
		bodyDef.linearDamping = data[%d]
		bodyDef.angularDamping = data[%d]
		bodyDef.position = data[%d]
		bodyDef.angle = data[%d]
		if data[%d] then
			bodyDef:attachCircleSensor(
				data[%d],
				data[%d],
				data[%d])
		else
			bodyDef:attachCircle(
				data[%d],
				data[%d],
				data[%d],
				data[%d],
				data[%d])
		end
		if data[%d] then
			for _,subShape in ipairs(data[%d]) do
				create(subShape,bodyDef)
			end
		end
		itemDict:set(data[%d],bodyDef)
	end,
]],
Circle.Type,
Circle.Bullet,
Circle.GravityScale,
Circle.FixedRotation,
Circle.LinearDamping,
Circle.AngularDamping,
Circle.Position,
Circle.Angle,
Circle.Sensor,
Circle.SensorTag,
Circle.Center,
Circle.Radius,
Circle.Center,
Circle.Radius,
Circle.Density,
Circle.Friction,
Circle.Restitution,
Circle.SubShapes,
Circle.SubShapes,
Circle.Name)..string.format([[
]])

oContent:saveToFile("loader.lua",loaderCodes)
