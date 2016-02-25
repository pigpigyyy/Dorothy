Dorothy!
ExprPreviewView = require "View.Control.Trigger.ExprPreview"

Class ExprPreviewView,
	__init:=>
		@owner = nil -- ExprChooser
		@setupMenuScroll @menu
		@previewItem.enabled = false

	update:=>
		@previewItem.text = tostring @owner.curExpr or ""
		offset = @offset
		@offset = oVec2.zero
		@viewSize = @menu\alignItems 5
		@offset = offset
