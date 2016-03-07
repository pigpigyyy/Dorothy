local TriggerDef
local Expressions

SetExprMeta = (expr)->
	isTrigger = expr[1] == "Trigger"
	for i = 2,#expr
		childExpr = expr[i]
		SetExprMeta childExpr if "table" == type childExpr
		if isTrigger
			switch childExpr[1]
				when "Condition","Action"
					childExpr.parent = expr
	setmetatable expr,Expressions[expr[1]]

GetArgsText = (trigger)->
	if trigger and trigger[4][2].Args
		args = {tonumber(info\match("%d*$")),name for name,info in pairs trigger[4][2].Args}
		" #{table.concat args,', '} "
	else
		""

ExprToString = (expr)->
	if TriggerDef.CodeMode or expr.CodeOnly
		expr\ToCode!
	else
		index = 1
		expr.Desc\gsub "%b[]",->
			index += 1
			"(#{tostring expr[index]})"

NewExpr = (...)->
	names = {...}
	=>
		exprs = [Expressions[name]\Create! for name in *names]
		table.insert exprs,1,@Name
		setmetatable exprs,@

NewExprVal = (value)-> => setmetatable {@Name,value},@

Expressions = {
	GlobalVar: {
		Type:"GlobalVar"
		Group:"None"
		Desc:"Global variable declaration and initialization."
		ToCode:=>
			codes = [tostring expr for expr in *@[2,]]
			table.insert codes,1,"GlobalScope()"
			table.concat codes,"\n"
		Create:NewExpr!
	}
	Trigger: {
		Type:"Trigger"
		Group:"None"
		Desc:"The trigger named [TriggerName] is enabled [Boolean]."
		ToCode:=> "Trigger( #{ @[2] }, #{ @[3] },"
		Create:NewExpr "TriggerName","True","Event","Condition","Action"
	}
	Event: {
		Type:"EventType"
		Group:"None"
		Desc:"Event to trigger."
		ToCode:=> "Event("
		Create:NewExpr "NoEvent"
	}
	Action: {
		Type:"ActionSequence"
		Group:"None"
		Desc:"An action execution sequence."
		ToCode:=> "Action( function(#{GetArgsText @parent})"
		Create:NewExpr "DoNothing"
	}
	Condition: {
		Type:"Condition"
		Group:"None"
		Desc:"Condition value."
		ToCode:=> "Condition( function(#{GetArgsText @parent}) return"
		Create:NewExpr "True"
	}
	NoEvent: {
		Type:"Event"
		Group:"Misc"
		Desc:"No event."
		ToCode:=> "NoEvent()"
		Create:NewExpr!
	}
	TimeCycle: {
		Type:"Event"
		Group:"Time"
		Desc:"Trigger event every [Number] seconds."
		ToCode:=> "TimeCycle( #{ @[2] } )"
		Create:NewExpr "Number"
	}
	BodyEnter: {
		Type:"Event"
		Group:"Body"
		Desc:"Any body enters sensor [Sensor] area."
		ToCode:=> "BodyEnter( #{ @[2] } )"
		Args:{
			targetBody:"Body1" -- param order is needed
			sensorTag:"Number2"
		}
		Create:NewExpr "SensorByName"
	}
	And: {
		Type:"Boolean"
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Boolean [Boolean] and [Boolean]."
		ToCode:=> "( #{ @[2] } and #{ @[3] } )"
		Create:NewExpr "True","True"
	}
	Or: {
		Type:"Boolean"
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Boolean [Boolean] or [Boolean]."
		ToCode:=> "( #{ @[2] } or #{ @[3] } )"
		Create:NewExpr "True","True"
	}
	Add: {
		Type:"Number"
		TypeIgnore:false
		Group:"Number"
		Desc:"Number [Number] + [Number]."
		ToCode:=> "( #{ @[2] } + #{ @[3] } )"
		Create:NewExpr "Number","Number"
	}
	String: {
		Type:"String"
		TypeIgnore:false
		Group:"String"
		Desc:"Raw string."
		CodeOnly:true
		ToCode:=> "\"#{ @[2]\gsub('\"','\\\"') }\""
		Create:NewExprVal ""
	}
	Number: {
		Type:"Number"
		TypeIgnore:false
		Group:"Number"
		Desc:"Raw number."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExprVal 0
	}
	True: {
		Type:"Boolean"
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Boolean true."
		CodeOnly:true
		ToCode:=> "true"
		Create:NewExpr!
	}
	False: {
		Type:"Boolean"
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Boolean false."
		CodeOnly:true
		ToCode:=> "false"
		Create:NewExpr!
	}
	NumberEqual: {
		Type:"Boolean"
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Number [Number] equals [Number]."
		ToCode:=> "( #{ @[2] } == #{ @[3] } )"
		Create:NewExpr "Number","Number"
	}
	BodyEqual: {
		Type:"Boolean"
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Body [Body] equals [Body]."
		ToCode:=> "( #{ @[2] } == #{ @[3] } )"
		Create:NewExpr "BodyByName","BodyByName"
	}
	TriggerName: {
		Type:"TriggerName"
		Group:"Special"
		Desc:"The trigger`s name."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
	}
	Text: {
		Type:"Text"
		Group:"Special"
		Desc:"The plain text."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExprVal ""
	}
	LocalName: {
		Type:"LocalName"
		Group:"Special"
		Desc:"A name for local value."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExprVal "InvalidName"
	}
	GlobalName: {
		Type:"GlobalName"
		Group:"Special"
		Desc:"A name for global value."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExprVal "InvalidName"
	}
	InitGlobalName: {
		Type:"InitGlobalName"
		Group:"Special"
		Desc:"A name for global value."
		CodeOnly:true
		ToCode:=> "#{ @[2] == '' and 'InvalidName' or @[2] }"
		Create:NewExprVal ""
	}
	ModelName: {
		Type:"ModelName"
		Group:"Special"
		Desc:"A name for model."
		CodeOnly:true
		Item:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
	}
	LayerName: {
		Type:"LayerName"
		Group:"Special"
		Desc:"A name for layer."
		CodeOnly:true
		Item:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
	}
	SensorName: {
		Type:"SensorName"
		Group:"Special"
		Desc:"A name for sensor."
		CodeOnly:true
		Item:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
	}
	BodyName: {
		Type:"BodyName"
		Group:"Special"
		Desc:"A name for body."
		CodeOnly:true
		Item:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
	}
	ModelType: {
		Type:"ModelType"
		Group:"Special"
		Desc:"A type name for model."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal ""
	}
	Animation: {
		Type:"Animation"
		Group:"Special"
		Desc:"A name for animation."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal ""
	}
	Look: {
		Type:"Look"
		Group:"Special"
		Desc:"A name for look."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal ""
	}
	SetLocalNumber: {
		Type:"LocalAssign"
		Group:"Variable"
		Desc:"Set [LocalName] to [Number]."
		ToCode:=> "#{ @[2] } = #{ @[3] }"
		Create:NewExpr "LocalName","Number"
	}
	LocalNumber: {
		Type:"Number"
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get local number named [LocalName]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "LocalName"
	}
	SetLocalString: {
		Type:"LocalAssign"
		Group:"Variable"
		Desc:"Set [LocalName] to [String]."
		ToCode:=> "#{ @[2] } = #{ @[3] }"
		Create:NewExpr "LocalName","String"
	}
	LocalString: {
		Type:"String"
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get local string named [LocalName]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "LocalName"
	}
	SetLocalModel: {
		Type:"LocalAssign"
		Group:"Variable"
		Desc:"Set [LocalName] to [Model]."
		ToCode:=> "#{ @[2] } = #{ @[3] }"
		Create:NewExpr "LocalName","ModelByName"
	}
	LocalModel: {
		Type:"Model"
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get local model named [LocalName]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "LocalName"
	}
	SetLocalSensor: {
		Type:"LocalAssign"
		Group:"Variable"
		Desc:"Set [LocalName] to [Sensor]."
		ToCode:=> "#{ @[2] } = #{ @[3] }"
		Create:NewExpr "LocalName","SensorByName"
	}
	LocalSensor: {
		Type:"Sensor"
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get local sensor named [LocalName]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "LocalName"
	}
	SetLocalBody: {
		Type:"LocalAssign"
		Group:"Variable"
		Desc:"Set [LocalName] to [Body]."
		ToCode:=> "#{ @[2] } = #{ @[3] }"
		Create:NewExpr "LocalName","BodyByName"
	}
	LocalBody: {
		Type:"Body"
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get local body named [LocalName]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "LocalName"
	}
	SetLocal: {
		Type:"None"
		Group:"Variable"
		Desc:"Do [LocalAssign]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "SetLocalNumber"
	}
	SetGlobal: {
		Type:"None"
		Group:"Variable"
		Desc:"Do [GlobalAssign]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "SetGlobalNumber"
	}
	InitGlobalNumber: {
		Type:"GlobalInit"
		Group:"Variable"
		Desc:"Init [InitGlobalName] to [Number] with note [Text]."
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"..(tostring(@[4]) == "" and "" or " -- #{ @[4] }")
		Create:NewExpr "InitGlobalName","Number","Text"
	}
	SetGlobalNumber: {
		Type:"GlobalAssign"
		Group:"Variable"
		Desc:"Set [GlobalName] to [Number]."
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"
		Create:NewExpr "GlobalName","Number"
	}
	GlobalNumber: {
		Type:"Number"
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get global number named [GlobalName]."
		ToCode:=> "g_#{ @[2] }"
		Create:NewExpr "GlobalName"
	}
	InitGlobalModel: {
		Type:"GlobalInit"
		Group:"Variable"
		Desc:"Init [InitGlobalName] to [Model] with note [Text]."
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"..(tostring(@[4]) == "" and "" or " -- #{ @[4] }")
		Create:NewExpr "InitGlobalName","ModelByName","Text"
	}
	SetGlobalModel: {
		Type:"GlobalAssign"
		Group:"Variable"
		Desc:"Set [GlobalName] to [Model]."
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"
		Create:NewExpr "GlobalName","ModelByName"
	}
	GlobalModel: {
		Type:"Model"
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get global model named [GlobalName]."
		ToCode:=> "g_#{ @[2] }"
		Create:NewExpr "GlobalName"
	}
	InitGlobalBody: {
		Type:"GlobalInit"
		Group:"Variable"
		Desc:"Init [InitGlobalName] to [Body] with note [Text]."
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"..(tostring(@[4]) == "" and "" or " -- #{ @[4] }")
		Create:NewExpr "InitGlobalName","BodyByName","Text"
	}
	SetGlobalBody: {
		Type:"GlobalAssign"
		Group:"Variable"
		Desc:"Set [GlobalName] to [Body]."
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"
		Create:NewExpr "GlobalName","BodyByName"
	}
	GlobalBody: {
		Type:"Body"
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get global body named [GlobalName]."
		ToCode:=> "g_#{ @[2] }"
		Create:NewExpr "GlobalName"
	}
	If: {
		Type:"None"
		Group:"Code Flow"
		Desc:"If condition [Boolean] meets do."
		MultiLine:true
		ToCode:=> "if #{ @[2] } then"
		Create:NewExpr "True","Action","Action"
	}
	Loopi: {
		Type:"None"
		Group:"Code Flow"
		Desc:"Count number i from [Number] to [Number] by [Number] and do."
		MultiLine:true
		ToCode:=> "for i = #{ @[2] }, #{ @[3] }, #{ @[4] } do"
		Create:NewExpr "Number","Number","Number","Action"
	}
	Sleep: {
		Type:"None"
		Group:"Code Flow"
		Desc:"Pause trigger execution for [Number] seconds."
		ToCode:=> "Sleep( #{ @[2] } )"
		Create:NewExpr "Number"
	}
	Note: {
		Type:"None"
		Group:"Code Flow"
		Desc:"Note: [Text]."
		ToCode:=> "-- #{ @[2] }"
		Create:NewExpr "Text"
	}
	Print: {
		Type:"None"
		Group:"Misc"
		Desc:"Print message [String] in console."
		ToCode:=> "Print( #{ @[2] } )"
		Create:NewExpr "String"
	}
	DoNothing: {
		Type:"None"
		Group:"Code Flow"
		Desc:"Do nothing."
		ToCode:=> "DoNothing()"
		Create:NewExpr!
	}
	ModelByName: {
		Type:"Model"
		Group:"Model"
		Desc:"Get model [ModelName] from current scene."
		ToCode:=> "Model( #{ @[2] } )"
		Create:NewExpr "ModelName"
	}
	LayerByName: {
		Type:"Layer"
		Group:"Model"
		Desc:"Get layer [LayerName] from current scene."
		ToCode:=> "Layer( #{ @[2] } )"
		Create:NewExpr "LayerName"
	}
	SensorByName: {
		Type:"Sensor"
		Group:"Sensor"
		Desc:"Get sensor [SensorName] from current scene."
		ToCode:=> "Sensor( #{ @[2] } )"
		Create:NewExpr "SensorName"
	}
	BodyByName: {
		Type:"Body"
		Group:"Body"
		Desc:"Get body [BodyName] from current scene."
		ToCode:=> "Body( #{ @[2] } )"
		Create:NewExpr "BodyName"
	}
	Point: {
		Type:"Point"
		Group:"Point"
		Desc:"Create point of position x [Number] and position y [Number]."
		ToCode:=> "Point( #{ @[2] }, #{ @[3] } )"
		Create:NewExpr "Number","Number"
	}
	CreateModel: {
		Type:"Model"
		TypeIgnore:true
		Group:"Model"
		Desc:"Create model [ModelType] at position [Point] of layer [Layer] with angle [Number] using look [Look] and play [Animation] with loop [Boolean]."
		ToCode:=> "CreateModel( #{ @[2] }, #{ @[3] }, #{ @[4] }, #{ @[5] }, #{ @[6] }, #{ @[7] }, #{ @[8] } )"
		Create:NewExpr "ModelType","Point","LayerByName","Number","Look","Animation","False"
	}
	DestroyModel: {
		Type:"None"
		Group:"Model"
		Desc:"Destroy a model [Model]."
		ToCode:=> "DestroyModel( #{ @[2] } )"
		Create:NewExpr "ModelByName"
	}
	PlayAnimation: {
		Type:"Number"
		TypeIgnore:true
		Group:"Model"
		Desc:"Play animation [Animation] of model [Model] with loop [Boolean] and set model look to [Look], then return animation`s duration."
		ToCode:=> "PlayAnimation( #{ @[2] }, #{ @[3] }, #{ @[4] }, #{ @[5] } )"
		Create:NewExpr "Animation","ModelByName","False","Look"
	}
}

TriggerDef = {
	CodeMode:false
	SetExprMeta:SetExprMeta
	Expressions:Expressions
	ToEditText:(expr)->
		strs = {"return "}
		insert = table.insert
		append = (str)-> insert strs,str
		indent = 0
		nextExpr = (expr)->
			append "{"
			for i = 1,#expr
				item = expr[i]
				switch type item
					when "table"
						indent += 1
						append "\n"
						append string.rep("\t",indent)
						nextExpr item
						indent -= 1
					when "string"
						append "\""
						append item\gsub "\"","\\\""
						append "\""
					else
						append tostring item
				if i ~= #expr
					append ","
			append "}"
		nextExpr expr
		table.concat strs

	ToCodeText:(exprData)->
		codeMode = TriggerDef.CodeMode
		TriggerDef.CodeMode = true
		strs,args = if exprData[1] == "Trigger"
			{"return\n"},exprData[4][2].Args
		else
			{},nil
		insert = table.insert
		rep = string.rep
		append = (indent,str)->
			insert strs,rep("\t",indent) if indent > 0
			insert strs,str if str ~= ""
			insert strs,"\n"
		appendTap = (num)-> rep "\t",num
		localSet = {}
		locals = {}
		nextExpr = (parentExpr,index,indent)->
			expr = index and parentExpr[index] or parentExpr
			switch expr[1]
				when "Trigger"
					append indent,tostring expr
					append 0,"" unless codeMode
					for i = 4,#expr
						nextExpr expr,i,indent+1
					append indent,")"
				when "Event"
					append indent,tostring expr
					for i = 2,#expr
						nextExpr expr,i,indent+1
					append indent,"),"
					indent -= 1
				when "Condition"
					append indent,tostring expr
					for i = 2,#expr
						nextExpr expr,i,indent+1
					append indent,"end ),"
				when "Action"
					append indent,tostring expr
					for i = 2,#expr
						nextExpr expr,i,indent+1
					if #locals > 0
						localLine = rep("\t",indent+1).."local "..table.concat(locals,", ").."\n"
						for i = 1,#strs
							if strs[i]\match "^Action%("
								insert strs,i+2,localLine
								break
					append indent,"end )"
				when "If"
					append indent,tostring expr
					for i = 2,#expr[3]
						nextExpr expr[3],i,indent+1
					append indent,"else"
					for i = 2,#expr[4]
						nextExpr expr[4],i,indent+1
					append indent,"end"
				when "Loopi"
					append indent,tostring expr
					for i = 2,#expr[5]
						nextExpr expr[5],i,indent+1
					append indent,"end"
				when "SetLocal"
					assignExpr = expr[2]
					exprName = assignExpr[1]
					varType = exprName\sub 9,-1
					varName = assignExpr[2][2]
					if varName ~= "InvalidName" and not localSet[varName]
						if not (args and args[varName])
							localSet[varName] = varType
							table.insert locals,varName
					append indent,tostring expr
				else
					append indent,tostring expr
			if parentExpr and parentExpr[1] == "Condition" and parentExpr[#parentExpr] ~= expr
				insert strs,#strs," and"
		nextExpr exprData,nil,0
		TriggerDef.CodeMode = codeMode
		table.concat strs
}

Groups = {}
Types = {}
for exprName,expr in pairs Expressions
	expr.Name = exprName
	expr.MultiLine = false unless expr.MultiLine
	expr.__index = expr
	expr.__tostring = ExprToString
	Groups[expr.Group] or= {}
	table.insert Groups[expr.Group],expr
	Types[expr.Type] or= {}
	table.insert Types[expr.Type],expr
	if expr.Type == "None" or expr.TypeIgnore
		Types["Action"] or= {}
		table.insert Types["Action"],expr
for _,group in pairs Groups
	table.sort group,(a,b)-> a.Name < b.Name
for _,typeList in pairs Types
	table.sort typeList,(a,b)-> a.Name < b.Name

TriggerDef.Groups = Groups
TriggerDef.Types = Types

TriggerDef
