#include "FirstScene.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "MenuScene.h"
USING_NS_CC;
using namespace ui;

Scene * EnterScene::createScene()
{
	auto scene = Scene::create();
	auto layer = EnterScene::create();
	scene->addChild(layer);
	return scene;
}

bool EnterScene::init()
{
	//���ø����init����
	if (!Layer::init())
	{
		return false;
	}

	//����豸�ɼ���ͼ��С
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//�˵�����
	auto title = Sprite::create("background1.png");
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(title, 0);

	auto transition = TransitionFade::create(12.0, GameMenu::createScene());
	Director::getInstance()->replaceScene(transition);
	this->addChild(transition,0);

	return true;
}