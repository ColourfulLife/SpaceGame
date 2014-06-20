#ifndef __LAYERBACKGROUND_H__
#define __LAYERBACKGROUND_H__

#include "Util.h"

/* 2014/6/20 12:50�޸�   ������ֹ���������*/
/*���Ը��ݲ�ͬ�ı���ͼƬ������ͬ�ı���*/

class LayerBackGround : public Layer
{
public:
	bool init(const char* bgFileName);
	static LayerBackGround* create(const char* bgFileName);

	Sprite* _bg;
};

/* 2014/6/20 13:00�޸�   �������ذ�ť��*/
/*�����ṩ���ذ�ť����Ϣ��Ϣ��Ӧ����*/
class LayerBackButton : public Layer
{
public:
	static LayerBackButton* create(const ccMenuCallback& callback);
	bool init(const ccMenuCallback& callback);
	Menu* _menu;
};
#endif

