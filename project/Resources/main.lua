Dorothy()

local winSize = CCDirector.winSize
if winSize.width >= 1280 and winSize.height >= 960 then
	CCView:setDesignResolution(winSize.width/2,winSize.height/2,CCView.ExactFit)
end

local fontSize_cov =
{
	[10] = 14,
	[12] = 14,
	[13] = 16,
	[14] = 17,
	[16] = 17,
	[17] = 17,
	[18] = 17,
	[20] = 20,
	[24] = 24,
}

local CCLabelTTF = builtin.CCLabelTTF
builtin.CCLabelTTF = function(text,fontName,fontSize)
	local cov = fontSize_cov[fontSize]
	if cov then
		return CCLabelBMFont(text,"Font/Arial"..cov..".fnt",CCLabelBMFont.AutomaticWidth,CCTextAlign.HCenter)
	end
	return CCLabelTTF(text,fontName,fontSize)
end

require("Dev.Entry")
--require("ActionEditor.Script.main")
--require("BodyEditor.Script.main")
--require("EffectEditor.Script.main")
--require("SceneEditor.main") -- need compile before run
