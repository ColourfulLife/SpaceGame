#ifndef __SCENE_START_H__
#define __SCENE_START_H__

#include "LayerBackGround.h"

/*
	������������Ҫ�߱����������Դ�LayerBackGround����
*/
class SceneStart : public LayerBackGround
{
public:
	CREATE_FUNC(SceneStart);
	bool init();

	void enter(Object*);
	void exit(Object*);
	void about(Object*);	

	CCParticleSun* m_pMeteorolite;	//��ʯ��Ч
	void move(float dt);
};


#endif