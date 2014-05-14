/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef __CCLAYER_H__
#define __CCLAYER_H__

#include "base_nodes/CCNode.h"
#include "CCProtocols.h"
#include "touch_dispatcher/CCTouchDelegateProtocol.h"
#include "platform/CCAccelerometerDelegate.h"
#include "keypad_dispatcher/CCKeypadDelegate.h"
#include "cocoa/CCArray.h"

NS_CC_BEGIN
/**
 * @addtogroup layer
 * @{
 */

class CCTouchScriptHandlerEntry;

//
// CCLayer
//
/** @brief CCLayer is a subclass of CCNode that implements the TouchEventsDelegate protocol.

All features from CCNode are valid, plus the following new features:
- It can receive iPhone Touches
- It can receive Accelerometer input
*/
class CC_DLL CCLayer : public CCNode, public CCTouchDelegate, public CCAccelerometerDelegate, public CCKeypadDelegate
{
public:
	enum
	{
		TouchesAllAtOnce,
		TouchesOneByOne
	};
	CCLayer();
    virtual ~CCLayer();
    virtual bool init();
    
    /** create one layer */
    static CCLayer *create();

    virtual void onEnter();
    virtual void onExit();
    virtual void onEnterTransitionDidFinish();
    
    // default implements are used to call script callback if exist
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    // default implements are used to call script callback if exist
    virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);
    virtual void ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent);
    
    virtual void didAccelerate(CCAcceleration* pAccelerationValue);
    void registerScriptAccelerateHandler(int nHandler);
    void unregisterScriptAccelerateHandler();

    /** If isTouchEnabled, this method is called onEnter. Override it to change the
    way CCLayer receives touch events.
    ( Default: CCTouchDispatcher::sharedDispatcher()->addStandardDelegate(this,0); )
    Example:
    void CCLayer::registerWithTouchDispatcher()
    {
    CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,INT_MIN+1,true);
    }
    @since v0.8.0
    */
    virtual void registerWithTouchDispatcher();
    
    /** Register script touch events handler */
    virtual void registerScriptTouchHandler(int nHandler, bool bIsMultiTouches = false, int nPriority = INT_MIN, bool bSwallowsTouches = false);
    /** Unregister script touch events handler */
    virtual void unregisterScriptTouchHandler();

    /** whether or not it will receive Touch events.
    You can enable / disable touch events with this property.
    Only the touches of this node will be affected. This "method" is not propagated to it's children.
    @since v0.8.1
    */
    virtual bool isTouchEnabled();
    virtual void setTouchEnabled(bool value);
    
    virtual void setTouchMode(int mode);
    virtual int getTouchMode();
    
    /** priority of the touch events. Default is 0 */
    virtual void setTouchPriority(int priority);
    virtual int getTouchPriority();

    /** whether or not it will receive Accelerometer events
    You can enable / disable accelerometer events with this property.
    @since v0.8.1
    */
    virtual bool isAccelerometerEnabled();
    virtual void setAccelerometerEnabled(bool value);
    virtual void setAccelerometerInterval(double interval);

    /** whether or not it will receive keypad events
    You can enable / disable accelerometer events with this property.
    it's new in cocos2d-x
    */
    virtual bool isKeypadEnabled();
    virtual void setKeypadEnabled(bool value);

    /** Register keypad events handler */
    void registerScriptKeypadHandler(int nHandler);
    /** Unregister keypad events handler */
    void unregisterScriptKeypadHandler();

    virtual void keyBackClicked();
    virtual void keyMenuClicked();
    
    inline CCTouchScriptHandlerEntry* getScriptTouchHandlerEntry() { return m_pScriptTouchHandlerEntry; };
    inline CCScriptHandlerEntry* getScriptKeypadHandlerEntry() { return m_pScriptKeypadHandlerEntry; };
    inline CCScriptHandlerEntry* getScriptAccelerateHandlerEntry() { return m_pScriptAccelerateHandlerEntry; };
protected:
    bool m_bTouchEnabled;
    bool m_bAccelerometerEnabled;
    bool m_bKeypadEnabled;
    
private:
    // Script touch events handler
    CCTouchScriptHandlerEntry* m_pScriptTouchHandlerEntry;
    CCScriptHandlerEntry* m_pScriptKeypadHandlerEntry;
    CCScriptHandlerEntry* m_pScriptAccelerateHandlerEntry;
    
    int m_nTouchPriority;
    int m_eTouchMode;
    
    int  excuteScriptTouchHandler(int nEventType, CCTouch *pTouch);
    int  excuteScriptTouchHandler(int nEventType, CCSet *pTouches);
	CC_LUA_TYPE(CCLayer)
};

//
// CCLayerColor
//
/** @brief CCLayerColor is a subclass of CCLayer that implements the CCRGBAProtocol protocol.

All features from CCLayer are valid, plus the following new features:
- opacity
- RGB colors
*/
class CC_DLL CCLayerColor : public CCLayer, public CCBlendProtocol
{
protected:
    ccVertex2F m_pSquareVertices[4];
    ccColor4F  m_pSquareColors[4];

public:
    CCLayerColor();
    virtual ~CCLayerColor();

    virtual void draw();
    virtual void setContentSize(const CCSize & var);
    
    static CCLayerColor* create();
    
    /** creates a CCLayer with color, width and height in Points */
    static CCLayerColor * create(const ccColor4B& color, GLfloat width, GLfloat height);
    /** creates a CCLayer with color. Width and height are the window size. */
    static CCLayerColor * create(const ccColor4B& color);

    virtual bool init();
    /** initializes a CCLayer with color, width and height in Points */
    virtual bool initWithColor(const ccColor4B& color, GLfloat width, GLfloat height);
    /** initializes a CCLayer with color. Width and height are the window size. */
    virtual bool initWithColor(const ccColor4B& color);

    /** change width in Points*/
    void changeWidth(GLfloat w);
    /** change height in Points*/
    void changeHeight(GLfloat h);
    /** change width and height in Points
    @since v0.8
    */
    void changeWidthAndHeight(GLfloat w ,GLfloat h);

    /** BlendFunction. Conforms to CCBlendProtocol protocol */
    CC_PROPERTY(ccBlendFunc, m_tBlendFunc, BlendFunc)

    virtual void setColor(const ccColor3B &color);
    virtual void setOpacity(float opacity);
	virtual void updateDisplayedOpacity(float parentOpacity);
	virtual void updateDisplayedColor(const ccColor3B& parentColor);

protected:
    virtual void updateColor();
	CC_LUA_TYPE(CCLayerColor)
};

//
// CCLayerGradient
//
/** @brief CCLayerGradient is a subclass of CCLayerColor that draws gradients across the background.

All features from CCLayerColor are valid, plus the following new features:
- direction
- final color
- interpolation mode

Color is interpolated between the startColor and endColor along the given
vector (starting at the origin, ending at the terminus).  If no vector is
supplied, it defaults to (0, -1) -- a fade from top to bottom.

If 'compressedInterpolation' is disabled, you will not see either the start or end color for
non-cardinal vectors; a smooth gradient implying both end points will be still
be drawn, however.

If ' compressedInterpolation' is enabled (default mode) you will see both the start and end colors of the gradient.

@since v0.99.5
*/
class CC_DLL CCLayerGradient : public CCLayerColor
{
public:

    /** Creates a full-screen CCLayer with a gradient between start and end. */
    static CCLayerGradient* create(const ccColor4B& start, const ccColor4B& end);

    /** Creates a full-screen CCLayer with a gradient between start and end in the direction of v. */
    static CCLayerGradient* create(const ccColor4B& start, const ccColor4B& end, const CCPoint& v);

    virtual bool init();
    /** Initializes the CCLayer with a gradient between start and end. */
    virtual bool initWithColor(const ccColor4B& start, const ccColor4B& end);

    /** Initializes the CCLayer with a gradient between start and end in the direction of v. */
    virtual bool initWithColor(const ccColor4B& start, const ccColor4B& end, const CCPoint& v);

    CC_PROPERTY_PASS_BY_REF(ccColor3B, m_startColor, StartColor)
    CC_PROPERTY_PASS_BY_REF(ccColor3B, m_endColor, EndColor)
    CC_PROPERTY(float, m_cStartOpacity, StartOpacity)
    CC_PROPERTY(float, m_cEndOpacity, EndOpacity)
    CC_PROPERTY_PASS_BY_REF(CCPoint, m_AlongVector, Vector)

    /** Whether or not the interpolation will be compressed in order to display all the colors of the gradient both in canonical and non canonical vectors
    Default: YES
    */
protected:
    bool m_bCompressedInterpolation;
public:
    virtual void setCompressedInterpolation(bool bCompressedInterpolation);
    virtual bool isCompressedInterpolation();
    
    static CCLayerGradient* create();

protected:
    virtual void updateColor();
	CC_LUA_TYPE(CCLayerGradient)
};


/** @brief CCMultipleLayer is a CCLayer with the ability to multiplex it's children.
Features:
- It supports one or more children
- Only one children will be active a time
*/
class CC_DLL CCLayerMultiplex : public CCLayer
{
protected:
    unsigned int m_nEnabledLayer;
    CCArray*     m_pLayers;
public:
    CCLayerMultiplex();
    virtual ~CCLayerMultiplex();
    
    static CCLayerMultiplex* create();
    
    /** creates a CCMultiplexLayer with an array of layers.
     @since v2.1
     */
    static CCLayerMultiplex* createWithArray(CCArray* arrayOfLayers);

    /** creates a CCLayerMultiplex with one or more layers using a variable argument list. */
    static CCLayerMultiplex * create(CCLayer* layer, ... );

    /**
     * lua script can not init with undetermined number of variables
     * so add these functions to be used with lua.
     */
    static CCLayerMultiplex * createWithLayer(CCLayer* layer);

    void addLayer(CCLayer* layer);

    /** initializes a MultiplexLayer with one or more layers using a variable argument list. */
    bool initWithLayers(CCLayer* layer, va_list params);
    /** switches to a certain layer indexed by n. 
    The current (old) layer will be removed from it's parent with 'cleanup:YES'.
    */

    /** initializes a CCMultiplexLayer with an array of layers
    @since v2.1
    */
    bool initWithArray(CCArray* arrayOfLayers);

    void switchTo(unsigned int n);
    /** release the current layer and switches to another layer indexed by n.
    The current (old) layer will be removed from it's parent with 'cleanup:YES'.
    */
    void switchToAndReleaseMe(unsigned int n);
};


// end of layer group
/// @}

NS_CC_END

#endif // __CCLAYER_H__

