Dorothy!
Class,property = unpack require "class"
MainSceneView = require "View.Scene.MainScene"

Class
  __partial: => MainSceneView!
  __init: =>
    @scrollArea\slots "scroll",(delta)->
      @menu\eachChild (child)->
        child.position += delta
