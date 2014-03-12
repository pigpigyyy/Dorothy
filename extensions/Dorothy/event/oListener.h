#ifndef __DOROTHY_OLISTENER_H__
#define __DOROTHY_OLISTENER_H__

NS_DOROTHY_BEGIN

class oEvent;
class oEventType;

typedef Delegate<void (oEvent* event)> oEventHandler;

/** @brief Use event listener to handle event. */
class oListener: public CCObject
{
public:
	~oListener();
	const string& getName() const;
	/** True to receive event and handle it, false to not receive event. */
	void setEnable(bool enable);
	/** Get is registered. */
	bool isEnable() const;
	/** Change the callback delegate. */
	void setHandler(const oEventHandler& handler);
	/** Get callback delegate. */
	const oEventHandler& getHandler() const;
	/** Invoked when event is received. */
	void handle(oEvent* e);
	/** Use it to create a new listener. You may want to get the listener retained for future use. */
	static oListener* create(const string& name, const oEventHandler& handler);
protected:
	oListener(const string& name, const oEventHandler& handler);
	oListener(const string& name, int handler);
	static const int INVALID_ORDER;
	string _name;
	int _order;
	oEventHandler _handler;
	friend class oEventType;
};

NS_DOROTHY_END

#endif //__DOROTHY_OLISTENER_H__
