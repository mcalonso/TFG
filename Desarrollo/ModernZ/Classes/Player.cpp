#include "Player.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Player::Player(cocos2d::Layer *layer) {

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	auto physicsBody = PhysicsBody::createBox(Size(70, 90), PhysicsMaterial(0.5f, 0.2f, 0.0f));

	spritePlayer = Sprite::create("player/player.png");
	spritePlayer->setPosition(600, 600);
	spritePlayer->setScale(0.2f);
	spritePlayer->setPhysicsBody(physicsBody);

	layer->addChild(spritePlayer);

}