Dorothy()
local class,property,classfield = unpack(require("class"))

--[[
Usage:
-- Extend TestBase and override function run()

local MyTest = class(TestBase)

function MyTest:run()
	print("Test is running.")
end
--]]

local TestBase = class(CCScene,
{
	isTest = classfield(function()
		return true
	end),
})

function TestBase:run() -- override it
end

function TestBase:profileRun()
	local startTime = CCDirector.eclapsedInterval
	self:run()
	local endTime = CCDirector.eclapsedInterval
	print("Test done. Time cost "..string.format("%.4f",endTime-startTime).." s.")
end

function TestBase:enterScene()
	CCDirector:run(self)
end

return MyTest
