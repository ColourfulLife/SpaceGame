#ifndef __SCENE_GAME_TWO_H__
#define __SCENE_GAME_TWO_H__

#include "BrainControl.h"
#include "LayerSBGOfParallax.h"
#include "SimpleAudioEngine.h"
#include "LayerScrollBackGround.h"
#include "Enemy.h"

using namespace CocosDenshion;

#define KNUMASTEROIDS 10  //创建星球的数量
#define KNUMLASERS 5      //创建激光的数量

class SceneGame : public LayerScrollBackGround
{
public:
	CREATE_FUNC(SceneGame);
	virtual bool init();
	virtual void update(float dt);
	virtual void onEnter();
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onAcceleration(Acceleration* acc, Event* unused_event);  //重力感应

	enum {EN_BACKGROUND_ZORDER=-1,EN_HERO_ZORDER=10};

	Sprite* _ship;
	Vector<Enemy*> _asteroids;   //储存创建的星球
	Vector<Enemy*> _stones;  //储存创建的陨石
	Vector<Enemy*> _ufos;    //储存ufo
	int _nextAsteroid;
	float _nextAsteroidSpawn;     //指示下一个星球出现的时间点。我们会在update循环中一直检测这个变量的值。
	int _nextStone;
	float _nextStoneSpawn;
	int _nextUfo;
	float _nextUfoSpawn;
	Vector<Sprite*> _shipLasers;  //储存创建的激光
	int _nextShipLaser;

	SpriteBatchNode* _batchNode;

	float _shipPointsPerSecY;

	void createHero();			//创建英雄
	void createGrainStar();     //使用粒子系统创建星星
	void InitAsteroid();		//初始化星球
	void InitStones();          //初始化陨石
	void InitUFO();         
	void AsteroidBlast(const Point& point);		//星球爆炸
	void InitShipLasers();		//初始化激光
	void initAudio();			//加载游戏中需要用到的音乐
	void ShipAccelerate(const Point& point);  //飞船加速效果

	float getTimeTick();
	void setInvisible(Node * node);
	float randomValueBetween(float low, float high);

	double _gameOverTime;
	bool _gameOver;
	int _lives;

	BrainControl* _brainControlShow;

	void ResponseAcceleration(float dt); //响应加速计
	void GenerationAsteroid();  //产生星球
	void GenerationStone();  //产生快速移动的陨石
	void GenerationUFO();   //产生UFO
	void HitCheck();  //碰撞检测
	void HitCheckWithUfo();
};

#endif