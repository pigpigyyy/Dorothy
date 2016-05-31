import NewExpr,NewExprVal,ExprIndex,ExprToString,AddItem from require "Data.API.Expression"
import Path from require "Lib.Utils"

for item in *{
	{
		Name:"AIRoot"
		Text:"AI Root Node"
		Type:"AIRoot"
		MultiLine:false
		TypeIgnore:false
		Group:"None"
		Desc:"AI Root Node."
		CodeOnly:false
		ToCode:=>
			codes = [tostring expr for expr in *@[3,]]
			table.concat {"return AIRoot( ", tostring(@[2]), ", ", table.concat(codes,", "), " )"}
		Create:NewExpr "TreeName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"TreeName"
		Text:"Tree Name"
		Type:"TreeName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"The AI tree`s name."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"ConName"
		Text:"Condition Name"
		Type:"ConName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"The condition node`s name."
		CodeOnly:true
		ToCode:=> (Path.getPath(@[2])..Path.getName(@[2]))\gsub("[\\/]+",".")
		Create:NewExprVal "InvalidName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"ActName"
		Text:"Action Name"
		Type:"ActName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"The action node`s name."
		CodeOnly:true
		ToCode:=> (Path.getPath(@[2])..Path.getName(@[2]))\gsub("[\\/]+",".")
		Create:NewExprVal "InvalidName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Sel"
		Text:"Selection"
		Type:"AINode"
		MultiLine:false
		TypeIgnore:false
		Group:"AI"
		Desc:"Selection Node."
		CodeOnly:true
		ToCode:=>
			codes = [tostring expr for expr in *@[2,]]
			table.concat {"SelNode( ", table.concat(codes,", "), " )"}
		Create:NewExpr!
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Seq"
		Text:"Sequence"
		Type:"AINode"
		MultiLine:false
		TypeIgnore:false
		Group:"AI"
		Desc:"Sequence Node."
		CodeOnly:true
		ToCode:=>
			codes = [tostring expr for expr in *@[2,]]
			table.concat {"SeqNode( ", table.concat(codes,", "), " )"}
		Create:NewExpr!
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Con"
		Text:"Condition"
		Type:"AINode"
		MultiLine:false
		TypeIgnore:false
		Group:"AI"
		Desc:"Condition Node."
		CodeOnly:true
		ToCode:=> "ConNode( \"#{ @[2] }\" )"
		Create:NewExpr "ConName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Act"
		Text:"Action"
		Type:"AINode"
		MultiLine:false
		TypeIgnore:false
		Group:"AI"
		Desc:"Action Node."
		CodeOnly:true
		ToCode:=> "ActNode( \"#{ @[2] }\" )"
		Create:NewExpr "ActName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"ConditionNode"
		Type:"ConditionNode"
		MultiLine:false
		TypeIgnore:false
		Group:"None"
		Desc:"This AI condition node named [NodeName] checks"
		CodeOnly:false
		ToCode:=> "ConNode( #{ @[2] }, function() return"
		Create:NewExpr "NodeName","True"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"NodeName"
		Text:"Node Name"
		Type:"NodeName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"The AI node`s name."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	AddItem item
