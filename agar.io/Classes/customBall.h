#pragma once
#include"cocos2d.h"
class customBall :public cocos2d::Sprite
{
public:
	customBall();
	~customBall();

	//�������
	int Kind;
	//��İ뾶
	float rad;

	//��дcreate
	static customBall* create(const std::string& filename, const int kind);


};

