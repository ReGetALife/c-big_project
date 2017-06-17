#include "ExitScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"
USING_NS_CC;
using namespace ui;

Scene * ExitGame::createScene()
{
	auto scene = Scene::create();
	auto layer = ExitGame::create();
	scene->addChild(layer);
	return scene;
}

bool ExitGame::init()
{
	//���ø����init����
	if (!Layer::init())
	{
		return false;
	}

	//����豸�ɼ���ͼ��С
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//�˵�����
	auto title = Sprite::create("background2.png");
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(title, 0);

    #if (CC_TARGET_PLATFORM ==CC_PLATFORM_WP8) || (CC_TARGET_PLATFROM ==CC_PLATFORM_WINRT)
	MessageBox("You pressed the cliose button.Window Store Apps do not implement a close button.", "Alert");
	return;
    #endif
	Director::getInstance()->end();


	return true;
}