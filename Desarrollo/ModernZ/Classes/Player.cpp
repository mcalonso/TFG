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

	if (type == 2) {

		spritePlayer = Sprite::createWithSpriteFrameName(Sprite_Nereita);

		////////////////////////////////////////////////////////////////////////////////

		// now lets animate the sprite we moved
		walkFrames.reserve(10);
		walkFrames.pushBack(SpriteFrame::create("player/GirlWalk/girlWalk0.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/GirlWalk/girlWalk1.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/GirlWalk/girlWalk2.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/GirlWalk/girlWalk3.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/GirlWalk/girlWalk4.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/GirlWalk/girlWalk5.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/GirlWalk/girlWalk6.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/GirlWalk/girlWalk7.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/GirlWalk/girlWalk8.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/GirlWalk/girlWalk9.png", Rect(0, 0, 360, 469)));

		// create the animation out of the frames
		walkAnimation = Animation::createWithSpriteFrames(walkFrames, 0.0f);
		walkAnimate = Animate::create(walkAnimation);

		/*********************************************************************************/

		// now lets animate the sprite we moved
		stopFrames.reserve(1);
		stopFrames.pushBack(SpriteFrame::create("player/GirlWalk/girlStop.png", Rect(0, 0, 360, 469)));

		// create the animation out of the frames
		stopAnimation = Animation::createWithSpriteFrames(stopFrames, 0.1f);
		stopAnimate = Animate::create(stopAnimation);

		/*********************************************************************************/

		// now lets animate the sprite we moved
		jumpUpFrames.reserve(1);
		jumpUpFrames.pushBack(SpriteFrame::create("player/GirlWalk/girlJump1.png", Rect(0, 0, 410, 469)));

		// create the animation out of the frames
		jumpUpAnimation = Animation::createWithSpriteFrames(jumpUpFrames, 0.1f);
		jumpUpAnimate = Animate::create(jumpUpAnimation);

		/*********************************************************************************/

		// now lets animate the sprite we moved
		jumpDownFrames.reserve(1);
		jumpDownFrames.pushBack(SpriteFrame::create("player/GirlWalk/girlJump2.png", Rect(0, 0, 410, 469)));

		// create the animation out of the frames
		jumpDownAnimation = Animation::createWithSpriteFrames(jumpDownFrames, 0.1f);
		jumpDownAnimate = Animate::create(jumpDownAnimation);

		////////////////////////////////////////////////////////////////////////////////

		spritePlayer->setScale(0.15f);
		initBody(b2Vec2(pos.x * MPP, pos.x * MPP), b2Vec2(30 * MPP, 33 * MPP));
		initFixture(b2Vec2(30 * MPP, 33 * MPP));
	}
	else if (type == 1) { 

		spritePlayer = Sprite::createWithSpriteFrameName(Sprite_Ignatius);

		////////////////////////////////////////////////////////////////////////////////

		// now lets animate the sprite we moved
		walkFrames.reserve(6);
		walkFrames.pushBack(SpriteFrame::create("player/PlayerWalk/playerOriginal1.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/PlayerWalk/playerOriginal2.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/PlayerWalk/playerOriginal3.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/PlayerWalk/playerOriginal4.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/PlayerWalk/playerOriginal5.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/PlayerWalk/playerOriginal6.png", Rect(0, 0, 360, 469)));

		// create the animation out of the frames
		walkAnimation = Animation::createWithSpriteFrames(walkFrames, 0.1f);
		walkAnimate = Animate::create(walkAnimation);

		/*********************************************************************************/

		// now lets animate the sprite we moved
		stopFrames.reserve(1);
		stopFrames.pushBack(SpriteFrame::create("player/PlayerWalk/playerOriginal1.png", Rect(0, 0, 360, 469)));

		// create the animation out of the frames
		stopAnimation = Animation::createWithSpriteFrames(stopFrames, 0.1f);
		stopAnimate = Animate::create(stopAnimation);

		/*********************************************************************************/

		// now lets animate the sprite we moved
		jumpUpFrames.reserve(1);
		jumpUpFrames.pushBack(SpriteFrame::create("player/PlayerWalk/playerSaltando1.png", Rect(0, 0, 410, 469)));

		// create the animation out of the frames
		jumpUpAnimation = Animation::createWithSpriteFrames(jumpUpFrames, 0.1f);
		jumpUpAnimate = Animate::create(jumpUpAnimation);

		/*********************************************************************************/

		// now lets animate the sprite we moved
		jumpDownFrames.reserve(1);
		jumpDownFrames.pushBack(SpriteFrame::create("player/PlayerWalk/playerSaltando2.png", Rect(0, 0, 410, 469)));

		// create the animation out of the frames
		jumpDownAnimation = Animation::createWithSpriteFrames(jumpDownFrames, 0.1f);
		jumpDownAnimate = Animate::create(jumpDownAnimation);


		////////////////////////////////////////////////////////////////////////////////

		spritePlayer->setScale(0.2f);
		initBody(b2Vec2(pos.x * MPP, pos.x * MPP), b2Vec2(35 * MPP, 42 * MPP));
		initFixture(b2Vec2(35 * MPP, 42 * MPP));
	}
	else {
		
		spritePlayer = Sprite::createWithSpriteFrameName(Sprite_Zombi1);

		////////////////////////////////////////////////////////////////////////////////

		// now lets animate the sprite we atack
		atackFrames.reserve(6);
		atackFrames.pushBack(SpriteFrame::create("player/Zombie1/zAtack1.png", Rect(0, 0, 360, 469)));
		atackFrames.pushBack(SpriteFrame::create("player/Zombie1/zAtack2.png", Rect(0, 0, 360, 469)));
		atackFrames.pushBack(SpriteFrame::create("player/Zombie1/zAtack3.png", Rect(0, 0, 360, 469)));
		atackFrames.pushBack(SpriteFrame::create("player/Zombie1/zAtack4.png", Rect(0, 0, 360, 469)));
		atackFrames.pushBack(SpriteFrame::create("player/Zombie1/zAtack5.png", Rect(0, 0, 360, 469)));
		atackFrames.pushBack(SpriteFrame::create("player/Zombie1/zAtack6.png", Rect(0, 0, 360, 469)));
		atackFrames.pushBack(SpriteFrame::create("player/Zombie1/zAtack7.png", Rect(0, 0, 360, 469)));
		atackFrames.pushBack(SpriteFrame::create("player/Zombie1/zAtack8.png", Rect(0, 0, 360, 469)));

		// create the animation out of the frames
		atackAnimation = Animation::createWithSpriteFrames(atackFrames, 0.1f);
		atackAnimate = Animate::create(atackAnimation);

		/*********************************************************************************/

		// now lets animate the sprite we moved
		walkFrames.reserve(10);
		walkFrames.pushBack(SpriteFrame::create("player/Zombie1/zWalk1.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/Zombie1/zWalk2.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/Zombie1/zWalk3.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/Zombie1/zWalk4.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/Zombie1/zWalk5.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/Zombie1/zWalk6.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/Zombie1/zWalk7.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/Zombie1/zWalk8.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/Zombie1/zWalk9.png", Rect(0, 0, 360, 469)));
		walkFrames.pushBack(SpriteFrame::create("player/Zombie1/zWalk10.png", Rect(0, 0, 360, 469)));

		// create the animation out of the frames
		walkAnimation = Animation::createWithSpriteFrames(walkFrames, 0.1f);
		walkAnimate = Animate::create(walkAnimation);

		/*********************************************************************************/

		// now lets animate the sprite we stop
		stopFrames.reserve(1);
		stopFrames.pushBack(SpriteFrame::create("player/Zombie1/zStop.png", Rect(0, 0, 360, 469)));

		// create the animation out of the frames
		stopAnimation = Animation::createWithSpriteFrames(stopFrames, 0.1f);
		stopAnimate = Animate::create(stopAnimation);

		////////////////////////////////////////////////////////////////////////////////

		spritePlayer->setScale(0.2f);
		initBody(b2Vec2(pos.x * MPP, pos.x * MPP), b2Vec2(35 * MPP, 42 * MPP));
		initFixture(b2Vec2(35 * MPP, 42 * MPP));
	}

	// run it and repeat it forever
	spritePlayer->runAction(stopAnimate);
	spritePlayer->setPosition(pos.x, pos.y);
	
	m_pBody->SetTransform(b2Vec2(pos.x * MPP, pos.y * MPP), m_pBody->GetAngle());

	jumping = false;

	layer->addChild(spritePlayer);
}

void Player::updatePlayer()
{
	spritePlayer->setPosition(Vec2(m_pBody->GetPosition().x * PPM, (m_pBody->GetPosition().y * PPM)));

	if (jumping) {
		if (m_pBody->GetLinearVelocity().y < 0) { setAction(3); }
	}
}

void Player::setAction(int type) {

	spritePlayer->stopAllActions();

	if (type == 0) {
		stopAnimation = Animation::createWithSpriteFrames(stopFrames, 10.1f);
		stopAnimate = Animate::create(stopAnimation);
		spritePlayer->runAction(RepeatForever::create(stopAnimate));
	}
	else if (type == 1) {
		walkAnimation = Animation::createWithSpriteFrames(walkFrames, 0.1f);
		walkAnimate = Animate::create(walkAnimation);
		spritePlayer->runAction(RepeatForever::create(walkAnimate));
	}
	else if (type == 2) {
		jumpUpAnimation = Animation::createWithSpriteFrames(jumpUpFrames, 0.1f);
		jumpUpAnimate = Animate::create(jumpUpAnimation);
		spritePlayer->runAction(RepeatForever::create(jumpUpAnimate));
	}
	else if (type == 3) {
		jumpDownAnimation = Animation::createWithSpriteFrames(jumpDownFrames, 0.1f);
		jumpDownAnimate = Animate::create(jumpDownAnimation);
		spritePlayer->runAction(RepeatForever::create(jumpDownAnimate));
	}
}

void Player::setJumping(bool j) {

	jumping = j;
	setAction(0);
}

void Player::jump(int dir) {

	if (!jumping) 
	{
		m_pBody->ApplyLinearImpulse(b2Vec2(m_pBody->GetLinearVelocity().x, jumpForce), m_pBody->GetWorldCenter(), true);
		jumping = true;
		setAction(2);
	}
}

void Player::move(int d) {

	dir = d;
	m_pBody->ApplyLinearImpulse(b2Vec2(velPlayer*dir, 0), m_pBody->GetWorldCenter(), true);

	if (dir == -1) { spritePlayer->setRotationY(180);}
	else spritePlayer->setRotationY(360);

	if (!jumping) setAction(1);
}

void Player::stopPlayer() {

	m_pBody->SetLinearVelocity(b2Vec2(0, m_pBody->GetLinearVelocity().y));
	
	if (!jumping) setAction(0);
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
	fixtureDef.friction = 0;
	fixtureDef.restitution = 0;
	fixtureDef.density = 5;
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	fixture->SetUserData((void*)DATA_PLAYER);
	polyShape.SetAsBox(tam.x / 2, tam.y / 2, b2Vec2(0, -tam.y), 0);
	fixtureDef.isSensor = true;

	b2Fixture* sensorFixture = m_pBody->CreateFixture(&fixtureDef);
	if(typePlayer == 1)sensorFixture->SetUserData((void*)DATA_PLAYER_SENSOR1);
	else sensorFixture->SetUserData((void*)DATA_PLAYER_SENSOR2);
}