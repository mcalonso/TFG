#include "GameObject.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"


USING_NS_CC;

GameObject::GameObject(cocos2d::Layer *layer, b2Vec2 pos, b2Vec2 tam, b2World* w) {

	_world = w;
	toChange = false;
	changed = false;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	spriteGameObject = Sprite::create("maps/platform2.png");

	spriteGameObject->setPosition(pos.x, pos.y);
	initBody(pos, tam);
	initFixture(tam);

	posBody = pos;
	tamBody = tam;

	spriteGameObject->setScale(0.2f);

	layer->addChild(spriteGameObject);

}

void GameObject::updateGameObject()
{
	spriteGameObject->setPosition(Vec2(m_pBody->GetPosition().x * PPM, m_pBody->GetPosition().y * PPM));
	if (!changed && toChange) {
		changed = true;
		this->setBodyType();
	}
}

void GameObject::initBody(b2Vec2 pos, b2Vec2 tam) {

	CCLOG("Create GameObject in: %f %f", pos.x, pos.y);

	b2BodyDef auxBodyDef;
	auxBodyDef.type = b2_staticBody;
	auxBodyDef.position.Set((pos.x + (tam.x / 2))*MPP, (pos.y + (tam.y / 2))*MPP);
	m_pBody = _world->CreateBody(&auxBodyDef);
}
void GameObject::initFixture(b2Vec2 tam) {

	b2FixtureDef fixtureDef;
	b2PolygonShape auxBox;
	auxBox.SetAsBox(tam.x / 2 * MPP, tam.y / 2 * MPP);
	fixtureDef.shape = &auxBox;
	fixtureDef.friction = 0;
	fixtureDef.restitution = 0;
	fixtureDef.density = 50;
	b2Fixture* auxFixture = m_pBody->CreateFixture(&fixtureDef);
	auxFixture->SetUserData((void*)DATA_DESTROYABLE);
}

void GameObject::setChange(bool b)
{
	toChange = b;
}

void GameObject::setBodyType()
{
	_world->DestroyBody(m_pBody);

	b2BodyDef auxBodyDef;
	auxBodyDef.type = b2_dynamicBody;
	auxBodyDef.position.Set((posBody.x + (tamBody.x / 2))*MPP, (posBody.y + (tamBody.y / 2))*MPP);
	m_pBody = _world->CreateBody(&auxBodyDef);

	b2FixtureDef fixtureDef;
	b2PolygonShape auxBox;
	auxBox.SetAsBox(tamBody.x / 2 * MPP, tamBody.y / 2 * MPP);
	fixtureDef.shape = &auxBox;
	fixtureDef.friction = 0;
	fixtureDef.restitution = 0;
	fixtureDef.density = 50;

	b2Fixture* auxFixture = this->m_pBody->CreateFixture(&fixtureDef);
	auxFixture->SetUserData((void*)DATA_DESTROYABLE);
}