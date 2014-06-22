#ifndef __LSBGPARALLAX_H__
#define __LSBGPARALLAX_H__

#include "Util.h"
#include "LayerBackGround.h"
#include "ParallaxNodeExtras.h"

class LayerSBGOfParallax : public Layer
{
public:
	CREATE_FUNC(LayerSBGOfParallax);
	enum{ EN_ORDER_BACKGROUND, EN_ORDER_BACK_MENU };
	enum{ EN_TAG_BACKGROUND };
	bool init();

	//����Ҫ�̳���������㣬������������Ҳ��Ҫ
	//shceduleUpdate();   void update(float dt);
	//�ڸ�����ʵ�ֺ���������ʵ�ֻᵱ��������ֻ�������ˣ�
	//�������������ø�������������
	void updateCallByChild(float dt);

	ParallaxNodeExtras *_backgroundNode;
	Sprite *_spacedust1;
	Sprite *_spacedust2;
	Sprite *_planetsunrise;
	Sprite *_galaxy;
	Sprite *_spacialanomaly;
	Sprite *_spacialanomaly2;
};
#endif

