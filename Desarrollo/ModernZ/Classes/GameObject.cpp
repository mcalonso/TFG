#include "GameObject.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"


USING_NS_CC;

GameObject::GameObject(cocos2d::Layer *layer, b2Vec2 pos, b2Vec2 tam, b2World* w) {

	_world = w;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	spriteGameObject = Sprite::create("maps/platform.png");

	spriteGameObject->setPosition(pos.x, pos.y);
	initBody(b2Vec2(pos.x * MPP, pos.x * MPP), b2Vec2(tam.x * MPP, tam.y * MPP));
	initFixture(b2Vec2(tam.x * MPP, tam.y * MPP));
	m_pBody->SetTransform(b2Vec2(pos.x * MPP, pos.y * MPP), m_pBody->GetAngle());

	spriteGameObject->setScale(0.2f);

	layer->addChild(spriteGameObject);

}

void GameObject::updateGameObject()
{
	spriteGameObject->setPosition(Vec2(m_pBody->GetPosition().x * PPM, m_pBody->GetPosition().y * PPM));
}

void GameObject::initBody(b2Vec2 pos, b2Vec2 tam) {
	CCLOG("Create body in: %f %f", pos.x, pos.y);
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x + (tam.x), -1 * (pos.y - (tam.y)));
	bodyDef.type = b2_staticBody;
	m_pBody = _world->CreateBody(&bodyDef);
	m_pBody->SetLinearDamping(0);
}
void GameObject::initFixture(b2Vec2 tam) {
	b2FixtureDef fixtureDef;
	b2PolygonShape polyShape;
	polyShape.SetAsBox((tam.x), (tam.y));
	fixtureDef.shape = &polyShape;
	fixtureDef.friction = 50;
	fixtureDef.restitution = 0;
	fixtureDef.density = 5;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	fixture->SetUserData((void*)DATA_DESTROYABLE);
}