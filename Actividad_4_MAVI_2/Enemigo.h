#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "box2d.h"
#include "raylib.h"
#include <vector>
#include "Cuerpos.h"
#include "Proyectiles.h"

using namespace std;

const float Diferencia = 100.0f;//Escala que utilizo con la referencia de 1 metro = 100 px.

class Enemigo : public Cuerpos {

private:

	b2Vec2 posicion;
	b2Vec2 tamano;
	Texture2D textura;
	Texture2D textura_2;
	vector<Proyectiles*> proyectil;
	b2PrismaticJoint* joint;
	int direccion;

	int vida;

public:

	Enemigo(b2World& mundo, b2Vec2 pos, b2Vec2 tam, Texture2D tex, Texture2D tex_2);//Cnstructor

//Herencia de clase Cuerpos
	void actualizacion() override;
	void dibujar() override;

	Proyectiles* disparo(b2World& mundo);//Crea su propio proyectil

	void conexion(b2World& mundo, b2Body* cuerpo_2);//Hace la conexion con un objeto para moverse

	void colision(Cuerpos* otro) override;//Detecta sus colisiones

	bool vivo();//Pregunta si esta vivo el enemigo

	void reinicio();//Reinicia su atributo de vida


};

#endif // !ENEMIGO_H

