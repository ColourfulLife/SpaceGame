#include "LayerSBGOfParallax.h"
#include "SceneStart.h"
#include "GameLevel.h"

bool LayerSBGOfParallax::init()
{
	Layer::init();

	LayerBackButton* backSprite = LayerBackButton::create([](Ref*){
		Util::replaceScene(CGameLevel::create());
	});
	addChild(backSprite);
	backSprite->setZOrder(1000);


	// 1) Create the CCParallaxNode
	_backgroundNode = ParallaxNodeExtras::node();
	this->addChild(_backgroundNode, -1);

	// 2) Create the sprites we'll add to the CCParallaxNode
	_spacedust1 = Sprite::create("bg_front_spacedust.png");
	_spacedust2 = Sprite::create("bg_front_spacedust.png");
	_planetsunrise = Sprite::create("bg_planetsunrise.png");
	_galaxy = Sprite::create("bg_galaxy.png");
	_spacialanomaly = Sprite::create("bg_spacialanomaly.png");
	_spacialanomaly2 = Sprite::create("bg_spacialanomaly2.png");

	// 3) Determine relative movement speeds for space dust and background
	Point dustSpeed = Point(0.1, 0.1);
	Point bgSpeed = Point(0.05, 0.05);

	// 4) Add children to CCParallaxNode
	_backgroundNode->addChild(_spacedust1, 0, dustSpeed, Point(0, winSize.height / 2));
	_backgroundNode->addChild(_spacedust2, 0, dustSpeed, Point(_spacedust1->getContentSize().width, winSize.height / 2));
	_backgroundNode->addChild(_galaxy, -1, bgSpeed, Point(0, winSize.height *0.7));
	_backgroundNode->addChild(_planetsunrise, -1, bgSpeed, Point(600, winSize.height * 0));
	_backgroundNode->addChild(_spacialanomaly, -1, bgSpeed, Point(900, winSize.height *0.3));
	_backgroundNode->addChild(_spacialanomaly2, -1, bgSpeed, Point(1500, winSize.height *0.9));

	//this->scheduleUpdate();

	return true;
}

void LayerSBGOfParallax::updateCallByChild(float dt)
{
	Point backgroundScrollVel = ccp(-1000, 0);
	_backgroundNode->setPosition(ccpAdd(_backgroundNode->getPosition(),
		ccpMult(backgroundScrollVel, dt)));

	Vector<Sprite*> spaceDusts;
	spaceDusts.pushBack(_spacedust1);
	spaceDusts.pushBack(_spacedust2);
	for (Sprite *spaceDust : spaceDusts)
	{
		if ((_backgroundNode->convertToWorldSpace(spaceDust->getPosition()).x < -spaceDust->getContentSize().width + 400))
		{
			_backgroundNode->incrementOffset(Point(2 * spaceDust->getContentSize().width, 0), spaceDust);
		}
	}

	Vector<Sprite*> backgrounds;
	backgrounds.pushBack(_planetsunrise);
	backgrounds.pushBack(_galaxy);
	backgrounds.pushBack(_spacialanomaly);
	backgrounds.pushBack(_spacialanomaly2);
	for (Sprite *background : backgrounds)
	{
		if ((_backgroundNode->convertToWorldSpace(background->getPosition()).x < -background->getContentSize().width))
		{
			_backgroundNode->incrementOffset(Point(2000, 0), background);
		}
	}
}