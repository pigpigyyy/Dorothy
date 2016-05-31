import NewExpr,NewExprVal,ExprIndex,ExprToString,Trim,AddItem from require "Data.API.Expression"

for item in *{
	{
		Name:"NoEvent"
		Text:"No Event"
		Type:"Event"
		MultiLine:false
		TypeIgnore:false
		Group:"Misc"
		Desc:"No event."
		ToCode:=> "NoEvent()"
		CodeOnly:false
		Create:NewExpr!
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"SceneInitialized"
		Text:"Scene Initialized"
		Type:"Event"
		MultiLine:false
		TypeIgnore:false
		Group:"Misc"
		Desc:"Target scene initialized."
		CodeOnly:false
		ToCode:=> "SceneInitialized()"
		Create:NewExpr!
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"TimeCycled"
		Text:"Time Cycled"
		Type:"Event"
		MultiLine:false
		TypeIgnore:false
		Group:"Time"
		Desc:"Trigger event every [Number] seconds."
		CodeOnly:false
		ToCode:=> "TimeCycled( #{ Trim @[2] } )"
		Create:NewExpr "Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"TimeElapsed"
		Text:"Time Elapsed"
		Type:"Event"
		MultiLine:false
		TypeIgnore:false
		Group:"Time"
		Desc:"Trigger event after [Number] seconds when target scene loaded."
		CodeOnly:false
		ToCode:=> "TimeElapsed( #{ Trim @[2] } )"
		Create:NewExpr "Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"BodyEnter"
		Text:"Body Enter"
		Type:"Event"
		MultiLine:false
		TypeIgnore:false
		Group:"Body"
		Desc:"Any body enters sensor [Sensor] area."
		CodeOnly:false
		ToCode:=> "BodyEnter( #{ @[2] } )"
		Create:NewExpr "SensorByName"
		Args:{
			target:"Slice1" -- param order is needed
			sensorTag:"Number2"
		}
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	AddItem item
