#ifndef __DOROTHY_PHYSICS_OSENSOR_H__
#define __DOROTHY_PHYSICS_OSENSOR_H__

NS_DOROTHY_BEGIN

class oBody;

class oSensor: public CCObject
{
	typedef Delegate<void(oSensor*,oBody*)> oSensorHandler;
public:
	virtual ~oSensor();
	/**
	 Set sensor enable to false to stop detection.
	 */
	PROPERTY_BOOL(_enabled, Enabled);
	PROPERTY_READONLY(int, Tag);
	PROPERTY_READONLY(oBody*, Owner);
	PROPERTY_READONLY(b2Fixture*, Fixture);
	PROPERTY_READONLY(CCArray*, SensedBodies);
	PROPERTY_NAME(int, Group);
	bool isSensed() const;
	bool contains(oBody* body);
	/**
	 Set the callback function which is called every time
	 there is a detectable body that entered the sensor`s area.
	 */
	oSensorHandler bodyEnter;
	/**
	 Set the callback function which is called every time
	 there is a detectable body that left the sensor`s area.
	 */
	oSensorHandler bodyLeave;
	
	static oSensor* create(oBody* owner, int tag, b2Fixture* fixture);
protected:
	oSensor(oBody* owner, int tag, b2Fixture* fixture);
	int _tag;
	oBody* _owner;
	b2Fixture* _fixture;
private:
	void executeEnterHandler();
	void executeLeaveHandler();
	void add(oBody* body);
	void remove(oBody* body);
	void clear();
	oRef<CCArray> _sensedBodies;
	friend class oContactListener;
};

NS_DOROTHY_END

#endif // __DOROTHY_PHYSICS_OSENSOR_H__