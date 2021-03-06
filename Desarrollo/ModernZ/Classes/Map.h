#ifndef __MAP_GAME_H__
#define __MAP_GAME_H__

#include <Box2D/Box2D.h>
#include "cocos2d.h"
class GameScene;


class MapGame
{
public:
	MapGame(GameScene *scene, b2World *w);
	cocos2d::Sprite* getBackgroundSprite() { return backgroundSprite; }
	cocos2d::TMXTiledMap* getBackgroundMap() { return backgoundMap; }

private:
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Sprite *backgroundSprite;
	cocos2d::TMXTiledMap *backgoundMap;

	b2World* world;


};

#endif // __MAP_GAME_H__
