oVec2 = require "oVec2"
oLine = require "oLine"
ccColor4 = require "ccColor4"

num = 20

newP = (index, radius)->
	angle = 2*math.pi*index/num
	oVec2(radius*math.cos(angle),radius*math.sin(angle)) + oVec2(radius,radius)

(args)->
	oLine [newP index, args.radius for index = 0, num], args.color and ccColor4 args.color or 0xffffffff
