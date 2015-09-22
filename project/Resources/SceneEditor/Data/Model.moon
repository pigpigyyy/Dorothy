--Dorothy!
oVec2 = (x,y)->{x,y}

local *

Point = (x,y)->	-> oVec2(x,y)

Types =
	PlatformWorld:1
	UILayer:2
	Camera:3
	Layer:4
	World:5
	Node:6
	Body:7
	Model:8
	Sprite:9
	Effect:10
	Unit:11

TypeNames = {v, k for k,v in pairs Types}

DataCreater = (dataDef)->
	dataMt =
		__newindex:(k,v)=>
			@[dataDef[k][1]] = v
		__index:(k)=>
			@[dataDef[k][1]]
	(data)->
		if not data
			data = {v[1],(type(v[2]) == "function" and v[2]() or v[2]) for _,v in pairs dataDef}
		data.typeName = TypeNames[data[1]]
		setmetatable data,dataMt
		data

Items =
	PlatformWorld:DataCreater {
		-- property
		itemType:{1,Types.PlatformWorld}
		gravity:{2,Point(0,-10)}
		contact:{3,false}
		simulation:{4,1}
		children:{5,false}
		-- design
		outline:{6,true}
	}
	UILayer:DataCreater {
		-- property
		itemType:{1,Types.UILayer}
		children:{2,false}
	}
	Camera:DataCreater {
		-- property
		itemType:{1,Types.Camera}
		position:{2,Point(0,0)}
		zoom:{3,1}
		target:{4,""}
		ratioX:{5,1}
		ratioY:{6,1}
		children:{7,false}
	}
	Layer:DataCreater {
		-- property
		itemType:{1,Types.Layer}
		name:{2,""}
		index:{3,0}
		ratioX:{4,1}
		ratioY:{5,1}
		offset:{6,Point(0,0)}
		zoom:{7,1}
		children:{8,false}
	}
	World:DataCreater {
		-- property
		itemType:{1,Types.World}
		name:{2,""}
		gravity:{3,Point(0,-10)}
		contact:{4,false}
		simulation:{5,1}
		children:{6,false}
		-- design
		outline:{7,false}
	}
	Layer:DataCreater {
		-- property
		itemType:{1,Types.Layer}
		name:{2,""}
		index:{3,0}
		ratioX:{4,1}
		ratioY:{5,1}
		offset:{6,Point(0,0)}
		zoom:{7,1}
		children:{8,false}
	}
	Body:DataCreater {
		-- property
		itemType:{1,Types.Body}
		name:{2,""}
		position:{3,Point(0,0)}
		angle:{4,0}
	}

data = Items.Layer!

print data.typeName
for item in *data
	print item
