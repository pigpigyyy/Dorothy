Dorothy!

oBody = require "oBodyEx"

Point = (x,y)-> -> oVec2(x,y)
Simulation = (level)->
	switch level
		when 1
			1,1
		when 2
			4,2
		when 3
			8,3
Children = (parent,children)->
	if children
		for child in *children
			child = child parent
			if child
				parent\addChild child
Contact = (world,contacts)->
	if contacts
		for contact in *contacts
			world\setShouldContact unpack contact

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

TypeNames = {v,k for k,v in pairs Types}

DataCreater = (dataDef)->
	create = dataDef.create
	dataDef.create = nil
	dataMt =
		__call:(parent)-> create parent
		__newindex:(k,v)=>
			itemDef = dataDef[k]
			if itemDef
				@[itemDef[1]] = v
			else
				error "assign invalid field to data"
		__index:(k)=>
			itemDef = dataDef[k]
			if itemDef
				@[itemDef[1]]
			else
				nil
		__tostring:=>
			str = "{"
			for i,item in ipairs @
				switch tolua.type item
					when "boolean"
						str ..= item and "t" or "f"
					when "oVec2"
						str ..= string.format "v(%.2f,%.2f)",item.x,item.y
					when "CCSize"
						str ..= string.format "s(%d,%d)",item.width,item.height
					when "string"
						str ..= "\""..item.."\""
					when "table"
						str ..= "{"
						for i,v in ipairs item
							str ..= tostring v
							str ..= "," unless i == #item
						str ..= "}"
					else
						str ..= tostring item
				str ..= "," unless i == #@
			str ..= "}"
			str = str\gsub ".00",""
			str
	(data)->
		if not data
			data = {v[1],type(v[2]) == "function" and v[2]! or v[2] for _,v in pairs dataDef}
		data.typeName = TypeNames[data[1]]
		data.getItems = => {v[1],k for k,v in pairs dataDef}
		setmetatable data,dataMt
		data

items = nil

local Items
Items =
	loadData:(filename)->
		setupData = (data)->
			Items[TypeNames[data[1]]] data
			if data.children
				for child in *data.children
					setupData child
		data = dofile editor.sceneFullPath..filename
		setupData data
		data

	dumpData:(data,filename)->
		str = "local v,s,t,f = require(\"oVec2\"),require(\"CCSize\"),true,false\nreturn "..tostring data
		oContent\saveToFile editor.sceneFullPath..filename,str

	PlatformWorld:DataCreater
		-- property
		itemType:{1,Types.PlatformWorld}
		gravity:{2,Point(0,-10)}
		contact:{3,false}
		simulation:{4,1}
		camera:{5,false}
		ui:{6,false}
		children:{7,false}
		-- design
		outline:{8,true}
		-- helper
		create:=>
			world = with oPlatformWorld!
				.gravity = @gravity
				.showDebug = @outline
				\setIterations Simulation @simulation
			items = {:world}
			Contact world,@contact
			Children world,@children
			@ui\create! if @ui
			tmpItems = items
			items = nil
			tmpItems

	UILayer:DataCreater
		-- property
		itemType:{1,Types.UILayer}
		children:{2,false}
		-- helper
		create:=>
			layer = items.world.UILayer
			Children layer,@children
			nil

	Camera:DataCreater
		-- property
		itemType:{1,Types.Camera}
		position:{2,Point(0,0)}
		zoom:{3,1}
		target:{4,""}
		ratioX:{5,1}
		ratioY:{6,1}
		-- helper
		create:=> nil

	Layer:DataCreater
		-- property
		itemType:{1,Types.Layer}
		name:{2,"layer"}
		index:{3,0}
		ratioX:{4,0}
		ratioY:{5,0}
		offset:{6,Point(0,0)}
		zoom:{7,1}
		children:{8,false}
		-- helper
		create:=>
			world = with items.world
				\setLayerRatio @index,oVec2(@ratioX,@ratioY)
				\setLayerOffset @index,@offset
			layer = with world\getLayer @index
				.scaleX = @zoom
				.scaleY = @zoom
			items[@name] = layer
			Children layer,@children
			nil

	World:DataCreater
		-- property
		itemType:{1,Types.World}
		name:{2,"world"}
		gravity:{3,Point(0,-10)}
		contact:{4,false}
		simulation:{5,1}
		children:{6,false}
		-- design
		outline:{7,false}
		-- helper
		create:=>
			world = with oWorld!
				.gravity = @gravity
				.showDebug = @outline
				\setIterations Simulation @simulation
			Contact world,@contact
			Children world,@children
			world

	Body:DataCreater
		-- property
		itemType:{1,Types.Body}
		name:{2,"body"}
		file:{3,""}
		position:{4,Point(0,0)}
		angle:{5,0}
		-- helper
		create:(parent)=>
			world = items.world
			if "oWorld" == tolua.type parent
				world = parent
			body = oBody @file,world,@position,@angle
			items[@name] = body
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
		faceRight:{13,true}
		-- helper
		create:=>
			model = with oModel @file
				.position = @position
				.angle = @angle
				.scaleX = @scale.x
				.scaleY = @scale.y
				.opacity = @opacity
				.look = @look
				.speed = @speed
				.loop = @loop
				.faceRight = @faceRight
				\play @animation
			items[@name] = model
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
		-- helper
		create:=>
			sprite = with CCSprite @file
				.position = @position
				.angle = @angle
				.scaleX = @scale.x
				.scaleY = @scale.y
				.skewX = @skew.x
				.skewY = @skew.y
				.opacity = @opacity
			items[@name] = sprite
			sprite

	Effect:DataCreater
		-- property
		itemType:{1,Types.Effect}
		name:{2,"effect"}
		effect:{3,""}
		offset:{4,Point(0,0)}
		play:{5,false}
		-- helper
		create:(parent)=>
			effect = oEffect(@effect)
			effect\attachTo parent
			effect\setOffset @offset
			if @play
				effect\start!
			effect

Items
