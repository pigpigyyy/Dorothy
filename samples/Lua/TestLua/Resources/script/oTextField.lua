local function oTextField(x,y,fontSize,limit,textChanged)
	local textField = CCTextFieldTTF("","Arial",fontSize)
	textField.anchorPoint = oVec2(0.5,0)
	textField.position = oVec2(x,y)
	local cursor = oLine({oVec2(0,0),oVec2(0,fontSize)},ccColor4(0xff00ffff))
	local blink = CCRepeatForever(
		CCSequence(
		{
			CCShow(),
			CCDelay(0.5),
			CCHide(),
			CCDelay(0.5)
		}))
	cursor.visible = false
	cursor.positionX = textField.contentSize.width
	textField:addChild(cursor)
	textField:registerInputHandler(
		function(self,eventType,text)
			if eventType == CCTextFieldTTF.Attach then
				cursor.visible = true
				cursor:stopAllActions()
				cursor:runAction(blink)
				cursor.positionX = textField.contentSize.width
			elseif eventType == CCTextFieldTTF.Detach then
				cursor.visible = false
				cursor:stopAllActions()
				if textChanged then
					textChanged(self)
				end
			elseif eventType == CCTextFieldTTF.Insert then
				if string.len(self.text) >= limit then
					return false
				end
			elseif eventType == CCTextFieldTTF.Inserted or eventType == CCTextFieldTTF.Deleted then
				cursor:stopAction(blink)
				cursor:runAction(blink)
				cursor.positionX = textField.contentSize.width
				self.texture.antiAlias = false
			end
			return true
		end)
	return textField
end

return oTextField