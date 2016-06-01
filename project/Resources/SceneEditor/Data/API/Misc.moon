import NewExpr,NewExprVal,ExprIndex,ExprToString,Trim,Items,AddItem from require "Data.API.Expression"

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
		ToCode:=> "if #{ Trim @[2] } then"
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
		ToCode:=> "Loop( #{ Trim @[3] }, #{ Trim @[4] }, #{ Trim @[5] }, function( #{ @[2] } )"
		Create:=>
			incExpr = Items.Number\Create!
			incExpr[2] = 1
			setmetatable {@Name,
				Items.VariableName\Create!
				Items.Number\Create!
				Items.Number\Create!
				incExpr
				Items.Action\Create!
			},@
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
		ToCode:=> "Sleep( #{ Trim @[2] } )"
		Create:NewExpr "Number"
		Args:false
		Async:true
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
		ToCode:=> "Print( #{ Trim @[2] } )"
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
	AddItem item
