#ifndef __CC_APPLICATION_WIN32_H__
#define __CC_APPLICATION_WIN32_H__

#include "CCStdC.h"
#include "platform/CCCommon.h"
#include "platform/CCApplicationProtocol.h"
#include <string>

NS_CC_BEGIN

class CCRect;
class CCScriptHandlerEntry;

class CC_DLL CCApplication : public CCApplicationProtocol
{
public:
	enum { EnterForeground, EnterBackground };
    CCApplication();
    virtual ~CCApplication();

    /**
    @brief    Run the message loop.
    */
    int run();
	void registerEventHandler(int handler);
	void unregisterEventHandler();
	virtual void applicationDidEnterBackground();
	virtual void applicationWillEnterForeground();
    /* override functions */
    virtual void setAnimationInterval(double interval);
    virtual ccLanguageType getCurrentLanguage();
    
    /**
     @brief Get target platform
     */
    virtual TargetPlatform getTargetPlatform();

	/**
	@brief    Get current applicaiton instance.
	@return Current application instance pointer.
	*/
	static CCApplication* sharedApplication();
protected:
	CCScriptHandlerEntry* m_scriptHandler;
    HINSTANCE           m_hInstance;
    HACCEL              m_hAccelTable;
    LARGE_INTEGER       m_nAnimationInterval;
    std::string         m_resourceRootPath;
    std::string         m_startupScriptFilename;

    static CCApplication * sm_pSharedApplication;
};

NS_CC_END

#endif    // __CC_APPLICATION_WIN32_H__
