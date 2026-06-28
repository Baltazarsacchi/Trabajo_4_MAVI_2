#ifndef JUGADOR_H
#define JUGADOR_H
#include "box2d.h"
#include "raylib.h"
#include <iostream>
#include <vector>
#include "Cuerpos.h"
#include "Proyectiles.h"

using namespace std;

const float Escala = 100.0f;//Hago la trasformaicon de 1 metro = 100 px.

class Jugador : public Cuerpos {


private:

	b2Vec2 posicion;
	b2Vec2 tamano;
	Texture2D textura_1;
	Texture2D textura_2;
	vector<Proyectiles*> proyectil;

	int vidas = 3;

public:
	
	Jugador(b2World& mundo, b2Vec2 pos, b2Vec2 tam,Texture2D base,Texture2D arma);//Constructor de la clase jugador

	Proyectiles* disparo(b2World& mundo);//Creacion de los proyectriles del jugador

	void actualizacion() override;//Funciones heredadas
	void dibujar() override;

	void reinicio();//Reinicia atributos del jugador
	bool vivo();//Pregunta si esta vivo el jugador
	void colision(Cuerpos* otro) override;//Hace el chequo de las colisiones del jugador

};


#endif
