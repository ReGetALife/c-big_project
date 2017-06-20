#pragma once
#include "cocos2d.h"
#include"customBall.h"
#include<vector>
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;


class GameScene :public cocos2d::Layer
{
private:
	Label* weightscore;
	int ballTag = 0;
	int _screenWidth, _screenHeight;
	int _Weight;
	Button* return1_button;
public:
	GameScene();
	~GameScene();

    //��������
	cocos2d::PhysicsWorld* m_world;
	//��ͼ
	cocos2d::TMXTiledMap* _map;
	//��ǰʳ������
	int foodCount = 0;
	//���ʳ������
	const int foodMax = 1200;
	//���ɼ�����������
	cocos2d::Sprite* master;

	//��������ı�ʶ��
	const int player = 1;
	const int food = 2;
	const int mass = 3;
	//const int player2 = 2;
	/* And so on......*/
	int aaa = 0;
	bool _checkDT = true;
	//ȷ��W���Ƿ���
	bool _checkWP = false;

	//������������
	void setPhyWorld(cocos2d::PhysicsWorld* world) { m_world = world; };
	//��������
	static cocos2d::Scene* createScene();
	//��ʼ��
	virtual bool init();
	//���ظ���
	void Weightchange(Node * who, Vec2 position);
	//�����򣨳ߴ磬����λ�ã��ٶ��趨�������ࣩ
	void creatBall(float scale, cocos2d::Vect pos, cocos2d::Vect vel,int kind);
	//���������tag
	void ballTagPlusOne();
	//�õ������tag
	int getBallTag();
	//���ϲ���ʳ�����
	void createFood(float dt);
	//�������Ϊ�Ӿ���������ʾ���õ�ͼ������ƶ�
	void setViewPointCenter(Vec2 position);
	//ȷ�Ϸ��ѹ���һ����
	void checkDT(float dt);

	//����ѡ�����
	void returnchoice(Node* who, Vec2 position);
	//
	void onEnter();

	Point  scenecenter(Vec2 position);

	//��дupdate����
	void update(float dt);
	//void update(float dt) override;
	//�Ӵ��¼�����
	bool _onContactBegin(const cocos2d::PhysicsContact & contact);
	//���õ�ͼ����
	//void setViewPointCenter(cocos2d::Vec2 position);
	//void mapMove(cocos2d::Vect pos);
	CREATE_FUNC(GameScene);

};

