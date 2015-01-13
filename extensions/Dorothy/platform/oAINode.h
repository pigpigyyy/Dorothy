/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_PLATFORM_OAI_NODE_H__
#define __DOROTHY_PLATFORM_OAI_NODE_H__

#include "Dorothy/platform/oProperty.h"

NS_DOROTHY_BEGIN
class oScriptHandler;
NS_DOROTHY_END

NS_DOROTHY_PLATFORM_BEGIN

class oUnit;
class oAILeaf;

class oInstinct: public CCObject
{
public:
	void install(oUnit* unit);
	void uninstall(oUnit* unit);
	void onInstinctPropertyChanged(oUnit* unit, float oldValue, float newValue);
	static oInstinct* create(const string& propName, oAILeaf* node);
	static void add(int id, const string& propName, oAILeaf* node);
	static void clear();
	static oInstinct* get(int id);
protected:
	oInstinct(const string& propName, oAILeaf* node);
private:
	string _propName;
	oRef<oAILeaf> _actionNode;
	static unordered_map<int, oRef<oInstinct>> _instincts;
};

/** @brief Behavior Tree base node */
class oAILeaf: public CCObject
{
public:
	virtual bool doAction() = 0;
	CC_LUA_TYPE(oAILeaf)
};

class oAINode: public oAILeaf
{
public:
	oAINode* add(oAILeaf* node);
	void remove(oAILeaf* node);
	void clear();
	const oRefVector<oAILeaf>& getChildren() const;
protected:
	oRefVector<oAILeaf> _children;
};

/** @brief Selector Node */
class oSelNode: public oAINode
{
public:
	virtual bool doAction();
	static oSelNode* create();
};

/** @brief Sequence Node */
class oSeqNode: public oAINode
{
public:
	virtual bool doAction();
	static oSeqNode* create();
};

/** @brief Parallel Selector Node */
class oParSelNode: public oAINode
{
public:
	virtual bool doAction();
	static oParSelNode* create();
};

/** @brief Parallel Sequence Node */
class oParSeqNode: public oAINode
{
public:
	virtual bool doAction();
	static oParSeqNode* create();
};

class oConNode: public oAILeaf
{
public:
	virtual bool doAction();
	static oConNode* create(int handler);
private:
	oRef<oScriptHandler> _handler;
};

class oActNode: public oAILeaf
{
public:
	virtual bool doAction();
	static oActNode* create(int actionId);
private:
	int _actionId;
};

oAILeaf* oSel(oAILeaf* nodes[], int count);
oAILeaf* oSeq(oAILeaf* nodes[], int count);
oAILeaf* oParSel(oAILeaf* nodes[], int count);
oAILeaf* oParSeq(oAILeaf* nodes[], int count);
oAILeaf* oCon(int handler);
oAILeaf* oAct(int actionId);

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OAI_NODE_H__
