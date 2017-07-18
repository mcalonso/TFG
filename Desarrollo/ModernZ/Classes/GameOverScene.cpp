#include "MainMenuScene.h"
#include "GameOverScene.h"
#include "GameScene.h"
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
    
    //auto rootNode = CSLoader::createNode("MainScene.csb");
    //addChild(rootNode);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Director::getInstance()->setDisplayStats(false);


	auto backgroundSprite = Sprite::create("backgroundMenu.jpg");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);

	MenuItemImage *buttonRetry = MenuItemImage::create("menu/retry.png", "menu/retrySelec.png", CC_CALLBACK_1(GameOverScene::returnMainMemu, this));
	MenuItemImage *buttonQuit = MenuItemImage::create("menu/quit.png", "menu/quitSelec.png", CC_CALLBACK_1(GameOverScene::exitGame, this));

	Menu* mainMenu = Menu::create(buttonRetry, buttonQuit, NULL);
	mainMenu->alignItemsVertically();
	this->addChild(mainMenu);

	return true;
}

void GameOverScene::returnMainMemu(cocos2d::Ref *sender) 
{
	
	auto scene = GameScene::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void GameOverScene::exitGame(cocos2d::Ref *sender)
{
	Director::getInstance()->end();
}
