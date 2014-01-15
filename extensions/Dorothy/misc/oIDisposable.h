#ifndef __DOROTHY_OIDISPOSABLE_H__
#define __DOROTHY_OIDISPOSABLE_H__

#include "Dorothy/const/oDefine.h"

NS_DOROTHY_BEGIN

class oIDisposable;
typedef Delegate<void (oIDisposable* item)> oDisposeHandler;

/** @brief Interface for disposable item. */
class oIDisposable
{
public:
	/** Implement the method to get the item disposed. */
	virtual bool dispose() = 0;
	/** Invoke the delegate when this item is disposing,
	 so others may know it`s being disposed through the delegate. */
	oDisposeHandler disposing;
};

NS_DOROTHY_END

#endif // __DOROTHY_OIDISPOSABLE_H__
