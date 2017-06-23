#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	Director::getInstance()->setDisplayStats(false);

	// 'layer' is an autorelease object
	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	// add layer as a child to scene
	scene->addChild(layer);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	//Define Position Variables
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
	offSetX = visibleSize.width / 2 + origin.x;
	offSetY = visibleSize.height / 2 + origin.y;

	//Define Game Objects
	map = new MapGame(this);
	ignatius = new Player(this, 1);
	nereita = new Player(this, 2);
	curretPlayer = ignatius;

	//Define Game Events
	auto _listener = EventListenerKeyboard::create();
	_listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressBegan, this);
	_listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleasedBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener,	this);

	auto _contactListener = EventListenerPhysicsContact::create(); 
	_contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_contactListener, this);

	//Define Game schedule Functons
	this->schedule(schedule_selector(GameScene::update), 0.5f);

    return true;
}

void GameScene::update(float dt) 
{
	//CCLOG("UPDATE");
	auto cam = Camera::getDefaultCamera();
	float posX = curretPlayer->getPosition().x;
	float posY = curretPlayer->getPosition().y;

	if (posX < offSetX)
		posX = offSetX;
	if (posY < offSetY )
		posY = offSetY;

	float z = cam->getPosition3D().z;
	CCMoveTo* action = CCMoveTo::create(0.5f, Vec3(posX, posY, z));
	cam->runAction(action);

	CCMoveTo* action2 = CCMoveTo::create(0.5f, Vec2(posX, posY));
	map->getBackgroundSprite()->runAction(action2);
}

bool GameScene::onKeyPressBegan(cocos2d::EventKeyboard::KeyCode	code, cocos2d::Event *event)
{
	if (code == cocos2d::EventKeyboard::KeyCode::KEY_SPACE)
	{
		curretPlayer->jump(1);
	}
	else if (code == cocos2d::EventKeyboard::KeyCode::KEY_F1) {
		if (this->getScene()->getPhysicsWorld()->getDebugDrawMask() == 0)
		{
			this->getScene()->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
			Director::getInstance()->setDisplayStats(true);
		}
		else {
			this->getScene()->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
			Director::getInstance()->setDisplayStats(false);
		}
	}
	else if (code == cocos2d::EventKeyboard::KeyCode::KEY_A) {
		curretPlayer->move(-1);
	}
	else if (code == cocos2d::EventKeyboard::KeyCode::KEY_D) {
		curretPlayer->move(1);
	}
	else if (code == cocos2d::EventKeyboard::KeyCode::KEY_P) {
		if (curretPlayer == ignatius) { curretPlayer = nereita; }
		else { curretPlayer = ignatius; }
	}

	return true;
}
bool GameScene::onKeyReleasedBegan(cocos2d::EventKeyboard::KeyCode	code, cocos2d::Event *event)
{
	curretPlayer->stopPlayer();

	return true;
}

bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact){

	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	if ((a->getCollisionBitmask() == 1 && b->getCollisionBitmask() == 2) || (a->getCollisionBitmask() == 2 && b->getCollisionBitmask() == 1)) {
		curretPlayer->setJumping(false);
		//CCLOG("Contacto");
	}

	return true;
}
