Dorothy!
TestBase = require "Dev.Test.TestBase"

Class TestBase,
	run:=>
		print "Fields of UnitDef:"
		for k,v in pairs oUnitDef[4]
			if type(k) == "string" and k\sub(1,2) ~= "__"
				print k
		
		print "\nFields of BodyDef:"
		for k,v in pairs oBodyDef[4]
			if type(k) == "string" and k\sub(1,2) ~= "__"
				print k
