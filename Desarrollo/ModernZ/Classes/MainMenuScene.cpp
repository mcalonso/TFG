#include "MainMenuScene.h"
#include "GameScene.h"
#include "SplashScenemenu.h"
#include "Definitions.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
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

	audio = CocosDenshion::SimpleAudioEngine::getInstance();

	auto backgroundSprite = Sprite::create("backgroundMenu.jpg");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite);

	titleSprite = Sprite::create("menu/Title.png");
	titleSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + visibleSize.height / 2.8f));
	titleSprite->setScale(2.0f);
	titleSprite->setTag(99);
	this->addChild(titleSprite);

	MenuItemImage *buttonPlay = MenuItemImage::create("menu/play.png", "menu/playS.png", CC_CALLBACK_1(MainMenuScene::playGameScene, this));
	MenuItemImage *buttonLoad = MenuItemImage::create("menu/load.png", "menu/loadS.png", CC_CALLBACK_1(MainMenuScene::playGameScene, this));
	MenuItemImage *buttonSettings = MenuItemImage::create("menu/settings.png", "menu/settingsS.png", CC_CALLBACK_1(MainMenuScene::playGameScene, this));
	MenuItemImage *buttonExit = MenuItemImage::create("menu/exit.png", "menu/exitS.png", CC_CALLBACK_1(MainMenuScene::playGameScene, this));

	Menu* mainMenu = Menu::create(buttonPlay, buttonLoad, buttonSettings, buttonExit, NULL);
	mainMenu->alignItemsVertically();
	this->addChild(mainMenu);

	//AUDIO
	audio->setBackgroundMusicVolume(0.1f);
	audio->playBackgroundMusic("sound/backGroundMenu2.wav", true);

	this->schedule(CC_SCHEDULE_SELECTOR(MainMenuScene::updateTitle));

	return true;
}

void MainMenuScene::playGameScene(cocos2d::Ref *sender) {

	audio->stopBackgroundMusic();
	CocosDenshion::SimpleAudioEngine* efect = CocosDenshion::SimpleAudioEngine::getInstance();
	efect->setEffectsVolume(1.0f);
	efect->playEffect("sound/playMenu.wav", false, 1.0f, 1.0f, 10.0f);
	
	auto scene = SplashScenemenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));
}

void MainMenuScene::updateTitle(float dt) {
	if (clock() - t > 4000) {
		CocosDenshion::SimpleAudioEngine* efect = CocosDenshion::SimpleAudioEngine::getInstance();
		efect->setEffectsVolume(1.0f);
		efect->playEffect("sound/interference.wav", false, 1.0f, 1.0f, 10.0f);

		titleSprite->setTexture("menu/Title2.png");
	}
	if (clock() - t > 4020) {
		titleSprite->setTexture("menu/Title.png");
	}
	if (clock() - t > 4035) {
		titleSprite->setTexture("menu/Title2.png");
	}
	if (clock() - t > 4050) {
		t = clock();
		titleSprite->setTexture("menu/Title.png");
	}

}