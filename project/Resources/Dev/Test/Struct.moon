Class = require "Class"
TestBase = require "Dev.Test.TestBase"
CCDirector = require "CCDirector"
import Struct from require "Lib.Utils"

Class TestBase,
	run:=>
		-- Declare struct classes
		Unit = Struct.Unit "name", "group", "type", "actions"
		Action = Struct.Action "name", "id"
		Array = Struct.Array

		-- Create struct instances
		unit = Unit
			name:"abc"
			group:123
			type:"typeX"
			actions:Array {
				Action name:"walk",id:"a1"
				Action name:"run",id:"a2"
				Action name:"sleep",id:"a3"
			}

		-- Convert instance to string 
		str = tostring unit

		print "unitStr",str

		-- Load string to instance
		unit = Struct\load str

		-- Register for field changes
		unit.__notify = (event,key,value)->
			print event,key,"to",value

		unit.actions.__notify = (event,index,item)->
			print event,index,tostring item

		-- Change some fields
		unit.type = "typeY"
		unit.group = 911
		-- Change container contents
		print unit.actions.count

		unit.actions\insert Action name:"idle",id:"a4"
		print unit.actions.count

		unit.actions\remove 2
		print unit.actions.count

		unit.actions\set 1, Action name:"attack",id:"a0"
		unit.actions\clear!

		action = Action name:"idle",id:"a4"
		unit.actions\insert(action)

		-- Traverse container
		unit.actions\each (item)->
			print tostring item

		unit.actions\removefor action
		print unit.actions.count
		print "Unit:",tostring unit

		-- Test different namespaces
		Grid = Struct.UI.Grid "cols","rows"
		Grid2 = Struct.Items.Grid "x","y","z"
		Cell = Struct.Items.Cell "number","text"
		print tostring Grid cols:123,rows:456
		print tostring Grid2 x:123,y:456,z:233

		unorderedField = Grid2 z:"unordered",x:217
		print tostring unorderedField
		unorderedField.y = 3
		print tostring unorderedField

		-- Serialize all struct defines to string
		print tostring Struct

		-- Profile test
		fieldNumber = 12
		tests = 10000
		fieldNames = {}
		for i = 1,fieldNumber
			fieldNames[i] = "field#{ i }"
		local tableItem,structItem

		@profile "Create #{ tests } table",->
			for i = 1,tests
				tableItem = {}
				for n = 1,fieldNumber
					tableItem[fieldNames[n]] = fieldNames[n]

		@profile "Create #{ tests } struct",->
			TestStruct = Struct.TestStruct unpack fieldNames
			for i = 1,tests
				structItem = TestStruct!
				for n = 1,fieldNumber
					structItem[fieldNames[n]] = fieldNames[n]

		{:insert,:concat} = table
		local tableStr
		@profile "Serialize table #{ tests } times",->
			for i = 1,tests
				tableStr = {}
				for k,v in pairs tableItem
					insert tableStr,k.."=\""..v.."\""
				tableStr = "return {#{ concat(tableStr,',') }}"

		local structStr
		@profile "Serialize struct #{ tests } times",->
			for i = 1,tests
				structStr = "return #{ structItem }"

		@profile "Load table for #{ tests } times",->
			for i = 1,tests
				loadstring(tableStr)!

		@profile "Load struct for #{ tests } times",->
			for i = 1,tests
				Struct\load structStr
