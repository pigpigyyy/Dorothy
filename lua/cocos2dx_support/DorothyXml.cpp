#include "DorothyXml.h"

static void oHandler(const char* begin, const char* end)
{
#define CHECK_CDATA(name) if (strcmp(begin,#name) == 0) CCSAXParser::placeCDataHeader("</"#name">");
#define ELSE_CHECK_CDATA(name) else CHECK_CDATA(name)
	if (*(begin-1) != '/')
	{
		CHECK_CDATA(Listener)
		ELSE_CHECK_CDATA(Schedule)
		ELSE_CHECK_CDATA(Script)
		ELSE_CHECK_CDATA(TapHandler)
		ELSE_CHECK_CDATA(TouchHandler)
		ELSE_CHECK_CDATA(NodeHandler)
		ELSE_CHECK_CDATA(AccelerateHandler)
		ELSE_CHECK_CDATA(KeypadHandler)
	}
}

#define __equals(src,dst) strcmp(src,dst) == 0
#define element_equal(dst) __equals(name,dst)
#define attr_equal(dst) __equals(atts[i],dst)

#define Self_Check(name) \
	if (self.empty()) { self = getUsableName(#name);names.insert(self); }

#define Schedule_Check \
	if (attr_equal("Priority")) { priority = atts[++i]; }

#define Object_Define \
	string self;
#define Object_Check \
	if (attr_equal("Name")) { self = atts[++i]; }

#define Speed_Define \
	Object_Define
#define Speed_Check \
	Object_Check\
	if (attr_equal("Key") && !currentKey) { currentKey = atts[++i]; }\
	else if (attr_equal("Rate")) { rate = atts[++i]; }
#define Speed_Create
#define Speed_Handle
#define Speed_Finish

#define Sequence_Define \
	Object_Define
#define Sequence_Check \
	Object_Check
#define Sequence_Create
#define Sequence_Handle
#define Sequence_Finish

#define Spawn_Define \
	Object_Define
#define Spawn_Check \
	Object_Check
#define Spawn_Create
#define Spawn_Handle
#define Spawn_Finish

#define Data_Define \
	Object_Define
#define Data_Check \
	Object_Check
#define Data_Create \
	stream << "local " << self << " = CCDictionary()\n";
#define Data_Handle
#define Data_Finish \
	if (!stack.empty()) {\
		const oItem& parent = stack.top();\
		stream << parent.name << ".data = " << self << "\n\n";\
	}

#define Listener_Define \
	Object_Define
#define Listener_Check \
	Object_Check\
	else if (attr_equal("Key")) { currentKey = atts[++i]; }\
	else if (attr_equal("Event")) { currentEvent = atts[++i]; }
#define Listener_Create
#define Listener_Handle
#define Listener_Finish

#define Add_To_Parent \
	if (!stack.empty()) {\
		const oItem& parent = stack.top();\
		stream << parent.name << ":addChild(" << self;\
		if (zOrder) {\
			stream << ',' << zOrder;\
			if (tag) stream << ',' << tag;\
		}\
		else if (tag) stream << ",0," << tag;\
		stream << ")\n\n";\
	}

#define Node_Define \
	Object_Define\
	const char* width = nullptr;\
	const char* height = nullptr;\
	const char* x = nullptr;\
	const char* y = nullptr;\
	const char* z = nullptr;\
	const char* anchorX = nullptr;\
	const char* anchorY = nullptr;\
	const char* passColor = nullptr;\
	const char* passOpacity = nullptr;\
	const char* color = nullptr;\
	const char* opacity = nullptr;\
	const char* angle = nullptr;\
	const char* scaleX = nullptr;\
	const char* scaleY = nullptr;\
	const char* scheduler = nullptr;\
	const char* skewX = nullptr;\
	const char* skewY = nullptr;\
	const char* zOrder = nullptr;\
	const char* tag = nullptr;\
	const char* transformTarget = nullptr;\
	const char* visible = nullptr;
#define Node_Check \
	Object_Check\
	else if (attr_equal("Width")) { width = atts[++i]; }\
	else if (attr_equal("Height")) { height = atts[++i];}\
	else if (attr_equal("X")) { x = atts[++i]; }\
	else if (attr_equal("Y")) { y = atts[++i]; }\
	else if (attr_equal("Z")) { z = atts[++i]; }\
	else if (attr_equal("AnchorX")) { anchorX = atts[++i]; }\
	else if (attr_equal("AnchorY")) { anchorY = atts[++i]; }\
	else if (attr_equal("PassColor")) { passColor = atts[++i]; }\
	else if (attr_equal("PassOpacity")) { passOpacity = atts[++i]; }\
	else if (attr_equal("Color")) { color = atts[++i]; }\
	else if (attr_equal("Opacity")) { opacity = atts[++i]; }\
	else if (attr_equal("Angle")) { angle = atts[++i]; }\
	else if (attr_equal("ScaleX")) { scaleX = atts[++i]; }\
	else if (attr_equal("ScaleY")) { scaleY = atts[++i]; }\
	else if (attr_equal("Scheduler")) { scheduler = atts[++i]; }\
	else if (attr_equal("SkewX")) { skewX = atts[++i]; }\
	else if (attr_equal("SkewY")) { skewY = atts[++i]; }\
	else if (attr_equal("ZOrder")) { zOrder = atts[++i]; }\
	else if (attr_equal("Tag")) { tag = atts[++i]; }\
	else if (attr_equal("TransformTarget")) { transformTarget = atts[++i]; }\
	else if (attr_equal("Visible")) { visible = atts[++i]; }
#define Node_Create \
	stream << "local " << self << " = CCNode()\n";
#define Node_Handle \
	if (anchorX && anchorY) stream << self << ".anchor = oVec2(" << anchorX << ',' << anchorY << ")\n";\
	else if (anchorX && !anchorY) stream << self << ".anchor = oVec2(" << anchorX << ',' << self << ".anchor.y)\n";\
	else if (!anchorX && anchorY) stream << self << ".anchor = oVec2(" << self << ".anchor.x," << anchorY << ")\n";\
	if (x) stream << self << ".positionX = " << x << '\n';\
	if (y) stream << self << ".positionY = " << y << '\n';\
	if (z) stream << self << ".positionZ = " << z << '\n';\
	if (passColor) stream << self << ".cascadeColor = " << passColor << '\n';\
	if (passOpacity) stream << self << ".cascadeOpacity = " << passOpacity << '\n';\
	if (color) stream << self << ".color = ccColor3(" << color << ")\n";\
	if (opacity) stream << self << ".opacity = " << opacity << '\n';\
	if (angle) stream << self << ".rotation = " << angle << '\n';\
	if (scaleX) stream << self << ".scaleX = " << scaleX << '\n';\
	if (scaleY) stream << self << ".scaleY = " << scaleY << '\n';\
	if (scheduler) stream << self << ".scheduler = " << scheduler << '\n';\
	if (skewX) stream << self << ".skewX = " << skewX << '\n';\
	if (skewY) stream << self << ".skewY = " << skewY << '\n';\
	if (transformTarget) stream << self << ".transformTarget = " << transformTarget << '\n';\
	if (visible) stream << self << ".visible = " << visible << '\n';\
	if (width && height) stream << self << ".contentSize = CCSize(" << width << ',' << height << ")\n";\
	else if (width && !height) stream << self << ".contentSize = CCSize(" << width << ',' << self << ".contentSize.height)\n";\
	else if (!width && height) stream << self << ".contentSize = CCSize(" << self << ".contentSize.width," << height << ")\n";
#define Node_Finish \
	Add_To_Parent

#define Scene_Define \
	Node_Define
#define Scene_Check \
	Node_Check
#define Scene_Create \
	stream << "local " << self << " = CCScene()\n";
#define Scene_Handle \
	Node_Handle
#define Scene_Finish \
	stream << '\n';

#define DrawNode_Define \
	Node_Define
#define DrawNode_Check \
	Node_Check
#define DrawNode_Create \
	stream << "local " << self << " = CCDrawNode()\n";
#define DrawNode_Handle \
	Node_Handle
#define DrawNode_Finish \
	Add_To_Parent

#define ClipNode_Define \
	Node_Define\
	const char* alphaThreshold = nullptr;\
	const char* inverted = nullptr;\
	const char* stencil = nullptr;
#define ClipNode_Check \
	Node_Check\
	else if (attr_equal("AlphaThreshold")) { alphaThreshold = atts[++i]; }\
	else if (attr_equal("Inverted")) { inverted = atts[++i]; }\
	else if (attr_equal("Stencil")) { stencil = atts[++i]; }
#define ClipNode_Create \
	stream << "local " << self << " = CCClipNode(" << (stencil ? stencil : "Stencil") << ")\n";
#define ClipNode_Handle \
	Node_Handle\
	if (alphaThreshold) stream << self << ".alphaThreshold = " << alphaThreshold << '\n';\
	if (inverted) stream << self << ".inverted = " << inverted << '\n';
#define ClipNode_Finish \
	Add_To_Parent

#define LabelAtlas_Define \
	Node_Define\
	const char* text = nullptr;\
	const char* fntFile = nullptr;
#define LabelAtlas_Check \
	Node_Check\
	else if (attr_equal("Text")) { text = atts[++i]; }\
	else if (attr_equal("File")) { fntFile = atts[++i]; }
#define LabelAtlas_Create \
	stream << "local " << self << " = CCLabelAtlas(\"" << (text ? text : "\"") << ',';\
	if (fntFile) stream << '\"' << fntFile << '\"';\
	else stream << "nil";\
	stream << ")\n";
#define LabelAtlas_Handle \
	Node_Handle
#define LabelAtlas_Finish \
	Add_To_Parent

#define LabelBMFont_Define \
	Node_Define\
	const char* text = nullptr;\
	const char* fntFile = nullptr;\
	const char* fontWidth = nullptr;\
	const char* alignment = nullptr;\
	const char* imageOffset = nullptr;
#define LabelBMFont_Check \
	Node_Check\
	else if (attr_equal("Text")) { text = atts[++i]; }\
	else if (attr_equal("File")) { fntFile = atts[++i]; }\
	else if (attr_equal("FontWidth")) { fontWidth = atts[++i]; }\
	else if (attr_equal("Alignment")) { alignment = atts[++i]; }\
	else if (attr_equal("ImageOffset")) { imageOffset = atts[++i]; }
#define LabelBMFont_Create \
	stream << "local " << self << " = CCLabelBMFont(\"" << (text ? text : "\"");\
	if (fntFile) stream << "\"," << fntFile << '\"';\
	else stream << ",nil";\
	stream << ',' << (fontWidth ? fontWidth : "CCLabelBMFont.AutomaticWidth") << ",CCTextAlign." << (alignment ? alignment : "HLeft") << ',' << (imageOffset ? imageOffset : "oVec2.zero") << ")\n";
#define LabelBMFont_Handle \
	Node_Handle
#define LabelBMFont_Finish \
	Add_To_Parent

#define LabelTTF_Define \
	Node_Define\
	const char* text = nullptr;\
	const char* fontName = nullptr;\
	const char* fontSize = nullptr;
#define LabelTTF_Check \
	Node_Check\
	else if (attr_equal("Text")) { text = atts[++i]; }\
	else if (attr_equal("FontName")) { fontName = atts[++i]; }\
	else if (attr_equal("FontSize")) { fontSize = atts[++i]; }
#define LabelTTF_Create \
	stream << "local " << self << " = CCLabelTTF(\"" << (text ? text : "") << "\",\"" << (fontName ? fontName : "Arial") << "\"," << (fontSize ? fontSize : "12") << ")\n";
#define LabelTTF_Handle \
	Node_Handle
#define LabelTTF_Finish \
	Add_To_Parent

#define Sprite_Define \
	Node_Define\
	const char* file = nullptr;\
	const char* flipX = nullptr;\
	const char* flipY = nullptr;\
	const char* blendFuncSrc = nullptr;\
	const char* blendFuncDst = nullptr;
#define Sprite_Check \
	Node_Check\
	else if (attr_equal("File")) { file = atts[++i]; }\
	else if (attr_equal("FlipX")) { flipX = atts[++i]; }\
	else if (attr_equal("FlipY")) { flipY = atts[++i]; }\
	else if (attr_equal("BlendSrc")) { blendFuncSrc = atts[++i]; }\
	else if (attr_equal("BlendDst")) { blendFuncDst = atts[++i]; }
#define Sprite_Create \
	stream << "local " << self << " = CCSprite(";\
	if (file) stream << '\"' << file << "\")\n";\
	else stream << ")\n";
#define Sprite_Handle \
	Node_Handle\
	if (flipX) stream << self << ".flipX = " << flipX << '\n';\
	if (flipY) stream << self << ".flipY = " << flipY << '\n';\
	if (blendFuncSrc && blendFuncDst) stream << self << ".blendFunc = ccBlendFunc(ccBlendFunc."\
									<< blendFuncSrc << ",ccBlendFunc." << blendFuncDst << ")\n";\
	else if (blendFuncSrc && !blendFuncDst) stream << self << ".blendFunc = ccBlendFunc(ccBlendFunc."\
									<< blendFuncSrc << ',' << self << ".blendFunc.dst)\n";\
	else if (!blendFuncSrc && blendFuncDst) stream << self << ".blendFunc = ccBlendFunc(" << self\
									<< ".blendFunc.src,ccBlendFunc." << blendFuncDst << ")\n";
#define Sprite_Finish \
	Add_To_Parent

#define SpriteBatch_Define \
	Node_Define\
	const char* file = nullptr;
#define SpriteBatch_Check \
	Node_Check\
	else if (attr_equal("File")) { file = atts[++i]; }
#define SpriteBatch_Create \
	stream << "local " << self << " = CCSpriteBatchNode(\"" << (file ? file : "") << "\")\n";
#define SpriteBatch_Handle \
	Node_Handle
#define SpriteBatch_Finish \
	Add_To_Parent

#define Layer_Define \
	Node_Define\
	const char* accelerometerEnabled = nullptr;\
	const char* keypadEnabled = nullptr;\
	const char* touchEnabled = nullptr;\
	const char* touchMode = nullptr;
#define Layer_Check \
	Node_Check\
	else if (attr_equal("AccelerometerEnabled")) { accelerometerEnabled = atts[++i]; }\
	else if (attr_equal("KeypadEnabled")) { keypadEnabled = atts[++i]; }\
	else if (attr_equal("TouchEnabled")) { touchEnabled = atts[++i]; }\
	else if (attr_equal("TouchMode")) { touchMode = atts[++i]; }\
	else if (attr_equal("TouchPriority")) { touchPriority = atts[++i]; }\
	else if (attr_equal("MultiTouch")) { isMultiTouches = atts[++i]; }\
	else if (attr_equal("SwallowTouch")) { swallowsTouches = atts[++i]; }
#define Layer_Create \
	stream << "local " << self << " = CCLayer()\n";
#define Layer_Handle \
	Node_Handle\
	if (accelerometerEnabled) stream << self << ".accelerometerEnabled = " << accelerometerEnabled << '\n';\
	if (keypadEnabled) stream << self << ".keypadEnabled = " << keypadEnabled << '\n';\
	if (touchEnabled) stream << self << ".touchEnabled = " << touchEnabled << '\n';\
	if (touchMode) stream << self << ".touchMode = CCLayer.Touches" << touchMode << '\n';
#define Layer_Finish \
	Add_To_Parent

#define LayerColor_Define \
	Layer_Define\
	const char* blendFuncSrc = nullptr;\
	const char* blendFuncDst = nullptr;
#define LayerColor_Check \
	Layer_Check\
	else if (attr_equal("BlendSrc")) { blendFuncSrc = atts[++i]; }\
	else if (attr_equal("BlendDst")) { blendFuncDst = atts[++i]; }
#define LayerColor_Create \
	stream << "local " << self << " = CCLayerColor()\n";
#define LayerColor_Handle \
	Layer_Handle\
	if (blendFuncSrc && blendFuncDst) stream << self << ".blendFunc = ccBlendFunc(ccBlendFunc."\
									<< blendFuncSrc << ",ccBlendFunc." << blendFuncDst << ")\n";\
	else if (blendFuncSrc && !blendFuncDst) stream << self << ".blendFunc = ccBlendFunc(ccBlendFunc."\
									<< blendFuncSrc << ',' << self << ".blendFunc.dst)\n";\
	else if (!blendFuncSrc && blendFuncDst) stream << self << ".blendFunc = ccBlendFunc(" << self\
									<< ".blendFunc.src,ccBlendFunc." << blendFuncDst << ")\n";
#define LayerColor_Finish \
	Add_To_Parent

#define LayerGradient_Define \
	LayerColor_Define\
	const char* start = nullptr;\
	const char* end = nullptr;\
	const char* vectorX = nullptr;\
	const char* vectorY = nullptr;
#define LayerGradient_Check \
	LayerColor_Check\
	else if (attr_equal("StartColor")) { start = atts[++i]; }\
	else if (attr_equal("EndColor")) { end = atts[++i]; }\
	else if (attr_equal("VectorX")) { vectorX = atts[++i]; }\
	else if (attr_equal("VectorY")) { vectorY = atts[++i]; }
#define LayerGradient_Create \
	stream << "local " << self << " = CCLayerGradient(";\
	if (!start || !start[0]) start = "0xffffffff";\
	if (!end || !end[0]) end = "0xffffffff";\
	if (!vectorX || !vectorX[0]) vectorX = "0";\
	if (!vectorY || !vectorY[0]) vectorY = "0.5";\
	stream << start << ',' << end << ',' << "oVec2(" << vectorX << ',' << vectorY << ")\n";
#define LayerGradient_Handle \
	LayerColor_Handle
#define LayerGradient_Finish \
	Add_To_Parent

#define Menu_Define \
	Layer_Define\
	const char* enabled = nullptr;
#define Menu_Check \
	Layer_Check\
	else if (attr_equal("Enabled")) { enabled = atts[++i]; }
#define Menu_Create \
	stream << "local " << self << " = CCMenu(" << (swallowsTouches ? swallowsTouches : "") << ")\n";\
	swallowsTouches = nullptr;
#define Menu_Handle \
	Layer_Handle\
	if (enabled) stream << self << ".enabled = " << enabled << '\n';
#define Menu_Finish \
	Add_To_Parent

#define MenuItem_Define \
	Node_Define\
	const char* enabled = nullptr;
#define MenuItem_Check \
	Node_Check\
	else if (attr_equal("Enabled")) { enabled = atts[++i]; }
#define MenuItem_Create \
	stream << "local " << self << " = CCMenuItem()\n";
#define MenuItem_Handle \
	Node_Handle\
	if (enabled) stream << self << ".enabled = " << enabled << '\n';
#define MenuItem_Finish \
	Add_To_Parent

#define Item_Equal(name) if (element_equal(#name))
#define Item_Define(name) name##_Define
#define Item_Loop(name) for (int i = 0; atts[i] != nullptr; i++) { name##_Check }
#define Item_Create(name) name##_Create
#define Item_Handle(name) name##_Handle
#define Item_Push(name) name##_Finish;oItem item = {#name,self};stack.push(item);

#define First_Item(name,var) \
	Item_Equal(name)\
	{\
		Item_Define(name)\
		Item_Loop(name)\
		Self_Check(var)\
		Item_Create(name)\
		Item_Handle(name)\
		Item_Push(name)\
	}
#define Item \
	else First_Item

class oXmlDelegate : public CCSAXDelegator
{
public:
	oXmlDelegate():
	codes(nullptr),
	currentKey(nullptr),
	currentEvent(nullptr),
	touchPriority(nullptr),
	isMultiTouches(nullptr),
	swallowsTouches(nullptr),
	priority(nullptr),
	rate(nullptr)
	{ }
    virtual void startElement(void *ctx, const char *name, const char **atts)
	{
		First_Item(Node, node)
		Item(Scene, scene)
		Item(DrawNode, drawNode)
		Item(Sprite, sprite)
		Item(SpriteBatch, spriteBatch)
		Item(Layer, layer)
		Item(LayerColor, layer)
		Item(LayerGradient, layer)
		Item(ClipNode, clipNode)
		Item(LabelAtlas, label)
		Item(LabelBMFont, label)
		Item(LabelTTF, label)
		Item(Menu, menu)
		Item(MenuItem, menuItem)
		Item(Data, data)
		Item(Listener, listener)
		Item(Speed, speed)
		Item(Sequence, sequence)
		Item(Spawn, spawn)
		else if (element_equal("Schedule"))
		{
			Item_Loop(Schedule)
		}
	}
    virtual void endElement(void *ctx, const char *name)
	{
		oItem currentData = stack.top();
		if (!stack.empty() && strcmp(name, stack.top().type) == 0)
		{
			stack.pop();
		}
		if (element_equal("Listener"))
		{
			if (!stack.empty())
			{
				stream << "local " << currentData.name << " = oListener(\"" << currentEvent << "\","
					<< codes << ")\n";
				oItem& data = stack.top();
				stream << data.name << "[\"" << (currentKey ? currentKey : currentData.name.c_str()) << "\"] = " << currentData.name << "\n\n";
			}
			codes = nullptr;
			currentKey = nullptr;
			currentEvent = nullptr;
		}
		else if (element_equal("Script"))
		{
			stream << codes << '\n';
			codes = nullptr;
		}
		else if (element_equal("TouchHandler"))
		{
			stream << currentData.name << ":registerTouchHandler(" << (codes ? codes : "")
				<< ',' << (isMultiTouches ? isMultiTouches : "false")
				<< ',' << (touchPriority ? touchPriority : "0")
				<< ',' << (swallowsTouches ? swallowsTouches : "false") << ")\n";
			codes = nullptr;
			isMultiTouches = nullptr;
			touchPriority = nullptr;
			swallowsTouches = nullptr;
		}
		else if (element_equal("AccelerateHandler"))
		{
			stream << currentData.name << ":registerAccelerateHandler(" << (codes ? codes : "") << ")\n";
			codes = nullptr;
		}
		else if (element_equal("KeypadHandler"))
		{
			stream << currentData.name << ":registerKeypadHandler(" << (codes ? codes : "") << ")\n";
			codes = nullptr;
		}
		else if (element_equal("NodeHandler"))
		{
			stream << currentData.name << ":registerEventHandler(" << (codes ? codes : "") << ")\n";
			codes = nullptr;
		}
		else if (element_equal("TapHandler"))
		{
			stream << currentData.name << ":registerTapHandler(" << (codes ? codes : "") << ")\n";
			codes = nullptr;
		}
		else if (element_equal("Schedule"))
		{
			stream << currentData.name << ":schedule(" << (codes ? codes : "");
			if (priority) stream << ',' << priority;
			stream << ")\n";
			codes = nullptr;
			priority = nullptr;
		}
		else if (element_equal("Layer") || element_equal("LayerColor") || element_equal("LayerGradient"))
		{
			if (touchPriority)
			{
				stream << currentData.name << ".touchPriority = " << touchPriority << '\n';
				touchPriority = nullptr;
			}
		}
		else if (element_equal("Speed"))
		{
			ostringstream tempStream;
			tempStream << "CCSpeed(";
			if (!rate || !rate[0]) rate = "1";
			if (!items.empty())
			{
				tempStream << items.top();
				items.pop();
			}
			else
			{
				tempStream << "nil";
			}
			tempStream << ',' << rate << ")";
			if (strcmp(stack.top().type, "Data") == 0)
			{
				stream << "local " << currentData.name << " = " << tempStream.str() << '\n';
				oItem& data = stack.top();
				stream << data.name << "[\"" << (currentKey ? currentKey : currentData.name.c_str()) << "\"] = " << currentData.name << "\n\n";
			}
			else items.push(tempStream.str());
		}
		else if (element_equal("Sequence"))
		{
			ostringstream tempStream;
			tempStream << "CCSequence({";
			while (!items.empty())
			{
				tempStream << items.top();
				items.pop();
				if (!items.empty())
				{
					tempStream << ",\n";
				}
			}
			tempStream << "})";
			if (strcmp(stack.top().type, "Data") == 0)
			{
				stream << "local " << currentData.name << " = " << tempStream.str() << '\n';
				oItem& data = stack.top();
				stream << data.name << "[\"" << (currentKey ? currentKey : currentData.name.c_str()) << "\"] = " << currentData.name << "\n\n";
			}
			else items.push(tempStream.str());
		}
		else if (element_equal("Spawn"))
		{
			ostringstream tempStream;
			tempStream << "CCSpawn({";
			while (!items.empty())
			{
				tempStream << items.top();
				items.pop();
				if (!items.empty())
				{
					tempStream << ",\n";
				}
			}
			tempStream << "})";
			if (strcmp(stack.top().type, "Data") == 0)
			{
				stream << "local " << currentData.name << " = " << tempStream.str() << '\n';
				oItem& data = stack.top();
				stream << data.name << "[\"" << (currentKey ? currentKey : currentData.name.c_str()) << "\"] = " << currentData.name << "\n\n";
			}
			else items.push(tempStream.str());
		}
	}
    virtual void textHandler(void *ctx, const char *s, int len)
	{
		codes = s;
	}
public:
	void clear()
	{
		currentKey = nullptr;
		currentEvent = nullptr;
		codes = nullptr;
		for (; !stack.empty(); stack.pop());
		stream.clear();
		names.clear();
	}
	string getResult()
	{
		return stream.str();
	}
private:
	string getUsableName(const char* baseName)
	{
		char number[7];// max number can only have 6 digits
		int index = 1;
		string base(baseName);
		string name;
		do
		{
			sprintf(number,"%d",index);
			name = base + number;
			auto it = names.find(name);
			if (it == names.end()) break;
			else index++;
		} 
		while (true);
		return name;
	}
private:
	struct oItem
	{
		const char* type;
		string name;
	};
	// Listener
	const char* codes;
	const char* currentKey;
	const char* currentEvent;
	// Layer
	const char* touchPriority;
	const char* isMultiTouches;
	const char* swallowsTouches;
	// Schedule
	const char* priority;
	// Speed
	const char* rate;
	// Loader
	stack<string> items;
	stack<oItem> stack;
	unordered_set<string> names;
	ostringstream stream;
};

oXmlLoader::oXmlLoader():_delegate(new oXmlDelegate())
{
	_parser.setDelegator(_delegate);
}

oXmlLoader::~oXmlLoader()
{ }

string oXmlLoader::load(const char* filename)
{
	_delegate->clear();
	CCSAXParser::setHeaderHandler(oHandler);
	bool result = _parser.parse(filename);
	CCSAXParser::setHeaderHandler(nullptr);
	return result ? _delegate->getResult() : string();
}
