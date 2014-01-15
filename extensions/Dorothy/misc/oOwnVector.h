#ifndef __DOROTHY_MISC_OOWNVECTOR_H__
#define __DOROTHY_MISC_OOWNVECTOR_H__

#include "Dorothy/misc/oOwn.h"

NS_DOROTHY_BEGIN

/** @brief vector of pointers, but accessed as values
 pointers pushed into oOwnVector are owned by the vector,
 pointers will be auto deleted when it`s erased/removed from the vector
 or the vector is destroyed.
 Used with Composition Relationship.
*/
template<class T>
class oOwnVector: public vector<oOwn<T>>
{
public:
	inline void push_back(T* item)
	{
		vector<oOwn<T>>::push_back(oOwnMake(item));
	}
	inline iterator insert(const_iterator where, T* item)
	{
		vector<oOwn<T>>::insert(where, oOwnMake(item));
	}
	bool remove(T* item)
	{
		for (auto it = begin();it != end();++it)
		{
			if ((*it) == item)
			{
				oOwnVector<T>::erase(it);
				return true;
			}
		}
		return false;
	}
};

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OOWNVECTOR_H__
