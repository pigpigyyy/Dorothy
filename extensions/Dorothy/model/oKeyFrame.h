/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_MODEL_OKEYFRAME_H__
#define __DOROTHY_MODEL_OKEYFRAME_H__

#include "Dorothy/model/oEase.h"
#include "Dorothy/misc/oMemoryPool.h"

NS_DOROTHY_BEGIN

class oKeyFrameDef;
class oKeyReset: public CCActionInstant
{
public:
	virtual void update(float time);
	virtual CCFiniteTimeAction* reverse();
	virtual CCObject* copyWithZone(CCZone* zone);
	static oKeyReset* create(oKeyFrameDef* def);
private:
	bool _visible;
	float _opacity;
	float _x;
	float _y;
	float _scaleX;
	float _scaleY;
	float _rotation;
	float _skewX;
	float _skewY;
public:
	inline void* operator new(size_t size){ return _memory.alloc(); }
	inline void operator delete(void* ptr, size_t size) { _memory.free(ptr); }
private:
	static oMemoryPool<oKeyReset> _memory;
};

class oKeyPos: public CCActionInterval
{
public:
	void setEase(uint8 easeId);
	bool initWithDuration(float duration, float posX, float posY);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode* pTarget);
	virtual void update(float time);
	void setValue(float endX, float endY);
public:
	static oKeyPos* create(float duration, float posX, float posY, uint8 easeId = 0);
protected:
	oEaseFunc _ease;
	float _startPosX;
	float _startPosY;
	float _endPosX;
	float _endPosY;
	float _deltaPosX;
	float _deltaPosY;
public:
	inline void* operator new(size_t size){ return _memory.alloc(); }
	inline void operator delete(void* ptr, size_t size) { _memory.free(ptr); }
private:
	static oMemoryPool<oKeyPos> _memory;
};

class oKeyScale: public CCActionInterval
{
public:
	void setEase(uint8 easeId);
	bool initWithDuration(float duration, float scaleX, float scaleY);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode* pTarget);
	virtual void update(float time);
	void setValue(float endScaleX, float endScaleY);
public:
	static oKeyScale* create(float duration, float scaleX, float scaleY, uint8 easeId = 0);
	static oKeyScale* create(float duration, float scale, uint8 easeId = 0);
protected:
	oEaseFunc _ease;
	float _startScaleX;
	float _startScaleY;
	float _endScaleX;
	float _endScaleY;
	float _deltaScaleX;
	float _deltaScaleY;
public:
	inline void* operator new(size_t size){ return _memory.alloc(); }
	inline void operator delete(void* ptr, size_t size) { _memory.free(ptr); }
private:
	static oMemoryPool<oKeyScale> _memory;
};

class oKeyRotate: public CCActionInterval
{
public:
	void setEase(uint8 easeId);
	bool initWithDuration(float duration, float rotate);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode* pTarget);
	virtual void update(float time);
	void setValue(float endRotate);
public:
	static oKeyRotate* create(float duration, float rotate, uint8 easeId = 0);
protected:
	oEaseFunc _ease;
	float _startRotate;
	float _endRotate;
	float _deltaRotate;
public:
	inline void* operator new(size_t size){ return _memory.alloc(); }
	inline void operator delete(void* ptr, size_t size) { _memory.free(ptr); }
private:
	static oMemoryPool<oKeyRotate> _memory;
};

class oKeyOpacity: public CCActionInterval
{
public:
	void setEase(uint8 easeId);
	bool initWithDuration(float duration, float opacity);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode* pTarget);
	virtual void update(float time);
	void setValue(float endOpacity);
public:
	static oKeyOpacity* create(float duration, float opacity, uint8 easeId = 0);
protected:
	oEaseFunc _ease;
	float _startOpacity;
	float _endOpacity;
	float _deltaOpacity;
public:
	inline void* operator new(size_t size){ return _memory.alloc(); }
	inline void operator delete(void* ptr, size_t size) { _memory.free(ptr); }
private:
	static oMemoryPool<oKeyOpacity> _memory;
};

class oKeySkew: public CCActionInterval
{
public:
	void setEase(uint8 easeId);
	bool initWithDuration(float duration, float skewX, float skewY);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode* pTarget);
	virtual void update(float time);
	void setValue(float endSkewX, float endSkewY);
public:
	static oKeySkew* create(float duration, float skewX, float skewY, uint8 easeId = 0);
protected:
	oEaseFunc _ease;
	float _startSkewX;
	float _startSkewY;
	float _endSkewX;
	float _endSkewY;
	float _deltaSkewX;
	float _deltaSkewY;
public:
	inline void* operator new(size_t size){ return _memory.alloc(); }
	inline void operator delete(void* ptr, size_t size) { _memory.free(ptr); }
private:
	static oMemoryPool<oKeySkew> _memory;
};

class oKeyRoll: public CCActionInterval
{
public:
	void setEase(uint8 easeId);
	bool initWithDuration(float duration, float roll);
	virtual CCObject* copyWithZone(CCZone* pZone);
	virtual void startWithTarget(CCNode* pTarget);
	virtual void update(float time);
	void setValue(float endRoll);
public:
	static oKeyRoll* create(float duration, float roll, uint8 easeId = 0);
protected:
	oEaseFunc _ease;
	float _startRoll;
	float _endRoll;
	float _deltaRoll;
public:
	inline void* operator new(size_t size){ return _memory.alloc(); }
	inline void operator delete(void* ptr, size_t size) { _memory.free(ptr); }
private:
	static oMemoryPool<oKeyRoll> _memory;
};

NS_DOROTHY_END

#endif // __DOROTHY_MODEL_OKEYFRAME_H__