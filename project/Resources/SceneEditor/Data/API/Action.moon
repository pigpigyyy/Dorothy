import NewExpr,ExprIndex,ExprToString,AddItem from require "Data.API.Expression"
oEase = require "oEase"

appendEasings = ->
	unpack for k in pairs oEase
		if k ~= "func" and "string" == type(k) and k\sub(1,2) ~= "__"
			{
				Name:k
				Text:k
				Type:"Easing"
				MultiLine:false
				TypeIgnore:false
				Group:"Easing"
				Desc:"#{ k } easing to perform action."
				CodeOnly:false
				ToCode:=> k
				Create:NewExpr!
				Args:false
				__index:ExprIndex
				__tostring:ExprToString
			}
		else continue

for item in *{
	{
		Name:"ActionGroup"
		Text:"ActionGroup"
		Type:"ActionGroup"
		MultiLine:false
		TypeIgnore:false
		Group:"Action"
		Desc:"A group of actions."
		CodeOnly:false
		ToCode:=> ""
		Create:NewExpr!
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Sequence"
		Text:"Sequence"
		Type:"Action"
		MultiLine:true
		TypeIgnore:false
		Group:"Action"
		Desc:"A group of actions execute in sequence order."
		CodeOnly:false
		ToCode:=> "Sequence("
		Create:NewExpr "ActionGroup"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Spawn"
		Text:"Spawn"
		Type:"Action"
		MultiLine:true
		TypeIgnore:false
		Group:"Action"
		Desc:"A group of actions execute in parrallel order."
		CodeOnly:false
		ToCode:=> "Spawn("
		Create:NewExpr "ActionGroup"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Move"
		Text:"Move"
		Type:"Action"
		MultiLine:false
		TypeIgnore:false
		Group:"Action"
		Desc:"Move item in [Number] seconds to position [Point] with [Easing]."
		CodeOnly:false
		ToCode:=> "Move( #{ @[2] }, #{ @[3] }, #{ @[4] } )"
		Create:NewExpr "Number","Point","Linear"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Scale"
		Text:"Scale"
		Type:"Action"
		MultiLine:false
		TypeIgnore:false
		Group:"Action"
		Desc:"Scale item in [Number] seconds to value [Point] with [Easing]."
		CodeOnly:false
		ToCode:=> "Scale( #{ @[2] }, #{ @[3] }, #{ @[4] } )"
		Create:NewExpr "Number","Point","Linear"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	appendEasings!
}
	AddItem item
