#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include <Box2D/Box2D.h>

class Player
{
public:
	Player(cocos2d::Layer *layer, int type, b2Vec2 pos, b2World* w);
	void jump(int dir);
	void move(int d);
	void stopPlayer();
	void updatePlayer();

	void initBody(b2Vec2 pos, b2Vec2 tam);
	void initFixture(b2Vec2 tam);

	int getTypePlayer() { return typePlayer; }
	b2Body* getBody() { return m_pBody; }
	b2Vec2 getPosition() { return m_pBody->GetPosition(); }
	bool getJumping() { return jumping; }
	cocos2d::Sprite* getSprite() { return spritePlayer; }
	void setJumping(bool j);
	void setAction(int type);

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite *spritePlayer;
	bool jumping;
	int dir;
	int typePlayer;

	b2Body* m_pBody;
	b2World* _world;

	cocos2d::Animate *walkAnimate;
	cocos2d::Animation *walkAnimation;
	cocos2d::Vector<cocos2d::SpriteFrame*> walkFrames;

	cocos2d::Animate *stopAnimate;
	cocos2d::Animation *stopAnimation;
	cocos2d::Vector<cocos2d::SpriteFrame*> stopFrames;

	cocos2d::Animate *jumpUpAnimate;
	cocos2d::Animation *jumpUpAnimation;
	cocos2d::Vector<cocos2d::SpriteFrame*> jumpUpFrames;

	cocos2d::Animate *jumpDownAnimate;
	cocos2d::Animation *jumpDownAnimation;
	cocos2d::Vector<cocos2d::SpriteFrame*> jumpDownFrames;

};

#endif // __PLAYER_H__
