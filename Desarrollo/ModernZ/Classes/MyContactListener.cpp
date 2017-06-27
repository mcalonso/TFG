#include "MyContactListener.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "GameScene.h"

USING_NS_CC;

MyContactListener::MyContactListener(GameScene *scene) {
	contactScene = scene;
}

void MyContactListener::BeginContact(b2Contact* contact) {
	unsigned long A = (unsigned long)contact->GetFixtureA()->GetUserData();
	unsigned long B = (unsigned long)contact->GetFixtureB()->GetUserData();

	if ((A == DATA_PLAYER_SENSOR && B == DATA_PLATFORM) || (B == DATA_PLAYER_SENSOR && A == DATA_PLATFORM))
	{
		//contactScene->getPlayer()->setJumping(false);
	}
}
void MyContactListener::EndContact(b2Contact* contact) {
	unsigned long A = (unsigned long)contact->GetFixtureA()->GetUserData();
	unsigned long B = (unsigned long)contact->GetFixtureB()->GetUserData();


}
