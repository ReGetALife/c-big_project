#include "cocos2d.h"
#include "VectorLayer.h"
#include "MenuScene.h"
#include "ChooseScene.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

Scene * VectorLayer::createScene()
{
	auto scene = Scene::create();
	auto layer = VectorLayer::create();
	scene->addChild(layer);
	return scene;
}

bool VectorLayer::init()
{
	//���ø����init����
	if (!Layer::init())
	{
		return false;
	}

	//����豸�ɼ���ͼ��С
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//�˵�����
	auto title = Sprite::create("vector.png");
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(title, 0);

	//"����һ��"��ť
	auto restart_button = Button::create("restart.png");
	restart_button->setPosition(Vec2(visibleSize.width *0.4, visibleSize.height*0.4));
	restart_button->addTouchEventListener([](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			//�л���pifu����
			auto transition = TransitionShrinkGrow::create(1.0, Choose::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(restart_button);
	//"���ز˵�"��ť
	auto back_button = Button::create("back.png");
	back_button->setPosition(Vec2(visibleSize.width *0.6, visibleSize.height*0.4));
	back_button->addTouchEventListener([](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			//�л���caidan����
			auto transition = TransitionShrinkGrow::create(1.0, GameMenu::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(back_button);

	return true;
}