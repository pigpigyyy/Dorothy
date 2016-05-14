import NewExpr,NewExprVal,ExprIndex,ExprToString,Items from require "Data.API.Expression"

for item in *{
	{
		Name:"Point"
		Text:"Point"
		Type:"Point"
		MultiLine:false
		TypeIgnore:false
		Group:"Point"
		Desc:"Create point of position x [Number] and position y [Number]."
		CodeOnly:false
		ToCode:=> "Point( #{ @[2] }, #{ @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	Items[item.Name] = item
