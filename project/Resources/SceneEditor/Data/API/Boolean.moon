import NewExpr,ExprIndex,ExprToString,Trim,AddItem from require "Data.API.Expression"
Types = require "Data.API.Types"

NewType = (typeName,defaultVal,group,nullable)->
	equal = {
		Name:"#{ typeName }Equal"
		Text:typeName
		Type:"ItemEqual"
		MultiLine:false
		TypeIgnore:false
		Group:group
		Desc:"#{ typeName } [#{ typeName }] equals [#{ typeName }]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } == #{ @[3] } )"
		Create:NewExpr defaultVal,defaultVal
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	valid = if nullable
		{
			Name:"#{ typeName }Valid"
			Text:typeName
			Type:"ItemValid"
			MultiLine:false
			TypeIgnore:false
			Group:group
			Desc:"#{ typeName } [#{ typeName }] is valid."
			CodeOnly:false
			ToCode:=> "IsValid( #{ Trim @[2] } )"
			Create:NewExpr defaultVal
			Args:false
			__index:ExprIndex
			__tostring:ExprToString
		}
	else nil
	{ equal,valid }

AppendTypes = ->
	unpack for typeName,item in pairs Types
		{defaultVal,group,nullable} = item
		NewType typeName,defaultVal,group,nullable

{
	Name:"BodyValid"
	Text:"Body"
	Type:"ItemValid"
	MultiLine:false
	TypeIgnore:false
	Group:"Boolean"
	Desc:"Body [Body] is valid."
	CodeOnly:false
	ToCode:=> "IsValid( #{ Trim @[2] } )"
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
	ToCode:=> "IsValid( #{ Trim @[2] } )"
	Create:NewExpr "SensorByName"
	Args:false
	__index:ExprIndex
	__tostring:ExprToString
}

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
		CodeOnly:true
		ToCode:=> tostring @[2]
		Create:NewExpr "NumberEqual2"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"NumberGreater"
		Text:"Greater"
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
		Text:"Greater Equal"
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
		Text:"Less"
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
		Text:"Less Equal"
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
		CodeOnly:true
		ToCode:=> tostring @[2]
		Create:NewExpr "ModelValid"
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
		Name:"NumberEqual2"
		Text:"Equal"
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
	AppendTypes!
}
	AddItem item
