#include "GameLevel.h"
#include "SceneStart.h"
#include "SceneGame.h"

bool CGameLevel::init()
{
	LayerBack::init();

	g_iGameLevel = 1;
	size = winSize;


	// ѡ���б�
	SpriteFrameCache *pCache = SpriteFrameCache::sharedSpriteFrameCache();
	pCache->addSpriteFramesWithFile("Image/GameLevel.plist");

	// ѡ�ر���
	SpriteFrame* pBG = pCache->spriteFrameByName("GameLevelBG.png");
	Sprite* pSprite = CCSprite::createWithSpriteFrame(pBG);
	pSprite->setPosition(ccp(size.width/2, size.height/2));
	pSprite->setScale(2.0f);
	pSprite->setRotation(90.0f);
	this->addChild(pSprite, 0);
	_pSprite = pSprite;
		
	/**������Ч	*/
	ParticleSystemQuad *emitter = ParticleSystemQuad::create("Image/Phoenix.plist");
	emitter->setPosition(ccp(size.width/2, size.height/2));
	this->addChild(emitter, 1);

	/**	�ؿ�һ��ť	*/
	MenuItemImage *pLevelOne = MenuItemImage::create();
	pLevelOne->setTarget(this, menu_selector(CGameLevel::setLevelMode));
	pLevelOne->setNormalSpriteFrame(pCache->spriteFrameByName("StartLevel1Normal.png")); 
	pLevelOne->setSelectedSpriteFrame(pCache->spriteFrameByName("StartLevel1Selected.png"));
	pLevelOne->setPosition(ccp(size.width*0.14f, size.height/2));
	pLevelOne->_ID = LEVEL_ONE;

	/**	�ؿ�����ť	*/
	MenuItemImage *pLevelTwo = MenuItemImage::create();
	pLevelTwo->setTarget(this, menu_selector(CGameLevel::setLevelMode));
	pLevelTwo->setNormalSpriteFrame(pCache->spriteFrameByName("StartLevel2Normal.png")); 
	pLevelTwo->setSelectedSpriteFrame(pCache->spriteFrameByName("StartLevel2Selected.png"));
	pLevelTwo->setPosition(ccp(size.width/2, size.height*0.8f));
	pLevelTwo->_ID = LEVEL_TWO;

	/**	�ؿ�����ť	*/
	MenuItemImage *pLevelThree = MenuItemImage::create();
	pLevelThree->setTarget(this, menu_selector(CGameLevel::setLevelMode));
	pLevelThree->setNormalSpriteFrame(pCache->spriteFrameByName("StartLevel3Normal.png")); 
	pLevelThree->setSelectedSpriteFrame(pCache->spriteFrameByName("StartLevel3Selected.png"));
	pLevelThree->setPosition(ccp(size.width*0.86f, size.height/2));
	pLevelThree->_ID = LEVEL_THREE;

	/**	��Ϸ��ʼ��ť	*/
	MenuItemImage *pStart = MenuItemImage::create();
	pStart->setTarget(this, menu_selector(CGameLevel::setLevelStart));
	pStart->setNormalSpriteFrame(pCache->spriteFrameByName("GameStartNormal.png")); 
	pStart->setSelectedSpriteFrame(pCache->spriteFrameByName("GameStartSelected.png"));
	pStart->setPosition(ccp(size.width/2, size.height*0.2f));

	/**	�˵�	*/
	_menu->addChild(pLevelOne);
	_menu->addChild(pLevelTwo);
	_menu->addChild(pLevelThree);
	_menu->addChild(pStart);
	_menu->setPosition(ccp(0, 0));
	_menu->setZOrder(3);

	/**	ѡ����Ч	*/
	m_pSun = ParticleSun::create();
	pSprite->addChild(m_pSun, 1);
	m_pSun->setTexture(TextureCache::sharedTextureCache()->addImage("Image/Fire.png") );
	m_pSun->setPosition(_pSprite->convertToNodeSpace(ccp(size.width*0.14f, size.height / 2)));
	m_pSun->setStartSize(30);

	_menuItem->setTarget(this, menu_selector(CGameLevel::back));
	//_menuItem�������

	return true;
}

void CGameLevel::setLevelMode(Object* pSender)
{
	g_iGameLevel = pSender->_ID;
	switch(g_iGameLevel)
	{
	case LEVEL_ONE:
		m_pSun->setPosition(_pSprite->convertToNodeSpace(ccp(size.width*0.14f, size.height / 2)));
		break;
	case LEVEL_TWO:
		m_pSun->setPosition(_pSprite->convertToNodeSpace(ccp(size.width / 2, size.height*0.8f)));
		break;
	case LEVEL_THREE:
		m_pSun->setPosition(_pSprite->convertToNodeSpace(ccp(size.width*0.86f, size.height / 2)));
		break;
	default:
		break;
	}
}

void CGameLevel::setLevelStart(Object* pSender)
{
	switch (g_iGameLevel)
	{
	case LEVEL_ONE:
		Director::getInstance()->replaceScene(Util::scene(SceneGame::create()));
		break;
	case LEVEL_TWO:
		Director::getInstance()->replaceScene(Util::scene(SceneGame::create()));
		break;
	case LEVEL_THREE:
		Director::getInstance()->replaceScene(Util::scene(SceneGame::create()));
		break;
	default:
		break;
	}
}

void CGameLevel::back(Object* pSender)
{
	Director::getInstance()->replaceScene(Util::scene(SceneStart::create()));
}