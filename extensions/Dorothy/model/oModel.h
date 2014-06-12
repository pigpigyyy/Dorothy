/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

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
	typedef unordered_map<string, CCNode*> oNodeMap;
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
	CC_LUA_TYPE(oModel)
};

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OMEDOL_H__