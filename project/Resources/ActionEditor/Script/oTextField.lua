local require = using("ActionEditor.Script")
local CCTextFieldTTF = require("CCTextFieldTTF")
local oVec2 = require("oVec2")
local oLine = require("oLine")
local ccColor4 = require("ccColor4")
local CCRepeatForever = require("CCRepeatForever")
local CCSequence = require("CCSequence")
local CCShow = require("CCShow")
local CCDelay = require("CCDelay")
local CCHide = require("CCHide")

local function oTextField(x,y,fontSize,limit,textChanged)
	local textField = CCTextFieldTTF("","Arial",fontSize)
	textField.anchor = oVec2(0.5,0)
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
	textField:slot("InputAttach",function(self)
		cursor.visible = true
		cursor:stopAllActions()
		cursor:runAction(blink)
		cursor.positionX = self.contentSize.width
		return true
	end)
	textField:slot("InputDetach",function(self)
		cursor.visible = false
		cursor:stopAllActions()
		if textChanged then
			textChanged(self)
		end
		return true
	end)
	textField:slot("InputInserting",function(addText,self)
		if string.len(self.text) >= limit and addText ~= "\n" then
			return false
		end
		return true
	end)
	local function inputed(_,self)
		cursor:stopAction(blink)
		cursor:runAction(blink)
		cursor.positionX = textField.contentSize.width
		self.texture.antiAlias = false
	end
	textField:slot("InputInserted",inputed)
	textField:slot("InputDeleted",inputed)
	return textField
end

return oTextField