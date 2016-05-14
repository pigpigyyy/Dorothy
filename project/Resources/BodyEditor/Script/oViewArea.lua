local require = using("BodyEditor.Script")
local CCDirector = require("CCDirector")
local CCLayerColor = require("CCLayerColor")
local ccColor4 = require("ccColor4")
local oVec2 = require("oVec2")
local CCNode = require("CCNode")
local oLine = require("oLine")
local CCSequence = require("CCSequence")
local oScale = require("oScale")
local oEase = require("oEase")
local CCCall = require("CCCall")
local oPos = require("oPos")
local emit = require("emit")
local CCRect = require("CCRect")

--[[
events:
	viewArea.move
	viewArea.toOrigin
	viewArea.scale
	viewArea.toScale
--]]

local function oViewArea()
	local oEditor = require("oEditor")
	local winSize = CCDirector.winSize
	local origin = oEditor.origin

	-- init view --
	local view = CCLayerColor(ccColor4(0xff1a1a1a),winSize.width,winSize.height)
	view.anchor = oVec2.zero
	view.cascadeOpacity = true

	local scaleNode = CCNode()
	scaleNode.contentSize = winSize
	local scalePos = oVec2(winSize.width*0.5+origin.x,winSize.height*0.5+origin.y)
	scaleNode.position = scalePos
	scaleNode.anchor = oVec2(origin.x/winSize.width,origin.y/winSize.height)
	view:addChild(scaleNode)

	local crossNode = CCNode()
	crossNode.position = origin
	scaleNode:addChild(crossNode)

	-- init cross --
	local xcross = oLine(
	{
		oVec2(0,-winSize.height*2),
		oVec2(0,winSize.height*2)
	},ccColor4())
	xcross.opacity = 0.2
	crossNode:addChild(xcross)
	local ycross = oLine(
	{
		oVec2(-winSize.width*2,0),
		oVec2(winSize.width*2,0)
	},ccColor4())
	ycross.opacity = 0.2
	crossNode:addChild(ycross)

	-- listen reset events --
	crossNode:gslot("Body.viewArea.toScale",function(scale)
		oEditor.scale = scale
		view.touchEnabled = false
		scaleNode:runAction(CCSequence(
		{
			oScale(0.5,scale,scale,oEase.OutQuad),
			CCCall(function()
				if scaleNode.numberOfRunningActions+crossNode.numberOfRunningActions == 1 then
					view.touchEnabled = true
				end
			end),
		}))
	end)
	crossNode:gslot("Body.viewArea.toPos",function(pos)
		view:unschedule()
		view.touchEnabled = false
		crossNode:runAction(CCSequence(
		{
			oPos(0.5,pos.x,pos.y,oEase.OutQuad),
			CCCall(function()
				if scaleNode.numberOfRunningActions+crossNode.numberOfRunningActions == 1 then
					view.touchEnabled = true
				end
			end),
		}))
		xcross:runAction(oPos(0.5,0,-pos.y,oEase.OutQuad))
		ycross:runAction(oPos(0.5,-pos.x,0,oEase.OutQuad))
	end)
	crossNode:gslot("Body.viewArea.move",function(delta)
		delta = delta/scaleNode.scaleX
		crossNode.position = crossNode.position + delta
		xcross.positionY = xcross.positionY - delta.y
		ycross.positionX = ycross.positionX - delta.x
	end)

	local shapeToCreate = nil
	crossNode:gslot("Body.viewArea.create",function(name)
		shapeToCreate = name
	end)

	local function createShape(name,pos)
		emit("Body.editControl.hide")
		local data
		if oEditor.currentData and not oEditor.currentData.parent and not oEditor.currentData.resetListener then
			data = oEditor["newSub"..name](oEditor)
			if data:has("Center") then
				local parent = oEditor.currentData
				local worldNode = oEditor.worldNode
				worldNode.position = parent:get("Position")
				worldNode.angle = parent:has("Angle") and parent:get("Angle") or 0
				pos = worldNode:convertToNodeSpace(pos)
				if oEditor.isFixed then
					pos = oEditor:round(pos)
				end
				data:set("Center",pos)
			end
			oEditor:addSubData(oEditor.currentData,data)
		else
			data = oEditor["new"..name](oEditor)
			pos = oEditor.world:convertToNodeSpace(pos)
			if oEditor.isFixed then
				pos = oEditor:round(pos)
			end
			data:set("Position",pos)
			oEditor:addData(data)
		end
		emit("Body.viewPanel.choose",data)
		emit("Body.editMenu.created")
		emit("Body.editor.change")
	end

	-- init world node --
	view.viewNode = CCNode()
	crossNode:addChild(view.viewNode,-1)
	crossNode:addChild(oEditor.world)

	-- handle view touch event --
	local pick = false
	view.multiTouches = true
	view.touchPriority = oEditor.touchPriorityViewArea
	view.touchEnabled = true

	local S = oVec2.zero
	local V = oVec2.zero
	local accel = winSize.height*2
	local function updateDragSpeed(dt)
		V = S / dt
		if V.length > accel then
			V:normalize()
			V = V * accel
		end
		S = oVec2.zero
	end
	local function updateDragPos(dt)
		local dir = oVec2(V.x,V.y)
		dir:normalize()
		local A = dir * -accel
		local incX = V.x > 0
		local incY = V.y > 0
		V = V + A * dt * 0.5
		local decX = V.x < 0
		local decY = V.y < 0
		if incX == decX and incY == decY then
			view:unschedule()
		else
			emit("Body.viewArea.move",V * dt)
		end
	end
	view:slot("TouchBegan",function(touches)
		if not oEditor.isPlaying and shapeToCreate ~= nil then
			createShape(shapeToCreate,touches[1].location)
			shapeToCreate = nil
			return false
		end
		pick = true
		S = oVec2.zero
		V = oVec2.zero
		view:schedule(updateDragSpeed)
		return true
	end)
	view:slot("TouchMoved",function(touches)
		if #touches == 1 then -- move view
			local delta = touches[1].delta
			if delta ~= oVec2.zero then
				pick = false
				S = delta
				emit("Body.viewArea.move",delta)
			end
		elseif #touches >= 2 then -- scale view
			local preDistance = touches[1].preLocation:distance(touches[2].preLocation)
			local distance = touches[1].location:distance(touches[2].location)
			local delta = (distance - preDistance) * 4 / winSize.height
			local scale = scaleNode.scaleX + delta
			if scale <= 0.5 then
				scale = 0.5
			end
			scaleNode.scaleX = scale
			scaleNode.scaleY = scale
			oEditor.scale = scale
			pick = false
			emit("Body.viewArea.scale",scale)
		end
	end)

	local function touchEnded(touches)
		if pick then
			view:unschedule()
			local pos = oEditor.world:convertToNodeSpace(touches[1].location)
			oEditor.world:query(CCRect(pos.x-0.5,pos.y-0.5,1,1),function(body)
				local data = body.dataItem
				emit("Body.viewPanel.choose",data)
				return true
			end)
		else
			if V ~= oVec2.zero then
				view:schedule(updateDragPos)
			end
		end
	end
	view:slot("TouchEnded",touchEnded)
	view:slot("TouchCancelled",touchEnded)

	-- test codes below
	--[[local CCDrawNode = require("CCDrawNode")
	local drawNode = CCDrawNode()
	drawNode:drawDot(oVec2.zero,100,ccColor4(0xff80ff00))
	oEditor.world:addChild(drawNode)]]
	--[[
	local bodyData = oEditor:newCircle()
	bodyData[oEditor.Circle.Center] = oVec2(100,0)
	bodyData[oEditor.Circle.Sensor] = true
	bodyData[oEditor.Circle.Radius] = 100
	bodyData[oEditor.Circle.Angle] = 25
	bodyData[oEditor.Circle.Type] = oBodyDef.Dynamic
	bodyData[oEditor.Circle.SubShapes] = {oEditor:newSubRectangle(),oEditor:newSubLoop()}
	bodyData[oEditor.Circle.SubShapes][2][oEditor.SubLoop.Vertices] =
	{
		oVec2(-160,0),
		oVec2(-80,160),
		oVec2(40,80),
		oVec2(80,160),
		oVec2(160,0),
		oVec2(80,-160),
		oVec2(-80,-160),
		oVec2(-160,0),
	}
	oEditor:addData(bodyData)

	bodyData = oEditor:newRectangle()
	bodyData[oEditor.Rectangle.Center] = oVec2(100,100)
	bodyData[oEditor.Rectangle.Size] = CCSize(1024,100)
	bodyData[oEditor.Rectangle.Type] = oBodyDef.Static
	bodyData[oEditor.Rectangle.Position] = oVec2(0,-400)
	bodyData[oEditor.Rectangle.Angle] = 45
	oEditor:addData(bodyData)

	bodyData = oEditor:newLoop()
	bodyData:set("Position",oVec2(0,300))
	bodyData:set("Type",oBodyDef.Dynamic)
	bodyData:set("Vertices",
	{
		oVec2(-160,0),
		oVec2(-80,160),
		oVec2(40,80),
		oVec2(80,160),
		oVec2(160,0),
		oVec2(80,-160),
		oVec2(-80,-160),
		oVec2(-160,0),
	})
	bodyData:set("SubShapes",{oEditor:newSubRectangle(),oEditor:newSubCircle()})
	bodyData:get("SubShapes")[2]:set("Center",oVec2(200,0))
	oEditor:addData(bodyData)
	--]]
	--oEditor:dumpData("test.lua")
	--oEditor:loadData("test.lua")
	-- test codes abow

	return view
end

return oViewArea
