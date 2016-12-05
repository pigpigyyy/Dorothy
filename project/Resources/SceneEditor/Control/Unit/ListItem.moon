Dorothy!
ListItemView = require "View.Control.Unit.ListItem"
import Path from require "Lib.Utils"

Class
	__partial:(args)=>
		args.item = args.text
		if args.text
			ext = Path.getExtension args.text
			if ext
				args.text = args.text\sub(1,-#ext-2)\gsub("[\\/]",".")
		ListItemView args

	__init:(args)=>
		@opBtn\slot "Tapped",->
			@emit "Operation",@
		@opBtn.color = ccColor3 0xff0080 if @opText == "-"
		@item = args.item

	text:property => @label.text,
		(value)=>
			@label.text = value
			@label.texture.antiAlias = false

	opText:property => @opBtn.text
