#ifndef __SCENE_START_H__
#define __SCENE_START_H__

#include "LayerBackGround.h"

/*
	������������Ҫ�߱����������Դ�LayerBackGround����
*/
class SceneStart : public Layer
{
public:
	CREATE_FUNC(SceneStart);
	bool init();	

	CCParticleSun* m_pMeteorolite;	//��ʯ��Ч
	void move(float dt);
};


#endif