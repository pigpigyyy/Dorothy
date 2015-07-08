Dorothy!
 
{:width,:height} = CCDirector.winSize

model = with oModel "ActionEditor/Model/Output/xiaoli.model"
	.look = "happy"
	.loop = true
	.position = oVec2 width*0.5, height*0.5
	\play "walk"
	\slots "AnimationEnd",(name)->print name

layer = with CCLayer!
	.anchor = oVec2.zero
	.touchEnabled = true
	\slots "TouchMoved",(touch)->model.position += touch.delta
	\addChild model

scene = with CCScene!
	\addChild layer

CCDirector\run CCScene\crossFade 1,scene
