#ifndef JUGADOR_H
#define JUGADOR_H
#include "box2d.h"
#include "raylib.h"
#include <iostream>
#include <vector>
#include "Cuerpos.h"
#include "Proyectiles.h"

using namespace std;

const float Escala = 100.0f;

class Jugador : public Cuerpos {


private:

	b2Vec2 posicion;
	b2Vec2 tamano;
	Texture2D textura_1;
	Texture2D textura_2;
	vector<Proyectiles*> proyectil;

	int vidas = 3;

public:
	
	Jugador(b2World& mundo, b2Vec2 pos, b2Vec2 tam,Texture2D base,Texture2D arma);

	Proyectiles* disparo(b2World& mundo);

	void actualizacion() override;
	void dibujar() override;

	void reinicio();
	bool vivo();
	void colision(Cuerpos* otro) override;

};


#endif
