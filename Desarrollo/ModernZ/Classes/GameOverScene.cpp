#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	/*Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Director::getInstance()->setDisplayStats(false);

	auto backgroundSprite = Sprite::create("backgroundMenu.jpg");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);

	MenuItemImage *buttonPlay = MenuItemImage::create("menu/play.png", "menu/playSelec.png", CC_CALLBACK_1(GameOverScene::openMainMenu, this));
	MenuItemImage *buttonQuit = MenuItemImage::create("menu/quit.png", "menu/quitSelec.png", CC_CALLBACK_1(GameOverScene::exitGame, this));

	Menu* menuOver = Menu::create(buttonPlay, buttonQuit, NULL);
	menuOver->alignItemsVertically();
	this->addChild(menuOver);*/

    return true;
}

void GameOverScene::openMainMenu(float dt) {

	auto scene = MainMenuScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameOverScene::exitGame(float dt) 
{

	Director::getInstance()->end();
}
