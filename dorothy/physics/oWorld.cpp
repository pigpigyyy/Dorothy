/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "const/oDefine.h"
#include "physics/oWorld.h"
#include "physics/oBody.h"
#include "physics/oSensor.h"
#include "physics/oJoint.h"
#include "other/DebugDraw.h"

NS_DOROTHY_BEGIN

void oContactListener::oSensorPair::retain()
{
	sensor->getOwner()->retain();
	sensor->retain();
	body->retain();
}

void oContactListener::oSensorPair::release()
{
	sensor->getOwner()->release();
	sensor->release();
	body->release();
}

void oContactListener::oContactPair::retain()
{
	bodyA->retain();
	bodyB->retain();
}

void oContactListener::oContactPair::release()
{
	bodyA->release();
	bodyB->release();
}

void oWorld::oQueryAABB::setInfo(const CCRect& rc)
{
	transform.Set(b2Vec2(b2Val(rc.getMidX()), b2Val(rc.getMidY())), 0);
	testShape.SetAsBox(b2Val(rc.size.width), b2Val(rc.size.height));
}
bool oWorld::oQueryAABB::ReportFixture( b2Fixture* fixture )
{
	BLOCK_START
	{
		BREAK_IF(fixture->IsSensor());
		b2Shape* shape = fixture->GetShape();
		bool isCommonShape = shape->GetType() != b2Shape::e_chain && shape->GetType() != b2Shape::e_edge;
		BREAK_IF(isCommonShape && !b2TestOverlap(&testShape, 0, shape, 0, transform, fixture->GetBody()->GetTransform()));
		oBody* body = (oBody*)fixture->GetBody()->GetUserData();
		vector<oBody*>& results = isCommonShape ? resultsOfCommonShapes : resultsOfChainsAndEdges;
		if (results.empty() || results.back() != body)
		{
			results.push_back(body);
		}
	}
	BLOCK_END
	return true;
}

float32 oWorld::oRayCast::ReportFixture(b2Fixture* fixture, const b2Vec2& point,
	const b2Vec2& normal, float32 fraction)
{
	result.body = (oBody*)(fixture->GetBody()->GetUserData());
	result.point = point;
	result.normal = normal;
	if (closest)
	{
		return fraction;
	}
	else
	{
		results.push_back(result);
		return 1;
	}
}

float oWorld::b2Factor = 100.0f;

oWorld::oWorld():
_world(b2Vec2(0,-10)),
_velocityIterations(1),
_positionIterations(1),
_contactListner(new oContactListener()),
_contactFilter(new oContactFilter()),
_destructionListener(new oDestructionListener())
{ }

oWorld::~oWorld()
{
	b2Body* b = nullptr;
	if (_world.GetBodyList())
	{
		oRefVector<oBody> bodies;
		while ((b = _world.GetBodyList()) != nullptr)
		{
			oBody* body = (oBody*)b->GetUserData();
			if (body)
			{
				bodies.push_back(body);
				body->cleanup();
			}
		}
	}
	b2Draw* draw = _world.GetDebugDraw();
	CC_SAFE_DELETE(draw);
}

bool oWorld::init()
{
	if (!CCNode::init()) return false;
	_world.SetContactFilter(_contactFilter);
	_world.SetContactListener(_contactListner);
	_world.SetDestructionListener(_destructionListener);
	for (int i = 0; i < 16; i++)
	{
		_filters[i].groupIndex = i;
		_filters[i].categoryBits = 1<<i;
		_filters[i].maskBits = 0;
	}
	CCNode::scheduleUpdate();
	return true;
}

b2World* oWorld::getB2World() const
{
	return const_cast<b2World*>(&_world);
}

void oWorld::setShowDebug(bool var)
{
	if (var)
	{
		if (!_world.GetDebugDraw())
		{
			_world.SetDebugDraw(new GLESDebugDraw());
		}
	}
	else
	{
		b2Draw* draw = _world.GetDebugDraw();
		CC_SAFE_DELETE(draw);
	}
}

bool oWorld::isShowDebug() const
{
	return _world.GetDebugDraw() != nullptr;
}

void oWorld::setIterations( int velocityIter, int positionIter )
{
	_velocityIterations = velocityIter;
	_positionIterations = positionIter;
}

void oWorld::setGravity( const oVec2& gravity )
{
	_world.SetGravity(gravity);
}

oVec2 oWorld::getGravity() const
{
	return _world.GetGravity();
}

void oWorld::update( float dt )
{
	_world.Step(dt, _velocityIterations, _positionIterations);
	for (b2Body* b = _world.GetBodyList();b;b = b->GetNext())
	{
		if (b->IsActive())
		{
			oBody* body = (oBody*)b->GetUserData();
			body->updatePhysics();
		}
	}
	_contactListner->SolveContacts();
	CCNode::update(dt);
}

void oWorld::draw()
{
	GLESDebugDraw* draw = (GLESDebugDraw*)_world.GetDebugDraw();
	if (draw)
	{
		draw->ratio = b2Factor;
		draw->Begin();
		_world.DrawDebugData();
	}
}

void oWorld::visit()
{
	if (!m_bVisible) return;

	kmGLPushMatrix();

	CCNode* transformTarget = CCNode::getTransformTarget();
	if (transformTarget)
	{
		CCDirector::sharedDirector()->projection();
		transformTarget->transformAncestors();
		transformTarget->transform();
	}

	if (m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->beforeDraw();
	}

	this->transform();

	this->sortAllChildren();
	CCObject* pObject;
	CCARRAY_FOREACH(m_pChildren, pObject)
	{
		CCNode* pNode = (CCNode*)pObject;
		if (pNode)
		{
			pNode->visit();
		}
	}

	this->draw();

	if (m_pGrid && m_pGrid->isActive())
	{
		m_pGrid->afterDraw(this);
	}

	kmGLPopMatrix();
}

void oWorld::query( const CCRect& rect, const function<bool(oBody*)>& callback )
{
	b2AABB b2aabb;
	b2aabb.lowerBound.Set(b2Val(rect.getMinX()), b2Val(rect.getMinY()));
	b2aabb.upperBound.Set(b2Val(rect.getMaxX()), b2Val(rect.getMaxY()));
	_queryCallback.setInfo(rect);
	_world.QueryAABB(&_queryCallback, b2aabb);
	for (oBody* item : _queryCallback.resultsOfCommonShapes)
	{
		if (callback(item))
		{
			_queryCallback.resultsOfChainsAndEdges.clear();
			_queryCallback.resultsOfCommonShapes.clear();
			return;
		}
	}
	for (oBody* item : _queryCallback.resultsOfChainsAndEdges)
	{
		if (callback(item)) break;
	}
	_queryCallback.resultsOfChainsAndEdges.clear();
	_queryCallback.resultsOfCommonShapes.clear();
}

void oWorld::cast(const oVec2& start, const oVec2& end, bool closest, const function<bool(oBody*, const oVec2&, const oVec2&)>& callback)
{
	_rayCastCallBack.closest = closest;
	_world.RayCast(&_rayCastCallBack, oWorld::b2Val(start), oWorld::b2Val(end));
	if (_rayCastCallBack.closest)
	{
		oRayCast::oRayCastData& data = _rayCastCallBack.result;
		callback(data.body, data.point, data.normal);
	}
	else
	{
		for (auto& item : _rayCastCallBack.results)
		{
			if (callback(item.body, item.point, item.normal)) break;
		}
	}
	_rayCastCallBack.results.clear();
}

void oWorld::setShouldContact( int groupA, int groupB, bool contact )
{
	b2Filter& filterA = _filters[groupA];
	b2Filter& filterB = _filters[groupB];
	if (contact)
	{
		filterA.maskBits |= filterB.categoryBits;
		filterB.maskBits |= filterA.categoryBits;
	}
	else
	{
		filterA.maskBits &= (~filterB.categoryBits);
		filterB.maskBits &= (~filterA.categoryBits);
	}
	for (b2Body* b = _world.GetBodyList();b;b = b->GetNext())
	{
		b2Fixture* first = b->GetFixtureList();
		if (first)
		{
			int groupIndex = first->GetFilterData().groupIndex;
			if (groupIndex == groupA)
			{
				first->SetFilterData(_filters[groupA]);
			}
			else if (groupIndex == groupB)
			{
				first->SetFilterData(_filters[groupB]);
			}
			// Some shapes make the fixture list a circular list
			for (b2Fixture* f = first->GetNext();f && f != first;f = f->GetNext())
			{
				int groupIndex = f->GetFilterData().groupIndex;
				if (groupIndex == groupA)
				{
					f->SetFilterData(_filters[groupA]);
				}
				else if (groupIndex == groupB)
				{
					f->SetFilterData(_filters[groupB]);
				}
			}
		}
	}
}

bool oWorld::getShouldContact( int groupA, int groupB ) const
{
	const b2Filter& filterA = _filters[groupA];
	const b2Filter& filterB = _filters[groupB];
	return (filterA.maskBits & filterB.categoryBits) && (filterA.categoryBits & filterB.maskBits);
}

const b2Filter& oWorld::getFilter( int group ) const
{
	return _filters[group];
}

void oWorld::setContactListener( oOwn<oContactListener>& listener )
{
	_contactListner = std::move(listener);
}

void oWorld::setContactFilter( oOwn<oContactFilter>& filter )
{
	_contactFilter = std::move(filter);
}

void oContactListener::BeginContact( b2Contact* contact )
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	oBody* bodyA = (oBody*)fixtureA->GetBody()->GetUserData();
	oBody* bodyB = (oBody*)fixtureB->GetBody()->GetUserData();
	if (!bodyA || !bodyB)
	{
		return;
	}
	if (fixtureA->IsSensor())
	{
		oSensor* sensor = (oSensor*)fixtureA->GetUserData();
		if (sensor && sensor->isEnabled() && !fixtureB->IsSensor())
		{
			oSensorPair pair = {sensor, bodyB};
			pair.retain();
			_sensorEnters.push_back(pair);
		}
	}
	else if (fixtureB->IsSensor())
	{
		oSensor* sensor = (oSensor*)fixtureB->GetUserData();
		if (sensor && sensor->isEnabled())
		{
			oSensorPair pair = {sensor, bodyA};
			pair.retain();
			_sensorEnters.push_back(pair);
		}
	}
	else if (bodyA->isReceivingContact() || bodyB->isReceivingContact())
	{
		b2WorldManifold worldManifold;
		contact->GetWorldManifold(&worldManifold);
		oVec2 point = oWorld::oVal(worldManifold.points[0]);
		if (bodyA->isReceivingContact())
		{
			oContactPair pair = { bodyA, bodyB, point, worldManifold.normal };
			pair.retain();
			_contactStarts.push_back(pair);
		}
		if (bodyB->isReceivingContact())
		{
			oContactPair pair = { bodyB, bodyA, point, worldManifold.normal };
			pair.retain();
			_contactStarts.push_back(pair);
		}
	}
}

void oContactListener::EndContact( b2Contact* contact )
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	oBody* bodyA = (oBody*)fixtureA->GetBody()->GetUserData();
	oBody* bodyB = (oBody*)fixtureB->GetBody()->GetUserData();
	if (fixtureA->IsSensor())
	{
		oSensor* sensor = (oSensor*)fixtureA->GetUserData();
		if (sensor && bodyB && sensor->isEnabled() && !fixtureB->IsSensor())
		{
			oSensorPair pair = {sensor, bodyB};
			pair.retain();
			_sensorLeaves.push_back(pair);
		}
	}
	else if (fixtureB->IsSensor())
	{
		oSensor* sensor = (oSensor*)fixtureB->GetUserData();
		if (sensor && bodyA && sensor->isEnabled())
		{
			oSensorPair pair = {sensor, bodyA};
			pair.retain();
			_sensorLeaves.push_back(pair);
		}
	}
	else if (bodyA->isReceivingContact() || bodyB->isReceivingContact())
	{
		b2WorldManifold worldManifold;
		contact->GetWorldManifold(&worldManifold);
		oVec2 point = oWorld::oVal(worldManifold.points[0]);
		if (bodyA->isReceivingContact())
		{
			oContactPair pair = { bodyA, bodyB, point, worldManifold.normal };
			pair.retain();
			_contactEnds.push_back(pair);
		}
		if (bodyB->isReceivingContact())
		{
			oContactPair pair = { bodyB, bodyA, point, worldManifold.normal };
			pair.retain();
			_contactEnds.push_back(pair);
		}
	}
}

void oContactListener::SolveContacts()
{
	if (!_contactStarts.empty())
	{
		for (oContactPair& pair : _contactStarts)
		{
			pair.bodyA->contactStart(pair.bodyB, pair.point, pair.normal);
			pair.release();
		}
		_contactStarts.clear();
	}
	if (!_contactEnds.empty())
	{
		for (oContactPair& pair : _contactEnds)
		{
			pair.bodyA->contactEnd(pair.bodyB, pair.point, pair.normal);
			pair.release();
		}
		_contactEnds.clear();
	}
	if (!_sensorEnters.empty())
	{
		for (oSensorPair& pair: _sensorEnters)
		{
			if (pair.sensor->isEnabled())
			{
				pair.sensor->add(pair.body);
			}
			pair.release();
		}
		_sensorEnters.clear();
	}
	if (!_sensorLeaves.empty())
	{
		for (oSensorPair& pair: _sensorLeaves)
		{
			if (pair.sensor->isEnabled())
			{
				pair.sensor->remove(pair.body);
			}
			pair.release();
		}
		_sensorLeaves.clear();
	}
}

oContactListener::~oContactListener()
{
	for (oSensorPair& pair: _sensorEnters)
	{
		pair.release();
	}
	for (oSensorPair& pair: _sensorLeaves)
	{
		pair.release();
	}
}

bool oContactFilter::ShouldCollide( b2Fixture* fixtureA, b2Fixture* fixtureB )
{
	const b2Filter& filterA = fixtureA->GetFilterData();
	const b2Filter& filterB = fixtureB->GetFilterData();
	return (filterA.maskBits & filterB.categoryBits) && (filterA.categoryBits & filterB.maskBits);
}

void oDestructionListener::SayGoodbye(b2Joint* joint)
{
	oJoint* jointItem = (oJoint*)joint->GetUserData();
	if (jointItem)
	{
		joint->SetUserData(nullptr);
		jointItem->_joint = nullptr;
	}
}
void oDestructionListener::SayGoodbye(b2Fixture* fixture)
{ }

NS_DOROTHY_END
