--require("Editor/Script/main")
--require("Test/Entry")
local class,property = unpack(require("untitled"))

local A = class({
	--self=CCNode
	__init__ = function(self,name)
		self._name = name
	end,
	__new__ = function(self)
		return CCScene()
	end,
	name = property(
		function(self)
			return self._name
		end,
		function(self,value)
			self._name = value
		end),
	
	show = function(self)
		self.visible = true
	end,
	
	hide = function(self)
		self.visible = false
	end,
})

local a = A("Pig")
print(a.name)
a:hide()
print(a.visible)

CCDirector:run(a)