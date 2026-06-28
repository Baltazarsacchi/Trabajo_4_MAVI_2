#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "box2d.h"
#include "raylib.h"
#include <vector>
#include "Cuerpos.h"
#include "Proyectiles.h"

using namespace std;

const float Diferencia = 100.0f;

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

	Enemigo(b2World& mundo, b2Vec2 pos, b2Vec2 tam, Texture2D tex, Texture2D tex_2);

	void actualizacion() override;
	void dibujar() override;

	Proyectiles* disparo(b2World& mundo);

	void conexion(b2World& mundo, b2Body* cuerpo_2);

	void colision(Cuerpos* otro) override;

	bool vivo();

	void reinicio();


};

#endif // !ENEMIGO_H

