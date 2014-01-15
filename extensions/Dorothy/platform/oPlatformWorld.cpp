#include "Dorothy/const/oDefine.h"
#include "Dorothy/platform/oPlatformDefine.h"
#include "Dorothy/platform/oPlatformWorld.h"
#include "Dorothy/platform/oCamera.h"
#include "Dorothy/platform/oData.h"

NS_DOROTHY_PLATFORM_BEGIN

void oPlatformWorld::addChild( CCNode* child )
{
	this->addChild(child, child->getZOrder(), child->getTag());
}

void oPlatformWorld::addChild( CCNode* child, int zOrder )
{
	this->addChild(child, zOrder, child->getTag());
}

void oPlatformWorld::addChild( CCNode* child, int zOrder, int tag )
{
	CCNode* layer = oPlatformWorld::getLayer(zOrder);
	layer->addChild(child, zOrder, tag);
}

void oPlatformWorld::reorderChild( CCNode * child, int zOrder )
{
	oRef<CCNode> temp(child);
	CCNode* layer = oPlatformWorld::getLayer(child->getZOrder());
	layer->removeChild(child, false);
	oPlatformWorld::addChild(child, zOrder);
}

void oPlatformWorld::removeChild( CCNode* child, bool cleanup )
{
	CCNode* layer = oPlatformWorld::getLayer(child->getZOrder());
	layer->removeChild(child, cleanup);
}

CCNode* oPlatformWorld::getChildByTag( int tag )
{
	CCAssert( tag != CCNode::InvalidTag, "Invalid tag");
	CCObject* layer;
	CCARRAY_FOREACH(_camera->getChildren(), layer)
	{
		CCObject* child;
		CCARRAY_FOREACH(((CCNode*)layer)->getChildren(), child)
		{
			CCNode* pNode = (CCNode*)child;
			if(pNode && pNode->getTag() == tag)
			{
				return pNode;
			}
		}
	}
	return NULL;
}

void oPlatformWorld::setLayerRatio( int zOrder, const oVec2& ratio )
{
	oLayer* layer = oPlatformWorld::getLayer(zOrder);
	layer->ratio = ratio;
}

const oVec2& oPlatformWorld::getLayerRatio(int zOrder)
{
	oLayer* layer = oPlatformWorld::getLayer(zOrder);
	return layer->ratio;
}

oLayer* oPlatformWorld::getLayer( int zOrder )
{
	auto it = _layers.find(zOrder);
	if (it != _layers.end())
	{
		return it->second;
	}
	else
	{
		oLayer* newLayer = oLayer::create();
		_camera->addChild(newLayer, zOrder, newLayer->getTag());
		_layers[zOrder] = newLayer;
		return newLayer;
	}
}

bool oPlatformWorld::init()
{
	if (!oWorld::init())
	{
		return false;
	}
	_camera = oCamera::create();
	_camera->moved += std::make_pair(this, &oPlatformWorld::onCameraMoved);
	CCNode::addChild(_camera, 0, 0);
	_layerUI = CCNode::create();
	CCNode::addChild(_layerUI, 0, 1);
	oData::shared()->apply(this);
	return true;
}

oCamera* oPlatformWorld::getCamera() const
{
	return _camera;
}

CCNode* oPlatformWorld::getUILayer() const
{
	return _layerUI;
}

void oPlatformWorld::onCameraMoved( float deltaX, float deltaY )
{
	for (auto it : _layers)
	{
		oLayer* layer = it.second;
		layer->setPositionX(deltaX * layer->ratio.x + layer->getPositionX());
		layer->setPositionY(deltaY * layer->ratio.y + layer->getPositionY());
	}
}

void oPlatformWorld::setLayerOffset( int zOrder, const oVec2& offset )
{
	oLayer* layer = oPlatformWorld::getLayer(zOrder);
	layer->setOffset(offset);
}

const oVec2& oPlatformWorld::getLayerOffset( int zOrder )
{
	oLayer* layer = oPlatformWorld::getLayer(zOrder);
	return layer->getOffset();
}

void oLayer::setOffset( const oVec2& offset )
{
	float deltaX = CCNode::getPositionX() - _offset.x;
	float deltaY = CCNode::getPositionY() - _offset.y;
	CCNode::setPosition(deltaX + offset.x, deltaY + offset.y);
	_offset = offset;
}

const oVec2& oLayer::getOffset() const
{
	return _offset;
}

void oLayer::reorderChild( CCNode * child, int zOrder )
{
	CCNode* camera = this->getParent();
	CCNode* world = camera->getParent();
	world->reorderChild(child, zOrder);
}

CCAffineTransform oLayer::nodeToGameParentTransform()
{
	return CCAffineTransformIdentity;
}

void oPlatformWorld::removeLayer( int zOrder )
{
	auto it = _layers.find(zOrder);
	if (it != _layers.end())
	{
		_camera->removeChild(it->second, true);
		_layers.erase(it);
	}
}

void oPlatformWorld::removeAllLayers()
{
	for (const oLayerMap::value_type& item : _layers)
	{
		_camera->removeChild(item.second, true);
	}
	_layers.clear();
}

NS_DOROTHY_PLATFORM_END
