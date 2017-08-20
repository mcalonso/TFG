#ifndef __Z_RUNNER_H__
#define __Z_RUNNER_H__

#include "cocos2d.h"
#include "Bot.h"
#include "Pathfinding/Nodo.h"
#include "PathFinding/Lista.h"
#include <Box2D/Box2D.h>

class Nodo;
class Lista;

class ZRunner : public Bot
{
public:
	ZRunner(cocos2d::Layer *layer, int type, b2Vec2 pos, b2World* w, std::vector<Nodo*>* nodos, int x);
	void mover();

private:

};

#endif // __Z_RUNNER_H__
