#ifndef PROYECTILES_H
#define PROYECTILES_H

#include "box2d.h"
#include "Cuerpos.h"
#include "raylib.h"

const float Tamano = 100.0f;

class Proyectiles : public Cuerpos {
private:
	b2Vec2 tamano;
	float direccion;
	Texture2D textura;
	
public:

	Dueno mando;

	bool destruccion;

	Proyectiles(b2World& mundo, b2Vec2 pos,b2Vec2 tam,Dueno es,float dire,Texture2D tex);
	void actualizacion() override;
	void dibujar() override;
	void colision(Cuerpos* otro) override;
	b2Body* obtenerCuerpo();
	
};


#endif
