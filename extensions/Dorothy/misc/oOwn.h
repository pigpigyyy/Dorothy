#ifndef __DOROTHY_MISC_OWN_H__
#define __DOROTHY_MISC_OWN_H__

NS_DOROTHY_BEGIN

/** @brief Used with Composition Relationship. */
template<class Item, class Del = std::default_delete<Item>>
class oOwn: public std::unique_ptr<Item, Del>
{
public:
	oOwn(){}
	oOwn(oOwn&& own):std::unique_ptr<Item>(std::move(own)){}
	explicit oOwn(Item* item):std::unique_ptr<Item>(item){}
	inline operator Item*() const
	{
		return get();
	}
	inline oOwn& operator=(oOwn&& own)
	{
		unique_ptr<Item, Del>::operator=(std::move(own));
		return *this;
	}
	inline operator bool() const
	{
		return get() != nullptr;
	}
private:
	oOwn(const oOwn& own);
};

template<class Item>
class oOwnArray: public std::unique_ptr<Item, std::default_delete<Item[]>>
{
	typedef std::unique_ptr<Item, std::default_delete<Item[]>> oUPtr;
public:
	oOwnArray(){}
	oOwnArray(oOwnArray&& own):oUPtr(std::move(own)){}
	explicit oOwnArray(Item* item):oUPtr(item){}
	inline operator Item*() const
	{
		return get();
	}
	inline oOwnArray& operator=(oOwnArray&& own)
	{
		oUPtr::operator=(std::move(own));
		return *this;
	}
	inline operator bool() const
	{
		return get() != nullptr;
	}
private:
	oOwnArray(const oOwnArray& own);
};

/** Useless */
template<class T>
inline oOwn<T> __oOwnMake(T* item)
{
	return oOwn<T>(item);
}
#define oOwnMake(item) std::move(__oOwnMake(item))
#define oOwnNew(type) std::move(oOwn<type>(new type()))

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OWN_H__