#ifndef _FIRST_SCENE_H_
#define _FIRST_SCENE_H_
#include "cocos2d.h"

class EnterScene : public cocos2d::Layer
{
public:
	//��̬����������Scene����
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(EnterScene);
};
#endif
