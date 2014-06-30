local seconds = function(duration)
	local time = 0
	return function(deltaTime)
		time = time + deltaTime
		return time >= duration
	end
end

local minutes = function(duration)
	duration = duration*60
	local time = 0
	return function(deltaTime)
		time = time + deltaTime
		return time >= duration
	end
end

local wait = (function()
	local director = CCDirector
	return function(timer)
		while not timer(director.deltaTime) do
			coroutine.yield()
		end
	end
end)()

local sequencer = function(job)
	return coroutine.wrap(job)
end

return {sequencer,wait,seconds,minutes}
