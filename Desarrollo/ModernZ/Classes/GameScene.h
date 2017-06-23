#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Map.h"
#include "Player.h"

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

	void update(float dt);

private: 
	MapGame *map;
	Player *ignatius;
	Player *nereita;
	Player *curretPlayer;
	cocos2d::PhysicsWorld *sceneWorld;
	//cocos2d::Camera *cam;

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	float offSetX;
	float offSetY;

	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
	bool onContactBegin(cocos2d::PhysicsContact &contact);

	bool onKeyPressBegan(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event *event);
	bool onKeyReleasedBegan(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event *event);
};

#endif // __GAME_SCENE_H__
