#include "LayerScrollBackGround.h"


bool LayerScrollBackGround::init()
{
	Layer::init();

	// ´´½¨¹ö¶¯µÄ±³¾°

	// ±³¾°Í¼Æ¬
	auto spriteFir = Sprite::create("SceneGameTwo/scrollbackground.png");
	addChild(spriteFir, EN_ORDER_BACKGROUND, EN_TAG_BACKGROUND);

	auto spriteSec = Sprite::create("SceneGameTwo/scrollbackground.png");
	addChild(spriteSec, EN_ORDER_BACKGROUND, EN_TAG_BACKGROUND);

	float width = spriteFir->boundingBox().size.height;

	spriteFir->setPosition(ccp(winSize.width / 2, winSize.height / 2));
	spriteSec->setPosition(ccp(winSize.width / 2 + width, winSize.height / 2));

	auto moveByFir = MoveBy::create(10, ccp(-width, 0));
	auto placeFir = Place::create(ccp(winSize.width / 2, winSize.height / 2));
	auto seqFir = Sequence::create(moveByFir, placeFir, NULL);
	spriteFir->runAction(RepeatForever::create(seqFir));

	auto moveBySec = MoveBy::create(10, ccp(-width, 0));
	auto placeSec = Place::create(ccp(winSize.width / 2 + width, winSize.height / 2));
	auto seqSec = Sequence::create(placeSec, moveBySec, NULL);
	spriteSec->runAction(RepeatForever::create(seqSec));

	return true;
}

