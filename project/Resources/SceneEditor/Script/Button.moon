Dorothy!
Class,property = unpack require "class"
ButtonView = require "View.Button"

Class
  __partial: (args)=> ButtonView args
  __init: => @label.texture.antiAlias = false
  text: property => @label.text,
    (value)=>
      @label.text = value
      @label.texture.antiAlias = false
