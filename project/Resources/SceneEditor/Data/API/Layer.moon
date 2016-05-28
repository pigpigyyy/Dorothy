import NewExpr,NewExprVal,ExprIndex,ExprToString,Items from require "Data.API.Expression"

for item in *{
	{
		Name:"LayerName"
		Text:"Layer Name"
		Type:"LayerName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"A name for layer."
		CodeOnly:true
		ToCode:=> @[2]
		Create:NewExprVal "InvalidName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"LayerByName"
		Text:"Layer"
		Type:"Layer"
		MultiLine:false
		TypeIgnore:false
		Group:"Layer"
		Desc:"Get layer [LayerName] from scene."
		CodeOnly:false
		ToCode:=> "Layer.#{ @[2] }"
		Create:NewExpr "LayerName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	Items[item.Name] = item
