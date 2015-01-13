/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_PHYSICS_OWORLD_H__
#define __DOROTHY_PHYSICS_OWORLD_H__

NS_DOROTHY_BEGIN

class oBody;
class oSensor;

class oContactListener: public b2ContactListener
{
public:
	virtual ~oContactListener();
	/**
	 In subclass functions first call these functions from the base class,
	 then do your extra works. 
	 */
	virtual void BeginContact( b2Contact* contact );
	virtual void EndContact( b2Contact* contact );
	void SolveSensors();

	struct oSensorPair
	{
		oSensor* sensor;
		oBody* body;
		void retain();
		void release();
	};
	struct oContactPair
	{
		oBody* bodyA;
		oBody* bodyB;
		oVec2 point;
		oVec2 normal;
		void retain();
		void release();
	};
protected:
	vector<oSensorPair> _sensorEnters;
	vector<oSensorPair> _sensorLeaves;
	vector<oContactPair> _contactStarts;
	vector<oContactPair> _contactEnds;
};

class oContactFilter: public b2ContactFilter
{
	virtual bool ShouldCollide( b2Fixture* fixtureA, b2Fixture* fixtureB );
};

class oDestructionListener: public b2DestructionListener
{
public:
	virtual void SayGoodbye(b2Joint* joint);
	virtual void SayGoodbye(b2Fixture* fixture);
};

class oWorld: public CCNode
{
public:
	oWorld();
	virtual ~oWorld();
	PROPERTY_READONLY(b2World*, B2World);
	PROPERTY_BOOL_NAME(ShowDebug);
	/**
	 Iterations affect Box2D`s CPU cost greatly.
	 Lower values to get better speed, high value to get better simulation.
	 Default are the minimum value 1,1.
	 */
	void setIterations(int velocityIter, int positionIter);
	/**
	 You can change the contact listener with a subclass of oContactListener with
	 world->setContactListener(oOwnNew(MyContactListener));
	 */
	void setContactListener(oOwn<oContactListener>& listener);
	/**
	 You can change the contact filter with a subclass of oContactFilter with
	 world->setContactFilter(oOwnNew(MyContactFilter));
	 */
	void setContactFilter(oOwn<oContactFilter>& filter);
	void setGravity(const oVec2& gravity);
	oVec2 getGravity() const;
	virtual void update(float dt);
	virtual void draw();
	virtual void visit();
	/**
	 Use this rect query at any time without worrying Box2D`s callback limits.
	 */
	void query(const CCRect& rect, const function<bool(oBody*)>& callback);
	void cast(const oVec2& start, const oVec2& end, bool closest, const function<bool(oBody*, const oVec2&, const oVec2&)>& callback);
	void setShouldContact(int groupA, int groupB, bool contact);
	bool getShouldContact(int groupA, int groupB) const;
	const b2Filter& getFilter(int group) const;
	static inline float oVal(float value){ return value * b2Factor; }
	static inline oVec2 oVal(const b2Vec2& value){ return oVec2(value.x * b2Factor, value.y * b2Factor); }
	static inline float b2Val(float value){ return value / b2Factor; }
	static inline b2Vec2 b2Val(const b2Vec2& value){ return b2Vec2(value.x / b2Factor, value.y / b2Factor); }
	static inline b2Vec2 b2Val(const CCPoint& value){ return b2Vec2(value.x / b2Factor, value.y / b2Factor); }
	static inline b2Vec2 b2Val(const oVec2& value){ return value / b2Factor; }
	/**
	 b2Factor is to convert Box2D meters value to pixel value.
	 Default 100.0f is a good value since Box2D can well simulate real life objects
	 between 0.1 to 10 meters. Use value 100.0f we can well simulate game objects
	 between 10 to 1000 pixels that suite most games.
	 Better change this value before any body creation.
	 */
	static float b2Factor;
	CREATE_FUNC(oWorld);
private:
	class oQueryAABB: public b2QueryCallback
	{
	public:
		vector<oBody*> results;
		virtual bool ReportFixture( b2Fixture* fixture );
	} _queryCallback;
	class oRayCast: public b2RayCastCallback
	{
	public:
		struct oRayCastData
		{
			oBody* body;
			b2Vec2 point;
			b2Vec2 normal;
		} result;
		vector<oRayCastData> results;
		bool closest;
		virtual float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
			const b2Vec2& normal, float32 fraction);
	} _rayCastCallBack;
private:
	b2Filter _filters[16];
	b2World _world;
	oOwn<oContactListener> _contactListner;
	oOwn<oContactFilter> _contactFilter;
	oOwn<oDestructionListener> _destructionListener;
	int _velocityIterations;
	int _positionIterations;
	CC_LUA_TYPE(oWorld)
};

NS_DOROTHY_END

#endif // __DOROTHY_PHYSICS_OWORLD_H__
