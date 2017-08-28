#ifndef __BOT_H__
#define __BOT_H__

#include "cocos2d.h"
#include "Player.h"
#include "Pathfinding/Nodo.h"
#include "PathFinding/Lista.h"
#include <Box2D/Box2D.h>
#include <time.h>

class Nodo;
class Lista;

class Bot: public Player
{
public:
	Bot(cocos2d::Layer *layer, int typeZ, int type, b2Vec2 pos, b2World* w, std::vector<Nodo*>* nodos);
	virtual void generatePathfinding(Nodo* inicial, Nodo* objetivo);
	void printNodes();
	void move();
	void patrol();
	void nextNode();
	void quietFor();
	Nodo* getNearNode(float x, float y);
	Nodo* findNumber(int i);
	void updatePlayer(Player* p1, Player* p2);

private:

	Nodo* aux;
	Nodo *startingNode;
	Nodo* destinationNode;
	Nodo* currentNode;
	Nodo* nodoFinIni;
	Lista *list;
	Lista *spawn;
	Lista* pathfinding;

	//estado = 0 --> quieto
	//estado = 1 --> patrullando
	//estado = 2 --> buscando player
	int stateBot;
	int dirBot;
	int lastDir;
	float nodox;
	float nodoy;
	int velBot;
	int typeZ;

	b2Vec2 findPlayer;
	std::vector<Nodo*>* nodes;

	clock_t t;
};

#endif // __BOT_H__
