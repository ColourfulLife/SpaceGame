#include "SceneGameTwo.h"
#include "SceneStart.h"

bool SceneGameTwo::init()
{
	LayerSBGOfParallax::init();

	_brainControlShow = BrainControl::create();
	this->addChild(_brainControlShow);
	_brainControlShow->setZOrder(100);

	_nextAsteroid = 0;
	_nextShipLaser = 0;

	//�����е�ͼƬ�洢��һ��ͼƬ���棬Ȼ��ʹ����� BatchNode 
	//�Ϳ��Խ�ʹ��һ�� opengl �����������еĻ�ͼ������
	//ʹ��һ�Ŵ��ͼƬ����һ�� CCSpriteBatchNode ���������������еĶ�
	//��������������յĲ����� Sprites.pvr.ccz��
	_batchNode = SpriteBatchNode::create("SceneGameTwo/ShipAsteroidStone.png");
	this->addChild(_batchNode);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("SceneGameTwo/ShipAsteroidStone.plist");

	//Ӣ�۷ɴ�����
	createHero();

	//ʹ������ϵͳ��������
	createGrainStar();

	//��ʼ������
	InitAsteroid();

	//��ʼ����ʯ
	InitStones();

	//��ʼ������
	InitShipLasers();

	//������Ϸ����Ҫ�õ�������
	initAudio();

	this->scheduleUpdate();
	this->setAccelerometerEnabled(true);   //����������Ӧ

	double curTime = getTimeTick();
	_gameOverTime = curTime + 30000;
	_gameOver = false;
	_lives = _brainControlShow->_lives;

	return true;
}

void SceneGameTwo::update(float dt)
{
	updateCallByChild(dt);  //���ø���ķ������ñ���������

	//��Ӧ���ټ�
	//ResponseAcceleration(dt);

	//��������
	GenerationAsteroid();

	//������ʯ
	GenerationStone();

	//��ײ���
	HitCheck();

	_brainControlShow->Brain();  //���ǵ�������������Բ���ص���������������ʾ

	//������Ϸ��ʾ����ֵ�ͷ�����
	_brainControlShow->SetLabelLives(_brainControlShow->_lives, 100);
}

void SceneGameTwo::createHero()
{
	_ship = Sprite::createWithSpriteFrameName("airplane02.png");
	_ship->setPosition(Point(winSize.width *0.1, winSize.height *0.5));
	_batchNode->addChild(_ship, EN_HERO_ZORDER);
	ShipAccelerate(_ship->getPosition());
}

void SceneGameTwo::createGrainStar()
{
	SceneGameTwo::addChild(ParticleSystemQuad::create("Stars1.plist"));
	SceneGameTwo::addChild(ParticleSystemQuad::create("Stars2.plist"));
	SceneGameTwo::addChild(ParticleSystemQuad::create("Stars3.plist"));
}

void SceneGameTwo::InitAsteroid()
{
	char filename[48];
	for (int i = 0; i < KNUMASTEROIDS; ++i)
	{
		const char* name1 = "block%02d.png";
		sprintf(filename, name1, i % 3 + 1);
	
		auto asteroid = Sprite::createWithSpriteFrameName(filename);

		asteroid->setVisible(false);
		_batchNode->addChild(asteroid, 5);
		_asteroids.pushBack(asteroid);
	}
}

void SceneGameTwo::InitStones()
{
	char filename[48];
	for (int i = 0; i < KNUMASTEROIDS; ++i)
	{
		const char* name = "stone_%02d.png";
		sprintf(filename, name, i % 3 + 1);

		auto stone = Sprite::createWithSpriteFrameName(filename);

		stone->setVisible(false);
		_batchNode->addChild(stone, 5);
		_stones.pushBack(stone);
	}
}

//����ըЧ��
void SceneGameTwo::AsteroidBlast(const Point& point)
{
	ParticleSystemQuad *emitter = ParticleSystemQuad::create("Image/ExplodingRing.plist");
	emitter->setPosition(point);
	this->addChild(emitter, 10);
}

//�ɴ�����Ч��
void SceneGameTwo::ShipAccelerate(const Point& point)
{
	ParticleSystemQuad *emitter = ParticleSystemQuad::create("Image/Comet.plist");
	emitter->setPosition(point);
	emitter->setRotation(-45.0);
	this->addChild(emitter, 10);
}

void SceneGameTwo::InitShipLasers()
{
	for (int i = 0; i < KNUMLASERS; ++i)
	{
		auto shipLaser = Sprite::createWithSpriteFrameName("shell.png");

		shipLaser->setVisible(false);
		_batchNode->addChild(shipLaser);
		_shipLasers.pushBack(shipLaser);
	}
}

void SceneGameTwo::initAudio()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("SpaceGame.wav", true);
	SimpleAudioEngine::getInstance()->preloadEffect("explosion_large.wav");  //��ը����
	SimpleAudioEngine::getInstance()->preloadEffect("laser_ship.wav");       //���伤������
}

float SceneGameTwo::getTimeTick()
{
	timeval* time = new timeval();

	//cocos2d::timezone* z = new cocos2d::timezone();
	struct timezone zz;
	struct timezone *z = &zz;
	gettimeofday(time, z);
	unsigned long millisecs = (time->tv_sec * 1000) + (time->tv_usec / 1000);
	return (float)millisecs;
}

void SceneGameTwo::setInvisible(Node * node)
{
	node->setVisible(false);
}

float SceneGameTwo::randomValueBetween(float low, float high)
{
	return ((float)CCRANDOM_0_1() * (high - low)) + low;
}

//���������麯������init������
// setTouchEnabled(true);
// setTouchMode(kCCTouchesOneByOne);
//�������õ�
void SceneGameTwo::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(SceneGameTwo::onTouchBegan, this);

	auto dispatcher = Director::getInstance()->getEventDispatcher();

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool SceneGameTwo::onTouchBegan(Touch *touch, Event *event)
{
	auto *shipLaser = _shipLasers.at(_nextShipLaser++);

	SimpleAudioEngine::getInstance()->playEffect("laser_ship.wav");
	if (_nextShipLaser >= _shipLasers.size())
		_nextShipLaser = 0;
	shipLaser->setPosition(_ship->getPosition() + Point(shipLaser->getContentSize().width / 2, 0));
	shipLaser->setVisible(true);
	shipLaser->stopAllActions();
	shipLaser->runAction(Sequence::create(
		MoveBy::create(0.5, Point(winSize.width, 0)),
		CCCallFuncN::create(this, callfuncN_selector(SceneGameTwo::setInvisible)),
		NULL  // DO NOT FORGET TO TERMINATE WITH NULL
		));

	return true;
}

void SceneGameTwo::onAcceleration(Acceleration* acc, Event* unused_event)
{
#define KFILTERINGFACTOR 0.1
#define KRESTACCELX -0.6
#define KSHIPMAXPOINTSPERSEC (winSize.height*0.5)
#define KMAXDIFFX 0.2

	double rollingX = 0.0;

	// Cocos2DX inverts X and Y accelerometer depending on device orientation
	// in landscape mode right x=-y and y=x !!! (Strange and confusing choice)
	acc->x = acc->y;
	rollingX = (acc->x * KFILTERINGFACTOR) + (rollingX * (1.0 - KFILTERINGFACTOR));
	float accelX = acc->x - rollingX;
	float accelDiff = accelX - KRESTACCELX;
	float accelFraction = accelDiff / KMAXDIFFX;
	_shipPointsPerSecY = KSHIPMAXPOINTSPERSEC * accelFraction;
}

void SceneGameTwo::ResponseAcceleration(float dt)
{
	float maxY = winSize.height - _ship->getContentSize().height / 2;
	float minY = _ship->getContentSize().height / 2;

	float diff = (_shipPointsPerSecY * dt);
	float newY = _ship->getPosition().y + diff;
	newY = MIN(MAX(newY, minY), maxY);
	_ship->setPosition(ccp(_ship->getPosition().x, newY));
}

void SceneGameTwo::GenerationAsteroid()
{
	float curTimeMillis = getTimeTick();
	if (curTimeMillis > _nextAsteroidSpawn)
	{

		float randMillisecs = randomValueBetween(0.20, 1.0) * 1000;
		_nextAsteroidSpawn = randMillisecs + curTimeMillis;

		float randY = randomValueBetween(0.0, winSize.height);
		float randDuration = randomValueBetween(2.0, 10.0);

		Sprite *asteroid = _asteroids.at(_nextAsteroid);
		_nextAsteroid++;

		if (_nextAsteroid >= _asteroids.size())
			_nextAsteroid = 0;

		asteroid->stopAllActions();
		asteroid->setPosition(Point(winSize.width + asteroid->getContentSize().width / 2, randY));
		asteroid->setVisible(true);

		asteroid->runAction(Sequence::create(
			MoveBy::create(randDuration, Point(-winSize.width - asteroid->getContentSize().width, 0)),
			CallFuncN::create(this, callfuncN_selector(SceneGameTwo::setInvisible)),
			NULL
			));
	}
}

void SceneGameTwo::GenerationStone()
{
	float curTimeMillis = getTimeTick();
	if (curTimeMillis > _nextStoneSpawn)
	{

		float randMillisecs = randomValueBetween(0.20, 1.0) * 1000;
		_nextStoneSpawn = randMillisecs + curTimeMillis;

		float randY = randomValueBetween(0.0, winSize.height);
		float randDuration = randomValueBetween(0.5, 2.0);

		Sprite *stone = _stones.at(_nextAsteroid);
		_nextStone++;

		if (_nextStone >= _stones.size())
			_nextStone = 0;

		stone->stopAllActions();
		stone->setPosition(Point(winSize.width + stone->getContentSize().width / 2, randY));
		stone->setVisible(true);

		stone->runAction(Sequence::create(
			MoveBy::create(randDuration, Point(-winSize.width - stone->getContentSize().width, 0)),
			CallFuncN::create(this, callfuncN_selector(SceneGameTwo::setInvisible)),
			NULL
			));
	}
}

void SceneGameTwo::HitCheck()
{
	Vector<Sprite*>::iterator itAster,itLaser;
	for (itAster = _asteroids.begin(); itAster != _asteroids.end(); itAster++)
	{
		auto *asteroid = (Sprite *)*itAster;
		if (!asteroid->isVisible())
			continue;
		for (itLaser = _shipLasers.begin(); itLaser != _shipLasers.end(); itLaser++)
		{
			auto *shipLaser = (Sprite *)*itLaser;
			if (!shipLaser->isVisible())
				continue;
			if (shipLaser->boundingBox().intersectsRect(asteroid->boundingBox()))
			{
				shipLaser->setVisible(false);
				asteroid->setVisible(false);
				AsteroidBlast(asteroid->getPosition());
				continue;
			}
		}
		if (_ship->boundingBox().intersectsRect(asteroid->boundingBox()))
		{
			SimpleAudioEngine::getInstance()->playEffect("explosion_large.wav");
			asteroid->setVisible(false);
			AsteroidBlast(asteroid->getPosition());
		}
	}
}