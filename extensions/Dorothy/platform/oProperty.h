#ifndef __DOROTHY_PLATFORM_OPROPERTY_H__
#define __DOROTHY_PLATFORM_OPROPERTY_H__

NS_DOROTHY_PLATFORM_BEGIN

class oUnit;

typedef Delegate<void (oUnit* owner, float oldValue, float newValue)> oPropertyHandler;

class oProperty
{
public:
	explicit oProperty(oUnit* owner, float data = 0.0f);
	oProperty(const oProperty& prop);
	oUnit* getOwner() const;
	/** Change its value and not let others know. */
	void reset(float value);
	void operator=(float value);
	void operator+=(float value);
	void operator-=(float value);
	void operator=(const oProperty& prop);
	void operator+=(const oProperty& prop);
	void operator-=(const oProperty& prop);
	bool operator==(const oProperty& prop);
	bool operator!=(const oProperty& prop);
	operator float() const;
	/** Change its value and notice others. */
	oPropertyHandler changed;
private:
	oUnit* _owner;
	float _data;
};

NS_DOROTHY_PLATFORM_END

#endif // __DOROTHY_PLATFORM_OPROPERTY_H__