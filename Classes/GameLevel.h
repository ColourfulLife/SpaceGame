#ifndef _GAMELEVEL_H_
#define _GAMELEVEL_H_

#include "LayerBack.h"
//#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"
#include "Util.h"

enum{
	LEVEL_ONE = 1, 
	LEVEL_TWO,  
	LEVEL_THREE,    
};

class CGameLevel : public LayerBack
{
public:
    virtual bool init();  
	CREATE_FUNC(CGameLevel);

private:
	/**	ѡ��ؿ��Ļص�����	*/
	void setLevelMode(Object* pSender);

	/**	��ʼ��ť�Ļص�����	*/
	void setLevelStart(Object* pSender);

	/**	���ذ�ť�Ļص�����	*/
	void back(Object* pSender);

	ParticleSun* m_pSun;		//̫����Ч

	int g_iGameLevel = 1;
	Size size = winSize;
	Sprite* _pSprite;   //��������
};

#endif
