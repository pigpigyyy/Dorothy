import NewExpr,NewExprVal,ExprIndex,ExprToString,Items from require "Data.API.Expression"

for item in *{
	{
		Name:"BodyName"
		Text:"Body Name"
		Type:"BodyName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"A name for body."
		CodeOnly:true
		ToCode:=> @[2]
		Create:NewExprVal "InvalidName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"BodyByName"
		Text:"Body"
		Type:"Body"
		MultiLine:false
		TypeIgnore:false
		Group:"Body"
		Desc:"Get body [BodyName] from scene."
		CodeOnly:false
		ToCode:=> "Body.#{ @[2] }"
		Create:NewExpr "BodyName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	Items[item.Name] = item
