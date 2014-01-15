class oData
{
	tolua_readonly tolua_property__common int GroupHide;
	tolua_readonly tolua_property__common int GroupDetectPlayer;
	tolua_readonly tolua_property__common int GroupTerrain;
	tolua_readonly tolua_property__common int GroupDetect;
	void setRelation(int groupA, int groupB, oRelation relation);
	oRelation getRelation(int groupA, int groupB);
	oRelation getRelation(oUnit* unitA, oUnit* unitB);
	void setDamageFactor(unsigned short damageType, unsigned short defenceType, float bounus);
	float getDamageFactor(unsigned short damageType, unsigned short defenceType);
	bool isPlayerUnit(oBody* body);
	bool isTerrain(oBody* body);
	
	static oData* shared @ create();
};
