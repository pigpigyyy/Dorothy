import NewExpr,NewExprVal,ExprIndex,ExprToString,Items from require "Data.API.Expression"

for item in *{
	{
		Name:"String"
		Text:"String"
		Type:"String"
		MultiLine:false
		TypeIgnore:false
		Group:"String"
		Desc:"Raw string."
		CodeOnly:true
		ToCode:=> "\"#{ @[2]\gsub('\"','\\\"') }\""
		Create:NewExprVal ""
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	Items[item.Name] = item
