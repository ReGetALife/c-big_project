#include "GameScene.h"
#include<math.h>
#include "ui/CocosGUI.h"
#include "MenuScene.h"
#include "string"
USING_NS_CC;
using namespace ui;
using namespace std;


GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}
cocos2d::Scene* GameScene::createScene()
{
	//����������ռ�ĳ���
	cocos2d::Scene* scene = cocos2d::Scene::createWithPhysics();
	//����Debugģʽ����ῴ������ı��汻������Χ����ҪΪ���ڵ����и����׵ع۲�
	//scene->getPhysicsWorld()->setDebugDrawMask(cocos2d::PhysicsWorld::DEBUGDRAW_ALL);
	GameScene* layer = GameScene::create();
	//�ѿռ䱣�����Ǵ����Ĳ��У�����������˵m_world�����ã�����������ÿռ�Ĳ���
	layer->setPhyWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	_screenWidth = visibleSize.width;
	_screenHeight = visibleSize.height;

	//��ӵ�ͼ
	_map = TMXTiledMap::create("_map.tmx");
	_map->setAnchorPoint(Vec2::ZERO);
	_map->setPosition(Vec2::ZERO);
	this->addChild(_map);
	_map->setTag(0);







	//��һ����
	GameScene::creatBall(0.5f, Vect(_map->getMapSize().width*_map->getTileSize().width/2, _map->getMapSize().height*_map->getTileSize().height / 2), Vect(0.f, 0.f), player);
	//ʳ��
	creatBall(0.1f, Vect(visibleSize.width / 2, visibleSize.height / 2), Vect(0.f, 0.f),food);

	//������ǩ
	_Weight = 100;
	char a[8];
	//����ת�ַ���
	char score[20] = "score:";
	sprintf(a, "%d", _Weight);
	strcat(score, a);
	weightscore = Label::createWithSystemFont(score, "Arial", 32);
	weightscore->setPosition(_map->getMapSize().width*_map->getTileSize().width / 2 - 300, _map->getMapSize().height*_map->getTileSize().height / 2 + 185);
	this->addChild(weightscore);


	//��������
	return1_button = Button::create("return.png");
	return1_button->setPosition(Vec2(_map->getMapSize().width*_map->getTileSize().width / 2+350, _map->getMapSize().height*_map->getTileSize().height / 2+185));
	return1_button->addTouchEventListener([](Ref* pSender, Widget::TouchEventType type)
	{
		if (type == Widget::TouchEventType::ENDED)
		{
			// �л���MenuScene���� 
			auto transition = TransitionShrinkGrow::create(0.2, GameMenu::createScene());
			Director::getInstance()->replaceScene(transition);
		}
	});
	this->addChild(return1_button);

	//����һ�����ӣ�������ײ
	Sprite* edgeSpace = Sprite::create();
	PhysicsBody* boundBody = PhysicsBody::createEdgeBox(Size(_map->getMapSize().width*_map->getTileSize().width, _map->getMapSize().height*_map->getTileSize().height), PHYSICSBODY_MATERIAL_DEFAULT);
	boundBody->getShape(0)->setFriction(0.0f);
	boundBody->getShape(0)->setRestitution(0.1f);

	edgeSpace->setPhysicsBody(boundBody);
	edgeSpace->setPosition(Point(_map->getMapSize().width*_map->getTileSize().width / 2, _map->getMapSize().height*_map->getTileSize().height / 2));
	this->addChild(edgeSpace);
	edgeSpace->setTag(10);


	//���̼��������Ʒ���
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			Vector<Node*> children = this->getChildren();
			for (auto n : children)
			{
				if (((n->getTag() % 10) == player)&&(n->getScale()>0.3f))
				{
					creatBall((n->getScale()) / 1.2599, n->getPosition(), n->getPhysicsBody()->getVelocity() * 2, player);
					creatBall((n->getScale()) / 1.2599, n->getPosition(), n->getPhysicsBody()->getVelocity(), player);
					n->removeFromParentAndCleanup(true);
					_checkDT = false;//�������Ѻ��ʱ�����ں�
				}
			}
			scheduleOnce(schedule_selector(GameScene::checkDT), 10.f);
		}
		else if (keyCode == EventKeyboard::KeyCode::KEY_W)
		{
			_checkWP = true;
		}
	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		if (keyCode == EventKeyboard::KeyCode::KEY_W)
			_checkWP = false;

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//���������������˶�
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [=](Touch* touch, Event* ev) {
		Vector<Node*> balls = this->getChildren();
		for (auto n : balls)
		{
			if (n->getTag() % 10 == player)
			{
				n->getPhysicsBody()->applyImpulse(((this->convertToNodeSpace(touch->getLocation())) - (n->getPosition())) * 1000);
			}
		}
		return true;
	};
	touchListener->onTouchMoved = [=](Touch* touch, Event* event) {
		Vector<Node*> balls = this->getChildren();
		for (auto n : balls)
		{
			if (n->getTag() % 10 == player)
			{
				n->getPhysicsBody()->applyImpulse(((this->convertToNodeSpace(touch->getLocation())) - (n->getPosition())) * 1000);
			}
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
	

	
	//��ӽӴ�����ײ��������
	auto contactListener = EventListenerPhysicsContact::create();
	//���ü���������ײ��ʼ����
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::_onContactBegin, this);
	//��ӵ��¼��ַ�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	//��ӵ�����
	scheduleUpdate();
	//��ʱ�� 
	schedule(schedule_selector(GameScene::createFood), 0.1f);

	this->schedule(schedule_selector(GameScene::update), 1 / 60);

	return true;
}


void GameScene::Weightchange(Node* who, Vec2 position)
{
	who->removeFromParentAndCleanup(true);
	char a[8];
	char score[20] = "score:";
	//����ת�ַ���
	sprintf(a, "%d", _Weight);
	strcat(score, a);
	weightscore = Label::createWithSystemFont(score, "Arial", 32);
	weightscore->setPosition(scenecenter(position).x - 300, scenecenter(position).y + 185);
	this->addChild(weightscore);
}


void GameScene::creatBall(float scale, Vect pos, Vect vel,int kind)
{

	if (kind == player)
	{
		auto ball = customBall::create("mengB.png", kind);
		//����ߴ�
		ball->setScale(scale);
		//����λ��
		ball->setPosition(pos);
		//��뾶
		ball->rad = ball->getContentSize().width / 2;
		//�������壬�����������״ΪԲ�Σ���һ����Ϊ�뾶���ڶ�������Ϊ�������
		//����������Ϊ�ߵĺ��,������Debugģʽ�¿������������������ĺ�ȣ�Ĭ��Ϊ0
		PhysicsBody* ballBody = PhysicsBody::createCircle(ball->rad, PHYSICSBODY_MATERIAL_DEFAULT);
		//�Ƿ���������Ϊ��̬
		//ballBody->setDynamic(true);
		//��������Ļָ��������ԣ�
		ballBody->getShape(0)->setRestitution(0.1f);
		//���������Ħ������ֻ����ײʱ�����ã�
		ballBody->getShape(0)->setFriction(0.0f);
		//���������ܶ�
		ballBody->getShape(0)->setDensity(1.f);
		//��������
		//ballBodyOne->getShape(0)->setMass(5000);
		//���������Ƿ�������ϵ��Ӱ��
		ballBody->setGravityEnable(false);

		//��������ĳ���
		Vect force = Vect(0.0f, 0.0f);
		ballBody->applyImpulse(force);
		//�����ٶ�
		ballBody->setVelocity(vel);
		ballBody->setVelocityLimit(20000.f / ball->rad);
		//��������ӵ�������
		ball->setPhysicsBody(ballBody);
		//���ñ�־
		ball->setTag(getBallTag()*10+kind);
		//���÷�������
		ballBody->setCategoryBitmask(0x0001);
		//������ײ����
		ballBody->setCollisionBitmask(0x0001);
		//���ýӴ���������
		ballBody->setContactTestBitmask(0x0001);

		this->addChild(ball);
		//���tag��һ
		ballTagPlusOne();
		
	}
	else if (kind == food)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		for (;foodCount != foodMax;)
		{
			auto ball = customBall::create("food.png", kind);
			ball->setScale(scale);
			int y = rand() % (int)( _map->getMapSize().height*_map->getTileSize().height);
			int x = rand() % (int)(_map->getMapSize().width*_map->getTileSize().width );
			ball->setPosition(x, y);
			ball->rad = ball->getContentSize().width / 2;
			PhysicsBody* ballBody = PhysicsBody::createCircle(ball->rad, PHYSICSBODY_MATERIAL_DEFAULT);
			//ballBody->setDynamic(true);
			ballBody->getShape(0)->setRestitution(0.1f);
			ballBody->getShape(0)->setFriction(0.0f);
			ballBody->getShape(0)->setDensity(1.0f);
			//ballBodyOne->getShape(0)->setMass(5000);
			ballBody->setGravityEnable(false);

			//Vect force = Vect(0.0f, 0.0f);
			//ballBody->applyImpulse(force);
			//ballBody->setVelocity(vel);
			ballBody->setVelocityLimit(1.f / ball->rad);
			ball->setPhysicsBody(ballBody);
			ball->setTag(getBallTag()*10+kind);
			ballBody->setCategoryBitmask(0x0001);
			ballBody->setCollisionBitmask(0x0001);
			ballBody->setContactTestBitmask(0x0001);

			this->addChild(ball);
			ballTagPlusOne();
			++foodCount;
		}
	}
	else if (kind == mass)
	{
		auto ball = customBall::create("mass.png", kind);
		ball->setScale(scale);
		ball->setPosition(pos);
		ball->rad = ball->getContentSize().width / 2;
		PhysicsBody* ballBody = PhysicsBody::createCircle(ball->rad, PHYSICSBODY_MATERIAL_DEFAULT);
		//ballBody->setDynamic(true);
		ballBody->getShape(0)->setRestitution(0.1f);
		ballBody->getShape(0)->setFriction(0.0f);
		//������������ʹ��ֹͣ
		ballBody->setLinearDamping(8.f);
		ballBody->getShape(0)->setDensity(1.0f);
		//ballBodyOne->getShape(0)->setMass(5000);
		ballBody->setGravityEnable(false);

		//Vect force = Vect(0.0f, 0.0f);
		//ballBody->applyImpulse(force);
		ballBody->setVelocity(vel);
		//ballBody->setVelocityLimit(20000.f / ball->rad);
		ball->setPhysicsBody(ballBody);
		ball->setTag(getBallTag() * 10 + kind);
		ballBody->setCategoryBitmask(0x0001);
		ballBody->setCollisionBitmask(0x0001);
		ballBody->setContactTestBitmask(0x0001);

		this->addChild(ball);
		ballTagPlusOne();
	}
}

void GameScene::ballTagPlusOne()
{
	++ballTag;
}

int GameScene::getBallTag()
{
	return ballTag;
}

void GameScene::createFood(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	creatBall(0.1f, Vect(_map->getMapSize().width*_map->getTileSize().width / 2, _map->getMapSize().height*_map->getTileSize().height / 2), Vect(0.f, 0.f), food);
	if (_checkWP)//����mass
	{
		Vector<Node*> children = this->getChildren();
		for (auto n : children)
		{
			if (((n->getTag() % 10) == player) && (n->getScale() > 0.3f))
			{
				creatBall(0.15f, n->getPosition(), n->getPhysicsBody()->getVelocity()* 15, mass);
				float newScale = pow(((n->getScale()*n->getScale()*n->getScale())-0.003375f), 0.333333f);
				creatBall(newScale, n->getPosition(), n->getPhysicsBody()->getVelocity(), player);
				_Weight -= 15;
				n->removeFromParentAndCleanup(true);
			}
		}
	}

}

void GameScene::checkDT(float dt)
{
	_checkDT = true;
}

void GameScene::onEnter()
{
	Layer::onEnter();
	//��Ӽ�����
	auto contactListener = EventListenerPhysicsContact::create();
	//���ü���������ײ��ʼ����
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::_onContactBegin, this);
	//��ӵ��¼��ַ�����
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

//��ͼ����Ѱ�Һ���
Point GameScene::scenecenter(Vec2 position)
{
	int x = MAX(position.x, _screenWidth / 2);
	int y = MAX(position.y, _screenHeight / 2);

	x = MIN(x, (_map->getMapSize().width*_map->getTileSize().width - _screenWidth / 2));
	y = MIN(y, (_map->getMapSize().height*_map->getTileSize().height - _screenHeight / 2));
	return Point(x, y);
}


void GameScene::returnchoice(Node* who, Vec2 position)
{
	who->setPosition(Vec2(scenecenter(position)).x+350, Vec2(scenecenter(position)).y+185);
}

void GameScene::setViewPointCenter(Vec2 position)
{
	
	Point actualPosition =scenecenter(position);

	Point centerOfView = Point(_screenWidth / 2, _screenHeight / 2);
	Point viewPoint = centerOfView - actualPosition;
	//Point try1 = Point(x + 10, y + 10);
	this->setPosition(viewPoint);
	//this->runAction(MoveTo::create(1.0f, viewPoint));
	//this->runAction(MoveTo::create(0.01f, Point(3000,3000));
}


void GameScene::update(float dt)
{
	Vector<Node*> children = this->getChildren();
	int index = 0;
	for (auto n : children)
	{
		if (n->getTag() %10 == player)
		{
			setViewPointCenter(n->getPosition());
			Weightchange(weightscore, n->getPosition());
			returnchoice(return1_button, n->getPosition());
			++index;
			if (index != 0)break;
		}
	}
}

/*void GameScene::update(float dt)
{
	Vector<Node*> balls = this->getChildren();
	for (auto n : balls)
	{
		PhysicsBody *_ballbody = n->getPhysicsBody();
		_ballbody->setVelocity(eventMouse->getLocation());
	}
}*/

bool GameScene::_onContactBegin(const PhysicsContact& contact)
{
	auto spriteA =contact.getShapeA()->getBody()->getNode();
	auto spriteB =contact.getShapeB()->getBody()->getNode();
	if ((spriteA != nullptr) && (spriteB != nullptr))
	{
		if (aaa % 2 == 1)
		{
			int tagA = spriteA->getTag();
			int tagB = spriteB->getTag();
			if ((tagA % 10 == 1) && (tagB % 10 == 1) && _checkDT)
			{
				float newScale = pow((spriteA->getScale()*spriteA->getScale()*spriteA->getScale()) + (spriteB->getScale()*spriteB->getScale()*spriteB->getScale()), 0.333333f);
				spriteA->setScale(newScale);
				spriteB->removeFromParentAndCleanup(true);
				unschedule(schedule_selector(GameScene::checkDT));
			}
			else if ((tagA % 10 == 1) && (tagB % 10 == 2))
			{
				float newScale = pow((spriteA->getScale()*spriteA->getScale()*spriteA->getScale()) + (spriteB->getScale()*spriteB->getScale()*spriteB->getScale()), 0.333333f);
				spriteA->setScale(newScale);
				spriteB->removeFromParentAndCleanup(true);
				_Weight += 10;
				--foodCount;
			}
			else if ((tagA % 10 == 2) && (tagB % 10 == 1))
			{
				float newScale = pow((spriteA->getScale()*spriteA->getScale()*spriteA->getScale()) + (spriteB->getScale()*spriteB->getScale()*spriteB->getScale()), 0.333333f);
				spriteB->setScale(newScale);
				spriteA->removeFromParentAndCleanup(true);
				_Weight += 10;
				--foodCount;
			}
			else if ((tagA % 10 == 1) && (tagB % 10 == 3) && (!_checkWP))
			{
				float newScale = pow((spriteA->getScale()*spriteA->getScale()*spriteA->getScale()) + (spriteB->getScale()*spriteB->getScale()*spriteB->getScale()), 0.333333);
				spriteA->setScale(newScale);
				spriteB->removeFromParentAndCleanup(true);
				_Weight += 15;
			}
			else if ((tagA % 10 == 3) && (tagB % 10 == 1) && (!_checkWP))
			{
				float newScale = pow((spriteA->getScale()*spriteA->getScale()*spriteA->getScale()) + (spriteB->getScale()*spriteB->getScale()*spriteB->getScale()), 0.333333);
				spriteB->setScale(newScale);
				spriteA->removeFromParentAndCleanup(true);
				_Weight += 15;
			}
		}
		++aaa;
	}
	//log("%d and %d", tagA, tagB);
	return true;
}


