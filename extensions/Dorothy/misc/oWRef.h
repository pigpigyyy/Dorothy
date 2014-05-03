#ifndef __DOROTHY_MISC_OWREF_H__
#define __DOROTHY_MISC_OWREF_H__

NS_DOROTHY_BEGIN

template<class T = CCObject>
class oWRef
{
public:
	oWRef(): _weak(nullptr)
	{ }
	explicit oWRef(T* item): _weak(nullptr)
	{
		if (item)
		{
			_weak = item->getWeakRef();
			_weak->retain();
		}
	}
	oWRef(const oRef<T>& ref): _weak(nullptr)
	{
		if (ref)
		{
			_weak = ref->getWeakRef();
			_weak->retain();
		}
	}
	oWRef(const oWRef& ref): _weak(ref._weak)
	{
		if (_weak)
		{
			_weak->retain();
		}
	}
	oWRef(oWRef&& ref): _weak(ref._weak)
	{
		ref._weak = nullptr;
	}
	~oWRef()
	{
		if (_weak)
		{
			_weak->release();
		}
	}
	inline T* operator->() const
	{
		return get();
	}
	T* operator=(T* item)
	{
		CCWeak* weak = nullptr;
		if (item)
		{
			weak = item->getWeakRef();
			weak->retain();
		}
		if (_weak)
		{
			_weak->release();
		}
		_weak = weak;
		return item;
	}
	const oWRef& operator=(const oRef<T>& ref)
	{
		operator=(ref.get());
		return *this;
	}
	const oWRef& operator=(const oWRef& ref)
	{
		operator=(ref.get());
		return *this;
	}
	const oWRef& operator=(oWRef&& ref)
	{
		if (this == &ref)
		{
			return *this;
		}
		if (_weak)
		{
			_weak->release();
		}
		_weak = ref._weak;
		ref._weak = nullptr;
		return *this;
	}
	bool operator==(const oWRef& ref) const
	{
		return get() == ref.get();
	}
	bool operator!=(const oWRef& ref) const
	{
		return get() != ref.get();
	}
	bool operator==(const oRef<T>& ref) const
	{
		return get() == ref;
	}
	bool operator!=(const oRef<T>& ref) const
	{
		return get() != ref;
	}
	inline operator T*() const
	{
		return get();
	}
	inline T* get() const
	{
		if (_weak) return (T*)_weak->target;
		else return nullptr;
	}
private:
	CCWeak* _weak;
};

template <class name>
inline oWRef<name> oWRefMake(name* item)
{
	return oWRef<name>(item);
}

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OWREF_H__
