#ifndef __SCENE_GAME_TWO_H__
#define __SCENE_GAME_TWO_H__

#include "BrainControl.h"
#include "LayerSBGOfParallax.h"
#include "SimpleAudioEngine.h"
#include "LayerScrollBackGround.h"
#include "Enemy.h"

using namespace CocosDenshion;

#define KNUMASTEROIDS 10  //�������������
#define KNUMLASERS 5      //�������������

class SceneGame : public LayerScrollBackGround
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
	Vector<Enemy*> _asteroids;   //���洴��������
	Vector<Enemy*> _stones;  //���洴������ʯ
	Vector<Enemy*> _ufos;    //����ufo
	int _nextAsteroid;
	float _nextAsteroidSpawn;     //ָʾ��һ��������ֵ�ʱ��㡣���ǻ���updateѭ����һֱ������������ֵ��
	int _nextStone;
	float _nextStoneSpawn;
	int _nextUfo;
	float _nextUfoSpawn;
	Vector<Sprite*> _shipLasers;  //���洴���ļ���
	int _nextShipLaser;

	SpriteBatchNode* _batchNode;

	float _shipPointsPerSecY;

	void createHero();			//����Ӣ��
	void createGrainStar();     //ʹ������ϵͳ��������
	void InitAsteroid();		//��ʼ������
	void InitStones();          //��ʼ����ʯ
	void InitUFO();         
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
	void GenerationStone();  //���������ƶ�����ʯ
	void GenerationUFO();   //����UFO
	void HitCheck();  //��ײ���
	void HitCheckWithUfo();
};

#endif