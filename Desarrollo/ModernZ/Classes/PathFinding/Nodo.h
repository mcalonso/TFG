#ifndef NODO_H
#define NODO_H

#include <vector>
#include <Box2D/Box2D.h>

class Nodo {
public:
	Nodo(b2Vec2 posicion, b2Vec2 tam, int num, int coste, Nodo *nodoPadre);
	~Nodo();
	void setPadre(Nodo *nodo, int g);
	void setNext(Nodo *nodo);
	b2Vec2 getPosicion();
	Nodo *getPadre();
	int getCostoTotal();
	int getNumero();
	Nodo *getNextNodo();
	void addAdyacente(int n);
	std::vector<int> getAdyacentes();
	int GetId();

private:
	Nodo* m_pNodoPadre;
	int m_coste;
	Nodo* m_pNextNodo;
	int m_numero;
	std::vector<int> m_Adyacentes;
	b2Vec2 m_posicion;
	int m_id;
};

#endif // NODO_H

