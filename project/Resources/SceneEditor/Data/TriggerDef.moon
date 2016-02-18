local TriggerDef

SetExprMeta = (expr)->
	for i = 2,#expr
		SetExprMeta expr[i] if "table" == type expr[i]
	setmetatable expr,TriggerDef.Expressions[expr[1]]

TriggerDef = {
	:SetExprMeta
	Expressions: {
		Trigger: {
			Type:"Trigger"
			Group:"None"
			Desc:"A trigger."
			Create:=>
				SetExprMeta {@Name
					{"Event"}
					{"Condition"}
					{"Action"}
				}
			__tostring:=> "Trigger"
		}
		Event: {
			Type:"EventType"
			Group:"None"
			Desc:"Event to trigger."
			Create:=>
				SetExprMeta {@Name}
			__tostring:=> "EventType"
		}
		Action: {
			Type:"ActionSequence"
			Group:"None"
			Desc:"An action execution sequence."
			Create:=>
				SetExprMeta {@Name}
			__tostring:=> "ActionSequence"
		}
		Condition: {
			Type:"Condition"
			Group:"None"
			Desc:"Condition value."
			Create:=>
				SetExprMeta {@Name}
			__tostring:=> "Condition"
		}
		TimeCycle: {
			Type:"Event"
			Group:"Time"
			Desc:"Trigger event every [Number] seconds."
			Create:=>
				SetExprMeta {@Name
					{"Number",0}
				}
			__tostring:=>
				"TimeCycle( #{ @[2] } )"
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
			__tostring:=>
				"( #{ @[2] } and #{ @[3] } )"
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
			__tostring:=>
				"( #{ @[2] } or #{ @[3] } )"
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
			__tostring:=>
				"( #{ @[2] } + #{ @[3] } )"
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
			__tostring:=>
				"GlobalNumber( #{ @[2] } )"
		}
		LocalNumber: {
			Type:"Number"
			TypeIgnore:false
			Group:"Variable"
			Desc:"Get local number named [LocalName]."
			Create:=>
				SetExprMeta {@Name
					{"LocalName","localName"}
				}
			__tostring:=>
				"#{ @[2] }"
		}
		String: {
			Type:"String"
			TypeIgnore:false
			Group:"String"
			Desc:"Raw string."
			Create:=>
				SetExprMeta {@Name,""}
			__tostring:=>
				"\"#{ @[2] }\""
		}
		Number: {
			Type:"Number"
			TypeIgnore:false
			Group:"Number"
			Desc:"Raw number."
			Create:=>
				SetExprMeta {@Name,0}
			__tostring:=>
				"#{ @[2] }"
		}
		True: {
			Type:"Boolean"
			TypeIgnore:false
			Group:"Boolean"
			Desc:"Boolean true."
			Create:=>
				SetExprMeta {@Name}
			__tostring:=>
				"true"
		}
		False: {
			Type:"Boolean"
			TypeIgnore:false
			Group:"Boolean"
			Desc:"Boolean false."
			Create:=>
				SetExprMeta {@Name}
			__tostring:=>
				"false"
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
			__tostring:=>
				"( #{ @[2] } == #{ @[3] } )"
		}
		LocalName: {
			Type:"LocalName"
			Group:"Special"
			Desc:"A name for local value."
			Create:=>
				SetExprMeta {@Name,"localName"}
			__tostring:=>
				"#{ @[2] }"
		}
		GlobalName: {
			Type:"GlobalName"
			Group:"Special"
			Desc:"A name for global value."
			Create:=>
				SetExprMeta {@Name,"globalName"}
			__tostring:=>
				"\"#{ @[2] }\""
		}
		ModelName: {
			Type:"ModelName"
			Group:"Special"
			Desc:"A name for model."
			Create:=>
				SetExprMeta {@Name,""}
			__tostring:=>
				"\"#{ @[2] }\""
		}
		LayerName: {
			Type:"LayerName"
			Group:"Special"
			Desc:"A name for layer."
			Create:=>
				SetExprMeta {@Name,""}
			__tostring:=>
				"\"#{ @[2] }\""
		}
		ModelType: {
			Type:"ModelType"
			Group:"Special"
			Desc:"A type name for model."
			Create:=>
				SetExprMeta {@Name,""}
			__tostring:=>
				"\"#{ @[2] }\""
		}
		Animation: {
			Type:"Animation"
			Group:"Special"
			Desc:"A name for animation."
			Create:=>
				SetExprMeta {@Name,""}
			__tostring:=>
				"\"#{ @[2] }\""
		}
		Look: {
			Type:"Look"
			Group:"Special"
			Desc:"A name for look."
			Create:=>
				SetExprMeta {@Name,""}
			__tostring:=>
				"\"#{ @[2] }\""
		}
		SetLocalNumber: {
			Type:"None"
			TypeIgnore:true
			Group:"Variable"
			Desc:"Set [LocalName] to [Number]."
			Create:=>
				SetExprMeta {@Name
					{"LocalName","localName"}
					{"Number",0}
				}
			__tostring:=>
				"#{ @[2] } = #{ @[3] }"
		}
		SetGlobalNumber: {
			Type:"None"
			TypeIgnore:true
			Group:"Variable"
			Desc:"Set [GlobalName] to [Number]."
			Create:=>
				SetExprMeta {@Name
					{"GlobalName","globalName"}
					{"Number",0}
				}
			__tostring:=>
				"SetGlobalNumber( #{ @[2] }, #{ @[3] } )"
		}
		If: {
			Type:"None"
			Group:"Code Flow"
			Desc:"If condition [Boolean] meets do [ActionSequence] otherwise do [ActionSequence]."
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
			__tostring:=>
				"if #{ @[2] } then"
		}
		Loopi: {
			Type:"None"
			Group:"Code Flow"
			Desc:"Count number i from [Number] to [Number] by [Number] and do [ActionSequence]."
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
			__tostring:=>
				"for i = #{ @[2] }, #{ @[3] }, #{ @[4] } do"
		}
		Sleep: {
			Type:"None"
			Group:"Code Flow"
			Desc:"Pause trigger execution for [Number] seconds."
			Create:=>
				SetExprMeta {@Name
					{"Number",0}
				}
			__tostring:=>
				"Sleep( #{ @[2] } )"
		}
		Print: {
			Type:"None"
			Group:"Misc"
			Desc:"Print message [String] in console."
			Create:=>
				SetExprMeta {@Name
					{"String",""}
				}
			__tostring:=>
				"Print( #{ @[2] } )"
		}
		DoNothing: {
			Type:"None"
			Group:"Code Flow"
			Desc:"Do nothing."
			Create:=>
				SetExprMeta {@Name}
			__tostring:=>
				"DoNothing()"
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
			__tostring:=>
				"ModelByName( #{ @[2] } )"
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
			__tostring:=>
				"LayerByName( #{ @[2] } )"
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
			__tostring:=>
				"Point( #{ @[2] }, #{ @[3] } )"
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
			__tostring:=>
				"CreateModel( #{ @[2] }, #{ @[3] }, #{ @[4] }, #{ @[5] }, #{ @[6] }, #{ @[7] }, #{ @[8] } )"
		}
		PlayAnimation: {
			Type:"None"
			Group:"Model"
			Desc:"Set look of model [Model] to [Look] and play animation [Animation] with loop [Boolean]."
			Create:=>
				SetExprMeta {@Name
					{"ModelByName",""} -- 2
					{"Look",""} -- 3
					{"Animation",""} -- 4
					{"False"} -- 5
				}
			__tostring:=>
				"PlayAnimation( #{ @[2] }, #{ @[3] }, #{ @[4] }, #{ @[5] } )"
		}
	}
	RawData: {
		LayerName:->
		LocalName:->
		GlobalName:->
		ModelName:->
		ModelType:->
		Number:->
		String:->
		Look:->
		Animation:->
	}
	Derivations: {
		{Base:"Number",Sub:"GlobalNumber"}
		{Base:"Number",Sub:"LocalNumber"}
	}
}

Groups = {}
Types = {}
for exprName,expr in pairs TriggerDef.Expressions
	expr.Name = exprName
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
