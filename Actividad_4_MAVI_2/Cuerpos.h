#ifndef CUERPOS_H
#define CUERPOS_H
#include "box2d.h"

enum Tipos {

	Proyectil,Personaje,Enemigos,Estructura


};
enum Dueno{

	Nd,Pj,Em
};

class Cuerpos {

public:

	b2Body* cuerpo;
	Tipos tipo;

	Cuerpos() : cuerpo(nullptr), tipo(Estructura) {};
	virtual ~Cuerpos() {};
	virtual void actualizacion() {};
	virtual void dibujar() {};
	virtual void colision(Cuerpos* otro) {}

};

#endif 