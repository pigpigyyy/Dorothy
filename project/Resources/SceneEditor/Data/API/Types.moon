oVec2 = require "oVec2"

DefaultNumber = -> 1
DefaultBoolean = -> true
DefaultString = -> ""
DefaultPoint = -> oVec2.zero
DefaultContainer = -> {}
DefaultItem = -> nil

{
	-- Name: { DefaultItem 1, Group 2, IsNullable 3, DefaultValue 4 }
	Number:{"Number","Data",false,DefaultNumber}
	Boolean:{"True","Data",false,DefaultBoolean}
	String:{"String","Data",false,DefaultString}
	Array:{"LocalArray","Container",false,DefaultContainer}
	Dict:{"LocalDict","Container",false,DefaultContainer}
	Point:{"Point","Geometry",false,DefaultPoint}
	Sprite:{"SpriteByName","Graphic",true,DefaultItem}
	Model:{"ModelByName","Graphic",true,DefaultItem}
	Body:{"BodyByName","Physics",true,DefaultItem}
	Slice:{"SliceByName","Physics",true,DefaultItem}
	Effect:{"EffectByName","Graphic",true,DefaultItem}
	Layer:{"LayerByName","Graphic",true,DefaultItem}
	Sensor:{"SensorByName","Physics",true,DefaultItem}
}
