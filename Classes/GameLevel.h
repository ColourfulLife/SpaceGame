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
	/**	选择关卡的回调函数	*/
	void setLevelMode(Object* pSender);

	/**	开始按钮的回调函数	*/
	void setLevelStart(Object* pSender);

	ParticleSun* m_pSun;		//太阳特效

	int g_iGameLevel;
	Size size;
	Sprite* _pSprite; //背景精灵
};

#endif
