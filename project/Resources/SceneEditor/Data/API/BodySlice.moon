import NewExpr,NewExprVal,ExprIndex,ExprToString,Items from require "Data.API.Expression"

for item in *{
	{
		Name:"BodySliceName"
		Text:"BodySlice Name"
		Type:"BodySliceName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"A name for body slice."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"BodySliceByName"
		Text:"BodySlice"
		Type:"BodySlice"
		MultiLine:false
		TypeIgnore:false
		Group:"Body"
		Desc:"Get body slice [BodySliceName] from scene."
		CodeOnly:false
		ToCode:=> "BodySlice( #{ @[2] } )"
		Create:NewExpr "BodySliceName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	Items[item.Name] = item
