class oFace: public CCObject
{
	void addChild(oFace* face);
	bool removeChild(oFace* face);
	CCNode* toNode();
	static oFace* create(const string& faceStr, const oVec2& point);
};
