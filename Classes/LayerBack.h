#ifndef __LAYERBACK_H__
#define __LAYERBACK_H__

#include "Util.h"

/* ���з��ذ�ť�Ĳ㣬����������ذ�ťû�д����� */
class LayerBack : public Layer
{
public:
	bool init();
	CREATE_FUNC(LayerBack)

	Menu* _menu;
	MenuItem* _menuItem;
};

#endif