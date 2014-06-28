#ifndef __SCENE_START_H__
#define __SCENE_START_H__

#include "LayerBackGround.h"

/*
	开场场景：需要具备背景，所以从LayerBackGround派生
*/
class SceneStart : public Layer
{
public:
	CREATE_FUNC(SceneStart);
	bool init();	

	CCParticleSun* m_pMeteorolite;	//陨石特效
	void move(float dt);

};


#endif