/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "const/oDefine.h"
#include "platform/oPlatformDefine.h"
#include "platform/oPlatformWorld.h"
#include "platform/oCamera.h"
#include "platform/oData.h"
#include "other/DebugDraw.h"

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
	CCARRAY_START(CCNode, layer, _camera->getChildren())
	{
		CCARRAY_START(CCNode, child, layer->getChildren())
		{
			if (child && child->getTag() == tag)
			{
				return child;
			}
		}
		CCARRAY_END
	}
	CCARRAY_END
	return nullptr;
}

void oPlatformWorld::draw()
{
	GLESDebugDraw* draw = (GLESDebugDraw*)oWorld::getB2World()->GetDebugDraw();
	if (draw)
	{
		kmGLTranslatef(_camera->getPositionX(), _camera->getPositionY(), 0);
		draw->ratio = b2Factor;
		draw->Begin();
		oWorld::getB2World()->DrawDebugData();
		kmGLTranslatef(-_camera->getPositionX(), -_camera->getPositionY(), 0);
	}
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
