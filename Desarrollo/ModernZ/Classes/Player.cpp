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

	if (type == 1) {spritePlayer = Sprite::create("player/PlayerWalk/playerOriginal2.png"); }
	else { spritePlayer = Sprite::create("player/playerS.png"); }

	CCSpriteFrameCache* frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
	frameCache->addSpriteFramesWithFile("player/PlayerWalk/IgnatiusWalk.plist");

	CCSpriteBatchNode* spritesheet = CCSpriteBatchNode::create("player/PlayerWalk/IgnatiusWalk.png");
	layer->addChild(spritesheet);

	Vector<SpriteFrame*> ignatiusWalkFrames;
	ignatiusWalkFrames.reserve(6);
	ignatiusWalkFrames.pushBack(SpriteFrame::create("player/PlayerWalk/playerOriginal1.png", Rect(0, 0, 360, 469)));
	ignatiusWalkFrames.pushBack(SpriteFrame::create("player/PlayerWalk/playerOriginal2.png", Rect(0, 0, 360, 469)));
	ignatiusWalkFrames.pushBack(SpriteFrame::create("player/PlayerWalk/playerOriginal3.png", Rect(0, 0, 360, 469)));
	ignatiusWalkFrames.pushBack(SpriteFrame::create("player/PlayerWalk/playerOriginal4.png", Rect(0, 0, 360, 469)));
	ignatiusWalkFrames.pushBack(SpriteFrame::create("player/PlayerWalk/playerOriginal5.png", Rect(0, 0, 360, 469)));
	ignatiusWalkFrames.pushBack(SpriteFrame::create("player/PlayerWalk/playerOriginal6.png", Rect(0, 0, 360, 469)));

	// create the animation out of the frames
	CCAnimation* animation = Animation::createWithSpriteFrames(ignatiusWalkFrames, 0.2f);
	CCAction* animate = CCRepeatForever::create(CCAnimate::create(animation));
	// run it and repeat it forever
	CCSprite* ignatiusWalk;
	sprite->runAction(RepeatForever::create(animate));

	/*CCAnimation* runAnim = CCAnimation::createWithSpriteFrames(ignatiusWalkFrames, 0.1);
	CCSprite* ignatiusWalk = CCSprite::createWithSpriteFrameName("player/PlayerWalk/playerOriginal1.png");

	ignatiusWalk->setPosition(pos.x, pos.y);

	CCAction* action = CCRepeatForever::create(CCAnimate::create(runAnim));

	ignatiusWalk->runAction(action);
	spritesheet->addChild(ignatiusWalk);*/


	spritePlayer->setPosition(pos.x, pos.y);
	initBody(b2Vec2(pos.x * MPP, pos.x * MPP), b2Vec2(35 * MPP, 42 * MPP));
	initFixture(b2Vec2(35 * MPP, 42 * MPP));
	m_pBody->SetTransform(b2Vec2(pos.x * MPP, pos.y * MPP), m_pBody->GetAngle());

	spritePlayer->setScale(0.2f);

	jumping = false;

	layer->addChild(spritePlayer);

	/*this->sprite = Sprite::createWithSpriteFrameName(MONEDA1);
		// now lets animate the sprite we moved
		Vector<SpriteFrame*> animFrames;
		animFrames.reserve(3);
		animFrames.pushBack(SpriteFrame::create("Sprites/moneda1.png", Rect(0, 0, 64, 64)));
		animFrames.pushBack(SpriteFrame::create("Sprites/moneda2.png", Rect(0, 0, 8, 64)));
		animFrames.pushBack(SpriteFrame::create("Sprites/moneda3.png", Rect(0, 0, 64, 64)));
		

		// create the animation out of the frames
		animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
		animate = Animate::create(animation);
		// run it and repeat it forever
		sprite->runAction(RepeatForever::create(animate));*/
}

void Player::updatePlayer()
{
	spritePlayer->setPosition(Vec2(m_pBody->GetPosition().x * PPM, (m_pBody->GetPosition().y * PPM)));
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
	b2Fixture* fixture = m_pBody->CreateFixture(&fixtureDef);
	fixture->SetUserData((void*)DATA_PLAYER);
	polyShape.SetAsBox(tam.x / 2, tam.y / 2, b2Vec2(0, -tam.y), 0);
	fixtureDef.isSensor = true;

	b2Fixture* sensorFixture = m_pBody->CreateFixture(&fixtureDef);
	if(typePlayer == 1)sensorFixture->SetUserData((void*)DATA_PLAYER_SENSOR1);
	else sensorFixture->SetUserData((void*)DATA_PLAYER_SENSOR2);
}