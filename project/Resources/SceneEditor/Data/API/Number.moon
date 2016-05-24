import NewExpr,NewExprVal,ExprIndex,ExprToString,Items from require "Data.API.Expression"

for item in *{
	{
		Name:"Plus"
		Text:"Plus"
		Type:"Number"
		MultiLine:false
		TypeIgnore:false
		Group:"Operation"
		Desc:"Number [Number] + [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } + #{ @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Minus"
		Text:"Minus"
		Type:"Number"
		MultiLine:false
		TypeIgnore:false
		Group:"Operation"
		Desc:"Number [Number] - [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } - #{ @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Multiply"
		Text:"Multiply"
		Type:"Number"
		MultiLine:false
		TypeIgnore:false
		Group:"Operation"
		Desc:"Number [Number] * [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } * #{ @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Divide"
		Text:"Divide"
		Type:"Number"
		MultiLine:false
		TypeIgnore:false
		Group:"Operation"
		Desc:"Number [Number] / [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } / #{ @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Power"
		Text:"Power"
		Type:"Number"
		MultiLine:false
		TypeIgnore:false
		Group:"Operation"
		Desc:"Power with base [Number] and exponent [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } ^ #{ @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Module"
		Text:"Module"
		Type:"Number"
		MultiLine:false
		TypeIgnore:false
		Group:"Operation"
		Desc:"Get remainders after [Number] divides [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } % #{ @[3] } )"
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
