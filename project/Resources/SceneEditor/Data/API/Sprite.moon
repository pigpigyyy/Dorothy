import NewExpr,NewExprVal,ExprIndex,ExprToString,AddItem from require "Data.API.Expression"

for item in *{
	{
		Name:"SpriteName"
		Text:"Sprite Name"
		Type:"SpriteName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"A name for sprite."
		CodeOnly:true
		ToCode:=> @[2]
		Create:NewExprVal "InvalidName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"SpriteByName"
		Text:"Get Sprite"
		Type:"Sprite"
		MultiLine:false
		TypeIgnore:false
		Group:"Sprite"
		Desc:"Get sprite [SpriteName] from scene."
		CodeOnly:false
		ToCode:=> "Sprite.#{ @[2] }"
		Create:NewExpr "SpriteName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	AddItem item
