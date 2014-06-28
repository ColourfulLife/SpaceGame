#include "SceneStart.h"
#include "SceneAbount.h"
#include "SceneGame.h"
#include "SceneGame.h"

bool SceneStart::init()
{
	Layer::init();

	LayerBackGround* bgLayer = LayerBackGround::create("Image/background1.png");
	addChild(bgLayer);

	// 菜单
	//2014/6/20 12:37修改，使用3.x新特性，让触摸消息处理代码更简洁
	auto itemStart = MenuItemImage::create("btn1_normal.png", "btn1_push.png", [](Ref*){
		Util::replaceScene(SceneGame::create());
	});
	auto itemAbout = MenuItemImage::create("btn2_normal.png", "btn2_push.png", [](Ref*){
		Util::replaceScene(SceneAbout::create());
	});
	auto itemExit = MenuItemImage::create("btn3_normal.png", "btn3_push.png", [](Ref*){
		Director::getInstance()->end();
	});
	itemStart->setScale(0.5f);
	itemAbout->setScale(0.5f);
	itemExit->setScale(0.5f);
	CCMenu* menu = CCMenu::create(itemStart, itemAbout, itemExit, NULL);
	addChild(menu,3);
	menu->alignItemsVertically();

	//陨石掉落特效
	m_pMeteorolite = CCParticleSun::create();
	m_pMeteorolite->setTexture(CCTextureCache::sharedTextureCache()->addImage("Image/Fire.png"));
	this->addChild(m_pMeteorolite, 1);
	move(0);
	this->schedule(schedule_selector(SceneStart::move), 3.0f);

	auto ptCenter = ccp(winSize.width / 2, winSize.height / 2);
	auto ptMove = ccp(200, 0);

	//星星闪烁的特效，效果不是很好啊！！！！
	auto pStar1 = Sprite::create("Image/Star.png");
	//pStar1->setPosition(ccpAdd(ptCenter,ccp(-250,0)));
	pStar1->setPosition(ptCenter);
	this->addChild(pStar1, 1);

	ActionInterval* actionFade1 = FadeOut::create(2.5f);
	ActionInterval* actionFadeBack1 = actionFade1->reverse();
	ActionInterval* seq1 = (ActionInterval*)Sequence::create(actionFade1, actionFadeBack1, NULL);
	RepeatForever* pRepeatForever1 = RepeatForever::create(seq1);

	pStar1->runAction(pRepeatForever1);

	//创建2个飞机图标
	auto pPlane1 = Sprite::create("Image/ShipIcon.png");
	pPlane1->setPosition(ccpAdd(ptCenter, ccp(-150,0)));
	this->addChild(pPlane1, 2);

	auto pPlane2 = Sprite::create("Image/ShipIcon.png");
	pPlane2->setPosition(ccpAdd(ptCenter, ccp(150, 0)));
	this->addChild(pPlane2, 2);

	//添加返回键和菜单键响应
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [&](EventKeyboard::KeyCode keyCode, Event* event)
	{
		//返回键
		if (keyCode == EventKeyboard::KeyCode::KEY_BACK_TAB ||
			keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		{
			Director::getInstance()->end();
		}
		//响应菜单键
		else if (keyCode == EventKeyboard::KeyCode::KEY_MENU)
		{

		}
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void SceneStart::move(float dt)
{
	int x = -40;
	int y = rand() % ((int)(winSize.width + winSize.height) / 2) + winSize.height / 2;
	m_pMeteorolite->setPosition(ccp(x, y));
	m_pMeteorolite->runAction(MoveBy::create(3, ccp(winSize.width + 40, -winSize.height - 40)));
}
