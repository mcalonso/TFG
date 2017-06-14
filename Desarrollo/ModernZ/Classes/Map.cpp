#include "Map.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

MapGame::MapGame(cocos2d::Layer *layer) {

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	backgroundSprite = Sprite::create("maps/backgroundMap1.jpg");
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

		CCLOG("Recogidos: %f %f %f %f", x, y, tamh, tamw);

		auto physicsBody = PhysicsBody::createBox(Size(16, 16),
			PhysicsMaterial(0.1f, 1.0f, 0.0f));
		physicsBody->setDynamic(false);

		auto sprite = Sprite::create("blueSprite.png");
		sprite->setPosition(Vec2(x,y));
		sprite->setPhysicsBody(physicsBody);

		layer->addChild(sprite);

	}

	CCLOG("Fin de la carga de mapa");
}