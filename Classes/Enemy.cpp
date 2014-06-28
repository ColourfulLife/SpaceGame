#include "Enemy.h"

Enemy * Enemy::initWithFileName(const char* frameName)
{
	Enemy *enemy = new Enemy();
	if (enemy && enemy->initWithSpriteFrameName(frameName))
	{
		enemy->autorelease();
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}