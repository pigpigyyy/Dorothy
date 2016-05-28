import NewExpr,NewExprVal,ExprIndex,ExprToString,Trim,Items from require "Data.API.Expression"
Types = require "Data.API.Types"

NewType = (typeName,defaultVal,groupName)->
	isContainer = switch typeName
		when "Array","Dict" then true
		else false
	{
		{
			Name:"SetLocal#{ typeName }"
			Text:typeName
			Type:"LocalAssign"
			MultiLine:false
			TypeIgnore:false
			Group:groupName
			Desc:"Set [LocalName] to [#{ typeName }]."
			CodeOnly:false
			ToCode:=> "#{ @[2] } = #{ Trim @[3] }"
			Create:NewExpr "LocalName",isContainer and defaultVal\gsub("Local","Create") or defaultVal
			Args:false
			__index:ExprIndex
			__tostring:ExprToString
		}
		{
			Name:"Local#{ typeName }"
			Text:"Local #{ typeName }"
			Type:typeName
			MultiLine:false
			TypeIgnore:false
			Group:"Variable"
			Desc:"Get local number named [LocalName]."
			CodeOnly:true
			ToCode:=> tostring @[2]
			Create:NewExpr "LocalName"
			Args:false
			__index:ExprIndex
			__tostring:ExprToString
		}
		{
			Name:"InitGlobal#{ typeName }"
			Text:typeName
			Type:"GlobalInit"
			MultiLine:false
			TypeIgnore:false
			Group:groupName
			Desc:"Initially set global variable [InitGlobalName] to [#{ typeName }] with note [Text]."
			CodeOnly:false
			ToCode:=> "g_#{ @[2] } = #{ Trim @[3] }"..(tostring(@[4]) == "" and "" or " -- #{ @[4] }")
			Create:NewExpr "InitGlobalName",defaultVal,"Text"
			Args:false
			__index:ExprIndex
			__tostring:ExprToString
		}
		{
			Name:"SetGlobal#{ typeName }"
			Text:typeName
			Type:"GlobalAssign"
			MultiLine:false
			TypeIgnore:false
			Group:groupName
			Desc:"Set [GlobalName] to [#{ typeName }]."
			CodeOnly:false
			ToCode:=> "g_#{ @[2] } = #{ Trim @[3] }"
			Create:NewExpr "GlobalName",defaultVal
			Args:false
			__index:ExprIndex
			__tostring:ExprToString
		}
		{
			Name:"Global#{ typeName }"
			Text:"Global #{ typeName }"
			Type:typeName
			MultiLine:false
			TypeIgnore:false
			Group:"Variable"
			Desc:"Get global #{ typeName\lower! } named [GlobalName]."
			CodeOnly:false
			ToCode:=> "g_#{ @[2] }"
			Create:NewExpr "GlobalName"
			Args:false
			__index:ExprIndex
			__tostring:ExprToString
		}
	}

AppendTypes = ->
	unpack [NewType typeName,item[1],item[2] for typeName,item in pairs Types]

for item in *{
	{
		Name:"GlobalVar"
		Text:"Global Variable"
		Type:"GlobalVar"
		MultiLine:false
		TypeIgnore:false
		Group:"None"
		Desc:"Global variable declaration and initialization."
		CodeOnly:false
		ToCode:=>
			codes = [tostring expr for expr in *@[2,]]
			table.concat codes,"\n"
		Create:NewExpr!
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"LocalName"
		Text:"Local Name"
		Type:"LocalName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"A name for local value."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExprVal "InvalidName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"GlobalName"
		Text:"Global Name"
		Type:"GlobalName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"A name for global value."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExprVal "InvalidName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"VariableName"
		Text:"Variable Name"
		Type:"VariableName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"A name for variable."
		CodeOnly:true
		ToCode:=> @[2]
		Create:NewExprVal "i"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"InitGlobalName"
		Text:"Global Name"
		Type:"InitGlobalName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"A name for global value."
		CodeOnly:true
		ToCode:=> "#{ @[2] == '' and 'InvalidName' or @[2] }"
		Create:NewExprVal ""
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"SetLocal"
		Text:"Set Local"
		Type:"None"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Do [LocalAssign]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "SetLocalNumber"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"SetGlobal"
		Text:"Set Global"
		Type:"None"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Do [GlobalAssign]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "SetGlobalNumber"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	AppendTypes!
}
	itemName = item.Name
	if itemName
		Items[itemName] = item
	else
		for subItem in *item
			Items[subItem.Name] = subItem
