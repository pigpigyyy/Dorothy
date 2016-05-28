Dorothy!
ExprPreviewView = require "View.Control.Trigger.ExprPreview"
Expression = require "Data.API.Expression"

Class ExprPreviewView,
	__init:=>
		@owner = nil -- ExprChooser
		@targetExpr = nil
		@setupMenuScroll @menu
		@previewItem.enabled = false
		@toCodeInner = nil
		@toCode = (expr)-> "| #{ @.toCodeInner expr } |"
		@toDesc = (expr)->
			index = 1
			desc = expr.Desc\gsub "%b[]",->
				index += 1
				"(#{tostring expr[index]})"
			"| #{ desc } |"

	update:=>
		if @targetExpr
			if Expression.CodeMode or @targetExpr.CodeOnly
				@toCodeInner = getmetatable(@targetExpr).ToCode
				@targetExpr.ToCode = @toCode
			else
				@targetExpr.ToDesc = @toDesc
		@previewItem.text = tostring @owner.curExpr or ""
		if @targetExpr
			if Expression.CodeMode or @targetExpr.CodeOnly
				@toCodeInner = nil
				@targetExpr.ToCode = nil
			else
				@targetExpr.ToDesc = nil
		offset = @offset
		@offset = oVec2.zero
		@viewSize = @menu\alignItems 5
		@offset = offset
