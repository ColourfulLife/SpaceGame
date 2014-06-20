#ifndef __SCENE_GAME_H__
#define __SCENE_GAME_H__

#include "BrainControl.h"
#include "LayerSBGOfParallax.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;

#define KNUMASTEROIDS 15  //�������������
#define KNUMLASERS 5      //�������������

class SceneGame : public LayerSBGOfParallax
{
public:
	CREATE_FUNC(SceneGame);
	virtual bool init();
	virtual void update(float dt);
	virtual void onEnter();
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onAcceleration(Acceleration* acc, Event* unused_event);  //������Ӧ

	enum {EN_BACKGROUND_ZORDER=-1,EN_HERO_ZORDER=10};

	Sprite* _ship;
	Vector<Sprite*> _asteroids;   //���洴��������
	int _nextAsteroid;
	float _nextAsteroidSpawn;     //ָʾ��һ����ʯ���ֵ�ʱ��㡣���ǻ���updateѭ����һֱ������������ֵ��
	Vector<Sprite*> _shipLasers;  //���洴���ļ���
	int _nextShipLaser;

	SpriteBatchNode* _batchNode;

	float _shipPointsPerSecY;

	void createHero();			//����Ӣ��
	void createGrainStar();     //ʹ������ϵͳ��������
	void InitAsteroid();		//��ʼ������
	void AsteroidBlast(const Point& point);		//����ը
	void InitShipLasers();		//��ʼ������
	void initAudio();			//������Ϸ����Ҫ�õ�������
	void ShipAccelerate(const Point& point);  //�ɴ�����Ч��

	float getTimeTick();
	void setInvisible(Node * node);
	float randomValueBetween(float low, float high);

	double _gameOverTime;
	bool _gameOver;
	int _lives;

	BrainControl* _brainControlShow;

	void ResponseAcceleration(float dt); //��Ӧ���ټ�
	void GenerationAsteroid();  //��������
	void HitCheck();  //��ײ���
};

#endif