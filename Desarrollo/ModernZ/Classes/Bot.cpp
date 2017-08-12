#include "Bot.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
#include "PathFinding\Lista.h"


USING_NS_CC;

Bot::Bot(cocos2d::Layer *layer, int type, b2Vec2 pos, b2World* w, std::vector<Nodo*>* nodosMap):Player(layer, type, pos, w){

	//_world = w;
	nodos = nodosMap;
}

Nodo* Bot::buscaNumero(int num) {
	Nodo *aux = NULL;

	for (int i = 0; i< nodos->size(); i++) {
		if (nodos->at(i)->getNumero() == num) return nodos->at(i);
	}
	return aux;
}

Nodo* Bot::getCercanoTotal(float x, float y) {

	Nodo *aux = NULL;
	float dif = 100000;


	for (int i = 0; i< nodos->size(); i++) {
		CCLOG("x: %f ---- xnodo: %f", y, nodos->at(i)->getPosicion().y);
		float coste = abs(nodos->at(i)->getPosicion().y - y) + abs(nodos->at(i)->getPosicion().x - x);
		CCLOG("Nodo %i Coste %f", nodos->at(i)->getNumero(), coste);
		if (coste<dif) {
			dif = coste;
			aux = nodos->at(i);
		}
	}
	return aux;
}

void Bot::calcularPathfinding(Nodo* inicial, Nodo* objetivo)
{
	Nodo* aux;
	Nodo* nodoInicial = inicial;
	Nodo* nodoDestino = objetivo;
	Nodo* nodoActual;

	if (nodoInicial == NULL || nodoDestino == NULL) {
		//std::cout<<"Inicial: "<<nodoInicial<<" Destino: "<<nodoDestino<<std::endl;
		//std::cout<<"NODO INICIAL O DESTINO ES IGUAL A NULL"<<std::endl;
		return;
	}

	Lista listaAbierta;
	Lista listaCerrada;

	//std::cout<<"Nodo inicial: "<<nodoInicial->getNumero()<<" Datos["<<nodoInicial->getPosicion().x<<" "<<nodoInicial->getPosicion().y<<"]"<<std::endl;
	//std::cout<<"Nodo destino: "<<nodoDestino->getNumero()<<" Datos["<<nodoDestino->getPosicion().x<<" "<<nodoDestino->getPosicion().y<<"]"<<std::endl;
	// std::cout<<std::endl;

	if (nodoInicial->getPosicion().x == nodoDestino->getPosicion().x && nodoInicial->getPosicion().y == nodoDestino->getPosicion().y) {
		pathfinding = new Lista();
		pathfinding->insertar(nodoInicial);
		//std::cout<<"<<<<<<<<<PATHFINDING>>>>>>>>>"<<std::endl;
		nodoFinIni = pathfinding->getHead();
		//pathfinding->imprimirLista();
	}
	else if (nodoInicial->getPosicion().x != nodoDestino->getPosicion().x || nodoInicial->getPosicion().y != nodoDestino->getPosicion().y) {
		nodoActual = new Nodo(nodoInicial->getPosicion(), b2Vec2(1, 1), nodoInicial->getNumero(), 0, NULL);
		listaAbierta.insertar(nodoActual);
		while (listaAbierta.getTamanyo() > 0 && listaAbierta.buscaNodo2(nodoDestino->getPosicion().x, nodoDestino->getPosicion().y) == NULL) {

			//listaAbierta.imprimirLista();
			//std::cout<<"NODO ACTUAL: "<<nodoActual->getNumero()<<std::endl;

			nodoActual = listaAbierta.getMenorCosto();
			listaAbierta.remove(nodoActual->getPosicion());

			nodoActual->setNext(NULL);
			listaCerrada.insertar(nodoActual);
			for (int i = 0; i<buscaNumero(nodoActual->getNumero())->getAdyacentes().size(); i++) {

				if (listaCerrada.buscaNumero(buscaNumero(nodoActual->getNumero())->getAdyacentes()[i]) == NULL
					&& listaAbierta.buscaNumero(buscaNumero(nodoActual->getNumero())->getAdyacentes()[i]) == NULL) {
					int numero = buscaNumero(nodoActual->getNumero())->getAdyacentes()[i];
					b2Vec2 posicion;
					posicion.x = buscaNumero(numero)->getPosicion().x;
					posicion.y = buscaNumero(numero)->getPosicion().y;
					int coste = abs(posicion.x - nodoDestino->getPosicion().x) + abs(posicion.y - nodoDestino->getPosicion().y);
					Nodo* aux = new Nodo(posicion, b2Vec2(1,1), numero, coste, nodoActual);
					listaAbierta.insertar(aux);
				}
			}
		}
		nodoActual = listaAbierta.buscaNodo2(nodoDestino->getPosicion().x, nodoDestino->getPosicion().y);
		pathfinding = new Lista();
		while (nodoActual != NULL) {
			pathfinding->insertar(nodoActual);
			nodoActual = nodoActual->getPadre();
		}
		//std::cout<<"<<<<<<<<<PATHFINDING>>>>>>>>>"<<std::endl;
		nodoFinIni = pathfinding->getHead();
		//pathfinding->imprimirLista();
		//std::cout<<std::endl;
	}
}