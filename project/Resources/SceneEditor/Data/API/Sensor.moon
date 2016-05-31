import NewExpr,NewExprVal,ExprIndex,ExprToString,AddItem from require "Data.API.Expression"

for item in *{
	{
		Name:"SensorName"
		Text:"Sensor Name"
		Type:"SensorName"
		MultiLine:false
		TypeIgnore:false
		Group:"Special"
		Desc:"A name for sensor."
		CodeOnly:true
		ToCode:=> @[2]
		Create:NewExprVal "InvalidName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"SensorByName"
		Text:"Sensor"
		Type:"Sensor"
		MultiLine:false
		TypeIgnore:false
		Group:"Sensor"
		Desc:"Get sensor [SensorName] from scene."
		CodeOnly:false
		ToCode:=> "Sensor.#{ @[2] }"
		Create:NewExpr "SensorName"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"IsSensed"
		Text:"Is Sensed"
		Type:"Boolean"
		MultiLine:false
		TypeIgnore:false
		Group:"Sensor"
		Desc:"Return true if sensor [Sensor] with area id [Number] detect a body slice."
		CodeOnly:false
		ToCode:=> "IsSensed( #{ @[2] }, #{ @[3] } )"
		Create:NewExpr "SensorByName","Number"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
}
	AddItem item
