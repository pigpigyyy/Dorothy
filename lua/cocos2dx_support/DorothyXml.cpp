#include "DorothyXml.h"

static void oHandler(const char* begin, const char* end)
{
#define CHECK_CDATA(name) if (strncmp(begin,#name,(end-begin)/sizeof(char)) == 0) CCSAXParser::placeCDataHeader("</"#name">");
#define ELSE_CHECK_CDATA(name) else CHECK_CDATA(name)
	if (*(begin - 1) != '/')
	{
		CHECK_CDATA(Listener)
		ELSE_CHECK_CDATA(Schedule)
		ELSE_CHECK_CDATA(TapHandler)
		ELSE_CHECK_CDATA(TouchHandler)
		ELSE_CHECK_CDATA(EventHandler)
	}
}

#define __equals(src,dst) strncmp(src,dst,sizeof(dst)/sizeof(char)-1) == 0
#define element_equal(dst) __equals(name,dst)
#define attr_equal(dst) __equals(atts[i],dst)

#define Self_Check(name) \
	if (self.empty()) { self = getUsableName(#name);names.insert(self); }

#define Object_Define \
	string self;
#define Object_Check \
	if (attr_equal("Name")) { self = atts[++i]; }

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
		stream << parent.name << ".data = " << self << '\n';\
	}

#define Listener_Define \
	Object_Define
#define Listener_Check \
	Object_Check\
	else if (attr_equal("Key")) { currentKey = atts[++i]; }\
	else if (attr_equal("Event")) { currentEvent = atts[++i]; }
#define Listener_Create
#define Listener_Handle
#define Listener_Finish \
	currentName = self;

#define Add_To_Parent \
	if (!stack.empty()) {\
		const oItem& parent = stack.top();\
		stream << parent.name << ":addChild(" << self << ")\n";\
	}

#define Node_Define \
	Object_Define \
	const char* width = nullptr;\
	const char* height = nullptr;\
	const char* x = nullptr;\
	const char* y = nullptr;
#define Node_Check \
	Object_Check \
	else if (attr_equal("Width")) { width = atts[++i]; }\
	else if (attr_equal("Height")) { height = atts[++i];}\
	else if (attr_equal("X")) { x = atts[++i]; }\
	else if (attr_equal("Y")) { y = atts[++i]; }
#define Node_Create \
	stream << "local " << self << " = CCNode()\n";
#define Node_Handle \
	if (x) stream << self << ".positionX = " << x << '\n';\
	if (y) stream << self << ".positionY = " << y << '\n';\
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
#define Scene_Finish

#define Sprite_Define \
	Node_Define\
	const char* source = nullptr;
#define Sprite_Check \
	Node_Check\
	else if (attr_equal("Source")) { source = atts[++i]; }
#define Sprite_Create \
	stream << "local " << self << " = CCSprite(\"" << (source ? source : "") << "\")\n";
#define Sprite_Handle \
	Node_Handle
#define Sprite_Finish \
	Add_To_Parent

#define Layer_Define \
	Node_Define
#define Layer_Check \
	Node_Check
#define Layer_Create \
	stream << "local " << self << " = CCLayer()\n";
#define Layer_Handle \
	Node_Handle
#define Layer_Finish \
	Add_To_Parent

#define Item_Equal(name) if (element_equal(#name))
#define Item_Define(name) name##_Define
#define Item_Loop(name) for (int i = 0; atts[i] != nullptr; i++) { name##_Check }
#define Item_Create(name) name##_Create
#define Item_Handle(name) name##_Handle
#define Item_Push(name) name##_Finish;stack.push(oItem{#name,self});

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
	virtual void startElement(void* ctx, const char* name, const char** atts)
	{
		First_Item(Node, node)
		Item(Scene, scene)
		Item(Sprite, sprite)
		Item(Layer, layer)
		Item(Data, data)
		Item(Listener, listener)
	}
	virtual void endElement(void* ctx, const char* name)
	{
		if (!stack.empty() && strcmp(name, stack.top().type) == 0)
		{
			stack.pop();
		}
		if (element_equal("Listener") && !stack.empty())
		{
			stream << "local " << currentName << " = oListener(\"" << currentEvent << "\","
				<< codes << ")\n";
			oItem& data = stack.top();
			stream << data.name << "[\"" << (currentKey ? currentKey : currentName.c_str()) << "\"] = " << currentName << '\n';
		}
		if (currentKey) currentKey = nullptr;
	}
	virtual void textHandler(void* ctx, const char* s, int len)
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
	const char* codes;
	const char* currentKey;
	const char* currentEvent;
	string currentName;
	ostringstream stream;
	stack<oItem> stack;
	unordered_set<string> names;
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
