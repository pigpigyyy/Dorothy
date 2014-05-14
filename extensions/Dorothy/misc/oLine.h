#ifndef __DOROTHY_MISC_OLINE_H__
#define __DOROTHY_MISC_OLINE_H__

NS_DOROTHY_BEGIN

class oLine : public CCNode
{
public:
	virtual ~oLine();
	virtual bool init();
	void set(oVec2 vecs[], int count);
	virtual void draw();
	static oLine* create(oVec2 vecs[], int count, const ccColor4B& color);
	static oLine* create();
private:
	oLine();
	ccVertex2F* _buffer;
	size_t _count;
	CC_LUA_TYPE(oLine)
};

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OLINE_H__
