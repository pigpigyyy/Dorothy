import NewExpr,NewExprVal,ExprIndex,ExprToString,Items from require "Data.API.Expression"

for item in *{
	{
		Name:"If"
		Text:"If"
		Type:"None"
		MultiLine:true
		TypeIgnore:false
		Group:"Code Flow"
		Desc:"If condition [Boolean] meets do."
		CodeOnly:false
		ToCode:=> "if #{ @[2] } then"
		Create:NewExpr "True","Action","Action"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Loop"
		Text:"Loop"
		Type:"None"
		MultiLine:true
		TypeIgnore:false
		Group:"Code Flow"
		Desc:"Count number [VariableName] from [Number] to [Number] by [Number] and do."
		CodeOnly:false
		ToCode:=> "Loop( #{ @[3] }, #{ @[4] }, #{ @[5] }, function( #{ @[2] } )"
		Create:NewExpr "VariableName","Number","Number","Number","Action"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Sleep"
		Text:"Sleep"
		Type:"None"
		MultiLine:false
		TypeIgnore:false
		Group:"Code Flow"
		Desc:"Pause trigger execution for [Number] seconds."
		CodeOnly:false
		ToCode:=> "Sleep( #{ @[2] } )"
		Create:NewExpr "Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Note"
		Text:"Note"
		Type:"None"
		MultiLine:false
		TypeIgnore:false
		Group:"Misc"
		Desc:"Note: [Text]."
		CodeOnly:false
		ToCode:=> "-- #{ @[2] }"
		Create:NewExpr "Text"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Print"
		Text:"Print"
		Type:"None"
		MultiLine:false
		TypeIgnore:false
		Group:"Misc"
		Desc:"Print message [String] in console."
		CodeOnly:false
		ToCode:=> "Print( #{ @[2] } )"
		Create:NewExpr "String"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"DoNothing"
		Text:"Do Nothing"
		Type:"None"
		MultiLine:false
		TypeIgnore:false
		Group:"Misc"
		Desc:"Do nothing."
		CodeOnly:false
		ToCode:=> "DoNothing()"
		Create:NewExpr!
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Text"
		Text:"Text"
		Type:"Text"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"The plain text."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExprVal ""
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	Items[item.Name] = item
