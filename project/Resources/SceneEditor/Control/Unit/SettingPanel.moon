Dorothy!
SettingPanelView = require "View.Control.Unit.SettingPanel"
--MessageBox = require "Control.Basic.MessageBox"
SolidRect = require "View.Shape.SolidRect"

Class SettingPanelView,
	__init:=>
		@_enabled = true
		thread -> @updateSize!
		animationTime = 0.6

		notifySizeChange = ->
			@height = @maxHeight-@maskContent.positionY
			@expandBtn.positionY = @height-30
			@mask.position = oVec2 0,-@maskContent.positionY
			@emit "SizeChanged",@
		@expandBtn\slot "Expanded",(expanded)->
			if expanded
				@mask.visible = true
				@expandBtn.enabled = false
				@maskContent\perform CCSequence {
					oPos animationTime,0,0,oEase.OutQuad
					CCCall ->
						@expandBtn.enabled = true
						@mask.visible = false
						children = [child for child in *@maskContent.children]
						for child in *children
							child.parent\removeChild child,false
							@addChild child
						notifySizeChange!
				}
			else
				@mask.visible = true
				@mask.stencil = SolidRect x:-1,y:-1,width:@width+2,height:@height+2-60
				@maskContent.positionY = 0
				children = [child for child in *@children]
				for child in *children
					if child ~= @expandBtn and child ~= @mask
						child.parent\removeChild child,false
						@maskContent\addChild child
				@expandBtn.enabled = false
				@maskContent\perform CCSequence {
					oPos animationTime,0,@maxHeight-60,oEase.OutQuad
					CCCall ->
						@expandBtn.enabled = true
						@mask.visible = false
						notifySizeChange!
				}
			@schedule once -> cycle animationTime,notifySizeChange

	updateSize:=>
		@removeChild @mask,false
		@height = @alignItems!.height
		@alignItems!
		@maxHeight = @height
		@addChild @mask

	isEnabled:property => @_enabled,
		(value)=>
			@_enabled = value
			@enabled = value
			for child in *@children
				if child ~= @expandBtn and child ~= @mask
					child.enabled = value
