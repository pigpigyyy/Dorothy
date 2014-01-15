#ifndef __DOROTHY_MISC_OREFVECTOR_H__
#define __DOROTHY_MISC_OREFVECTOR_H__

#include "Dorothy/misc/oRef.h"

NS_DOROTHY_BEGIN

/** @brief Used with Aggregation Relationship. */
template<class T = CCObject>
class oRefVector: public vector<oRef<T>>
{
public:
	inline void push_back(T* item)
	{
		vector<oRef<T>>::push_back(oRefMake(item));
	}
	inline iterator insert(const_iterator where, T* item)
	{
		vector<oRef<T>>::insert(where, oRefMake(item));
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
		oRef<T>* data = data();
		for (int i = 0; i < size; i++)
		{
			if (data[i] == body)
			{
				data[i] = data[_sensedBodies.size() - 1];
				pop_back();
				return true;
			}
		}
		return false;
	}
};

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OREFVECTOR_H__
