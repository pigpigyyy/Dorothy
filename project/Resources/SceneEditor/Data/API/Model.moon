Expression = require "Data.API.Expression"
import NewExpr,NewExprVal,ExprIndex,ExprToString,Trim,AddItem,Items from Expression

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
		ToCode:=> @[2]
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
		ToCode:=> "Model.#{ @[2] }"
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
		Desc:"Create model [ModelType] at position [Point] of layer [Layer] with angle [Number] using look [Look] and play [Animation] with loop [Boolean] and"
		CodeOnly:false
		ToCode:=>
			codeMode = Expression.CodeMode
			prefix = (@[9] and (codeMode and "Wait( " or "Wait ") or "")
			appendix = (@[9] and (codeMode and " )" or "") or "")
			desc = if codeMode
				"CreateModel( #{ @[2] }, #{ Trim @[3] }, #{ @[4] }, #{ Trim @[5] }, #{ @[6] }, #{ @[7] }, #{ Trim @[8] } )"
			else
				"Create model [#{ @[2] }] at position [#{ @[3] }] of layer [#{ @[4] }] with angle [#{ @[5] }] using look [#{ @[6] }] and play [#{ @[7] }] with loop [#{ @[8] }]."
			prefix..desc..appendix
		Create:=>
			setmetatable { "CreateModel"
				Items.ModelType\Create!
				Items.Point\Create!
				Items.LayerByName\Create!
				Items.Number\Create!
				Items.Look\Create!
				Items.Animation\Create!
				Items.False\Create!
				false
			},@
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
		ToCode:=> "DestroyModel( #{ Trim @[2] } )"
		Create:NewExpr "ModelByName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"PlayAnimation"
		Text:"Play Animation"
		Type:"None"
		MultiLine:false
		TypeIgnore:true
		Group:"Model"
		Desc:"Play model [Model] animation [Animation] using look [Look] with loop [Boolean] and"
		CodeOnly:true
		ToCode:=>
			codeMode = Expression.CodeMode
			prefix = (@[6] and (codeMode and "Wait( " or "Wait ") or "")
			appendix = (@[6] and (codeMode and " )" or "") or "")
			desc = if codeMode
				"#{ @[2] }:play( #{ @[3] }, #{ @[4] }, #{ Trim @[5] } )"
			else
				"Play model [#{ @[2] }] animation [#{ @[3] }] using look [#{ @[4] }] with loop [#{ Trim @[5] }]."
			prefix..desc..appendix
		Create:=>
			setmetatable { "PlayAnimation"
				Items.ModelByName\Create!
				Items.Animation\Create!
				Items.Look\Create!
				Items.False\Create!
				false
			},@
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"SetModelLook"
		Text:"Look"
		Type:"ModelProperty"
		MultiLine:false
		TypeIgnore:false
		Group:"Graphic"
		Desc:"Set look of [Model] to [Look]."
		CodeOnly:false
		ToCode:=> "#{ @[2] }.look = #{ @[3] }"
		Create:NewExpr "ModelByName","Look"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"GetModelLook"
		Text:"Get Look"
		Type:"Look"
		MultiLine:false
		TypeIgnore:false
		Group:"Graphic"
		Desc:"Get look of [Model]."
		CodeOnly:false
		ToCode:=> "#{ @[2] }.look"
		Create:NewExpr "ModelByName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	AddItem item
