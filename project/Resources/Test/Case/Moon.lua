Dorothy()
local width, height
do
  local _obj_0 = CCDirector.winSize
  width, height = _obj_0.width, _obj_0.height
end
local model
do
  local _with_0 = oModel("ActionEditor/Model/Output/xiaoli.model")
  _with_0.look = "happy"
  _with_0.loop = true
  _with_0.position = oVec2(width * 0.5, height * 0.5)
  _with_0:play("walk")
  model = _with_0
end
local layer
do
  local _with_0 = CCLayer()
  _with_0.anchor = oVec2.zero
  _with_0.touchEnabled = true
  _with_0.touchHandler = function(eventType, touch)
    if eventType == CCTouch.Moved then
      model.position = model.position + touch.delta
    end
    return true
  end
  _with_0:addChild(model)
  layer = _with_0
end
local scene
do
  local _with_0 = CCScene()
  _with_0:addChild(layer)
  scene = _with_0
end
return CCDirector:run(CCScene:crossFade(1, scene))