#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include <Box2D/Box2D.h>
#include "Map.h"
#include "Player.h"
#include "Bot.h"
#include "GameObject.h"
#include "MyContactListener.h"

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
	void updateWorld(float dt);
	void initWorld();
	void initPlayers(b2Vec2 pos, int type);
	void initBots(b2Vec2 pos, int type);
	void initGameObjects(b2Vec2 pos, b2Vec2 tam);
	void initNodes(b2Vec2 pos, b2Vec2 tam);

	Player* getPlayer() { return curretPlayer; }
	std::vector<GameObject*>* getObjects() { return &objects; }
	std::vector<Node*>* getNodos() { return &nodos; }

	void setGameObject(GameObject *obj);

private: 
	GameObject* obj;
	MapGame *map;
	Player *ignatius;
	Player *nereita;
	Player *curretPlayer;
	b2World* world;
	MyContactListener* contactListener;

	Bot *zombi1;
	Node *nodo;

	std::vector<GameObject*> objects;
	std::vector<Node*> nodos;

	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	float offSetX;
	float offSetY;

	bool onKeyPressBegan(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event *event);
	bool onKeyReleasedBegan(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event *event);
};

#endif // __GAME_SCENE_H__
