import NewExpr,NewExprVal,ExprIndex,ExprToString,Items from require "Data.API.Expression"

for item in *{
	{
		Name:"Add"
		Text:"Add +"
		Type:"Number"
		MultiLine:false
		TypeIgnore:false
		Group:"Number"
		Desc:"Number [Number] + [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } + #{ @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Number"
		Text:"Number"
		Type:"Number"
		MultiLine:false
		TypeIgnore:false
		Group:"Number"
		Desc:"Raw number."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExprVal 0
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	Items[item.Name] = item
