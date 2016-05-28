import NewExpr,NewExprVal,ExprIndex,ExprToString,Trim,Items from require "Data.API.Expression"

for item in *{
	{
		Name:"UnitAction"
		Text:"UnitAction"
		Type:"UnitAction"
		MultiLine:false
		TypeIgnore:false
		Group:"None"
		Desc:"This action is named [ActionName]."
		CodeOnly:false
		ToCode:=> "UnitAction( #{ @[2] },"
		Create:NewExpr "ActionName","Priority","Reaction","Recovery","Available","Run","Stop"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"ActionName"
		Text:"Action Name"
		Type:"ActionName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"The action`s name."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Priority"
		Text:"Priority"
		Type:"Priority"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"Priority [Number] to cancel other action."
		CodeOnly:false
		ToCode:=> "--[[Priority]] #{ Trim @[2] },"
		Create:NewExpr "Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Reaction"
		Text:"Reaction"
		Type:"Reaction"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"Reaction [Number] time to response to AI while doing the action."
		CodeOnly:false
		ToCode:=> "--[[Reaction]] #{ Trim @[2] },"
		Create:NewExpr "Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Recovery"
		Text:"Recovery"
		Type:"Recovery"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"Recovery [Number] time to restore animation."
		CodeOnly:false
		ToCode:=> "--[[Recovery]] #{ Trim @[2] },"
		Create:NewExpr "Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Available"
		Text:"Available"
		Type:"Available"
		MultiLine:false
		TypeIgnore:false
		Group:"None"
		Desc:"Tell whether an action is available."
		CodeOnly:false
		ToCode:=> "--[[Available]] function( action ) return"
		Create:NewExpr "True"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Run"
		Text:"Run"
		Type:"Run"
		MultiLine:false
		TypeIgnore:false
		Group:"None"
		Desc:"Run action of an unit action."
		CodeOnly:false
		ToCode:=> "--[[Run]] function( action )"
		Create:NewExpr "DoNothing"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Stop"
		Text:"Stop"
		Type:"Stop"
		MultiLine:false
		TypeIgnore:false
		Group:"None"
		Desc:"Stop function of an unit action."
		CodeOnly:false
		ToCode:=> "--[[Stop]] function( action )"
		Create:NewExpr "DoNothing"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	Items[item.Name] = item
