local TriggerDef

SetExprMeta = (expr)->
	for i = 2,#expr
		SetExprMeta expr[i] if "table" == type expr[i]
	setmetatable expr,TriggerDef.Expressions[expr[1]]

__tostring = (expr)->
	if TriggerDef.CodeMode or expr.CodeOnly
		expr\ToCode!
	else
		index = 1
		expr.Desc\gsub "%b[]",->
			index += 1
			"(#{tostring expr[index]})"

TriggerDef = {
	CodeMode:false
	:SetExprMeta
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
		strs = {"return\n"}
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
					append indent,"Action( function()"
					for i = 2,#expr
						nextExpr expr,i,indent+1
					if #locals > 0
						localLine = rep("\t",indent+1).."local "..table.concat(locals,", ").."\n"
						for i = 1,#strs
							if strs[i] == "Action( function()"
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
				else
					exprName = expr[1]
					if "SetLocal" == exprName\sub 1,8
						varType = exprName\sub 9,-1
						varName = expr[2][2]
						if not localSet[varName]
							localSet[varName] = varType
							table.insert locals,varName
					append indent,tostring expr
		nextExpr exprData,nil,0
		TriggerDef.CodeMode = codeMode
		table.concat strs

	Expressions: {
		Trigger: {
			Type:"Trigger"
			Group:"None"
			Desc:"The trigger named [TriggerName] is enabled [Boolean]."
			Create:(triggerName)=>
				SetExprMeta {@Name
					{"TriggerName",triggerName or "triggerName"}
					{"True"}
					{"Event"
						{"NoEvent"}
					}
					{"Condition"
						{"True"}
					}
					{"Action"
						{"DoNothing"}
					}
				}
			ToCode:=>
				"Trigger( #{ @[2] }, #{ @[3] },"
			:__tostring
		}
		Event: {
			Type:"EventType"
			Group:"None"
			Desc:"Event to trigger."
			Create:=>
				SetExprMeta {@Name}
			ToCode:=> "Event("
			:__tostring
		}
		Action: {
			Type:"ActionSequence"
			Group:"None"
			Desc:"An action execution sequence."
			Create:=>
				SetExprMeta {@Name}
			ToCode:=> "ActionSequence"
			:__tostring
		}
		Condition: {
			Type:"Condition"
			Group:"None"
			Desc:"Condition value."
			Create:=>
				SetExprMeta {@Name}
			ToCode:=> "Condition( function() return"
			:__tostring
		}
		NoEvent: {
			Type:"Event"
			Group:"Misc"
			Desc:"No event."
			Create:=>
				SetExprMeta {@Name}
			ToCode:=>
				"NoEvent()"
			:__tostring
		}
		TimeCycle: {
			Type:"Event"
			Group:"Time"
			Desc:"Trigger event every [Number] seconds."
			Create:=>
				SetExprMeta {@Name
					{"Number",0}
				}
			ToCode:=>
				"TimeCycle( #{ @[2] } )"
			:__tostring
		}
		And: {
			Type:"Boolean"
			TypeIgnore:false
			Group:"Boolean"
			Desc:"Boolean [Boolean] and [Boolean]."
			Create:=>
				SetExprMeta {@Name
					{"True"}
					{"True"}
				}
			ToCode:=>
				"( #{ @[2] } and #{ @[3] } )"
			:__tostring
		}
		Or: {
			Type:"Boolean"
			TypeIgnore:false
			Group:"Boolean"
			Desc:"Boolean [Boolean] or [Boolean]."
			Create:=>
				SetExprMeta {@Name
					{"True"}
					{"True"}
				}
			ToCode:=>
				"( #{ @[2] } or #{ @[3] } )"
			:__tostring
		}
		Add: {
			Type:"Number"
			TypeIgnore:false
			Group:"Number"
			Desc:"Number [Number] + [Number]."
			Create:=>
				SetExprMeta {@Name
					{"Number",0}
					{"Number",0}
				}
			ToCode:=>
				"( #{ @[2] } + #{ @[3] } )"
			:__tostring
		}
		GlobalNumber: {
			Type:"Number"
			TypeIgnore:false
			Group:"Variable"
			Desc:"Get global number named [GlobalName]."
			Create:=>
				SetExprMeta {@Name
					{"GlobalName","globalName"}
				}
			ToCode:=>
				"G.#{ @[2] }"
			:__tostring
		}
		String: {
			Type:"String"
			TypeIgnore:false
			Group:"String"
			Desc:"Raw string."
			CodeOnly:true
			Create:=>
				SetExprMeta {@Name,""}
			ToCode:=>
				"\"#{ @[2]\gsub('\"','\\\"') }\""
			:__tostring
		}
		Number: {
			Type:"Number"
			TypeIgnore:false
			Group:"Number"
			Desc:"Raw number."
			CodeOnly:true
			Create:=>
				SetExprMeta {@Name,0}
			ToCode:=>
				"#{ @[2] }"
			:__tostring
		}
		True: {
			Type:"Boolean"
			TypeIgnore:false
			Group:"Boolean"
			Desc:"Boolean true."
			CodeOnly:true
			Create:=>
				SetExprMeta {@Name}
			ToCode:=>
				"true"
			:__tostring
		}
		False: {
			Type:"Boolean"
			TypeIgnore:false
			Group:"Boolean"
			Desc:"Boolean false."
			CodeOnly:true
			Create:=>
				SetExprMeta {@Name}
			ToCode:=>
				"false"
			:__tostring
		}
		NumberEqual: {
			Type:"Boolean"
			TypeIgnore:false
			Group:"Boolean"
			Desc:"Number [Number] equals [Number]."
			Create:=>
				SetExprMeta {@Name
					{"Number",0}
					{"Number",0}
				}
			ToCode:=>
				"( #{ @[2] } == #{ @[3] } )"
			:__tostring
		}
		TriggerName: {
			Type:"TriggerName"
			Group:"Special"
			Desc:"The trigger`s name."
			CodeOnly:true
			Create:=>
				SetExprMeta {@Name,""}
			ToCode:=>
				"\"#{ @[2] }\""
			:__tostring
		}
		Text: {
			Type:"Text"
			Group:"Special"
			Desc:"The note text."
			CodeOnly:true
			Create:=>
				SetExprMeta {@Name,""}
			ToCode:=>
				"#{ @[2] }"
			:__tostring
		}
		LocalName: {
			Type:"LocalName"
			Group:"Special"
			Desc:"A name for local value."
			CodeOnly:true
			Create:=>
				SetExprMeta {@Name,"localName"}
			ToCode:=>
				"#{ @[2] }"
			:__tostring
		}
		GlobalName: {
			Type:"GlobalName"
			Group:"Special"
			Desc:"A name for global value."
			CodeOnly:true
			Create:=>
				SetExprMeta {@Name,"globalName"}
			ToCode:=>
				"#{ @[2] }"
			:__tostring
		}
		ModelName: {
			Type:"ModelName"
			Group:"Special"
			Desc:"A name for model."
			CodeOnly:true
			Item:true
			Create:=>
				SetExprMeta {@Name,""}
			ToCode:=>
				"\"#{ @[2] }\""
			:__tostring
		}
		LayerName: {
			Type:"LayerName"
			Group:"Special"
			Desc:"A name for layer."
			CodeOnly:true
			Item:true
			Create:=>
				SetExprMeta {@Name,""}
			ToCode:=>
				"\"#{ @[2] }\""
			:__tostring
		}
		SensorName: {
			Type:"SensorName"
			Group:"Special"
			Desc:"A name for sensor."
			CodeOnly:true
			Item:true
			Create:=>
				SetExprMeta {@Name,""}
			ToCode:=>
				"\"#{ @[2] }\""
			:__tostring
		}
		ModelType: {
			Type:"ModelType"
			Group:"Special"
			Desc:"A type name for model."
			CodeOnly:true
			Create:=>
				SetExprMeta {@Name,""}
			ToCode:=>
				"\"#{ @[2] }\""
			:__tostring
		}
		Animation: {
			Type:"Animation"
			Group:"Special"
			Desc:"A name for animation."
			CodeOnly:true
			Create:=>
				SetExprMeta {@Name,""}
			ToCode:=>
				"\"#{ @[2] }\""
			:__tostring
		}
		Look: {
			Type:"Look"
			Group:"Special"
			Desc:"A name for look."
			CodeOnly:true
			Create:=>
				SetExprMeta {@Name,""}
			ToCode:=>
				"\"#{ @[2] }\""
			:__tostring
		}
		SetLocalNumber: {
			Type:"None"
			Group:"Variable"
			Desc:"Set [LocalName] to [Number]."
			Create:=>
				SetExprMeta {@Name
					{"LocalName","localName"}
					{"Number",0}
				}
			ToCode:=>
				"#{ @[2] } = #{ @[3] }"
			:__tostring
		}
		LocalNumber: {
			Type:"Number"
			TypeIgnore:false
			Group:"Variable"
			Desc:"Get local number named [LocalName]."
			CodeOnly:true
			Create:=>
				SetExprMeta {@Name
					{"LocalName","localName"}
				}
			ToCode:=>
				"#{ @[2] }"
			:__tostring
		}
		SetLocalString: {
			Type:"None"
			Group:"Variable"
			Desc:"Set [LocalName] to [String]."
			Create:=>
				SetExprMeta {@Name
					{"LocalName","localName"}
					{"String",""}
				}
			ToCode:=>
				"#{ @[2] } = #{ @[3] }"
			:__tostring
		}
		LocalString: {
			Type:"String"
			TypeIgnore:false
			Group:"Variable"
			Desc:"Get local string named [LocalName]."
			CodeOnly:true
			Create:=>
				SetExprMeta {@Name
					{"LocalName","localName"}
				}
			ToCode:=>
				"#{ @[2] }"
			:__tostring
		}
		SetLocalModel: {
			Type:"None"
			Group:"Variable"
			Desc:"Set [LocalName] to [Model]."
			Create:=>
				SetExprMeta {@Name
					{"LocalName","localName"}
					{"ModelByName"
						{"ModelName",""}
					}
				}
			ToCode:=>
				"#{ @[2] } = #{ @[3] }"
			:__tostring
		}
		LocalModel: {
			Type:"Model"
			TypeIgnore:false
			Group:"Variable"
			Desc:"Get local model named [LocalName]."
			CodeOnly:true
			Create:=>
				SetExprMeta {@Name
					{"LocalName","localName"}
				}
			ToCode:=>
				"#{ @[2] }"
			:__tostring
		}
		SetLocalSensor: {
			Type:"None"
			Group:"Variable"
			Desc:"Set [LocalName] to [Sensor]."
			Create:=>
				SetExprMeta {@Name
					{"LocalName","localName"}
					{"SensorByName"
						{"SensorName",""}
					}
				}
			ToCode:=>
				"#{ @[2] } = #{ @[3] }"
			:__tostring
		}
		LocalSensor: {
			Type:"Sensor"
			TypeIgnore:false
			Group:"Variable"
			Desc:"Get local sensor named [LocalName]."
			CodeOnly:true
			Create:=>
				SetExprMeta {@Name
					{"LocalName","localName"}
				}
			ToCode:=>
				"#{ @[2] }"
			:__tostring
		}
		SetGlobalNumber: {
			Type:"None"
			Group:"Variable"
			Desc:"Set [GlobalName] to [Number]."
			Create:=>
				SetExprMeta {@Name
					{"GlobalName","globalName"}
					{"Number",0}
				}
			ToCode:=>
				"G.#{ @[2] } = #{ @[3] }"
			:__tostring
		}
		If: {
			Type:"None"
			Group:"Code Flow"
			Desc:"If condition [Boolean] meets do."
			MultiLine:true
			Create:=>
				SetExprMeta {@Name
					{"True"}
					{"Action"
						{"DoNothing"}
					}
					{"Action"
						{"DoNothing"}
					}
				}
			ToCode:=>
				"if #{ @[2] } then"
			:__tostring
		}
		Loopi: {
			Type:"None"
			Group:"Code Flow"
			Desc:"Count number i from [Number] to [Number] by [Number] and do."
			MultiLine:true
			Create:=>
				SetExprMeta {@Name,
					{"Number",0}
					{"Number",0}
					{"Number",0}
					{"Action"
						{"DoNothing"}
					}
				}
			ToCode:=>
				"for i = #{ @[2] }, #{ @[3] }, #{ @[4] } do"
			:__tostring
		}
		Sleep: {
			Type:"None"
			Group:"Code Flow"
			Desc:"Pause trigger execution for [Number] seconds."
			Create:=>
				SetExprMeta {@Name
					{"Number",0}
				}
			ToCode:=>
				"Sleep( #{ @[2] } )"
			:__tostring
		}
		Note: {
			Type:"None"
			Group:"Code Flow"
			Desc:"Note: [Text]."
			Create:=>
				SetExprMeta {@Name
					{"Text",""}
				}
			ToCode:=>
				"-- #{ @[2] }"
			:__tostring
		}
		Print: {
			Type:"None"
			Group:"Misc"
			Desc:"Print message [String] in console."
			Create:=>
				SetExprMeta {@Name
					{"String",""}
				}
			ToCode:=>
				"Print( #{ @[2] } )"
			:__tostring
		}
		DoNothing: {
			Type:"None"
			Group:"Code Flow"
			Desc:"Do nothing."
			Create:=>
				SetExprMeta {@Name}
			ToCode:=>
				"DoNothing()"
			:__tostring
		}
		ModelByName: {
			Type:"Model"
			TypeIgnore:false
			Group:"Model"
			Desc:"Get model [ModelName] from current scene."
			Create:=>
				SetExprMeta {@Name
					{"ModelName",""}
				}
			ToCode:=>
				"Model( #{ @[2] } )"
			:__tostring
		}
		LayerByName: {
			Type:"Layer"
			TypeIgnore:false
			Group:"Model"
			Desc:"Get layer [LayerName] from current scene."
			Create:=>
				SetExprMeta {@Name
					{"LayerName",""}
				}
			ToCode:=>
				"Layer( #{ @[2] } )"
			:__tostring
		}
		SensorByName: {
			Type:"Sensor"
			TypeIgnore:false
			Group:"Sensor"
			Desc:"Get sensor [SensorName] from current scene."
			Create:=>
				SetExprMeta {@Name
					{"SensorName",""}
				}
			ToCode:=>
				"Sensor( #{ @[2] } )"
			:__tostring
		}
		Point: {
			Type:"Point"
			TypeIgnore:false
			Group:"Point"
			Desc:"Create point of position x [Number] and position y [Number]."
			Create:=>
				SetExprMeta {@Name
					{"Number",0}
					{"Number",0}
				}
			ToCode:=>
				"Point( #{ @[2] }, #{ @[3] } )"
			:__tostring
		}
		CreateModel: {
			Type:"Model"
			TypeIgnore:true
			Group:"Model"
			Desc:"Create model [ModelType] at position [Point] of layer [Layer] with angle [Number] using look [Look] and play [Animation] with loop [Boolean]."
			Create:=>
				SetExprMeta {@Name
					{"ModelType",""} -- 2
					{"Point" -- 3
						{"Number",0}
						{"Number",0}
					}
					{"LayerByName" -- 4
						{"LayerName",""}
					}
					{"Number",0} -- 5
					{"Look",""} -- 6
					{"Animation",""} -- 7
					{"False"} -- 8
				}
			ToCode:=>
				"CreateModel( #{ @[2] }, #{ @[3] }, #{ @[4] }, #{ @[5] }, #{ @[6] }, #{ @[7] }, #{ @[8] } )"
			:__tostring
		}
		DestroyModel: {
			Type:"None"
			Group:"Model"
			Desc:"Destroy a model [Model]."
			Create:=>
				SetExprMeta {@Name
					{"ModelByName",
						{"ModelName",""}
					}
				}
			ToCode:=>
				"DestroyModel( #{ @[2] } )"
			:__tostring
		}
		PlayAnimation: {
			Type:"Number"
			TypeIgnore:true
			Group:"Model"
			Desc:"Play animation [Animation] of model [Model] with loop [Boolean] and set model look to [Look], then return animation`s duration."
			Create:=>
				SetExprMeta {@Name
					{"Animation",""} -- 2
					{"ModelByName",
						{"ModelName",""}
					} -- 3
					{"False"} -- 4
					{"Look",""} -- 5
				}
			ToCode:=>
				"PlayAnimation( #{ @[2] }, #{ @[3] }, #{ @[4] }, #{ @[5] } )"
			:__tostring
		}
	}
}

Groups = {}
Types = {}
for exprName,expr in pairs TriggerDef.Expressions
	expr.Name = exprName
	expr.MultiLine = false unless expr.MultiLine
	expr.__index = expr
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
