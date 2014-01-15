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
	virtual void PostSolve( b2Contact* contact, const b2ContactImpulse* impulse );
	virtual void PreSolve( b2Contact* contact, const b2Manifold* oldManifold );
	virtual void BeginContact( b2Contact* contact );
	virtual void EndContact( b2Contact* contact );
	void SolveSensors();
protected:
	struct oSensorPair
	{
		oSensor* sensor;
		oBody* body;
		void retain();
		void release();
	};
	vector<oSensorPair> _sensorEnters;
	vector<oSensorPair> _sensorLeaves;
};

class oContactFilter: public b2ContactFilter
{
	virtual bool ShouldCollide( b2Fixture* fixtureA, b2Fixture* fixtureB );
};

class oWorld: public CCLayer
{
public:
	oWorld();
	virtual ~oWorld();
	b2World* getB2World();
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
	/**
	 Use this rect query at any time without worrying Box2D`s callback limits.
	 */
	void query(const CCRect& rect, const function<bool(oBody*)>& callback);
	void setShouldContact(int groupA, int groupB, bool contact);
	bool getShouldContact(int groupA, int groupB) const;
	const b2Filter& getFilter(int group) const;
	static inline float oVal(float value){ return value * b2Factor; }
	static inline b2Vec2 oVal(const b2Vec2& value){ return b2Vec2(value.x * b2Factor, value.y * b2Factor); }
	static inline oVec2 oVal(const oVec2& value){ return value * b2Factor; }
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
protected:
	class oQueryAABB: public b2QueryCallback
	{
	public:
		vector<oBody*> results;
		virtual bool ReportFixture( b2Fixture* fixture );
	} _queryCallback;
private:
	b2Filter _filters[16];
	b2World _world;
	oOwn<oContactListener> _contactListner;
	oOwn<oContactFilter> _contactFilter;
	int _velocityIterations;
	int _positionIterations;
};

NS_DOROTHY_END

#endif // __DOROTHY_PHYSICS_OWORLD_H__
