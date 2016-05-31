import NewExpr,NewExprVal,ExprIndex,ExprToString,AddItem from require "Data.API.Expression"

for item in *{
	{
		Name:"EffectName"
		Text:"Effect Name"
		Type:"EffectName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"A name for effect."
		CodeOnly:true
		ToCode:=> @[2]
		Create:NewExprVal "InvalidName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"EffectByName"
		Text:"Effect"
		Type:"Effect"
		MultiLine:false
		TypeIgnore:false
		Group:"Effect"
		Desc:"Get effect [EffectName] from scene."
		CodeOnly:false
		ToCode:=> "Effect.#{ @[2] }"
		Create:NewExpr "EffectName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	AddItem item
