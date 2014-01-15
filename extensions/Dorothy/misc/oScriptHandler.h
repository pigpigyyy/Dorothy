#ifndef __DOROTHY_MISC_OSCRIPTHANDLER_H__
#define __DOROTHY_MISC_OSCRIPTHANDLER_H__

NS_DOROTHY_BEGIN


class oScriptHandler: public CCObject
{
public:
	~oScriptHandler();
	static oScriptHandler* create(int handler);
	int get() const;
private:
	oScriptHandler(int handler);
	int _handler;
};

class oHandlerWrapper
{
public:
	oHandlerWrapper(int handler);
	bool operator==(const oHandlerWrapper& handler) const;
	int getHandler() const;
private:
	oRef<oScriptHandler> _handler;
};
#define HANDLER_WRAP_START(type) class type: public oHandlerWrapper\
{\
public:\
	type(int handler):oHandlerWrapper(handler){}\
	const type& operator*() const {return *this;}

#define HANDLER_WRAP_END };

NS_DOROTHY_END

#endif // __DOROTHY_MISC_OSCRIPTHANDLER_H__