#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"

class Player
{
public:
	Player(cocos2d::Layer *layer, int type);
	void jump(int dir);
	void setJumping(bool j);
	void move(int d);
	void stopPlayer();
	cocos2d::Vec2 getPosition() { return spritePlayer->getPosition(); }

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite *spritePlayer;
	bool jumping;
	int dir;


};

#endif // __PLAYER_H__
