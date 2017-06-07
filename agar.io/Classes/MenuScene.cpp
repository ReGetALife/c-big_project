#include "cocos2d.h"
#include "MenuScene.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace ui;
cocos2d::Scene * GameMenu::createScene()
{
	return nullptr;
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

	//"��ʼ��Ϸ"��ť
	auto start_button = Button::create("button.png");
	start_button->setScale(2);
	start_button->setTitleText("��ʼ��Ϸ");
	start_button->setTitleFontName("΢���ź�");
	start_button->setTitleFontSize(16);
	start_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.7));
	start_button->addTouchEventListener([](Ref*pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED) 
		{
			//�л���preload����
			auto transition = TransitionSlideInL::create(2.0, PreLoad::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(start_button);
	//"��Ϸ����"��ť
	auto set_button = Button::create("button.png");
	set_button->setScale(2);
	set_button->setTitleText("��Ϸ����");
	set_button->setTitleFontName("΢���ź�");
	set_button->setTitleFontSize(16);
	set_button->setPosition(Vec2(visibleSize. width / 2, visibleSize.height*0.55));
	set_button->addTouchEventListener([](Ref*pSender, Widget::TouchEventType type)
		{
			if (type == Widget::TouchEventType::ENDED)
			{
				//�л���AudioControl����
				auto transition = TransitionSlideInL::create(2.0, AudioControlScene::createScene());
				Director::getInstance()->replaceScene(transition);
			}
		});
	this->addChild(set_button);
	//"�˳���Ϸ"��ť
	auto close_button = Button::create("button.png");
	close_button->setScale(2);
	close_button->setTitleText("��Ϸ����");
	close_button->setTitleFontName("΢���ź�");
	close_button->setTitleFontSize(16);
	close_button->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*0.4));
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

GameMenu::CREATE_FUNC(GameMenu)
{
}
