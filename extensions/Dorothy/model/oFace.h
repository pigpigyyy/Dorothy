/* Copyright (c) 2013 Jin Li, http://www.luv-fight.com

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

#ifndef __DOROTHY_OFACE_H__
#define __DOROTHY_OFACE_H__

#include "Dorothy/misc/oIDisposable.h"

NS_DOROTHY_BEGIN

class oParticleDef;

/** @brief Particle which perform well when used as bullet. */
class oParticleSystemQuad: public CCParticleSystemQuad, public oIDisposable
{
public:
	virtual ~oParticleSystemQuad();
	virtual void draw();
	virtual bool dispose();
	static oParticleSystemQuad* createWithDef(oParticleDef* def);
	void childrenDisposed(oIDisposable* item);
protected:
	oParticleSystemQuad();
	bool _isFaceRoot;
	friend class oFace;
};

/** @brief Sprite works with face particle. */
class oSprite: public CCSprite, public oIDisposable
{
public:
	virtual ~oSprite();
	/** Set self visibility and its children`s visibility is not affected. */
	PROPERTY(bool, _isSelfVisible, SelfVisible);
	virtual void draw();
	virtual bool dispose();
	void childrenDisposed(oIDisposable* item);
	static oSprite* createWithTexture(CCTexture2D *pTexture);
	static oSprite* createWithTexture(CCTexture2D *pTexture, const CCRect& rect);
protected:
	oSprite();
private:
	bool _isFaceRoot;
	friend class oFace;
};

/** @brief A face is a combination of sprites and particles.
 When a face is removing, its particles stop emitting and its sprites are all hide.
 And later the entire face is truly removed from memory once it gets totally invisible.  

 Faces can attach to each other just as nodes.

 Faces can only be 4 types:
	oFace::Clip       0
	oFace::Image      1
	oFace::Frame      2
	oFace::Particle   3

 Face is just data define, use toNode() method to get visible instance.
*/
class oFace: public CCObject
{
public:
	enum {Clip = 0, Image = 1, Frame = 2, Particle = 3};
	void addChild(oFace* face);
	bool removeChild(oFace* face);
	/** Get a new instance of the face. */
	CCNode* toNode();
	/** Type of face, Clip, Image, Frame, Particle. */
	uint32 getType() const;
	/** Different type has different faceStr:
	     enum      type             faceStr
          0     oFace::Clip      "loli.clip|0"
          1     oFace::Image     "loli.png"
          2     oFace::Frame     "loli.frame"
          3     oFace::Particle  "loli.particle"
	*/
	static oFace* create(const string& faceStr, const oVec2& point);
private:
	CCNode* load(bool isRoot = false);
	oFace(const string& file, const oVec2& point);
	void visit(CCNode* parent, oFace* current, oParticleSystemQuad*& badChild);
	string _file;
	uint32 _type;
	oVec2 _pos;
	oRefVector<oFace> _children;
	CC_LUA_TYPE(oFace)
};

NS_DOROTHY_END

#endif // __DOROTHY_OFACE_H__