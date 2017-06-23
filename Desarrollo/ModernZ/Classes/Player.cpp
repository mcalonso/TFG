#include "Player.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Player::Player(cocos2d::Layer *layer, int type) {

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto physicsBody = PhysicsBody::createBox(Size(70, 90), PhysicsMaterial(0.5f, 0.2f, 0.0f));
	physicsBody->setRotationEnable(false);
	physicsBody->setCollisionBitmask(1);
	physicsBody->setContactTestBitmask(true);

	if (type == 1) {
		spritePlayer = Sprite::create("player/playerOriginal.png"); 
		spritePlayer->setPosition(600, 600);
	}
	else { 
		spritePlayer = Sprite::create("player/playerS.png"); 
		spritePlayer->setPosition(900, 600);
	}

	spritePlayer->setScale(0.2f);
	spritePlayer->setPhysicsBody(physicsBody);

	jumping = false;

	layer->addChild(spritePlayer);

}

void Player::jump(int dir) {

	if (!jumping) {

		spritePlayer->getPhysicsBody()->setVelocity(cocos2d::Vec2(spritePlayer->getPhysicsBody()->getVelocity().x, 200));
		jumping = true;
	}
}

void Player::move(int d) {

	dir = d;
	spritePlayer->getPhysicsBody()->setVelocity(cocos2d::Vec2(100*dir, spritePlayer->getPhysicsBody()->getVelocity().y));
}

void Player::stopPlayer() {

	spritePlayer->getPhysicsBody()->setVelocity(cocos2d::Vec2(0, spritePlayer->getPhysicsBody()->getVelocity().y));
}

void Player::setJumping(bool j) { jumping = j; }