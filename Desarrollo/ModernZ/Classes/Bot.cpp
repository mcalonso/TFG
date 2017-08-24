#include "Bot.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
#include "PathFinding\Lista.h"


USING_NS_CC;

Bot::Bot(cocos2d::Layer *layer, int type, b2Vec2 pos, b2World* w, std::vector<Nodo*>* nodosMap):Player(layer, type, pos, w){

	//_world = w;
	nodes = nodosMap;

	currentNode = NULL;
	nodox = 0;
	nodoy = 0; 
	stateBot = 1;
	dirBot = 1;
	velBot = 5;

	t = clock();
}

void Bot::updatePlayer() {

	this->getSprite()->setPosition(Vec2(this->getBody()->GetPosition().x * PPM, this->getBody()->GetPosition().y * PPM));


	switch (stateBot)
	{
	case 0:
		quietFor();
	break;
	case 1:
		patrol();
	break;
	case 2:
		move();
	break;
		default:
		break;
	}
}

void Bot::move() {

	if (currentNode == NULL) {
		nextNode();
	}

	if (this->getPosition().x > nodox) dirBot = -1;
	else dirBot = 1;

	this->stopPlayer();
	if (abs(this->getPosition().x) > abs(nodox - 10) && abs(this->getPosition().x) < abs(nodox + 10)) {
		nextNode();
	}
	this->getBody()->ApplyLinearImpulse(b2Vec2(velBot*dirBot, 0), this->getBody()->GetWorldCenter(), true);
}

void Bot::patrol() {

	if (clock() - t > 3000) {
		dirBot*=-1; 
		t = clock();
		quietFor();
	}

	this->stopPlayer();
	this->getBody()->ApplyLinearImpulse(b2Vec2(velBot*dirBot, 0), this->getBody()->GetWorldCenter(), true);
}

void Bot::nextNode() {

	currentNode = pathfinding->getUltimo();
	nodox = currentNode->getPosicion().x;
	nodoy = currentNode->getPosicion().y;
}

void Bot::quietFor() {
	if (stateBot != 0){	stateBot = 0; t = clock(); }
	this->stopPlayer();
	if (clock() - t > 1000) { stateBot = 1; t = clock(); }
}

Nodo* Bot::findNumber(int num) {
	Nodo *aux = NULL;

	for (int i = 0; i< nodes->size(); i++) {
		if (nodes->at(i)->getNumero() == num) return nodes->at(i);
	}
	return aux;
}

Nodo* Bot::getNearNode(float x, float y) {

	Nodo *aux = NULL;
	float dif = 100000;

	for (int i = 0; i< nodes->size(); i++) {
		float coste = abs(nodes->at(i)->getPosicion().y*MPP - y) + abs(nodes->at(i)->getPosicion().x*MPP - x);
		if (coste<dif) {
			dif = coste;
			aux = nodes->at(i);
		}
	}
	return aux;
}

void Bot::generatePathfinding(Nodo* inicial, Nodo* objetivo)
{
	Nodo* aux;
	Nodo* nodoInicial = inicial;
	Nodo* nodoDestino = objetivo;
	Nodo* nodoActual;

	if (nodoInicial == NULL || nodoDestino == NULL) {
		CCLOG("Nodos nulos");
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
		CCLOG("<<<<<<<<<PATHFINDING>>>>>>>>>");
		nodoFinIni = pathfinding->getHead();
		pathfinding->imprimirLista();
	}
	else if (nodoInicial->getPosicion().x != nodoDestino->getPosicion().x || nodoInicial->getPosicion().y != nodoDestino->getPosicion().y) {
		nodoActual = new Nodo(nodoInicial->getPosicion(), b2Vec2(1, 1), nodoInicial->getNumero(), 0, NULL);
		listaAbierta.insertar(nodoActual);
		while (listaAbierta.getTamanyo() > 0 && listaAbierta.buscaNodo2(nodoDestino->getPosicion().x, nodoDestino->getPosicion().y) == NULL) {

			//listaAbierta.imprimirLista();
			//CCLOG("NODO ACTUAL: %i", nodoActual->getNumero());

			nodoActual = listaAbierta.getMenorCosto();
			listaAbierta.remove(nodoActual->getPosicion());

			nodoActual->setNext(NULL);
			listaCerrada.insertar(nodoActual);
			for (int i = 0; i<findNumber(nodoActual->getNumero())->getAdyacentes().size(); i++) {

				if (listaCerrada.buscaNumero(findNumber(nodoActual->getNumero())->getAdyacentes()[i]) == NULL
					&& listaAbierta.buscaNumero(findNumber(nodoActual->getNumero())->getAdyacentes()[i]) == NULL) {
					int numero = findNumber(nodoActual->getNumero())->getAdyacentes()[i];
					//CCLOG("Adyacente(%i): %i", i, numero);
					b2Vec2 posicion;
					posicion.x = findNumber(numero)->getPosicion().x;
					posicion.y = findNumber(numero)->getPosicion().y;
					int coste = abs(posicion.x - nodoDestino->getPosicion().x) + abs(posicion.y - nodoDestino->getPosicion().y);
					Nodo* aux = new Nodo(posicion, b2Vec2(1,1), numero, coste, nodoActual);
					listaAbierta.insertar(aux);
				}
			}
		}
		nodoActual = listaAbierta.buscaNodo2(nodoDestino->getPosicion().x, nodoDestino->getPosicion().y);
		pathfinding = new Lista();
		//CCLOG("<<<<<<<<<LISTA>>>>>>>>>");
		while (nodoActual != NULL) {
			//CCLOG("Nodo---> %i", nodoActual->getNumero());
			pathfinding->insertar(nodoActual);
			nodoActual = nodoActual->getPadre();
		}
		CCLOG("<<<<<<<<<PATHFINDING>>>>>>>>>");
		nodoFinIni = pathfinding->getHead();
		pathfinding->imprimirLista();
	}
}