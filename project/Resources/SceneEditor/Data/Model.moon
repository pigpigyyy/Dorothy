Dorothy!

Point = (x,y)-> -> oVec2(x,y)

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
	Unit:10

TypeNames = {v,k for k,v in pairs Types}

DataCreater = (dataDef)->
	dataMt =
		__newindex:(k,v)=>
			@[dataDef[k][1]] = v
		__index:(k)=>
			@[dataDef[k][1]]
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
		setmetatable data,dataMt
		data

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
		children:{5,false}
		-- design
		outline:{6,true}

	UILayer:DataCreater
		-- property
		itemType:{1,Types.UILayer}
		children:{2,false}

	Camera:DataCreater
		-- property
		itemType:{1,Types.Camera}
		position:{2,Point(0,0)}
		zoom:{3,1}
		target:{4,""}
		ratioX:{5,1}
		ratioY:{6,1}
		children:{7,false}

	Layer:DataCreater
		-- property
		itemType:{1,Types.Layer}
		name:{2,""}
		index:{3,0}
		ratioX:{4,1}
		ratioY:{5,1}
		offset:{6,Point(0,0)}
		zoom:{7,1}
		children:{8,false}

	World:DataCreater
		-- property
		itemType:{1,Types.World}
		name:{2,""}
		gravity:{3,Point(0,-10)}
		contact:{4,false}
		simulation:{5,1}
		children:{6,false}
		-- design
		outline:{7,false}

	Layer:DataCreater
		-- property
		itemType:{1,Types.Layer}
		name:{2,""}
		index:{3,0}
		ratioX:{4,1}
		ratioY:{5,1}
		offset:{6,Point(0,0)}
		zoom:{7,1}
		children:{8,false}

	Body:DataCreater
		-- property
		itemType:{1,Types.Body}
		name:{2,""}
		position:{3,Point(0,0)}
		angle:{4,0}

	Model:DataCreater
		-- property
		itemType:{1,Types.Model}
		name:{2,""}
		position:{3,Point(0,0)}
		angle:{4,0}
		scale:{5,Point(1,1)}
		skew:{6,Point(0,0)}
		opacity:{7,1}
		look:{8,""}
		animation:{9,""}
		speed:{10,1}
		loop:{11,false}
		faceRight:{12,true}

	Sprite:DataCreater
		-- property
		itemType:{1,Types.Sprite}
		name:{2,""}
		position:{3,Point(0,0)}
		angle:{4,0}
		scale:{5,Point(1,1)}
		skew:{6,Point(0,0)}
		opacity:{7,1}

	Effect:DataCreater
		-- property
		itemType:{1,Types.Effect}
		name:{2,""}
		offset:{3,Point(0,0)}

	Unit:DataCreater
		-- property
		itemType:{1,Types.Unit}
		name:{2,""}
		position:{3,Point(0,0)}
		ai:{4,""}

Items
