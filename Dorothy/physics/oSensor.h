/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

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
	CC_LUA_TYPE(oSensor)
};

NS_DOROTHY_END

#endif // __DOROTHY_PHYSICS_OSENSOR_H__