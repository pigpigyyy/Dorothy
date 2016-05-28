import NewExpr,NewExprVal,ExprIndex,ExprToString,Trim,Items from require "Data.API.Expression"

for item in *{
	{
		Name:"Point"
		Text:"Point"
		Type:"Point"
		MultiLine:false
		TypeIgnore:false
		Group:"Point"
		Desc:"Create point of position x [Number] and y [Number]."
		CodeOnly:false
		ToCode:=> "Point( #{ Trim @[2] }, #{ Trim @[3] } )"
		Create:NewExpr "Number","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"PointAdd"
		Text:"Add"
		Type:"Point"
		MultiLine:false
		TypeIgnore:false
		Group:"Operation"
		Desc:"Point [Point] + [Point]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } + #{ @[3] } )"
		Create:NewExpr "Point","Point"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"PointSub"
		Text:"Substract"
		Type:"Point"
		MultiLine:false
		TypeIgnore:false
		Group:"Operation"
		Desc:"Point [Point] - [Point]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } - #{ @[3] } )"
		Create:NewExpr "Point","Point"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"PointMult"
		Text:"Multiply"
		Type:"Point"
		MultiLine:false
		TypeIgnore:false
		Group:"Operation"
		Desc:"Point [Point] * [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } * #{ @[3] } )"
		Create:NewExpr "Point","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"PointDiv"
		Text:"Divide"
		Type:"Point"
		MultiLine:false
		TypeIgnore:false
		Group:"Operation"
		Desc:"Point [Point] / [Number]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } / #{ @[3] } )"
		Create:NewExpr "Point","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"PointCross"
		Text:"Cross"
		Type:"Point"
		MultiLine:false
		TypeIgnore:false
		Group:"Operation"
		Desc:"Point [Point] * [Point]."
		CodeOnly:false
		ToCode:=> "( #{ @[2] } * #{ @[3] } )"
		Create:NewExpr "Point","Point"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	Items[item.Name] = item
