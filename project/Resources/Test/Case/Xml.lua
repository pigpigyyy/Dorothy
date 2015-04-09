doXml([[
<Scene Name="scene">
	<LayerColor Name="layer" Angle="10" Color="0xff00ffff" AnchorX="0" AnchorY="0"/>
	<LabelTTF Name="label" Text="Hello" FontName="Arial" FontSize="20" Color="0x000000"
		X="layer.contentSize.width*0.5"
		Y="layer.contentSize.height*0.5"/>
	<Data>
		<Loop Name="fade">
			<Sequence>
				<Grid.Twirl Time="5" GridX="100" GridY="100" Twirls="1" Amplitude="0.5"/>
				<Opacity Time="1" Alpha="0"/>
				<Opacity Time="1" Alpha="1"/>
			</Sequence>
		</Loop>
		<Sequence Name="scale">
			<Scale Time="1" X="3" Y="3" Ease="OutElastic"/>
			<Delay Time="4"/>
			<Scale Time="1" X="1" Y="1" Ease="OutElastic"/>
		</Sequence>
	</Data>
	<Schedule>
		once(function()
			wait(seconds(1))
			label:runAction(scale)
			for i = 5,0,-1 do
				wait(seconds(1))
				label.text = tostring(i)
			end
			wait(seconds(1))
			label.text = "Good"
			scene:runAction(fade)
		end)
	</Schedule>
	<Script>
		CCDirector:run(scene)
	</Script>
</Scene>
]])()
