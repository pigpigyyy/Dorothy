local CCDirector = require("CCDirector")
local CCLayerColor = require("CCLayerColor")
local ccColor4 = require("ccColor4")
local oVec2 = require("oVec2")
local CCNode = require("CCNode")
local oLine = require("oLine")
local CCTouch = require("CCTouch")
local oEvent = require("oEvent")
local oListener = require("oListener")
local oScale = require("oScale")
local oEase = require("oEase")
local CCDictionary = require("CCDictionary")
local oPos = require("oPos")
local CCSequence = require("CCSequence")
local CCCall = require("CCCall")
local oEditor = require("oEditor")
local CCRect = require("CCRect")

--[[
events:
	viewArea.move
	viewArea.toOrigin
	viewArea.scale
	viewArea.toScale
--]]

local function oViewArea()
	local winSize = CCDirector.winSize
	local origin = oEditor.origin
	
	-- init view --
	local view = CCLayerColor(ccColor4(--[[0xff1a1a1a]]),winSize.width,winSize.height)
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
	local cross = oLine(
	{
		oVec2(0,-winSize.height*2),
		oVec2(0,winSize.height*2)
	},ccColor4())
	cross.opacity = 0.2
	crossNode:addChild(cross)
	cross = oLine(
	{
		oVec2(-winSize.width*2,0),
		oVec2(winSize.width*2,0)
	},ccColor4())
	cross.opacity = 0.2
	crossNode:addChild(cross)

	-- listen reset events --
	crossNode.data = CCDictionary()
	crossNode.data.toScaleListener = oListener("viewArea.toScale",function(scale)
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
	crossNode.data.toPosListener = oListener("viewArea.toPos",function(pos)
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
	end)
	crossNode.data.moveListener = oListener("viewArea.move",function(delta)
		crossNode.position = crossNode.position + delta/scaleNode.scaleX
	end)

	local shapeToCreate = nil
	crossNode.data.createListener = oListener("viewArea.create",function(name)
		shapeToCreate = name
	end)

	local function createShape(name,pos)
		oEvent:send("editControl.hide")
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
		oEvent:send("viewPanel.choose",data)
		oEvent:send("editMenu.created")
		oEvent:send("editor.change")
	end
	
	-- init world node --
	crossNode:addChild(oEditor.world)

	-- register view touch event --
	local pick = false
	view:registerTouchHandler(
		function(eventType, touches)
			if eventType == CCTouch.Began then
				if not oEditor.isPlaying and shapeToCreate ~= nil then
					createShape(shapeToCreate,touches[1].location)
					shapeToCreate = nil
					return false
				else
					pick = true
					return true
				end
			elseif eventType == CCTouch.Moved then
				if #touches == 1 then -- move view
					local delta = touches[1].delta
					if delta ~= oVec2.zero then
						pick = false
						oEvent:send("viewArea.move",touches[1].delta)
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
					oEvent:send("viewArea.scale",scale)
				end
			elseif eventType == CCTouch.Ended or eventType == CCTouch.Cancelled then
				if pick then
					local pos = oEditor.world:convertToNodeSpace(touches[1].location)
					oEditor.world:query(CCRect(pos.x-0.5,pos.y-0.5,1,1),function(body)
							local data = body.dataItem
							oEvent:send("viewPanel.choose",data)
						return true
					end)
				end
			end
		end,true,oEditor.touchPriorityViewArea)
	view.touchEnabled = true

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