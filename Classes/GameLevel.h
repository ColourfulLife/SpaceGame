#ifndef _GAMELEVEL_H_
#define _GAMELEVEL_H_

#include "SimpleAudioEngine.h"
#include "Util.h"

enum{
	LEVEL_ONE = 1, 
	LEVEL_TWO,  
	LEVEL_THREE,    
};

class CGameLevel : public Layer
{
public:
    virtual bool init();  
	CREATE_FUNC(CGameLevel);

private:
	/**	ѡ��ؿ��Ļص�����	*/
	void setLevelMode(Object* pSender);

	/**	��ʼ��ť�Ļص�����	*/
	void setLevelStart(Object* pSender);

	ParticleSun* m_pSun;		//̫����Ч

	int g_iGameLevel;
	Size size;
	Sprite* _pSprite; //��������
};

#endif
