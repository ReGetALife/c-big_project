#include "cocos2d.h"
#include "GameScene.h"
USING_NS_CC;


bool Game::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	_screenWidth = visibleSize.width;
	_screenHeight = visibleSize.height;


	//��ӵ�ͼ
	_map = TMXTiledMap::create("_map.tmx");
	_map->setAnchorPoint(Vec2::ZERO);
	_map->setPosition(Vec2::ZERO);
	this->addChild(_map);




	//�����
	player = Sprite::create("qiu.png");
	player->setPosition(_screenWidth / 2, _screenHeight / 2);
	this->addChild(player);


	_map->addChild(player, 2);


	auto gameListener = EventListenerTouchOneByOne::create();

	gameListener->onTouchBegan = [](Touch* touch, Event* event) {return true; };
	gameListener->onTouchEnded = [this](Touch* touch, Event* event)
	{
		Vec2 touchLocation = touch->getLocation();
		Vec2 nodeLocation = this->convertToNodeSpace(touchLocation);
		if (player->getNumberOfRunningActions() == 0)
		{
			this->playerMover(nodeLocation);
		}
		else
		{
			player->stopAllActions();
			this->stopAllActions();
			this->playerMover(nodeLocation);
		}
	};

	//ÿ1�����һ����ת������ָ������ʳ�ﺯ����
	this->schedule(schedule_selector(Game::foodmagic), 1);

	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(gameListener, this);

	return true;
}

//��opengl����ת��Ϊtilemap����
Vec2 Game::tileCoordForPosition(Vec2 position)
{
	int x = (int)(position.x / (_map->getTileSize().width / CC_CONTENT_SCALE_FACTOR()));
	float pointHeight = _map->getTileSize().height / CC_CONTENT_SCALE_FACTOR();
	int y = (int)((_map->getMapSize().height* pointHeight - position.y) / pointHeight);
	return Vec2(x, y);
}

//��������ƶ�ʱ��
float Game::getPlayerMoveTime(Vec2 startPos, Vec2 endPos)
{
	Vec2 tileStart = tileCoordForPosition(startPos);

	Vec2 tileEnd = tileCoordForPosition(endPos);
	//�ƶ�һ�������ʱ��
	float duration = 0.01f;
	//�����ƶ���������ƶ�ʱ��
	duration = duration*sqrtf((tileStart.x - tileEnd.x)*(tileStart.x - tileEnd.x) + (tileStart.y - tileEnd.y)*(tileStart.y - tileEnd.y));
	return duration;
}

//���ƶ�
void Game::playerMover(Point position)
{
	float duration = getPlayerMoveTime(player->getPosition(), position);
	auto moveTo = MoveTo::create(duration, position);
	auto sequence = Sequence::create(moveTo, nullptr);
	player->runAction(sequence);
}

//��ͼ��
void Game::setViewPointCenter(float duration, Vec2 position)
{
	int x = MAX(position.x, _screenWidth / 2);
	int y = MAX(position.y, _screenHeight / 2);

	x = MIN(x, (_map->getMapSize().width*_map->getTileSize().width - _screenWidth / 2));
	y = MIN(y, (_map->getMapSize().height*_map->getTileSize().height - _screenHeight / 2));
	Point actualPosition = Point(x, y);
	Point centerOfView = Point(_screenWidth / 2, _screenHeight / 2);
	Point viewPoint = centerOfView - actualPosition;
	this->runAction(MoveTo::create(duration, viewPoint));

}

//��ת
void Game::foodmagic(float dt)
{
	createfood();
}

//�������ʳ��
void Game::createfood()
{
	Sprite* _food = Sprite::create("food1.png");
	int y = rand() % (int)(_screenHeight);
	int x = rand() % (int)(_screenHeight);
	_food->setPosition(x, y);
	this->addChild(_food);


}


/*

GameScene::GameScene()
{
}


GameScene::~GameScene()
{
}
*/