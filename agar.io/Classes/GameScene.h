#pragma once
#include "cocos2d.h"
USING_NS_CC;


class Game : public cocos2d::Layer
{
private:
	int _screenWidth, _screenHeight;
	int _count;
	TMXTiledMap* _map;
	Sprite* player;
public:
	static cocos2d::Scene* createScene();

	//��ö�������
	//Animate* getAnimateByName(std::string animName, float delay, int animNum);
	//����ĻOpenGL����ת��ΪTileMap����
	Vec2 tileCoordForPosition(Vec2 position);
	//��������ƶ�ʱ�亯��
	float getPlayerMoveTime(Vec2 startPos, Vec2 endPos);
	//����ƶ�����
	void playerMover(Vec2 position);
	//�������Ϊ�Ӿ���������ʾ���õ�ͼ������ƶ�
	void setViewPointCenter(Vec2 position);
	//�������ʳ��
	void createfood();
	//��ʱ����ת����
	void foodmagic(float dt);

	virtual bool init();

	//void update(float delta);


	//a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(Game);
};
