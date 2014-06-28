#include "SceneGameTest.h"
#include "LayerBackGround.h"
#include "GameLevel.h"

bool SceneGameTest::init()
{
	Layer::init();

	LayerBackButton* back = LayerBackButton::create([](Ref*){
		Util::replaceScene(CGameLevel::create());
	});
	addChild(back);

	Size size = winSize;

	_light = Sprite::create("light.png");
	_light->setScaleX(0.5);
	_light->setScaleY(size.height / _light->getContentSize().height);
	_light->setPosition(size.width*0.5, size.height+_light->boundingBox().size.height/2);
	addChild(_light);

	_light->runAction(Sequence::create(
		MoveBy::create(0.1,Point(0,-size.height)),
		MoveBy::create(2.0, Point(-size.width/2, 0)),
		CCCallFuncN::create(this, callfuncN_selector(SceneGameTest::removefromparent)),
		NULL  // DO NOT FORGET TO TERMINATE WITH NULL
		));

	//·É´¬³å´ÌÐ§¹û
// 	ParticleSystemQuad *emitter = ParticleSystemQuad::create("Image/Comet.plist");
// 	emitter->setPosition(ccp(size.width / 2, size.height / 2));
// 	emitter->setRotation(-45.0);
// 	this->addChild(emitter, 10);

// 	Sprite* ship = Sprite::create("airplane02.png");
// 	addChild(ship);
// 	ship->setAnchorPoint(Point(0,0));
// 	ship->setPosition(0,winSize.height/2);

	return true;
}

void SceneGameTest::removefromparent(Node* node)
{
	node->removeFromParent();
}