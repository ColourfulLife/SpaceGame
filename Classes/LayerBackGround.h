#ifndef __LAYERBACKGROUND_H__
#define __LAYERBACKGROUND_H__

#include "LayerBack.h"

/* �ṩ��ֹ�����ͷ��ذ�ť�Ĳ� */
class LayerBackGround : public LayerBack
{
public:
	enum{ EN_ORDER_BACKGROUND , EN_ORDER_BACK_MENU};
	enum{ EN_TAG_BACKGROUND };

	bool init();
	CREATE_FUNC(LayerBackGround)
};

#endif

