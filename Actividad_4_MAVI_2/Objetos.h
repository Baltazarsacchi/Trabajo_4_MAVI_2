#ifndef OBJETOS_H
#define OBJETOS_H	
#include "box2d.h"
#include "raylib.h"
#include "Cuerpos.h"

const float ESCALE = 100.0f;

class Objetos : public Cuerpos {

private:

	b2Body* cuerpo;
	b2Vec2 posicion;
	b2Vec2 tamano;
	Color color;

public:
	bool estado;

	void crear_objetos(b2World& world, b2Vec2 posicion, b2Vec2 tamano, bool esEstatico, Color col);//Constructor
	b2Body* obtenerCuerpo() { return cuerpo; }//Devuelve el cuerpo del objeto
	void dibujar() override;//Funciones heredadas
	b2Vec2 obtenerPosicionX();//Posicion del objeto

	float angulo();//Angulo del objeto
	void reiniciarPosicion();//Reinicia su posicion
	b2Body* Obtener_cuerpo();


};


#endif 
