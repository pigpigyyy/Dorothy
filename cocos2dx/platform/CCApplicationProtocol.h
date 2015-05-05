#ifndef __CC_APPLICATION_PROTOCOL_H__
#define __CC_APPLICATION_PROTOCOL_H__

NS_CC_BEGIN

enum TargetPlatform
{
    kTargetWindows,
    kTargetMacOS,
    kTargetAndroid,
    kTargetIphone,
    kTargetIpad,
};

/**
 * @addtogroup platform
 * @{
 */

class CC_DLL CCApplicationProtocol
{
public:
	enum
	{
		EnterBackground,
		EnterForeground,
		LowMemoryWarning,
	};
	CCApplicationProtocol();
	virtual ~CCApplicationProtocol();

	void setScriptHandler(int handler);
	int getScriptHandler() const;

    /**
    @brief    Implement CCDirector and CCScene init code here.
    @return true    Initialize success, app continue.
    @return false   Initialize failed, app terminate.
    */
    virtual bool applicationDidFinishLaunching() = 0;

    /**
    @brief  The function be called when the application enter background
    @param  the pointer of the application
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  The function be called when the application enter foreground
    @param  the pointer of the application
    */
    virtual void applicationWillEnterForeground();

	virtual void applicationDidReceiveMemoryWarning();
    /**
    @brief    Callback by CCDirector for limit FPS.
    @interval       The time, expressed in seconds, between current frame and next. 
    */
    virtual void setAnimationInterval(double interval) = 0;

    /**
    @brief Get current language config
    @return Current language config
    */
    virtual ccLanguageType getCurrentLanguage() = 0;
    
    /**
     @brief Get target platform
     */
    virtual TargetPlatform getTargetPlatform() = 0;
private:
	int _handler;
};

// end of platform group
/// @}

NS_CC_END

#endif    // __CC_APPLICATION_PROTOCOL_H__
