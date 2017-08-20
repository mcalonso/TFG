#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	Director::getInstance()->setDisplayStats(false);

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

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
	initWorld();
	map = new MapGame(this, world);
	curretPlayer = ignatius;
	otherPlayer = nereita;

	//Init Bots actions

	//Define Game Events
	auto _listener = EventListenerKeyboard::create();
	_listener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressBegan, this);
	_listener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleasedBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(_listener,	this);

	//Define Game schedule Functons
	this->schedule(schedule_selector(GameScene::update), 0.5f);
	this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updateWorld));

    return true;
}

void GameScene::initWorld() 
{
	b2Vec2 gravity;
	gravity.Set(0.0f, -20.0f);
	world = new b2World(gravity);

	world->SetAllowSleeping(false);
	world->SetContinuousPhysics(false);

	contactListener = new MyContactListener(this);
	world->SetContactListener(contactListener);
}

void GameScene::initPlayers(b2Vec2 pos, int type)
{
	if(type == 1)	ignatius = new Player(this, type, pos, world);
	else			nereita = new Player(this, type, pos, world);
}

void GameScene::initBots(b2Vec2 pos, int type)
{
	if (type == 0)		zombi1 = new Bot(this, type, pos, world, &nodos);
}

void GameScene::initGameObjects(b2Vec2 pos, b2Vec2 tam)
{
	obj = new GameObject(this, pos, tam, world);

	objects.push_back(obj);
}

void GameScene::initNodes(b2Vec2 pos, b2Vec2 tam, int name, std::string adds)
{
	nodo = new Nodo(pos, tam, name, 0, NULL);

	char * token;
	char* chr = strdup(adds.c_str());
	token = strtok(chr, ",");

	CCLOG("Nodo Creado: %i", nodo->getNumero());

	while (token != NULL) {
		int i = atoi(token);
		CCLOG("Adyacente: %i", i);
		nodo->addAdyacente(i);
		token = strtok(NULL, ",");
	}

	nodos.push_back(nodo);
}

void GameScene::updateWorld(float dt)
{
	world->Step(dt, VELOCITY_ITINERATIONS, POSITIONS_ITINERATIONS);
	ignatius->updatePlayer();
	nereita->updatePlayer();
	zombi1->updatePlayer();

	for (unsigned int i = 0; i<objects.size(); i++)
	{
		objects.at(i)->updateGameObject();;
	}

	//zombi1->mover();

	world->DrawDebugData();
	world->ClearForces();
}


void GameScene::update(float dt) 
{
	//CCLOG("UPDATE");
	auto cam = Camera::getDefaultCamera();
	float posX = curretPlayer->getPosition().x * PPM;
	float posY = curretPlayer->getPosition().y * PPM;

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
		if(!Director::getInstance()->isDisplayStats())
			Director::getInstance()->setDisplayStats(true);
		else
			Director::getInstance()->setDisplayStats(false);
	}
	else if (code == cocos2d::EventKeyboard::KeyCode::KEY_A) {
		curretPlayer->move(-1);
	}
	else if (code == cocos2d::EventKeyboard::KeyCode::KEY_D) {
		curretPlayer->move(1);
	}
	else if (code == cocos2d::EventKeyboard::KeyCode::KEY_P) {

		if (!curretPlayer->getJumping()) { 
			curretPlayer->stopPlayer(); 
		}

		if (curretPlayer == ignatius) { curretPlayer = nereita; otherPlayer = ignatius; }
		else { curretPlayer = ignatius; otherPlayer = nereita; }
	}
	else if (code == cocos2d::EventKeyboard::KeyCode::KEY_O) {
		/*Nodo* inicial = zombi1->getCercanoTotal(zombi1->getPosition().x, zombi1->getPosition().y);
		Nodo* final = zombi1->getCercanoTotal(curretPlayer->getPosition().x, curretPlayer->getPosition().y);

		CCLOG("Nodo mas cercano al zombi: %i", inicial->getNumero());
		CCLOG("Nodo mas cercano al jugador: %i", final->getNumero());

		zombi1->calcularPathfinding(inicial, final);*/
	}
	else if (code == cocos2d::EventKeyboard::KeyCode::KEY_J) {
		zombi1->mover();
	}


	return true;
}
bool GameScene::onKeyReleasedBegan(cocos2d::EventKeyboard::KeyCode	code, cocos2d::Event *event)
{
	if (code != cocos2d::EventKeyboard::KeyCode::KEY_SPACE)
		curretPlayer->stopPlayer();

	

	return true;
}

void GameScene::setGameObject(GameObject *obj) 
{
	objects.push_back(obj);
}