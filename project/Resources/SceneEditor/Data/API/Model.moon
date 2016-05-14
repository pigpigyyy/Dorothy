import NewExpr,NewExprVal,ExprIndex,ExprToString,Items from require "Data.API.Expression"

for item in *{
	{
		Name:"ModelType"
		Text:"Model Type"
		Type:"ModelType"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"A type name for model."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal ""
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Animation"
		Type:"Animation"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"A name for animation."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal ""
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Look"
		Text:"Look"
		Type:"Look"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"A name for look."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal ""
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"ModelName"
		Text:"Model Name"
		Type:"ModelName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"A name for model."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"ModelByName"
		Text:"Model"
		Type:"Model"
		MultiLine:false
		TypeIgnore:false
		Group:"Model"
		Desc:"Get model [ModelName] from scene."
		CodeOnly:false
		ToCode:=> "Model( #{ @[2] } )"
		Create:NewExpr "ModelName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"CreateModel"
		Text:"Create Model"
		Type:"Model"
		MultiLine:false
		TypeIgnore:true
		Group:"Model"
		Desc:"Create model [ModelType] at position [Point] of layer [Layer] with angle [Number] using look [Look] and play [Animation] with loop [Boolean]."
		CodeOnly:false
		ToCode:=> "CreateModel( #{ @[2] }, #{ @[3] }, #{ @[4] }, #{ @[5] }, #{ @[6] }, #{ @[7] }, #{ @[8] } )"
		Create:NewExpr "ModelType","Point","LayerByName","Number","Look","Animation","False"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"DestroyModel"
		Text:"Destroy Model"
		Type:"None"
		MultiLine:false
		TypeIgnore:false
		Group:"Model"
		Desc:"Destroy a model [Model]."
		CodeOnly:false
		ToCode:=> "DestroyModel( #{ @[2] } )"
		Create:NewExpr "ModelByName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"PlayAnimation"
		Text:"Play Animation"
		Type:"Number"
		MultiLine:false
		TypeIgnore:true
		Group:"Model"
		Desc:"Play model [Model] animation [Animation] with loop [Boolean] and set model look to [Look], then return animation`s duration."
		CodeOnly:false
		ToCode:=> "PlayAnimation( #{ @[2] }, #{ @[3] }, #{ @[4] }, #{ @[5] } )"
		Create:NewExpr "ModelByName","Animation","False","Look"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	Items[item.Name] = item
