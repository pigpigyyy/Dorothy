--require("Editor/Script/main")
require("Test/Entry")

--require("Test/Case/Unit")
--[[
local CCNode = require("CCNode")
local CCScene = require("CCScene")
local CCDirector = require("CCDirector")
local CCArray = require("CCArray")
local CCDrawNode = require("CCDrawNode")
local CCDictionary = require("CCDictionary")

local class,property,classfield,classmethod = unpack(require("class"))

local A = class({
	--self=CCNode
	__initc = function(cls)
		cls._count = 0
	end,
	__init = function(self,name)
		self._name = name
		local cls = getmetatable(self)
		cls._count = cls._count+1
		return CCNode()
	end,
	objCount = classfield(
		function(cls)
			return cls._count
		end),
	name = property(
		function(self)
			return self._name
		end,
		function(self,value)
			self._name = value
		end),

	print = function(self)
		print(self._name,"Hello Pig")
	end,
	
	show = function(self)
		self.visible = true
	end,

	hide = function(self)
		self.visible = false
	end,
	
	flag = "flag",
})

print(A.objCount)

local B = class(A,{
	--self=CCScene
	__init = function(self,name)
		A.__init(self,name)
		return CCScene()
	end,

	inst = classmethod(
		function()
			return "inst"
		end),
})

B.print = function(self)
		print(self._name,"Hello World")
	end

local b = B("Pig")
b:print()
A("child"):print()
print(A.objCount,B:inst())

CCDirector:run(CCScene())
local arr = CCArray({CCNode(),CCDrawNode()})
--arr[1] = CCClipNode()
print(arr[1])
print(arr[2])
local dict = CCDictionary()
dict.A = "A"
dict.B = "B"
dict.B = CCNode()
local node = CCNode()
node.data = dict
print(dict.randomObject)
print(dict.randomObject)
print(dict.randomObject)
]]
