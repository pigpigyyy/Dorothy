/* Copyright (c) 2013 Jin Li, http://www.luvfight.me

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */

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
	inline const string& getName() const { return _name; }
public:
	static oListener* addListener(const string& name, const oEventHandler& handler);
	static void send(const string& name);
	static void clear();
private:
	static void reg(oListener* listener);
	static void unreg(oListener* listener);
	static unordered_map<string, oOwn<oEventType>> _eventMap;
	static oEvent _event;
protected:
	static void send(oEvent* event);
	string _name;
	friend class oListener;
};

NS_DOROTHY_END

#endif //__DOROTHY_EVENT_OEVENT_H__