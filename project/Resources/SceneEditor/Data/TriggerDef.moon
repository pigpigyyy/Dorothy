Dorothy!
Expression = require "Data.API.Expression"
{:Items,:LoadAPIs,:SetExprMeta} = Expression
import Path from require "Lib.Utils"

local TriggerDef

TriggerDef = Class {
	:SetExprMeta

	Expressions:classfield => Items

	CodeMode:classfield => Expression.CodeMode,
		(value)=> Expression.CodeMode = value

	ToEditText:(expr)->
		strs = {"return "}
		insert = table.insert
		append = (str)-> insert strs,str
		indent = 0
		nextExpr = (expr)->
			append "{"
			for i = 1,#expr
				item = expr[i]
				switch type item
					when "table"
						indent += 1
						append "\n"
						append string.rep("\t",indent)
						nextExpr item
						indent -= 1
					when "string"
						append "\""
						append item\gsub "\"","\\\""
						append "\""
					else
						append tostring item
				if i ~= #expr
					append ","
			append "}"
		nextExpr expr
		table.concat strs

	ToCodeText:(exprData)->
		codeMode = Expression.CodeMode
		Expression.CodeMode = true

		strs,args = switch exprData[1]
			when "Trigger"
				eventArgs = exprData[4][2].Args or {}
				{"return\n"},{k,v\match "%a*" for k,v in pairs eventArgs}
			when "UnitAction"
				{"return\n"},{action:"Action"}
			else
				{},{}

		insert = table.insert
		rep = string.rep
		append = (indent,str)->
			insert strs,rep("\t",indent) if indent > 0
			insert strs,str if str ~= ""
			insert strs,"\n"
		appendTap = (num)-> rep "\t",num

		local localSet
		local locals
		local nextExpr
		createHandleAction = (startPattern,ending="")->
			(indent,expr)->
				localSet = {k,v for k,v in pairs args}
				locals = {}
				append indent,tostring expr
				for i = 2,#expr
					nextExpr expr,i,indent+1
				if #locals > 0
					localLine = rep("\t",indent+1).."local "..table.concat(locals,", ").."\n"
					for i = 1,#strs
						if strs[i]\match startPattern
							insert strs,i+2,localLine
							break
				append indent,"end"..ending

		handleAction = createHandleAction "^Action%("," )"
		handleRun = createHandleAction "^%-%-%[%[Run%]%]",","
		handleStop = createHandleAction "^%-%-%[%[Stop%]%]"

		nextExpr = (parentExpr,index,indent)->
			expr = index and parentExpr[index] or parentExpr
			switch expr[1]
				when "ConditionNode"
					append 0,"return"
					append indent,tostring expr
					for i = 3,#expr
						nextExpr expr,i,indent+1
					append indent,"end )"
				when "Trigger"
					append indent,tostring expr
					append 0,"" unless Expression.CodeMode
					for i = 4,#expr
						nextExpr expr,i,indent+1
					append indent,")"
				when "Event"
					append indent,tostring expr
					for i = 2,#expr
						nextExpr expr,i,indent+1
					append indent,"),"
					indent -= 1
				when "Condition"
					append indent,tostring expr
					for i = 2,#expr
						nextExpr expr,i,indent+1
					append indent,"end ),"
				when "Action"
					handleAction indent,expr
				when "UnitAction"
					append indent,tostring expr
					append 0,"" unless Expression.CodeMode
					for i = 3,#expr
						nextExpr expr,i,indent+1
					append indent,")"
				when "Available"
					append indent,tostring expr
					for i = 2,#expr
						nextExpr expr,i,indent+1
					append indent,"end,"
				when "Run"
					handleRun indent,expr
				when "Stop"
					handleStop indent,expr
				when "If"
					append indent,tostring expr
					for i = 2,#expr[3]
						nextExpr expr[3],i,indent+1
					append indent,"else"
					for i = 2,#expr[4]
						nextExpr expr[4],i,indent+1
					append indent,"end"
				when "Perform"
					performExpr = expr[2]
					append indent,tostring expr
					for i = 2,#performExpr[3]
						nextExpr performExpr[3],i,indent+1
					append indent,expr[3] and ") )" or ")"
				when "Sequence","Spawn"
					groupExpr = expr[2]
					append indent,tostring expr
					for i = 2,#groupExpr
						nextExpr groupExpr,i,indent+1
					append indent,")"
				when "Loop"
					append indent,tostring expr
					for i = 2,#expr[6]
						nextExpr expr[6],i,indent+1
					append indent,"end )"
				when "SetLocal"
					assignExpr = expr[2]
					exprName = assignExpr[1]
					varType = exprName\sub 9,-1
					varName = assignExpr[2][2]
					if varName ~= "InvalidName" and not localSet[varName]
						if not (args and args[varName])
							localSet[varName] = varType
							table.insert locals,varName
					append indent,tostring expr
				else
					append indent,tostring expr
			if parentExpr
				switch parentExpr[1]
					when "Condition","Available","ConditionNode"
						if parentExpr ~= expr and parentExpr[#parentExpr] ~= expr
							insert strs,#strs," and"
					when "ActionGroup"
						if parentExpr ~= expr and parentExpr[#parentExpr] ~= expr
							insert strs,#strs,", "
		nextExpr exprData,nil,0
		Expression.CodeMode = codeMode
		table.concat strs

	GetLintFunction:(locals,globals)->
		errors = nil
		varScope = {locals}
		varInScope = (varName)->
			local result
			for scope in *varScope
				varType = scope[varName]
				result = varType if varType
			return result
		err = (...)-> table.insert errors,table.concat{...}
		pushScope = -> table.insert varScope,{}
		popScope = -> table.remove varScope
		nextExpr = (expr,parentExpr)->
			return if "table" ~= type expr
			switch expr[1]
				when "Trigger"
					nextExpr expr[3]
				when "Condition","Action","UnitAction","ConditionNode","Available","Run","Stop","Event"
					return
				when "Perform"
					nextExpr expr[2][2]
				when "Loop"
					-- check params before adding loop variable into scope
					for subExpr in *expr[3,]
						nextExpr subExpr,expr
					varName = expr[2][2]
					if varInScope varName
						err "Loop variable \"",varName,"\" uses the same name with a local variable."
					else
						scope = varScope[#varScope]
						scope[varName] = "Number"
				when "SetLocal"
					assignExpr = expr[2]
					varName = assignExpr[2][2]
					if varName == "InvalidName"
						err "Use local variable with invalid name."
					elseif varName\sub(1,2) == "g_" and globals[varName\sub 3]
						err "Name of local variable duplicates with global variable \"",
							varName, "\"."
					else
						localType = varInScope varName
						varType = assignExpr[1]\match "^SetLocal(.*)"
						if localType and localType ~= varType
							err "Assign local variable \"",varName,
								"\" of type \"",localType,
								"\" to value of type \"",varType,"\"."
						else
							scope = varScope[#varScope]
							scope[varName] = varType
							if not localType
								usedLocals = {}
								searchExpr = (expr)->
									return unless "table" == type expr
									if expr[1] ~= "LocalName" and expr[1]\match "^Local"
										usedLocals[expr[2][2]] = true
									for i = 2,#expr
										searchExpr expr[i]
								searchExpr assignExpr[3]
								if usedLocals[varName]
									err "Local variable \"",varName,
										"\" of type \"",varType,
										"\" is used without initialization."
					nextExpr assignExpr[3],assignExpr
				when "SetGlobal"
					assignExpr = expr[2]
					varName = assignExpr[2][2]
					if varName == "InvalidName"
						err "Use global variable with invalid name."
					varType = assignExpr[1]\match "^SetGlobal(.*)"
					globalType = globals[varName]
					if globalType
						if globalType ~= varType
							err "Assign global variable \"g_",varName,
								"\" of type \"",globalType,
								"\" to value of type \"",varType,"\"."
					else
						err "Assign an uninitialized global variable \"g_",varName,
							"\" to value of type \"",varType,"\"."
					nextExpr assignExpr[3],assignExpr
				when "LocalName"
					varName = expr[2]
					if varName == "InvalidName"
						err "Use local variable with invalid name."
						return
					elseif varName\sub(1,2) == "g_" and globals[varName\sub 3]
						err "Name of local variable duplicates with global variable \"",
							varName, "\"."
						return
					localType = varInScope varName
					varType = parentExpr[1]\match "^Local(.*)"
					if localType
						if localType ~= varType
							err "Local variable \"",varName,
								"\" of type \"",localType,
								"\" is used as type \"",varType,"\"."
					else
						err "Local variable \"",varName,
							"\" of type \"",varType,
							"\" is used without initialization."
				when "GlobalName"
					varName = expr[2]
					if varName == "InvalidName"
						err "Use global variable with invalid name."
						return
					globalType = globals[varName]
					varType = parentExpr[1]\match "^Global(.*)"
					if globalType
						if globalType ~= varType
							err "Global variable \"g_",varName,
								"\" of type \"",globalType,
								"\" is used as type \"",varType,"\"."
					else
						err "Global variable \"g_",varName,
							"\" of type \"",varType,
							"\" is used without initialization."
				else
					for subExpr in *expr[2,]
						nextExpr subExpr,expr
		checkExpr = (expr,parentExpr,itemType)->
			errors = {} if errors == nil or #errors > 0
			switch itemType
				when "Start"
					pushScope!
					nextExpr expr,parentExpr
				when "Mid"
					popScope!
					pushScope!
				when "End"
					popScope!
				else
					nextExpr expr,parentExpr
			#errors > 0 and table.concat(errors,"\n") or ""
		checkExpr

	LintNotPass:(exprData)->
		args = switch exprData[1]
			when "Trigger"
				exprData[4][2].Args
			when "UnitAction"
				action:"Action"
			else
				{}
		locals = args and {k,v\match("^%a*") for k,v in pairs args} or nil
		globals = {expr[2][2],expr[3].Type for expr in *editor\getGlobalExpr![2,]}

		lintFunc = TriggerDef.GetLintFunction locals,globals

		checkError = (parentExpr,index)->
			expr = index and parentExpr[index] or parentExpr
			switch expr[1]
				when "Trigger"
					for i = 4,#expr
						return true if checkError expr,i
				when "UnitAction"
					for i = 3,#expr
						return true if checkError expr,i
				when "Event","Condition","Action","Available","Run","Stop"
					return true if lintFunc(expr,parentExpr,"Start") ~= ""
					for i = 2,#expr
						return true if checkError expr,i
					return true if lintFunc(expr,parentExpr,"End") ~= ""
				when "If"
					return true if lintFunc(expr,parentExpr,"Start") ~= ""
					for i = 2,#expr[3]
						return true if checkError expr[3],i
					return true if lintFunc(expr,parentExpr,"Mid") ~= ""
					for i = 2,#expr[4]
						return true if checkError expr[4],i
					return true if lintFunc(expr,parentExpr,"End") ~= ""
				when "Loop"
					return true if lintFunc(expr,parentExpr,"Start") ~= ""
					for i = 2,#expr[6]
						return true if checkError expr[6],i
					return true if lintFunc(expr,parentExpr,"End") ~= ""
				else
					return true if lintFunc(expr,parentExpr) ~= ""
			false

		checkError exprData
}

LoadAPIs!

Groups = {}
Types = {}
for exprName,expr in pairs Items
	Groups[expr.Group] or= {}
	table.insert Groups[expr.Group],expr
	Types[expr.Type] or= {}
	table.insert Types[expr.Type],expr
	if expr.Type == "None" or expr.TypeIgnore
		Types["TriggerAction"] or= {}
		table.insert Types["TriggerAction"],expr
for _,group in pairs Groups
	table.sort group,(a,b)-> a.Name < b.Name
for _,typeList in pairs Types
	table.sort typeList,(a,b)-> a.Name < b.Name

TriggerDef.Groups = Groups
TriggerDef.Types = Types

TriggerDef
