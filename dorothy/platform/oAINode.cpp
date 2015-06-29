/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "const/oDefine.h"
#include "platform/oPlatformDefine.h"
#include "platform/oAINode.h"
#include "platform/oAI.h"
#include "platform/oProperty.h"
#include "platform/oUnit.h"
#include "misc/oScriptHandler.h"

NS_DOROTHY_PLATFORM_BEGIN

unordered_map<int, oRef<oInstinct>> oInstinct::_instincts;

oInstinct::oInstinct( const string& propName, oAILeaf* node ):
_actionNode(node),
_propName(propName)
{ }

void oInstinct::install(oUnit* unit)
{
	oProperty* prop = unit->properties.get(_propName);
	if (prop)
	{
		prop->changed += std::make_pair(this, &oInstinct::onInstinctPropertyChanged);
	}
}

void oInstinct::uninstall( oUnit* unit )
{
	oProperty* prop = unit->properties.get(_propName);
	if (prop)
	{
		prop->changed -= std::make_pair(this, &oInstinct::onInstinctPropertyChanged);
	}
}

void oInstinct::onInstinctPropertyChanged( oUnit* unit, float oldValue, float newValue )
{
	oAI::_self = unit;
	oAI::_oldInstinctValue = oldValue;
	oAI::_newInstinctValue = newValue;
	_actionNode->doAction();
}

oInstinct* oInstinct::create( const string& propName, oAILeaf* node )
{
	oInstinct* instinct = new oInstinct(propName, node);
	CC_INIT(instinct);
	instinct->autorelease();
	return instinct;
}

void oInstinct::add( int id, const string& propName, oAILeaf* node )
{
	_instincts[id] = oInstinct::create(propName, node);
}

void oInstinct::clear()
{
	_instincts.clear();
}

oInstinct* oInstinct::get( int id )
{
	auto it = _instincts.find(id);
	if (it != _instincts.end())
	{
		return it->second;
	}
	return nullptr;
}

oAINode* oAINode::add( oAILeaf* node )
{
	_children.push_back(node);
	return this;
}

void oAINode::remove( oAILeaf* node )
{
	_children.remove(node);
}

void oAINode::clear()
{
	_children.clear();
}

const oRefVector<oAILeaf>& oAINode::getChildren() const
{
	return _children;
}

bool oSelNode::doAction()
{
	for (oAILeaf* node : _children)
	{
		if (node->doAction())
		{
			return true;
		}
	}
	return false;
}

oSelNode* oSelNode::create()
{
	oSelNode* node = new oSelNode();
	CC_INIT(node);
	node->autorelease();
	return node;
}

oSeqNode* oSeqNode::create()
{
	oSeqNode* node = new oSeqNode();
	CC_INIT(node);
	node->autorelease();
	return node;
}

bool oSeqNode::doAction()
{
	for (oAILeaf* node : _children)
	{
		if (!node->doAction())
		{
			return false;
		}
	}
	return true;
}

oParSelNode* oParSelNode::create()
{
	oParSelNode* node = new oParSelNode();
	CC_INIT(node);
	node->autorelease();
	return node;
}

bool oParSelNode::doAction()
{
	bool result = true;
	for (oAILeaf* node : _children)
	{
		if (!node->doAction())
		{
			result = false;
		}
	}
	return result;
}

oParSeqNode* oParSeqNode::create()
{
	oParSeqNode* node = new oParSeqNode();
	CC_INIT(node);
	node->autorelease();
	return node;
}

bool oParSeqNode::doAction()
{
	bool result = false;
	for (oAILeaf* node : _children)
	{
		if (node->doAction())
		{
			result = true;
		}
	}
	return result;
}

bool oConNode::doAction()
{
	return CCScriptEngine::sharedEngine()->executeFunction(_handler->get()) != 0;
}

oConNode* oConNode::create( int handler )
{
	oConNode* node = new oConNode();
	CC_INIT(node);
	node->_handler = oScriptHandler::create(handler);
	node->autorelease();
	return node;
}

bool oActNode::doAction()
{
	return oAI::getSelf()->start(_actionName);
}

oActNode* oActNode::create(const string& actionName)
{
	oActNode* node = new oActNode();
	CC_INIT(node);
	node->_actionName = actionName;
	node->autorelease();
	return node;
}

oAILeaf* oSel(oAILeaf* nodes[], int count)
{
	oSelNode* sel = oSelNode::create();
	for (int i = 0; i < count; i++)
	{
		sel->add(nodes[i]);
	}
	return sel;
}
oAILeaf* oSeq(oAILeaf* nodes[], int count)
{
	oSeqNode* seq = oSeqNode::create();
	for (int i = 0; i < count; i++)
	{
		seq->add(nodes[i]);
	}
	return seq;
}
oAILeaf* oParSel(oAILeaf* nodes[], int count)
{
	oParSelNode* parSel = oParSelNode::create();
	for (int i = 0; i < count; i++)
	{
		parSel->add(nodes[i]);
	}
	return parSel;
}
oAILeaf* oParSeq(oAILeaf* nodes[], int count)
{
	oParSeqNode* parSeq = oParSeqNode::create();
	for (int i = 0; i < count; i++)
	{
		parSeq->add(nodes[i]);
	}
	return parSeq;
}
oAILeaf* oCon(int handler)
{
	return oConNode::create(handler);
}
oAILeaf* oAct(const string& actionName)
{
	return oActNode::create(actionName);
}

NS_DOROTHY_PLATFORM_END
