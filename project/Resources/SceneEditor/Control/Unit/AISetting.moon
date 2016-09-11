Dorothy!
AISettingView = require "View.Control.Unit.AISetting"
import Struct from require "Lib.Utils"
--MessageBox = require "Control.Basic.MessageBox"

Class AISettingView,
	__init:=>
		@instinctPanel.itemSource = Struct.Array!
