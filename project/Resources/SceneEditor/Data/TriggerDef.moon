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
	AIRoot: {
		Text:"AI Root Node"
		Type:"AIRoot"
		Group:"None"
		Desc:"AI Root Node."
		ToCode:=>
			codes = [tostring expr for expr in *@[3,]]
			table.concat {"return AIRoot(", @[2], table.concat(codes,","), ")"}
		Create:NewExpr "TreeName"
	}
	TreeName: {
		Text:"Tree Name"
		Type:"TreeName"
		Group:"Special"
		Desc:"The AI tree`s name."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
	}
	ConName: {
		Text:"Condition Name"
		Type:"ConName"
		Group:"Special"
		Desc:"The condition node`s name."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
	}
	ActName: {
		Text:"Action Name"
		Type:"ActName"
		Group:"Special"
		Desc:"The action node`s name."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
	}
	Sel: {
		Text:"Selection"
		Type:"AINode"
		Group:"AI"
		Desc:"Selection Node."
		ToCode:=>
			codes = [tostring expr for expr in *@[2,]]
			table.concat {"oSel(", table.concat(codes,","), ")"}
		Create:NewExpr!
	}
	Seq: {
		Text:"Sequence"
		Type:"AINode"
		Group:"AI"
		Desc:"Sequence Node."
		ToCode:=>
			codes = [tostring expr for expr in *@[2,]]
			table.concat {"oSeq(", table.concat(codes,","), ")"}
		Create:NewExpr!
	}
	Con: {
		Text:"Condition"
		Type:"AINode"
		Group:"AI"
		Desc:"Condition Node."
		ToCode:=>
			"GCon( #{ @[2] } )"
		Create:NewExpr "ConName"
	}
	Act: {
		Text:"Action"
		Type:"AINode"
		Group:"AI"
		Desc:"Action Node."
		ToCode:=>
			"GAct( \"#{ @[2] }\" )"
		Create:NewExpr "ActName"
	}
	GlobalVar: {
		Text:"Global Variable"
		Type:"GlobalVar"
		Group:"None"
		Desc:"Global variable declaration and initialization."
		ToCode:=>
			codes = [tostring expr for expr in *@[2,]]
			table.insert codes,1,"GlobalScope()"
			table.concat codes,"\n"
		Create:NewExpr!
	}
	ConditionNode: {
		Type:"ConditionNode"
		Group:"None"
		Desc:"This AI condition node named [NodeName] checks"
		ToCode:=> "ConditionNode( #{ @[2] }, function()"
		Create:NewExpr "NodeName","True"
	}
	NodeName: {
		Text:"Node Name"
		Type:"NodeName"
		Group:"Special"
		Desc:"The AI node`s name."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
	}
	UnitAction: {
		Type:"UnitAction"
		Group:"None"
		Desc:"This action is named [ActionName]."
		ToCode:=> "UnitAction( #{ @[2] },"
		Create:NewExpr "ActionName","Priority","Reaction","Recovery","Available","Run","Stop"
	}
	ActionName: {
		Text:"Action Name"
		Type:"ActionName"
		Group:"Special"
		Desc:"The action`s name."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
	}
	Priority: {
		Type:"Priority"
		TypeIgnore:false
		Group:"Special"
		Desc:"Priority [Number] to cancel other action."
		ToCode:=> "--[[Priority]] #{ @[2] },"
		Create:NewExpr "Number"
	}
	Reaction: {
		Type:"Reaction"
		TypeIgnore:false
		Group:"Special"
		Desc:"Reaction [Number] time to response to AI while doing the action."
		ToCode:=> "--[[Reaction]] #{ @[2] },"
		Create:NewExpr "Number"
	}
	Recovery: {
		Type:"Recovery"
		TypeIgnore:false
		Group:"Special"
		Desc:"Recovery [Number] time to restore animation."
		ToCode:=> "--[[Recovery]] #{ @[2] },"
		Create:NewExpr "Number"
	}
	Available: {
		Type:"Available"
		Group:"None"
		Desc:"Tell whether an action is available."
		ToCode:=> "--[[Available]] function( action ) return"
		Create:NewExpr "True"
	}
	Run: {
		Type:"Run"
		Group:"None"
		Desc:"Run action of an unit action."
		ToCode:=> "--[[Run]] function( action )"
		Create:NewExpr "DoNothing"
	}
	Stop: {
		Type:"Stop"
		Group:"None"
		Desc:"Stop function of an unit action."
		ToCode:=> "--[[Stop]] function( action )"
		Create:NewExpr "DoNothing"
	}
	Trigger: {
		Type:"Trigger"
		Group:"None"
		Desc:"The trigger named [TriggerName] is enabled [Boolean]."
		ToCode:=> "Trigger( #{ @[2] }, #{ @[3] },"
		Create:NewExpr "TriggerName","True","Event","Condition","Action"
	}
	TriggerName: {
		Text:"Trigger Name"
		Type:"TriggerName"
		Group:"Special"
		Desc:"The trigger`s name."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
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
		Text:"No Event"
		Type:"Event"
		Group:"Misc"
		Desc:"No event."
		ToCode:=> "NoEvent()"
		Create:NewExpr!
	}
	TimeCycle: {
		Text:"Time Cycle"
		Type:"Event"
		Group:"Time"
		Desc:"Trigger event every [Number] seconds."
		ToCode:=> "TimeCycle( #{ @[2] } )"
		Create:NewExpr "Number"
	}
	BodyEnter: {
		Text:"Body Enter"
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
		Text:"Number Equal"
		Type:"Boolean"
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Number [Number] equals [Number]."
		ToCode:=> "( #{ @[2] } == #{ @[3] } )"
		Create:NewExpr "Number","Number"
	}
	BodyEqual: {
		Text:"Body Equal"
		Type:"Boolean"
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Body [Body] equals [Body]."
		ToCode:=> "( #{ @[2] } == #{ @[3] } )"
		Create:NewExpr "BodyByName","BodyByName"
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
		Text:"Local Name"
		Type:"LocalName"
		Group:"Special"
		Desc:"A name for local value."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExprVal "InvalidName"
	}
	GlobalName: {
		Text:"Global Name"
		Type:"GlobalName"
		Group:"Special"
		Desc:"A name for global value."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExprVal "InvalidName"
	}
	InitGlobalName: {
		Text:"Global Name"
		Type:"InitGlobalName"
		Group:"Special"
		Desc:"A name for global value."
		CodeOnly:true
		ToCode:=> "#{ @[2] == '' and 'InvalidName' or @[2] }"
		Create:NewExprVal ""
	}
	ModelName: {
		Text:"Model Name"
		Type:"ModelName"
		Group:"Special"
		Desc:"A name for model."
		CodeOnly:true
		Item:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
	}
	LayerName: {
		Text:"Layer Name"
		Type:"LayerName"
		Group:"Special"
		Desc:"A name for layer."
		CodeOnly:true
		Item:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
	}
	SensorName: {
		Text:"Sensor Name"
		Type:"SensorName"
		Group:"Special"
		Desc:"A name for sensor."
		CodeOnly:true
		Item:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
	}
	BodyName: {
		Text:"Body Name"
		Type:"BodyName"
		Group:"Special"
		Desc:"A name for body."
		CodeOnly:true
		Item:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
	}
	ModelType: {
		Text:"Model Type"
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
		Text:"Number"
		Type:"LocalAssign"
		Group:"Variable"
		Desc:"Set [LocalName] to [Number]."
		ToCode:=> "#{ @[2] } = #{ @[3] }"
		Create:NewExpr "LocalName","Number"
	}
	LocalNumber: {
		Text:"Local Number"
		Type:"Number"
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get local number named [LocalName]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "LocalName"
	}
	SetLocalString: {
		Text:"String"
		Type:"LocalAssign"
		Group:"Variable"
		Desc:"Set [LocalName] to [String]."
		ToCode:=> "#{ @[2] } = #{ @[3] }"
		Create:NewExpr "LocalName","String"
	}
	LocalString: {
		Text:"Local String"
		Type:"String"
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get local string named [LocalName]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "LocalName"
	}
	SetLocalModel: {
		Text:"Model"
		Type:"LocalAssign"
		Group:"Variable"
		Desc:"Set [LocalName] to [Model]."
		ToCode:=> "#{ @[2] } = #{ @[3] }"
		Create:NewExpr "LocalName","ModelByName"
	}
	LocalModel: {
		Text:"Local Model"
		Type:"Model"
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get local model named [LocalName]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "LocalName"
	}
	SetLocalSensor: {
		Text:"Sensor"
		Type:"LocalAssign"
		Group:"Variable"
		Desc:"Set [LocalName] to [Sensor]."
		ToCode:=> "#{ @[2] } = #{ @[3] }"
		Create:NewExpr "LocalName","SensorByName"
	}
	LocalSensor: {
		Text:"Local Sensor"
		Type:"Sensor"
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get local sensor named [LocalName]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "LocalName"
	}
	SetLocalBody: {
		Text:"Body"
		Type:"LocalAssign"
		Group:"Variable"
		Desc:"Set [LocalName] to [Body]."
		ToCode:=> "#{ @[2] } = #{ @[3] }"
		Create:NewExpr "LocalName","BodyByName"
	}
	LocalBody: {
		Text:"Local Body"
		Type:"Body"
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get local body named [LocalName]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "LocalName"
	}
	SetLocal: {
		Text:"Set Local"
		Type:"None"
		Group:"Variable"
		Desc:"Do [LocalAssign]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "SetLocalNumber"
	}
	SetGlobal: {
		Text:"Set Global"
		Type:"None"
		Group:"Variable"
		Desc:"Do [GlobalAssign]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "SetGlobalNumber"
	}
	InitGlobalNumber: {
		Text:"Number"
		Type:"GlobalInit"
		Group:"Variable"
		Desc:"Initially set global variable [InitGlobalName] to [Number] with note [Text]."
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"..(tostring(@[4]) == "" and "" or " -- #{ @[4] }")
		Create:NewExpr "InitGlobalName","Number","Text"
	}
	SetGlobalNumber: {
		Text:"Number"
		Type:"GlobalAssign"
		Group:"Variable"
		Desc:"Set [GlobalName] to [Number]."
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"
		Create:NewExpr "GlobalName","Number"
	}
	GlobalNumber: {
		Text:"Global Number"
		Type:"Number"
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get global number named [GlobalName]."
		ToCode:=> "g_#{ @[2] }"
		Create:NewExpr "GlobalName"
	}
	InitGlobalModel: {
		Text:"Model"
		Type:"GlobalInit"
		Group:"Variable"
		Desc:"Initially set global variable [InitGlobalName] to [Model] with note [Text]."
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"..(tostring(@[4]) == "" and "" or " -- #{ @[4] }")
		Create:NewExpr "InitGlobalName","ModelByName","Text"
	}
	SetGlobalModel: {
		Text:"Model"
		Type:"GlobalAssign"
		Group:"Variable"
		Desc:"Set [GlobalName] to [Model]."
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"
		Create:NewExpr "GlobalName","ModelByName"
	}
	GlobalModel: {
		Text:"Global Model"
		Type:"Model"
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get global model named [GlobalName]."
		ToCode:=> "g_#{ @[2] }"
		Create:NewExpr "GlobalName"
	}
	InitGlobalBody: {
		Text:"Body"
		Type:"GlobalInit"
		Group:"Variable"
		Desc:"Initially set global variable [InitGlobalName] to [Body] with note [Text]."
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"..(tostring(@[4]) == "" and "" or " -- #{ @[4] }")
		Create:NewExpr "InitGlobalName","BodyByName","Text"
	}
	SetGlobalBody: {
		Text:"Body"
		Type:"GlobalAssign"
		Group:"Variable"
		Desc:"Set [GlobalName] to [Body]."
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"
		Create:NewExpr "GlobalName","BodyByName"
	}
	GlobalBody: {
		Text:"Global Body"
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
		Text:"Do Nothing"
		Type:"None"
		Group:"Code Flow"
		Desc:"Do nothing."
		ToCode:=> "DoNothing()"
		Create:NewExpr!
	}
	ModelByName: {
		Text:"Model"
		Type:"Model"
		Group:"Model"
		Desc:"Get model [ModelName] from current scene."
		ToCode:=> "Model( #{ @[2] } )"
		Create:NewExpr "ModelName"
	}
	LayerByName: {
		Text:"Layer"
		Type:"Layer"
		Group:"Model"
		Desc:"Get layer [LayerName] from current scene."
		ToCode:=> "Layer( #{ @[2] } )"
		Create:NewExpr "LayerName"
	}
	SensorByName: {
		Text:"Sensor"
		Type:"Sensor"
		Group:"Sensor"
		Desc:"Get sensor [SensorName] from current scene."
		ToCode:=> "Sensor( #{ @[2] } )"
		Create:NewExpr "SensorName"
	}
	BodyByName: {
		Text:"Body"
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
		Text:"Create Model"
		Type:"Model"
		TypeIgnore:true
		Group:"Model"
		Desc:"Create model [ModelType] at position [Point] of layer [Layer] with angle [Number] using look [Look] and play [Animation] with loop [Boolean]."
		ToCode:=> "CreateModel( #{ @[2] }, #{ @[3] }, #{ @[4] }, #{ @[5] }, #{ @[6] }, #{ @[7] }, #{ @[8] } )"
		Create:NewExpr "ModelType","Point","LayerByName","Number","Look","Animation","False"
	}
	DestroyModel: {
		Text:"Destroy Model"
		Type:"None"
		Group:"Model"
		Desc:"Destroy a model [Model]."
		ToCode:=> "DestroyModel( #{ @[2] } )"
		Create:NewExpr "ModelByName"
	}
	PlayAnimation: {
		Text:"Play Animation"
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

		strs,args = switch exprData[1]
			when "Trigger"
				eventArgs = exprData[4][2].Args or {}
				{"return\n"},{k,v\match "%a*" for k,v in pairs eventArgs}
			when "UnitAction"
				{"return\n"},{action:"Action"}
			else
				{},{}

		insert = table.insert
		rep = string.rep
		append = (indent,str)->
			insert strs,rep("\t",indent) if indent > 0
			insert strs,str if str ~= ""
			insert strs,"\n"
		appendTap = (num)-> rep "\t",num

		local localSet
		local locals
		local nextExpr
		createHandleAction = (startPattern,ending="")->
			(indent,expr)->
				localSet = {k,v for k,v in pairs args}
				locals = {}
				append indent,tostring expr
				for i = 2,#expr
					nextExpr expr,i,indent+1
				if #locals > 0
					localLine = rep("\t",indent+1).."local "..table.concat(locals,", ").."\n"
					for i = 1,#strs
						if strs[i]\match startPattern
							insert strs,i+2,localLine
							break
				append indent,"end )"..ending

		handleAction = createHandleAction "^Action%("
		handleRun = createHandleAction "^%-%-%[%[Run%]%]",","
		handleStop = createHandleAction "^%-%-%[%[Stop%]%]"

		nextExpr = (parentExpr,index,indent)->
			expr = index and parentExpr[index] or parentExpr
			switch expr[1]
				when "Trigger"
					append indent,tostring expr
					append 0,"" unless TriggerDef.CodeMode
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
					handleAction indent,expr
				when "UnitAction"
					append indent,tostring expr
					append 0,"" unless TriggerDef.CodeMode
					for i = 3,#expr
						nextExpr expr,i,indent+1
					append indent,")"
				when "Available"
					append indent,tostring expr
					for i = 2,#expr
						nextExpr expr,i,indent+1
					append indent,"end ),"
				when "Run"
					handleRun indent,expr
				when "Stop"
					handleStop indent,expr
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
			if parentExpr
				switch parentExpr[1]
					when "Condition","Available"
						if parentExpr[#parentExpr] ~= expr
							insert strs,#strs," and"
		nextExpr exprData,nil,0
		TriggerDef.CodeMode = codeMode
		table.concat strs

	GetLintFunction:(locals,globals)->
		errors = nil
		varScope = {locals}
		varInScope = (varName)->
			for scope in *varScope
				varType = scope[varName]
				return varType if varType
			return nil
		err = (...)-> table.insert errors,table.concat{...}
		pushScope = -> table.insert varScope,{}
		popScope = -> table.remove varScope
		nextExpr = (expr,parentExpr)->
			return if "table" ~= type expr
			switch expr[1]
				when "Trigger"
					nextExpr expr[3]
				when "Condition","Action","UnitAction","ConditionNode","Available","Run","Stop","Event"
					return
				when "SetLocal"
					assignExpr = expr[2]
					varName = assignExpr[2][2]
					if varName == "InvalidName"
						err "Use local variable with invalid name."
					elseif varName\sub(1,2) == "g_" and globals[varName\sub 3]
						err "Name of local variable duplicates with global variable \"",
							varName, "\"."
					else
						localType = varInScope varName
						varType = assignExpr[1]\match "^SetLocal(.*)"
						if localType and localType ~= varType
							err "Assign local variable \"",varName,
								"\" of type \"",localType,
								"\" to value of type \"",varType,"\"."
						else
							scope = varScope[#varScope]
							scope[varName] = varType
					nextExpr assignExpr[3],assignExpr
				when "SetGlobal"
					assignExpr = expr[2]
					varName = assignExpr[2][2]
					if varName == "InvalidName"
						err "Use global variable with invalid name."
					varType = assignExpr[1]\match "^SetGlobal(.*)"
					globalType = globals[varName]
					if globalType
						if globalType ~= varType
							err "Assign global variable \"g_",varName,
								"\" of type \"",globalType,
								"\" to value of type \"",varType,"\"."
					else
						err "Assign an uninitialized global variable \"g_",varName,
							"\" to value of type \"",varType,"\"."
					nextExpr assignExpr[3],assignExpr
				when "LocalName"
					varName = expr[2]
					if varName == "InvalidName"
						err "Use local variable with invalid name."
						return
					elseif varName\sub(1,2) == "g_" and globals[varName\sub 3]
						err "Name of local variable duplicates with global variable \"",
							varName, "\"."
						return
					localType = varInScope varName
					varType = parentExpr[1]\match "^Local(.*)"
					if localType
						if localType ~= varType
							err "Local variable \"",varName,
								"\" of type \"",localType,
								"\" is used as type \"",varType,"\"."
					else
						err "Local variable \"",varName,
							"\" of type \"",varType,
							"\" is used without initialization."
				when "GlobalName"
					varName = expr[2]
					if varName == "InvalidName"
						err "Use global variable with invalid name."
						return
					globalType = globals[varName]
					varType = parentExpr[1]\match "^Global(.*)"
					if globalType
						if globalType ~= varType
							err "Global variable \"g_",varName,
								"\" of type \"",globalType,
								"\" is used as type \"",varType,"\"."
					else
						err "Global variable \"g_",varName,
							"\" of type \"",varType,
							"\" is used without initialization."
				else
					for subExpr in *expr[2,]
						nextExpr subExpr,expr
		checkExpr = (expr,parentExpr,itemType)->
			errors = {} if errors == nil or #errors > 0
			switch itemType
				when "Start"
					nextExpr expr,parentExpr
					pushScope!
				when "Mid"
					popScope!
					pushScope!
				when "End"
					popScope!
				else
					nextExpr expr,parentExpr
			#errors > 0 and table.concat(errors,"\n") or ""
		checkExpr

	LintNotPass:(exprData)->
		args = switch exprData[1]
			when "Trigger"
				exprData[4][2].Args
			when "UnitAction"
				action:"Action"
			else
				{}
		locals = args and {k,v\match("^%a*") for k,v in pairs args} or nil
		globals = {expr[2][2],expr[3].Type for expr in *editor\getGlobalExpr![2,]}

		lintFunc = TriggerDef.GetLintFunction locals,globals

		checkError = (parentExpr,index)->
			expr = index and parentExpr[index] or parentExpr
			switch expr[1]
				when "Trigger"
					for i = 4,#expr
						return true if checkError expr,i
				when "UnitAction"
					for i = 3,#expr
						return true if checkError expr,i
				when "Event","Condition","Action","Available","Run","Stop"
					return true if lintFunc(expr,parentExpr,"Start") ~= ""
					for i = 2,#expr
						return true if checkError expr,i
					return true if lintFunc(expr,parentExpr,"End") ~= ""
				when "If"
					return true if lintFunc(expr,parentExpr,"Start") ~= ""
					for i = 2,#expr[3]
						return true if checkError expr[3],i
					return true if lintFunc(expr,parentExpr,"Mid") ~= ""
					for i = 2,#expr[4]
						return true if checkError expr[4],i
					return true if lintFunc(expr,parentExpr,"End") ~= ""
				when "Loopi"
					return true if lintFunc(expr,parentExpr,"Start") ~= ""
					for i = 2,#expr[5]
						return true if checkError expr[5],i
					return true if lintFunc(expr,parentExpr,"End") ~= ""
				else
					return true if lintFunc(expr,parentExpr) ~= ""
			false

		checkError exprData
}

Groups = {}
Types = {}
for exprName,expr in pairs Expressions
	expr.Name = exprName
	expr.MultiLine = false unless expr.MultiLine
	expr.TypeIgnore = false unless expr.TypeIgnore
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
