#include "ZStalker.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
#include "PathFinding\Lista.h"


USING_NS_CC;

ZStalker::ZStalker(cocos2d::Layer *layer, int type, b2Vec2 pos, b2World* w, std::vector<Nodo*>* nodosMap, int x):Bot(layer, type, pos, w, nodosMap){

	//_world = w;
}
