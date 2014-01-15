#include "Dorothy/const/oDefine.h"
#include "Dorothy/misc/oVec2.h"

NS_DOROTHY_BEGIN

oMemoryPool<oVec2> oVec2::_memory;

const oVec2 oVec2::zero;

oVec2::oVec2(float x, float y):
x(x),
y(y)
{ }
oVec2::oVec2(const oVec2& vec):
x(vec.x),
y(vec.y)
{ }
oVec2::oVec2(const b2Vec2& v):
x(v.x),
y(v.y)
{ }
oVec2::oVec2(const CCPoint& p):
x(p.x),
y(p.y)
{ }
void oVec2::set(float x, float y)
{
	x = x;
	y = y;
}
oVec2 oVec2::operator+(const oVec2& vec) const
{
	return oVec2(x + vec.x, y + vec.y);
}
oVec2 oVec2::operator-(const oVec2& vec) const
{
	return oVec2(x - vec.x, y - vec.y);
}
oVec2 oVec2::operator*(float value) const
{
	return oVec2(x * value, y * value);
}
oVec2 oVec2::operator*(const oVec2& vec) const
{
	return oVec2(x * vec.x, y * vec.y);
}
oVec2 oVec2::operator/(float value) const
{
	return oVec2(x / value, y / value);
}
bool oVec2::operator==(const oVec2& vec) const
{
	return x == vec.x && y == vec.y;
}
bool oVec2::operator!=(const oVec2& vec) const
{
	return x != vec.x || y != vec.y;
}
float oVec2::distance(const oVec2& vec) const
{
	float dx = x - vec.x;
	float dy = y - vec.y;
	return sqrtf(dx * dx + dy * dy);
}
float oVec2::distanceSquared(const oVec2& vec) const
{
	float dx = x - vec.x;
	float dy = y - vec.y;
	return dx * dx + dy * dy;
}
float oVec2::length() const
{
	return sqrtf(x * x + y * y);
}
float oVec2::lengthSquared() const
{
	return x * x + y * y;
}
void oVec2::normalize()
{
	float length = oVec2::length();
	x /= length;
	y /= length;
}
float oVec2::angle() const
{
	return atan2f(y, x);
}

NS_DOROTHY_END
