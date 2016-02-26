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
		strs = {}
		insert = table.insert
		append = (str)-> insert strs,str
		append "return "
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
						append item
						append "\""
					else
						append tostring item
				if i ~= #expr
					append ","
			append "}"
		nextExpr expr
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
		String: {
			Type:"String"
			TypeIgnore:false
			Group:"String"
			Desc:"Raw string."
			CodeOnly:true
			Create:=>
				SetExprMeta {@Name,""}
			ToCode:=>
				"\"#{ @[2] }\""
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
			Desc:"Note: [String]."
			Create:=>
				SetExprMeta {@Name
					{"String",""}
				}
			ToCode:=>
				"-- #{ tostring(@[2])\sub(2,-2) }"
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
				"ModelByName( #{ @[2] } )"
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
				"LayerByName( #{ @[2] } )"
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
		PlayAnimation: {
			Type:"Number"
			TypeIgnore:true
			Group:"Model"
			Desc:"Play animation [Animation] of model [Model] with loop [Boolean] and set model look to [Look], then return animation`s duration."
			Create:=>
				SetExprMeta {@Name
					{"Animation",""} -- 2
					{"ModelByName",""} -- 3
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
