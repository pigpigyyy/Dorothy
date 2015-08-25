local function genIndex()
	local i = 0
	return function() i = i + 1 return i end
end

local index = genIndex()

local Dorothy =
{
	tolua =
	{
		childs =
		{
			type =
			{
				args = "(...)",
				description = " get tolua++ type string of any object",
				typeName = "string",
				returns = "(typename: string)",
				static = true,
				type = "function",
			},
			cast =
			{
				args = "(object: CCObject, classname: string)",
				description = " type cast, if classname is not a super or base class of object, it returns nil",
				typeName = "CCObject",
				returns = "(object: CCObject)",
				static = true,
				type = "function",
			},
			class =
			{
				args = "(classname: string)",
				description = " get tolua++ type object of given classname",
				returns = "(type: table)",
				static = true,
				type = "function",
			},
			setpeer =
			{
				args = "(item: userdata, data: table)",
				description = "",
				returns = "()",
				static = true,
				type = "function",
			},
			getpeer =
			{
				args = "(item: userdata)",
				description = "",
				returns = "(data: table)",
				static = true,
				type = "function",
			},
		},
		description = "class tolua. \n A helper class",
		type = "class",
		index = index()
	},
	CCObject =
	{
		childs =
		{
			id =
			{
				description = "[int][Readonly] Every CCObject is created with its own unique id.",
				type = "value",
			},
			ref =
			{
				description = "[int][Readonly] Any CCObject accessed by lua has its own unique ref id.",
				type = "value",
			},
			count =
			{
				description = "[int][Readonly] Total CCObjects.",
				static = true,
				type = "value",
			},
			luaRefCount =
			{
				description = "[int][Readonly] Total CCObjects used by lua.",
				static = true,
				type = "value",
			},
			callRefCount =
			{
				description = "[int][Readonly] Total lua functions referenced by C++.",
				static = true,
				type = "value",
			},
		},
		description = "class CCObject.",
		type = "class",
		index = index()
	},
	CCSize =
	{
		childs =
		{
			width =
			{
				description = "[float]",
				type = "value",
			},
			height =
			{
				description = "[float]",
				type = "value",
			},
			zero =
			{
				description = "[CCSize][Readonly]",
				static = true,
				type = "value",
			},
		},
		description = "class CCSize.\n args -- ()\n args1 -- (width: float, height: float)",
		type = "class",
		index = index()
	},
	CCRect =
	{
		childs =
		{
			origin =
			{
				description = "[oVec2]",
				typeName = "oVec2",
				type = "value",
			},
			size =
			{
				description = "[CCSize]",
				typeName = "CCSize",
				type = "value",
			},
			left =
			{
				description = "[float][Readonly]",
				type = "value",
			},
			right =
			{
				description = "[float][Readonly]",
				type = "value",
			},
			bottom =
			{
				description = "[float][Readonly]",
				type = "value",
			},
			up =
			{
				description = "[float][Readonly]",
				type = "value",
			},
			midX =
			{
				description = "[float][Readonly]",
				type = "value",
			},
			midY =
			{
				description = "[float][Readonly]",
				type = "value",
			},
			zero =
			{
				description = "[CCRect][Readonly]",
				typeName = "CCRect",
				static = true,
				type = "value",
			},
			containsPoint =
			{
				args = "(point: oVec2)",
				description = "",
				returns = "(result: bool)",
				type = "method",
			},
			intersectsRect =
			{
				args = "(rect: CCRect)",
				description = "",
				returns = "(result: bool)",
				type = "method",
			},
			set =
			{
				args = "(x: float, y: float, width: float, height: float)",
				description = "",
				returns = "()",
				type = "method",
			},
		},
		description = "class CCRect.\n args -- ()\n args1 -- (x: float, y: float, width: float, height: float)\n args2 -- (origin: oVec2, size: CCSize)",
		type = "class",
		index = index()
	},
	ccColor3 =
	{
		childs =
		{
			r =
			{
				description = "[uint8]",
				type = "value",
			},
			g =
			{
				description = "[uint8]",
				type = "value",
			},
			b =
			{
				description = "[uint8]",
				type = "value",
			},
		},
		description = "class ccColor3.\n args -- ()\n args1 -- (rgb: uint)\n args2 -- (r: uint8, g: uint8, b: uint8)",
		type = "class",
		index = index()
	},
	ccColor4 =
	{
		childs =
		{
			r =
			{
				description = "[uint8]",
				type = "value",
			},
			g =
			{
				description = "[uint8]",
				type = "value",
			},
			b =
			{
				description = "[uint8]",
				type = "value",
			},
			a =
			{
				description = "[uint8]",
				type = "value",
			},
		},
		description = "class ccColor4.\n args -- ()\n args1 -- (argb: uint)\n args2 -- (r: uint8, g: uint8, b: uint8, a: uint8)\n args3 -- (c: ccColor3, a: uint8 = 255)",
		type = "class",
		index = index()
	},
	ccBlendFunc =
	{
		childs =
		{
			Src =
			{
				description = "[uint][Const]",
				static = true,
				type = "value",
			},
			OneMinSrc =
			{
				description = "[uint][Const]",
				static = true,
				type = "value",
			},
			Dst =
			{
				description = "[uint][Const]",
				static = true,
				type = "value",
			},
			OneMinDst =
			{
				description = "[uint][Const]",
				static = true,
				type = "value",
			},
			One =
			{
				description = "[uint][Const]",
				static = true,
				type = "value",
			},
			Zero =
			{
				description = "[uint][Const]",
				static = true,
				type = "value",
			},
			src =
			{
				description = "[uint]",
				type = "value",
			},
			dst =
			{
				description = "[uint]",
				type = "value",
			},
		},
		description = "class ccBlendFunc.\n args -- (src: uint, dst: uint)\n -- src and dst: ccBlendFunc.[Src|Dst|OneMinSrc|OneMinDst|One|Zero]",
		type = "class",
		index = index()
	},
	CCNode =
	{
		childs =
		{
			zOrder =
			{
				description = "[int]",
				type = "value",
			},
			angle =
			{
				description = "[float]",
				type = "value",
			},
			scaleX =
			{
				description = "[float]",
				type = "value",
			},
			scaleY =
			{
				description = "[float]",
				type = "value",
			},
			position =
			{
				description = "[oVec2]",
				typeName = "oVec2",
				type = "value",
			},
			positionX =
			{
				description = "[float]",
				type = "value",
			},
			positionY =
			{
				description = "[float]",
				type = "value",
			},
			positionZ =
			{
				description = "[float]",
				type = "value",
			},
			skewX =
			{
				description = "[float]",
				type = "value",
			},
			skewY =
			{
				description = "[float]",
				type = "value",
			},
			visible =
			{
				description = "[bool]",
				type = "value",
			},
			anchor =
			{
				description = "[oVec2]",
				typeName = "oVec2",
				type = "value",
			},
			contentSize =
			{
				description = "[CCSize]",
				typeName = "CCSize",
				type = "value",
			},
			width =
			{
				description = "[float]",
				type = "value",
			},
			height =
			{
				description = "[float]",
				type = "value",
			},
			tag =
			{
				description = "[int]",
				type = "value",
			},
			data =
			{
				description = "[CCObject]",
				typeName = "CCObject",
				type = "value",
			},
			parent =
			{
				description = "[CCNode][Readonly]",
				typeName = "CCNode",
				type = "value",
			},
			transformTarget =
			{
				description = "[CCNode]",
				typeName = "CCNode",
				type = "value",
			},
			scheduler =
			{
				description = "[CCScheduler]",
				typeName = "CCScheduler",
				type = "value",
			},
			opacity =
			{
				description = "[float]",
				type = "value",
			},
			color =
			{
				description = "[ccColor3]",
				typeName = "ccColor3",
				type = "value",
			},
			cascadeOpacity =
			{
				description = "[bool]",
				type = "value",
			},
			cascadeColor =
			{
				description = "[bool]",
				type = "value",
			},
			boundingBox =
			{
				description = "[CCRect][Readonly]",
				typeName = "CCRect",
				type = "value",
			},
			description =
			{
				description = "[string][Readonly]",
				typeName = "string",
				type = "value",
			},
			numberOfRunningActions =
			{
				description = "[int][Readonly]",
				type = "value",
			},
			running =
			{
				description = "[bool][Readonly]",
				type = "value",
			},
			addChild =
			{
				args = "(child: CCNode)",
				description = " args1 -- (child: CCNode, zOrder: int)\n\n args2 -- (child: CCNode, zOrder: int, tag: int)",
				returns = "()",
				type = "method",
			},
			removeChild =
			{
				args = "(child: CCNode, cleanup: bool)",
				description = "",
				returns = "()",
				type = "method",
			},
			removeChildByTag =
			{
				args = "(tag: int, cleanup: bool)",
				description = "",
				returns = "()",
				type = "method",
			},
			removeAllChildrenWithCleanup =
			{
				args = "(cleanup: bool = true)",
				description = "",
				returns = "()",
				type = "method",
			},
			runAction =
			{
				args = "(action: CCAction)",
				description = "",
				returns = "()",
				type = "method",
			},
			stopAllActions =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
			perform =
			{
				args = "(action: CCAction)",
				description = "",
				returns = "()",
				type = "method",
			},
			cleanup =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
			stopAction =
			{
				args = "(action: CCAction)",
				description = "",
				returns = "()",
				type = "method",
			},
			getChildByTag =
			{
				args = "(tag: int)",
				description = "",
				returns = "(child: CCNode)",
				typeName = "CCNode",
				type = "method",
			},
			getChildByIndex =
			{
				args = "(index: int)",
				description = "",
				returns = "(child: CCNode)",
				typeName = "CCNode",
				type = "method",
			},
			getChildren =
			{
				args = "()",
				description = "",
				returns = "(children: table{CCNode})",
				typeName = "CCNode",
				type = "method",
			},
			schedule =
			{
				args = "(handler: function, priority: int = 0)",
				description = " -- handler: function(deltaTime: float)",
				returns = "()",
				type = "method",
			},
			unschedule =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
			convertToNodeSpace =
			{
				args = "(point: oVec2)",
				description = "",
				returns = "(point: oVec2)",
				typeName = "oVec2",
				type = "method",
			},
			convertToWorldSpace =
			{
				args = "(point: oVec2)",
				description = "",
				returns = "(point: oVec2)",
				typeName = "oVec2",
				type = "method",
			},
			convertToGameSpace =
			{
				args = "(point: oVec2)",
				description = "",
				returns = "(point: oVec2)",
				typeName = "oVec2",
				type = "method",
			},
			gslot =
			{
				args = "(name: string, handler: function)",
				description = " -- handler: function{eventArgs: table, event: oEvent}",
				returns = "(slot: oSlot)",
				typeName = "oSlot",
				type = "method",
			},
			slots =
			{
				args = "(name: string, deleteFlag: nil)",
				description = " -- handler: function{eventArgs: ...}",
				returns = "(slotList: oSlotList)",
				typeName = "oSlotList",
				type = "method",
			},
			emit =
			{
				args = "(slotName: string, eventArgs: ...)",
				description = "",
				returns = "()",
				type = "method",
			},
			traverse =
			{
				args = "(handler: function)",
				description = " -- handler: function{child: CCNode}",
				returns = "()",
				type = "method",
			},
			eachChild =
			{
				args = "(handler: function)",
				description = " -- handler: function{child: CCNode}",
				returns = "()",
				type = "method",
			},
		},
		description = "class CCNode(CCObject).\n args -- ()",
		parents = {"CCObject",},
		type = "class",
		index = index()
	},
	CCDrawNode =
	{
		childs =
		{
			drawDot =
			{
				args = "(pos: oVec2, radius: float, color: ccColor4)",
				description = "",
				returns = "()",
				type = "method",
			},
			drawSegment =
			{
				args = "(from: oVec2, to: oVec2, radius: float, color: ccColor4)",
				description = "",
				returns = "()",
				type = "method",
			},
			drawPolygon =
			{
				args = "(verts: table{oVec2}, fillColor: ccColor4, borderWidth: float, borderColor: ccColor4)",
				description = " args1 -- (verts: table{oVec2}, fillColor: ccColor4)",
				returns = "()",
				type = "method",
			},
			clear =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
		},
		description = "class CCDrawNode(CCNode).\n args -- ()",
		parents = {"CCNode",},
		type = "class",
		index = index()
	},
	CCLayer =
	{
		childs =
		{
			touchEnabled =
			{
				description = "[bool]",
				type = "value",
			},
			accelerometerEnabled =
			{
				description = "[bool]",
				type = "value",
			},
			keypadEnabled =
			{
				description = "[bool]",
				type = "value",
			},
			multiTouches =
			{
				description = "[bool]",
				type = "value",
			},
			swallowTouches =
			{
				description = "[bool]",
				type = "value",
			},
			touchPriority =
			{
				description = "[int]",
				type = "value",
			},
		},
		description = "class CCLayer(CCNode).\n args -- ()",
		parents = {"CCNode",},
		type = "class",
		index = index()
	},
	CCLayerColor =
	{
		childs =
		{
			blendFunc =
			{
				description = "[ccBlendFunc]",
				typeName = "ccBlendFunc",
				type = "value",
			},
			resetColor =
			{
				args = "(color1: ccColor4, color2: ccColor4, color3: ccColor4, color4: ccColor4)",
				description = "",
				returns = "()",
				type = "method",
			},
		},
		description = "class CCLayerColor(CCLayer).\n args -- (color: ccColor4, width: float, height: float)",
		parents = {"CCLayer",},
		type = "class",
		index = index()
	},
	CCLayerGradient =
	{
		childs =
		{
			blendFunc =
			{
				description = "[ccBlendFunc]",
				typeName = "ccBlendFunc",
				type = "value",
			},
			startColor =
			{
				description = "[ccColor3]",
				typeName = "ccColor3",
				type = "value",
			},
			endColor =
			{
				description = "[ccColor3]",
				typeName = "ccColor3",
				type = "value",
			},
			startOpacity =
			{
				description = "[float]",
				type = "value",
			},
			endOpacity =
			{
				description = "[float]",
				type = "value",
			},
			vector =
			{
				description = "[oVec2]",
				typeName = "oVec2",
				type = "value",
			},
			compressedInterpolation =
			{
				description = "[bool]",
				type = "value",
			},
		},
		description = "class CCLayerGradient(CCLayer).\n args -- (start: ccColor4, end: ccColor4, v: oVec2)\n args1 -- (start: ccColor4, end: ccColor4)\n args2 -- ()",
		parents = {"CCLayer",},
		type = "class",
		index = index()
	},
	cclog =
	{
		args = "(format: string, any: ...)",
		description = "",
		returns = "()",
		type = "function",
		index = index()
	},
	ccmsg =
	{
		args = "(title: string, any: ...)",
		description = "",
		returns = "()",
		type = "function",
		index = index()
	},
	CCArray =
	{
		childs =
		{
			count =
			{
				description = "[uint][Readonly]",
				type = "value",
			},
			capacity =
			{
				description = "[int][Readonly]",
				type = "value",
			},
			index =
			{
				args = "(object: CCObject)",
				description = "",
				returns = "(index: int)",
				type = "method",
			},
			get =
			{
				args = "(index: uint)",
				description = "",
				typeName = "CCObject",
				returns = "(object: CCObject)",
				type = "method",
			},
			last =
			{
				description = "[CCObject][Readonly]",
				typeName = "CCObject",
				type = "value",
			},
			randomObject =
			{
				description = "[CCObject][Readonly]",
				typeName = "CCObject",
				type = "value",
			},
			equals =
			{
				args = "(other: CCArray)",
				description = "",
				returns = "(result: bool)",
				type = "method",
			},
			contains =
			{
				args = "(object: CCObject)",
				description = "",
				returns = "(result: bool)",
				type = "method",
			},
			add =
			{
				args = "(object: CCObject)",
				description = "",
				returns = "()",
				type = "method",
			},
			addRange =
			{
				args = "(array: CCArray)",
				description = "",
				returns = "()",
				type = "method",
			},
			insert =
			{
				args = "(object: CCObject, index: uint)",
				description = "",
				returns = "()",
				type = "method",
			},
			removeLast =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
			remove =
			{
				args = "(object: CCObject)",
				description = "",
				returns = "()",
				type = "method",
			},
			removeAt =
			{
				args = "(index: uint)",
				description = "",
				returns = "()",
				type = "method",
			},
			removeFrom =
			{
				args = "(other: CCArray)",
				description = "",
				returns = "()",
				type = "method",
			},
			clear =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
			fastRemove =
			{
				args = "(object: CCObject)",
				description = "",
				returns = "()",
				type = "method",
			},
			fastRemoveAt =
			{
				args = "(index: uint)",
				description = "",
				returns = "()",
				type = "method",
			},
			exchange =
			{
				args = "(objectA: CCObject, objectB: CCObject)",
				description = " args1 -- (indexA: uint, indexB: uint)",
				returns = "()",
				type = "method",
			},
			reverse =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
			shrink =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
			set =
			{
				args = "(index: uint, object: CCObject)",
				description = "",
				returns = "()",
				type = "method",
			},
		},
		description = "class CCArray(CCObject).\n args -- ()\n args1 -- (capacity: int)\n args2 -- (other: CCArray)\n args3 -- (objects: table{CCObject})",
		parents = {"CCObject",},
		type = "class",
		index = index()
	},
	CCDictionary =
	{
		childs =
		{
			count =
			{
				description = "[uint][Readonly]",
				type = "value",
			},
			randomObject =
			{
				description = "[CCObject][Readonly]",
				typeName = "CCObject",
				type = "value",
			},
			getKeys =
			{
				args = "()",
				description = "",
				returns = "(keys: table{int|string})",
				type = "method",
			},
			get =
			{
				args = "(key: int|string)",
				description = "",
				returns = "(item: number|bool|string|CCObject)",
				type = "method",
			},
			set =
			{
				args = "(key: int|string, value: number|bool|string|CCObject)",
				description = "",
				returns = "()",
				type = "method",
			},
			clear =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
		},
		description = "class CCDictionary(CCObject).\n args -- ()\n args1 -- (dict: CCDictionary)\n args2 -- (filename: string)",
		parents = {"CCObject",},
		type = "class",
		index = index()
	},
	CCView =
	{
		childs =
		{
			ExactFit =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			NoBorder =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			ShowAll =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			UnKnown =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			visibleSize =
			{
				description = "[CCSize][Readonly]",
				typeName = "CCSize",
				static = true,
				type = "value",
			},
			visibleOrigin =
			{
				description = "[oVec2][Readonly]",
				typeName = "oVec2",
				static = true,
				type = "value",
			},
			scaleX =
			{
				description = "[float][Readonly]",
				static = true,
				type = "value",
			},
			scaleY =
			{
				description = "[float][Readonly]",
				static = true,
				type = "value",
			},
			designResolutionSize =
			{
				description = "[CCSize][Readonly]",
				typeName = "CCSize",
				static = true,
				type = "value",
			},
			frameSize =
			{
				description = "[CCSize]",
				typeName = "CCSize",
				static = true,
				type = "value",
			},
			viewPort =
			{
				description = "[CCRect]",
				typeName = "CCRect",
				static = true,
				type = "value",
			},
			viewName =
			{
				description = "[string]",
				typeName = "string",
				static = true,
				type = "value",
			},
			setDesignResolution =
			{
				args = "(width: float, height: float, resolutionPolicy: int)",
				description = " -- resolutionPolicy: CCView.ExactFit|CCView.NoBorder|CCView.ShowAll|CCView.UnKnown",
				returns = "()",
				static = true,
				type = "method",
			},
			setScissorRect =
			{
				args = "(x: float, y: float, width: float, height: float)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
		},
		description = "class CCView.",
		type = "class",
		index = index()
	},
	CCLanguageType =
	{
		childs =
		{
			English =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Chinese =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			French =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Italian =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			German =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Spanish =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Russian =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Korean =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Japanese =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Hungarian =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Portuguese =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Arabic =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
		},
		description = "enum CCLanguageType.",
		type = "class",
		index = index()
	},
	CCTargetPlatform =
	{
		childs =
		{
			Windows =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			MacOS =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Android =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Iphone =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Ipad =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
		},
		description = "enum CCTargetPlatform.",
		type = "class",
		index = index()
	},
	CCApplication =
	{
		childs =
		{
			EnterBackground =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			EnterForeground =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			LowMemoryWarning =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			eventHandler =
			{
				description = "[function]\n\n -- handler: function(eventType: int)\n\n -- eventType: CCApplication.{EnterBackground|EnterForeground|LowMemoryWarning}",
				static = true,
				type = "value",
			},
			currentLanguage =
			{
				description = "[CCLanguageType]",
				typeName = "CCLanguageType",
				static = true,
				type = "value",
			},
			targetPlatform =
			{
				description = "[CCTargetPlatform]",
				typeName = "CCTargetPlatform",
				static = true,
				type = "value",
			},
		},
		description = "class CCApplication.",
		type = "class",
		index = index()
	},
	CCDirector =
	{
		childs =
		{
			currentScene =
			{
				description = "[CCScene][Readonly]",
				typeName = "CCScene",
				static = true,
				type = "value",
			},
			animationInterval =
			{
				description = "[double][Readonly]",
				static = true,
				type = "value",
			},
			deltaTime =
			{
				description = "[float][Readonly]",
				static = true,
				type = "value",
			},
			paused =
			{
				description = "[bool][Readonly]",
				static = true,
				type = "value",
			},
			winSize =
			{
				description = "[CCSize][Readonly]",
				typeName = "CCSize",
				static = true,
				type = "value",
			},
			visibleSize =
			{
				description = "[CCSize][Readonly]",
				typeName = "CCSize",
				static = true,
				type = "value",
			},
			visibleOrigin =
			{
				description = "[oVec2][Readonly]",
				typeName = "oVec2",
				static = true,
				type = "value",
			},
			sceneStackSize =
			{
				description = "[int][Readonly]",
				static = true,
				type = "value",
			},
			displayStats =
			{
				description = "[bool]",
				static = true,
				type = "value",
			},
			contentScaleFactor =
			{
				description = "[float]",
				static = true,
				type = "value",
			},
			notificationNode =
			{
				description = "[CCNode]",
				typeName = "CCNode",
				static = true,
				type = "value",
			},
			scheduler =
			{
				description = "[CCScheduler]",
				typeName = "CCScheduler",
				static = true,
				type = "value",
			},
			convertToGL =
			{
				args = "(point: oVec2)",
				description = "",
				typeName = "oVec2",
				returns = "(point: oVec2)",
				static = true,
				type = "method",
			},
			convertToUI =
			{
				args = "(point: oVec2)",
				description = "",
				typeName = "oVec2",
				returns = "(point: oVec2)",
				static = true,
				type = "method",
			},
			run =
			{
				args = "(scene: CCScene)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			pause =
			{
				args = "()",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			resume =
			{
				args = "()",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			stop =
			{
				args = "()",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			purge =
			{
				args = "()",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			pushScene =
			{
				args = "(scene: CCScene)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			popScene =
			{
				args = "(scene: CCScene)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			replaceScene =
			{
				args = "(scene: CCScene)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			popToRootScene =
			{
				args = "()",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			setDepthTest =
			{
				args = "(flag: bool)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
		},
		description = "class CCDirector.",
		type = "class",
		index = index()
	},
	CCUserDefault =
	{
		childs =
		{
			filePath =
			{
				description = "[string][Readonly]",
				typeName = "string",
				static = true,
				type = "value",
			},
			get =
			{
				args = "(key: string)",
				description = "",
				returns = "(key: bool|double|string)",
				static = true,
				type = "method",
			},
			set =
			{
				args = "(key: string, value: bool|double|string)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
		},
		description = "class CCUserDefault.",
		type = "class",
		index = index()
	},
	CCTexture2D =
	{
		childs =
		{
			RGB888 =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			RGB565 =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			A8 =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			I8 =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			AI88 =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			RGBA4444 =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			RGB5A1 =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			PVRTC4 =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			PVRTC2 =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Default =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			RGBA8888 =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			size =
			{
				description = "[CCSize][Readonly]",
				typeName = "CCSize",
				type = "value",
			},
			hasMipmaps =
			{
				description = "[bool][Readonly]",
				type = "value",
			},
			antiAlias =
			{
				description = "[bool]",
				type = "value",
			},
			repeatX =
			{
				description = "[bool]",
				type = "value",
			},
			repeatY =
			{
				description = "[bool]",
				type = "value",
			},
			pixelFormat =
			{
				description = "[bool]",
				static = true,
				type = "value",
			},
			generateMipmap =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
		},
		description = "class CCTexture2D(CCObject).",
		type = "class",
		index = index()
	},
	CCTextureCache =
	{
		childs =
		{
			load =
			{
				args = "(filename: string)",
				description = "",
				typeName = "CCTexture2D",
				returns = "(texture: CCTexture2D)",
				type = "method",
			},
			add =
			{
				args = "(renderTarget: CCRenderTarget, name: string)",
				description = "",
				typeName = "CCTexture2D",
				returns = "(texture: CCTexture2D)",
				type = "method",
			},
			reload =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
			removeUnused =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
			unload =
			{
				args = "(texture: CCTexture2D)",
				description = " args1 -- (filename: string)\n\n args2 -- ()",
				returns = "()",
				type = "method",
			},
			dumpInfo =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
		},
		description = "class CCTextureCache.",
		hide = true,
		type = "class",
		index = index()
	},
	CCImage =
	{
		childs =
		{
			JPG =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			PNG =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			isPngAlphaPremultiplied =
			{
				description = "[bool]",
				static = true,
				type = "value",
			},
			width =
			{
				description = "[float][Readonly]",
				type = "value",
			},
			height =
			{
				description = "[float][Readonly]",
				type = "value",
			},
		},
		description = "class CCImage(CCObject).",
		parents = {"CCObject",},
		type = "class",
		index = index()
	},
	CCRenderTarget =
	{
		childs =
		{
			autoDraw =
			{
				description = "[bool]",
				type = "value",
			},
			beginDraw =
			{
				args = "()",
				description = " args1 -- (color: ccColor4)",
				returns = "()",
				type = "method",
			},
			draw =
			{
				args = "(target: CCNode)",
				description = "",
				returns = "()",
				type = "method",
			},
			endDraw =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
			save =
			{
				args = "(filename: string, format: CCImageFormat = CCImage.JPG)",
				description = " -- CCImageFormat: CCImage.JPG|CCImage.PNG",
				returns = "()",
				type = "method",
			},
		},
		parents = {"CCNode",},
		description = "class CCRenderTarget(CCNode).\n args -- (width: int, height: int,  withDepthStencil: bool = false)",
		type = "class",
		index = index()
	},
	CCSprite =
	{
		childs =
		{
			texture =
			{
				description = "[CCTexture2D]",
				typeName = "CCTexture2D",
				type = "value",
			},
			textureRect =
			{
				description = "[CCRect]",
				typeName = "CCRect",
				type = "value",
			},
			blendFunc =
			{
				description = "[ccBlendFunc]",
				typeName = "ccBlendFunc",
				type = "value",
			},
			flipX =
			{
				description = "[bool]",
				type = "value",
			},
			flipY =
			{
				description = "[bool]",
				type = "value",
			},
		},
		parents = {"CCNode",},
		description = "class CCSprite(CCNode).\n args -- ()\n args1 -- (texture: CCTexture2D)\n args2 -- (texture: CCTexture2D, rect: CCRect)\n args3 -- (clipStr: string)",
		type = "class",
		index = index()
	},
	CCSpriteBatchNode =
	{
		childs =
		{
		},
		description = "class CCSpriteBatchNode(CCNode).\n args -- (imageFile: string, capacity: int = 3)\n args1 -- (texture: CCTexture2D, capacity: int = 3)",
		parents = {"CCNode",},
		type = "class",
		index = index()
	},
	CCOrientation =
	{
		childs =
		{
			Left =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Right =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Up =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Down =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
		},
		description = "enum CCOrientation.",
		type = "class",
		index = index()
	},
	CCScene =
	{
		childs =
		{
			rotoZoom =
			{
				args = "(duration: float, nextScene: CCScene)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			jumpZoom =
			{
				args = "(duration: float, nextScene: CCScene)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			move =
			{
				args = "(duration: float, nextScene: CCScene, orientation: CCOrientation)",
				description = " -- orientation: CCOrientation.[Left|Right|Up|Down]",
				returns = "()",
				static = true,
				type = "method",
			},
			slide =
			{
				args = "(duration: float, nextScene: CCScene, orientation: CCOrientation)",
				description = " -- orientation: CCOrientation.[Left|Right|Up|Down]",
				returns = "()",
				static = true,
				type = "method",
			},
			shrinkGrow =
			{
				args = "(duration: float, nextScene: CCScene)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			flip =
			{
				args = "(duration: float, nextScene: CCScene, orientation: CCOrientation)",
				description = " -- orientation: CCOrientation.[Left|Right|Up|Down]",
				returns = "()",
				static = true,
				type = "method",
			},
			flipAngular =
			{
				args = "(duration: float, nextScene: CCScene, rightOver: bool = true)",
				description = " -- orientation: CCOrientation.[Left|Right|Up|Down]",
				returns = "()",
				static = true,
				type = "method",
			},
			zoomFlip =
			{
				args = "(duration: float, nextScene: CCScene, orientation: CCOrientation)",
				description = " -- orientation: CCOrientation.[Left|Right|Up|Down]",
				returns = "()",
				static = true,
				type = "method",
			},
			zoomFlipAngular =
			{
				args = "(duration: float, nextScene: CCScene, rightOver: bool = true)",
				description = " -- orientation: CCOrientation.[Left|Right|Up|Down]",
				returns = "()",
				static = true,
				type = "method",
			},
			fade =
			{
				args = "(duration: float, nextScene: CCScene, color: ccColor3)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			crossFade =
			{
				args = "(duration: float, nextScene: CCScene)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			turnOffTiles =
			{
				args = "(duration: float, nextScene: CCScene)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			splitCols =
			{
				args = "(duration: float, nextScene: CCScene)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			splitRows =
			{
				args = "(duration: float, nextScene: CCScene)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			fadeTiles =
			{
				args = "(duration: float, nextScene: CCScene, orientation: CCOrientation)",
				description = " -- orientation: CCOrientation.[Left|Right|Up|Down]",
				returns = "()",
				static = true,
				type = "method",
			},
			pageTurn =
			{
				args = "(duration: float, nextScene: CCScene, backward: bool = false",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			progressCCW =
			{
				args = "(duration: float, nextScene: CCScene)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			progressCW =
			{
				args = "(duration: float, nextScene: CCScene)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			progressH =
			{
				args = "(duration: float, nextScene: CCScene)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			progressV =
			{
				args = "(duration: float, nextScene: CCScene)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			progressIO =
			{
				args = "(duration: float, nextScene: CCScene)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			progressOI =
			{
				args = "(duration: float, nextScene: CCScene)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
		},
		description = "class CCScene(CCNode).\n args -- ()",
		parents = {"CCNode",},
		type = "class",
		index = index()
	},
	CCScheduler =
	{
		childs =
		{
			timeScale =
			{
				description = "[float]",
				type = "value",
			},
			shedule =
			{
				args = "(handler: function, interval: float = 0)",
				description = " -- handler: function(deltaTime: float)\n\n args1 -- (target: CCScheduler, priority: int = 0)",
				returns = "()",
				type = "method",
			},
			unshedule =
			{
				args = "(handler: function)",
				description = " args1 -- (target: CCScheduler)",
				returns = "()",
				type = "method",
			},
		},
		description = "class CCScheduler(CCObject).\n args -- ()",
		parents = {"CCObject",},
		type = "class",
		index = index()
	},
	CCAction =
	{
		childs =
		{
			done =
			{
				description = "[bool][Readonly]",
				type = "value",
			},
			target =
			{
				description = "[CCNode][Readonly]",
				typeName = "CCNode",
				type = "value",
			},
			tag =
			{
				description = "[int]",
				type = "value",
			},
		},
		description = "class CCAction(CCObject).",
		parents = {"CCObject",},
		hide = true,
		type = "class",
		index = index()
	},
	CCFiniteTimeAction =
	{
		childs =
		{
			duration =
			{
				description = "[float][Readonly]",
				type = "value",
			},
			reverse =
			{
				args = "()",
				description = "",
				typeName = "CCFiniteTimeAction",
				returns = "(action: CCFiniteTimeAction)",
				type = "method",
			},
		},
		description = "class CCFiniteTimeAction(CCAction).",
		parents = {"CCAction",},
		hide = true,
		type = "class",
		index = index()
	},
	CCActionInterval =
	{
		childs =
		{
			elapsed =
			{
				description = "[float][Readonly]",
				type = "value",
			},
			reverse =
			{
				args = "()",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				type = "method",
			},
		},
		description = "class CCActionInterval(CCFiniteTimeAction).",
		parents = {"CCFiniteTimeAction",},
		hide = true,
		type = "class",
		index = index()
	},
	CCSpeed =
	{
		childs =
		{
			rate =
			{
				description = "[float]",
				type = "value",
			},
		},
		description = "class CCSpeed(CCAction).\n args -- (action: CCActionInterval, rate: float)",
		parents = {"CCAction",},
		type = "class",
		index = index()
	},
	CCFollow =
	{
		args = "(target: CCNode, rect: CCRect)",
		description = " args1 -- (target: CCNode)",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCSequence =
	{
		args = "(actions: table{CCFiniteTimeAction})",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCRepeat =
	{
		args = "(action: CCFiniteTimeAction, times: int)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCRepeatForever =
	{
		args = "(action: CCFiniteTimeAction)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCSpawn =
	{
		args = "(actions: table{CCFiniteTimeAction})",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCJumpBy =
	{
		args = "(duration: float, deltaPositon: oVec2, height: float, jumps: int)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCJumpTo =
	{
		args = "(duration: float, positon: oVec2, height: float, jumps: int)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCBezierBy =
	{
		args = "(duration: float, deltaPosition: oVec2, deltaControlA: oVec2, deltaControlB: oVec2)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCBezierTo =
	{
		args = "(duration: float, position: oVec2, controlA: oVec2, controlB: oVec2)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCBlink =
	{
		args = "(duration: float, blinks: int)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCTintTo =
	{
		args = "(duration: float, colorValue: uint)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCTintBy =
	{
		args = "(duration: float, colorValue: uint)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCDelay =
	{
		args = "(duration: float)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCShow =
	{
		args = "()",
		description = "",
		typeName = "CCFiniteTimeAction",
		returns = "(action: CCFiniteTimeAction)",
		type = "function",
		index = index()
	},
	CCHide =
	{
		args = "()",
		description = "",
		typeName = "CCFiniteTimeAction",
		returns = "(action: CCFiniteTimeAction)",
		type = "function",
		index = index()
	},
	CCToggleVisibility =
	{
		args = "()",
		description = "",
		typeName = "CCFiniteTimeAction",
		returns = "(action: CCFiniteTimeAction)",
		type = "function",
		index = index()
	},
	CCFlipX =
	{
		args = "(flip: bool)",
		description = "",
		typeName = "CCFiniteTimeAction",
		returns = "(action: CCFiniteTimeAction)",
		type = "function",
		index = index()
	},
	CCFlipY =
	{
		args = "(flip: bool)",
		description = "",
		typeName = "CCFiniteTimeAction",
		returns = "(action: CCFiniteTimeAction)",
		type = "function",
		index = index()
	},
	CCCall =
	{
		args = "(handler: function)",
		description = " -- handler: function()",
		typeName = "CCFiniteTimeAction",
		returns = "(action: CCFiniteTimeAction)",
		type = "function",
		index = index()
	},
	CCOrbitCamera =
	{
		args = "(duration: float, radius: float, deltaRadius: float, angleZ: float, deltaAngleZ: float, angleX: float, deltaAngleX: float)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCCardinalSplineTo =
	{
		args = "(duration: float, points: table{oVec2}, tensionv: float)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCCardinalSplineBy =
	{
		args = "(duration: float, points: table{oVec2}, tensionv: float)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCCatmullRomTo =
	{
		args = "(duration: float, points: table{oVec2})",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCCatmullRomBy =
	{
		args = "(duration: float, points: table{oVec2})",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCGrid =
	{
		childs =
		{
			stop =
			{
				args = "()",
				description = "",
				typeName = "CCFiniteTimeAction",
				returns = "(action: CCFiniteTimeAction)",
				static = true,
				type = "method"
			},
			reuse =
			{
				args = "(times: int)",
				description = "",
				typeName = "CCFiniteTimeAction",
				returns = "(action: CCFiniteTimeAction)",
				static = true,
				type = "method"
			},
			waves3D =
			{
				args = "(duration: float, gridSize: CCSize, waves: uint, amplitude: float)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method"
			},
			flipX3D =
			{
				args = "(duration: float)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method"
			},
			flipY3D =
			{
				args = "(duration: float)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method"
			},
			lens3D =
			{
				args = "(duration: float, gridSize: CCSize, position: oVec2, radius: float)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method"
			},
			ripple3D =
			{
				args = "(duration: float, gridSize: CCSize, position: oVec2, radius: float, waves: uint, amplitude: float)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method"
			},
			shaky3D =
			{
				args = "(duration: float, gridSize: CCSize, range: int, shakeZ: bool)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method"
			},
			liquid =
			{
				args = "(duration: float, gridSize: CCSize, waves: uint, amplitude: float)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method"
			},
			waves =
			{
				args = "(duration: float, gridSize: CCSize, waves: uint, amplitude: float, horizontal: bool, vertical: bool)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method"
			},
			twirl =
			{
				args = "(duration: float, gridSize: CCSize, position: oVec2, twirls: uint, amplitude: float)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method"
			},
		},
		description = "class CCGrid.",
		type = "class",
		index = index()
	},
	CCTile =
	{
		childs =
		{
			shaky3D =
			{
				args = "(duration: float, gridSize: CCSize, range: int, shakeZ: bool)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			shuffle =
			{
				args = "(duration: float, gridSize: CCSize)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			fadeOut =
			{
				args = "(duration: float, gridSize: CCSize, orientation: CCOrientation)",
				description = " -- orientation: CCOrientation.[Left|Right|Up|Down]",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			turnOff =
			{
				args = "(duration: float, gridSize: CCSize)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			waves3D =
			{
				args = "(duration: float, gridSize: CCSize, waves: uint, amplitude: float)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			jump3D =
			{
				args = "(duration: float, gridSize: CCSize, numberOfJumps: uint, amplitude: float)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			splitRows =
			{
				args = "(duration: float, rows: uint)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			splitCols =
			{
				args = "(duration: float, cols: uint)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
		},
		description = "class CCTile.",
		type = "class",
		index = index()
	},
	CCPageTurn3D =
	{
		args = "(duration: float, gridSize: CCSize)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCProgress =
	{
		args = "(duration: float, percent: float)",
		description = " args -- (duration: float, fromPercentage: float, toPercentage: float)\n Returned action can only be executed by CCProgressTimer.",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	CCMotionStreak =
	{
		childs =
		{
			texture =
			{
				description = "[CCTexture2D]",
				typeName = "CCTexture2D",
				type = "value",
			},
			blendFunc =
			{
				description = "[ccBlendFunc]",
				typeName = "ccBlendFunc",
				type = "value",
			},
			fastMode =
			{
				description = "[bool]",
				type = "value",
			},
			startPosInit =
			{
				description = "[bool]",
				type = "value",
			},
			tintWithColor =
			{
				args = "(color: ccColor3)",
				description = "",
				returns = "()",
				type = "method",
			},
			reset =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},

		},
		parents = {"CCNode",},
		description = "class CCMotionStreak(CCNode).\n args -- (fade: float, minSeg: float, stroke: float, color: ccColor3, imageFile: string)\n args1 -- (fade: float, minSeg: float, stroke: float, color: ccColor3, texture: CCTexture2D)",
		type = "class",
		index = index()
	},
	CCClipNode =
	{
		childs =
		{
			stencil =
			{
				description = "[CCNode]",
				typeName = "CCNode",
				type = "value",
			},
			alphaThreshold =
			{
				description = "[float]",
				type = "value",
			},
			inverted =
			{
				description = "[bool]",
				type = "value",
			},
		},
		description = " args -- (stencil: CCNode)\n args1 -- ()",
		parents = {"CCNode",},
		type = "class",
		index = index()
	},

	CCLabelAtlas =
	{
		childs =
		{
			text =
			{
				description = "[string]",
				typeName = "string",
				type = "value",
			},
			texture =
			{
				description = "[CCTexture2D]",
				typeName = "CCTexture2D",
				type = "value",
			},
		},
		parents = {"CCNode",},
		description = "class CCLabelAtlas(CCNode).\n args -- (text: string, charMapFile: string, itemWidth: int, itemHeight: int, startCharMapa: int)\n args1 -- (text: string, fntFile: string)",
		type = "class",
		index = index()
	},
	CCLabelBMFont =
	{
		childs =
		{
			AutomaticWidth =
			{
				description = "[float][Const]",
				static = true,
				type = "value",
			},
			text =
			{
				description = "[string]",
				typeName = "string",
				type = "value",
			},
			fntFile =
			{
				description = "[string]",
				typeName = "string",
				type = "value",
			},
			setWidth =
			{
				args = "(width: float)",
				description = "",
				returns = "()",
				type = "method",
			},
			setLineBreakWithoutSpace =
			{
				args = "(breakWithoutSpace: bool)",
				description = "",
				returns = "()",
				type = "method",
			},
			purgeCachedData =
			{
				args = "()",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
		},
		description = "class CCLabelBMFont(CCNode).\n args -- (text: string, fntFile: string, width: float = CCLabelBMFont.AutomaticWidth, alignment: CCTextAlign = CCTextAlign.HLeft, imageOffset: oVec2 = oVec2.zero)\n args1 -- ()",
		parents = {"CCNode",},
		type = "class",
		index = index()
	},
	CCTextAlign =
	{
		childs =
		{
			HLeft =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			HCenter =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			HRight =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			VTop =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			VCenter =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			VBottom =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
		},
		description = "enum CCTextAlign.",
		type = "class",
		index = index()
	},
	CCLabelTTF =
	{
		childs =
		{
			text =
			{
				description = "[string]",
				typeName = "string",
				type = "value",
			},
			horizontalAlignment =
			{
				description = "[CCTextAlign]",
				typeName = "CCTextAlign",
				type = "value",
			},
			verticalAlignment =
			{
				description = "[CCTextAlign]",
				typeName = "CCTextAlign",
				type = "value",
			},
			dimensions =
			{
				description = "[CCSize]",
				typeName = "CCSize",
				type = "value",
			},
			fontSize =
			{
				description = "[float]",
				type = "value",
			},
			fontName =
			{
				description = "[string]",
				typeName = "string",
				type = "value",
			},
		},
		description = "class CCLabelTTF(CCSprite).\n args -- (text: string, fontName: string, fontSize: float)\n args1 -- ()",
		parents = {"CCSprite",},
		type = "class",
		index = index()
	},
	CCMenu =
	{
		childs =
		{
			DefaultHandlerPriority =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			enabled =
			{
				description = "[bool]",
				type = "value",
			},
			alignItemsVertically =
			{
				args = "(nil|padding: float)",
				description = "",
				returns = "()",
				type = "method",
			},
			alignItemsHorizontally =
			{
				args = "(nil|padding: float)",
				description = "",
				returns = "()",
				type = "method",
			},
		},
		description = "class CCMenu(CCLayer).\n args -- (swallowTouches: bool = true)",
		parents = {"CCLayer",},
		type = "class",
		index = index()
	},
	CCMenuItem =
	{
		childs =
		{
			hitArea =
			{
				description = "[CCRect][Readonly]",
				typeName = "CCRect",
				type = "value",
			},
			enabled =
			{
				description = "[bool]",
				type = "value",
			},
		},
		description = "class CCMenuItem(CCNode).\n args -- ()",
		parents = {"CCNode",},
		type = "class",
		index = index()
	},
	CCParallaxNode =
	{
		childs =
		{
			addChild =
			{
				args = "(child: CCNode, zOrder: uint, ratio: oVec2, offset: oVec2)",
				description = "",
				returns = "()",
				type = "method",
			},
		},
		description = "class CCParallaxNode(CCNode).\n args -- ()",
		parents = {"CCNode",},
		type = "class",
		index = index()
	},
	CCProgressTimer =
	{
		childs =
		{
			Radial =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Bar =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			midPoint =
			{
				description = "[oVec2]",
				typeName = "oVec2",
				type = "value",
			},
			type =
			{
				description = "[int]\n\nCCProgressTimer.Radial|CCProgressTimer.Bar",
				type = "value",
			},
			percentage =
			{
				description = "[float]",
				type = "value",
			},
			sprite =
			{
				description = "[CCSprite]",
				typeName = "CCSprite",
				type = "value",
			},
			barChangeRate =
			{
				description = "[oVec2]",
				typeName = "oVec2",
				type = "value",
			},
			reverseDirection =
			{
				description = "[bool]",
				type = "value",
			},
		},
		description = "class CCProgressTimer(CCNode).\n args -- (sprite: CCSprite)",
		parents = {"CCNode",},
		type = "class",
		index = index()
	},
	CCTextFieldTTF =
	{
		childs =
		{
			colorPlaceHolder =
			{
				description = "[ccColor3]",
				typeName = "ccColor3",
				type = "value",
			},
			text =
			{
				description = "[string]",
				typeName = "string",
				type = "value",
			},
			placeHolder =
			{
				description = "[string]",
				typeName = "string",
				type = "value",
			},
			attachWithIME =
			{
				args = "()",
				description = "",
				returns = "(result: bool)",
				type = "method",
			},
			detachWithIME =
			{
				args = "()",
				description = "",
				returns = "(result: bool)",
				type = "method",
			},
		},
		description = "class CCTextFieldTTF(CCLabelTTF).\n args -- (placeholder: string, fontName: string, fontSize: float)",
		parents = {"CCLabelTTF",},
		type = "class",
		index = index()
	},
	CCTileMapAtlas =
	{
		childs =
		{
			setTile =
			{
				args = "(tile: ccColor3, position: oVec2)",
				description = "",
				returns = "()",
				type = "method",
			},
			getTile =
			{
				args = "(pos: oVec2)",
				description = "",
				typeName = "ccColor3",
				returns = "(tile: ccColor3)",
				type = "method",
			},
		},
		description = "class CCTileMapAtlas(CCNode).\n args -- (tile: string, mapFile: string, tileWidth: int, tileHeight: int)",
		parents = {"CCNode",},
		type = "class",
		index = index()
	},
	CCTMXLayer =
	{
		childs =
		{
			layerSize =
			{
				description = "[CCSize][Readonly]",
				typeName = "CCSize",
				type = "value",
			},
			mapTileSize =
			{
				description = "[CCSize][Readonly]",
				typeName = "CCSize",
				type = "value",
			},
			layerName =
			{
				description = "[string][Readonly]",
				typeName = "string",
				type = "value",
			},
			getTile =
			{
				args = "(tileCoordinate: oVec2)",
				description = "",
				typeName = "CCSprite",
				returns = "(tile: CCSprite)",
				type = "method",
			},
			getTileGID =
			{
				args = "(tileCoordinate: oVec2)",
				description = "",
				returns = "(gid: uint)",
				type = "method",
			},
			removeTile =
			{
				args = "(tileCoordinate: oVec2)",
				description = "",
				returns = "()",
				type = "method",
			},
			getPosition =
			{
				args = "(tileCoordinate: oVec2)",
				description = "",
				typeName = "oVec2",
				returns = "(position: oVec2)",
				type = "method",
			},
		},
		description = "class CCTMXLayer(CCSpriteBatchNode).",
		parents = {"CCSpriteBatchNode",},
		type = "class",
		hide = true,
		index = index()
	},
	CCTMXTiledMap =
	{
		childs =
		{
			Ortho =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Hex =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			Iso =
			{
				description = "[int][Const]",
				static = true,
				type = "value",
			},
			mapSize =
			{
				description = "[CCSize][Readonly]",
				typeName = "CCSize",
				type = "value",
			},
			tileSize =
			{
				description = "[CCSize][Readonly]",
				typeName = "CCSize",
				type = "value",
			},
			mapOrientation =
			{
				description = "[int][Readonly]\n\nCCTMXTiledMap.Ortho|CCTMXTiledMap.Hex|CCTMXTiledMap.Iso",
				type = "value",
			},
			getLayer =
			{
				args = "(layerName: string)",
				description = "",
				typeName = "CCTMXLayer",
				returns = "(layer: CCTMXLayer)",
				type = "method",
			},
		},
		description = "class CCTMXTiledMap(CCNode).\n args -- (tmxstring: string, resourcePath: string)\n args1 -- (tmxFile: string)",
		parents = {"CCNode",},
		type = "class",
		index = index()
	},
	CCTouch =
	{
		childs =
		{
			location =
			{
				description = "[oVec2][Readonly]",
				typeName = "oVec2",
				type = "value",
			},
			preLocation =
			{
				description = "[oVec2][Readonly]",
				typeName = "oVec2",
				type = "value",
			},
			delta =
			{
				description = "[oVec2][Readonly]",
				typeName = "oVec2",
				type = "value",
			},
			id =
			{
				description = "[int][Readonly]",
				type = "value",
			},
		},
		description = "class CCTouch(CCObject).",
		parents = {"CCObject",},
		type = "class",
		index = index()
	},
	CCKeyboard =
	{
		childs =
		{
			updateKey =
			{
				args = "(key: uint8, isDown: bool)",
				description = "",
				returns = "()",
				static = true,
				type = "method"
			},
			isKeyDown =
			{
				args = "(key: uint8)",
				description = "",
				returns = "(state: bool)",
				static = true,
				type = "method"
			},
			isKeyUp =
			{
				args = "(key: uint8)",
				description = "",
				returns = "(state: bool)",
				static = true,
				type = "method"
			},
			isKeyPressed =
			{
				args = "(key: uint8)",
				description = "",
				returns = "(state: bool)",
				static = true,
				type = "method"
			},
		},
		description = "class CCKeyboard.\n [Only available in Win32]",
		type = "class",
		index = index()
	},
	CCParticle =
	{
		childs =
		{
			autoRemove =
			{
				description = "[bool]",
				type = "value",
			},
			defaultTexture =
			{
				description = "[CCTexture2D][Readonly]",
				typeName = "CCTexture2D",
				static = true,
				type = "value",
			},
			start =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
			stop =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
			fire =
			{
				args = "(totalParticles: number = 250)",
				description = "",
				typeName = "CCParticle",
				returns = "(particle: CCParticle)",
				static = true,
				type = "method",
			},
		},
		description = "class CCParticle(CCNode).\n args -- (particleFile: string)",
		parents = {"CCNode",},
		type = "class",
		index = index()
	},
	CCParticleBatchNode =
	{
		childs = { },
		description = "class CCParticleBatchNode(CCNode).\n args -- (texture: CCTexture2D, capacity: int = 500)\n args1 -- (textureFile: string, capacity: int = 500)",
		parents = {"CCNode",},
		type = "class",
		index = index()
	},
	CCEase =
	{
		childs =
		{
			holdIn =
			{
				args = "(action: CCActionInterval, rate: float)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			holdOut =
			{
				args = "(action: CCActionInterval, rate: float)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			holdInOut =
			{
				args = "(action: CCActionInterval, rate: float)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			exponentialIn =
			{
				args = "(action: CCActionInterval)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			exponentialOut =
			{
				args = "(action: CCActionInterval)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			exponentialInOut =
			{
				args = "(action: CCActionInterval)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			sineIn =
			{
				args = "(action: CCActionInterval)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			sineOut =
			{
				args = "(action: CCActionInterval)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			sineInOut =
			{
				args = "(action: CCActionInterval)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			elasticIn =
			{
				args = "(action: CCActionInterval, period: float = 0.3)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			elasticOut =
			{
				args = "(action: CCActionInterval, period: float = 0.3)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			elasticInOut =
			{
				args = "(action: CCActionInterval, period: float = 0.3)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			bounceIn =
			{
				args = "(action: CCActionInterval)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			bounceOut =
			{
				args = "(action: CCActionInterval)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			bounceInOut =
			{
				args = "(action: CCActionInterval)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			backIn =
			{
				args = "(action: CCActionInterval)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			backOut =
			{
				args = "(action: CCActionInterval)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
			backInOut =
			{
				args = "(action: CCActionInterval)",
				description = "",
				typeName = "CCActionInterval",
				returns = "(action: CCActionInterval)",
				static = true,
				type = "method",
			},
		},
		description = "class oEase.",
		type = "class",
		index = index()
	},

	oVec2 =
	{
		childs =
		{
			x =
			{
				description = "[float]",
				type = "value"
			},
			y =
			{
				description = "[float]",
				type = "value"
			},
			zero =
			{
				description = "[oVec2]",
				typeName = "oVec2",
				static = true,
				type = "value"
			},
			distance =
			{
				args = "(vec: oVec2)",
				description = "",
				returns = "(value: float)",
				type = "method"
			},
			distanceSquared =
			{
				args = "(vec: oVec2)",
				description = "",
				returns = "(value: float)",
				type = "method"
			},
			length =
			{
				description = "[float]",
				type = "value"
			},
			lengthSquared =
			{
				description = "[float]",
				type = "value"
			},
			normalize =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method"
			},
		},
		description = "class oVec2.\n args -- (x:  float = 0, y: float = 0)",
		type = "class",
		index = index()
	},
	oModel =
	{
		childs =
		{
			look =
			{
				description = "[string] Model`s look.",
				type = "value"
			},
			speed =
			{
				description = "[float] Model animation`s play speed,\n\n 1.0 - normal, 2.0 - twice as fast.",
				type = "value"
			},
			loop =
			{
				description = "[bool] Model animation`s loop mode,\n\n true - enable, false - disable.",
				type = "value"
			},
			time =
			{
				description = "[float] Current model animation`s play time,\n\n 0.0 - begin, 1.0 - end.",
				type = "value"
			},
			recovery =
			{
				description = "[float] Current model animation`s recovery time in seconds,\n\n during recovery time, the model reset its pose for\n\n current animation to start.",
				type = "value"
			},
			faceRight =
			{
				description = "[bool] Model character`s face direction,\n\n true - face right, false - face left.",
				type = "value"
			},
			duration =
			{
				description = "[float][Readonly] Current model animation`s duration,\n\n 0.0 - begin, 1.0 - end.",
				type = "value"
			},
			playing =
			{
				description = "[bool][Readonly] Whether current model animation is playing.",
				type = "value"
			},
			paused =
			{
				description = "[bool][Readonly] Whether current model animation is paused.",
				type = "value"
			},
			currentAnimation =
			{
				description = "[string][Readonly] Current model animation`s name.",
				type = "value"
			},
			getKey =
			{
				args = "(key: string)",
				description = "Get model key point by key name.",
				returns = "(key: oVec2)",
				typeName = "oVec2",
				type = "method"
			},
			play =
			{
				args = "(animationName: string)",
				description = "Play model`s animation of certain name.",
				returns = "()",
				type = "method"
			},
			pause =
			{
				args = "()",
				description = "Pause model`s current playing animation.",
				returns = "()",
				type = "method"
			},
			resume =
			{
				args = "(nil|animationName: string)",
				description = "Resume model`s current paused animation or continue to play a new animation.",
				returns = "()",
				type = "method"
			},
			stop =
			{
				args = "()",
				description = "Stop model`s current animation.",
				returns = "()",
				type = "method"
			},
			reset =
			{
				args = "()",
				description = "Stop model`s current animation and reset its look to default.",
				returns = "()",
				type = "method"
			},
			getChildByName =
			{
				args = "(name: string)",
				description = "Get model`s node of certain name.",
				returns = "(node: CCNode)",
				typeName = "CCNode",
				type = "method"
			},
		},
		parents = {"CCNode",},
		description = "class oModel(CCNode).\n args -- (filename: string)",
		type = "class",
		index = index()
	},
	oAction =
	{
		childs =
		{
			reaction =
			{
				description = "[float] When doing this action, the unit will take this extra reaction time\n\n in seconds to respond to the game world changes.",
				type = "value"
			},
			recovery =
			{
				description = "[float]",
				type = "value"
			},
			name =
			{
				description = "[string] Each action type has its unique name.",
				type = "value"
			},
			doing =
			{
				description = "[bool][Readonly] Telling whether the action is doing.",
				type = "value"
			},
			priority =
			{
				description = "[int] Doing higher priority action will always break\n\nthe ongoing lower priority action .",
				type = "value"
			},
			doing =
			{
				description = "[bool][Readonly] Telling whether the action is doing.",
				type = "value"
			},
			owner =
			{
				description = "[oUnit][Readonly] Get the owner of the action.",
				typeName = "oUnit",
				type = "value"
			},
			add =
			{
				args = "(name: string, priority: int, reaction: float, recovery: float, available: function, create: function, stop: function)",
				description = "[Class Method] Add a new action type with its own special id, properties and functions.\n\navailable -- isStarted: bool function(self: oAction)\n\ncreate -- function()\n\nstop -- function(self: oAction)\n\ncreate - return function(self: oAction)",
				returns = "()",
				static = true,
				type = "method"
			},
			clear =
			{
				args = "()",
				description = "[Class Method] Remove all action types.",
				returns = "()",
				static = true,
				type = "method"
			},
		},
		description = "class oAction.",
		type = "class",
		index = index()
	},
	oAttackType =
	{
		childs =
		{
			Melee =
			{
				description = "[int][Const] Flag stands for melee attack.",
				static = true,
				type = "value"
			},
			Range =
			{
				description = "[int][Const] Flag stands for ranged attack.",
				static = true,
				type = "value"
			}
		},
		description = "enum oAttackType.",
		type = "class",
		index = index()
	},
	oAttackTarget =
	{
		childs =
		{
			Single =
			{
				description = "[int][Const] Flag stands for single attack target.",
				static = true,
				type = "value"
			},
			Multi =
			{
				description = "[int][Const] Flag stands for multiple attack targets.",
				static = true,
				type = "value"
			}
		},
		description = "enum oAttackTarget.",
		type = "class",
		index = index()
	},
	oRelation =
	{
		childs =
		{
			Unkown =
			{
				description = "[int][Const] Flag stands for unkown relationship.",
				static = true,
				type = "value"
			},
			Friend =
			{
				description = "[int][Const] Flag stands for allies.",
				static = true,
				type = "value"
			},
			Neutral =
			{
				description = "[int][Const] Flag stands for neutral relationship.",
				static = true,
				type = "value"
			},
			Enemy =
			{
				description = "[int][Const] Flag stands for opponents.",
				static = true,
				type = "value"
			},
			Any =
			{
				description = "[int][Const] Flag stands for any relationship.",
				static = true,
				type = "value"
			}
		},
		description = "enum oRelation.",
		type = "class",
		index = index()
	},
	oTargetAllow =
	{
		childs =
		{
			terrainAllowed =
			{
				description = "[bool] Whether terrain is allowed as target.",
				type = "value"
			},
			allow =
			{
				args = "(relation: oRelation, allow: bool)",
				description = "Set whether units with certain relation is allowed as target.",
				returns = "()",
				type = "method"
			},
			isAllow =
			{
				args = "(relation: oRelation)",
				description = "Get whether units with certain relation is allowed as target.",
				returns = "(allow: bool)",
				type = "method"
			}
		},
		description = "class oTargetAllow.",
		hide = true,
		type = "class",
		index = index()
	},
	oAI =
	{
		childs =
		{
			self =
			{
				description = "[oUnit] Get the current AI unit.",
				typeName = "oUnit",
				static = true,
				type = "value"
			},
			oldValue =
			{
				description = "[float] Get the old, last triggered instinct value.",
				static = true,
				type = "value"
			},
			newValue =
			{
				description = "[float] Get the new, last triggered instinct value.",
				static = true,
				type = "value"
			},
			getUnitsByRelation =
			{
				args = "(relation: oRelation)",
				description = "[Class Method] Get the units of certain relationship within detect range of the AI unit.",
				returns = "(units: CCArray)",
				typeName = "CCArray",
				static = true,
				type = "method"
			},
			getDetectedUnits =
			{
				args = "()",
				description = "[Class Method] Get the units within detect range of the AI unit.",
				returns = "(units: CCArray)",
				typeName = "CCArray",
				static = true,
				type = "method"
			},
			getNearestUnit =
			{
				args = "(relation: oRelation)",
				description = "[Class Method] Get the nearest unit of certain relationship within detect range of the AI unit.",
				returns = "(unit: oUnit)",
				typeName = "oUnit",
				static = true,
				type = "method"
			},
			getNearestUnitDistance =
			{
				args = "(relation: oRelation)",
				description = "[Class Method] Get distance between the nearest unit and the AI unit.",
				returns = "(distance: float)",
				static = true,
				type = "method"
			},
			add =
			{
				args = "(id: int, node: oAINode)",
				description = "[Class Method] Add a new AI type of specified ID to store.",
				returns = "()",
				static = true,
				type = "method"
			},
			clear =
			{
				args = "()",
				description = "[Class Method] Remove all stored AI types.",
				returns = "()",
				static = true,
				type = "method"
			}
		},
		description = "class oAI.",
		type = "class",
		index = index()
	},
	oAINode =
	{
		childs =
		{
			DUMMY =
			{
				args = "()",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
		},
		parents = {"CCObject",},
		description = "class oAINode(CCObject).",
		type = "class",
		hide = true,
		index = index()
	},
	oSel =
	{
		args = "(nodes: CCArray)",
		description = "Create a selector node.",
		returns = "(node: oAINode)",
		typeName = "oAINode",
		type = "function",
		index = index()
	},
	oSeq =
	{
		args = "(nodes: CCArray)",
		description = "Create a sequence node.",
		returns = "(node: oAINode)",
		typeName = "oAINode",
		type = "function",
		index = index()
	},
	oParSel =
	{
		args = "(nodes: CCArray)",
		description = "Create a parallel selector node.",
		returns = "(node: oAINode)",
		typeName = "oAINode",
		type = "function",
		index = index()
	},
	oParSeq =
	{
		args = "(nodes: CCArray)",
		description = "Create a parallel sequence node.",
		returns = "(node: oAINode)",
		typeName = "oAINode",
		type = "function",
		index = index()
	},
	oCon =
	{
		args = "(handler: bool function())",
		description = "Create a condition node.",
		returns = "(node: oAINode)",
		typeName = "oAINode",
		type = "function",
		index = index()
	},
	oAct =
	{
		args = "(actionName: string)",
		description = "Create an action node.",
		returns = "(node: oAINode)",
		typeName = "oAINode",
		type = "function",
		index = index()
	},
	oInstinct =
	{
		childs =
		{
			add =
			{
				args = "(id: int, propName: string, node: oAINode)",
				description = "[Class Method] Add a new instinct type triggered by specified property, executing new AI node.",
				returns = "()",
				static = true,
				type = "method"
			},
			clear =
			{
				args = "()",
				description = "[Class Method] Remove all stored instinct types.",
				returns = "()",
				static = true,
				type = "method"
			}
		},
		description = "class oInstinct.",
		type = "class",
		index = index()
	},
	oFrameAction =
	{
		args = "(filename: string)",
		description = "",
		typeName = "CCFiniteTimeAction",
		returns = "(action: CCFiniteTimeAction)",
		type = "function",
		index = index()
	},
	oSound =
	{
		childs =
		{
			load =
			{
				args = "(filename: string)",
				description = "[Class Method] Preload sound data into memory from source file.",
				returns = "()",
				static = true,
				type = "method"
			},
			unload =
			{
				args = "(filename: string)",
				description = "[Class Method]",
				returns = "()",
				static = true,
				type = "method"
			},
			play =
			{
				args = "(filename: string, nil|loop: bool)",
				description = "[Class Method] Preload and play a sound effect and then returns a sound id.",
				returns = "(soundId: int)",
				static = true,
				type = "method"
			},
			stop =
			{
				args = "(nil|soundId: int)",
				description = "[Class Method] Stop all playing sounds or stop a sound by its id.",
				returns = "()",
				static = true,
				type = "method"
			},
			volume =
			{
				description = "[float] All playing sounds` volume, value from 0.0f to 1.0f.",
				static = true,
				type = "value"
			},
			useCache =
			{
				description = "[bool]",
				static = true,
				type = "value"
			},
		},
		description = "class oSound.",
		type = "class",
		index = index()
	},
	oMusic =
	{
		childs =
		{
			preload =
			{
				args = "(filename: string)",
				description = "[Class Method] Preload music data into memory from source file.",
				returns = "()",
				static = true,
				type = "method"
			},
			play =
			{
				args = "(filename: string, nil|loop: bool)",
				description = "[Class Method] Preload and play BGM.",
				returns = "()",
				static = true,
				type = "method"
			},
			pause =
			{
				args = "()",
				description = "[Class Method] Pause BGM.",
				returns = "()",
				static = true,
				type = "method"
			},
			resume =
			{
				args = "()",
				description = "[Class Method] Resume BGM.",
				returns = "()",
				static = true,
				type = "method"
			},
			stop =
			{
				args = "()",
				description = "[Class Method] Stop BGM.",
				returns = "()",
				static = true,
				type = "method"
			},
			volume =
			{
				description = "[float] BGM volume, value from 0.0f to 1.0f.",
				static = true,
				type = "value"
			},
		},
		description = "class oMusic.",
		type = "class",
		index = index()
	},
	oWorld =
	{
		childs =
		{
			gravity =
			{
				description = "[oVec2]",
				typeName = "oVec2",
				type = "value",
			},
			query =
			{
				args = "(rect: CCRect, handler: function)",
				description = " -- handler: bool function(body: oBody)\n return true to stop query.",
				returns = "()",
				type = "method",
			},
			cast =
			{
				args = "(start: oVec2, stop: oVec2, closest: bool, handler: function)",
				description = " -- handler: bool function(body: oBody, point: oVec2, normal: oVec2)\n return true to stop query.",
				returns = "()",
				type = "method",
			},
			setIterations =
			{
				args = "(velocityIter: int, positionIter: int)",
				description = "",
				returns = "()",
				type = "method",
			},
			setShouldContact =
			{
				args = "(groupA: int, groupB: int, contact: bool)",
				description = "",
				returns = "()",
				type = "method",
			},
			getShouldContact =
			{
				args = "(groupA: int, groupB: int)",
				description = "",
				returns = "(contact: bool)",
				type = "method",
			},
			b2Factor =
			{
				description = "[float]",
				static = true,
				type = "value",
			},
			showDebug =
			{
				description = "[bool]",
				type = "value",
			},
		},
		description = "class oWorld(CCNode).\n args -- ()",
		parents = {"CCNode",},
		type = "class",
		index = index()
	},
	oBody =
	{
		childs =
		{
			world =
			{
				description = "[oWorld]",
				typeName = "oWorld",
				type = "value"
			},
			bodyDef =
			{
				description = "[oBodyDef]",
				typeName = "oBodyDef",
				type = "value"
			},
			mass =
			{
				description = "[float][Readonly]",
				type = "value"
			},
			velocityX =
			{
				description = "[float]",
				type = "value"
			},
			velocityY =
			{
				description = "[float]",
				type = "value"
			},
			velocity =
			{
				description = "[oVec2]",
				typeName = "oVec2",
				type = "value"
			},
			angularRate =
			{
				description = "[float] Degrees per second",
				type = "value"
			},
			linearDamping =
			{
				description = "[float]",
				type = "value"
			},
			angularDamping =
			{
				description = "[float]",
				type = "value"
			},
			group =
			{
				description = "[int]\n\n Value Range:\n\n (0) - Hide\n\n (1-12) - Player\n\n (13) - Sense player\n\n (14) - Terrain\n\n (15) - Contact all",
				type = "value"
			},
			owner =
			{
				description = "[CCObject]",
				typeName = "CCObject",
				type = "value"
			},
			applyLinearImpulse =
			{
				args = "(impulse: oVec2, pos: oVec2)",
				description = "",
				returns = "()",
				type = "method"
			},
			applyAngularImpulse =
			{
				args = "(impulse: float)",
				description = "",
				returns = "()",
				type = "method"
			},
			getSensorByTag =
			{
				args = "(tag: int)",
				description = "",
				returns = "(sensor: oSensor)",
				typeName = "oSensor",
				type = "method"
			},
			removeSensorByTag =
			{
				args = "(tag: int)",
				description = "",
				returns = "(removed: bool)",
				type = "method"
			},
			removeSensor =
			{
				args = "(sensor: oSensor)",
				description = "",
				returns = "(removed: bool)",
				type = "method"
			},
			attach =
			{
				args = "(fixtureDef: oFixtureDef)",
				description = "",
				returns = "()",
				type = "method"
			},
			attachSensor =
			{
				args = "(tag: int, fixtureDef: oFixtureDef)",
				description = "",
				returns = "(sensor: oSensor)",
				typeName = "oSensor",
				type = "method"
			},
			destroy =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method"
			},
		},
		parents = {"CCNode",},
		description = "class oBody(CCNode).\n args -- (bodyDef: oBodyDef, world: oWorld, pos: oVec2 = oVec2.zero, rot: float = 0)",
		type = "class",
		index = index()
	},
	oFixtureDef =
	{
		childs =
		{
			DUMMY =
			{
				args = "()",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
		},
		description = "class oFixtureDef.",
		type = "class",
		hide = true,
		index = index()
	},
	oBodyDef =
	{
		childs =
		{
			Static =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			Dynamic =
				{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			Kinematic =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			type =
			{
				description = "[int] The body type should be set with [oBodyDef.Static], [oBodyDef.Dynamic] or [oBodyDef.Kinematic].",
				type = "value"
			},
			linearDamping =
			{
				description = "[float]",
				type = "value"
			},
			angularDamping =
			{
				description = "[float]",
				type = "value"
			},
			fixedRotation =
			{
				description = "[bool]",
				type = "value"
			},
			isBullet =
			{
				description = "[bool]",
				type = "value"
			},
			gravityScale =
			{
				description = "[float]",
				type = "value"
			},
			position =
			{
				description = "[oVec2]",
				typeName = "oVec2",
				type = "value"
			},
			angle =
			{
				description = "[float]",
				type = "value"
			},
			polygon =
			{
				args = "(center: oVec2, width: float, height: float, angle: float, density: float, friction: float, restitution: float)",
				description = "[Class Method]\n\n args1 -- (width: float, height: float, density: float, friction: float, restitution: float)\n\n args2 -- (vertices: table{oVec2}, density: float, friction: float, restitution: float)",
				returns = "(fixtureDef: oFixtureDef)",
				typeName = "oFixtureDef",
				static = true,
				type = "method"
			},
			loop =
			{
				args = "(vertices: table{oVec2}, friction: float, restitution: float)",
				description = "[Class Method]",
				returns = "(fixtureDef: oFixtureDef)",
				typeName = "oFixtureDef",
				static = true,
				type = "method"
			},
			circle =
			{
				args = "(center: oVec2, radius: float, density: float, friction: float, restitution: float)",
				description = "[Class Method]\n\n args1 -- (radius: float, density: float, friction: float, restitution: float)",
				returns = "(fixtureDef: oFixtureDef)",
				typeName = "oFixtureDef",
				static = true,
				type = "method"
			},
			chain =
			{
				args = "(vertices: table{oVec2}, friction: float, restitution: float)",
				description = "[Class Method]",
				returns = "(fixtureDef: oFixtureDef)",
				typeName = "oFixtureDef",
				static = true,
				type = "method"
			},
			attachPolygon =
			{
				args = "(center: oVec2, width: float, height: float, angle: float, density: float, friction: float, restitution: float)",
				description = " args1 -- (width: float, height: float, density: float, friction: float, restitution: float)\n\n args2 -- (vertices: table{oVec2}, density: float, friction: float, restitution: float)",
				returns = "()",
				type = "method"
			},
			attachLoop =
			{
				args = "(vertices: table{oVec2}, friction: float, restitution: float)",
				description = "",
				returns = "()",
				type = "method"
			},
			attachCircle =
			{
				args = "(center: oVec2, radius: float, density: float, friction: float, restitution: float)",
				description = " args1 -- (radius: float, density: float, friction: float, restitution: float)",
				returns = "()",
				type = "method"
			},
			attachChain =
			{
				args = "(vertices: table{oVec2}, friction: float, restitution: float)",
				description = "",
				returns = "()",
				type = "method"
			},
			attachPolygonSensor =
			{
				args = "(tag: int, width: float, height: float)",
				description = " args1 -- (tag: float, width: float, height: float, center: oVec2, angle: float)\n\n args2 -- (tag: float, vertices: table{oVec2})",
				returns = "()",
				type = "method"
			},
			attachCircleSensor =
			{
				args = "(tag: int, center: oVec2, radius: float)",
				description = "args1 -- (tag: float, radius: float))",
				returns = "()",
				type = "method"
			},
		},
		parents = {"CCObject",},
		description = "class oBodyDef(CCObject).\n args -- ()",
		type = "class",
		index = index()
	},
	oBullet =
	{
		childs =
		{
			targetAllow =
			{
				description = "[oTargetAllow][Readonly]",
				type = "value"
			},
			faceRight =
			{
				description = "[bool][Readonly]",
				type = "value"
			},
			owner =
			{
				description = "[oBody][Readonly]",
				typeName = "oBody",
				type = "value"
			},
			detectSensor =
			{
				description = "[oSensor][Readonly]",
				typeName = "oSensor",
				type = "value"
			},
			bulletDef =
			{
				description = "[oBulletDef][Readonly]",
				typeName = "oBulletDef",
				type = "value"
			},
			face =
			{
				description = "[CCNode]",
				typeName = "CCNode",
				type = "value"
			},
			destroy =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method"
			},
		},
		parents = {"oBody",},
		description = "class oBullet(oBody).\n args -- (bulletDef: oBulletDef, owner: oUnit)",
		type = "class",
		index = index()
	},
	oBulletDef =
	{
		childs =
		{
			tag =
			{
				description = "[int]",
				type = "value"
			},
			endEffect =
			{
				description = "[string]",
				type = "value"
			},
			lifeTime =
			{
				description = "[float] Living time in seconds",
				type = "value"
			},
			damageRadius =
			{
				description = "[float] Damage area is a circle area, the radius is in pixels",
				type = "value"
			},
			highSpeedFix =
			{
				description = "[bool] When the defined bullet is going to run in wery high speed, set this flag with true to get accurate simulation",
				type = "value"
			},
			gravityScale =
			{
				description = "[float]",
				type = "value"
			},
			face =
			{
				description = "[oFace]",
				typeName = "oFace",
				type = "value"
			},
			bodyDef =
			{
				description = "[oBodyDef][Readonly]",
				typeName = "oBodyDef",
				type = "value"
			},
			velocity =
			{
				description = "[oVec2][Readonly] Bullet start velocity",
				typeName = "oVec2",
				type = "value"
			},
			SensorTag =
			{
				description = "[int] Tag of bullet`s detect sensor.",
				type = "value"
			},
			setAsCircle =
			{
				args = "(radius: float)",
				description = "Set bullet shape as circle",
				returns = "()",
				type = "method"
			},
			setVelocity =
			{
				args = "(angle: float, speed: float)",
				description = "Set bullet start velocity",
				returns = "()",
				type = "method"
			},
		},
		parents = {"CCObject",},
		description = "class oBulletDef(CCObject). \n args -- ()",
		type = "class",
		index = index()
	},
	oCamera =
	{
		childs =
		{
			boudary =
			{
				description = "[CCRect]",
				typeName = "CCRect",
				type = "value"
			},
			view =
			{
				description = "[CCSize]",
				typeName = "CCSize",
				type = "value"
			},
			followRatio =
			{
				description = "[oVec2]",
				typeName = "oVec2",
				type = "value"
			},
			follow =
			{
				args = "(target: CCNode)",
				description = "",
				returns = "()",
				type = "method"
			},
		},
		parents = {"CCNode",},
		description = "class oCamera(CCNode).",
		type = "class",
		hide = true,
		index = index()
	},
	oContent =
	{
		childs =
		{
			useGameFile =
			{
				description = "[bool]",
				static = true,
				type = "value"
			},
			setGameFile =
			{
				args = "(filename: string)",
				description = "[Class Method]",
				returns = "()",
				static = true,
				type = "method"
			},
			setPassword =
			{
				args = "(password: string)",
				description = "[Class Method]",
				returns = "()",
				static = true,
				type = "method"
			},
			saveToFile =
			{
				args = "(filename: string, content: string)",
				description = "[Class Method]",
				returns = "()",
				static = true,
				type = "method"
			},
			copyAsync =
			{
				args = "(src: string, dst: string)",
				description = "[Class Method]",
				returns = "()",
				static = true,
				type = "method"
			},
			exist =
			{
				args = "(path: string)",
				description = "[Class Method]",
				returns = "(exist: bool)",
				static = true,
				type = "method"
			},
			getEntries =
			{
				args = "(path: string, isFolder: bool)",
				description = "[Class Method]",
				returns = "()",
				static = true,
				type = "method"
			},
			mkdir =
			{
				args = "(path: string)",
				description = "[Class Method]",
				returns = "(success: bool)",
				static = true,
				type = "method"
			},
			remove =
			{
				args = "(path: string)",
				description = "[Class Method]",
				returns = "(success: bool)",
				static = true,
				type = "method"
			},
			writablePath =
			{
				description = "[string][Readonly]",
				typeName = "string",
				static = true,
				type = "value",
			},
			popupNotify =
			{
				description = "[bool]",
				static = true,
				type = "value",
			},
			getFullPath =
			{
				args = "(filename: string)",
				description = "",
				typeName = "string",
				returns = "(fullname: string)",
				static = true,
				type = "method",
			},
			getRelativeFullPath =
			{
				args = "(filename: string, relativeFile: string)",
				description = "",
				typeName = "string",
				returns = "(relativeName: string)",
				static = true,
				type = "method",
			},
			loadFileLookupInfo =
			{
				args = "(filename: string)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			addSearchPath =
			{
				args = "(path: string)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			removeSearchPath =
			{
				args = "(path: string)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			setSearchPaths =
			{
				args = "(paths: table{string})",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			setSearchResolutionsOrder =
			{
				args = "(orders: table{string})",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			purgeCachedEntries =
			{
				args = "()",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
		},
		description = "class oContent.",
		type = "class",
		index = index()
	},
	oData =
	{
		childs =
		{
			GroupHide =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			GroupDetectPlayer =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			GroupDetect =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			GroupTerrain =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			setRelation =
			{
				args = "(groupA: int,  groupB: int, relation: oRelation)",
				description = "[Class Method]",
				returns = "()",
				static = true,
				type = "method"
			},
			getRelation =
			{
				args = "(groupA: int, groupB: int)",
				description = "[Class Method]\n\n args1 -- (unitA: oUnit, unitB: oUnit)",
				returns = "(relation: oRelation)",
				typeName = "oRelation",
				static = true,
				type = "method"
			},
			setDamageFactor =
			{
				args = "(damageType: uint16, defenceType: uint16, bounus: float)",
				description = "[Class Method]",
				returns = "()",
				static = true,
				type = "method"
			},
			getDamageFactor =
			{
				args = "(damageType: uint16, defenceType: uint16)",
				description = "[Class Method]",
				returns = "(bounus: float)",
				static = true,
				type = "method"
			},
			isPlayer =
			{
				args = "(body: oBody)",
				description = "[Class Method]",
				returns = "(isPlayer: bool)",
				static = true,
				type = "method"
			},
			isTerrain =
			{
				args = "(body: oBody)",
				description = "[Class Method]",
				returns = "(isTerrain: bool)",
				static = true,
				type = "method"
			},
		},
		description = "class oData.",
		type = "class",
		index = index()
	},
	oEase =
	{
		childs =
		{
			Linear =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InQuad =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			OutQuad =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InOutQuad =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InCubic =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			OutCubic =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InOutCubic =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InQuart =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			OutQuart =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InOutQuart =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InQuint =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			OutQuint =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InOutQuint =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InSine =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			OutSine =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InOutSine =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InExpo =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			OutExpo =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InOutExpo =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InCirc =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			OutCirc =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InOutCirc =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InElastic =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			OutElastic =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InOutElastic =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InBack =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			OutBack =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InOutBack =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InBounce =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			OutBounce =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			InOutBounce =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			func =
			{
				args = "(easeId: int, time: float, begin: float, end: float)",
				description = " - time: [0.0 - 1.0]\n\n - easeId: oEase.[Linear|InQuad|...]",
				returns = "(value: float)",
				static = true,
				type = "method"
			},		
		},
		description = "class oEase.",
		type = "class",
		index = index()
	},
	oEffect =
	{
		childs =
		{
			playing =
			{
				description = "[bool][Readonly]",
				type = "value"
			},
			start =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method"
			},
			stop =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method"
			},
			setOffset =
			{
				args = "(pos: oVec2)",
				description = "",
				returns = "(self: oEffect)",
				typeName = "oEffect",
				type = "method"
			},
			attachTo =
			{
				args = "(parent: CCNode, nil|zOrder: int)",
				description = "",
				returns = "(self: oEffect)",
				typeName = "oEffect",
				type = "method"
			},
			autoRemove =
			{
				args = "()",
				description = "",
				returns = "(self: oEffect)",
				typeName = "oEffect",
				type = "method"
			},
			update =
			{
				args = "(particleEffect: oEffect, content: table)",
				description = "Update an particle effect with a Lua table containing its attributes, used for editor.",
				returns = "(self: oEffect)",
				typeName = "oEffect",
				static = true,
				type = "method"
			},
		},
		parents = {"CCObject",},
		description = "class oEffect(CCObject).\n -- (name: string)",
		type = "class",
		index = index()
	},
	oFace =
	{
		childs =
		{
			addChild =
			{
				args = "(face: oFace)",
				description = "",
				returns = "()",
				type = "method"
			},
			removeChild =
			{
				args = "(face: oFace)",
				description = "",
				returns = "(success: bool)",
				type = "method"
			},
			toNode =
			{
				args = "()",
				description = "",
				returns = "(node: CCNode)",
				typeName = "CCNode",
				type = "method"
			},
		},
		parents = {"CCObject",},
		description = "class oFace(CCObject).\n args -- (faceStr: string, point: oVec2)",
		type = "class",
		index = index()
	},
	oLine =
	{
		childs =
		{
			set =
			{
				args = "(verts: table{oVec2})",
				description = "",
				returns = "()",
				type = "method"
			},
		},
		parents = {"CCNode",},
		description = "class oLine(CCNode).\n args -- (verts: table{oVec2}, color: ccColor4)\n args1 -- ()",
		type = "class",
		index = index()
	},
	oPos =
	{
		args = "(duration: float, posX: float, posY: float, easeId: uint8 = oEase.Linear)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	oScale =
	{
		args = "(duration: float, scaleX: float, scaleY: float, easeId: uint8 = oEase.Linear)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	oRotate =
	{
		args = "(duration: float, endRotate: float, easeId: uint8 = oEase.Linear)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	oOpacity =
	{
		args = "(duration: float, endOpacity: float, easeId: uint8 = oEase.Linear)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	oSkew =
	{
		args = "(duration: float, skewX: float, skewY: float, easeId: uint8 = oEase.Linear)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	oRoll =
	{
		args = "(duration: float, roll: float, easeId: uint8 = oEase.Linear)",
		description = "",
		typeName = "CCActionInterval",
		returns = "(action: CCActionInterval)",
		type = "function",
		index = index()
	},
	oNode3D =
	{
		childs =
		{
			angleX =
			{
				description = "[float]",
				type = "value"
			},
			angleY =
			{
				description = "[float]",
				type = "value"
			},
		},
		parents = {"CCNode",},
		description = "class oNode3D(CCNode).\n args -- ()",
		type = "class",
		index = index()
	},
	oClipCache =
	{
		childs =
		{
			load =
			{
				args = "(filename: string)",
				description = "[Class Method] Load new clip data item from .clip file.",
				returns = "(loaded: bool)",
				type = "method"
			},
			update =
			{
				args = "(name: string, content: string)",
				description = "",
				returns = "(loaded: bool)",
				type = "method"
			},
			unload =
			{
				args = "(nil|filename: string)",
				description = "[Class Method] Unload clip data item from .clip file.\n\n false - No such item in cache\n\n true - Item unloaded\n\nOr unload all clip data when no parameters passed.\n\n false - No data in cache\n\n true - Data unloaded",
				returns = "(loaded: bool)",
				type = "method"
			},
			removeUnused =
			{
				args = "()",
				description = "[Class Method]",
				returns = "()",
				type = "method"
			},
			getNames =
			{
				args = "(filename: string)",
				description = "",
				returns = "(names: table{string})",
				type = "method"
			},
			getTextureFile =
			{
				args = "(filename: string)",
				description = "",
				returns = "(textureFile: string)",
				type = "method"
			}
		},
		description = "class oClipCache.",
		hide = true,
		type = "class",
		index = index()
	},
	oAnimationCache =
	{
		childs =
		{
			load =
			{
				args = "(filename: string)",
				description = "[Class Method] Load a new frame action data item from .frame file.",
				returns = "(loaded: bool)",
				type = "method"
			},
			update =
			{
				args = "(name: string, content: string)",
				description = "",
				returns = "(loaded: bool)",
				type = "method"
			},
			unload =
			{
				args = "(nil|filename: string)",
				description = "[Class Method] Unload a frame action data item from .frame file.\n\n false - No such item in cache\n\n true - Item unloaded\n\nOr unload all frame action data when no parameters passed.\n\n false - No data in cache\n\n true - Data unloaded",
				returns = "(loaded: bool)",
				type = "method"
			},
			removeUnused =
			{
				args = "()",
				description = "[Class Method]",
				returns = "()",
				type = "method"
			},
		},
		description = "class oAnimationCache.",
		hide = true,
		type = "class",
		index = index()
	},
	oParticleCache =
	{
		childs =
		{
			load =
			{
				args = "(filename: string)",
				description = "[Class Method] Load new particle data item from .plist file.",
				returns = "(loaded: bool)",
				type = "method"
			},
			update =
			{
				args = "(name: string, content: string)",
				description = "",
				returns = "(loaded: bool)",
				type = "method"
			},
			unload =
			{
				args = "(nil|filename: string)",
				description = "[Class Method] Unload particle data item from .plist file.\n\n false - No such item in cache\n\n true - Item unloaded\n\nOr unload all particle data when no parameters passed.\n\n false - No data in cache\n\n true - Data unloaded",
				returns = "(loaded: bool)",
				type = "method"
			},
			removeUnused =
			{
				args = "()",
				description = "[Class Method]",
				returns = "()",
				type = "method"
			},
		},
		description = "class oParticleCache.",
		hide = true,
		type = "class",
		index = index()
	},
	oEffectCache =
	{
		childs =
		{
			load =
			{
				args = "(filename: string)",
				description = "[Class Method] Load new data of effects item from .effect file.",
				returns = "(loaded: bool)",
				type = "method"
			},
			update =
			{
				args = "(content: string)",
				description = "",
				returns = "(loaded: bool)",
				type = "method"
			},
			unload =
			{
				args = "(nil|filename: string)",
				description = "[Class Method] Unload data of effects.\n\n false - No data in cache\n\n true - Data unloaded",
				returns = "(loaded: bool)",
				type = "method"
			},
		},
		description = "class oEffectCache.",
		hide = true,
		type = "class",
		index = index()
	},
	oModelCache =
	{
		childs =
		{
			load =
			{
				args = "(filename: string)",
				description = "[Class Method] Load new model data item from .model file.",
				returns = "(loaded: bool)",
				type = "method"
			},
			update =
			{
				args = "(name: string, content: string)",
				description = "",
				returns = "(loaded: bool)",
				type = "method"
			},
			unload =
			{
				args = "(nil|filename: string)",
				description = "[Class Method] Unload model data item from .model file.\n\n false - No such item in cache\n\n true - Item unloaded\n\nOr unload all model data when no parameters passed.\n\n false - No data in cache\n\n true - Data unloaded",
				returns = "(loaded: bool)",
				type = "method"
			},
			removeUnused =
			{
				args = "()",
				description = "[Class Method]",
				returns = "()",
				type = "method"
			},
			getData =
			{
				args = "(filename: string)",
				description = "[Class Method] Get model data as Lua table from .model file, usable for editor.",
				returns = "(content: table)",
				type = "method"
			},
			loadData =
			{
				args = "(itemName: string, content: table)",
				description = "Load a Lua table filled with model data, and convert it to a modelDef item with itemName, usable for editor",
				typeName = "oModelDef",
				returns = "(modelDef: oModelDef)",
				type = "method"
			},
			save =
			{
				args = "(itemName: string, targetName: string)",
				description = "",
				returns = "()",
				type = "method"
			},
			getClipFile =
			{
				args = "(filename: string)",
				description = "",
				returns = "(clipFile: string)",
				type = "method"
			}
		},
		description = "class oModelCache.",
		hide = true,
		type = "class",
		index = index()
	},
	oPool =
	{
		childs =
		{
			collect =
			{
				args = "()",
				description = "",
				returns = "(collectedMemory: int)",
				type = "method",
			},
			size =
			{
				description = "[int][Readonly]",
				type = "value",
			},
		},
		description = "",
		type = "class",
		hide = true,
		index = index()
	},
	oCache =
	{
		childs =
		{
			Effect =
			{
				description = "[oEffectCache]",
				typeName = "oEffectCache",
				static = true,
				type = "value"
			},
			Animation =
			{
				description = "[oAnimationCache]",
				typeName = "oAnimationCache",
				static = true,
				type = "value"
			},
			Particle =
			{
				description = "[oParticleCache]",
				typeName = "oParticleCache",
				static = true,
				type = "value"
			},
			Model =
			{
				description = "[oModelCache]",
				typeName = "oModelCache",
				static = true,
				type = "value"
			},
			Clip =
			{
				description = "[oClipCache]",
				typeName = "oClipCache",
				static = true,
				type = "value"
			},
			Texture =
			{
				description = "[CCTextureCache]",
				typeName = "CCTextureCache",
				static = true,
				type = "value"
			},
			Pool =
			{
				description = "[oPool]",
				typeName = "oPool",
				static = true,
				type = "value"
			},
			clear =
			{
				args = "()",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			removeUnused =
			{
				args = "()",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			loadAsync =
			{
				args = "(filename: string|filenames: table{string}, callback: function)",
				description = " -- callback: function(filename)",
				typeName = "",
				returns = "()",
				static = true,
				type = "method",
			},
			swapAsync =
			{
				args = "(oldResourses: table{string}, newResourses: table{string}, callback: function)",
				description = " -- callback: function(filename)",
				typeName = "",
				returns = "()",
				static = true,
				type = "method",
			},
		},
		description = "class oCache.",
		type = "class",
		index = index()
	},
	oLayer =
	{
		childs =
		{
		},
		description = "class oLayer(oNode3D).",
		parents = {"oNode3D",},
		hide = true,
		type = "class",
		index = index()
	},
	oPlatformWorld =
	{
		childs =
		{
			camera =
			{
				description = "[oCamera][Readonly]",
				typeName = "oCamera",
				type = "value"
			},
			UILayer =
			{
				description = "[oLayer][Readonly]",
				typeName = "oLayer",
				type = "value"
			},
			getLayer =
			{
				args = "(zOrder: int)",
				description = "",
				returns = "(layer: oLayer)",
				typeName = "oLayer",
				type = "method"
			},
			removeLayer =
			{
				args = "(zOrder: int)",
				description = "",
				returns = "()",
				type = "method"
			},
			removeAllLayers =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method"
			},
			setLayerRatio =
			{
				args = "(zOrder: int, ratio: oVec2)",
				description = "",
				returns = "()",
				type = "method"
			},
			getLayerRatio =
			{
				args = "(zOrder: int)",
				description = "",
				returns = "(vec2: oVec2)",
				typeName = "oVec2",
				type = "method"
			},
			setLayerOffset =
			{
				args = "(zOrder: int, offset: oVec2)",
				description = "",
				returns = "()",
				type = "method"
			},
			getLayerOffset =
			{
				args = "(zOrder: int)",
				description = "",
				returns = "(vec2: oVec2)",
				typeName = "oVec2",
				type = "method"
			},
		},
		description = "class oPlatformWorld(oWorld).\n args -- ()",
		parents = {"oWorld",},
		type = "class",
		index = index()
	},
	oSensor =
	{
		childs =
		{
			enabled =
			{
				description = "[bool]",
				type = "value"
			},
			tag =
			{
				description = "[int][Readonly]",
				type = "value"
			},
			owner =
			{
				description = "[oBody][Readonly]",
				typeName = "oBody",
				type = "value"
			},
			sensed =
			{
				description = "[bool][Readonly]",
				type = "value"
			},
			sensedBodies =
			{
				description = "[CCArray][Readonly]",
				typeName = "CCArray",
				type = "value"
			},
			contains =
			{
				args = "(body: oBody)",
				description = "",
				returns = "(find: bool)",
				type = "method"
			},
		},
		description = "class oSensor(CCObject).",
		parents = {"CCObject",},
		type = "class",
		index = index()
	},	
	oUnit =
	{
		childs =
		{
			sensity =
			{
				description = "[float]",
				type = "value"
			},
			move =
			{
				description = "[float]",
				type = "value"
			},
			moveSpeed =
			{
				description = "[float]",
				type = "value"
			},
			jump =
			{
				description = "[float]",
				type = "value"
			},
			maxHp =
			{
				description = "[float]",
				type = "value"
			},
			attackBase =
			{
				description = "[float]",
				type = "value"
			},
			attackBonus =
			{
				description = "[float]",
				type = "value"
			},
			attackFactor =
			{
				description = "[float]",
				type = "value"
			},
			attackSpeed =
			{
				description = "[float]",
				type = "value"
			},
			attackPower =
			{
				description = "[oVec2]",
				typeName = "oVec2",
				type = "value"
			},
			attackType =
			{
				description = "[oAttackType]",
				typeName = "oAttackType",
				type = "value"
			},
			attackTarget =
			{
				description = "[oAttackTarget]",
				typeName = "oAttackTarget",
				type = "value"
			},
			targetAllow =
			{
				description = "[oTargetAllow]",
				typeName = "oTargetAllow",
				type = "value"
			},
			damageType =
			{
				description = "[int]",
				type = "value"
			},
			defenceType =
			{
				description = "[int]",
				type = "value"
			},	
			model =
			{
				description = "[oModel]",
				typeName = "oModel",
				type = "value"
			},	
			detectDistance =
			{
				description = "[float]",
				type = "value"
			},	
			attackRange =
			{
				description = "[CCSize]",
				typeName = "CCSize",
				type = "value"
			},	
			faceRight =
			{
				description = "[bool]",
				type = "value"
			},	
			bulletDef =
			{
				description = "[oBulletDef]",
				typeName = "oBulletDef",
				type = "value"
			},	
			onSurface =
			{
				description = "[bool][Readonly]",
				type = "value"
			},
			groundSensor =
			{
				description = "[oSensor][Readonly]",
				typeName = "oSensor",
				type = "value"
			},
			detectSensor =
			{
				description = "[oSensor][Readonly]",
				typeName = "oSensor",
				type = "value"
			},
			attackSensor =
			{
				description = "[oSensor][Readonly]",
				typeName = "oSensor",
				type = "value"
			},
			unitDef =
			{
				description = "[oUnitDef][Readonly]",
				typeName = "oUnitDef",
				type = "value"
			},
			currentAction =
			{
				description = "[oAction][Readonly]",
				typeName = "oAction",
				type = "value"
			},
			width =
			{
				description = "[float][Readonly]",
				type = "value"
			},
			height =
			{
				description = "[float][Readonly]",
				type = "value"
			},
			reflexArc =
			{
				description = "[string]",
				type = "value"
			},
			attachAction =
			{
				args = "(name: string)",
				description = "",
				returns = "(action: oAction)",
				typeName = "oAction",
				type = "method"
			},
			removeAction =
			{
				args = "(name: string)",
				description = "",
				returns = "()",
				type = "method"
			},
			removeAllActions =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method"
			},
			getAction =
			{
				args = "(name: string)",
				description = "",
				returns = "(action: oAction)",
				typeName = "oAction",
				type = "method"
			},
			start =
			{
				args = "(actionName: string)",
				description = "",
				returns = "(success: bool)",
				type = "method"
			},
			stop =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method"
			},
			isDoing =
			{
				args = "(actionName: string)",
				description = "",
				returns = "(doing: bool)",
				type = "method"
			},
			set =
			{
				args = "(name: string, value: float)",
				description = "",
				returns = "()",
				type = "method"
			},
			get =
			{
				args = "(name: string)",
				description = "",
				returns = "(value: float)",
				type = "method"
			},
			remove =
			{
				args = "(name: string)",
				description = "",
				returns = "()",
				type = "method"
			},
			clear =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method"
			},
		},
		description = "class oUnit(oBody).\n args -- (unitDef: oUnitDef, world: oWorld, pos: oVec2 = oVec2.zero, rot: float = 0)",
		parents = {"oBody",},
		type = "class",
		index = index()
	},
	oUnitDef =
	{
		childs =
		{
			bodyDef =
			{
				description = "[oBodyDef]",
				typeName = "oBodyDef",
				type = "value"
			},
			size =
			{
				description = "[CCSize]",
				typeName = "CCSize",
				type = "value"
			},
			density =
			{
				description = "[float]",
				type = "value"
			},
			friction =
			{
				description = "[float]",
				type = "value"
			},
			restitution =
			{
				description = "[float]",
				type = "value"
			},
			static =
			{
				description = "[bool]",
				type = "value"
			},
			GroundSensorTag =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			DetectSensorTag =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			AttackSensorTag =
			{
				description = "[int][Const]",
				static = true,
				type = "value"
			},
			BulletKey =
			{
				description = "[string][Const]",
				static = true,
				type = "value"
			},
			AttackKey =
			{
				description = "[string][Const]",
				static = true,
				type = "value"
			},
			HitKey =
			{
				description = "[string][Const]",
				static = true,
				type = "value"
			},
			tag =
			{
				description = "[int]",
				type = "value"
			},
			reflexArc =
			{
				description = "[string]",
				type = "value"
			},
			scale =
			{
				description = "[float]",
				type = "value"
			},
			sensity =
			{
				description = "[float]",
				type = "value"
			},
			move =
			{
				description = "[float]",
				type = "value"
			},
			jump =
			{
				description = "[float]",
				type = "value"
			},
			detectDistance =
			{
				description = "[float]",
				type = "value"
			},
			maxHp =
			{
				description = "[float]",
				type = "value"
			},
			attackBase =
			{
				description = "[float]",
				type = "value"
			},
			attackDelay =
			{
				description = "[float]",
				type = "value"
			},
			attackEffectDelay =
			{
				description = "[float]",
				type = "value"
			},
			attackRange =
			{
				description = "[CCSize]",
				typeName = "CCSize",
				type = "value"
			},
			attackPower =
			{
				description = "[oVec2]",
				typeName = "oVec2",
				type = "value"
			},
			attackType =
			{
				description = "[oAttackType]",
				typeName = "oAttackType",
				type = "value"
			},
			attackTarget =
			{
				description = "[oAttackTarget]",
				typeName = "oAttackTarget",
				type = "value"
			},
			targetAllow =
			{
				description = "[oTargetAllow]",
				typeName = "oTargetAllow",
				type = "value"
			},
			damageType =
			{
				description = "[unit16]",
				type = "value"
			},
			defenceType =
			{
				description = "[unit16]",
				type = "value"
			},
			bulletType =
			{
				description = "[string]",
				type = "value"
			},
			attackEffect =
			{
				description = "[string]",
				type = "value"
			},
			hitEffect =
			{
				description = "[string]",
				type = "value"
			},
			name =
			{
				description = "[string]",
				typeName = "string",
				type = "value"
			},
			desc =
			{
				description = "[string]",
				typeName = "string",
				type = "value"
			},
			model =
			{
				description = "[string]",
				typeName = "string",
				type = "value"
			},
			sndAttack =
			{
				description = "[string]",
				typeName = "string",
				type = "value"
			},
			sndDeath =
			{
				description = "[string]",
				typeName = "string",
				type = "value"
			},
			setActions =
			{
				args = "(actionIds: table{int})",
				description = "",
				returns = "()",
				type = "method"
			},
			setInstincts =
			{
				args = "(instinctIds: table{int})",
				description = "",
				returns = "()",
				type = "method"
			},
			usePreciseHit =
			{
				description = "[bool]",
				static = true,
				type = "value"
			},
		},
		description = "class oUnitDef(CCObject).\n args -- ()",
		parents = {"CCObject",},
		type = "class",
		index = index()
	},
	oJointDef =
	{
		childs =
		{
			position =
			{
				description = "[oVec2]",
				typeName = "oVec2",
				type = "value"
			},
			angle =
			{
				description = "[float]",
				type = "value"
			},
			distance =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, anchorA: oVec2, anchorB: oVec2, frequency: float = 0, damping: float = 0)",
				description = "[Class Method]",
				typeName = "oJointDef",
				returns = "(jointDef: oJointDef)",
				static = true,
				type = "method",
			},
			friction =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, worldPos: oVec2, maxForce: float, maxTorque: float)",
				description = "[Class Method]",
				typeName = "oJointDef",
				returns = "(jointDef: oJointDef)",
				static = true,
				type = "method",
			},
			spring =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, linearOffset: oVec2, angularOffset: float, maxForce: float, maxTorque: float, correctionFactor: float = 1)",
				description = "[Class Method]",
				typeName = "oJointDef",
				returns = "(jointDef: oJointDef)",
				static = true,
				type = "method",
			},
			pulley =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, anchorA: oVec2, anchorB: oVec2, groundAnchorA: oVec2, groundAnchorB: float, ratio: float = 1)",
				description = "[Class Method]",
				typeName = "oJointDef",
				returns = "(jointDef: oJointDef)",
				static = true,
				type = "method",
			},
			prismatic =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, worldPos: oVec2, axis: oVec2, lowerTranslation: float = 0, upperTranslation: float = 0, maxMotorForce: float = 0, motorSpeed: float = 0)",
				description = "[Class Method]",
				typeName = "oJointDef",
				returns = "(jointDef: oJointDef)",
				static = true,
				type = "method",
			},
			revolute =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, worldPos: oVec2, lowerAngle: float = 0, upperAngle: float = 0, maxMotorTorque: float = 0, motorSpeed: float = 0)",
				description = "[Class Method]",
				typeName = "oJointDef",
				returns = "(jointDef: oJointDef)",
				static = true,
				type = "method",
			},
			rope =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, anchorA: oVec2, anchorB: oVec2, maxLength: float)",
				description = "[Class Method]",
				typeName = "oJointDef",
				returns = "(jointDef: oJointDef)",
				static = true,
				type = "method",
			},
			weld =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, worldPos: oVec2, frequency: float = 0, damping: float = 0)",
				description = "[Class Method]",
				typeName = "oJointDef",
				returns = "(jointDef: oJointDef)",
				static = true,
				type = "method",
			},
			wheel =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, worldPos: oVec2, axis: oVec2, maxMotorTorque: float = 0, motorSpeed: float = 0, frequency: float = 2, damping: float = 0.7)",
				description = "[Class Method]",
				typeName = "oJointDef",
				returns = "(jointDef: oJointDef)",
				static = true,
				type = "method",
			},
		},
		description = "class oJointDef(CCObject).",
		parents = {"CCObject",},
		type = "class",
		index = index()
	},
	oJoint =
	{
		childs =
		{
			world =
			{
				description = "[oWorld][Readonly]",
				typeName = "oWorld",
				type = "value",
			},
			destroy =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
			distance =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, anchorA: oVec2, anchorB: oVec2, frequency: float = 0, damping: float = 0)",
				description = "[Class Method]",
				typeName = "oJoint",
				returns = "(joint: oJoint)",
				static = true,
				type = "method",
			},
			friction =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, worldPos: oVec2, maxForce: float, maxTorque: float)",
				description = "[Class Method]",
				typeName = "oJoint",
				returns = "(joint: oJoint)",
				static = true,
				type = "method",
			},
			spring =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, linearOffset: oVec2, angularOffset: float, maxForce: float, maxTorque: float, correctionFactor: float = 1)",
				description = "[Class Method]",
				typeName = "oJoint",
				returns = "(joint: oJoint)",
				static = true,
				type = "method",
			},
			move =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, targetPos: oVec2, maxForce: float, frequency: float = 5.0, damping: float = 0.7)",
				description = "[Class Method]",
				typeName = "oMoveJoint",
				returns = "(joint: oMoveJoint)",
				static = true,
				type = "method",
			},
			pulley =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, anchorA: oVec2, anchorB: oVec2, groundAnchorA: oVec2, groundAnchorB: float, ratio: float = 1)",
				description = "[Class Method]",
				typeName = "oJoint",
				returns = "(joint: oJoint)",
				static = true,
				type = "method",
			},
			prismatic =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, worldPos: oVec2, axis: oVec2, lowerTranslation: float = 0, upperTranslation: float = 0, maxMotorForce: float = 0, motorSpeed: float = 0)",
				description = "[Class Method]",
				typeName = "oMotorJoint",
				returns = "(joint: oMotorJoint)",
				static = true,
				type = "method",
			},
			revolute =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, worldPos: oVec2, lowerAngle: float = 0, upperAngle: float = 0, maxMotorTorque: float = 0, motorSpeed: float = 0)",
				description = "[Class Method]",
				typeName = "oMotorJoint",
				returns = "(joint: oMotorJoint)",
				static = true,
				type = "method",
			},
			rope =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, anchorA: oVec2, anchorB: oVec2, maxLength: float)",
				description = "[Class Method]",
				typeName = "oJoint",
				returns = "(joint: oJoint)",
				static = true,
				type = "method",
			},
			weld =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, worldPos: oVec2, frequency: float = 0, damping: float = 0)",
				description = "[Class Method]",
				typeName = "oJoint",
				returns = "(joint: oJoint)",
				static = true,
				type = "method",
			},
			wheel =
			{
				args = "(collision: bool, bodyA: oBody, bodyB: oBody, worldPos: oVec2, axis: oVec2, maxMotorTorque: float = 0, motorSpeed: float = 0, frequency: float = 2, damping: float = 0.7)",
				description = "[Class Method]",
				typeName = "oMotorJoint",
				returns = "(joint: oMotorJoint)",
				static = true,
				type = "method",
			},
		},
		description = "class oJoint(CCObject).\n args -- (def: oJointDef, itemDict: CCDictionary)",
		parents = {"CCObject",},
		type = "class",
		index = index()
	},
	oMoveJoint =
	{
		childs =
		{
			position =
			{
				description = "[oVec2]",
				typeName = "oVec2",
				type = "value",
			},
		},
		description = "class oMotorJoint(oJoint).",
		parents = {"oJoint",},
		type = "class",
		hide = true,
		index = index()
	},
	oMotorJoint =
	{
		childs =
		{
			enabled =
			{
				description = "[bool]",
				type = "value",
			},
			force =
			{
				description = "[float]",
				type = "value",
			},
			speed =
			{
				description = "[float]",
				type = "value",
			},
		},
		description = "class oMotorJoint(oJoint).",
		parents = {"oJoint",},
		type = "class",
		hide = true,
		index = index()
	},
	oEvent =
	{
		childs =
		{
			name =
			{
				description = "[string]",
				typeName = "string",
				type = "value",
			},
		},
		description = "class oEvent.",
		hide = true,
		type = "class",
		index = index()
	},
	oSlot =
	{
		childs =
		{
			name =
			{
				description = "[Readonly][string]",
				type = "value",
			},
			enabled =
			{
				description = "[bool]",
				type = "value",
			},
		},
		description = "class oSlot.",
		parents = {"CCObject",},
 		type = "class",
		hide = true,
 		index = index()
 	},
	oSlotList =
	{
		childs =
		{
			add =
			{
				args = "(handler: function)",
				description = " -- handler: function{any: ...}",
				returns = "()",
				type = "method",
			},
			remove =
			{
				args = "(handler: function)",
				description = " -- handler: function{any: ...}",
				returns = "(result: bool)",
				type = "method",
			},
			clear =
			{
				args = "()",
				description = "",
				returns = "()",
				type = "method",
			},
		},
		description = "class oSlotList(CCObject).",
		parents = {"CCObject",},
		type = "class",
		hide = true,
		index = index()
	},
	oRoutine =
	{
		childs =
		{
			remove =
			{
				args = "(routine: thread)",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			start =
			{
				args = "()",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
			stop =
			{
				args = "()",
				description = "",
				returns = "()",
				static = true,
				type = "method",
			},
		},
		description = "class oRoutine.\n args -- (routine: thread)\n -- routine: created by once(function() end) or loop(function() end)",
		type = "class",
		index = index()
	},
	once =
	{
		args = "(action: function)",
		description = "",
		returns = "(routine: thread)",
		type = "function",
		index = index()
	},
	loop =
	{
		args = "(action: function)",
		description = "",
		returns = "(routine: thread)",
		type = "function",
		index = index()
	},
	wait =
	{
		args = "(action: function)",
		description = "",
		returns = "()",
		type = "function",
		index = index()
	},
	seconds =
	{
		args = "(time: float)",
		description = "",
		returns = "(action: function)",
		type = "function",
		index = index()
	},
	thread =
	{
		args = "(action: function)",
		description = "",
		returns = "(routine: thread)",
		type = "function",
		index = index()
	},
	threadLoop =
	{
		args = "(action: function)",
		description = "",
		returns = "(routine: thread)",
		type = "function",
		index = index()
	},
	sleep =
	{
		args = "(nil|time: float)",
		description = "",
		returns = "(action: function)",
		type = "function",
		index = index()
	},
	emit =
	{
		args = "(name: string, eventArgs: ...)",
		description = "send event",
		returns = "()",
		type = "function",
		index = index()
	},
	doXml =
	{
		args = "(xml: string)",
		description = "execute codes of Dorothy Xml format.",
		returns = "(...)",
		type = "function",
		index = index()
	},

	TouchBegan =
	{
		args = "",
		description = " a builtin slot string for CCLayer\n\n single touch -- handler : function(touch: CCTouch)\n\n multi touches -- handler : function(touches: table{CCTouch})\n\n return true to accept touches",
		returns = "",
		type = "function",
		index = index()
	},
	TouchEnded =
	{
		args = "",
		description = " a builtin slot string for CCLayer\n\n single touch -- handler : function(touch: CCTouch)\n\n multi touches -- handler : function(touches: table{CCTouch})",
		returns = "",
		type = "function",
		index = index()
	},
	TouchMoved =
	{
		args = "",
		description = " a builtin slot string for CCLayer\n\n single touch -- handler : function(touch: CCTouch)\n\n multi touches -- handler : function(touches: table{CCTouch})",
		returns = "",
		type = "function",
		index = index()
	},
	TouchCancelled =
	{
		args = "",
		description = " a builtin slot string for CCLayer\n\n single touch -- handler : function(touch: CCTouch)\n\n multi touches -- handler : function(touches: table{CCTouch})",
		returns = "",
		type = "function",
		index = index()
	},
	TapBegan =
	{
		args = "",
		description = " a builtin slot string for CCMenuItem\n\n -- handler : function(menuItem: CCMenuItem)",
		returns = "",
		type = "function",
		index = index()
	},
	TapEnded =
	{
		args = "",
		description = " a builtin slot string for CCMenuItem\n\n -- handler : function(menuItem: CCMenuItem)",
		returns = "",
		type = "function",
		index = index()
	},
	Tapped =
	{
		args = "",
		description = " a builtin slot string for CCMenuItem\n\n -- handler : function(menuItem: CCMenuItem)",
		returns = "",
		type = "function",
		index = index()
	},
	KeyMenu =
	{
		args = "",
		description = " a builtin slot string for CCLayer\n\n -- handler : function()",
		returns = "",
		type = "function",
		index = index()
	},
	KeyBack =
	{
		args = "",
		description = " a builtin slot string for CCLayer\n\n -- handler : function()",
		returns = "",
		type = "function",
		index = index()
	},
	Acceleration =
	{
		args = "",
		description = " a builtin slot string for CCLayer\n\n -- handler : function(x: float, y: float, z: float, timeStep: float)",
		returns = "",
		type = "function",
		index = index()
	},
	Entering =
	{
		args = "",
		description = " a builtin slot string for CCNode\n\n -- handler : function()",
		returns = "",
		type = "function",
		index = index()
	},
	Entered =
	{
		args = "",
		description = " a builtin slot string for CCNode\n\n -- handler : function()",
		returns = "",
		type = "function",
		index = index()
	},
	Exiting =
	{
		args = "",
		description = " a builtin slot string for CCNode\n\n -- handler : function()",
		returns = "",
		type = "function",
		index = index()
	},
	Exited =
	{
		args = "",
		description = " a builtin slot string for CCNode\n\n -- handler : function()",
		returns = "",
		type = "function",
		index = index()
	},
	Cleanup =
	{
		args = "",
		description = " a builtin slot string for CCNode\n\n -- handler : function()",
		returns = "",
		type = "function",
		index = index()
	},
	ContactStart =
	{
		args = "",
		description = " a builtin slot string for oBody\n\n -- handler : function(other: oBody, pos: oVec2, normal: oVec2)",
		returns = "",
		type = "function",
		index = index()
	},
	ContactEnd =
	{
		args = "",
		description = " a builtin slot string for oBody\n\n -- handler : function(other: oBody, pos: oVec2, normal: oVec2)",
		returns = "",
		type = "function",
		index = index()
	},
	BodyEnter =
	{
		args = "",
		description = " a builtin slot string for oBody\n\n -- handler : function(other: oBody, sensor: oSensor)",
		returns = "",
		type = "function",
		index = index()
	},
	BodyLeave =
	{
		args = "",
		description = " a builtin slot string for oBody\n\n -- handler : function(other: oBody, sensor: oSensor)",
		returns = "",
		type = "function",
		index = index()
	},
	InputAttach =
	{
		args = "",
		description = " a builtin slot string for CCTextFieldTTF\n\n -- handler : function(textField: CCTextFieldTTF)\n\n return true to allow IME to open",
		returns = "",
		type = "function",
		index = index()
	},
	InputDettach =
	{
		args = "",
		description = " a builtin slot string for CCTextFieldTTF\n\n -- handler : function(textField: CCTextFieldTTF)\n\n return true to allow IME to close",
		returns = "",
		type = "function",
		index = index()
	},
	InputInserting =
	{
		args = "",
		description = " a builtin slot string for CCTextFieldTTF\n\n -- handler : function(addText: string, textField: CCTextFieldTTF)\n\n return true to accept the input text",
		returns = "",
		type = "function",
		index = index()
	},
	InputInserted =
	{
		args = "",
		description = " a builtin slot string for CCTextFieldTTF\n\n -- handler : function(addText: string, textField: CCTextFieldTTF)",
		returns = "",
		type = "function",
		index = index()
	},
	InputDeleting =
	{
		args = "",
		description = " a builtin slot string for CCTextFieldTTF\n\n -- handler : function(delText: string, textField: CCTextFieldTTF)\n\n return true to make text deleted",
		returns = "",
		type = "function",
		index = index()
	},
	InputDeleted =
	{
		args = "",
		description = " a builtin slot string for CCTextFieldTTF\n\n -- handler : function(delText: string, textField: CCTextFieldTTF)",
		returns = "",
		type = "function",
		index = index()
	},
	AnimationEnd =
	{
		args = "",
		description = " a builtin slot string for oModel\n\n -- handler : function(animationName: string, model: oModel)",
		returns = "",
		type = "function",
		index = index()
	},
	ActionStart =
	{
		args = "",
		description = " a builtin slot string for oUnit\n\n -- handler : function(actionName: string, action: oAction)",
		returns = "",
		type = "function",
		index = index()
	},
	ActionEnd =
	{
		args = "",
		description = " a builtin slot string for oUnit\n\n -- handler : function(actionName: string, action: oAction)",
		returns = "",
		type = "function",
		index = index()
	},
	HitTarget =
	{
		args = "",
		description = " a builtin slot string for oBullet\n\n -- handler : function(target: oUnit, bullet: oBullet)",
		returns = "",
		type = "function",
		index = index()
	},
}

local function makeDerivation(pack)
	local classIndices = {}
	for k,v in pairs(pack) do
		classIndices[v.index] = k
	end
	for i = 1,#classIndices do
		local className = classIndices[i]
		local class = pack[className]
		class.level = 0
		if class.parents then
			for _, parent in ipairs(class.parents) do
				if pack[parent] then
					class.level = pack[parent].level + 1
					--DisplayOutputLn(className,class.level)
					for name,item in pairs(pack[parent].childs) do
						if not class.childs[name] and not item.static then
							class.childs[name] = item
							if not item.className then
								item.className = parent
							end
						end
					end
				end
			end
		end
	end
end

makeDerivation(Dorothy)

return Dorothy