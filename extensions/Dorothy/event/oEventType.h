#ifndef __DOROTHY_OEVENT_TYPE_H__
#define __DOROTHY_OEVENT_TYPE_H__

NS_DOROTHY_BEGIN

class oEvent;
class oListener;

/** @brief Inner class for event system. */
class oEventType
{
public:
	oEventType(const string& name);
	const string& getName() const;
	void add(oListener* listener);
	void remove(oListener* listener);
	void handle(oEvent* e);
protected:
	string _name;
private:
	vector<oListener*> _listeners;
};

NS_DOROTHY_END

#endif //__DOROTHY_OEVENT_TYPE_H__