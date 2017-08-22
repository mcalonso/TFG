#include "Player.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"


USING_NS_CC;

Player::Player(cocos2d::Layer *layer, int type, b2Vec2 pos, b2World* w) {

	_world = w;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	typePlayer = type;

	if (type == 1) {spritePlayer = Sprite::create("player/playerOriginal.png"); }
	else { 	spritePlayer = Sprite::create("player/playerS.png"); }

	spritePlayer->setPosition(pos.x, pos.y);
	initBody(b2Vec2(pos.x * MPP, pos.x * MPP), b2Vec2(72 * MPP, 94 * MPP));
	initFixture(b2Vec2(72 * MPP, 94 * MPP));
	m_pBody->SetTransform(b2Vec2(pos.x * MPP, pos.y * MPP), m_pBody->GetAngle());

	spritePlayer->setScale(0.2f);

	jumping = false;

	layer->addChild(spritePlayer);

}

void Player::updatePlayer()
{
	spritePlayer->setPosition(Vec2(m_pBody->GetPosition().x * PPM, (m_pBody->GetPosition().y * PPM)+35));
}

void Player::jump(int dir) {

	if (!jumping) 
	{
		m_pBody->ApplyLinearImpulse(b2Vec2(m_pBody->GetLinearVelocity().x, jumpForce), m_pBody->GetWorldCenter(), true);
		jumping = true;
	}
}

void Player::move(int d) {

	dir = d;
	m_pBody->ApplyLinearImpulse(b2Vec2(velPlayer*dir, 0), m_pBody->GetWorldCenter(), true);
}

void Player::stopPlayer() {

	m_pBody->SetLinearVelocity(b2Vec2(0, m_pBody->GetLinearVelocity().y));
}

void Player::initBody(b2Vec2 pos, b2Vec2 tam) {
	CCLOG("Create body in: %f %f", pos.x, pos.y);
	b2BodyDef bodyDef;
	bodyDef.position.Set(pos.x + (tam.x), -1 * (pos.y - (tam.y)));
	bodyDef.type = b2_dynamicBody;
	m_pBody = _world->CreateBody(&bodyDef);
	m_pBody->SetLinearDamping(0);
}
void Player::initFixture(b2Vec2 tam) {
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
	polyShape.SetAsBox(tam.x / 2, tam.y / 2, b2Vec2(0, -tam.y), 0);
	fixtureDef.isSensor = true;
	//fixtureDef.filter.maskBits = M_SUELO;
	b2Fixture* sensorFixture = m_pBody->CreateFixture(&fixtureDef);

	if(typePlayer == 1)sensorFixture->SetUserData((void*)DATA_PLAYER_SENSOR1);
	else sensorFixture->SetUserData((void*)DATA_PLAYER_SENSOR2);
}