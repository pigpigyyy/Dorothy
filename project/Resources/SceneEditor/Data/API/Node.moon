import NewExpr,ExprIndex,ExprToString,Items from require "Data.API.Expression"
Types = require "Data.API.Types"

NewType = (typeName,defaultVal,group)->
	typeLowerCase = typeName\lower!
	itemProperty = "#{ typeName }Property"
	{
		{
			Name:"Set#{ typeName }Property"
			Text:typeName
			Type:"SetItemProperty"
			MultiLine:false
			TypeIgnore:false
			Group:group
			Desc:"Set [#{ itemProperty }]."
			CodeOnly:true
			ToCode:=> tostring @[2]
			Create:NewExpr "Set#{ typeName }Position"
			Args:false
			__index:ExprIndex
			__tostring:ExprToString
		}
		{
			Name:"Set#{ typeName }Position"
			Text:"Position"
			Type:itemProperty
			MultiLine:false
			TypeIgnore:false
			Group:typeName
			Desc:"Set #{ typeLowerCase } [#{ typeName }] position to [Point]."
			CodeOnly:false
			ToCode:=> "SetPosition( #{ @[2] }, #{ @[3] } )"
			Create:NewExpr defaultVal,"Point"
			Args:false
			__index:ExprIndex
			__tostring:ExprToString
		}
		{
			Name:"Set#{ typeName }Angle"
			Text:"Angle"
			Type:itemProperty
			MultiLine:false
			TypeIgnore:false
			Group:typeName
			Desc:"Set #{ typeLowerCase } [#{ typeName }] angle to [Number]."
			CodeOnly:false
			ToCode:=> "SetAngle( #{ @[2] }, #{ @[3] } )"
			Create:NewExpr defaultVal,"Number"
			Args:false
			__index:ExprIndex
			__tostring:ExprToString
		}
		{
			Name:"Set#{ typeName }Visible"
			Text:"Visible"
			Type:itemProperty
			MultiLine:false
			TypeIgnore:false
			Group:typeName
			Desc:"Set #{ typeLowerCase } [#{ typeName }] visibility to [Boolean]."
			CodeOnly:false
			ToCode:=> "SetVisibility( #{ @[2] }, #{ @[3] } )"
			Create:NewExpr defaultVal,"True"
			Args:false
			__index:ExprIndex
			__tostring:ExprToString
		}
		{
			Name:"Set#{ typeName }Scale"
			Text:"Scale"
			Type:itemProperty
			MultiLine:false
			TypeIgnore:false
			Group:typeName
			Desc:"Set #{ typeLowerCase } [#{ typeName }] scale to [Point]."
			CodeOnly:false
			ToCode:=> "SetScale( #{ @[2] }, #{ @[3] } )"
			Create:NewExpr "SpriteByName","Point"
			Args:false
			__index:ExprIndex
			__tostring:ExprToString
		}
		{
			Name:"Set#{ typeName }Skew"
			Text:"Skew"
			Type:itemProperty
			MultiLine:false
			TypeIgnore:false
			Group:typeName
			Desc:"Set #{ typeLowerCase } [#{ typeName }] skew to [Point]."
			CodeOnly:false
			ToCode:=> "SetSkew( #{ @[2] }, #{ @[3] } )"
			Create:NewExpr "SpriteByName","Point"
			Args:false
			__index:ExprIndex
			__tostring:ExprToString
		}
		{
			Name:"Get#{ typeName }Position"
			Text:typeName
			Type:"ItemPosition"
			MultiLine:false
			TypeIgnore:false
			Group:group
			Desc:"Get #{ typeLowerCase } [#{ typeName }] position."
			CodeOnly:false
			ToCode:=> "GetPosition( #{ @[2] } )"
			Create:NewExpr "SpriteByName"
			Args:false
			__index:ExprIndex
			__tostring:ExprToString
		}
		{
			Name:"Get#{ typeName }Angle"
			Text:typeName
			Type:"ItemAngle"
			MultiLine:false
			TypeIgnore:false
			Group:group
			Desc:"Get #{ typeLowerCase } [#{ typeName }] angle."
			CodeOnly:false
			ToCode:=> "GetAngle( #{ @[2] } )"
			Create:NewExpr "SpriteByName"
			Args:false
			__index:ExprIndex
			__tostring:ExprToString
		}
		{
			Name:"Get#{ typeName }Visibility"
			Text:typeName
			Type:"ItemVisibility"
			MultiLine:false
			TypeIgnore:false
			Group:group
			Desc:"Get #{ typeLowerCase } [#{ typeName }] visibility."
			CodeOnly:false
			ToCode:=> "GetVisibility( #{ @[2] } )"
			Create:NewExpr "SpriteByName"
			Args:false
			__index:ExprIndex
			__tostring:ExprToString
		}
		{
			Name:"Get#{ typeName }Scale"
			Text:typeName
			Type:"ItemScale"
			MultiLine:false
			TypeIgnore:false
			Group:group
			Desc:"Get #{ typeLowerCase } [#{ typeName }] scale."
			CodeOnly:false
			ToCode:=> "GetScale( #{ @[2] } )"
			Create:NewExpr "SpriteByName"
			Args:false
			__index:ExprIndex
			__tostring:ExprToString
		}
		{
			Name:"Get#{ typeName }Skew"
			Text:typeName
			Type:"ItemSkew"
			MultiLine:false
			TypeIgnore:false
			Group:group
			Desc:"Get #{ typeLowerCase } [#{ typeName }] skew."
			CodeOnly:false
			ToCode:=> "GetSkew( #{ @[2] } )"
			Create:NewExpr "SpriteByName"
			Args:false
			__index:ExprIndex
			__tostring:ExprToString
		}
	}

AppendTypes = ->
	unpack for typeName in *{"Sprite","Model","BodySlice","Sensor"}
		{defaultVal,group} = Types[typeName]
		NewType typeName,defaultVal,group

for item in *{
	{
		Name:"SetProperty"
		Text:"Set Property"
		Type:"None"
		MultiLine:false
		TypeIgnore:false
		Group:"Property"
		Desc:"Do [SetItemProperty]."
		CodeOnly:true
		ToCode:=> tostring @[2]
		Create:NewExpr "SetSpriteProperty"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"GetPosition"
		Text:"Get Position"
		Type:"Point"
		MultiLine:false
		TypeIgnore:false
		Group:"Property"
		Desc:"Get [ItemPosition]."
		CodeOnly:true
		ToCode:=> tostring @[2]
		Create:NewExpr "GetSpritePosition"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"GetAngle"
		Text:"Get Angle"
		Type:"Number"
		MultiLine:false
		TypeIgnore:false
		Group:"Property"
		Desc:"Get [ItemAngle]."
		CodeOnly:true
		ToCode:=> tostring @[2]
		Create:NewExpr "GetSpriteAngle"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"GetVisibility"
		Text:"Get Visibility"
		Type:"Boolean"
		MultiLine:false
		TypeIgnore:false
		Group:"Property"
		Desc:"Get [ItemVisibility]."
		CodeOnly:true
		ToCode:=> tostring @[2]
		Create:NewExpr "GetSpriteVisibility"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"GetScale"
		Text:"Get Scale"
		Type:"Point"
		MultiLine:false
		TypeIgnore:false
		Group:"Property"
		Desc:"Get [ItemScale]."
		CodeOnly:true
		ToCode:=> tostring @[2]
		Create:NewExpr "GetSpriteScale"
		Args:false
		__index:ExprIndex
		__tostring:ExprToString
	}
	{
		Name:"GetSkew"
		Text:"Get Skew"
		Type:"Point"
		MultiLine:false
		TypeIgnore:false
		Group:"Property"
		Desc:"Get [ItemSkew]."
		CodeOnly:true
		ToCode:=> tostring @[2]
		Create:NewExpr "GetSpriteSkew"
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
