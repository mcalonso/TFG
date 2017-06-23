#include "ContactListener.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

PhysicsDemoCollisionProcessing::PhysicsDemoCollisionProcessing(cocos2d::Layer *layer) {

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();


}