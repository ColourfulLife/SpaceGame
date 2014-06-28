#include "AppDelegate.h"
#include "SceneStart.h"
#include "Util.h"

USING_NS_CC;

AppDelegate::AppDelegate() 
{
}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
	
	//glview->setFrameSize(480, 320);
	glview->setDesignResolutionSize(480, 320, ResolutionPolicy::EXACT_FIT);
	
    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

	// ¼ÓÔØ±¬Õ¨¶¯»­
 	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
 	cache->addSpriteFramesWithFile("SceneGameTwo/explosion.plist");
 
 	Vector<SpriteFrame*> arr;
 	for (int i = 0; i < 35; ++i)
 	{
 		//"explosion_01.png"
 		char filename[48];
 		const char* name1 = "explosion_%02d.png";
 		sprintf(filename, name1, i+1);
		//cache->spriteFrameByName()
		SpriteFrame* frame = cache->spriteFrameByName(filename);
 		arr.pushBack(frame);
 	}
 
 	Animation* animation = Animation::createWithSpriteFrames(arr, 1.0f / 35);
 	AnimationCache::getInstance()->addAnimation(animation, BOOM);

    // create a scene. it's an autorelease object
    auto scene = Util::scene(SceneStart::create());

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}