#ifndef CUERPOS_H
#define CUERPOS_H
#include "box2d.h"

enum Tipos {//Tipo de cuerpo

	Proyectil,Personaje,Enemigos,Estructura


};
enum Dueno{//De quien sale el proyectil

	Nd,Pj,Em
};

class Cuerpos { //Clase base para la creacion de otros cuerpo y simplificacion de chequo de colisiones

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
