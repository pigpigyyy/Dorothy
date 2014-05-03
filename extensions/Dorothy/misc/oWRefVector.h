#ifndef __DOROTHY_MISC_oWREFVECTOR_H__
#define __DOROTHY_MISC_oWREFVECTOR_H__

#include "Dorothy/misc/oWRef.h"

NS_DOROTHY_BEGIN

/** @brief Used with Aggregation Relationship. */
template<class T = CCObject>
class oWRefVector: public vector<oWRef<T>>
{
public:
	inline void push_back(T* item)
	{
		vector<oWRef<T>>::push_back(oWRefMake(item));
	}
	bool insert(size_t where, T* item)
	{
		if (where >= 0 && where < size())
		{
			auto it = begin();
			for (int i = 0; i < where; ++i, ++it);
			vector<oWRef<T>>::insert(it, oWRefMake(item));
			return true;
		}
		return false;
	}
	bool remove(T* item)
	{
		for (auto it = begin();it != end();it++)
		{
			if ((*it) == item)
			{
				erase(it);
				return true;
			}
		}
		return false;
	}
	bool fast_remove(T* item)
	{
		int size = size();
		oWRef<T>* data = data();
		for (int i = 0; i < size; i++)
		{
			if (data[i] == body)
			{
				data[i] = data[size - 1];
				pop_back();
				return true;
			}
		}
		return false;
	}
};

NS_DOROTHY_END

#endif // __DOROTHY_MISC_oWREFVECTOR_H__
