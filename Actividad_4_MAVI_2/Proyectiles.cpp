#include "box2d.h"
#include "raylib.h"
#include "Proyectiles.h"

Proyectiles::Proyectiles(b2World& mundo, b2Vec2 pos, b2Vec2 tam, Dueno es, float dire, Texture2D tex) {//Creaccion del cuerpo del proyectil, defino su tipo y desde quien fue lanzado

	tamano = tam;
	mando = es;
	textura = tex;

	destruccion = false;

	direccion = dire;

	tipo = Proyectil;

	b2BodyDef cuerpoDef;
	cuerpoDef.type = b2_dynamicBody;
	cuerpoDef.position.Set(pos.x, pos.y);
	cuerpo = mundo.CreateBody(&cuerpoDef);

	b2PolygonShape cuerpoShape;
	cuerpoShape.SetAsBox((tam.x / 8.0f) / Tamano, tam.y / Tamano);

	b2FixtureDef cuerpoFixture;
	cuerpoFixture.shape = &cuerpoShape;
	cuerpoFixture.density = 0.2f;
	cuerpoFixture.friction = 0.5f;
	cuerpoFixture.restitution = 0.0f;
	cuerpo->CreateFixture(&cuerpoFixture);

	cuerpo->GetUserData().pointer = (uintptr_t)this;

	actualizacion();
	

}

void Proyectiles::actualizacion() {//Le aplico una velocidad con su respectiva direccion
	b2Vec2 vel = cuerpo->GetLinearVelocity();
	vel.x = 0.0f;
	vel.y = 10.0f * direccion;

	cuerpo->SetLinearVelocity(vel);
}

void Proyectiles::dibujar() {//Dibujo los proyectiles 

	b2Vec2 posPro = cuerpo->GetPosition();

	Rectangle source = { 0, 0,(float)textura.width ,(float)textura.height };

	Rectangle dest = { posPro.x * Tamano, posPro.y * Tamano, tamano.x , tamano.y };

	Vector2 origin = { tamano.x / 2.0,tamano.y / 2.0f };

	DrawTexturePro(textura, source, dest, origin, 0.0f, WHITE);
}

void Proyectiles::colision(Cuerpos* otro) {//Detecta las respectivas colisiones que puede llegar a hacer el proyectil

	if (mando == Pj && otro->tipo == Personaje) { return; }
	if (mando == Em && otro->tipo == Enemigos) { return; }

	if (mando == Pj && (otro->tipo == Enemigos || otro->tipo == Estructura)) {

		destruccion = true;

	}
	if (mando == Em && (otro->tipo == Personaje || otro->tipo == Estructura)) {

		destruccion = true;
	}
	if (otro->tipo == Proyectil) {
		destruccion = true;
	}
	
}

b2Body* Proyectiles::obtenerCuerpo() {//Devuelve el cuerpo del proyectil
	return cuerpo;
}
