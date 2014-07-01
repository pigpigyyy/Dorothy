local yield = coroutine.yield
local wrap = coroutine.wrap
local create = coroutine.create
local resume = coroutine.resume
local CCDirector = require("CCDirector")

local seconds = function(duration)
	local time = 0
	return function(deltaTime)
		time = time + deltaTime
		return time < duration
	end
end

local wait = (function()
	local director = CCDirector
	return function(cond)
		while cond(director.deltaTime) do
			yield()
		end
	end
end)()

local once = function(job)
	return wrap(function()
		job()
		return true
	end)
end

local loop = function(job)
	return wrap(function(...)
		local _job = job
		local worker = create(_job)
		repeat
			local running,result = resume(worker,...)
			if not running then
				worker = create(_job)
			end
			yield(result)
		until false
	end)
end

return {wait,once,loop,seconds}
