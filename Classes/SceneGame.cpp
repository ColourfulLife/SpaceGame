#include "SceneGame.h"
#include "SceneStart.h"

bool SceneGame::init()
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
	_batchNode = SpriteBatchNode::create("Sprites.pvr.ccz");
	this->addChild(_batchNode);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Sprites.plist");

	//Ӣ�۷ɴ�����
	createHero();

	//ʹ������ϵͳ��������
	createGrainStar();

	//��ʼ������
	InitAsteroid();

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

void SceneGame::update(float dt)
{
	updateCallByChild(dt);  //���ø���ķ������ñ���������

	//��Ӧ���ټ�
	ResponseAcceleration(dt);

	//��������
	GenerationAsteroid();

	//��ײ���
	HitCheck();

	//_brainControlShow->Brain();  //���ǵ�������������Բ���ص���������������ʾ

	//������Ϸ��ʾ����ֵ�ͷ�����
	//_brainControlShow->SetLabelLives(_brainControlShow->_lives, 100);
}

void SceneGame::createHero()
{
	_ship = Sprite::createWithSpriteFrameName("SpaceFlier_sm_1.png");
	_ship->setPosition(Point(winSize.width *0.1, winSize.height *0.5));
	_batchNode->addChild(_ship, EN_HERO_ZORDER);
	/*ShipAccelerate(_ship->getPosition());*/
}

void SceneGame::createGrainStar()
{
	SceneGame::addChild(ParticleSystemQuad::create("Stars1.plist"));
	SceneGame::addChild(ParticleSystemQuad::create("Stars2.plist"));
	SceneGame::addChild(ParticleSystemQuad::create("Stars3.plist"));
}

void SceneGame::InitAsteroid()
{
	for (int i = 0; i < KNUMASTEROIDS; ++i)
	{
		auto asteroid = Sprite::createWithSpriteFrameName("asteroid.png");

		asteroid->setVisible(false);
		_batchNode->addChild(asteroid, 5);
		_asteroids.pushBack(asteroid);
	}
}

//����ըЧ��
void SceneGame::AsteroidBlast(const Point& point)
{
	ParticleSystemQuad *emitter = ParticleSystemQuad::create("Image/ExplodingRing.plist");
	emitter->setPosition(point);
	this->addChild(emitter, 10);
}

//�ɴ�����Ч��
void SceneGame::ShipAccelerate(const Point& point)
{
	ParticleSystemQuad *emitter = ParticleSystemQuad::create("Image/Comet.plist");
	emitter->setPosition(point);
	emitter->setRotation(-45.0);
	this->addChild(emitter, 10);
}

void SceneGame::InitShipLasers()
{
	for (int i = 0; i < KNUMLASERS; ++i)
	{
		auto shipLaser = Sprite::createWithSpriteFrameName("laserbeam_blue.png");

		shipLaser->setVisible(false);
		_batchNode->addChild(shipLaser);
		_shipLasers.pushBack(shipLaser);
	}
}

void SceneGame::initAudio()
{
	SimpleAudioEngine::getInstance()->playBackgroundMusic("SpaceGame.wav", true);
	SimpleAudioEngine::getInstance()->preloadEffect("explosion_large.wav");  //��ը����
	SimpleAudioEngine::getInstance()->preloadEffect("laser_ship.wav");       //���伤������
}

float SceneGame::getTimeTick()
{
	timeval* time = new timeval();

	//cocos2d::timezone* z = new cocos2d::timezone();
	struct timezone zz;
	struct timezone *z = &zz;
	gettimeofday(time, z);
	unsigned long millisecs = (time->tv_sec * 1000) + (time->tv_usec / 1000);
	return (float)millisecs;
}

void SceneGame::setInvisible(Node * node)
{
	node->setVisible(false);
}

float SceneGame::randomValueBetween(float low, float high)
{
	return ((float)CCRANDOM_0_1() * (high - low)) + low;
}

//���������麯������init������
// setTouchEnabled(true);
// setTouchMode(kCCTouchesOneByOne);
//�������õ�
void SceneGame::onEnter()
{
	Layer::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(SceneGame::onTouchBegan, this);

	auto dispatcher = Director::getInstance()->getEventDispatcher();

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool SceneGame::onTouchBegan(Touch *touch, Event *event)
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
		CCCallFuncN::create(this, callfuncN_selector(SceneGame::setInvisible)),
		NULL  // DO NOT FORGET TO TERMINATE WITH NULL
		));

	return true;
}

void SceneGame::onAcceleration(Acceleration* acc, Event* unused_event)
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

void SceneGame::ResponseAcceleration(float dt)
{
	float maxY = winSize.height - _ship->getContentSize().height / 2;
	float minY = _ship->getContentSize().height / 2;

	float diff = (_shipPointsPerSecY * dt);
	float newY = _ship->getPosition().y + diff;
	newY = MIN(MAX(newY, minY), maxY);
	_ship->setPosition(ccp(_ship->getPosition().x, newY));
}

void SceneGame::GenerationAsteroid()
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
			CallFuncN::create(this, callfuncN_selector(SceneGame::setInvisible)),
			NULL
			));
	}
}

void SceneGame::HitCheck()
{
	Vector<Sprite*>::iterator itAster, itLaser;
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
