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

	void crear_objetos(b2World& world, b2Vec2 posicion, b2Vec2 tamano, bool esEstatico, Color col);
	b2Body* obtenerCuerpo() { return cuerpo; }
	void dibujar() override;
	b2Vec2 obtenerPosicionX();

	float angulo();
	void reiniciarPosicion();
	b2Body* Obtener_cuerpo();


};


#endif 