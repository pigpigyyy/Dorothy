Dorothy!
Class,property = unpack require "class"
ButtonView = require "View.Control.Button"

Class
  __partial: (args)=> ButtonView args
  __init: =>
    @_text = nil
    @label.texture.antiAlias = false
  text: property => @_text,
    (value)=>
      @_text = value
      if @label
        @label.text = value
        @label.texture.antiAlias = false
