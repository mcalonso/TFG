#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "cocos2d.h"
#include <Box2D/Box2D.h>

class Platform
{
public:
	Platform(cocos2d::Layer *layer, int type, b2Vec2 pos, b2World* w);

	void initBody(b2Vec2 pos, b2Vec2 tam);
	void initFixture(b2Vec2 tam);
	void updatePlatform();

	int getTypePlatform() { return typePlatform; }
	b2Vec2 getPosition() { return m_pBody->GetPosition(); }

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite *spritePlatform;
	int typePlatform;

	b2Body* m_pBody;
	b2World* _world;


};

#endif // __PLATFORM_H__
