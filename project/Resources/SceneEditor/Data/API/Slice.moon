import NewExpr,NewExprVal,ExprIndex,ExprToString,Items from require "Data.API.Expression"

for item in *{
	{
		Name:"SliceName"
		Text:"Slice Name"
		Type:"SliceName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"A name for body slice."
		CodeOnly:true
		ToCode:=> @[2]
		Create:NewExprVal "InvalidName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"SliceByName"
		Text:"Slice"
		Type:"Slice"
		MultiLine:false
		TypeIgnore:false
		Group:"Physics"
		Desc:"Get body slice [SliceName] from scene."
		CodeOnly:false
		ToCode:=> "Slice.#{ @[2] }"
		Create:NewExpr "SliceName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	Items[item.Name] = item
