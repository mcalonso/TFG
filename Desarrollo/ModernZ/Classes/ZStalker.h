#ifndef __Z_STALKER_H__
#define __Z_STALKER_H__

#include "cocos2d.h"
#include "Bot.h"
#include "Pathfinding/Nodo.h"
#include "PathFinding/Lista.h"
#include <Box2D/Box2D.h>

class Nodo;
class Lista;

class ZStalker: public Bot
{
public:
	ZStalker(cocos2d::Layer *layer, int type, b2Vec2 pos, b2World* w, std::vector<Nodo*>* nodos, int x);


private:

};

#endif // __Z_STALKER_H__
