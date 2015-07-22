return function(args)
Dorothy(args)

local scene = CCScene()

local fade = CCRepeatForever(CCSequence({CCGrid:twirl(5,CCSize(100,100),oVec2(0,0),1,0.5),oOpacity(1,0),oOpacity(1,1)}))
scene.fade = fade

local scale = CCSequence({oScale(1,3,3,oEase.OutElastic),CCDelay(4),oScale(1,1,1,oEase.OutElastic)})
scene.scale = scale

local layer1 = CCLayerColor(ccColor4(0xff00ffff))
layer1.anchor = oVec2(0,0)
layer1.angle = 10
scene:addChild(layer1)

local label = CCLabelTTF("Hello","Arial",20)
label.positionX = scene.contentSize.width*0.5
label.positionY = scene.contentSize.height*0.5
label.color = ccColor3(0x000000)
scene:addChild(label)
scene.label = label


		scene:schedule(once(function()
			wait(seconds(1))
			label:runAction(scale)
			for i = 5,0,-1 do
				wait(seconds(1))
				label.text = tostring(i)
			end
			wait(seconds(1))
			label.text = "Good"
			scene:runAction(fade)
		end))
		CCDirector:run(CCScene:crossFade(0.5,scene))
	

return scene

end