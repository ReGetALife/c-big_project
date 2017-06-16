#include "GameScene.h"
#include<math.h>
USING_NS_CC;
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

	//��ӵ�ͼ
	_map = TMXTiledMap::create("_map.tmx");
	_map->setAnchorPoint(Vec2::ZERO);
	_map->setPosition(Vec2::ZERO);
	this->addChild(_map);
	_map->setTag(0);

	//��һ����
	GameScene::creatBall(0.5f, Vect(visibleSize.width / 2, visibleSize.height / 2), Vect(0.f, 0.f), player);
	//ʳ��
	creatBall(0.1f, Vect(visibleSize.width / 2, visibleSize.height / 2), Vect(0.f, 0.f),food);


	//����һ�����ӣ�������ײ
	Sprite* edgeSpace = Sprite::create();
	PhysicsBody* boundBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT);
	boundBody->getShape(0)->setFriction(0.0f);
	boundBody->getShape(0)->setRestitution(0.1f);

	edgeSpace->setPhysicsBody(boundBody);
	edgeSpace->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(edgeSpace);
	edgeSpace->setTag(10);


	//���̼��������Ʒ���
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		log("Key with keycode %d pressed", keyCode);
		if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
		{
			Vector<Node*> children = this->getChildren();
			for (auto n : children)
				if ((n->getTag() % 10) == player)
				{
					creatBall((n->getScale()) / 1.2599, n->getPosition(), n->getPhysicsBody()->getVelocity() * 2, player);
					creatBall((n->getScale()) / 1.2599, n->getPosition(), n->getPhysicsBody()->getVelocity(), player);
					n->removeFromParentAndCleanup(true);
				}
		}
	};
	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event) {
		log("Key with keycode %d released", keyCode);

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
				n->getPhysicsBody()->applyImpulse(((touch->getLocation()) - (n->getPosition())) * 1000);
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
				n->getPhysicsBody()->applyImpulse(((touch->getLocation()) - (n->getPosition())) * 1000);
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
	schedule(schedule_selector(GameScene::createFood), 1.f);

	return true;
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
		//���������Ħ����
		ballBody->getShape(0)->setFriction(0.0f);
		//���������ܶ�
		ballBody->getShape(0)->setDensity(1.0f);
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
			auto ball = customBall::create("mengB.png", kind);
			ball->setScale(scale);
			int y = rand() % (int)(visibleSize.height);
			int x = rand() % (int)(visibleSize.width);
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
	creatBall(0.1f, Vect(visibleSize.width / 2, visibleSize.height / 2), Vect(0.f, 0.f), food);
	log("ok");
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
	customBall* spriteB = (customBall*)contact.getShapeB()->getBody()->getNode();
	if (aaa%2==1)
	{
		int tagA = spriteA->getTag();
		int tagB = spriteB->getTag();
		if ((tagA % 10 == 1) && (tagB % 10 == 1))
		{
			float newScale = pow((spriteA->getScale()*spriteA->getScale()*spriteA->getScale()) + (spriteB->getScale()*spriteB->getScale()*spriteB->getScale()), 0.333333);
			spriteA->setScale(newScale);
			spriteB->removeFromParentAndCleanup(true);
		}
		else if ((tagA % 10 == 1) && (tagB % 10 == 2))
		{
			float newScale = pow((spriteA->getScale()*spriteA->getScale()*spriteA->getScale()) + (spriteB->getScale()*spriteB->getScale()*spriteB->getScale()), 0.333333);
			spriteA->setScale(newScale);
			spriteB->removeFromParentAndCleanup(true);
			--foodCount;
		}
		else if ((tagA % 10 == 2) && (tagB % 10 == 1))
		{
			float newScale = pow((spriteA->getScale()*spriteA->getScale()*spriteA->getScale()) + (spriteB->getScale()*spriteB->getScale()*spriteB->getScale()), 0.333333);
			spriteB->setScale(newScale);
			spriteA->removeFromParentAndCleanup(true);
			--foodCount;
		}
	}
	++aaa;
	//log("%d and %d", tagA, tagB);
	return true;
}


