#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Util.h"

/*
����У��������HP����������
*/
class Enemy : public Sprite
{
public:
	static Enemy* initWithFileName(const char* frameName);
};

#endif

