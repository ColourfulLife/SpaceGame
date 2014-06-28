#ifndef __UTIL_H__
#define __UTIL_H__

#include "cocos2d.h"
USING_NS_CC;

#define winSize Director::getInstance()->getWinSize()
#define BOOM "BOOM"

class Util
{
public:
	static Scene* scene(Layer* layer)
	{
		Scene* scene = Scene::create();
		scene->addChild(layer);
		return scene;
	}

	static void replaceScene(Layer* layer)
	{
		Scene* scene = Scene::create();
		scene->addChild(layer);
		Director::getInstance()->replaceScene(scene);
	}

	static const char* format(int val, const char* prefix = "", const char* suffix = "")
	{
		static char buf[1024];
		sprintf(buf, "%s%02d%s", prefix, val, suffix);
		return buf;
	}

	static int GetPlaneID(){
		return CCUserDefault::sharedUserDefault()->getIntegerForKey("PlaneID");
	}
	static void SetPlaneID(int id){
		CCUserDefault::sharedUserDefault()->setIntegerForKey("PlaneID", id);
	}
};

#endif