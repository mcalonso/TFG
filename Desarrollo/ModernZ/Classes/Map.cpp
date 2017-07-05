#include "Map.h"
#include "Definitions.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <Box2D/Box2D.h>

USING_NS_CC;

MapGame::MapGame(GameScene *scene, b2World *w) {

	world = w;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	backgroundSprite = Sprite::create("maps/backgroundMap11.jpg");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	scene->addChild(backgroundSprite);

	backgoundMap = TMXTiledMap::create("maps/map1.tmx");
	scene->addChild(backgoundMap);

	CCLOG("Empieza la carga de mapa");

	float x;
	float y;
	float tamh;
	float tamw;
	int type;

	TMXObjectGroup	*objectsGroup = backgoundMap->getObjectGroup("colisiones");

	auto& objects = objectsGroup->getObjects();
	for (auto &obj : objects) {
		auto &properties = obj.asValueMap();
		x = properties["x"].asFloat();
		y = properties["y"].asFloat();
		tamh = properties["height"].asFloat();
		tamw = properties["width"].asFloat();

		CCLOG("Recogidas colisiones: %f %f %f %f", x, y, tamw, tamh);

		b2BodyDef auxBodyDef;
		auxBodyDef.type = b2_staticBody;
		auxBodyDef.position.Set((x + (tamw / 2))*MPP, (y + (tamh / 2))*MPP);
		b2Body* auxBody = world->CreateBody(&auxBodyDef);
		b2FixtureDef fixtureDef;
		b2PolygonShape auxBox;
		//bodies->insert(bodies->begin(), auxBody);
		auxBox.SetAsBox(tamw / 2 * MPP, tamh / 2 * MPP);
		fixtureDef.shape = &auxBox;
		fixtureDef.friction = 0;
		fixtureDef.restitution = 0;
		fixtureDef.density = 50;
		b2Fixture* auxFixture = auxBody->CreateFixture(&fixtureDef);
		auxFixture->SetUserData((void*)DATA_PLATFORM);

		//Rect Debug Colisiones
		/*auto rectNode = DrawNode::create();
		Vec2 rectangle[4];
		rectangle[0] = Vec2(x, y);
		rectangle[1] = Vec2(x, y+tamh);
		rectangle[2] = Vec2(x+tamw, y+tamh);
		rectangle[3] = Vec2(x+tamw, y);

		Color4F white(1, 1, 1, 1);
		rectNode->drawPolygon(rectangle, 4, white, 1, white);
		scene->addChild(rectNode);*/
		/////////////////////////////////////////////////////////

	}

	objectsGroup = backgoundMap->getObjectGroup("players");

	objects = objectsGroup->getObjects();
	for (auto &obj : objects) {
		auto &properties = obj.asValueMap();
		x = properties["x"].asFloat();
		y = properties["y"].asFloat();
		type = properties["name"].asInt();
		tamh = properties["height"].asFloat();
		tamw = properties["width"].asFloat();

		CCLOG("Recogidos Players: %f %f %f %f %i", x, y, tamw, tamh, type);

		scene->initPlayers(b2Vec2(x, y), type);
	}

	objectsGroup = backgoundMap->getObjectGroup("hostiles");

	objects = objectsGroup->getObjects();
	for (auto &obj : objects) {
		auto &properties = obj.asValueMap();
		x = properties["x"].asFloat();
		y = properties["y"].asFloat();
		type = properties["name"].asInt();
		tamh = properties["height"].asFloat();
		tamw = properties["width"].asFloat();

		CCLOG("Recogidos elementos hostiles: %f %f %f %f %i", x, y, tamw, tamh, type);

		b2BodyDef auxBodyDef;
		auxBodyDef.type = b2_staticBody;
		auxBodyDef.position.Set((x + (tamw / 2))*MPP, (y + (tamh / 2))*MPP);
		b2Body* auxBody = world->CreateBody(&auxBodyDef);
		b2FixtureDef fixtureDef;
		b2PolygonShape auxBox;
		//bodies->insert(bodies->begin(), auxBody);
		auxBox.SetAsBox(tamw / 2 * MPP, tamh / 2 * MPP);
		fixtureDef.shape = &auxBox;
		fixtureDef.friction = 0;
		fixtureDef.restitution = 0;
		fixtureDef.density = 50;
		b2Fixture* auxFixture = auxBody->CreateFixture(&fixtureDef);
		auxFixture->SetUserData((void*)DATA_VOID);
	}

	CCLOG("Fin de la carga de mapa");
}