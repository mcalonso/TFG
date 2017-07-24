#ifndef __MY_CONTACT_LISTENER_H__
#define __MY_CONTACT_LISTENER_H__

#include "cocos2d.h"
#include "Definitions.h"
#include <Box2D/Box2D.h>

class GameScene;
class MyContactListener;
class Player;

struct Contact2Method {
	unsigned long A;
	unsigned long B;
	void (MyContactListener::*p)();
};

class MyContactListener: public b2ContactListener
{
public:
	MyContactListener(GameScene* scene);
	virtual ~MyContactListener() {}
	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);

private:
	b2World* m_pWorld;
	b2Contact* contact;
	Player* player;
	GameScene* contactScene;
	std::vector<GameObject*> objects;



};

#endif // __MY_CONTACT_LISTENER_H__
