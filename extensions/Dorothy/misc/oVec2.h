#ifndef __DOROTHY_MISC_OVEC2_H__
#define __DOROTHY_MISC_OVEC2_H__

#include "Dorothy/misc/oMemoryPool.h"

NS_DOROTHY_BEGIN

class oVec2
{
public:
	oVec2(float x = 0.0f, float y = 0.0f);
	oVec2(const oVec2& vec);
	oVec2(const b2Vec2& v);
	oVec2(const CCPoint& p);
	inline operator b2Vec2() const { return *((b2Vec2*)this); }
	inline operator CCPoint() const { return *((CCPoint*)this); }
	void set(float x, float y);
	oVec2 operator+(const oVec2& vec) const;
	oVec2 operator-(const oVec2& vec) const;
	oVec2 operator*(float value) const;
	oVec2 operator*(const oVec2& vec) const;
	oVec2 operator/(float value) const;
	bool operator==(const oVec2& vec) const;
	bool operator!=(const oVec2& vec) const;
	float distance(const oVec2& vec) const;
	float distanceSquared(const oVec2& vec) const;
	float length() const;
	float lengthSquared() const;
	float angle() const;
	void normalize();
	float x;
	float y;
	static const oVec2 zero;
public:
	inline void* operator new(size_t size) { return _memory.alloc(); }
	inline void operator delete(void* ptr, size_t size) { _memory.free(ptr); }
private:
	static oMemoryPool<oVec2> _memory;
};

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OVEC2_H__