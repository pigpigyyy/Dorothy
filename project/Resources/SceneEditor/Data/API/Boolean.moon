import NewExpr,ExprIndex,ExprToString,Items from require "Data.API.Expression"

for item in *{
	{
		Name:"And"
		Text:"And"
		Type:"Boolean"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Boolean [Boolean] and [Boolean]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } and #{ @[3] } )"
		Create:NewExpr "True","True"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Or"
		Text:"Or"
		Type:"Boolean"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Boolean [Boolean] or [Boolean]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } or #{ @[3] } )"
		Create:NewExpr "True","True"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"NumberCompare"
		Text:"Number Compare"
		Type:"Boolean"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Check [NumberCompare]."
		CodeOnly:false
		ToCode:=> tostring @[2]
		Create:NewExpr "NumberEqual2"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"NumberGreater"
		Text:">"
		Type:"NumberCompare"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Number [Number] greater than [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } > #{ @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"NumberGreaterEqual"
		Text:">="
		Type:"NumberCompare"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Number [Number] greater equal than [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } >= #{ @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"NumberLess"
		Text:"<"
		Type:"NumberCompare"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Number [Number] less than [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } < #{ @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"NumberLessEqual"
		Text:"<="
		Type:"NumberCompare"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Number [Number] less equal than [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } <= #{ @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"StringCompare"
		Text:"String Compare"
		Type:"Boolean"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Check [StringCompare]."
		CodeOnly:false
		ToCode:=> tostring @[2]
		Create:NewExpr "NumberEqual2"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"NumberGreater"
		Text:">"
		Type:"NumberCompare"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Number [Number] greater than [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } > #{ @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"NumberGreaterEqual"
		Text:">="
		Type:"NumberCompare"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Number [Number] greater equal than [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } >= #{ @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"NumberLess"
		Text:"<"
		Type:"NumberCompare"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Number [Number] less than [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } < #{ @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"NumberLessEqual"
		Text:"<="
		Type:"NumberCompare"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Number [Number] less equal than [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } <= #{ @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Valid"
		Text:"Valid"
		Type:"Boolean"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Is [ItemValid]."
		CodeOnly:false
		ToCode:=> tostring @[2]
		Create:NewExpr "ModelValid"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"ModelValid"
		Text:"Model"
		Type:"ItemValid"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Model [Model] is valid."
		CodeOnly:false
		ToCode:=> "IsValid( #{ @[2] } )"
		Create:NewExpr "ModelByName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"BodyValid"
		Text:"Body"
		Type:"ItemValid"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Body [Body] is valid."
		CodeOnly:false
		ToCode:=> "IsValid( #{ @[2] } )"
		Create:NewExpr "BodyByName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"SensorValid"
		Text:"Sensor"
		Type:"ItemValid"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Sensor [Sensor] is valid."
		CodeOnly:false
		ToCode:=> "IsValid( #{ @[2] } )"
		Create:NewExpr "SensorByName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Not"
		Text:"Not"
		Type:"Boolean"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Not [Boolean]."
		CodeOnly:false
		ToCode:=> "( not #{ @[2] } )"
		Create:NewExpr "True"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"True"
		Text:"True"
		Type:"Boolean"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Boolean true."
		CodeOnly:true
		ToCode:=> "true"
		Create:NewExpr!
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"False"
		Text:"False"
		Type:"Boolean"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Boolean false."
		CodeOnly:true
		ToCode:=> "false"
		Create:NewExpr!
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Equal"
		Text:"Equal"
		Type:"Boolean"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Compare [ItemEqual]."
		CodeOnly:false
		ToCode:=> tostring @[2]
		Create:NewExpr "NumberEqual"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"NumberEqual"
		Text:"Number"
		Type:"ItemEqual"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Number [Number] equals [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } == #{ @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"NumberEqual2"
		Text:"=="
		Type:"NumberCompare"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Number [Number] equals [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } == #{ @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"BodyEqual"
		Text:"Body"
		Type:"ItemEqual"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Body [Body] equals [Body]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } == #{ @[3] } )"
		Create:NewExpr "BodyByName","BodyByName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"ModelEqual"
		Text:"Model"
		Type:"ItemEqual"
		MultiLine:false
		TypeIgnore:false
		Group:"Boolean"
		Desc:"Model [Model] equals [Model]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } == #{ @[3] } )"
		Create:NewExpr "ModelByName","ModelByName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	Items[item.Name] = item
