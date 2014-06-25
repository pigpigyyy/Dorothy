--require("Editor/Script/main")
require("Test/Entry")
--[[
local class,property = unpack(require("class"))

local A = class({
	--self=CCNode
	__init__ = function(self,name)
		self._name = name
	end,
	__new__ = function(self)
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
		print("Hello Pig")
	end,
	
	show = function(self)
		self.visible = true
	end,

	hide = function(self)
		self.visible = false
	end,
})

local B = class(A,{
	--self=CCScene
	__new__ = function(self)
		return CCScene()
	end,
	print = function(self)
		print("Hello World")
	end,
})

local a = B("Pig")
a:print()
print(a.name)
a:hide()
print(a.visible)

CCDirector:run(a)
]]