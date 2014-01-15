class oLayer: public oNode3D
{ };

class oPlatformWorld: public oWorld
{
	tolua_readonly tolua_property__common oCamera* camera;
	tolua_readonly tolua_property__common CCNode* UILayer;
	oLayer* getLayer(int zOrder);
	void removeLayer(int zOrder);
	void removeAllLayers();
	void setLayerRatio(int zOrder, const oVec2& ratio);
	const oVec2& getLayerRatio(int zOrder);
	void setLayerOffset(int zOrder, const oVec2& offset);
	const oVec2& getLayerOffset(int zOrder);
	static oPlatformWorld* create();
};
