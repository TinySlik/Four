#include "AppDelegate.h"
#include "HelpScene.h"
#include "StartScene.h"
#include "SimpleAudioEngine.h"
#include "AudioManager.h"

USING_NS_CC;

AppDelegate::AppDelegate() {
    audio = AudioManager::create();
    CC_SAFE_RETAIN(audio);
}

AppDelegate::~AppDelegate() 
{
    CC_SAFE_RELEASE(audio);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    
    pDirector->setOpenGLView(pEGLView);

    pEGLView->setDesignResolutionSize(640, 1136, kResolutionShowAll);

    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    
    CCDictionary* config = CCDictionary::createWithContentsOfFileThreadSafe("Config.plist");
    
    CCScene* pScene = nullptr;
    
    CCAssert(config  != nullptr, "null");
    
    bool firstTime = dynamic_cast<CCString*>(config->objectForKey("FirstTime"))->boolValue();
    
    if (firstTime) {
        pScene = HelpScene::create();
        config->setObject(CCBool::create(!firstTime), "FirstTime");
        config->writeToFile("Config.plist");
    }else{
        pScene = StartScene::create();
    }
    
    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    audio->pause();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    audio->resume();
}
