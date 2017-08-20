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
	Bot(cocos2d::Layer *layer, int type, b2Vec2 pos, b2World* w, std::vector<Nodo*>* nodos);
	virtual void calcularPathfinding(Nodo* inicial, Nodo* objetivo);
	void imprimirNodos();
	void mover();
	void siguienteNodo();
	Nodo* getCercanoTotal(float x, float y);
	Nodo* buscaNumero(int i);
	void updatePlayer();


private:

	Nodo* aux;
	Nodo *nodoInicial;
	Nodo* nodoDestino;
	Nodo* nodoActual;
	Nodo* nodoFinIni;
	Lista *lista;
	Lista *spawn;
	Lista* pathfinding;

	//estado = 0 --> quieto
	//estado = 1 --> patrullando
	//estado = 2 --> buscando player
	int estadoBot;
	int dirBot;
	int lastDir;
	float nodox;
	float nodoy;

	b2Vec2 findPlayer;
	std::vector<Nodo*>* nodos;

	clock_t t;
};

#endif // __BOT_H__
