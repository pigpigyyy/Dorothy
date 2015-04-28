local CCDictionary = require("CCDictionary")
local CCNode = require("CCNode")
local tolua = require("tolua")
local oBody = require("oBody")
local oVec2 = require("oVec2")
local oJoint = require("oJoint")
local oBodyDef = require("oBodyDef")
local oJointDef = require("oJointDef")
local oCache = require("oCache")
local CCSprite = require("CCSprite")
local oModel = require("oModel")
local type = tolua.type

local bodyCache = CCDictionary()

local loadFuncs = nil
local function loadData(data,item)
	local itemType = data[1]
	loadFuncs[itemType](data,item)
end

local function load(_,filename)
	local itemDict = bodyCache[filename]
	if not itemDict then
		local bodyData = dofile(filename)
		itemDict = CCDictionary()
		for _,data in ipairs(bodyData) do
			loadData(data,itemDict)
		end
		bodyCache[filename] = itemDict
	end
	return itemDict
end

local function unload(_,filename)
	if filename then
		bodyCache[filename] = nil
	else
		bodyCache:clear()
	end
end

local oCache_clear = oCache.clear
oCache.clear = function(self)
	oCache_clear(self)
	bodyCache:clear()
end
oCache.Body = {load=load,unload=unload}

local oBody_create = oBody[2]

local function create(itemDict,world,pos,angle)
	local items = CCDictionary()
	local node = CCNode()
	node.data = items
	local center = nil
	local keys = itemDict.keys
	for i = 1,#keys do
		local key = keys[i]
		local itemDef = itemDict[key]
		if type(itemDef) == "oBodyDef" then
			local newPos = pos
			if not center then
				center = itemDef.position
			elseif angle ~= 0 then
				local oldPos = itemDef.position
				newPos = oldPos - center
				local realAngle = -math.rad(angle) + math.atan2(newPos.y, newPos.x)
				local length = newPos.length
				newPos = oVec2(length*math.cos(realAngle), length*math.sin(realAngle))
				newPos = newPos + pos - oldPos
			end
			local body = oBody_create(oBody,itemDef,world,newPos,angle)
			local face = nil
			local faceStr = itemDef.face
			if faceStr ~= "" then
				if faceStr:match("|") then
					face = CCSprite(faceStr)
				else
					local extension = string.lower(string.match(faceStr,"%.([^%.\\/]*)$"))
					if extension == "model" then
						face = oModel(faceStr)
					else
						face = CCSprite(faceStr)
					end
				end
			end
			if face then
				face.position = itemDef.facePos
				body:addChild(face)
			end
			items[key] = body
			node:addChild(body)
		else
			if center then
				itemDef.center = center
				itemDef.position = pos
				itemDef.angle = angle
			end
			local joint = oJoint(itemDef,items)
			if joint then
				items[key] = joint
			end
		end
	end
	return node
end

oBody[2] = function(self,data,world,pos,angle)
	pos = pos or oVec2.zero
	angle = angle or 0
	if type(data) == "oBodyDef" then
		return oBody_create(self,data,world,pos,angle)
	elseif type(data) == "string" then
		return create(load(nil,data),world,pos,angle)
	else
		return create(data,world,pos,angle)
	end
end

loadFuncs =
{
	Rectangle = function(data,itemDict)
		local bodyDef = oBodyDef()
		bodyDef.type = data[3]
		bodyDef.isBullet = data[15]
		bodyDef.gravityScale = data[14]
		bodyDef.fixedRotation = data[13]
		bodyDef.linearDamping = data[11]
		bodyDef.angularDamping = data[12]
		bodyDef.position = data[4]
		bodyDef.angle = data[5]
		bodyDef.face = data[19]
		bodyDef.facePos = data[20]
		if data[16] then
			bodyDef:attachPolygonSensor(data[17],
				data[7].width,data[7].height,data[6],0)
		else
			bodyDef:attachPolygon(data[6],
				data[7].width,data[7].height,
				0,data[8],data[9],data[10])
		end
		if data[18] then
			for _,subShape in ipairs(data[18]) do
				loadData(subShape,bodyDef)
			end
		end
		itemDict:set(data[2],bodyDef)
	end,
	Circle = function(data,itemDict)
		local bodyDef = oBodyDef()
		bodyDef.type = data[3]
		bodyDef.isBullet = data[15]
		bodyDef.gravityScale = data[14]
		bodyDef.fixedRotation = data[13]
		bodyDef.linearDamping = data[11]
		bodyDef.angularDamping = data[12]
		bodyDef.position = data[4]
		bodyDef.angle = data[5]
		bodyDef.face = data[19]
		bodyDef.facePos = data[20]
		if data[16] then
			bodyDef:attachCircleSensor(data[17],data[6],data[7])
		else
			bodyDef:attachCircle(data[6],data[7],data[8],data[9],data[10])
		end
		if data[18] then
			for _,subShape in ipairs(data[18]) do
				loadData(subShape,bodyDef)
			end
		end
		itemDict:set(data[2],bodyDef)
	end,
	Polygon = function(data,itemDict)
		if not data[6] or #data[6] < 3 then return end
		local bodyDef = oBodyDef()
		bodyDef.type = data[3]
		bodyDef.isBullet = data[14]
		bodyDef.gravityScale = data[13]
		bodyDef.fixedRotation = data[12]
		bodyDef.linearDamping = data[10]
		bodyDef.angularDamping = data[11]
		bodyDef.position = data[4]
		bodyDef.angle = data[5]
		bodyDef.face = data[18]
		bodyDef.facePos = data[19]
		if data[15] then
			bodyDef:attachPolygonSensor(data[16],data[6])
		else
			bodyDef:attachPolygon(data[6],data[7],data[8],data[9])
		end
		if data[17] then
			for _,subShape in ipairs(data[17]) do
				loadData(subShape,bodyDef)
			end
		end
		itemDict:set(data[2],bodyDef)
	end,
	Chain = function(data,itemDict)
		if not data[6] or #data[6] < 2 then return end
		local bodyDef = oBodyDef()
		bodyDef.type = data[3]
		bodyDef.isBullet = data[13]
		bodyDef.gravityScale = data[12]
		bodyDef.fixedRotation = data[11]
		bodyDef.linearDamping = data[9]
		bodyDef.angularDamping = data[10]
		bodyDef.position = data[4]
		bodyDef.angle = data[5]
		bodyDef.face = data[15]
		bodyDef.facePos = data[16]
		bodyDef:attachChain(data[6],data[7],data[8])
		if data[14] then
			for _,subShape in ipairs(data[14]) do
				loadData(subShape,bodyDef)
			end
		end
		itemDict:set(data[2],bodyDef)
	end,
	Loop = function(data,itemDict)
		if not data[6] or #data[6] < 3 then return end
		local bodyDef = oBodyDef()
		bodyDef.type = data[3]
		bodyDef.isBullet = data[13]
		bodyDef.gravityScale = data[12]
		bodyDef.fixedRotation = data[11]
		bodyDef.linearDamping = data[9]
		bodyDef.angularDamping = data[10]
		bodyDef.position = data[4]
		bodyDef.angle = data[5]
		bodyDef.face = data[15]
		bodyDef.facePos = data[16]
		bodyDef:attachLoop(data[6],data[7],data[8])
		if data[14] then
			for _,subShape in ipairs(data[14]) do
				loadData(subShape,bodyDef)
			end
		end
		itemDict:set(data[2],bodyDef)
	end,
	SubRectangle = function(data,bodyDef)
		if data[8] then
			bodyDef:attachPolygonSensor(data[9],
				data[4].width,data[4].height,
				data[2],data[3])
		else
			bodyDef:attachPolygon(data[2],
				data[4].width,data[4].height,
				data[3],data[5],data[6],data[7])
		end
	end,
	SubCircle = function(data,bodyDef)
		if data[7] then
			bodyDef:attachCircleSensor(data[8],data[2],data[3])
		else
			bodyDef:attachCircle(data[2],data[3],data[4],data[5],data[6])
		end
	end,
	SubPolygon = function(data,bodyDef)
		if not data[2] or #data[2] < 3 then return end
		if data[6] then
			bodyDef:attachPolygonSensor(data[7],data[2])
		else
			bodyDef:attachPolygon(data[2],data[3],data[4],data[5])
		end
	end,
	SubChain = function(data,bodyDef)
		if not data[2] or #data[2] < 2 then return end
		bodyDef:attachChain(data[2],data[3],data[4])
	end,
	SubLoop = function(data,bodyDef)
		if not data[2] or #data[2] < 3 then return end
		bodyDef:attachLoop(data[2],data[3],data[4])
	end,
	Distance = function(data,itemDict)
		itemDict:set(data[2],
			oJointDef:distance(data[3],data[4],data[5],data[6],data[7],data[8],data[9]))
	end,
	Friction = function(data,itemDict)
		itemDict:set(data[2],
			oJointDef:friction(data[3],data[4],data[5],data[6],data[7],data[8]))
	end,
	Gear = function(data,itemDict)
		itemDict:set(data[2],
			oJointDef:gear(data[3],data[4],data[5],data[6]))
	end,
	Spring = function(data,itemDict)
		itemDict:set(data[2],
			oJointDef:spring(data[3],data[4],data[5],data[6],data[7],data[8],data[9],data[10]))
	end,
	Prismatic = function(data,itemDict)
		itemDict:set(data[2],
			oJointDef:prismatic(data[3],data[4],data[5],data[6],data[7],data[8],data[9],data[10],data[11]))
	end,
	Pulley = function(data,itemDict)
		itemDict:set(data[2],
			oJointDef:pulley(data[3],data[4],data[5],data[6],data[7],data[8],data[9],data[10]))
	end,
	Revolute = function(data,itemDict)
		itemDict:set(data[2],
			oJointDef:revolute(data[3],data[4],data[5],data[6],data[7],data[8],data[9],data[10]))
	end,
	Rope = function(data,itemDict)
		itemDict:set(data[2],
			oJointDef:rope(data[3],data[4],data[5],data[6],data[7],data[8]))
	end,
	Weld = function(data,itemDict)
		itemDict:set(data[2],
			oJointDef:weld(data[3],data[4],data[5],data[6],data[7],data[8]))
	end,
	Wheel = function(data,itemDict)
		itemDict:set(data[2],
			oJointDef:wheel(data[3],data[4],data[5],data[6],data[7],data[8],data[9],data[10],data[11]))
	end,
}

return oBody
