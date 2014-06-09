/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_PLATFORM_OPLATFORMWORLD_H__
#define __DOROTHY_PLATFORM_OPLATFORMWORLD_H__

#include "Dorothy/physics/oWorld.h"
#include "Dorothy/misc/oNode3D.h"

NS_DOROTHY_PLATFORM_BEGIN

class oCamera;

class oLayer: public oNode3D
{
public:
	oVec2 ratio;
	void setOffset(const oVec2& offset);
	const oVec2& getOffset() const;
	virtual void reorderChild(CCNode * child, int zOrder);
	virtual CCAffineTransform nodeToGameParentTransform();
	CREATE_FUNC(oLayer);
private:
	oVec2 _offset;
};

class oPlatformWorld: public oWorld
{
	typedef unordered_map<int, oLayer*> oLayerMap;
public:
	virtual bool init();
	PROPERTY_READONLY(oCamera*, Camera);
	PROPERTY_READONLY(CCNode*, UILayer);
	virtual void addChild(CCNode* child);
	virtual void addChild(CCNode* child, int zOrder);
	virtual void addChild(CCNode* child, int zOrder, int tag);
	virtual void reorderChild(CCNode * child, int zOrder);
	virtual void removeChild(CCNode* child, bool cleanup);
	virtual CCNode* getChildByTag(int tag);
	virtual void draw();
	oLayer* getLayer(int zOrder);
	void removeLayer(int zOrder);
	void removeAllLayers();
	void setLayerRatio(int zOrder, const oVec2& ratio);
	const oVec2& getLayerRatio(int zOrder);
	void setLayerOffset(int zOrder, const oVec2& offset);
	const oVec2& getLayerOffset(int zOrder);
	void onCameraMoved(float deltaX, float deltaY);
	CREATE_FUNC(oPlatformWorld);
private:
	oCamera* _camera;
	CCNode* _layerUI;
	oLayerMap _layers;
	CC_LUA_TYPE(oPlatformWorld)
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OPLATFORMWORLD_H__