local CCDirector = require("CCDirector")

local oRoutine =
{
	remove = function(self,routine)
		local pos
		for i = 1,#self do
			if self[i] == routine then
				pos = i
				break
			end
		end
		if pos then
			table.remove(self,pos)
		end
	end,
	clear = function(self)
		while #self > 0 do
			table.remove(self)
		end
	end,
}

setmetatable(oRoutine,
{
	__call = function(self,routine)
		table.insert(self,routine)
	end,
})

local function update()
	local i,count = 1,#oRoutine
	while i <= count do
		if oRoutine[i]() then
			if i ~= count then
				oRoutine[i] = oRoutine[count]
			end
			table.remove(oRoutine)
			i = i-1
			count = count-1
		end
		i = i+1
	end
end

oRoutine.start = function(self)
	CCDirector:schedule(update)
end

oRoutine.stop = function(self)
	CCDirector:unschedule()
end

oRoutine:start()

return oRoutine
