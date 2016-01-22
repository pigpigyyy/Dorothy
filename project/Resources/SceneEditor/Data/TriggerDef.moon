{
	Events: {
		TimeCycle: {
			Group:"Time"
			Desc:"Trigger event every [Number] seconds."
		}
	}
	Expressions: {
		And: {
			Type:"Boolean"
			TypeIgnore:false
			Group:"Boolean"
			Desc:"[Boolean] and [Boolean]."
		}
		Or: {
			Type:"Boolean"
			TypeIgnore:false
			Group:"Boolean"
			Desc:"[Boolean] or [Boolean]."
		}
		Add: {
			Type:"Number"
			TypeIgnore:false
			Group:"Number"
			Desc:"[Number] + [Number]."
		}
		GlobalNumber: {
			Type:"GlobalNumber"
			TypeIgnore:false
			Group:"Number"
			Desc:"Get global number named [String]."
		}
		Number: {
			Type:"Number"
			TypeIgnore:false
			Group:"Number"
			Desc:"Raw number."
		}
		True: {
			Type:"Boolean"
			TypeIgnore:false
			Group:"Boolean"
			Desc:"Boolean true."
		}
		NumberEqual: {
			Type:"Boolean"
			TypeIgnore:false
			Group:"Boolean"
			Desc:"Number [Number] equals [Number]."
		}
		AssignLocal: {
			Type:"Number"
			TypeIgnore:true
			Group:"Code Flow"
			Desc:"Assign [LocalNumber] to [Number]."
		}
		AssignGlobal: {
			Type:"Number"
			TypeIgnore:true
			Group:"Code Flow"
			Desc:"Assign [GlobalNumber] to [Number]."
		}
		If: {
			Type:"None"
			Group:"Code Flow"
			Desc:"If [Condition] meet do [Action] otherwise do [Action]."
		}
		Loop: {
			Type:"None"
			Group:"Code Flow"
			Desc:"Count numbers from [Number] to [Number] by [Number] and do [Action]."
		}
		Sleep: {
			Type:"None"
			Group:"Code Flow"
			Desc:"Pause trigger execution for [Number] seconds."
		}
		Print: {
			Type:"None"
			Group:"Misc"
			Desc:"Print message [String] in console."
		}
		DoNothing: {
			Type:"None"
			Group:"Code Flow"
			Desc:"Do nothing."
		}
		GetModel: {
			Type:"Model"
			TypeIgnore:false
			Group:"Model"
			Desc:"Get model [String] in current scene."
		}
		CreateModel: {
			Type:"Model"
			TypeIgnore:true
			Group:"Model"
			Desc:"Create model [ModelType] at position [Point] of layer [Layer] with angle [Number] using look [Look] and play [Animation] with loop [Boolean]."
		}
		PlayAnimation: {
			Type:"None"
			Group:"Model"
			Desc:"Set model [Model] look to [Look] and play animation [Animation] with loop [Boolean]."
		}
	}
	Derivations: {
		{Base:"Number",Sub:"GlobalNumber"}
		{Base:"Number",Sub:"LocalNumber"}
		{Base:"String",Sub:"Look"}
		{Base:"String",Sub:"Animation"}
	}
}
