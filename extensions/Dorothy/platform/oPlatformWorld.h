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
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OPLATFORMWORLD_H__