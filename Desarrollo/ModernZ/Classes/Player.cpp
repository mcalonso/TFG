#include "Player.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"

USING_NS_CC;

Player::Player(cocos2d::Layer *layer, int type, b2World* w) {

	_world = w;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	if (type == 1) {
		spritePlayer = Sprite::create("player/playerOriginal.png"); 
		spritePlayer->setPosition(600, 600);
		initBody(b2Vec2(600 * MPP, 600 * MPP), b2Vec2(10 * MPP, 10 * MPP));
		initFixture(b2Vec2(10 * MPP, 10 * MPP));
	}
	else { 
		spritePlayer = Sprite::create("player/playerS.png"); 
		spritePlayer->setPosition(900, 600);
		initBody(b2Vec2(600 * MPP, 600 * MPP), b2Vec2(10 * MPP, 10 * MPP));
		initFixture(b2Vec2(10 * MPP, 10 * MPP));
	}

	spritePlayer->setScale(0.2f);

	jumping = false;

	layer->addChild(spritePlayer);

}

void Player::updatePlayer()
{
	spritePlayer->setPosition(Vec2(m_pBody->GetPosition().x * PPM, m_pBody->GetPosition().y * PPM));
	CCLOG("Recogidos: %f %f", m_pBody->GetPosition().x, m_pBody->GetPosition().y);

}

void Player::jump(int dir) {

	if (!jumping) {

		//spritePlayer->getPhysicsBody()->setVelocity(cocos2d::Vec2(spritePlayer->getPhysicsBody()->getVelocity().x, 200));
		jumping = true;
	}
}

void Player::move(int d) {

	dir = d;
	//spritePlayer->getPhysicsBody()->setVelocity(cocos2d::Vec2(100 * dir, spritePlayer->getPhysicsBody()->getVelocity().y));
}

void Player::stopPlayer() {

	//spritePlayer->getPhysicsBody()->setVelocity(cocos2d::Vec2(0, spritePlayer->getPhysicsBody()->getVelocity().y));
}

void Player::initBody(b2Vec2 pos, b2Vec2 tam) {
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
	fixtureDef.friction = 0;
	fixtureDef.restitution = 0;
	fixtureDef.density = 20;
	fixtureDef.filter.categoryBits = M_PLAYER;
	fixtureDef.filter.maskBits = M_SUELO;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	fixture->SetUserData((void*)DATA_PLAYER);
	polyShape.SetAsBox(tam.x / 2, tam.y / 2, b2Vec2(0, -tam.y), 0);
	fixtureDef.isSensor = true;
	fixtureDef.filter.maskBits = M_SUELO;
	b2Fixture* sensorFixture = m_pBody->CreateFixture(&fixtureDef);
	sensorFixture->SetUserData((void*)DATA_PLAYER_SENSOR);
}