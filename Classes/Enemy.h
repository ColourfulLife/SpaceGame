#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "Util.h"

/*
抽象敌，负责敌人HP，纹理。。。
*/
class Enemy : public Sprite
{
public:
	static Enemy* initWithFileName(const char* frameName);
};

#endif

