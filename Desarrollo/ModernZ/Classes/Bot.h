#ifndef __BOT_H__
#define __BOT_H__

#include "cocos2d.h"
#include "Player.h"
#include "Pathfinding/Nodo.h"
#include "PathFinding/Lista.h"
#include <Box2D/Box2D.h>

class Nodo;
class Lista;

class Bot: public Player
{
public:
	Bot(cocos2d::Layer *layer, int type, b2Vec2 pos, b2World* w);
	virtual void calcularPathfinding(Nodo* inicial, Nodo* objetivo);
	void imprimirNodos();
	Nodo* buscaNumero(int i);

private:

	Nodo* aux;
	Nodo *nodoInicial;
	Nodo* nodoDestino;
	Nodo* nodoActual;
	Nodo* nodoFinIni;
	Lista *lista;
	Lista *spawn;
	Lista* pathfinding;

	int estadoBot;
	int spawnbusco;
	bool enMuelle;
	bool primera;
	int direccion;
	int direccionA;
	int lastDir;
	float nodox;
	float nodoy;

	b2Vec2 posicionSpawn;
	std::vector<Nodo*> nodos;
};

#endif // __BOT_H__
