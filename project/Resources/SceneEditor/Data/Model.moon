Dorothy!

Point = (x,y)-> -> oVec2 x or 0,y or 0
Rect = (x,y,width,height)-> -> CCRect x or 0,y or 0,width or 0,height or 0

Simulation = (level)->
	switch level
		when 1
			1,1
		when 2
			4,2
		when 3
			8,3

Children = (parent,data)->
	children = data.children
	if children
		for i,child in ipairs children
			child = child parent,i
			if child
				parent\addChild child

Contact = (world,data)->
	groups = data.groups
	contacts = data.contacts
	if groups and contacts
		for contact in *contacts
			world\setShouldContact unpack contact

Groups = (data)->
	default = {
		[0]:"Hide"
		"P1","P2","P3"
		"P4","P5","P6"
		"P7","P8","P9"
		"P10","P11","P12"
		"DetectPlayer" -- 13
		"Terrain" -- 14
		"Detect" -- 15
	}
	setmetatable data or {}, {
		__index: default
		__tostring: =>
			str = "{"
			for k,v in pairs @
				str ..= "["..k.."]=\""..v.."\","
			str = str\sub 1,-2 if #str > 1
			str ..= "}"
			str
		}

Contacts = (data)->
	setmetatable data or {{1,1,true}},{
		__tostring:=>
			str = "{"
			for i,contact in ipairs @
				str ..= "{"
				for i,item in ipairs contact
					switch tolua.type item
						when "boolean"
							str ..= item and "t" or "f"
						else
							str ..= tostring item
					str ..= "," unless i == #contact
				str ..= "}"
				str ..= "," unless i == #@
			str ..= "}"
			str
		}

local Align
Align = {
	Center:1
	LeftBottom:2
	LeftTop:3
	RightTop:4
	RightBottom:5
	ToName:(align)->
		switch align
			when Align.Center
				"Center"
			when Align.LeftBottom
				"Left Bottom"
			when Align.LeftTop
				"Left Top"
			when Align.RightTop
				"Right Top"
			when Align.RightBottom
				"Right Bottom"
			else
				"Center"
	Get:(pos,align)->
		if align == Align.Center
			pos
		else
			{:width,:height} = CCDirector.winSize
			switch align
				when Align.LeftBottom
					pos-oVec2 width/2,height/2
				when Align.LeftTop
					oVec2 pos.x-width/2,height/2-pos.y
				when Align.RightTop
					oVec2(width/2,height/2)-pos
				when Align.RightBottom
					oVec2 width/2-pos.x,pos.y-height/2
				else
					pos

	Convert:(pos,fromAlign,toAlign)->
		pos = Align.Get pos,fromAlign
		if toAlign == Align.Center
			pos
		else
			{:width,:height} = CCDirector.winSize
			switch toAlign
				when Align.LeftBottom
					pos+oVec2 width/2,height/2
				when Align.LeftTop
					oVec2 pos.x+width/2,height/2-pos.y
				when Align.RightTop
					oVec2(width/2,height/2)-pos
				when Align.RightBottom
					oVec2 width/2-pos.x,pos.y+height/2
				else
					pos
}

Types =
	PlatformWorld:1
	UILayer:2
	Camera:3
	Layer:4
	World:5
	Body:6
	Model:7
	Sprite:8
	Effect:9
	SubCam:10

TypeNames = {v,k for k,v in pairs Types}

local Items

DataCreater = (dataDef)->
	create = dataDef.create
	dataDef.create = nil
	dataMt =
		__call:(parent,index)=> create @,parent,index
		__newindex:(k,v)=>
			if "number" == type k
				rawset @,k,v
			else
				itemDef = dataDef[k]
				if itemDef
					if @[itemDef[1]] ~= v
						@[itemDef[1]] = v
						if k ~= "ui" and k ~= "camera"
							emit "Scene.Dirty",true
							if k ~= "fold" and k ~= "display"
								emit "Scene.ViewArea.Frame",@
				else
					error "assign invalid field #{k} to data"
		__index:(k)=>
			itemDef = dataDef[k]
			if itemDef
				if itemDef[1] == 1
					TypeNames[@[itemDef[1]]]
				else
					@[itemDef[1]]
			else
				nil
		__tostring:=>
			strs = {}
			insert = table.insert
			append = (str)-> insert strs,str
			append "{"
			for i,item in ipairs @
				switch tolua.type item
					when "boolean"
						append item and "t" or "f"
					when "oVec2"
						append string.format "v(%.2f,%.2f)",item.x,item.y
					when "CCSize"
						append string.format "s(%d,%d)",item.width,item.height
					when "CCRect"
						append string.format "r(%d,%d,%d,%d)",item.origin.x,item.origin.y,item.size.width,item.size.height
					when "string"
						append "\""
						append item
						append "\""
					when "table"
						if getmetatable item
							append tostring item
						elseif #item > 0
							append "{"
							for i,v in ipairs item
								append tostring v
								append "," unless i == #item
							append "}"
						else
							append "f"
					when "number"
						append string.format "%.2f",item
					else
						append tostring item
				append "," unless i == #@
			append "}"
			table.concat(strs)\gsub("%.00","")
	(data)->
		if not data
			data = {v[1],(type(v[2]) == "function" and v[2]! or v[2]) for _,v in pairs dataDef}
		data.typeName = TypeNames[data[1]]
		data.getItems = => {v[1],k for k,v in pairs dataDef}
		setmetatable data,dataMt
		data

Items =
	loadData:(filename)->
		setupData = (data)->
			Items[TypeNames[data[1]]] data
			if data.children
				for child in *data.children
					setupData child
		data = dofile filename
		setupData data
		Contacts data.contacts if data.contacts
		Groups data.groups if data.groups
		if data.camera
			camera = data.camera
			Items.Camera camera
			if camera.subCams
				for cam in *camera.subCams
					Items.SubCam cam
		data

	dumpData:(data,filename)->
		str = "local v,r,t,f = require(\"oVec2\"),require(\"CCRect\"),true,false\nreturn "..tostring data
		oContent\saveToFile filename,str

	:Align
	:Simulation

	PlatformWorld:DataCreater
		-- property
		itemType:{1,Types.PlatformWorld}
		gravity:{2,-10}
		contacts:{3,Contacts}
		groups:{4,Groups}
		simulation:{5,1}
		camera:{6,false}
		ui:{7,false}
		children:{8,false}
		-- design
		outline:{9,true}
		-- helper
		create:=>
			world = with oPlatformWorld!
				.gravity = oVec2 0,@gravity
				.showDebug = @outline
				\setIterations Simulation @simulation
			world.scheduler = with CCScheduler!
				.timeScale = 0
			CCDirector.scheduler\schedule world.scheduler
			world\slot "Cleanup",->
				CCDirector.scheduler\unschedule world.scheduler
			editor.items = {Scene:world}
			editor.itemDefs = {[world]:@}
			world.itemData = @
			@.camera world if @camera
			@.ui world if @ui
			Contact world,@
			Children world,@
			world

	UILayer:DataCreater
		-- property
		itemType:{1,Types.UILayer}
		visible:{2,true}
		children:{3,false}
		-- design
		display:{4,true}
		fold:{5,false}
		-- helper
		create:(scene)=>
			layer = scene.UILayer
			editor.items.UI = layer
			layer.position += editor.origin
			layer.visible = @visible and @display
			editor.itemDefs[layer] = @
			Children layer,@
			nil

	Camera:DataCreater
		-- property
		itemType:{1,Types.Camera}
		boundary:{2,false}
		area:{3,Rect!}
		subCams:{4,false}
		-- helper
		create:(scene)=>
			camera = scene.camera
			editor.items.Camera = camera
			editor.itemDefs[camera] = @
			nil

	SubCam:DataCreater
		-- property
		itemType:{1,Types.SubCam}
		name:{2,"camera"}
		position:{3,Point(0,0)}
		zoom:{4,1}
		angle:{5,0}
		-- helper
		create:=>

	Layer:DataCreater
		-- property
		itemType:{1,Types.Layer}
		name:{2,"layer"}
		ratioX:{3,0}
		ratioY:{4,0}
		offset:{5,Point(0,0)}
		zoom:{6,1}
		visible:{7,true}
		children:{8,false}
		-- design
		display:{9,true}
		fold:{10,false}
		-- helper
		create:(scene,index)=>
			scene\setLayerOffset index,@offset
			layer = with scene\getLayer index
				.scaleX = @zoom
				.scaleY = @zoom
				.visible = @visible and @display
			editor.items[@name] = layer
			editor.itemDefs[layer] = @
			Children layer,@
			nil

	World:DataCreater
		-- property
		itemType:{1,Types.World}
		name:{2,"world"}
		gravity:{3,Point(0,-10)}
		simulation:{4,1}
		ratioX:{5,0}
		ratioY:{6,0}
		offset:{7,Point(0,0)}
		zoom:{8,1}
		visible:{9,true}
		children:{10,false}
		-- design
		outline:{11,true}
		display:{12,true}
		fold:{13,false}
		-- helper
		create:(scene,index)=>
			scene\setLayerOffset index,@offset
			layer = with scene\getLayer index
				.scaleX = @zoom
				.scaleY = @zoom
			world = with oWorld!
				.gravity = @gravity
				.showDebug = @outline
				.visible = @visible and @display
				\setIterations Simulation @simulation
			layer\addChild world
			world.scheduler = with CCScheduler!
				.timeScale = 0
			CCDirector.scheduler\schedule world.scheduler
			world\slot "Cleanup",->
				CCDirector.scheduler\unschedule world.scheduler
			oData\apply world
			Contact world,editor.sceneData
			editor.items[@name] = world
			editor.itemDefs[world] = @
			Contact world,@
			Children world,@
			nil

	Body:DataCreater
		-- property
		itemType:{1,Types.Body}
		name:{2,"body"}
		file:{3,""}
		group:{4,1}
		position:{5,Point(0,0)}
		angle:{6,0}
		visible:{7,true}
		-- design
		display:{8,true}
		-- helper
		create:(parent)=>
			world = editor.items.Scene
			if "oWorld" == tolua.type parent
				world = parent
			body = with oBody @file,world,@position,@angle
				.data\each (_,v)->
					v.group = @group if "oBody" == tolua.type v
				.visible = @visible and @display
			editor.items[@name] = body
			editor.itemDefs[body] = @
			body

	Model:DataCreater
		-- property
		itemType:{1,Types.Model}
		name:{2,"model"}
		file:{3,""}
		position:{4,Point(0,0)}
		angle:{5,0}
		scale:{6,Point(1,1)}
		skew:{7,Point(0,0)}
		opacity:{8,1}
		look:{9,""}
		animation:{10,""}
		speed:{11,1}
		loop:{12,false}
		faceRight:{13,false}
		visible:{14,true}
		-- design
		display:{15,true}
		-- ui
		align:{16,Align.Center}
		-- helper
		create:=>
			model = with oModel @file
				.position = Align.Get @position,@align
				.angle = @angle
				.scaleX = @scale.x
				.scaleY = @scale.y
				.skewX = @skew.x
				.skewY = @skew.y
				.opacity = @opacity
				.look = @look
				.speed = @speed
				.loop = @loop
				.faceRight = @faceRight
				.visible = @visible and @display
				\play @animation
			editor.items[@name] = model
			editor.itemDefs[model] = @
			model

	Sprite:DataCreater
		-- property
		itemType:{1,Types.Sprite}
		name:{2,"sprite"}
		file:{3,""}
		position:{4,Point(0,0)}
		angle:{5,0}
		scale:{6,Point(1,1)}
		skew:{7,Point(0,0)}
		opacity:{8,1}
		visible:{9,true}
		-- design
		display:{10,true}
		-- ui
		align:{11,Align.Center}
		-- helper
		create:=>
			sprite = with CCSprite @file
				.position = Align.Get @position,@align
				.angle = @angle
				.scaleX = @scale.x
				.scaleY = @scale.y
				.skewX = @skew.x
				.skewY = @skew.y
				.opacity = @opacity
				.visible = @visible and @display
			editor.items[@name] = sprite
			editor.itemDefs[sprite] = @
			sprite

	Effect:DataCreater
		-- property
		itemType:{1,Types.Effect}
		name:{2,"effect"}
		effect:{3,""}
		position:{4,Point(0,0)}
		play:{5,true}
		visible:{6,true}
		-- design
		display:{7,true}
		-- ui
		align:{8,Align.Center}
		-- helper
		create:(parent)=>
			effect = with oEffect @effect
				.parent = parent
				.visible = @visible and @display
				.position Align.Get @position,@align
				\addTo parent
				\start! if @play
			editor.items[@name] = effect
			editor.itemDefs[effect] = @
			nil

Items
