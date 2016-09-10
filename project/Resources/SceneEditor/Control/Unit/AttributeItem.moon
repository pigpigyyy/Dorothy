Dorothy!
AttributeItemView = require "View.Control.Unit.AttributeItem"

Class AttributeItemView,
	__init:(args)=>
		@valueFormat = args.valueFormat
		@_selected = false
		@slot "Tapped",-> @selected = not @selected

	value:property => @label.text,
		(value)=>
			if value ~= nil
				format = @valueFormat
				switch tolua.type value
					when "boolean"
						@label.text = tostring value
					when "oVec2"
						@label.text = string.format format..", "..format,value.x,value.y
					when "CCSize"
						@label.text = string.format format..", "..format,value.width,value.height
					else
						@label.text = string.format format,value
				@label.texture.antiAlias = false
			else
				@label.text = ""

	selected:property => @_selected,
		(value)=>
			@_selected = value
			@frame.visible = value
			@emit "Selected",@
