/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#include "Dorothy/const/oDefine.h"
#include "Dorothy/physics/oBodyDef.h"
#include "Dorothy/physics/oWorld.h"
#include "Dorothy/physics/oBody.h"

NS_DOROTHY_BEGIN

b2ChainShape oBodyDef::_chainShape;
b2CircleShape oBodyDef::_circleShape;
b2PolygonShape oBodyDef::_polygenShape;
b2FixtureDef oBodyDef::_fixtureDef;

oBodyDef::oBodyDef():
angleOffset(0)
{ }

oBodyDef::~oBodyDef()
{
	oBodyDef::clearFixtures();
}

void oBodyDef::attachPolygon( const oVec2& center, float width, float height, float angle, float density, float friction, float restitution )
{
	b2PolygonShape* shape = new b2PolygonShape();
	shape->SetAsBox(oWorld::b2Val(width * 0.5f),
		oWorld::b2Val(height * 0.5f),
		oWorld::b2Val(center),
		-CC_DEGREES_TO_RADIANS(angle));
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;
	fixtureDef->density = density;
	fixtureDef->friction = friction;
	fixtureDef->restitution = restitution;
	_fixtureDefs.push_back(fixtureDef);
}
void oBodyDef::attachPolygon( float width, float height, float density, float friction, float restitution )
{
	b2PolygonShape* shape = new b2PolygonShape();
	shape->SetAsBox(oWorld::b2Val(width * 0.5f), oWorld::b2Val(height * 0.5f));
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;
	fixtureDef->density = density;
	fixtureDef->friction = friction;
	fixtureDef->restitution = restitution;
	_fixtureDefs.push_back(fixtureDef);
}
void oBodyDef::attachPolygon( const vector<oVec2>& vertices, float density, float friction, float restitution )
{
	b2PolygonShape* shape = new b2PolygonShape();
	int length = (int)vertices.size();
	b2Vec2 vs[b2_maxPolygonVertices];
	for (int i = 0; i < length; i++)
	{
	vs[i] = oWorld::b2Val(vertices[i]);
	}
	shape->Set(vs, length);
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;
	fixtureDef->density = density;
	fixtureDef->friction = friction;
	fixtureDef->restitution = restitution;
	_fixtureDefs.push_back(fixtureDef);
}
void oBodyDef::attachPolygon( const oVec2 vertices[], int count, float density, float friction, float restitution )
{
	count = MIN(count, b2_maxPolygonVertices);
	b2PolygonShape* shape = new b2PolygonShape();
	b2Vec2 vs[b2_maxPolygonVertices];
	for (int i = 0; i < count; i++)
	{
		vs[i] = oWorld::b2Val(vertices[i]);
	}
	shape->Set(vs, count);
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;
	fixtureDef->density = density;
	fixtureDef->friction = friction;
	fixtureDef->restitution = restitution;
	_fixtureDefs.push_back(fixtureDef);
}
void oBodyDef::attachLoop( const vector<oVec2>& vertices, float friction, float restitution )
{
	b2ChainShape* shape = new b2ChainShape();
	int length = (int)vertices.size();
	b2Vec2* vs = new b2Vec2[length];
	for (int i = 0; i < length; i++)
	{
		vs[i] = oWorld::b2Val(vertices[i]);
	}
	shape->CreateLoop(vs, length);
	delete [] vs;
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;
	fixtureDef->friction = friction;
	fixtureDef->restitution = restitution;
	_fixtureDefs.push_back(fixtureDef);
}
void oBodyDef::attachLoop( const oVec2 vertices[], int count, float friction, float restitution)
{
	b2ChainShape* shape = new b2ChainShape();
	b2Vec2* vs = new b2Vec2[count];
	for (int i = 0; i < count; i++)
	{
		vs[i] = oWorld::b2Val(vertices[i]);
	}
	shape->CreateLoop(vs, count);
	delete[] vs;
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;
	fixtureDef->friction = friction;
	fixtureDef->restitution = restitution;
	_fixtureDefs.push_back(fixtureDef);
}
void oBodyDef::attachCircle( const oVec2& center, float radius, float density, float friction, float restitution )
{
	b2CircleShape* shape = new b2CircleShape();
	shape->m_p = oWorld::b2Val(center);
	shape->m_radius = oWorld::b2Val(radius);
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;
	fixtureDef->density = density;
	fixtureDef->friction = friction;
	fixtureDef->restitution = restitution;
	_fixtureDefs.push_back(fixtureDef);
}
void oBodyDef::attachCircle( float radius, float density, float friction, float restitution )
{
	oBodyDef::attachCircle(oVec2(0,0), radius, density, friction, restitution);
}
void oBodyDef::attachChain( const vector<oVec2>& vertices, float friction, float restitution )
{
	b2ChainShape* shape = new b2ChainShape();
	int length = (int)vertices.size();
	b2Vec2* vs = new b2Vec2[length];
	for (int i = 0; i < length; i++)
	{
		vs[i] = oWorld::b2Val(vertices[i]);
	}
	shape->CreateChain(vs, length);
	delete [] vs;
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;
	fixtureDef->friction = friction;
	fixtureDef->restitution = restitution;
	_fixtureDefs.push_back(fixtureDef);
}
void oBodyDef::attachChain(const oVec2 vertices[], int count, float friction, float restitution)
{
	b2ChainShape* shape = new b2ChainShape();
	b2Vec2* vs = new b2Vec2[count];
	for (int i = 0; i < count; i++)
	{
		vs[i] = oWorld::b2Val(vertices[i]);
	}
	shape->CreateChain(vs, count);
	delete[] vs;
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;
	fixtureDef->friction = friction;
	fixtureDef->restitution = restitution;
	_fixtureDefs.push_back(fixtureDef);
}
void oBodyDef::attachPolygonSensor( int tag, float width, float height )
{
	oBodyDef::attachPolygonSensor(tag, width, height, oVec2(0,0), 0);
}
void oBodyDef::attachPolygonSensor( int tag, float width, float height, const oVec2& center, float angle )
{
	b2PolygonShape* shape = new b2PolygonShape();
	shape->SetAsBox(oWorld::b2Val(width * 0.5f),
		oWorld::b2Val(height * 0.5f),
		oWorld::b2Val(center),
		-CC_DEGREES_TO_RADIANS(angle));
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;
	fixtureDef->isSensor = true;
	fixtureDef->userData = (void*)(long)tag;
	_fixtureDefs.push_back(fixtureDef);
}
void oBodyDef::attachPolygonSensor( int tag, const vector<oVec2>& vertices )
{
	b2PolygonShape* shape = new b2PolygonShape();
	int length = (int)vertices.size();
	b2Vec2 vs[b2_maxPolygonVertices];
	for (int i = 0; i < length; i++)
	{
		vs[i] = oWorld::b2Val(vertices[i]);
	}
	shape->Set(vs, length);
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;
	fixtureDef->isSensor = true;
	fixtureDef->userData = (void*)(long)tag;
	_fixtureDefs.push_back(fixtureDef);
}
void oBodyDef::attachPolygonSensor(int tag, const oVec2 vertices[], int count)
{
	b2PolygonShape* shape = new b2PolygonShape();
	b2Vec2 vs[b2_maxPolygonVertices];
	for (int i = 0; i < count; i++)
	{
		vs[i] = oWorld::b2Val(vertices[i]);
	}
	shape->Set(vs, count);
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;
	fixtureDef->isSensor = true;
	fixtureDef->userData = (void*)(long)tag;
	_fixtureDefs.push_back(fixtureDef);
}
void oBodyDef::attachCircleSensor( int tag, const oVec2& center, float radius )
{
	b2CircleShape* shape = new b2CircleShape();
	shape->m_p = oWorld::b2Val(center);
	shape->m_radius = oWorld::b2Val(radius);
	b2FixtureDef* fixtureDef = new b2FixtureDef();
	fixtureDef->shape = shape;
	fixtureDef->isSensor = true;
	fixtureDef->userData = (void*)(long)tag;
	_fixtureDefs.push_back(fixtureDef);
}
void oBodyDef::attachCircleSensor( int tag, float radius )
{
	oBodyDef::attachCircleSensor(tag, oVec2(0,0), radius);
}

b2FixtureDef* oBodyDef::polygon( const oVec2& center, float width, float height, float angle, float density, float friction, float restitution )
{
	_polygenShape.SetAsBox(oWorld::b2Val(width * 0.5f), oWorld::b2Val(height * 0.5f), oWorld::b2Val(center), -CC_DEGREES_TO_RADIANS(angle));
	_fixtureDef.shape = &_polygenShape;
	_fixtureDef.density = density;
	_fixtureDef.friction = friction;
	_fixtureDef.restitution = restitution;
	return &_fixtureDef;
}
b2FixtureDef* oBodyDef::polygon( float width, float height, float density, float friction, float restitution )
{
	_polygenShape.SetAsBox(oWorld::b2Val(width * 0.5f), oWorld::b2Val(height * 0.5f));
	_fixtureDef.shape = &_polygenShape;
	_fixtureDef.density = density;
	_fixtureDef.friction = friction;
	_fixtureDef.restitution = restitution;
	return &_fixtureDef;
}
b2FixtureDef* oBodyDef::polygon( const vector<oVec2>& vertices, float density, float friction, float restitution )
{
	int length = (int)vertices.size();
	b2Vec2 vs[b2_maxPolygonVertices];
	for (int i = 0; i < length; i++)
	{
		vs[i] = oWorld::b2Val(vertices[i]);
	}
	_polygenShape.Set(vs, length);
	_fixtureDef.shape = &_polygenShape;
	_fixtureDef.density = density;
	_fixtureDef.friction = friction;
	_fixtureDef.restitution = restitution;
	return &_fixtureDef;
}
b2FixtureDef* oBodyDef::polygon( const oVec2 vertices[], int count, float density, float friction, float restitution )
{
	b2Vec2 vs[b2_maxPolygonVertices];
	for (int i = 0; i < count; i++)
	{
		vs[i] = oWorld::b2Val(vertices[i]);
	}
	_polygenShape.Set(vs, count);
	_fixtureDef.shape = &_polygenShape;
	_fixtureDef.density = density;
	_fixtureDef.friction = friction;
	_fixtureDef.restitution = restitution;
	return &_fixtureDef;
}
b2FixtureDef* oBodyDef::loop( const vector<oVec2>& vertices, float friction, float restitution )
{
	_chainShape.ClearVertices();
	int length = (int)vertices.size();
	b2Vec2* vs = new b2Vec2[length];
	for (int i = 0; i < length; i++)
	{
		vs[i] = oWorld::b2Val(vertices[i]);
	}
	_chainShape.CreateLoop(vs, length);
	delete [] vs;
	_fixtureDef.shape = &_chainShape;
	_fixtureDef.friction = friction;
	_fixtureDef.restitution = restitution;
	return &_fixtureDef;
}
b2FixtureDef* oBodyDef::loop(const oVec2 vertices[], int count, float friction, float restitution)
{
	_chainShape.ClearVertices();
	b2Vec2* vs = new b2Vec2[count];
	for (int i = 0; i < count; i++)
	{
		vs[i] = oWorld::b2Val(vertices[i]);
	}
	_chainShape.CreateLoop(vs, count);
	delete[] vs;
	_fixtureDef.shape = &_chainShape;
	_fixtureDef.friction = friction;
	_fixtureDef.restitution = restitution;
	return &_fixtureDef;
}
b2FixtureDef* oBodyDef::circle( const oVec2& center, float radius, float density, float friction, float restitution )
{
	_circleShape.m_p = oWorld::b2Val(center);
	_circleShape.m_radius = oWorld::b2Val(radius);
	_fixtureDef.shape = &_circleShape;
	_fixtureDef.density = density;
	_fixtureDef.friction = friction;
	_fixtureDef.restitution = restitution;
	return &_fixtureDef;
}
b2FixtureDef* oBodyDef::circle( float radius, float density, float friction, float restitution )
{
	return oBodyDef::circle(oVec2(0,0), radius, density, friction, restitution);
}
b2FixtureDef* oBodyDef::chain( const vector<oVec2>& vertices, float friction, float restitution )
{
	_chainShape.ClearVertices();
	int length = (int)vertices.size();
	b2Vec2* vs = new b2Vec2[length];
	for (int i = 0; i < length; i++)
	{
		vs[i] = oWorld::b2Val(vertices[i]);
	}
	_chainShape.CreateChain(vs, length);
	delete [] vs;
	_fixtureDef.shape = &_chainShape;
	_fixtureDef.friction = friction;
	_fixtureDef.restitution = restitution;
	return &_fixtureDef;
}
b2FixtureDef* oBodyDef::chain(const oVec2 vertices[], int count, float friction, float restitution)
{
	_chainShape.ClearVertices();
	b2Vec2* vs = new b2Vec2[count];
	for (int i = 0; i < count; i++)
	{
		vs[i] = oWorld::b2Val(vertices[i]);
	}
	_chainShape.CreateChain(vs, count);
	delete[] vs;
	_fixtureDef.shape = &_chainShape;
	_fixtureDef.friction = friction;
	_fixtureDef.restitution = restitution;
	return &_fixtureDef;
}

oBodyDef* oBodyDef::create()
{
	oBodyDef* bodyDef = new oBodyDef();
	bodyDef->autorelease();
	return bodyDef;
}

const oOwnVector<b2FixtureDef>& oBodyDef::getFixtureDefs() const
{
	return _fixtureDefs;
}

void oBodyDef::clearFixtures()
{
	for (b2FixtureDef* fixtureDef : _fixtureDefs)
	{
		delete fixtureDef->shape;
		fixtureDef->shape = nullptr;
	}
	_fixtureDefs.clear();
}

void oBodyDef::setDensity(float var)
{
	for (b2FixtureDef* fixtureDef : _fixtureDefs)
	{
		if (!fixtureDef->isSensor)
		{
			fixtureDef->density = var;
		}
	}
}
void oBodyDef::setFriction(float var)
{
	for (b2FixtureDef* fixtureDef : _fixtureDefs)
	{
		if (!fixtureDef->isSensor)
		{
			fixtureDef->friction = var;
		}
	}
}
void oBodyDef::setRestitution(float var)
{
	for (b2FixtureDef* fixtureDef : _fixtureDefs)
	{
		if (!fixtureDef->isSensor)
		{
			fixtureDef->restitution = var;
		}
	}
}

NS_DOROTHY_END
