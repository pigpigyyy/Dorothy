#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oAINode.h"
#include "Dorothy/platform/oAI.h"
#include "Dorothy/platform/oProperty.h"
#include "Dorothy/platform/oUnit.h"
#include "Dorothy/misc/oScriptHandler.h"

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
	instinct->autorelease();
	return instinct;
}

void oInstinct::add( int id, const string& propName, oAILeaf* node )
{
	oInstinct* instinct = new oInstinct(propName, node);
	instinct->autorelease();
	_instincts[id] = instinct;
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
	node->autorelease();
	return node;
}

oSeqNode* oSeqNode::create()
{
	oSeqNode* node = new oSeqNode();
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
	node->_handler = oScriptHandler::create(handler);
	return node;
}

bool oActNode::doAction()
{
	return oAI::getSelf()->doIt(_actionId);
}

oActNode* oActNode::create(int actionId)
{
	oActNode* node = new oActNode();
	node->_actionId = actionId;
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
oAILeaf* oAct(int actionId)
{
	return oActNode::create(actionId);
}

NS_DOROTHY_PLATFORM_END
