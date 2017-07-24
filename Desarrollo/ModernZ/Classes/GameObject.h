#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include "cocos2d.h"
#include <Box2D/Box2D.h>

class GameObject
{
public:
	GameObject(cocos2d::Layer *layer, b2Vec2 pos, b2Vec2 tam, b2World* w);
	void updateGameObject();

	void initBody(b2Vec2 pos, b2Vec2 tam);
	void initFixture(b2Vec2 tam);

	b2Vec2 getPosition() { return m_pBody->GetPosition(); }
	b2Body* getBody() { return m_pBody; }
	void setBodyType();

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite *spriteGameObject;

	b2Vec2 posBody;
	b2Vec2 tamBody;

	b2Body* m_pBody;
	b2World* _world;


};

#endif // __GAME_OBJECT_H__
