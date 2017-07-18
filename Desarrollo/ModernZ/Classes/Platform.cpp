#include "Platform.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"


USING_NS_CC;

Platform::Platform(cocos2d::Layer *layer, int type, b2Vec2 pos, b2World* w) {

	_world = w;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	typePlatform = type;

	if (type == 1) {spritePlatform = Sprite::create("player/playerOriginal.png"); }
	else { spritePlatform = Sprite::create("player/playerS.png"); }

	spritePlatform->setPosition(pos.x, pos.y);
	initBody(b2Vec2(pos.x * MPP, pos.x * MPP), b2Vec2(10 * MPP, 10 * MPP));
	initFixture(b2Vec2(10 * MPP, 10 * MPP));
	m_pBody->SetTransform(b2Vec2(pos.x * MPP, pos.y * MPP), m_pBody->GetAngle());

	spritePlatform->setScale(0.2f);

	layer->addChild(spritePlatform);

}

void Platform::updatePlatform()
{
	spritePlatform->setPosition(Vec2(m_pBody->GetPosition().x * PPM, m_pBody->GetPosition().y * PPM));
}

void Platform::initBody(b2Vec2 pos, b2Vec2 tam) {
	CCLOG("Create body in: %f %f", pos.x, pos.y);
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x + (tam.x), -1 * (pos.y - (tam.y)));
	bodyDef.type = b2_dynamicBody;
	m_pBody = _world->CreateBody(&bodyDef);
	m_pBody->SetLinearDamping(0);
}
void Platform::initFixture(b2Vec2 tam) {
	b2FixtureDef fixtureDef;
	b2PolygonShape polyShape;
	polyShape.SetAsBox((tam.x), (tam.y));
	fixtureDef.shape = &polyShape;
	fixtureDef.friction = 50;
	fixtureDef.restitution = 0;
	fixtureDef.density = 5;
	//fixtureDef.filter.categoryBits = M_PLAYER;
	//fixtureDef.filter.maskBits = M_SUELO;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	fixture->SetUserData((void*)DATA_PLAYER);
}