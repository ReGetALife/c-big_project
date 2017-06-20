#include "cocos2d.h"
#include "MenuScene.h"
#include "ChooseScene.h"
#include "ui/CocosGUI.h"
#include"GameScene.h"
#define userDefault CCUserDefault::sharedUserDefault()

USING_NS_CC;
using namespace ui;

Scene * Choose::createScene()
{
	auto scene = Scene::create();
	auto layer = Choose::create();
	scene->addChild(layer);
	return scene;
}

bool Choose::init()
{
	//���ø����init����
	if (!Layer::init())
	{
		return false;
	}

	//����豸�ɼ���ͼ��С
	Size visibleSize = Director::getInstance()->getVisibleSize();

	//�˵�����
	auto title = Sprite::create("menu_background.png");
	title->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(title, 0);

	//"Ƥ��"��ť
	auto choose_button1 = Button::create("Begin.png");
	choose_button1->setPosition(Vec2(visibleSize.width *0.2, visibleSize.height*0.75));
	choose_button1->addTouchEventListener([](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			int getIntegerForKey(const char* pKey, int defaultValue = 1);
			//�л���youxi����
			auto transition = TransitionShrinkGrow::create(1.0, GameScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(choose_button1);
	//2
	auto choose_button2 = Button::create("Begin.png");
	choose_button2->setPosition(Vec2(visibleSize.width *0.5, visibleSize.height*0.75));
	choose_button2->addTouchEventListener([](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			int getIntegerForKey(const char* pKey, int defaultValue = 2);
			//�л���youxi����
			auto transition = TransitionShrinkGrow::create(1.0, GameScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(choose_button2);
	//3
	auto choose_button3 = Button::create("Begin.png");
	choose_button3->setPosition(Vec2(visibleSize.width *0.8, visibleSize.height*0.75));
	choose_button3->addTouchEventListener([](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			int getIntegerForKey(const char* pKey, int defaultValue = 3);
			//�л���youxi����
			auto transition = TransitionShrinkGrow::create(1.0, GameScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(choose_button3);
	//4
	auto choose_button4 = Button::create("Begin.png");
	choose_button1->setPosition(Vec2(visibleSize.width *0.2, visibleSize.height*0.30));
	choose_button1->addTouchEventListener([](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			int getIntegerForKey(const char* pKey, int defaultValue = 4);
			//�л���youxi����
			auto transition = TransitionShrinkGrow::create(1.0, GameScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(choose_button4);
	//5
	auto choose_button5 = Button::create("Begin.png");
	choose_button1->setPosition(Vec2(visibleSize.width *0.5, visibleSize.height*0.30));
	choose_button1->addTouchEventListener([](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			int getIntegerForKey(const char* pKey, int defaultValue = 5);
			//�л���youxi����
			auto transition = TransitionShrinkGrow::create(1.0, GameScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(choose_button5);
	//6
	auto choose_button6 = Button::create("Begin.png");
	choose_button1->setPosition(Vec2(visibleSize.width *0.8, visibleSize.height*0.30));
	choose_button1->addTouchEventListener([](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			int getIntegerForKey(const char* pKey, int defaultValue = 6);
			//�л���youxi����
			auto transition = TransitionShrinkGrow::create(1.0, GameScene::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(choose_button6);

	//����������ť���ʱ����returnToMenu���� 
	auto return_button = Button::create("return.png");
	return_button->setPosition(Vec2(visibleSize.width *0.9, visibleSize.height*0.1));
	return_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			// �л���MenuScene���� 
			auto transition = TransitionShrinkGrow::create(0.2, GameMenu::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(return_button);

	return true;
}


	