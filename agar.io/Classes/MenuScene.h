#ifndef _MENU_SCENE_H_
#define _MUNE_SCENE_H_

#include "cocos2d.h"

class GameMenu : public cocos2d::Layer
{
public:
	//��̬����������Scene����
	static cocos2d::Scene* createScene();
	virtual bool init();
    CREATE_FUNC(GameMenu);
};
#endif
