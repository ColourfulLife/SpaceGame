#include "BrainControl.h"

bool BrainControl::init()
{
	Layer::init();

	labelLives = LabelBMFont::create("", "fonts/Arial.fnt");
	labelLives->setScale(0.5);
	labelLives->setPosition(winSize.width*0.6, winSize.height*0.92);
	this->addChild(labelLives);

	//attention  初始化注意力的标签
	labelAttention = LabelBMFont::create("0", "fonts/Arial.fnt");
	labelAttention->setScale(0.5);
	labelAttention->setPosition(winSize.width*0.1, winSize.height*0.92);
	this->addChild(labelAttention);

	//初始化注意力进度条
	progress1 = ProgressTimer::create(Sprite::create("attention2.png"));
	progress1->setScale(0.3);
	progress1->setPosition(winSize.width*0.1, winSize.height*0.92);

	//设置进度条的样式
	progress1->setType(kCCProgressTimerTypeRadial);

	//设置进度值范围[0,100]
	progress1->setPercentage(100);

	//反进度计时
	progress1->setReverseProgress(true);
	this->addChild(progress1);

	//初始化脑波信号进度条
	progress2 = ProgressTimer::create(Sprite::create("attention.png"));
	progress2->setScale(0.5);
	progress2->setPosition(winSize.width*0.95, winSize.height*0.95);
	//设置进度条的样式
	progress2->setType(kCCProgressTimerTypeBar);
	//设置计时器起始点
	progress2->setMidpoint(ccp(0, 0));
	//设置计时器方向
	progress2->setBarChangeRate(ccp(1, 0));
	this->addChild(progress2);

	//添加眨眼睛的效果,初始化眨眼时需要显示的图片元素
	//auto *pTexture = TextureCache::sharedTextureCache()->addImage("eyesm.png");
	auto* pNewBatchNode = SpriteBatchNode::create("eyesm.png", 2);
	addChild(pNewBatchNode, 1);
	pNewBatchNode->getTexture()->setAliasTexParameters();
	auto *pTexture = pNewBatchNode->getTexture();
	auto *frame0 = SpriteFrame::createWithTexture(pTexture, CCRectMake(0, 0, 147, 147));
	auto *frame1 = SpriteFrame::createWithTexture(pTexture, CCRectMake(147, 0, 147, 147));
	_animFrames.pushBack(frame0);
	_animFrames.pushBack(frame1);

	_lives = 20;

	//脑波相关
	_Attention = 0;
	_PoolSignal = 0;
	_Attack = 0;

	scheduleUpdate();

	return true;
}

void BrainControl::update(float dt)
{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	int iAttention = 0;
	int iPoolSignal = 0;
	int iBlink = 0;

	//void doStuff();
	int getAttention();
	int getPoorSignal();
	int getBlink();

	//doStuff();
	iPoolSignal = getPoorSignal();
	iBlink = getBlink();
	iAttention = getAttention();
	_Attack = iAttention;
#else
	int iAttention = 50;
	int iPoolSignal = 50;
	int iBlink = 1;
#endif
	if (_PoolSignal > 100 - iPoolSignal / 2)
		_PoolSignal--;
	else if (_PoolSignal < 100 - iPoolSignal / 2)
		_PoolSignal++;
	progress2->setPercentage(_PoolSignal);

	//判断信号
	if (iPoolSignal < 10)
		return;

	if (iAttention < 5)
		return;

	if (iBlink)
	{
		iBlink = 0;

		//SimpleAudioEngine::getInstance()->playEffect("laser_enemy.wav");
		_lives--;
		iAttention = 30;
		_Attack = 30;


		//眨眼睛播放动画
		animation = Animation::createWithSpriteFrames(_animFrames, 0.2f);
		animation->setDelayPerUnit(0.2f);
		animation->setRestoreOriginalFrame(true);
		action = Animate::create(animation);

		spriteEyes = Sprite::create();
		spriteEyes->setPosition(ccp(winSize.width*0.25, winSize.height*0.92));
		spriteEyes->stopAllActions();
		repeatEyes = Repeat::create(action, 1);
		spriteEyes->setScaleX(0.4f);
		spriteEyes->setScaleY(0.32f);
		spriteEyes->runAction(repeatEyes);
		addChild(spriteEyes, 1);
	}

	if (_Attention > iAttention)
		_Attention--;
	else if (_Attention < iAttention)
		_Attention++;

	char szAttention[100];
	sprintf(szAttention, "%3d", _Attention);
	labelAttention->setString(szAttention);
	progress1->setPercentage(_Attention);
}

void BrainControl::SetLabelLives(int lives, int score)
{
	char szLives[100];
	sprintf(szLives, "highest score:%3d | lives:%2d | score:%3d", getHighestHistorySorce(), lives, score);
	labelLives->setString(szLives);
}

bool BrainControl::isHaveSaveFile()//判断存档是否存在
{
	if (!UserDefault::getInstance()->getBoolForKey("isHaveSaveFileXml"))//通过设置的bool型标志位判断，如果不存在
	{
		UserDefault::getInstance()->setBoolForKey("isHaveSaveFileXml", true);//写入bool判断位
		UserDefault::getInstance()->setIntegerForKey("HighestScore", 0);//写入初始分数0
		UserDefault::getInstance()->flush();//设置完一定要调用flush，才能从缓冲写入io
		return false;
	}
	else
	{
		return true;
	}
}

int BrainControl::getHighestHistorySorce()
{
	if (isHaveSaveFile()) //如果存在存档
	{
		return UserDefault::getInstance()->getIntegerForKey("HighestScore", 0);//读取历史最高分
	}
	return 0;
}

void BrainControl::setHighestHistorySorce(int score)
{
	int lScore = getHighestHistorySorce();
	if (score > lScore)
	{
		UserDefault::getInstance()->setIntegerForKey("HighestScore", score);//修改存档
	}
}
