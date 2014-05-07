#ifndef __DOROTHY_MODEL_OMEDOL_H__
#define __DOROTHY_MODEL_OMEDOL_H__

NS_DOROTHY_BEGIN

class oModel;
class oActionDuration;
class oSequence;
class oSpriteDef;
class oModelDef;

/** @brief A look is to change visibility of a model`s different parts.
 For example you can change a character`s face by different look.
 It`s component class of oModel. Do not use it alone.
*/
class oLook
{
public:
	enum {None = -1};
	void add(CCNode* node);
	void apply();
	void unApply();
private:
	vector<CCNode*> _nodes;
};

/** @brief It`s component class of oModelDef. Do not use it alone. */
class oAnimation
{
public:
	enum {None = -1};
	oAnimation(CCNode* node, oActionDuration* action);
	void run();
	void pause();
	void resume();
	void stop();
	void setElapsed(float time);
	float getTime() const;
	float getDuration() const;
	void setSpeed(float speed);
	float getSpeed() const;
	CCNode* getNode() const;
	void setAction(oActionDuration* action);
	oActionDuration* getAction() const;
private:
	CCNode* _node;
	oRef<oActionDuration> _action;
};

typedef Delegate<void (oModel* model)> oAnimationHandler;

class oAnimationGroup
{
public:
	oOwnVector<oAnimation> animations;
	oAnimationHandler animationEnd;
};

class oResetAnimation: public CCObject
{
public:
	void add(
		oSpriteDef* spriteDef,
		CCNode* node,
		CCFiniteTimeAction* animation,
		CCArray* keyFrames);
	void run(float duration, int index);
	void stop();
	Delegate<void()> end;
private:
	void onActionEnd();
	struct oAnimationData
	{
		oSpriteDef* spriteDef;
		CCNode* node;// weak reference
		oRef<CCFiniteTimeAction> animation;
		oRef<CCArray> keyFrames;
	};
	oOwnVector<oAnimationData> _group;
};

class oModel: public CCNode
{
public:
	PROPERTY_NAME_REF(string, Look);
	PROPERTY(float, _speed, Speed);
	PROPERTY_BOOL(_loop, Loop);
	PROPERTY_NAME(float, Time);
	PROPERTY_READONLY(float, Duration);
	PROPERTY(float, _recoverTime, Recovery);
	PROPERTY_BOOL(_faceRight, FaceRight);
	virtual bool init();
	void setLook(int index);
	void play(uint32 index);
	void play(const string& name);
	void pause();
	void resume();
	void resume(uint32 index);
	void resume(const string& name);
	void reset();
	void stop();
	bool isPlaying() const;
	bool isPaused() const;
	int getCurrentAnimationIndex() const;
	string getCurrentAnimationName() const;
	oModelDef* getModelDef() const;
	CCNode* getNodeByName(const string& name);
	class oAnimationHandlerGroup
	{
	public:
		void operator()(oModel* owner);
		oAnimationHandler& operator[](int index);
		oAnimationHandler& operator[](const string& name);
	private:
		oModel* _owner;
		friend class oModel;
	} handlers;
	static oModel* create(oModelDef* modelDef);
	static oModel* create(const char* filename);
	static oModel* none();
protected:
	oModel(oModelDef* def);
private:
	typedef hash_strmap<CCNode*> oNodeMap;
	void visit(oSpriteDef* parentDef, CCNode* parentNode);
	void onResetAnimationEnd();
	void addLook(int index, CCNode* node);
	void addAnimation(int index, CCNode* node, oActionDuration* action);
	void reset(oSpriteDef* parentDef, CCNode* parentNode);
	void setupCallback();
	void onActionEnd();
	oNodeMap& nodeMap();
	bool _isPlaying;
	bool _isPaused;
	bool _isRecovering;
	int _currentLook;
	const string& _currentLookName;
	int _currentAnimation;
	CCNode* _root;
	oOwn<oNodeMap> _nodeMap;
	oRef<oModelDef> _modelDef;
	oOwnVector<oLook> _looks;
	oOwnVector<oAnimationGroup> _animationGroups;
	oResetAnimation _resetAnimation;
};

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OMEDOL_H__