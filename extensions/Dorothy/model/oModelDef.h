#ifndef __DOROTHY_MODEL_OMEDOLDEF_H__
#define __DOROTHY_MODEL_OMEDOLDEF_H__

NS_DOROTHY_BEGIN

class oModelAnimationDef;
class oModel;

/** @brief It`s component class of oModelDef. Do not use it alone. */
class oSpriteDef
{
public:
	CCTexture2D* texture;
	int clip;
	float x;
	float y;
	float rotation;
	float anchorX;
	float anchorY;
	float scaleX;
	float scaleY;
	float skewX;
	float skewY;
	bool visible;
	float opacity;
	CCRect rect;
	string name;

	oOwnVector<oSpriteDef> children;
	oOwnVector<oModelAnimationDef> animationDefs;
	vector<int> looks;

	oSpriteDef();
	void restore(CCSprite* sprite);
	/**
	 @brief get a new reset animation to restore a node before playing a new animation
	 returns an animation of CCSpawn with an array of
	 [oKeyPos,oKeyScale,oKeyRoll,oKeySkew,oKeyOpacity] instances that compose the CCSpawn instance.
	 or returns an animation of CCHide with nullptr.
	*/
	tuple<CCFiniteTimeAction*,CCArray*> toResetAction();
	CCSprite* toSprite();
	string toXml();

	template<typename NodeFunc>
	static void traverse(oSpriteDef* root, const NodeFunc& func)
	{
		func(root);
		const oOwnVector<oSpriteDef>& childrenDef = root->children();
		for (oSpriteDef* childDef: childrenDef)
		{
			oSpriteDef::traverse(childDef, func);
		}
	}
};

/** @brief Data define for a 2D model. */
class oModelDef: public CCObject
{
public:
	oModelDef();
	oModelDef(
		bool isFaceRight,
		bool isBatchUsed,
		const string& clipFile,
		CCTexture2D* texture,
		oSpriteDef* root,
		const vector<oVec2>& keys,
		const hash_strmap<int>& animationIndex,
		const hash_strmap<int>& lookIndex);
	const string& getClipFile() const;
	CCTexture2D* getTexture();
	oSpriteDef* getRoot();
	void addKeyPoint(const oVec2& point);
	const oVec2& getKeyPoint(uint32 index) const;
	bool isFaceRight() const;
	bool isBatchUsed() const;
	void setActionName(int index, const string& name);
	void setLookName(int index, const string& name);
	int getAnimationIndexByName(const string& name);
	string getAnimationNameByIndex(int index);
	int getLookIndexByName(const string& name);
	int getKeyPointCount() const;
	const hash_strmap<int>& getAnimationIndexMap() const;
	const hash_strmap<int>& getLookIndexMap() const;
	oModel* toModel();
	string toXml();
	static oModelDef* create();
private:
	typedef hash_strmap<int> oIndexMap;
	void setTexture(CCTexture2D* tex);
	void setRoot(oSpriteDef* root);
	bool _isBatchUsed;
	bool _isFaceRight;
	vector<oVec2> _keys;
	oRef<CCTexture2D> _texture;
	oOwn<oSpriteDef> _root;
	string _clip;
	oIndexMap _animationIndex;
	oIndexMap _lookIndex;
	friend class oModelCache;
};

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OMEDOLDEF_H__