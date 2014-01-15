class oAILeaf: public CCObject
{};

class oInstinct
{
	static void add(int id, const string& propName, oAILeaf* node);
	static void clear();
};

oAILeaf* oSel(CCArray* nodes);
oAILeaf* oSeq(CCArray* nodes);
oAILeaf* oParSel(CCArray* nodes);
oAILeaf* oParSeq(CCArray* nodes);
oAILeaf* oCon(LUA_FUNCTION handler);
oAILeaf* oAct(int actionId);
