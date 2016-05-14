import NewExpr,NewExprVal,ExprIndex,ExprToString,Items from require "Data.API.Expression"

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
	-- Number
	{
		Name:"SetLocalNumber"
		Text:"Number"
		Type:"LocalAssign"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Set [LocalName] to [Number]."
		CodeOnly:false
		ToCode:=> "#{ @[2] } = #{ @[3] }"
		Create:NewExpr "LocalName","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"LocalNumber"
		Text:"Local Number"
		Type:"Number"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get local number named [LocalName]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "LocalName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"InitGlobalNumber"
		Text:"Number"
		Type:"GlobalInit"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Initially set global variable [InitGlobalName] to [Number] with note [Text]."
		CodeOnly:false
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"..(tostring(@[4]) == "" and "" or " -- #{ @[4] }")
		Create:NewExpr "InitGlobalName","Number","Text"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"SetGlobalNumber"
		Text:"Number"
		Type:"GlobalAssign"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Set [GlobalName] to [Number]."
		CodeOnly:false
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"
		Create:NewExpr "GlobalName","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"GlobalNumber"
		Text:"Global Number"
		Type:"Number"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get global number named [GlobalName]."
		CodeOnly:false
		ToCode:=> "g_#{ @[2] }"
		Create:NewExpr "GlobalName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	-- String
	{
		Name:"SetLocalString"
		Text:"String"
		Type:"LocalAssign"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Set [LocalName] to [String]."
		CodeOnly:false
		ToCode:=> "#{ @[2] } = #{ @[3] }"
		Create:NewExpr "LocalName","String"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"LocalString"
		Text:"Local String"
		Type:"String"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get local string named [LocalName]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "LocalName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	-- Model
	{
		Name:"SetLocalModel"
		Text:"Model"
		Type:"LocalAssign"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Set [LocalName] to [Model]."
		CodeOnly:false
		ToCode:=> "#{ @[2] } = #{ @[3] }"
		Create:NewExpr "LocalName","ModelByName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"LocalModel"
		Text:"Local Model"
		Type:"Model"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get local model named [LocalName]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "LocalName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"InitGlobalModel"
		Text:"Model"
		Type:"GlobalInit"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Initially set global variable [InitGlobalName] to [Model] with note [Text]."
		CodeOnly:false
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"..(tostring(@[4]) == "" and "" or " -- #{ @[4] }")
		Create:NewExpr "InitGlobalName","ModelByName","Text"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"SetGlobalModel"
		Text:"Model"
		Type:"GlobalAssign"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Set [GlobalName] to [Model]."
		CodeOnly:false
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"
		Create:NewExpr "GlobalName","ModelByName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"GlobalModel"
		Text:"Global Model"
		Type:"Model"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get global model named [GlobalName]."
		CodeOnly:false
		ToCode:=> "g_#{ @[2] }"
		Create:NewExpr "GlobalName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	-- Body
	{
		Name:"SetLocalBody"
		Text:"Body"
		Type:"LocalAssign"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Set [LocalName] to [Body]."
		CodeOnly:false
		ToCode:=> "#{ @[2] } = #{ @[3] }"
		Create:NewExpr "LocalName","BodyByName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"LocalBody"
		Text:"Local Body"
		Type:"Body"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get local body named [LocalName]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "LocalName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"InitGlobalBody"
		Text:"Body"
		Type:"GlobalInit"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Initially set global variable [InitGlobalName] to [Body] with note [Text]."
		CodeOnly:false
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"..(tostring(@[4]) == "" and "" or " -- #{ @[4] }")
		Create:NewExpr "InitGlobalName","BodyByName","Text"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"SetGlobalBody"
		Text:"Body"
		Type:"GlobalAssign"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Set [GlobalName] to [Body]."
		CodeOnly:false
		ToCode:=> "g_#{ @[2] } = #{ @[3] }"
		Create:NewExpr "GlobalName","BodyByName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"GlobalBody"
		Text:"Global Body"
		Type:"Body"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get global body named [GlobalName]."
		CodeOnly:false
		ToCode:=> "g_#{ @[2] }"
		Create:NewExpr "GlobalName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	-- Sensor
	{
		Name:"SetLocalSensor"
		Text:"Sensor"
		Type:"LocalAssign"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Set [LocalName] to [Sensor]."
		CodeOnly:false
		ToCode:=> "#{ @[2] } = #{ @[3] }"
		Create:NewExpr "LocalName","SensorByName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"LocalSensor"
		Text:"Local Sensor"
		Type:"Sensor"
		MultiLine:false
		TypeIgnore:false
		Group:"Variable"
		Desc:"Get local sensor named [LocalName]."
		CodeOnly:true
		ToCode:=> "#{ @[2] }"
		Create:NewExpr "LocalName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	Items[item.Name] = item
