#ifndef __LOADINGSCENE_H__
#define __LOADINGSCENE_H__

#include "Util.h"
/*
���س�����
*/
class LoadingScene : public Layer
{
public:
	CREATE_FUNC(LoadingScene);
	bool init();

	CCParticleSun* m_pMeteorolite;	//��ʯ��Ч
	void move(float dt);

	void loadedCallBack();
	void loading();

};


#endif