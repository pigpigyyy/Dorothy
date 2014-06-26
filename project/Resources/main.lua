--require("Editor/Script/main")
require("Test/Entry")
--[[
local class,property = unpack(require("class"))

local A = class({
	--self=CCNode
	__init = function(self,name)
		self._name = name
		return CCNode()
	end,
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

local B = class(A,{
	--self=CCScene
	__init = function(self,name)
		A.__init(self,name)
		return CCScene()
	end,
	
	--@static
	inst = function(cls)
		return "inst"
	end,
})

B.print = function(self)
		print(self._name,"Hello World")
	end

local b = B("Pig")
b:print()
A("child"):print()
]]
--CCDirector:run(CCScene())
