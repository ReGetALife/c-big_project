#ifndef _EXIT_SCENE_H_
#define _EXIT_SCENE_H_

#include "cocos2d.h"

class ExitGame : public cocos2d::Layer
{
public:
	//��̬����������Scene����
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(ExitGame);
};
#endif
