#ifndef __PROPERTY_H__
#define __PROPERTY_H__

template <
	class T,
	class Object,
		typename T (Object::*_getter)()
>
class _RProperty
{
public:
	void operator()(Object* obj)  
	{
		_target = obj;
	}
	T get() const
	{
		return (_target->*_setter)(value);
	}
	operator T() const
	{
		return (_target->*_getter)();
	}
private:
	Object* _target;
};

template <
	class T,
	class Object,
		typename const T& (Object::*_getter)()
>
class _RPropertyRef
{
public:
	void operator()(Object* obj)  
	{
		_target = obj;
	}
	const T& get() const
	{
		return (_target->*_setter)(value);
	}
	operator T() const
	{
		return (_target->*_getter)();
	}
private:
	Object* _target;
};

template <
	class T,
	class Object,
		typename T (Object::*_setter)( T ),
		typename T (Object::*_getter)()
>
class _Property
{
public:
	void operator()(Object* obj)
	{
		_target = obj;
	}
	void set(T value)
	{
		(_target->*_setter)(value);
	}
	T get() const
	{
		return (_target->*_getter)();
	}
	operator T() const 
	{
		return (_target->*_getter)();
	}
	T operator=( T value )
	{
		return (_target->*_setter)(value);
	}
private:
	Object* _target;
};

template <
	class T,
	class Object,
		typename const T& (Object::*_setter)( T const & ),
		typename const T& (Object::*_getter)()
>
class _PropertyRef
{
public:
	void operator()(Object* obj)
	{
		_target = obj;
	}
	void set(const T& value)
	{
		(_target->*_setter)(value);
	}
	const T& get() const
	{
		return (_target->*_getter)();
	}
	operator T() const 
	{
		return (_target->*_getter)();
	}
	T operator=( T const & value )
	{
		return (_target->*_setter)(value);
	}
private:
	Object* _target;
};

template <
	class T,
	class Object,
		typename T (Object::*_setter)( T ),
		typename T (Object::*_getter)(),
		typename T (Object::*_inc)( T ),
		typename T (Object::*_dec)( T )
>
class _PropertyEx
{
public:
	void operator()(Object* obj)
	{
		_target = obj;
	}
	void set(T value)
	{ 
		(_target->*_setter)(value); 
	} 
	T get() const
	{ 
		return (_target->*_setter)(value); 
	}
	operator T() const
	{ 
		return (_target->*_getter)();
	} 
	T operator=( T value ) 
	{ 
		return (_target->*_setter)(value);
	}
	T operator+=( T value )
	{ 
		return (_target->*_inc)(value);
	}
	T operator-=( T value )
	{ 
		return (_target->*_dec)(value);
	}
private:
	Object* _target;
};

template <
	class T,
	class Object,
		typename const T& (Object::*_setter)( T const & ),
		typename const T& (Object::*_getter)(),
		typename const T& (Object::*_inc)( T const & ),
		typename const T& (Object::*_dec)( T const & )
>
class _PropertyRefEx
{
public:
	void operator()(Object* obj)
	{
		_target = obj;
	}
	void set(const T& value)
	{ 
		(_target->*_setter)(value); 
	} 
	const T& get() const
	{ 
		return (_target->*_setter)(value); 
	}
	operator T() const
	{ 
		return (_target->*_getter)();
	} 
	T operator=( T const & value ) 
	{ 
		return (_target->*_setter)(value);
	}
	T operator+=( T const & value )
	{ 
		return (_target->*_inc)(value);
	}
	T operator-=( T const & value )
	{ 
		return (_target->*_dec)(value);
	}
private:
	Object* _target;
};

#define __SET(type, cls, name) type cls::__set##name(type value)
#define __GET(type, cls, name) type cls::__get##name()
#define __INC(type, cls, name) type cls::__inc##name(type value)
#define __DEC(type, cls, name) type cls::__dec##name(type value)

#define __SET_REF(type, cls, name) const type& cls::__set##name(const type& value)
#define __GET_REF(type, cls, name) const type& cls::__get##name()
#define __INC_REF(type, cls, name) const type& cls::__inc##name(const type& value)
#define __DEC_REF(type, cls, name) const type& cls::__dec##name(const type& value)

#define PropertyRefR(type, cls, name) \
	protected:\
	const type& __get##name();\
	public:\
	_RPropertyRef<type, cls, &__get##name> name

#define PropertyRef(type, cls, name) \
	protected:\
	const type& __set##name(const type& value);\
	const type& __get##name();\
	public:\
	_PropertyRef<type, cls, &__set##name, &__get##name> name


#define PropertyRefV(type, cls, name) \
	protected:\
	virtual const type& __set##name(const type& value);\
	virtual const type& __get##name();\
	public:\
	_PropertyRef<type, cls, &__set##name, &__get##name> name

#define PropertyRefEx(type, cls, name) \
	protected:\
	const type& __set##name(const type& value);\
	const type& __get##name();\
	const type& __inc##name(const type& value);\
	const type& __dec##name(const type& value);\
	public:\
	_PropertyEx<type, cls, &__set##name, &__get##name, &__inc##name, &__dec##name> name

#define PropertyRefVEx(type, cls, name) \
	protected:\
	virtual const type& __set##name(const type& value);\
	virtual const type& __get##name();\
	virtual const type& __inc##name(const type& value);\
	virtual const type& __dec##name(const type& value);\
	public:\
	_PropertyEx<type, cls, &__set##name, &__get##name, &__inc##name, &__dec##name> name

#define PropertyR(type, cls, name) \
	protected:\
	const type& __get##name();\
	public:\
	_RProperty<type, cls, &__get##name> name

#define Property(type, cls, name) \
	protected:\
	type __set##name(type value);\
	type __get##name();\
	public:\
	_Property<type, cls, &__set##name, &__get##name> name

#define PropertyV(type, cls, name) \
	protected:\
	virtual type __set##name(type value);\
	virtual type __get##name();\
	public:\
	_Property<type, cls, &__set##name, &__get##name> name

#define PropertyEx(type, cls, name) \
	protected:\
	type __set##name(type value);\
	type __get##name();\
	type __inc##name(type value);\
	type __dec##name(type value);\
	public:\
	_PropertyEx<type, cls, &__set##name, &__get##name, &__inc##name, &__dec##name> name

#define PropertyVEx(type, cls, name) \
	protected:\
	virtual type __set##name(type value);\
	virtual type __get##name();\
	virtual type __inc##name(type value);\
	virtual type __dec##name(type value);\
	public:\
	_PropertyEx<type, cls, &__set##name, &__get##name, &__inc##name, &__dec##name> name

#endif
