import NewExpr,NewExprVal,GetArgsText,ExprIndex,ExprToString,Items from require "Data.API.Expression"

for item in *{
	{
		Name:"Trigger"
		Text:"Trigger"
		Type:"Trigger"
		MultiLine:false
		TypeIgnore:false
		Group:"None"
		Desc:"The trigger named [TriggerName] is enabled [Boolean]."
		CodeOnly:false
		ToCode:=> "Trigger( #{ @[2] }, #{ @[3] },"
		Create:NewExpr "TriggerName","True","Event","Condition","Action"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"TriggerName"
		Text:"Trigger Name"
		Type:"TriggerName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"The trigger`s name."
		CodeOnly:true
		ToCode:=> "\"#{ @[2] }\""
		Create:NewExprVal "InvalidName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Event"
		Text:"Event"
		Type:"EventType"
		MultiLine:false
		TypeIgnore:false
		Group:"None"
		Desc:"Event to trigger."
		CodeOnly:false
		ToCode:=> "Event("
		Create:NewExpr "NoEvent"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Action"
		Text:"Action"
		Type:"ActionSequence"
		MultiLine:false
		TypeIgnore:false
		Group:"None"
		Desc:"An action execution sequence."
		CodeOnly:false
		ToCode:=> "Action( function(#{GetArgsText @parent})"
		Create:NewExpr "DoNothing"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"Condition"
		Text:"Condition"
		Type:"Condition"
		MultiLine:false
		TypeIgnore:false
		Group:"None"
		Desc:"Condition value."
		CodeOnly:false
		ToCode:=> "Condition( function(#{GetArgsText @parent}) return"
		Create:NewExpr "True"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	Items[item.Name] = item
