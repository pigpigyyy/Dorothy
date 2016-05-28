local Expression
Items = {}

tostring = tostring
type = type
concat = table.concat

SetExprMeta = (expr)->
	isTrigger = expr[1] == "Trigger"
	for i = 2,#expr
		childExpr = expr[i]
		SetExprMeta childExpr if "table" == type childExpr
		if isTrigger
			switch childExpr[1]
				when "Condition","Action"
					childExpr.parent = expr
	setmetatable expr,Items[expr[1]]

GetArgsText = (trigger)->
	if trigger and trigger[4][2].Args
		args = {tonumber(info\match("%d*$")),name for name,info in pairs trigger[4][2].Args}
		" #{concat args,', '} "
	else
		""

ExprToString = (expr)->
	if Expression.CodeMode or expr.CodeOnly
		expr\ToCode!
	elseif expr.ToDesc
		expr\ToDesc!
	else
		index = 1
		expr.Desc\gsub "%b[]",->
			index += 1
			"(#{tostring expr[index]})"

NewExpr = (...)->
	names = {...}
	=>
		exprs = [Items[name]\Create! for name in *names]
		table.insert exprs,1,@Name
		setmetatable exprs,@

NewExprVal = (value)-> => setmetatable {@Name,value},@

ExprIndex = (key)=> (getmetatable @)[key]

Trim = (item)->
	item = tostring item
	item\sub(1,1) == "(" and item\sub(2,-2) or item

LoadAPIs = ()->
	for name in *{
			"Variable"
			"Trigger"
			"Event"
			"UnitAction"
			"AI"
			"Misc"
			"Boolean"
			"Number"
			"String"
			"Point"
			"Effect"
			"Node"
			"Sprite"
			"Model"
			"Body"
			"Slice"
			"Layer"
			"Sensor"
		}
		require "Data.API.#{ name }"

Expression = {
	CodeMode:false
	:SetExprMeta
	:GetArgsText
	:ExprToString
	:NewExpr
	:NewExprVal
	:Items
	:LoadAPIs
	:ExprIndex
	:ExprToString
	:Trim
}

Expression
