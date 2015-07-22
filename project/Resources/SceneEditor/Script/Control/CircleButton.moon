Dorothy!
Class,property = unpack require "class"
CircleButtonView = require "View.Control.CircleButton"

Class
  __partial: (args)=> CircleButtonView args
  __init: =>
    @_text = nil
    @label.texture.antiAlias = false
  text: property => @_text,
    (value)=>
      @_text = value
      if @label
        @label.text = value
        @label.texture.antiAlias = false
