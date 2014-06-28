#ifndef __LOADINGSCENE_H__
#define __LOADINGSCENE_H__

#include "Util.h"
/*
加载场景，
*/
class LoadingScene : public Layer
{
public:
	CREATE_FUNC(LoadingScene);
	bool init();

	CCParticleSun* m_pMeteorolite;	//陨石特效
	void move(float dt);

	void loadedCallBack();
	void loading();

};


#endif