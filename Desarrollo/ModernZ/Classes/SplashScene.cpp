#include "SplashScene.h"
#include "SplashSceneVideo.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* SplashScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Director::getInstance()->setDisplayStats(false);

	this->scheduleOnce(schedule_selector(SplashScene::openMainMenu), DISPLAY_TIME_SPLASH_SCENE);

	auto backgroundSprite = Sprite::create("SplashScene.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

    return true;
}

void SplashScene::openMainMenu(float dt) {

	auto scene = MainMenuScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

