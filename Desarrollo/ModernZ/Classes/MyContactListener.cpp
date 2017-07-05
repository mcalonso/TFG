#include "MyContactListener.h"
#include "MainMenuScene.h"
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

	if (((A == DATA_PLAYER_SENSOR1 || A == DATA_PLAYER_SENSOR2) && (B == DATA_PLATFORM || B == DATA_PLAYER)) ||
		((B == DATA_PLAYER_SENSOR1 || B == DATA_PLAYER_SENSOR2) && (A == DATA_PLATFORM || A == DATA_PLAYER)))
	{
		contactScene->getPlayer()->setJumping(false);
	}

	if (((A == DATA_PLAYER_SENSOR1 || A == DATA_PLAYER_SENSOR2) && (B == DATA_VOID)) ||
		((B == DATA_PLAYER_SENSOR1 || B == DATA_PLAYER_SENSOR2) && (A == DATA_VOID)))
	{
		CCLOG("Player choca con los pinchos");

		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}

}
void MyContactListener::EndContact(b2Contact* contact) {
	unsigned long A = (unsigned long)contact->GetFixtureA()->GetUserData();
	unsigned long B = (unsigned long)contact->GetFixtureB()->GetUserData();

	if (((A == DATA_PLAYER_SENSOR1 || A == DATA_PLAYER_SENSOR2) && (B == DATA_PLATFORM || B == DATA_PLAYER)) ||
		((B == DATA_PLAYER_SENSOR1 || B == DATA_PLAYER_SENSOR2) && (A == DATA_PLATFORM || A == DATA_PLAYER)))
	{
		if(contactScene->getPlayer()->getTypePlayer() == 2) contactScene->getPlayer()->setJumping(false);
	}

	if (((A == DATA_PLAYER_SENSOR1 || A == DATA_PLAYER_SENSOR2) && (B == DATA_VOID)) ||
		((B == DATA_PLAYER_SENSOR1 || B == DATA_PLAYER_SENSOR2) && (A == DATA_VOID)))
	{
		CCLOG("Player choca con los pinchos");

		auto scene = MainMenuScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
	}


}
