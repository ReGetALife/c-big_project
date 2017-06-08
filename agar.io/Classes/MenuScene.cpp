#include"cocos2d.h"
#include "MenuScene.h"
#include"AudioControlScene.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;

Scene * GameMenu::createScene()
{
	auto scene = Scene::create();
    auto layer = GameMenu::create();
	scene->addChild(layer);
	return scene;
}
bool GameMenu::init()
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
	title->setPosition(Vec2(visibleSize.width/2 , visibleSize.height/2 ));
	this->addChild(title,0);
	
	//"��ʼ��Ϸ"��ť
	auto start_button = Button::create("Begin.png");
	start_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.6));
	/*start_button->addTouchEventListener([](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED) 
		{
			//�л���preload����
			auto transition = TransitionShrinkGrow::create(1.0, preload::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});*/ 
	this->addChild(start_button);
	
	//"��Ϸ����"��ť
	auto set_button = Button::create("Setting.png");
	set_button->setPosition(Vec2(visibleSize. width / 2, visibleSize.height*0.45));
	set_button->addTouchEventListener([](Ref*pSender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				//�л���AudioControl����
				auto transition = TransitionShrinkGrow::create(0.2, AudioControl::createScene());
				Director::getInstance()->replaceScene(transition);
			}
		});
	this->addChild(set_button);
	
	//"�˳���Ϸ"��ť
	auto close_button = Button::create("Exit.png");
	close_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.3));
	close_button->addTouchEventListener([](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
          #if (CC_TARGET_PLATFORM ==CC_PLATFORM_WP8) || (CC_TARGET_PLATFROM ==CC_PLATFORM_WINRT)
			MessageBox("You pressed the cliose button.Window Store Apps do not implement a close button.", "Alert");
			return;
          #endif
			Director::getInstance()->end();

		}
	});
	this->addChild(close_button);
	return true;
}


