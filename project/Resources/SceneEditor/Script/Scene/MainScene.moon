Dorothy!
Class,property = unpack require "class"
MainSceneView = require "View.Scene.MainScene"

Class
  __partial: => MainSceneView!
  __init: =>
    @scrollArea\slots "Scrolled",(delta)->
      @menu\eachChild (child)->
        child.position += delta
    
    @scrollArea\slots "ScrollStart",->
      @menu.enabled = false

    @scrollArea\slots "TouchEnded",->
      @menu.enabled = true
    
    @scrollArea.offset = oVec2 -100,0