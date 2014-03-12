#ifndef __DOROTHY_EVENT_OEVENT_H__
#define __DOROTHY_EVENT_OEVENT_H__

NS_DOROTHY_BEGIN

class oListener;
class oEventType;
class oEvent;
typedef Delegate<void (oEvent* event)> oEventHandler;

/** @brief The event system is associate with event,
 event type and event listener.Use the system as following.
 @example // Self defined event.
 class MyEvent: public oEvent
 {
	public:
		int arg;
		void send(const string& name, int arg)
		{
			_event._name = name;
			_event.arg = arg;
			oEvent::send(&_event);
		}
	private:
		static MyEvent _event;
 };
 
 // Event callback function.
 void onMyEvent(oEvent* e)
 {
	MyEvent* myEvent = (MyEvent*)e;
	//Do something.
 }

 // Name your new event.
 const string MYEVENT_A = "EventA";

 // Register for event.
 _listener = MyEvent::addListener(MYEVENT_A, onMyEvent);
 _listener->retain();

 // Send event, then the callback function should be invoked.
 MyEvent::send(MYEVENT_A, 123);
*/
class oEvent
{
public:
	oEvent();
	oEvent(const string& name);
	inline const string& getName() const;
public:
	static void addType(const string& name);
	static bool removeType(const string& name);
	static oListener* addListener(const string& name, const oEventHandler& handler);
	static void send(const string& name);
private:
	static void reg(oListener* listener);
	static void unreg(oListener* listener);
	static hash_strmap<oOwn<oEventType>> _eventMap;
	static oEvent _event;
protected:
	static void send(oEvent* event);
	string _name;
	friend class oListener;
};

NS_DOROTHY_END

#endif //__DOROTHY_EVENT_OEVENT_H__