#include"cocos2d.h"

class AudioControl : public cocos2d::Layer
{
public:
	//��̬����������Scene����
	static cocos2d::Scene* createScene();
	//init��������ɳ�ʼ������
	virtual bool init();
	CREATE_FUNC(GameSet);
};