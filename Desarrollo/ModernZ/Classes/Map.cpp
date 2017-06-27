#include "Map.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <Box2D/Box2D.h>

USING_NS_CC;

MapGame::MapGame(cocos2d::Layer *layer, b2World *w) {

	world = w;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	backgroundSprite = Sprite::create("maps/backgroundMap11.jpg");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	layer->addChild(backgroundSprite);

	backgoundMap = TMXTiledMap::create("maps/map1.tmx");
	layer->addChild(backgoundMap);

	CCLOG("Empieza la carga de mapa");

	float x;
	float y;
	float tamh;
	float tamw;

	TMXObjectGroup	*objectsGroup = backgoundMap->getObjectGroup("colisiones");

	auto& objects = objectsGroup->getObjects();
	for (auto &obj : objects) {
		auto &properties = obj.asValueMap();
		x = properties["x"].asFloat();
		y = properties["y"].asFloat();
		tamh = properties["height"].asFloat();
		tamw = properties["width"].asFloat();

		CCLOG("Recogidos: %f %f %f %f", x, y, tamw, tamh);

		/*auto physicsBody = PhysicsBody::createBox(Size(tamw, tamh),
			PhysicsMaterial(0.1f, 1.0f, 0.0f));
		physicsBody->setDynamic(false);
		physicsBody->setCollisionBitmask(2);
		physicsBody->setContactTestBitmask(true);*/

		auto sprite = Sprite::create("maps/tm.png");
		sprite->setPosition(Vec2(x + (tamw / 2), y + (tamh / 2)));
		//sprite->setPhysicsBody(physicsBody);

		layer->addChild(sprite);

	}

	objectsGroup = backgoundMap->getObjectGroup("objetos");

	objects = objectsGroup->getObjects();
	for (auto &obj : objects) {
		auto &properties = obj.asValueMap();
		x = properties["x"].asFloat();
		y = properties["y"].asFloat();
		tamh = properties["height"].asFloat();
		tamw = properties["width"].asFloat();

		CCLOG("Recogidos: %f %f %f %f", x, y, tamw, tamh);

		b2BodyDef auxBodyDef;
		auxBodyDef.position.Set((x + (tamw / 2))*MPP, (y + (tamh / 2))*MPP);
		b2Body* auxBody = world->CreateBody(&auxBodyDef);
		b2PolygonShape auxBox;
		//bodies->insert(bodies->begin(), auxBody);
		auxBox.SetAsBox(tamw / 2 * MPP, tamh / 2 * MPP);
		b2Fixture* auxFixture = auxBody->CreateFixture(&auxBox, 0.0f);
		auxFixture->SetUserData((void*)999);
		b2Filter filter = auxFixture->GetFilterData();
		filter.categoryBits = 2;
		auxFixture->SetFilterData(filter);

		auto sprite = Sprite::create("maps/tm.png");
		sprite->setPosition(Vec2(x + (tamw / 2), y + (tamh / 2)));

		layer->addChild(sprite);

	}

	CCLOG("Fin de la carga de mapa");
}